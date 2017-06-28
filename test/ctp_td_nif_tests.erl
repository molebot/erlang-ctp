%%% -*- coding: utf-8 -*-

-module(ctp_td_nif_tests).

-include_lib("eunit/include/eunit.hrl").
-include("ctp_record.hrl").
-include("ctp_define.hrl").

%% 请填写登录信息
-define(BROKER_ID, <<"">>).
-define(USER_ID, <<"">>).
-define(PASSWORD, <<"">>).

%% SimNow测试用前置机地址
-define(TD_FRONT_API, <<"tcp://180.168.146.187:10030">>).

%% SimNow模拟用前置机地址
-define(TD_FRONT_SIM, <<"tcp://180.168.146.187:10000">>).

td_test() ->
    {ok, Td} = ctp_td_nif:new(self()),
    ok = ctp_td_nif:create_api(Td, <<"/tmp/erlang_ctp_td_">>),

    {ok, Version} = ctp_td_nif:get_api_version(Td),
    ?debugFmt("api version: ~p~n", [Version]),

    ok = ctp_td_nif:register_front(Td, ?TD_FRONT_SIM),
    ok = ctp_td_nif:subscribe_private_topic(Td, ?THOST_TERT_QUICK),
    ok = ctp_td_nif:subscribe_public_topic(Td, ?THOST_TERT_QUICK),

    ok = ctp_td_nif:init(Td),
    receive
        {ctp_td, {on_front_connected}} ->
            ok
    after 1000 ->
            erlang:exit(timeout)
    end,

    ok = ctp_td_nif:req_user_login(Td, #cthost_ftdc_req_user_login_field{
                                          broker_id = ?BROKER_ID,
                                          user_id = ?USER_ID,
                                          password = ?PASSWORD
                                         }, 1),
    receive
        {ctp_td, {on_rsp_user_login, Data, Error, ReqId, Last}} ->
            ?debugFmt("on_rsp_user_login: ~p ~p ~p ~p~n", [Data, Error, ReqId, Last]),
            if Error#cthost_ftdc_rsp_info_field.error_id =/= 0 ->
                    erlang:exit(please_check_your_password);
               true ->
                    ok
            end
    after 1000 ->
            erlang:exit(timeout)
    end,

    {ok, TradingDay} = ctp_td_nif:get_trading_day(Td),
    ?debugFmt("trading day: ~p~n", [TradingDay]),

    ok = ctp_td_nif:req_qry_instrument(Td, #cthost_ftdc_qry_instrument_field{}, 2),
    receive
        {ctp_td, {on_rsp_qry_instrument, MarketData, _Error, _ReqId, _Last}} ->
            ?debugFmt("on_rtn_instrument_status: ~p ~n", [MarketData])
    after 1000 ->
            erlang:exit(timeout)
    end,

    ok = ctp_td_nif:exit(Td).
