%%% -*- coding: utf-8 -*-

-module(ctp_md_nif).
-on_load(init/0).
-include("ctp_record.hrl").

-export([new/1,
         create_api/2,
         get_api_version/1,
         init/1,
         exit/1,
         get_trading_day/1,
         register_front/2,
         register_name_server/2,
         register_fens_user_info/2,
         subscribe_market_data/2,
         un_subscribe_market_data/2,
         subscribe_for_quote_rsp/2,
         un_subscribe_for_quote_rsp/2,
         req_user_login/3,
         req_user_logout/3
        ]).

init() ->
    PrivDir = case code:priv_dir(?MODULE) of
                  {error, _} ->
                      EbinDir = filename:dirname(code:which(?MODULE)),
                      filename:join(filename:dirname(EbinDir), "priv");
                  Path ->
                      Path
              end,
    erlang:load_nif(filename:join(PrivDir, "ctp_md_nif"), 0).

%%% ----------------------------------------------------------------------------
%%% API函数
%%% ----------------------------------------------------------------------------

new(_Pid) ->
    erlang:exit(nif_library_not_loaded).

create_api(_Obj, _FlowPath) ->
    erlang:exit(nif_library_not_loaded).

get_api_version(_Obj) ->
    erlang:exit(nif_library_not_loaded).

init(_Obj) ->
    erlang:exit(nif_library_not_loaded).

exit(_Obj) ->
    erlang:exit(nif_library_not_loaded).

get_trading_day(_Obj) ->
    erlang:exit(nif_library_not_loaded).

register_front(_Obj, _FrontAddress) ->
    erlang:exit(nif_library_not_loaded).

register_name_server(_Obj, _NsAddress) ->
    erlang:exit(nif_library_not_loaded).

register_fens_user_info(_Obj, _Req) ->
    erlang:exit(nif_library_not_loaded).

subscribe_market_data(_Obj, _Ids) ->
    erlang:exit(nif_library_not_loaded).

un_subscribe_market_data(_Obj, _Ids) ->
    erlang:exit(nif_library_not_loaded).

subscribe_for_quote_rsp(_Obj, _Ids) ->
    erlang:exit(nif_library_not_loaded).

un_subscribe_for_quote_rsp(_Obj, _Ids) ->
    erlang:exit(nif_library_not_loaded).

req_user_login(_Obj, #cthost_ftdc_user_logout_field{} = _Req, _ReqId) ->
    erlang:exit(nif_library_not_loaded).

req_user_logout(_Obj, #cthost_ftdc_user_logout_field{} = _Req, _ReqId) ->
    erlang:exit(nif_library_not_loaded).
