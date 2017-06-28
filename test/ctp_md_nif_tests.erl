%%% -*- coding: utf-8 -*-

-module(ctp_md_nif_tests).

-include_lib("eunit/include/eunit.hrl").
-include("ctp_record.hrl").

%% SimNow测试用前置机地址
-define(MD_FRONT_API, <<"tcp://180.168.146.187:10031">>).

%% SimNow模拟用前置机地址
-define(MD_FRONT_SIM, <<"tcp://180.168.146.187:10010">>).

md_test() ->
    {ok, Md} = ctp_md_nif:new(self()),
    ok = ctp_md_nif:create_api(Md, <<"/tmp/erlang_ctp_">>),

    {ok, Version} = ctp_md_nif:get_api_version(Md),
    ?debugFmt("api version: ~p~n", [Version]),

    ok = ctp_md_nif:register_front(Md, ?MD_FRONT_SIM),

    ok = ctp_md_nif:init(Md),
    receive
        {ctp_md, {on_front_connected}} ->
            ok
    after 1000 ->
            erlang:exit(timeout)
    end,

    ok = ctp_md_nif:req_user_login(Md, #cthost_ftdc_req_user_login_field{}, 1),
    receive
        {ctp_md, {on_rsp_user_login, Data, Error, ReqId, Last}} ->
            ?debugFmt("on_rsp_user_login: ~p ~p ~p ~p~n", [Data, Error, ReqId, Last])
    after 1000 ->
            erlang:exit(timeout)
    end,

    {ok, TradingDay} = ctp_md_nif:get_trading_day(Md),
    ?debugFmt("trading day: ~p~n", [TradingDay]),

    ok = ctp_md_nif:subscribe_market_data(Md, [<<"SR709">>]),
    receive
        {ctp_md, {on_rtn_depth_market_data, MarketData}} ->
            ?debugFmt("on_rtn_depth_market_data: ~p~n", [MarketData])
    after 1000 ->
            ok
    end,

    ok = ctp_md_nif:exit(Md).
