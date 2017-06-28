%%% -*- coding: utf-8 -*-

-module(ctp_md_nif).

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

-define(NIF_STUB, erlang:nif_error(nif_library_not_loaded)).

-on_load(init/0).

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
    ?NIF_STUB.

create_api(_Obj, _FlowPath) ->
    ?NIF_STUB.

get_api_version(_Obj) ->
    ?NIF_STUB.

init(_Obj) ->
    ?NIF_STUB.

exit(_Obj) ->
    ?NIF_STUB.

get_trading_day(_Obj) ->
    ?NIF_STUB.

register_front(_Obj, _FrontAddress) ->
    ?NIF_STUB.

register_name_server(_Obj, _NsAddress) ->
    ?NIF_STUB.

register_fens_user_info(_Obj, _Req) ->
    ?NIF_STUB.

subscribe_market_data(_Obj, _Ids) ->
    ?NIF_STUB.

un_subscribe_market_data(_Obj, _Ids) ->
    ?NIF_STUB.

subscribe_for_quote_rsp(_Obj, _Ids) ->
    ?NIF_STUB.

un_subscribe_for_quote_rsp(_Obj, _Ids) ->
    ?NIF_STUB.

req_user_login(_Obj, #cthost_ftdc_user_logout_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_user_logout(_Obj, #cthost_ftdc_user_logout_field{} = _Req, _ReqId) ->
    ?NIF_STUB.
