#include "ctp_md.h"
#include <iostream>
#include <stdio.h>
#include <string.h>

CtpMd::CtpMd(ErlNifPid pid) : pid_(pid), api_(NULL) {}

CtpMd::~CtpMd() { this->Exit(); }

/* -------------------------------------------------------------------------
 * API接口
 * -------------------------------------------------------------------------
 */

void CtpMd::CreateApi(const ErlNifBinary *flow_path) {
  this->api_ = CThostFtdcMdApi::CreateFtdcMdApi(
      std::string(reinterpret_cast<char *>(flow_path->data), flow_path->size)
          .c_str());
  this->api_->RegisterSpi(this);
}

ERL_NIF_TERM CtpMd::GetApiVersion(ErlNifEnv *env) {
  ERL_NIF_TERM term;
  std::string str = this->api_->GetApiVersion();
  memcpy(enif_make_new_binary(env, str.size(), &term), str.c_str(), str.size());
  return term;
}

void CtpMd::Init() { this->api_->Init(); }

void CtpMd::Exit() {
  if (this->api_) {
    this->api_->RegisterSpi(NULL);
    this->api_->Release();
    this->api_ = NULL;
  }
}

ERL_NIF_TERM CtpMd::GetTradingDay(ErlNifEnv *env) {
  ERL_NIF_TERM term;
  std::string str = this->api_->GetTradingDay();
  memcpy(enif_make_new_binary(env, str.size(), &term), str.c_str(), str.size());
  return term;
}

void CtpMd::RegisterFront(const ErlNifBinary *front_address) {
  this->api_->RegisterFront(const_cast<char *>(
      std::string(reinterpret_cast<char *>(front_address->data),
                  front_address->size)
          .c_str()));
}

void CtpMd::RegisterNameServer(const ErlNifBinary *ns_address) {
  this->api_->RegisterNameServer(const_cast<char *>(
      std::string(reinterpret_cast<char *>(ns_address->data), ns_address->size)
          .c_str()));
}

void CtpMd::RegisterFensUserInfo(ErlNifEnv *env, const NifRecord *req) {
  int n = 1;
  CThostFtdcFensUserInfoField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.UserID), creq.UserID);
  ErlNifGetChar(env, req, n++, &creq.LoginMode);
}

int CtpMd::SubscribeMarketData(ErlNifEnv *env, ERL_NIF_TERM list) {
  ERL_NIF_TERM head, tail;

  while (enif_get_list_cell(env, list, &head, &tail)) {
    ErlNifBinary bin;
    if (enif_inspect_binary(env, head, &bin)) {
      if (bin.size) {
        std::string str(reinterpret_cast<char *>(bin.data), bin.size);
        char *ids[1] = {const_cast<char *>(str.c_str())};
        this->api_->SubscribeMarketData(ids, 1);
      }
    }
    list = tail;
  }

  return 0;
}

int CtpMd::UnSubscribeMarketData(ErlNifEnv *env, ERL_NIF_TERM list) {
  ERL_NIF_TERM head, tail;

  while (enif_get_list_cell(env, list, &head, &tail)) {
    ErlNifBinary bin;
    if (enif_inspect_binary(env, head, &bin)) {
      if (bin.size) {
        std::string str(reinterpret_cast<char *>(bin.data), bin.size);
        char *ids[1] = {const_cast<char *>(str.c_str())};
        this->api_->UnSubscribeMarketData(ids, 1);
      }
    }
    list = tail;
  }

  return 0;
}

int CtpMd::SubscribeForQuoteRsp(ErlNifEnv *env, ERL_NIF_TERM list) {
  ERL_NIF_TERM head, tail;

  while (enif_get_list_cell(env, list, &head, &tail)) {
    ErlNifBinary bin;
    if (enif_inspect_binary(env, head, &bin)) {
      if (bin.size) {
        std::string str(reinterpret_cast<char *>(bin.data), bin.size);
        char *ids[1] = {const_cast<char *>(str.c_str())};
        this->api_->SubscribeForQuoteRsp(ids, 1);
      }
    }
    list = tail;
  }

  return 0;
}

int CtpMd::UnSubscribeForQuoteRsp(ErlNifEnv *env, ERL_NIF_TERM list) {
  ERL_NIF_TERM head, tail;

  while (enif_get_list_cell(env, list, &head, &tail)) {
    ErlNifBinary bin;
    if (enif_inspect_binary(env, head, &bin)) {
      if (bin.size) {
        std::string str(reinterpret_cast<char *>(bin.data), bin.size);
        char *ids[1] = {const_cast<char *>(str.c_str())};
        this->api_->UnSubscribeForQuoteRsp(ids, 1);
      }
    }
    list = tail;
  }

  return 0;
}

int CtpMd::ReqUserLogin(ErlNifEnv *env, const NifRecord *req, int req_id) {
  int n = 1;
  CThostFtdcReqUserLoginField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.TradingDay), creq.TradingDay);
  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.UserID), creq.UserID);
  ErlNifGetString(env, req, n++, sizeof(creq.Password), creq.Password);
  ErlNifGetString(env, req, n++, sizeof(creq.UserProductInfo),
                  creq.UserProductInfo);
  ErlNifGetString(env, req, n++, sizeof(creq.InterfaceProductInfo),
                  creq.InterfaceProductInfo);
  ErlNifGetString(env, req, n++, sizeof(creq.ProtocolInfo), creq.ProtocolInfo);
  ErlNifGetString(env, req, n++, sizeof(creq.MacAddress), creq.MacAddress);
  ErlNifGetString(env, req, n++, sizeof(creq.OneTimePassword),
                  creq.OneTimePassword);
  ErlNifGetString(env, req, n++, sizeof(creq.ClientIPAddress),
                  creq.ClientIPAddress);
  ErlNifGetString(env, req, n++, sizeof(creq.LoginRemark), creq.LoginRemark);

  return this->api_->ReqUserLogin(&creq, req_id);
}

int CtpMd::ReqUserLogout(ErlNifEnv *env, const NifRecord *req, int req_id) {
  int n = 1;
  CThostFtdcUserLogoutField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.UserID), creq.UserID);

  return this->api_->ReqUserLogout(&creq, req_id);
}

/* ---------------------------------------------------------------------------
 * SPI接口
 * ---------------------------------------------------------------------------
 */

void CtpMd::OnFrontConnected() {
  ErlNifEnv *env = enif_alloc_env();
  enif_send(
      NULL, &this->pid_, env,
      enif_make_tuple2(
          env, enif_make_atom(env, "ctp_md"),
          enif_make_tuple1(env, enif_make_atom(env, "on_front_connected"))));
  enif_free_env(env);
}

void CtpMd::OnFrontDisconnected(int reason) {
  ErlNifEnv *env = enif_alloc_env();
  enif_send(
      NULL, &this->pid_, env,
      enif_make_tuple2(
          env, enif_make_atom(env, "ctp_md"),
          enif_make_tuple2(env, enif_make_atom(env, "on_front_disconnected"),
                           enif_make_int(env, reason))));
  enif_free_env(env);
}

void CtpMd::OnHeartBeatWarning(int time_lapse) {
  ErlNifEnv *env = enif_alloc_env();
  enif_send(
      NULL, &this->pid_, env,
      enif_make_tuple2(
          env, enif_make_atom(env, "ctp_md"),
          enif_make_tuple2(env, enif_make_atom(env, "on_heart_beat_warnning"),
                           enif_make_int(env, time_lapse))));
  enif_free_env(env);
}

void CtpMd::OnRspUserLogin(CThostFtdcRspUserLoginField *data,
                           CThostFtdcRspInfoField *error, int req_id,
                           bool last) {
  static CThostFtdcRspUserLoginField empty_data = {};
  static CThostFtdcRspInfoField empty_error = {};

  if (!data) {
    data = &empty_data;
  }
  if (!error) {
    error = &empty_error;
  }

  ErlNifEnv *env = enif_alloc_env();
  enif_send(
      NULL, &this->pid_, env,
      enif_make_tuple2(
          env, enif_make_atom(env, "ctp_md"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_user_login"),
              enif_make_tuple(
                  env, 14,
                  enif_make_atom(env, "cthost_ftdc_rsp_user_login_field"),
                  ErlNifMakeGbkBinary(env, data->TradingDay),
                  ErlNifMakeGbkBinary(env, data->LoginTime),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  ErlNifMakeGbkBinary(env, data->SystemName),
                  enif_make_int(env, data->FrontID),
                  enif_make_int(env, data->SessionID),
                  ErlNifMakeGbkBinary(env, data->MaxOrderRef),
                  ErlNifMakeGbkBinary(env, data->SHFETime),
                  ErlNifMakeGbkBinary(env, data->DCETime),
                  ErlNifMakeGbkBinary(env, data->CZCETime),
                  ErlNifMakeGbkBinary(env, data->FFEXTime),
                  ErlNifMakeGbkBinary(env, data->INETime)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpMd::OnRspUserLogout(CThostFtdcUserLogoutField *data,
                            CThostFtdcRspInfoField *error, int req_id,
                            bool last) {
  static CThostFtdcUserLogoutField empty_data = {};
  static CThostFtdcRspInfoField empty_error = {};

  if (!data) {
    data = &empty_data;
  }
  if (!error) {
    error = &empty_error;
  }

  ErlNifEnv *env = enif_alloc_env();
  enif_send(
      NULL, &this->pid_, env,
      enif_make_tuple2(
          env, enif_make_atom(env, "ctp_md"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_user_logout"),
              enif_make_tuple(
                  env, 3, enif_make_atom(env, "cthost_ftdc_user_logout_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->UserID)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpMd::OnRspError(CThostFtdcRspInfoField *error, int req_id, bool last) {
  static CThostFtdcRspInfoField empty_error = {};

  if (!error) {
    error = &empty_error;
  }

  ErlNifEnv *env = enif_alloc_env();
  enif_send(
      NULL, &this->pid_, env,
      enif_make_tuple2(
          env, enif_make_atom(env, "ctp_md"),
          enif_make_tuple4(
              env, enif_make_atom(env, "on_rsp_error"),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpMd::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *data,
                               CThostFtdcRspInfoField *error, int req_id,
                               bool last) {
  static CThostFtdcSpecificInstrumentField empty_data = {};
  static CThostFtdcRspInfoField empty_error = {};

  if (!data) {
    data = &empty_data;
  }
  if (!error) {
    error = &empty_error;
  }

  ErlNifEnv *env = enif_alloc_env();
  enif_send(
      NULL, &this->pid_, env,
      enif_make_tuple2(
          env, enif_make_atom(env, "ctp_md"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_sub_market_data"),
              enif_make_tuple(
                  env, 2,
                  enif_make_atom(env, "cthost_ftdc_specific_instrument_field"),
                  ErlNifMakeGbkBinary(env, data->InstrumentID)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpMd::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *data,
                                 CThostFtdcRspInfoField *error, int req_id,
                                 bool last) {
  static CThostFtdcSpecificInstrumentField empty_data = {};
  static CThostFtdcRspInfoField empty_error = {};

  if (!data) {
    data = &empty_data;
  }
  if (!error) {
    error = &empty_error;
  }

  ErlNifEnv *env = enif_alloc_env();
  enif_send(
      NULL, &this->pid_, env,
      enif_make_tuple2(
          env, enif_make_atom(env, "ctp_md"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_un_sub_market_data"),
              enif_make_tuple(
                  env, 2,
                  enif_make_atom(env, "cthost_ftdc_specific_instrument_field"),
                  ErlNifMakeGbkBinary(env, data->InstrumentID)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpMd::OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *data,
                                CThostFtdcRspInfoField *error, int req_id,
                                bool last) {
  static CThostFtdcSpecificInstrumentField empty_data = {};
  static CThostFtdcRspInfoField empty_error = {};

  if (!data) {
    data = &empty_data;
  }
  if (!error) {
    error = &empty_error;
  }

  ErlNifEnv *env = enif_alloc_env();
  enif_send(
      NULL, &this->pid_, env,
      enif_make_tuple2(
          env, enif_make_atom(env, "ctp_md"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_sub_for_quote_rsp"),
              enif_make_tuple(
                  env, 2,
                  enif_make_atom(env, "cthost_ftdc_specific_instrument_field"),
                  ErlNifMakeGbkBinary(env, data->InstrumentID)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpMd::OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *data,
                                  CThostFtdcRspInfoField *error, int req_id,
                                  bool last) {
  static CThostFtdcSpecificInstrumentField empty_data = {};
  static CThostFtdcRspInfoField empty_error = {};

  if (!data) {
    data = &empty_data;
  }
  if (!error) {
    error = &empty_error;
  }

  ErlNifEnv *env = enif_alloc_env();
  enif_send(
      NULL, &this->pid_, env,
      enif_make_tuple2(
          env, enif_make_atom(env, "ctp_md"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_un_sub_for_quote_rsp"),
              enif_make_tuple(
                  env, 2,
                  enif_make_atom(env, "cthost_ftdc_specific_instrument_field"),
                  ErlNifMakeGbkBinary(env, data->InstrumentID)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpMd::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *data) {
  static CThostFtdcDepthMarketDataField empty_data = {};

  if (!data) {
    data = &empty_data;
  }

  ErlNifEnv *env = enif_alloc_env();
  enif_send(
      NULL, &this->pid_, env,
      enif_make_tuple2(
          env, enif_make_atom(env, "ctp_md"),
          enif_make_tuple2(
              env, enif_make_atom(env, "on_rtn_depth_market_data"),
              enif_make_tuple(
                  env, 45,
                  enif_make_atom(env, "cthost_ftdc_depth_market_data_field"),
                  ErlNifMakeGbkBinary(env, data->TradingDay),
                  ErlNifMakeGbkBinary(env, data->InstrumentID),
                  ErlNifMakeGbkBinary(env, data->ExchangeID),
                  ErlNifMakeGbkBinary(env, data->ExchangeInstID),
                  enif_make_double(env, data->LastPrice),
                  enif_make_double(env, data->PreSettlementPrice),
                  enif_make_double(env, data->PreClosePrice),
                  enif_make_double(env, data->PreOpenInterest),
                  enif_make_double(env, data->OpenPrice),
                  enif_make_double(env, data->HighestPrice),
                  enif_make_double(env, data->LowestPrice),
                  enif_make_int(env, data->Volume),
                  enif_make_double(env, data->Turnover),
                  enif_make_double(env, data->OpenInterest),
                  enif_make_double(env, data->ClosePrice),
                  enif_make_double(env, data->SettlementPrice),
                  enif_make_double(env, data->UpperLimitPrice),
                  enif_make_double(env, data->LowerLimitPrice),
                  enif_make_double(env, data->PreDelta),
                  enif_make_double(env, data->CurrDelta),
                  ErlNifMakeGbkBinary(env, data->UpdateTime),
                  enif_make_int(env, data->UpdateMillisec),
                  enif_make_double(env, data->BidPrice1),
                  enif_make_int(env, data->BidVolume1),
                  enif_make_double(env, data->AskPrice1),
                  enif_make_int(env, data->AskVolume1),
                  enif_make_double(env, data->BidPrice2),
                  enif_make_int(env, data->BidVolume2),
                  enif_make_double(env, data->AskPrice2),
                  enif_make_int(env, data->AskVolume2),
                  enif_make_double(env, data->BidPrice3),
                  enif_make_int(env, data->BidVolume3),
                  enif_make_double(env, data->AskPrice3),
                  enif_make_int(env, data->AskVolume3),
                  enif_make_double(env, data->BidPrice4),
                  enif_make_int(env, data->BidVolume4),
                  enif_make_double(env, data->AskPrice4),
                  enif_make_int(env, data->AskVolume4),
                  enif_make_double(env, data->BidPrice5),
                  enif_make_int(env, data->BidVolume5),
                  enif_make_double(env, data->AskPrice5),
                  enif_make_int(env, data->AskVolume5),
                  enif_make_double(env, data->AveragePrice),
                  ErlNifMakeGbkBinary(env, data->ActionDay)))));
  enif_free_env(env);
}

void CtpMd::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *data) {
  static CThostFtdcForQuoteRspField empty_data = {};

  if (!data) {
    data = &empty_data;
  }

  ErlNifEnv *env = enif_alloc_env();
  enif_send(NULL, &this->pid_, env,
            enif_make_tuple2(
                env, enif_make_atom(env, "ctp_md"),
                enif_make_tuple2(
                    env, enif_make_atom(env, "on_rtn_for_quote_rsp"),
                    enif_make_tuple(
                        env, 7,
                        enif_make_atom(env, "cthost_ftdc_for_quote_rsp_field"),
                        ErlNifMakeGbkBinary(env, data->TradingDay),
                        ErlNifMakeGbkBinary(env, data->InstrumentID),
                        ErlNifMakeGbkBinary(env, data->ForQuoteSysID),
                        ErlNifMakeGbkBinary(env, data->ForQuoteTime),
                        ErlNifMakeGbkBinary(env, data->ActionDay),
                        ErlNifMakeGbkBinary(env, data->ExchangeID)))));
  enif_free_env(env);
}
