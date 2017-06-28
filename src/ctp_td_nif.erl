%%% -*- coding: utf-8 -*-

-module(ctp_td_nif).

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
         subscribe_private_topic/2,
         subscribe_public_topic/2,
         req_authenticate/3,
         req_user_login/3,
         req_user_logout/3,
         req_user_password_update/3,
         req_trading_account_password_update/3,
         req_order_insert/3,
         req_parked_order_insert/3,
         req_parked_order_action/3,
         req_order_action/3,
         req_query_max_order_volume/3,
         req_settlement_info_confirm/3,
         req_remove_parked_order/3,
         req_remove_parked_order_action/3,
         req_exec_order_insert/3,
         req_exec_order_action/3,
         req_for_quote_insert/3,
         req_quote_insert/3,
         req_quote_action/3,
         req_lock_insert/3,
         req_batch_order_action/3,
         req_comb_action_insert/3,
         req_qry_order/3,
         req_qry_trade/3,
         req_qry_investor_position/3,
         req_qry_trading_account/3,
         req_qry_investor/3,
         req_qry_trading_code/3,
         req_qry_instrument_margin_rate/3,
         req_qry_instrument_commission_rate/3,
         req_qry_exchange/3,
         req_qry_product/3,
         req_qry_instrument/3,
         req_qry_depth_market_data/3,
         req_qry_settlement_info/3,
         req_qry_transfer_bank/3,
         req_qry_investor_position_detail/3,
         req_qry_notice/3,
         req_qry_settlement_info_confirm/3,
         req_qry_investor_position_combine_detail/3,
         req_qry_cfmmctrading_account_key/3,
         req_qry_ewarrant_offset/3,
         req_qry_investor_product_group_margin/3,
         req_qry_exchange_margin_rate/3,
         req_qry_exchange_margin_rate_adjust/3,
         req_qry_exchange_rate/3,
         req_qry_sec_agent_acidmap/3,
         req_qry_product_exch_rate/3,
         req_qry_product_group/3,
         req_qry_mminstrument_commission_rate/3,
         req_qry_mmoption_instr_comm_rate/3,
         req_qry_instrument_order_comm_rate/3,
         req_qry_option_instr_trade_cost/3,
         req_qry_option_instr_comm_rate/3,
         req_qry_exec_order/3,
         req_qry_for_quote/3,
         req_qry_quote/3,
         req_qry_lock/3,
         req_qry_lock_position/3,
         req_qry_etfoption_instr_comm_rate/3,
         req_qry_investor_level/3,
         req_qry_exec_freeze/3,
         req_qry_comb_instrument_guard/3,
         req_qry_comb_action/3,
         req_qry_transfer_serial/3,
         req_qry_accountregister/3,
         req_qry_contract_bank/3,
         req_qry_parked_order/3,
         req_qry_parked_order_action/3,
         req_qry_trading_notice/3,
         req_qry_broker_trading_params/3,
         req_qry_broker_trading_algos/3,
         req_query_cfmmctrading_account_token/3,
         req_from_bank_to_future_by_future/3,
         req_from_future_to_bank_by_future/3,
         req_query_bank_account_money_by_future/3
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
    erlang:load_nif(filename:join(PrivDir, "ctp_td_nif"), 0).

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

subscribe_private_topic(_Obj, _ResumeType) ->
    ?NIF_STUB.

subscribe_public_topic(_Obj, _ResumeType) ->
    ?NIF_STUB.

req_authenticate(_Obj, #cthost_ftdc_req_authenticate_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_user_login(_Obj, #cthost_ftdc_req_user_login_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_user_logout(_Obj, #cthost_ftdc_user_logout_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_user_password_update(_Obj, #cthost_ftdc_user_password_update_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_trading_account_password_update(_Obj, #cthost_ftdc_trading_account_password_update_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_order_insert(_Obj, #cthost_ftdc_input_order_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_parked_order_insert(_Obj, #cthost_ftdc_parked_order_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_parked_order_action(_Obj, #cthost_ftdc_parked_order_action_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_order_action(_Obj, #cthost_ftdc_input_order_action_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_query_max_order_volume(_Obj, #cthost_ftdc_query_max_order_volume_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_settlement_info_confirm(_Obj, #cthost_ftdc_settlement_info_confirm_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_remove_parked_order(_Obj, #cthost_ftdc_remove_parked_order_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_remove_parked_order_action(_Obj, #cthost_ftdc_remove_parked_order_action_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_exec_order_insert(_Obj, #cthost_ftdc_input_exec_order_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_exec_order_action(_Obj, #cthost_ftdc_input_exec_order_action_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_for_quote_insert(_Obj, #cthost_ftdc_input_for_quote_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_quote_insert(_Obj, #cthost_ftdc_input_quote_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_quote_action(_Obj, #cthost_ftdc_input_quote_action_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_lock_insert(_Obj, #cthost_ftdc_input_lock_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_batch_order_action(_Obj, #cthost_ftdc_input_batch_order_action_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_comb_action_insert(_Obj, #cthost_ftdc_input_comb_action_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_qry_order(_Obj, #cthost_ftdc_qry_order_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_qry_trade(_Obj, #cthost_ftdc_qry_trade_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_qry_investor_position(_Obj, #cthost_ftdc_qry_investor_position_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_qry_trading_account(_Obj, #cthost_ftdc_qry_trading_account_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_qry_investor(_Obj, #cthost_ftdc_qry_investor_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_qry_trading_code(_Obj, #cthost_ftdc_qry_trading_code_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_qry_instrument_margin_rate(_Obj, #cthost_ftdc_qry_instrument_margin_rate_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_qry_instrument_commission_rate(_Obj, #cthost_ftdc_qry_instrument_commission_rate_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_qry_exchange(_Obj, #cthost_ftdc_qry_exchange_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_qry_product(_Obj, #cthost_ftdc_qry_product_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_qry_instrument(_Obj, #cthost_ftdc_qry_instrument_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_qry_depth_market_data(_Obj, #cthost_ftdc_qry_depth_market_data_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_qry_settlement_info(_Obj, #cthost_ftdc_qry_settlement_info_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_qry_transfer_bank(_Obj, #cthost_ftdc_qry_transfer_bank_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_qry_investor_position_detail(_Obj, #cthost_ftdc_qry_investor_position_detail_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_qry_notice(_Obj, #cthost_ftdc_qry_notice_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_qry_settlement_info_confirm(_Obj, #cthost_ftdc_qry_settlement_info_confirm_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_qry_investor_position_combine_detail(_Obj, #cthost_ftdc_qry_investor_position_combine_detail_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_qry_cfmmctrading_account_key(_Obj, #cthost_ftdc_qry_cfmmctrading_account_key_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_qry_ewarrant_offset(_Obj, #cthost_ftdc_qry_ewarrant_offset_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_qry_investor_product_group_margin(_Obj, #cthost_ftdc_qry_investor_product_group_margin_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_qry_exchange_margin_rate(_Obj, #cthost_ftdc_qry_exchange_margin_rate_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_qry_exchange_margin_rate_adjust(_Obj, #cthost_ftdc_qry_exchange_margin_rate_adjust_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_qry_exchange_rate(_Obj, #cthost_ftdc_qry_exchange_rate_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_qry_sec_agent_acidmap(_Obj, #cthost_ftdc_qry_sec_agent_acidmap_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_qry_product_exch_rate(_Obj, #cthost_ftdc_qry_product_exch_rate_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_qry_product_group(_Obj, #cthost_ftdc_qry_product_group_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_qry_mminstrument_commission_rate(_Obj, #cthost_ftdc_qry_mminstrument_commission_rate_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_qry_mmoption_instr_comm_rate(_Obj, #cthost_ftdc_qry_mmoption_instr_comm_rate_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_qry_instrument_order_comm_rate(_Obj, #cthost_ftdc_qry_instrument_order_comm_rate_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_qry_option_instr_trade_cost(_Obj, #cthost_ftdc_qry_option_instr_trade_cost_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_qry_option_instr_comm_rate(_Obj, #cthost_ftdc_qry_option_instr_comm_rate_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_qry_exec_order(_Obj, #cthost_ftdc_qry_exec_order_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_qry_for_quote(_Obj, #cthost_ftdc_qry_for_quote_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_qry_quote(_Obj, #cthost_ftdc_qry_quote_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_qry_lock(_Obj, #cthost_ftdc_qry_lock_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_qry_lock_position(_Obj, #cthost_ftdc_qry_lock_position_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_qry_etfoption_instr_comm_rate(_Obj, #cthost_ftdc_qry_etfoption_instr_comm_rate_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_qry_investor_level(_Obj, #cthost_ftdc_qry_investor_level_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_qry_exec_freeze(_Obj, #cthost_ftdc_qry_exec_freeze_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_qry_comb_instrument_guard(_Obj, #cthost_ftdc_qry_comb_instrument_guard_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_qry_comb_action(_Obj, #cthost_ftdc_qry_comb_action_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_qry_transfer_serial(_Obj, #cthost_ftdc_qry_transfer_serial_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_qry_accountregister(_Obj, #cthost_ftdc_qry_accountregister_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_qry_contract_bank(_Obj, #cthost_ftdc_qry_contract_bank_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_qry_parked_order(_Obj, #cthost_ftdc_qry_parked_order_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_qry_parked_order_action(_Obj, #cthost_ftdc_qry_parked_order_action_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_qry_trading_notice(_Obj, #cthost_ftdc_qry_trading_notice_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_qry_broker_trading_params(_Obj, #cthost_ftdc_qry_broker_trading_params_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_qry_broker_trading_algos(_Obj, #cthost_ftdc_qry_broker_trading_algos_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_query_cfmmctrading_account_token(_Obj, #cthost_ftdc_query_cfmmctrading_account_token_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_from_bank_to_future_by_future(_Obj, #cthost_ftdc_req_transfer_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_from_future_to_bank_by_future(_Obj, #cthost_ftdc_req_transfer_field{} = _Req, _ReqId) ->
    ?NIF_STUB.

req_query_bank_account_money_by_future(_Obj, #cthost_ftdc_req_query_account_field{} = _Req, _ReqId) ->
    ?NIF_STUB.
