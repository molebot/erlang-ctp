#include "ctp_td.h"
#include <iostream>
#include <stdio.h>
#include <string.h>

CtpTd::CtpTd(ErlNifPid pid) : pid_(pid), api_(NULL) {}

CtpTd::~CtpTd() { this->Exit(); }

/* -------------------------------------------------------------------------
 * API接口
 * -------------------------------------------------------------------------
 */

void CtpTd::CreateApi(const ErlNifBinary *flow_path) {
  this->api_ = CThostFtdcTraderApi::CreateFtdcTraderApi(
      std::string(reinterpret_cast<char *>(flow_path->data), flow_path->size)
          .c_str());
  this->api_->RegisterSpi(this);
}

ERL_NIF_TERM CtpTd::GetApiVersion(ErlNifEnv *env) {
  ERL_NIF_TERM term;
  std::string str = this->api_->GetApiVersion();
  memcpy(enif_make_new_binary(env, str.size(), &term), str.c_str(), str.size());
  return term;
}

void CtpTd::Init() { this->api_->Init(); }

void CtpTd::Exit() {
  if (this->api_) {
    this->api_->RegisterSpi(NULL);
    this->api_->Release();
    this->api_ = NULL;
  }
}

ERL_NIF_TERM CtpTd::GetTradingDay(ErlNifEnv *env) {
  ERL_NIF_TERM term;
  std::string str = this->api_->GetTradingDay();
  memcpy(enif_make_new_binary(env, str.size(), &term), str.c_str(), str.size());
  return term;
}

void CtpTd::RegisterFront(const ErlNifBinary *front_address) {
  this->api_->RegisterFront(const_cast<char *>(
      std::string(reinterpret_cast<char *>(front_address->data),
                  front_address->size)
          .c_str()));
}

void CtpTd::RegisterNameServer(const ErlNifBinary *ns_address) {
  this->api_->RegisterNameServer(const_cast<char *>(
      std::string(reinterpret_cast<char *>(ns_address->data), ns_address->size)
          .c_str()));
}

void CtpTd::RegisterFensUserInfo(ErlNifEnv *env, const NifRecord *req) {
  int n = 1;
  CThostFtdcFensUserInfoField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.UserID), creq.UserID);
  ErlNifGetChar(env, req, n++, &creq.LoginMode);
}

void CtpTd::SubscribePrivateTopic(int resume_type) {
  this->api_->SubscribePrivateTopic(
      static_cast<THOST_TE_RESUME_TYPE>(resume_type));
}

void CtpTd::SubscribePublicTopic(int resume_type) {
  this->api_->SubscribePublicTopic(
      static_cast<THOST_TE_RESUME_TYPE>(resume_type));
}

int CtpTd::ReqAuthenticate(ErlNifEnv *env, NifRecord *req, int req_id) {
  int n = 1;
  CThostFtdcReqAuthenticateField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.UserID), creq.UserID);
  ErlNifGetString(env, req, n++, sizeof(creq.UserProductInfo),
                  creq.UserProductInfo);
  ErlNifGetString(env, req, n++, sizeof(creq.AuthCode), creq.AuthCode);

  return this->api_->ReqAuthenticate(&creq, req_id);
}

int CtpTd::ReqUserLogin(ErlNifEnv *env, NifRecord *req, int req_id) {
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

int CtpTd::ReqUserLogout(ErlNifEnv *env, NifRecord *req, int req_id) {
  int n = 1;
  CThostFtdcUserLogoutField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.UserID), creq.UserID);

  return this->api_->ReqUserLogout(&creq, req_id);
}

int CtpTd::ReqUserPasswordUpdate(ErlNifEnv *env, NifRecord *req, int req_id) {
  int n = 1;
  CThostFtdcUserPasswordUpdateField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.UserID), creq.UserID);
  ErlNifGetString(env, req, n++, sizeof(creq.OldPassword), creq.OldPassword);
  ErlNifGetString(env, req, n++, sizeof(creq.NewPassword), creq.NewPassword);

  return this->api_->ReqUserPasswordUpdate(&creq, req_id);
}

int CtpTd::ReqTradingAccountPasswordUpdate(ErlNifEnv *env, NifRecord *req,
                                           int req_id) {
  int n = 1;
  CThostFtdcTradingAccountPasswordUpdateField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.AccountID), creq.AccountID);
  ErlNifGetString(env, req, n++, sizeof(creq.OldPassword), creq.OldPassword);
  ErlNifGetString(env, req, n++, sizeof(creq.NewPassword), creq.NewPassword);
  ErlNifGetString(env, req, n++, sizeof(creq.CurrencyID), creq.CurrencyID);

  return this->api_->ReqTradingAccountPasswordUpdate(&creq, req_id);
}

int CtpTd::ReqOrderInsert(ErlNifEnv *env, NifRecord *req, int req_id) {
  int n = 1;
  CThostFtdcInputOrderField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestorID), creq.InvestorID);
  ErlNifGetString(env, req, n++, sizeof(creq.InstrumentID), creq.InstrumentID);
  ErlNifGetString(env, req, n++, sizeof(creq.OrderRef), creq.OrderRef);
  ErlNifGetString(env, req, n++, sizeof(creq.UserID), creq.UserID);
  ErlNifGetChar(env, req, n++, &creq.OrderPriceType);
  ErlNifGetChar(env, req, n++, &creq.Direction);
  ErlNifGetString(env, req, n++, sizeof(creq.CombOffsetFlag),
                  creq.CombOffsetFlag);
  ErlNifGetString(env, req, n++, sizeof(creq.CombHedgeFlag),
                  creq.CombHedgeFlag);
  ErlNifGetDouble(env, req, n++, &creq.LimitPrice);
  ErlNifGetInt(env, req, n++, &creq.VolumeTotalOriginal);
  ErlNifGetChar(env, req, n++, &creq.TimeCondition);
  ErlNifGetString(env, req, n++, sizeof(creq.GTDDate), creq.GTDDate);
  ErlNifGetChar(env, req, n++, &creq.VolumeCondition);
  ErlNifGetInt(env, req, n++, &creq.MinVolume);
  ErlNifGetChar(env, req, n++, &creq.ContingentCondition);
  ErlNifGetDouble(env, req, n++, &creq.StopPrice);
  ErlNifGetChar(env, req, n++, &creq.ForceCloseReason);
  ErlNifGetInt(env, req, n++, &creq.IsAutoSuspend);
  ErlNifGetString(env, req, n++, sizeof(creq.BusinessUnit), creq.BusinessUnit);
  ErlNifGetInt(env, req, n++, &creq.RequestID);
  ErlNifGetInt(env, req, n++, &creq.UserForceClose);
  ErlNifGetInt(env, req, n++, &creq.IsSwapOrder);
  ErlNifGetString(env, req, n++, sizeof(creq.ExchangeID), creq.ExchangeID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestUnitID), creq.InvestUnitID);
  ErlNifGetString(env, req, n++, sizeof(creq.AccountID), creq.AccountID);
  ErlNifGetString(env, req, n++, sizeof(creq.CurrencyID), creq.CurrencyID);
  ErlNifGetString(env, req, n++, sizeof(creq.ClientID), creq.ClientID);
  ErlNifGetString(env, req, n++, sizeof(creq.IPAddress), creq.IPAddress);
  ErlNifGetString(env, req, n++, sizeof(creq.MacAddress), creq.MacAddress);

  return this->api_->ReqOrderInsert(&creq, req_id);
}

int CtpTd::ReqParkedOrderInsert(ErlNifEnv *env, NifRecord *req, int req_id) {
  int n = 1;
  CThostFtdcParkedOrderField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestorID), creq.InvestorID);
  ErlNifGetString(env, req, n++, sizeof(creq.InstrumentID), creq.InstrumentID);
  ErlNifGetString(env, req, n++, sizeof(creq.OrderRef), creq.OrderRef);
  ErlNifGetString(env, req, n++, sizeof(creq.UserID), creq.UserID);
  ErlNifGetChar(env, req, n++, &creq.OrderPriceType);
  ErlNifGetChar(env, req, n++, &creq.Direction);
  ErlNifGetString(env, req, n++, sizeof(creq.CombOffsetFlag),
                  creq.CombOffsetFlag);
  ErlNifGetString(env, req, n++, sizeof(creq.CombHedgeFlag),
                  creq.CombHedgeFlag);
  ErlNifGetDouble(env, req, n++, &creq.LimitPrice);
  ErlNifGetInt(env, req, n++, &creq.VolumeTotalOriginal);
  ErlNifGetChar(env, req, n++, &creq.TimeCondition);
  ErlNifGetString(env, req, n++, sizeof(creq.GTDDate), creq.GTDDate);
  ErlNifGetChar(env, req, n++, &creq.VolumeCondition);
  ErlNifGetInt(env, req, n++, &creq.MinVolume);
  ErlNifGetChar(env, req, n++, &creq.ContingentCondition);
  ErlNifGetDouble(env, req, n++, &creq.StopPrice);
  ErlNifGetChar(env, req, n++, &creq.ForceCloseReason);
  ErlNifGetInt(env, req, n++, &creq.IsAutoSuspend);
  ErlNifGetString(env, req, n++, sizeof(creq.BusinessUnit), creq.BusinessUnit);
  ErlNifGetInt(env, req, n++, &creq.RequestID);
  ErlNifGetInt(env, req, n++, &creq.UserForceClose);
  ErlNifGetString(env, req, n++, sizeof(creq.ExchangeID), creq.ExchangeID);
  ErlNifGetString(env, req, n++, sizeof(creq.ParkedOrderID),
                  creq.ParkedOrderID);
  ErlNifGetChar(env, req, n++, &creq.UserType);
  ErlNifGetChar(env, req, n++, &creq.Status);
  ErlNifGetInt(env, req, n++, &creq.ErrorID);
  ErlNifGetString(env, req, n++, sizeof(creq.ErrorMsg), creq.ErrorMsg);
  ErlNifGetInt(env, req, n++, &creq.IsSwapOrder);
  ErlNifGetString(env, req, n++, sizeof(creq.AccountID), creq.AccountID);
  ErlNifGetString(env, req, n++, sizeof(creq.CurrencyID), creq.CurrencyID);
  ErlNifGetString(env, req, n++, sizeof(creq.ClientID), creq.ClientID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestUnitID), creq.InvestUnitID);
  ErlNifGetString(env, req, n++, sizeof(creq.IPAddress), creq.IPAddress);
  ErlNifGetString(env, req, n++, sizeof(creq.MacAddress), creq.MacAddress);

  return this->api_->ReqParkedOrderInsert(&creq, req_id);
}

int CtpTd::ReqParkedOrderAction(ErlNifEnv *env, NifRecord *req, int req_id) {
  int n = 1;
  CThostFtdcParkedOrderActionField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestorID), creq.InvestorID);
  ErlNifGetInt(env, req, n++, &creq.OrderActionRef);
  ErlNifGetString(env, req, n++, sizeof(creq.OrderRef), creq.OrderRef);
  ErlNifGetInt(env, req, n++, &creq.RequestID);
  ErlNifGetInt(env, req, n++, &creq.FrontID);
  ErlNifGetInt(env, req, n++, &creq.SessionID);
  ErlNifGetString(env, req, n++, sizeof(creq.ExchangeID), creq.ExchangeID);
  ErlNifGetString(env, req, n++, sizeof(creq.OrderSysID), creq.OrderSysID);
  ErlNifGetChar(env, req, n++, &creq.ActionFlag);
  ErlNifGetDouble(env, req, n++, &creq.LimitPrice);
  ErlNifGetInt(env, req, n++, &creq.VolumeChange);
  ErlNifGetString(env, req, n++, sizeof(creq.UserID), creq.UserID);
  ErlNifGetString(env, req, n++, sizeof(creq.InstrumentID), creq.InstrumentID);
  ErlNifGetString(env, req, n++, sizeof(creq.ParkedOrderActionID),
                  creq.ParkedOrderActionID);
  ErlNifGetChar(env, req, n++, &creq.UserType);
  ErlNifGetChar(env, req, n++, &creq.Status);
  ErlNifGetInt(env, req, n++, &creq.ErrorID);
  ErlNifGetString(env, req, n++, sizeof(creq.ErrorMsg), creq.ErrorMsg);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestUnitID), creq.InvestUnitID);
  ErlNifGetString(env, req, n++, sizeof(creq.IPAddress), creq.IPAddress);
  ErlNifGetString(env, req, n++, sizeof(creq.MacAddress), creq.MacAddress);

  return this->api_->ReqParkedOrderAction(&creq, req_id);
}

int CtpTd::ReqOrderAction(ErlNifEnv *env, NifRecord *req, int req_id) {
  int n = 1;
  CThostFtdcInputOrderActionField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestorID), creq.InvestorID);
  ErlNifGetInt(env, req, n++, &creq.OrderActionRef);
  ErlNifGetString(env, req, n++, sizeof(creq.OrderRef), creq.OrderRef);
  ErlNifGetInt(env, req, n++, &creq.RequestID);
  ErlNifGetInt(env, req, n++, &creq.FrontID);
  ErlNifGetInt(env, req, n++, &creq.SessionID);
  ErlNifGetString(env, req, n++, sizeof(creq.ExchangeID), creq.ExchangeID);
  ErlNifGetString(env, req, n++, sizeof(creq.OrderSysID), creq.OrderSysID);
  ErlNifGetChar(env, req, n++, &creq.ActionFlag);
  ErlNifGetDouble(env, req, n++, &creq.LimitPrice);
  ErlNifGetInt(env, req, n++, &creq.VolumeChange);
  ErlNifGetString(env, req, n++, sizeof(creq.UserID), creq.UserID);
  ErlNifGetString(env, req, n++, sizeof(creq.InstrumentID), creq.InstrumentID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestUnitID), creq.InvestUnitID);
  ErlNifGetString(env, req, n++, sizeof(creq.IPAddress), creq.IPAddress);
  ErlNifGetString(env, req, n++, sizeof(creq.MacAddress), creq.MacAddress);

  return this->api_->ReqOrderAction(&creq, req_id);
}

int CtpTd::ReqQueryMaxOrderVolume(ErlNifEnv *env, NifRecord *req, int req_id) {
  int n = 1;
  CThostFtdcQueryMaxOrderVolumeField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestorID), creq.InvestorID);
  ErlNifGetString(env, req, n++, sizeof(creq.InstrumentID), creq.InstrumentID);
  ErlNifGetChar(env, req, n++, &creq.Direction);
  ErlNifGetChar(env, req, n++, &creq.OffsetFlag);
  ErlNifGetChar(env, req, n++, &creq.HedgeFlag);
  ErlNifGetInt(env, req, n++, &creq.MaxVolume);
  ErlNifGetString(env, req, n++, sizeof(creq.ExchangeID), creq.ExchangeID);

  return this->api_->ReqQueryMaxOrderVolume(&creq, req_id);
}

int CtpTd::ReqSettlementInfoConfirm(ErlNifEnv *env, NifRecord *req,
                                    int req_id) {
  int n = 1;
  CThostFtdcSettlementInfoConfirmField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestorID), creq.InvestorID);
  ErlNifGetString(env, req, n++, sizeof(creq.ConfirmDate), creq.ConfirmDate);
  ErlNifGetString(env, req, n++, sizeof(creq.ConfirmTime), creq.ConfirmTime);

  return this->api_->ReqSettlementInfoConfirm(&creq, req_id);
}

int CtpTd::ReqRemoveParkedOrder(ErlNifEnv *env, NifRecord *req, int req_id) {
  int n = 1;
  CThostFtdcRemoveParkedOrderField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestorID), creq.InvestorID);
  ErlNifGetString(env, req, n++, sizeof(creq.ParkedOrderID),
                  creq.ParkedOrderID);

  return this->api_->ReqRemoveParkedOrder(&creq, req_id);
}

int CtpTd::ReqRemoveParkedOrderAction(ErlNifEnv *env, NifRecord *req,
                                      int req_id) {
  int n = 1;
  CThostFtdcRemoveParkedOrderActionField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestorID), creq.InvestorID);
  ErlNifGetString(env, req, n++, sizeof(creq.ParkedOrderActionID),
                  creq.ParkedOrderActionID);

  return this->api_->ReqRemoveParkedOrderAction(&creq, req_id);
}

int CtpTd::ReqExecOrderInsert(ErlNifEnv *env, NifRecord *req, int req_id) {
  int n = 1;
  CThostFtdcInputExecOrderField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestorID), creq.InvestorID);
  ErlNifGetString(env, req, n++, sizeof(creq.InstrumentID), creq.InstrumentID);
  ErlNifGetString(env, req, n++, sizeof(creq.ExecOrderRef), creq.ExecOrderRef);
  ErlNifGetString(env, req, n++, sizeof(creq.UserID), creq.UserID);
  ErlNifGetInt(env, req, n++, &creq.Volume);
  ErlNifGetInt(env, req, n++, &creq.RequestID);
  ErlNifGetString(env, req, n++, sizeof(creq.BusinessUnit), creq.BusinessUnit);
  ErlNifGetChar(env, req, n++, &creq.OffsetFlag);
  ErlNifGetChar(env, req, n++, &creq.HedgeFlag);
  ErlNifGetChar(env, req, n++, &creq.ActionType);
  ErlNifGetChar(env, req, n++, &creq.PosiDirection);
  ErlNifGetChar(env, req, n++, &creq.ReservePositionFlag);
  ErlNifGetChar(env, req, n++, &creq.CloseFlag);
  ErlNifGetString(env, req, n++, sizeof(creq.ExchangeID), creq.ExchangeID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestUnitID), creq.InvestUnitID);
  ErlNifGetString(env, req, n++, sizeof(creq.AccountID), creq.AccountID);
  ErlNifGetString(env, req, n++, sizeof(creq.CurrencyID), creq.CurrencyID);
  ErlNifGetString(env, req, n++, sizeof(creq.ClientID), creq.ClientID);
  ErlNifGetString(env, req, n++, sizeof(creq.IPAddress), creq.IPAddress);
  ErlNifGetString(env, req, n++, sizeof(creq.MacAddress), creq.MacAddress);

  return this->api_->ReqExecOrderInsert(&creq, req_id);
}

int CtpTd::ReqExecOrderAction(ErlNifEnv *env, NifRecord *req, int req_id) {
  int n = 1;
  CThostFtdcInputExecOrderActionField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestorID), creq.InvestorID);
  ErlNifGetInt(env, req, n++, &creq.ExecOrderActionRef);
  ErlNifGetString(env, req, n++, sizeof(creq.ExecOrderRef), creq.ExecOrderRef);
  ErlNifGetInt(env, req, n++, &creq.RequestID);
  ErlNifGetInt(env, req, n++, &creq.FrontID);
  ErlNifGetInt(env, req, n++, &creq.SessionID);
  ErlNifGetString(env, req, n++, sizeof(creq.ExchangeID), creq.ExchangeID);
  ErlNifGetString(env, req, n++, sizeof(creq.ExecOrderSysID),
                  creq.ExecOrderSysID);
  ErlNifGetChar(env, req, n++, &creq.ActionFlag);
  ErlNifGetString(env, req, n++, sizeof(creq.UserID), creq.UserID);
  ErlNifGetString(env, req, n++, sizeof(creq.InstrumentID), creq.InstrumentID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestUnitID), creq.InvestUnitID);
  ErlNifGetString(env, req, n++, sizeof(creq.IPAddress), creq.IPAddress);
  ErlNifGetString(env, req, n++, sizeof(creq.MacAddress), creq.MacAddress);

  return this->api_->ReqExecOrderAction(&creq, req_id);
}

int CtpTd::ReqForQuoteInsert(ErlNifEnv *env, NifRecord *req, int req_id) {
  int n = 1;
  CThostFtdcInputForQuoteField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestorID), creq.InvestorID);
  ErlNifGetString(env, req, n++, sizeof(creq.InstrumentID), creq.InstrumentID);
  ErlNifGetString(env, req, n++, sizeof(creq.ForQuoteRef), creq.ForQuoteRef);
  ErlNifGetString(env, req, n++, sizeof(creq.UserID), creq.UserID);
  ErlNifGetString(env, req, n++, sizeof(creq.ExchangeID), creq.ExchangeID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestUnitID), creq.InvestUnitID);
  ErlNifGetString(env, req, n++, sizeof(creq.IPAddress), creq.IPAddress);
  ErlNifGetString(env, req, n++, sizeof(creq.MacAddress), creq.MacAddress);

  return this->api_->ReqForQuoteInsert(&creq, req_id);
}

int CtpTd::ReqQuoteInsert(ErlNifEnv *env, NifRecord *req, int req_id) {
  int n = 1;
  CThostFtdcInputQuoteField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestorID), creq.InvestorID);
  ErlNifGetString(env, req, n++, sizeof(creq.InstrumentID), creq.InstrumentID);
  ErlNifGetString(env, req, n++, sizeof(creq.QuoteRef), creq.QuoteRef);
  ErlNifGetString(env, req, n++, sizeof(creq.UserID), creq.UserID);
  ErlNifGetDouble(env, req, n++, &creq.AskPrice);
  ErlNifGetDouble(env, req, n++, &creq.BidPrice);
  ErlNifGetInt(env, req, n++, &creq.AskVolume);
  ErlNifGetInt(env, req, n++, &creq.BidVolume);
  ErlNifGetInt(env, req, n++, &creq.RequestID);
  ErlNifGetString(env, req, n++, sizeof(creq.BusinessUnit), creq.BusinessUnit);
  ErlNifGetChar(env, req, n++, &creq.AskOffsetFlag);
  ErlNifGetChar(env, req, n++, &creq.BidOffsetFlag);
  ErlNifGetChar(env, req, n++, &creq.AskHedgeFlag);
  ErlNifGetChar(env, req, n++, &creq.BidHedgeFlag);
  ErlNifGetString(env, req, n++, sizeof(creq.AskOrderRef), creq.AskOrderRef);
  ErlNifGetString(env, req, n++, sizeof(creq.BidOrderRef), creq.BidOrderRef);
  ErlNifGetString(env, req, n++, sizeof(creq.ForQuoteSysID),
                  creq.ForQuoteSysID);
  ErlNifGetString(env, req, n++, sizeof(creq.ExchangeID), creq.ExchangeID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestUnitID), creq.InvestUnitID);
  ErlNifGetString(env, req, n++, sizeof(creq.ClientID), creq.ClientID);
  ErlNifGetString(env, req, n++, sizeof(creq.IPAddress), creq.IPAddress);
  ErlNifGetString(env, req, n++, sizeof(creq.MacAddress), creq.MacAddress);

  return this->api_->ReqQuoteInsert(&creq, req_id);
}

int CtpTd::ReqQuoteAction(ErlNifEnv *env, NifRecord *req, int req_id) {
  int n = 1;
  CThostFtdcInputQuoteActionField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestorID), creq.InvestorID);
  ErlNifGetInt(env, req, n++, &creq.QuoteActionRef);
  ErlNifGetString(env, req, n++, sizeof(creq.QuoteRef), creq.QuoteRef);
  ErlNifGetInt(env, req, n++, &creq.RequestID);
  ErlNifGetInt(env, req, n++, &creq.FrontID);
  ErlNifGetInt(env, req, n++, &creq.SessionID);
  ErlNifGetString(env, req, n++, sizeof(creq.ExchangeID), creq.ExchangeID);
  ErlNifGetString(env, req, n++, sizeof(creq.QuoteSysID), creq.QuoteSysID);
  ErlNifGetChar(env, req, n++, &creq.ActionFlag);
  ErlNifGetString(env, req, n++, sizeof(creq.UserID), creq.UserID);
  ErlNifGetString(env, req, n++, sizeof(creq.InstrumentID), creq.InstrumentID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestUnitID), creq.InvestUnitID);
  ErlNifGetString(env, req, n++, sizeof(creq.ClientID), creq.ClientID);
  ErlNifGetString(env, req, n++, sizeof(creq.IPAddress), creq.IPAddress);
  ErlNifGetString(env, req, n++, sizeof(creq.MacAddress), creq.MacAddress);

  return this->api_->ReqQuoteAction(&creq, req_id);
}

int CtpTd::ReqLockInsert(ErlNifEnv *env, NifRecord *req, int req_id) {
  int n = 1;
  CThostFtdcInputLockField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestorID), creq.InvestorID);
  ErlNifGetString(env, req, n++, sizeof(creq.InstrumentID), creq.InstrumentID);
  ErlNifGetString(env, req, n++, sizeof(creq.LockRef), creq.LockRef);
  ErlNifGetString(env, req, n++, sizeof(creq.UserID), creq.UserID);
  ErlNifGetInt(env, req, n++, &creq.Volume);
  ErlNifGetInt(env, req, n++, &creq.RequestID);
  ErlNifGetString(env, req, n++, sizeof(creq.BusinessUnit), creq.BusinessUnit);
  ErlNifGetChar(env, req, n++, &creq.LockType);
  ErlNifGetString(env, req, n++, sizeof(creq.ExchangeID), creq.ExchangeID);
  ErlNifGetString(env, req, n++, sizeof(creq.IPAddress), creq.IPAddress);
  ErlNifGetString(env, req, n++, sizeof(creq.MacAddress), creq.MacAddress);

  return this->api_->ReqLockInsert(&creq, req_id);
}

int CtpTd::ReqBatchOrderAction(ErlNifEnv *env, NifRecord *req, int req_id) {
  int n = 1;
  CThostFtdcInputBatchOrderActionField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestorID), creq.InvestorID);
  ErlNifGetInt(env, req, n++, &creq.OrderActionRef);
  ErlNifGetInt(env, req, n++, &creq.RequestID);
  ErlNifGetInt(env, req, n++, &creq.FrontID);
  ErlNifGetInt(env, req, n++, &creq.SessionID);
  ErlNifGetString(env, req, n++, sizeof(creq.ExchangeID), creq.ExchangeID);
  ErlNifGetString(env, req, n++, sizeof(creq.UserID), creq.UserID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestUnitID), creq.InvestUnitID);
  ErlNifGetString(env, req, n++, sizeof(creq.IPAddress), creq.IPAddress);
  ErlNifGetString(env, req, n++, sizeof(creq.MacAddress), creq.MacAddress);

  return this->api_->ReqBatchOrderAction(&creq, req_id);
}

int CtpTd::ReqCombActionInsert(ErlNifEnv *env, NifRecord *req, int req_id) {
  int n = 1;
  CThostFtdcInputCombActionField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestorID), creq.InvestorID);
  ErlNifGetString(env, req, n++, sizeof(creq.InstrumentID), creq.InstrumentID);
  ErlNifGetString(env, req, n++, sizeof(creq.CombActionRef),
                  creq.CombActionRef);
  ErlNifGetString(env, req, n++, sizeof(creq.UserID), creq.UserID);
  ErlNifGetChar(env, req, n++, &creq.Direction);
  ErlNifGetInt(env, req, n++, &creq.Volume);
  ErlNifGetChar(env, req, n++, &creq.CombDirection);
  ErlNifGetChar(env, req, n++, &creq.HedgeFlag);
  ErlNifGetString(env, req, n++, sizeof(creq.ExchangeID), creq.ExchangeID);
  ErlNifGetString(env, req, n++, sizeof(creq.IPAddress), creq.IPAddress);
  ErlNifGetString(env, req, n++, sizeof(creq.MacAddress), creq.MacAddress);

  return this->api_->ReqCombActionInsert(&creq, req_id);
}

int CtpTd::ReqQryOrder(ErlNifEnv *env, NifRecord *req, int req_id) {
  int n = 1;
  CThostFtdcQryOrderField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestorID), creq.InvestorID);
  ErlNifGetString(env, req, n++, sizeof(creq.InstrumentID), creq.InstrumentID);
  ErlNifGetString(env, req, n++, sizeof(creq.ExchangeID), creq.ExchangeID);
  ErlNifGetString(env, req, n++, sizeof(creq.OrderSysID), creq.OrderSysID);
  ErlNifGetString(env, req, n++, sizeof(creq.InsertTimeStart),
                  creq.InsertTimeStart);
  ErlNifGetString(env, req, n++, sizeof(creq.InsertTimeEnd),
                  creq.InsertTimeEnd);

  return this->api_->ReqQryOrder(&creq, req_id);
}

int CtpTd::ReqQryTrade(ErlNifEnv *env, NifRecord *req, int req_id) {
  int n = 1;
  CThostFtdcQryTradeField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestorID), creq.InvestorID);
  ErlNifGetString(env, req, n++, sizeof(creq.InstrumentID), creq.InstrumentID);
  ErlNifGetString(env, req, n++, sizeof(creq.ExchangeID), creq.ExchangeID);
  ErlNifGetString(env, req, n++, sizeof(creq.TradeID), creq.TradeID);
  ErlNifGetString(env, req, n++, sizeof(creq.TradeTimeStart),
                  creq.TradeTimeStart);
  ErlNifGetString(env, req, n++, sizeof(creq.TradeTimeEnd), creq.TradeTimeEnd);

  return this->api_->ReqQryTrade(&creq, req_id);
}

int CtpTd::ReqQryInvestorPosition(ErlNifEnv *env, NifRecord *req, int req_id) {
  int n = 1;
  CThostFtdcQryInvestorPositionField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestorID), creq.InvestorID);
  ErlNifGetString(env, req, n++, sizeof(creq.InstrumentID), creq.InstrumentID);
  ErlNifGetString(env, req, n++, sizeof(creq.ExchangeID), creq.ExchangeID);

  return this->api_->ReqQryInvestorPosition(&creq, req_id);
}

int CtpTd::ReqQryTradingAccount(ErlNifEnv *env, NifRecord *req, int req_id) {
  int n = 1;
  CThostFtdcQryTradingAccountField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestorID), creq.InvestorID);
  ErlNifGetString(env, req, n++, sizeof(creq.CurrencyID), creq.CurrencyID);
  ErlNifGetChar(env, req, n++, &creq.BizType);

  return this->api_->ReqQryTradingAccount(&creq, req_id);
}

int CtpTd::ReqQryInvestor(ErlNifEnv *env, NifRecord *req, int req_id) {
  int n = 1;
  CThostFtdcQryInvestorField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestorID), creq.InvestorID);

  return this->api_->ReqQryInvestor(&creq, req_id);
}

int CtpTd::ReqQryTradingCode(ErlNifEnv *env, NifRecord *req, int req_id) {
  int n = 1;
  CThostFtdcQryTradingCodeField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestorID), creq.InvestorID);
  ErlNifGetString(env, req, n++, sizeof(creq.ExchangeID), creq.ExchangeID);
  ErlNifGetString(env, req, n++, sizeof(creq.ClientID), creq.ClientID);
  ErlNifGetChar(env, req, n++, &creq.ClientIDType);

  return this->api_->ReqQryTradingCode(&creq, req_id);
}

int CtpTd::ReqQryInstrumentMarginRate(ErlNifEnv *env, NifRecord *req,
                                      int req_id) {
  int n = 1;
  CThostFtdcQryInstrumentMarginRateField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestorID), creq.InvestorID);
  ErlNifGetString(env, req, n++, sizeof(creq.InstrumentID), creq.InstrumentID);
  ErlNifGetChar(env, req, n++, &creq.HedgeFlag);

  return this->api_->ReqQryInstrumentMarginRate(&creq, req_id);
}

int CtpTd::ReqQryInstrumentCommissionRate(ErlNifEnv *env, NifRecord *req,
                                          int req_id) {
  int n = 1;
  CThostFtdcQryInstrumentCommissionRateField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestorID), creq.InvestorID);
  ErlNifGetString(env, req, n++, sizeof(creq.InstrumentID), creq.InstrumentID);
  ErlNifGetString(env, req, n++, sizeof(creq.ExchangeID), creq.ExchangeID);

  return this->api_->ReqQryInstrumentCommissionRate(&creq, req_id);
}

int CtpTd::ReqQryExchange(ErlNifEnv *env, NifRecord *req, int req_id) {
  int n = 1;
  CThostFtdcQryExchangeField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.ExchangeID), creq.ExchangeID);

  return this->api_->ReqQryExchange(&creq, req_id);
}

int CtpTd::ReqQryProduct(ErlNifEnv *env, NifRecord *req, int req_id) {
  int n = 1;
  CThostFtdcQryProductField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.ProductID), creq.ProductID);
  ErlNifGetChar(env, req, n++, &creq.ProductClass);
  ErlNifGetString(env, req, n++, sizeof(creq.ExchangeID), creq.ExchangeID);

  return this->api_->ReqQryProduct(&creq, req_id);
}

int CtpTd::ReqQryInstrument(ErlNifEnv *env, NifRecord *req, int req_id) {
  int n = 1;
  CThostFtdcQryInstrumentField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.InstrumentID), creq.InstrumentID);
  ErlNifGetString(env, req, n++, sizeof(creq.ExchangeID), creq.ExchangeID);
  ErlNifGetString(env, req, n++, sizeof(creq.ExchangeInstID),
                  creq.ExchangeInstID);
  ErlNifGetString(env, req, n++, sizeof(creq.ProductID), creq.ProductID);

  return this->api_->ReqQryInstrument(&creq, req_id);
}

int CtpTd::ReqQryDepthMarketData(ErlNifEnv *env, NifRecord *req, int req_id) {
  int n = 1;
  CThostFtdcQryDepthMarketDataField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.InstrumentID), creq.InstrumentID);
  ErlNifGetString(env, req, n++, sizeof(creq.ExchangeID), creq.ExchangeID);

  return this->api_->ReqQryDepthMarketData(&creq, req_id);
}

int CtpTd::ReqQrySettlementInfo(ErlNifEnv *env, NifRecord *req, int req_id) {
  int n = 1;
  CThostFtdcQrySettlementInfoField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestorID), creq.InvestorID);
  ErlNifGetString(env, req, n++, sizeof(creq.TradingDay), creq.TradingDay);

  return this->api_->ReqQrySettlementInfo(&creq, req_id);
}

int CtpTd::ReqQryTransferBank(ErlNifEnv *env, NifRecord *req, int req_id) {
  int n = 1;
  CThostFtdcQryTransferBankField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BankID), creq.BankID);
  ErlNifGetString(env, req, n++, sizeof(creq.BankBrchID), creq.BankBrchID);

  return this->api_->ReqQryTransferBank(&creq, req_id);
}

int CtpTd::ReqQryInvestorPositionDetail(ErlNifEnv *env, NifRecord *req,
                                        int req_id) {
  int n = 1;
  CThostFtdcQryInvestorPositionDetailField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestorID), creq.InvestorID);
  ErlNifGetString(env, req, n++, sizeof(creq.InstrumentID), creq.InstrumentID);
  ErlNifGetString(env, req, n++, sizeof(creq.ExchangeID), creq.ExchangeID);

  return this->api_->ReqQryInvestorPositionDetail(&creq, req_id);
}

int CtpTd::ReqQryNotice(ErlNifEnv *env, NifRecord *req, int req_id) {
  int n = 1;
  CThostFtdcQryNoticeField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);

  return this->api_->ReqQryNotice(&creq, req_id);
}

int CtpTd::ReqQrySettlementInfoConfirm(ErlNifEnv *env, NifRecord *req,
                                       int req_id) {
  int n = 1;
  CThostFtdcQrySettlementInfoConfirmField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestorID), creq.InvestorID);

  return this->api_->ReqQrySettlementInfoConfirm(&creq, req_id);
}

int CtpTd::ReqQryInvestorPositionCombineDetail(ErlNifEnv *env, NifRecord *req,
                                               int req_id) {
  int n = 1;
  CThostFtdcQryInvestorPositionCombineDetailField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestorID), creq.InvestorID);
  ErlNifGetString(env, req, n++, sizeof(creq.CombInstrumentID),
                  creq.CombInstrumentID);

  return this->api_->ReqQryInvestorPositionCombineDetail(&creq, req_id);
}

int CtpTd::ReqQryCFMMCTradingAccountKey(ErlNifEnv *env, NifRecord *req,
                                        int req_id) {
  int n = 1;
  CThostFtdcQryCFMMCTradingAccountKeyField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestorID), creq.InvestorID);

  return this->api_->ReqQryCFMMCTradingAccountKey(&creq, req_id);
}

int CtpTd::ReqQryEWarrantOffset(ErlNifEnv *env, NifRecord *req, int req_id) {
  int n = 1;
  CThostFtdcQryEWarrantOffsetField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestorID), creq.InvestorID);
  ErlNifGetString(env, req, n++, sizeof(creq.ExchangeID), creq.ExchangeID);
  ErlNifGetString(env, req, n++, sizeof(creq.InstrumentID), creq.InstrumentID);

  return this->api_->ReqQryEWarrantOffset(&creq, req_id);
}

int CtpTd::ReqQryInvestorProductGroupMargin(ErlNifEnv *env, NifRecord *req,
                                            int req_id) {
  int n = 1;
  CThostFtdcQryInvestorProductGroupMarginField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestorID), creq.InvestorID);
  ErlNifGetString(env, req, n++, sizeof(creq.ProductGroupID),
                  creq.ProductGroupID);
  ErlNifGetChar(env, req, n++, &creq.HedgeFlag);

  return this->api_->ReqQryInvestorProductGroupMargin(&creq, req_id);
}

int CtpTd::ReqQryExchangeMarginRate(ErlNifEnv *env, NifRecord *req,
                                    int req_id) {
  int n = 1;
  CThostFtdcQryExchangeMarginRateField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InstrumentID), creq.InstrumentID);
  ErlNifGetChar(env, req, n++, &creq.HedgeFlag);

  return this->api_->ReqQryExchangeMarginRate(&creq, req_id);
}

int CtpTd::ReqQryExchangeMarginRateAdjust(ErlNifEnv *env, NifRecord *req,
                                          int req_id) {
  int n = 1;
  CThostFtdcQryExchangeMarginRateAdjustField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InstrumentID), creq.InstrumentID);
  ErlNifGetChar(env, req, n++, &creq.HedgeFlag);

  return this->api_->ReqQryExchangeMarginRateAdjust(&creq, req_id);
}

int CtpTd::ReqQryExchangeRate(ErlNifEnv *env, NifRecord *req, int req_id) {
  int n = 1;
  CThostFtdcQryExchangeRateField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.FromCurrencyID),
                  creq.FromCurrencyID);
  ErlNifGetString(env, req, n++, sizeof(creq.ToCurrencyID), creq.ToCurrencyID);

  return this->api_->ReqQryExchangeRate(&creq, req_id);
}

int CtpTd::ReqQrySecAgentACIDMap(ErlNifEnv *env, NifRecord *req, int req_id) {
  int n = 1;
  CThostFtdcQrySecAgentACIDMapField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.UserID), creq.UserID);
  ErlNifGetString(env, req, n++, sizeof(creq.AccountID), creq.AccountID);
  ErlNifGetString(env, req, n++, sizeof(creq.CurrencyID), creq.CurrencyID);

  return this->api_->ReqQrySecAgentACIDMap(&creq, req_id);
}

int CtpTd::ReqQryProductExchRate(ErlNifEnv *env, NifRecord *req, int req_id) {
  int n = 1;
  CThostFtdcQryProductExchRateField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.ProductID), creq.ProductID);

  return this->api_->ReqQryProductExchRate(&creq, req_id);
}

int CtpTd::ReqQryProductGroup(ErlNifEnv *env, NifRecord *req, int req_id) {
  int n = 1;
  CThostFtdcQryProductGroupField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.ProductID), creq.ProductID);
  ErlNifGetString(env, req, n++, sizeof(creq.ExchangeID), creq.ExchangeID);

  return this->api_->ReqQryProductGroup(&creq, req_id);
}

int CtpTd::ReqQryMMInstrumentCommissionRate(ErlNifEnv *env, NifRecord *req,
                                            int req_id) {
  int n = 1;
  CThostFtdcQryMMInstrumentCommissionRateField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestorID), creq.InvestorID);
  ErlNifGetString(env, req, n++, sizeof(creq.InstrumentID), creq.InstrumentID);
  ErlNifGetString(env, req, n++, sizeof(creq.ExchangeID), creq.ExchangeID);

  return this->api_->ReqQryMMInstrumentCommissionRate(&creq, req_id);
}

int CtpTd::ReqQryMMOptionInstrCommRate(ErlNifEnv *env, NifRecord *req,
                                       int req_id) {
  int n = 1;
  CThostFtdcQryMMOptionInstrCommRateField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestorID), creq.InvestorID);
  ErlNifGetString(env, req, n++, sizeof(creq.InstrumentID), creq.InstrumentID);
  ErlNifGetString(env, req, n++, sizeof(creq.ExchangeID), creq.ExchangeID);

  return this->api_->ReqQryMMOptionInstrCommRate(&creq, req_id);
}

int CtpTd::ReqQryInstrumentOrderCommRate(ErlNifEnv *env, NifRecord *req,
                                         int req_id) {
  int n = 1;
  CThostFtdcQryInstrumentOrderCommRateField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestorID), creq.InvestorID);
  ErlNifGetString(env, req, n++, sizeof(creq.InstrumentID), creq.InstrumentID);
  ErlNifGetString(env, req, n++, sizeof(creq.ExchangeID), creq.ExchangeID);

  return this->api_->ReqQryInstrumentOrderCommRate(&creq, req_id);
}

int CtpTd::ReqQryOptionInstrTradeCost(ErlNifEnv *env, NifRecord *req,
                                      int req_id) {
  int n = 1;
  CThostFtdcQryOptionInstrTradeCostField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestorID), creq.InvestorID);
  ErlNifGetString(env, req, n++, sizeof(creq.InstrumentID), creq.InstrumentID);
  ErlNifGetChar(env, req, n++, &creq.HedgeFlag);
  ErlNifGetDouble(env, req, n++, &creq.InputPrice);
  ErlNifGetDouble(env, req, n++, &creq.UnderlyingPrice);
  ErlNifGetString(env, req, n++, sizeof(creq.ExchangeID), creq.ExchangeID);

  return this->api_->ReqQryOptionInstrTradeCost(&creq, req_id);
}

int CtpTd::ReqQryOptionInstrCommRate(ErlNifEnv *env, NifRecord *req,
                                     int req_id) {
  int n = 1;
  CThostFtdcQryOptionInstrCommRateField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestorID), creq.InvestorID);
  ErlNifGetString(env, req, n++, sizeof(creq.InstrumentID), creq.InstrumentID);
  ErlNifGetString(env, req, n++, sizeof(creq.ExchangeID), creq.ExchangeID);

  return this->api_->ReqQryOptionInstrCommRate(&creq, req_id);
}

int CtpTd::ReqQryExecOrder(ErlNifEnv *env, NifRecord *req, int req_id) {
  int n = 1;
  CThostFtdcQryExecOrderField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestorID), creq.InvestorID);
  ErlNifGetString(env, req, n++, sizeof(creq.InstrumentID), creq.InstrumentID);
  ErlNifGetString(env, req, n++, sizeof(creq.ExchangeID), creq.ExchangeID);
  ErlNifGetString(env, req, n++, sizeof(creq.ExecOrderSysID),
                  creq.ExecOrderSysID);
  ErlNifGetString(env, req, n++, sizeof(creq.InsertTimeStart),
                  creq.InsertTimeStart);
  ErlNifGetString(env, req, n++, sizeof(creq.InsertTimeEnd),
                  creq.InsertTimeEnd);

  return this->api_->ReqQryExecOrder(&creq, req_id);
}

int CtpTd::ReqQryForQuote(ErlNifEnv *env, NifRecord *req, int req_id) {
  int n = 1;
  CThostFtdcQryForQuoteField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestorID), creq.InvestorID);
  ErlNifGetString(env, req, n++, sizeof(creq.InstrumentID), creq.InstrumentID);
  ErlNifGetString(env, req, n++, sizeof(creq.ExchangeID), creq.ExchangeID);
  ErlNifGetString(env, req, n++, sizeof(creq.InsertTimeStart),
                  creq.InsertTimeStart);
  ErlNifGetString(env, req, n++, sizeof(creq.InsertTimeEnd),
                  creq.InsertTimeEnd);

  return this->api_->ReqQryForQuote(&creq, req_id);
}

int CtpTd::ReqQryQuote(ErlNifEnv *env, NifRecord *req, int req_id) {
  int n = 1;
  CThostFtdcQryQuoteField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestorID), creq.InvestorID);
  ErlNifGetString(env, req, n++, sizeof(creq.InstrumentID), creq.InstrumentID);
  ErlNifGetString(env, req, n++, sizeof(creq.ExchangeID), creq.ExchangeID);
  ErlNifGetString(env, req, n++, sizeof(creq.QuoteSysID), creq.QuoteSysID);
  ErlNifGetString(env, req, n++, sizeof(creq.InsertTimeStart),
                  creq.InsertTimeStart);
  ErlNifGetString(env, req, n++, sizeof(creq.InsertTimeEnd),
                  creq.InsertTimeEnd);

  return this->api_->ReqQryQuote(&creq, req_id);
}

int CtpTd::ReqQryLock(ErlNifEnv *env, NifRecord *req, int req_id) {
  int n = 1;
  CThostFtdcQryLockField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestorID), creq.InvestorID);
  ErlNifGetString(env, req, n++, sizeof(creq.InstrumentID), creq.InstrumentID);
  ErlNifGetString(env, req, n++, sizeof(creq.ExchangeID), creq.ExchangeID);
  ErlNifGetString(env, req, n++, sizeof(creq.LockSysID), creq.LockSysID);
  ErlNifGetString(env, req, n++, sizeof(creq.InsertTimeStart),
                  creq.InsertTimeStart);
  ErlNifGetString(env, req, n++, sizeof(creq.InsertTimeEnd),
                  creq.InsertTimeEnd);

  return this->api_->ReqQryLock(&creq, req_id);
}

int CtpTd::ReqQryLockPosition(ErlNifEnv *env, NifRecord *req, int req_id) {
  int n = 1;
  CThostFtdcQryLockPositionField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestorID), creq.InvestorID);
  ErlNifGetString(env, req, n++, sizeof(creq.InstrumentID), creq.InstrumentID);
  ErlNifGetString(env, req, n++, sizeof(creq.ExchangeID), creq.ExchangeID);

  return this->api_->ReqQryLockPosition(&creq, req_id);
}

int CtpTd::ReqQryETFOptionInstrCommRate(ErlNifEnv *env, NifRecord *req,
                                        int req_id) {
  int n = 1;
  CThostFtdcQryETFOptionInstrCommRateField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestorID), creq.InvestorID);
  ErlNifGetString(env, req, n++, sizeof(creq.InstrumentID), creq.InstrumentID);
  ErlNifGetString(env, req, n++, sizeof(creq.ExchangeID), creq.ExchangeID);

  return this->api_->ReqQryETFOptionInstrCommRate(&creq, req_id);
}

int CtpTd::ReqQryInvestorLevel(ErlNifEnv *env, NifRecord *req, int req_id) {
  int n = 1;
  CThostFtdcQryInvestorLevelField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestorID), creq.InvestorID);
  ErlNifGetString(env, req, n++, sizeof(creq.ExchangeID), creq.ExchangeID);

  return this->api_->ReqQryInvestorLevel(&creq, req_id);
}

int CtpTd::ReqQryExecFreeze(ErlNifEnv *env, NifRecord *req, int req_id) {
  int n = 1;
  CThostFtdcQryExecFreezeField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestorID), creq.InvestorID);
  ErlNifGetString(env, req, n++, sizeof(creq.InstrumentID), creq.InstrumentID);
  ErlNifGetString(env, req, n++, sizeof(creq.ExchangeID), creq.ExchangeID);

  return this->api_->ReqQryExecFreeze(&creq, req_id);
}

int CtpTd::ReqQryCombInstrumentGuard(ErlNifEnv *env, NifRecord *req,
                                     int req_id) {
  int n = 1;
  CThostFtdcQryCombInstrumentGuardField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InstrumentID), creq.InstrumentID);

  return this->api_->ReqQryCombInstrumentGuard(&creq, req_id);
}

int CtpTd::ReqQryCombAction(ErlNifEnv *env, NifRecord *req, int req_id) {
  int n = 1;
  CThostFtdcQryCombActionField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestorID), creq.InvestorID);
  ErlNifGetString(env, req, n++, sizeof(creq.InstrumentID), creq.InstrumentID);
  ErlNifGetString(env, req, n++, sizeof(creq.ExchangeID), creq.ExchangeID);

  return this->api_->ReqQryCombAction(&creq, req_id);
}

int CtpTd::ReqQryTransferSerial(ErlNifEnv *env, NifRecord *req, int req_id) {
  int n = 1;
  CThostFtdcQryTransferSerialField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.AccountID), creq.AccountID);
  ErlNifGetString(env, req, n++, sizeof(creq.BankID), creq.BankID);
  ErlNifGetString(env, req, n++, sizeof(creq.CurrencyID), creq.CurrencyID);

  return this->api_->ReqQryTransferSerial(&creq, req_id);
}

int CtpTd::ReqQryAccountregister(ErlNifEnv *env, NifRecord *req, int req_id) {
  int n = 1;
  CThostFtdcQryAccountregisterField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.AccountID), creq.AccountID);
  ErlNifGetString(env, req, n++, sizeof(creq.BankID), creq.BankID);
  ErlNifGetString(env, req, n++, sizeof(creq.BankBranchID), creq.BankBranchID);
  ErlNifGetString(env, req, n++, sizeof(creq.CurrencyID), creq.CurrencyID);

  return this->api_->ReqQryAccountregister(&creq, req_id);
}

int CtpTd::ReqQryContractBank(ErlNifEnv *env, NifRecord *req, int req_id) {
  int n = 1;
  CThostFtdcQryContractBankField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.BankID), creq.BankID);
  ErlNifGetString(env, req, n++, sizeof(creq.BankBrchID), creq.BankBrchID);

  return this->api_->ReqQryContractBank(&creq, req_id);
}

int CtpTd::ReqQryParkedOrder(ErlNifEnv *env, NifRecord *req, int req_id) {
  int n = 1;
  CThostFtdcQryParkedOrderField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestorID), creq.InvestorID);
  ErlNifGetString(env, req, n++, sizeof(creq.InstrumentID), creq.InstrumentID);
  ErlNifGetString(env, req, n++, sizeof(creq.ExchangeID), creq.ExchangeID);

  return this->api_->ReqQryParkedOrder(&creq, req_id);
}

int CtpTd::ReqQryParkedOrderAction(ErlNifEnv *env, NifRecord *req, int req_id) {
  int n = 1;
  CThostFtdcQryParkedOrderActionField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestorID), creq.InvestorID);
  ErlNifGetString(env, req, n++, sizeof(creq.InstrumentID), creq.InstrumentID);
  ErlNifGetString(env, req, n++, sizeof(creq.ExchangeID), creq.ExchangeID);

  return this->api_->ReqQryParkedOrderAction(&creq, req_id);
}

int CtpTd::ReqQryTradingNotice(ErlNifEnv *env, NifRecord *req, int req_id) {
  int n = 1;
  CThostFtdcQryTradingNoticeField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestorID), creq.InvestorID);

  return this->api_->ReqQryTradingNotice(&creq, req_id);
}

int CtpTd::ReqQryBrokerTradingParams(ErlNifEnv *env, NifRecord *req,
                                     int req_id) {
  int n = 1;
  CThostFtdcQryBrokerTradingParamsField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestorID), creq.InvestorID);
  ErlNifGetString(env, req, n++, sizeof(creq.CurrencyID), creq.CurrencyID);

  return this->api_->ReqQryBrokerTradingParams(&creq, req_id);
}

int CtpTd::ReqQryBrokerTradingAlgos(ErlNifEnv *env, NifRecord *req,
                                    int req_id) {
  int n = 1;
  CThostFtdcQryBrokerTradingAlgosField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.ExchangeID), creq.ExchangeID);
  ErlNifGetString(env, req, n++, sizeof(creq.InstrumentID), creq.InstrumentID);

  return this->api_->ReqQryBrokerTradingAlgos(&creq, req_id);
}

int CtpTd::ReqQueryCFMMCTradingAccountToken(ErlNifEnv *env, NifRecord *req,
                                            int req_id) {
  int n = 1;
  CThostFtdcQueryCFMMCTradingAccountTokenField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.InvestorID), creq.InvestorID);

  return this->api_->ReqQueryCFMMCTradingAccountToken(&creq, req_id);
}

int CtpTd::ReqFromBankToFutureByFuture(ErlNifEnv *env, NifRecord *req,
                                       int req_id) {
  int n = 1;
  CThostFtdcReqTransferField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.TradeCode), creq.TradeCode);
  ErlNifGetString(env, req, n++, sizeof(creq.BankID), creq.BankID);
  ErlNifGetString(env, req, n++, sizeof(creq.BankBranchID), creq.BankBranchID);
  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.BrokerBranchID),
                  creq.BrokerBranchID);
  ErlNifGetString(env, req, n++, sizeof(creq.TradeDate), creq.TradeDate);
  ErlNifGetString(env, req, n++, sizeof(creq.TradeTime), creq.TradeTime);
  ErlNifGetString(env, req, n++, sizeof(creq.BankSerial), creq.BankSerial);
  ErlNifGetString(env, req, n++, sizeof(creq.TradingDay), creq.TradingDay);
  ErlNifGetInt(env, req, n++, &creq.PlateSerial);
  ErlNifGetChar(env, req, n++, &creq.LastFragment);
  ErlNifGetInt(env, req, n++, &creq.SessionID);
  ErlNifGetString(env, req, n++, sizeof(creq.CustomerName), creq.CustomerName);
  ErlNifGetChar(env, req, n++, &creq.IdCardType);
  ErlNifGetString(env, req, n++, sizeof(creq.IdentifiedCardNo),
                  creq.IdentifiedCardNo);
  ErlNifGetChar(env, req, n++, &creq.CustType);
  ErlNifGetString(env, req, n++, sizeof(creq.BankAccount), creq.BankAccount);
  ErlNifGetString(env, req, n++, sizeof(creq.BankPassWord), creq.BankPassWord);
  ErlNifGetString(env, req, n++, sizeof(creq.AccountID), creq.AccountID);
  ErlNifGetString(env, req, n++, sizeof(creq.Password), creq.Password);
  ErlNifGetInt(env, req, n++, &creq.InstallID);
  ErlNifGetInt(env, req, n++, &creq.FutureSerial);
  ErlNifGetString(env, req, n++, sizeof(creq.UserID), creq.UserID);
  ErlNifGetChar(env, req, n++, &creq.VerifyCertNoFlag);
  ErlNifGetString(env, req, n++, sizeof(creq.CurrencyID), creq.CurrencyID);
  ErlNifGetDouble(env, req, n++, &creq.TradeAmount);
  ErlNifGetDouble(env, req, n++, &creq.FutureFetchAmount);
  ErlNifGetChar(env, req, n++, &creq.FeePayFlag);
  ErlNifGetDouble(env, req, n++, &creq.CustFee);
  ErlNifGetDouble(env, req, n++, &creq.BrokerFee);
  ErlNifGetString(env, req, n++, sizeof(creq.Message), creq.Message);
  ErlNifGetString(env, req, n++, sizeof(creq.Digest), creq.Digest);
  ErlNifGetChar(env, req, n++, &creq.BankAccType);
  ErlNifGetString(env, req, n++, sizeof(creq.DeviceID), creq.DeviceID);
  ErlNifGetChar(env, req, n++, &creq.BankSecuAccType);
  ErlNifGetString(env, req, n++, sizeof(creq.BrokerIDByBank),
                  creq.BrokerIDByBank);
  ErlNifGetString(env, req, n++, sizeof(creq.BankSecuAcc), creq.BankSecuAcc);
  ErlNifGetChar(env, req, n++, &creq.BankPwdFlag);
  ErlNifGetChar(env, req, n++, &creq.SecuPwdFlag);
  ErlNifGetString(env, req, n++, sizeof(creq.OperNo), creq.OperNo);
  ErlNifGetInt(env, req, n++, &creq.RequestID);
  ErlNifGetInt(env, req, n++, &creq.TID);
  ErlNifGetChar(env, req, n++, &creq.TransferStatus);

  return this->api_->ReqFromBankToFutureByFuture(&creq, req_id);
}

int CtpTd::ReqFromFutureToBankByFuture(ErlNifEnv *env, NifRecord *req,
                                       int req_id) {
  int n = 1;
  CThostFtdcReqTransferField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.TradeCode), creq.TradeCode);
  ErlNifGetString(env, req, n++, sizeof(creq.BankID), creq.BankID);
  ErlNifGetString(env, req, n++, sizeof(creq.BankBranchID), creq.BankBranchID);
  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.BrokerBranchID),
                  creq.BrokerBranchID);
  ErlNifGetString(env, req, n++, sizeof(creq.TradeDate), creq.TradeDate);
  ErlNifGetString(env, req, n++, sizeof(creq.TradeTime), creq.TradeTime);
  ErlNifGetString(env, req, n++, sizeof(creq.BankSerial), creq.BankSerial);
  ErlNifGetString(env, req, n++, sizeof(creq.TradingDay), creq.TradingDay);
  ErlNifGetInt(env, req, n++, &creq.PlateSerial);
  ErlNifGetChar(env, req, n++, &creq.LastFragment);
  ErlNifGetInt(env, req, n++, &creq.SessionID);
  ErlNifGetString(env, req, n++, sizeof(creq.CustomerName), creq.CustomerName);
  ErlNifGetChar(env, req, n++, &creq.IdCardType);
  ErlNifGetString(env, req, n++, sizeof(creq.IdentifiedCardNo),
                  creq.IdentifiedCardNo);
  ErlNifGetChar(env, req, n++, &creq.CustType);
  ErlNifGetString(env, req, n++, sizeof(creq.BankAccount), creq.BankAccount);
  ErlNifGetString(env, req, n++, sizeof(creq.BankPassWord), creq.BankPassWord);
  ErlNifGetString(env, req, n++, sizeof(creq.AccountID), creq.AccountID);
  ErlNifGetString(env, req, n++, sizeof(creq.Password), creq.Password);
  ErlNifGetInt(env, req, n++, &creq.InstallID);
  ErlNifGetInt(env, req, n++, &creq.FutureSerial);
  ErlNifGetString(env, req, n++, sizeof(creq.UserID), creq.UserID);
  ErlNifGetChar(env, req, n++, &creq.VerifyCertNoFlag);
  ErlNifGetString(env, req, n++, sizeof(creq.CurrencyID), creq.CurrencyID);
  ErlNifGetDouble(env, req, n++, &creq.TradeAmount);
  ErlNifGetDouble(env, req, n++, &creq.FutureFetchAmount);
  ErlNifGetChar(env, req, n++, &creq.FeePayFlag);
  ErlNifGetDouble(env, req, n++, &creq.CustFee);
  ErlNifGetDouble(env, req, n++, &creq.BrokerFee);
  ErlNifGetString(env, req, n++, sizeof(creq.Message), creq.Message);
  ErlNifGetString(env, req, n++, sizeof(creq.Digest), creq.Digest);
  ErlNifGetChar(env, req, n++, &creq.BankAccType);
  ErlNifGetString(env, req, n++, sizeof(creq.DeviceID), creq.DeviceID);
  ErlNifGetChar(env, req, n++, &creq.BankSecuAccType);
  ErlNifGetString(env, req, n++, sizeof(creq.BrokerIDByBank),
                  creq.BrokerIDByBank);
  ErlNifGetString(env, req, n++, sizeof(creq.BankSecuAcc), creq.BankSecuAcc);
  ErlNifGetChar(env, req, n++, &creq.BankPwdFlag);
  ErlNifGetChar(env, req, n++, &creq.SecuPwdFlag);
  ErlNifGetString(env, req, n++, sizeof(creq.OperNo), creq.OperNo);
  ErlNifGetInt(env, req, n++, &creq.RequestID);
  ErlNifGetInt(env, req, n++, &creq.TID);
  ErlNifGetChar(env, req, n++, &creq.TransferStatus);

  return this->api_->ReqFromFutureToBankByFuture(&creq, req_id);
}

int CtpTd::ReqQueryBankAccountMoneyByFuture(ErlNifEnv *env, NifRecord *req,
                                            int req_id) {
  int n = 1;
  CThostFtdcReqQueryAccountField creq = {};

  ErlNifGetString(env, req, n++, sizeof(creq.TradeCode), creq.TradeCode);
  ErlNifGetString(env, req, n++, sizeof(creq.BankID), creq.BankID);
  ErlNifGetString(env, req, n++, sizeof(creq.BankBranchID), creq.BankBranchID);
  ErlNifGetString(env, req, n++, sizeof(creq.BrokerID), creq.BrokerID);
  ErlNifGetString(env, req, n++, sizeof(creq.BrokerBranchID),
                  creq.BrokerBranchID);
  ErlNifGetString(env, req, n++, sizeof(creq.TradeDate), creq.TradeDate);
  ErlNifGetString(env, req, n++, sizeof(creq.TradeTime), creq.TradeTime);
  ErlNifGetString(env, req, n++, sizeof(creq.BankSerial), creq.BankSerial);
  ErlNifGetString(env, req, n++, sizeof(creq.TradingDay), creq.TradingDay);
  ErlNifGetInt(env, req, n++, &creq.PlateSerial);
  ErlNifGetChar(env, req, n++, &creq.LastFragment);
  ErlNifGetInt(env, req, n++, &creq.SessionID);
  ErlNifGetString(env, req, n++, sizeof(creq.CustomerName), creq.CustomerName);
  ErlNifGetChar(env, req, n++, &creq.IdCardType);
  ErlNifGetString(env, req, n++, sizeof(creq.IdentifiedCardNo),
                  creq.IdentifiedCardNo);
  ErlNifGetChar(env, req, n++, &creq.CustType);
  ErlNifGetString(env, req, n++, sizeof(creq.BankAccount), creq.BankAccount);
  ErlNifGetString(env, req, n++, sizeof(creq.BankPassWord), creq.BankPassWord);
  ErlNifGetString(env, req, n++, sizeof(creq.AccountID), creq.AccountID);
  ErlNifGetString(env, req, n++, sizeof(creq.Password), creq.Password);
  ErlNifGetInt(env, req, n++, &creq.FutureSerial);
  ErlNifGetInt(env, req, n++, &creq.InstallID);
  ErlNifGetString(env, req, n++, sizeof(creq.UserID), creq.UserID);
  ErlNifGetChar(env, req, n++, &creq.VerifyCertNoFlag);
  ErlNifGetString(env, req, n++, sizeof(creq.CurrencyID), creq.CurrencyID);
  ErlNifGetString(env, req, n++, sizeof(creq.Digest), creq.Digest);
  ErlNifGetChar(env, req, n++, &creq.BankAccType);
  ErlNifGetString(env, req, n++, sizeof(creq.DeviceID), creq.DeviceID);
  ErlNifGetChar(env, req, n++, &creq.BankSecuAccType);
  ErlNifGetString(env, req, n++, sizeof(creq.BrokerIDByBank),
                  creq.BrokerIDByBank);
  ErlNifGetString(env, req, n++, sizeof(creq.BankSecuAcc), creq.BankSecuAcc);
  ErlNifGetChar(env, req, n++, &creq.BankPwdFlag);
  ErlNifGetChar(env, req, n++, &creq.SecuPwdFlag);
  ErlNifGetString(env, req, n++, sizeof(creq.OperNo), creq.OperNo);
  ErlNifGetInt(env, req, n++, &creq.RequestID);
  ErlNifGetInt(env, req, n++, &creq.TID);

  return this->api_->ReqQueryBankAccountMoneyByFuture(&creq, req_id);
}

/* -------------------------------------------------------------------------
 * SPI接口
 * -------------------------------------------------------------------------
 */

void CtpTd::OnFrontConnected() {
  ErlNifEnv *env = enif_alloc_env();
  enif_send(
      NULL, &this->pid_, env,
      enif_make_tuple2(
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple1(env, enif_make_atom(env, "on_front_connected"))));
  enif_free_env(env);
}

void CtpTd::OnFrontDisconnected(int reason) {
  ErlNifEnv *env = enif_alloc_env();
  enif_send(
      NULL, &this->pid_, env,
      enif_make_tuple2(
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple2(env, enif_make_atom(env, "on_front_disconnected"),
                           enif_make_int(env, reason))));
  enif_free_env(env);
}

void CtpTd::OnHeartBeatWarning(int time_lapse) {
  ErlNifEnv *env = enif_alloc_env();
  enif_send(
      NULL, &this->pid_, env,
      enif_make_tuple2(
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple2(env, enif_make_atom(env, "on_heart_beat_warnning"),
                           enif_make_int(env, time_lapse))));
  enif_free_env(env);
}

void CtpTd::OnRspAuthenticate(CThostFtdcRspAuthenticateField *data,
                              CThostFtdcRspInfoField *error, int req_id,
                              bool last) {
  static CThostFtdcRspAuthenticateField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_authenticate"),
              enif_make_tuple(
                  env, 4,
                  enif_make_atom(env, "cthost_ftdc_rsp_authenticate_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  ErlNifMakeGbkBinary(env, data->UserProductInfo)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspUserLogin(CThostFtdcRspUserLoginField *data,
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
          env, enif_make_atom(env, "ctp_td"),
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

void CtpTd::OnRspUserLogout(CThostFtdcUserLogoutField *data,
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
          env, enif_make_atom(env, "ctp_td"),
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

void CtpTd::OnRspUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *data,
                                    CThostFtdcRspInfoField *error, int req_id,
                                    bool last) {
  static CThostFtdcUserPasswordUpdateField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_user_password_update"),
              enif_make_tuple(
                  env, 5,
                  enif_make_atom(env, "cthost_ftdc_user_password_update_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  ErlNifMakeGbkBinary(env, data->OldPassword),
                  ErlNifMakeGbkBinary(env, data->NewPassword)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspTradingAccountPasswordUpdate(
    CThostFtdcTradingAccountPasswordUpdateField *data,
    CThostFtdcRspInfoField *error, int req_id, bool last) {
  static CThostFtdcTradingAccountPasswordUpdateField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env,
              enif_make_atom(env, "on_rsp_trading_account_password_update"),
              enif_make_tuple(
                  env, 6,
                  enif_make_atom(
                      env, "cthost_ftdc_trading_account_password_update_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->AccountID),
                  ErlNifMakeGbkBinary(env, data->OldPassword),
                  ErlNifMakeGbkBinary(env, data->NewPassword),
                  ErlNifMakeGbkBinary(env, data->CurrencyID)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspOrderInsert(CThostFtdcInputOrderField *data,
                             CThostFtdcRspInfoField *error, int req_id,
                             bool last) {
  static CThostFtdcInputOrderField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_order_insert"),
              enif_make_tuple(
                  env, 31, enif_make_atom(env, "cthost_ftdc_input_order_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  ErlNifMakeGbkBinary(env, data->InstrumentID),
                  ErlNifMakeGbkBinary(env, data->OrderRef),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  ErlNifMakeGbkBinary(env, data->OrderPriceType),
                  ErlNifMakeGbkBinary(env, data->Direction),
                  ErlNifMakeGbkBinary(env, data->CombOffsetFlag),
                  ErlNifMakeGbkBinary(env, data->CombHedgeFlag),
                  enif_make_double(env, data->LimitPrice),
                  enif_make_int(env, data->VolumeTotalOriginal),
                  ErlNifMakeGbkBinary(env, data->TimeCondition),
                  ErlNifMakeGbkBinary(env, data->GTDDate),
                  ErlNifMakeGbkBinary(env, data->VolumeCondition),
                  enif_make_int(env, data->MinVolume),
                  ErlNifMakeGbkBinary(env, data->ContingentCondition),
                  enif_make_double(env, data->StopPrice),
                  ErlNifMakeGbkBinary(env, data->ForceCloseReason),
                  enif_make_int(env, data->IsAutoSuspend),
                  ErlNifMakeGbkBinary(env, data->BusinessUnit),
                  enif_make_int(env, data->RequestID),
                  enif_make_int(env, data->UserForceClose),
                  enif_make_int(env, data->IsSwapOrder),
                  ErlNifMakeGbkBinary(env, data->ExchangeID),
                  ErlNifMakeGbkBinary(env, data->InvestUnitID),
                  ErlNifMakeGbkBinary(env, data->AccountID),
                  ErlNifMakeGbkBinary(env, data->CurrencyID),
                  ErlNifMakeGbkBinary(env, data->ClientID),
                  ErlNifMakeGbkBinary(env, data->IPAddress),
                  ErlNifMakeGbkBinary(env, data->MacAddress)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspParkedOrderInsert(CThostFtdcParkedOrderField *data,
                                   CThostFtdcRspInfoField *error, int req_id,
                                   bool last) {
  static CThostFtdcParkedOrderField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_parked_order_insert"),
              enif_make_tuple(
                  env, 36,
                  enif_make_atom(env, "cthost_ftdc_parked_order_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  ErlNifMakeGbkBinary(env, data->InstrumentID),
                  ErlNifMakeGbkBinary(env, data->OrderRef),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  ErlNifMakeGbkBinary(env, data->OrderPriceType),
                  ErlNifMakeGbkBinary(env, data->Direction),
                  ErlNifMakeGbkBinary(env, data->CombOffsetFlag),
                  ErlNifMakeGbkBinary(env, data->CombHedgeFlag),
                  enif_make_double(env, data->LimitPrice),
                  enif_make_int(env, data->VolumeTotalOriginal),
                  ErlNifMakeGbkBinary(env, data->TimeCondition),
                  ErlNifMakeGbkBinary(env, data->GTDDate),
                  ErlNifMakeGbkBinary(env, data->VolumeCondition),
                  enif_make_int(env, data->MinVolume),
                  ErlNifMakeGbkBinary(env, data->ContingentCondition),
                  enif_make_double(env, data->StopPrice),
                  ErlNifMakeGbkBinary(env, data->ForceCloseReason),
                  enif_make_int(env, data->IsAutoSuspend),
                  ErlNifMakeGbkBinary(env, data->BusinessUnit),
                  enif_make_int(env, data->RequestID),
                  enif_make_int(env, data->UserForceClose),
                  ErlNifMakeGbkBinary(env, data->ExchangeID),
                  ErlNifMakeGbkBinary(env, data->ParkedOrderID),
                  ErlNifMakeGbkBinary(env, data->UserType),
                  ErlNifMakeGbkBinary(env, data->Status),
                  enif_make_int(env, data->ErrorID),
                  ErlNifMakeGbkBinary(env, data->ErrorMsg),
                  enif_make_int(env, data->IsSwapOrder),
                  ErlNifMakeGbkBinary(env, data->AccountID),
                  ErlNifMakeGbkBinary(env, data->CurrencyID),
                  ErlNifMakeGbkBinary(env, data->ClientID),
                  ErlNifMakeGbkBinary(env, data->InvestUnitID),
                  ErlNifMakeGbkBinary(env, data->IPAddress),
                  ErlNifMakeGbkBinary(env, data->MacAddress)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspParkedOrderAction(CThostFtdcParkedOrderActionField *data,
                                   CThostFtdcRspInfoField *error, int req_id,
                                   bool last) {
  static CThostFtdcParkedOrderActionField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_parked_order_action"),
              enif_make_tuple(
                  env, 23,
                  enif_make_atom(env, "cthost_ftdc_parked_order_action_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  enif_make_int(env, data->OrderActionRef),
                  ErlNifMakeGbkBinary(env, data->OrderRef),
                  enif_make_int(env, data->RequestID),
                  enif_make_int(env, data->FrontID),
                  enif_make_int(env, data->SessionID),
                  ErlNifMakeGbkBinary(env, data->ExchangeID),
                  ErlNifMakeGbkBinary(env, data->OrderSysID),
                  ErlNifMakeGbkBinary(env, data->ActionFlag),
                  enif_make_double(env, data->LimitPrice),
                  enif_make_int(env, data->VolumeChange),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  ErlNifMakeGbkBinary(env, data->InstrumentID),
                  ErlNifMakeGbkBinary(env, data->ParkedOrderActionID),
                  ErlNifMakeGbkBinary(env, data->UserType),
                  ErlNifMakeGbkBinary(env, data->Status),
                  enif_make_int(env, data->ErrorID),
                  ErlNifMakeGbkBinary(env, data->ErrorMsg),
                  ErlNifMakeGbkBinary(env, data->InvestUnitID),
                  ErlNifMakeGbkBinary(env, data->IPAddress),
                  ErlNifMakeGbkBinary(env, data->MacAddress)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspOrderAction(CThostFtdcInputOrderActionField *data,
                             CThostFtdcRspInfoField *error, int req_id,
                             bool last) {
  static CThostFtdcInputOrderActionField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_order_action"),
              enif_make_tuple(
                  env, 18,
                  enif_make_atom(env, "cthost_ftdc_input_order_action_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  enif_make_int(env, data->OrderActionRef),
                  ErlNifMakeGbkBinary(env, data->OrderRef),
                  enif_make_int(env, data->RequestID),
                  enif_make_int(env, data->FrontID),
                  enif_make_int(env, data->SessionID),
                  ErlNifMakeGbkBinary(env, data->ExchangeID),
                  ErlNifMakeGbkBinary(env, data->OrderSysID),
                  ErlNifMakeGbkBinary(env, data->ActionFlag),
                  enif_make_double(env, data->LimitPrice),
                  enif_make_int(env, data->VolumeChange),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  ErlNifMakeGbkBinary(env, data->InstrumentID),
                  ErlNifMakeGbkBinary(env, data->InvestUnitID),
                  ErlNifMakeGbkBinary(env, data->IPAddress),
                  ErlNifMakeGbkBinary(env, data->MacAddress)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField *data,
                                     CThostFtdcRspInfoField *error, int req_id,
                                     bool last) {
  static CThostFtdcQueryMaxOrderVolumeField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_query_max_order_volume"),
              enif_make_tuple(
                  env, 9,
                  enif_make_atom(env,
                                 "cthost_ftdc_query_max_order_volume_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  ErlNifMakeGbkBinary(env, data->InstrumentID),
                  ErlNifMakeGbkBinary(env, data->Direction),
                  ErlNifMakeGbkBinary(env, data->OffsetFlag),
                  ErlNifMakeGbkBinary(env, data->HedgeFlag),
                  enif_make_int(env, data->MaxVolume),
                  ErlNifMakeGbkBinary(env, data->ExchangeID)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspSettlementInfoConfirm(
    CThostFtdcSettlementInfoConfirmField *data, CThostFtdcRspInfoField *error,
    int req_id, bool last) {
  static CThostFtdcSettlementInfoConfirmField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_settlement_info_confirm"),
              enif_make_tuple(
                  env, 5,
                  enif_make_atom(env,
                                 "cthost_ftdc_settlement_info_confirm_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  ErlNifMakeGbkBinary(env, data->ConfirmDate),
                  ErlNifMakeGbkBinary(env, data->ConfirmTime)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *data,
                                   CThostFtdcRspInfoField *error, int req_id,
                                   bool last) {
  static CThostFtdcRemoveParkedOrderField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_remove_parked_order"),
              enif_make_tuple(
                  env, 4,
                  enif_make_atom(env, "cthost_ftdc_remove_parked_order_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  ErlNifMakeGbkBinary(env, data->ParkedOrderID)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspRemoveParkedOrderAction(
    CThostFtdcRemoveParkedOrderActionField *data, CThostFtdcRspInfoField *error,
    int req_id, bool last) {
  static CThostFtdcRemoveParkedOrderActionField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_remove_parked_order_action"),
              enif_make_tuple(
                  env, 4,
                  enif_make_atom(
                      env, "cthost_ftdc_remove_parked_order_action_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  ErlNifMakeGbkBinary(env, data->ParkedOrderActionID)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspExecOrderInsert(CThostFtdcInputExecOrderField *data,
                                 CThostFtdcRspInfoField *error, int req_id,
                                 bool last) {
  static CThostFtdcInputExecOrderField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_exec_order_insert"),
              enif_make_tuple(
                  env, 22,
                  enif_make_atom(env, "cthost_ftdc_input_exec_order_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  ErlNifMakeGbkBinary(env, data->InstrumentID),
                  ErlNifMakeGbkBinary(env, data->ExecOrderRef),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  enif_make_int(env, data->Volume),
                  enif_make_int(env, data->RequestID),
                  ErlNifMakeGbkBinary(env, data->BusinessUnit),
                  ErlNifMakeGbkBinary(env, data->OffsetFlag),
                  ErlNifMakeGbkBinary(env, data->HedgeFlag),
                  ErlNifMakeGbkBinary(env, data->ActionType),
                  ErlNifMakeGbkBinary(env, data->PosiDirection),
                  ErlNifMakeGbkBinary(env, data->ReservePositionFlag),
                  ErlNifMakeGbkBinary(env, data->CloseFlag),
                  ErlNifMakeGbkBinary(env, data->ExchangeID),
                  ErlNifMakeGbkBinary(env, data->InvestUnitID),
                  ErlNifMakeGbkBinary(env, data->AccountID),
                  ErlNifMakeGbkBinary(env, data->CurrencyID),
                  ErlNifMakeGbkBinary(env, data->ClientID),
                  ErlNifMakeGbkBinary(env, data->IPAddress),
                  ErlNifMakeGbkBinary(env, data->MacAddress)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspExecOrderAction(CThostFtdcInputExecOrderActionField *data,
                                 CThostFtdcRspInfoField *error, int req_id,
                                 bool last) {
  static CThostFtdcInputExecOrderActionField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_exec_order_action"),
              enif_make_tuple(
                  env, 16,
                  enif_make_atom(env,
                                 "cthost_ftdc_input_exec_order_action_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  enif_make_int(env, data->ExecOrderActionRef),
                  ErlNifMakeGbkBinary(env, data->ExecOrderRef),
                  enif_make_int(env, data->RequestID),
                  enif_make_int(env, data->FrontID),
                  enif_make_int(env, data->SessionID),
                  ErlNifMakeGbkBinary(env, data->ExchangeID),
                  ErlNifMakeGbkBinary(env, data->ExecOrderSysID),
                  ErlNifMakeGbkBinary(env, data->ActionFlag),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  ErlNifMakeGbkBinary(env, data->InstrumentID),
                  ErlNifMakeGbkBinary(env, data->InvestUnitID),
                  ErlNifMakeGbkBinary(env, data->IPAddress),
                  ErlNifMakeGbkBinary(env, data->MacAddress)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspForQuoteInsert(CThostFtdcInputForQuoteField *data,
                                CThostFtdcRspInfoField *error, int req_id,
                                bool last) {
  static CThostFtdcInputForQuoteField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_for_quote_insert"),
              enif_make_tuple(
                  env, 10,
                  enif_make_atom(env, "cthost_ftdc_input_for_quote_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  ErlNifMakeGbkBinary(env, data->InstrumentID),
                  ErlNifMakeGbkBinary(env, data->ForQuoteRef),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  ErlNifMakeGbkBinary(env, data->ExchangeID),
                  ErlNifMakeGbkBinary(env, data->InvestUnitID),
                  ErlNifMakeGbkBinary(env, data->IPAddress),
                  ErlNifMakeGbkBinary(env, data->MacAddress)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQuoteInsert(CThostFtdcInputQuoteField *data,
                             CThostFtdcRspInfoField *error, int req_id,
                             bool last) {
  static CThostFtdcInputQuoteField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_quote_insert"),
              enif_make_tuple(
                  env, 24, enif_make_atom(env, "cthost_ftdc_input_quote_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  ErlNifMakeGbkBinary(env, data->InstrumentID),
                  ErlNifMakeGbkBinary(env, data->QuoteRef),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  enif_make_double(env, data->AskPrice),
                  enif_make_double(env, data->BidPrice),
                  enif_make_int(env, data->AskVolume),
                  enif_make_int(env, data->BidVolume),
                  enif_make_int(env, data->RequestID),
                  ErlNifMakeGbkBinary(env, data->BusinessUnit),
                  ErlNifMakeGbkBinary(env, data->AskOffsetFlag),
                  ErlNifMakeGbkBinary(env, data->BidOffsetFlag),
                  ErlNifMakeGbkBinary(env, data->AskHedgeFlag),
                  ErlNifMakeGbkBinary(env, data->BidHedgeFlag),
                  ErlNifMakeGbkBinary(env, data->AskOrderRef),
                  ErlNifMakeGbkBinary(env, data->BidOrderRef),
                  ErlNifMakeGbkBinary(env, data->ForQuoteSysID),
                  ErlNifMakeGbkBinary(env, data->ExchangeID),
                  ErlNifMakeGbkBinary(env, data->InvestUnitID),
                  ErlNifMakeGbkBinary(env, data->ClientID),
                  ErlNifMakeGbkBinary(env, data->IPAddress),
                  ErlNifMakeGbkBinary(env, data->MacAddress)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQuoteAction(CThostFtdcInputQuoteActionField *data,
                             CThostFtdcRspInfoField *error, int req_id,
                             bool last) {
  static CThostFtdcInputQuoteActionField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_quote_action"),
              enif_make_tuple(
                  env, 17,
                  enif_make_atom(env, "cthost_ftdc_input_quote_action_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  enif_make_int(env, data->QuoteActionRef),
                  ErlNifMakeGbkBinary(env, data->QuoteRef),
                  enif_make_int(env, data->RequestID),
                  enif_make_int(env, data->FrontID),
                  enif_make_int(env, data->SessionID),
                  ErlNifMakeGbkBinary(env, data->ExchangeID),
                  ErlNifMakeGbkBinary(env, data->QuoteSysID),
                  ErlNifMakeGbkBinary(env, data->ActionFlag),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  ErlNifMakeGbkBinary(env, data->InstrumentID),
                  ErlNifMakeGbkBinary(env, data->InvestUnitID),
                  ErlNifMakeGbkBinary(env, data->ClientID),
                  ErlNifMakeGbkBinary(env, data->IPAddress),
                  ErlNifMakeGbkBinary(env, data->MacAddress)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspLockInsert(CThostFtdcInputLockField *data,
                            CThostFtdcRspInfoField *error, int req_id,
                            bool last) {
  static CThostFtdcInputLockField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_lock_insert"),
              enif_make_tuple(
                  env, 13, enif_make_atom(env, "cthost_ftdc_input_lock_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  ErlNifMakeGbkBinary(env, data->InstrumentID),
                  ErlNifMakeGbkBinary(env, data->LockRef),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  enif_make_int(env, data->Volume),
                  enif_make_int(env, data->RequestID),
                  ErlNifMakeGbkBinary(env, data->BusinessUnit),
                  ErlNifMakeGbkBinary(env, data->LockType),
                  ErlNifMakeGbkBinary(env, data->ExchangeID),
                  ErlNifMakeGbkBinary(env, data->IPAddress),
                  ErlNifMakeGbkBinary(env, data->MacAddress)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspBatchOrderAction(CThostFtdcInputBatchOrderActionField *data,
                                  CThostFtdcRspInfoField *error, int req_id,
                                  bool last) {
  static CThostFtdcInputBatchOrderActionField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_batch_order_action"),
              enif_make_tuple(
                  env, 12,
                  enif_make_atom(env,
                                 "cthost_ftdc_input_batch_order_action_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  enif_make_int(env, data->OrderActionRef),
                  enif_make_int(env, data->RequestID),
                  enif_make_int(env, data->FrontID),
                  enif_make_int(env, data->SessionID),
                  ErlNifMakeGbkBinary(env, data->ExchangeID),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  ErlNifMakeGbkBinary(env, data->InvestUnitID),
                  ErlNifMakeGbkBinary(env, data->IPAddress),
                  ErlNifMakeGbkBinary(env, data->MacAddress)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspCombActionInsert(CThostFtdcInputCombActionField *data,
                                  CThostFtdcRspInfoField *error, int req_id,
                                  bool last) {
  static CThostFtdcInputCombActionField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_comb_action_insert"),
              enif_make_tuple(
                  env, 13,
                  enif_make_atom(env, "cthost_ftdc_input_comb_action_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  ErlNifMakeGbkBinary(env, data->InstrumentID),
                  ErlNifMakeGbkBinary(env, data->CombActionRef),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  ErlNifMakeGbkBinary(env, data->Direction),
                  enif_make_int(env, data->Volume),
                  ErlNifMakeGbkBinary(env, data->CombDirection),
                  ErlNifMakeGbkBinary(env, data->HedgeFlag),
                  ErlNifMakeGbkBinary(env, data->ExchangeID),
                  ErlNifMakeGbkBinary(env, data->IPAddress),
                  ErlNifMakeGbkBinary(env, data->MacAddress)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQryOrder(CThostFtdcOrderField *data,
                          CThostFtdcRspInfoField *error, int req_id,
                          bool last) {
  static CThostFtdcOrderField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_qry_order"),
              enif_make_tuple(
                  env, 64, enif_make_atom(env, "cthost_ftdc_order_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  ErlNifMakeGbkBinary(env, data->InstrumentID),
                  ErlNifMakeGbkBinary(env, data->OrderRef),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  ErlNifMakeGbkBinary(env, data->OrderPriceType),
                  ErlNifMakeGbkBinary(env, data->Direction),
                  ErlNifMakeGbkBinary(env, data->CombOffsetFlag),
                  ErlNifMakeGbkBinary(env, data->CombHedgeFlag),
                  enif_make_double(env, data->LimitPrice),
                  enif_make_int(env, data->VolumeTotalOriginal),
                  ErlNifMakeGbkBinary(env, data->TimeCondition),
                  ErlNifMakeGbkBinary(env, data->GTDDate),
                  ErlNifMakeGbkBinary(env, data->VolumeCondition),
                  enif_make_int(env, data->MinVolume),
                  ErlNifMakeGbkBinary(env, data->ContingentCondition),
                  enif_make_double(env, data->StopPrice),
                  ErlNifMakeGbkBinary(env, data->ForceCloseReason),
                  enif_make_int(env, data->IsAutoSuspend),
                  ErlNifMakeGbkBinary(env, data->BusinessUnit),
                  enif_make_int(env, data->RequestID),
                  ErlNifMakeGbkBinary(env, data->OrderLocalID),
                  ErlNifMakeGbkBinary(env, data->ExchangeID),
                  ErlNifMakeGbkBinary(env, data->ParticipantID),
                  ErlNifMakeGbkBinary(env, data->ClientID),
                  ErlNifMakeGbkBinary(env, data->ExchangeInstID),
                  ErlNifMakeGbkBinary(env, data->TraderID),
                  enif_make_int(env, data->InstallID),
                  ErlNifMakeGbkBinary(env, data->OrderSubmitStatus),
                  enif_make_int(env, data->NotifySequence),
                  ErlNifMakeGbkBinary(env, data->TradingDay),
                  enif_make_int(env, data->SettlementID),
                  ErlNifMakeGbkBinary(env, data->OrderSysID),
                  ErlNifMakeGbkBinary(env, data->OrderSource),
                  ErlNifMakeGbkBinary(env, data->OrderStatus),
                  ErlNifMakeGbkBinary(env, data->OrderType),
                  enif_make_int(env, data->VolumeTraded),
                  enif_make_int(env, data->VolumeTotal),
                  ErlNifMakeGbkBinary(env, data->InsertDate),
                  ErlNifMakeGbkBinary(env, data->InsertTime),
                  ErlNifMakeGbkBinary(env, data->ActiveTime),
                  ErlNifMakeGbkBinary(env, data->SuspendTime),
                  ErlNifMakeGbkBinary(env, data->UpdateTime),
                  ErlNifMakeGbkBinary(env, data->CancelTime),
                  ErlNifMakeGbkBinary(env, data->ActiveTraderID),
                  ErlNifMakeGbkBinary(env, data->ClearingPartID),
                  enif_make_int(env, data->SequenceNo),
                  enif_make_int(env, data->FrontID),
                  enif_make_int(env, data->SessionID),
                  ErlNifMakeGbkBinary(env, data->UserProductInfo),
                  ErlNifMakeGbkBinary(env, data->StatusMsg),
                  enif_make_int(env, data->UserForceClose),
                  ErlNifMakeGbkBinary(env, data->ActiveUserID),
                  enif_make_int(env, data->BrokerOrderSeq),
                  ErlNifMakeGbkBinary(env, data->RelativeOrderSysID),
                  enif_make_int(env, data->ZCETotalTradedVolume),
                  enif_make_int(env, data->IsSwapOrder),
                  ErlNifMakeGbkBinary(env, data->BranchID),
                  ErlNifMakeGbkBinary(env, data->InvestUnitID),
                  ErlNifMakeGbkBinary(env, data->AccountID),
                  ErlNifMakeGbkBinary(env, data->CurrencyID),
                  ErlNifMakeGbkBinary(env, data->IPAddress),
                  ErlNifMakeGbkBinary(env, data->MacAddress)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQryTrade(CThostFtdcTradeField *data,
                          CThostFtdcRspInfoField *error, int req_id,
                          bool last) {
  static CThostFtdcTradeField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_qry_trade"),
              enif_make_tuple(env, 31,
                              enif_make_atom(env, "cthost_ftdc_trade_field"),
                              ErlNifMakeGbkBinary(env, data->BrokerID),
                              ErlNifMakeGbkBinary(env, data->InvestorID),
                              ErlNifMakeGbkBinary(env, data->InstrumentID),
                              ErlNifMakeGbkBinary(env, data->OrderRef),
                              ErlNifMakeGbkBinary(env, data->UserID),
                              ErlNifMakeGbkBinary(env, data->ExchangeID),
                              ErlNifMakeGbkBinary(env, data->TradeID),
                              ErlNifMakeGbkBinary(env, data->Direction),
                              ErlNifMakeGbkBinary(env, data->OrderSysID),
                              ErlNifMakeGbkBinary(env, data->ParticipantID),
                              ErlNifMakeGbkBinary(env, data->ClientID),
                              ErlNifMakeGbkBinary(env, data->TradingRole),
                              ErlNifMakeGbkBinary(env, data->ExchangeInstID),
                              ErlNifMakeGbkBinary(env, data->OffsetFlag),
                              ErlNifMakeGbkBinary(env, data->HedgeFlag),
                              enif_make_double(env, data->Price),
                              enif_make_int(env, data->Volume),
                              ErlNifMakeGbkBinary(env, data->TradeDate),
                              ErlNifMakeGbkBinary(env, data->TradeTime),
                              ErlNifMakeGbkBinary(env, data->TradeType),
                              ErlNifMakeGbkBinary(env, data->PriceSource),
                              ErlNifMakeGbkBinary(env, data->TraderID),
                              ErlNifMakeGbkBinary(env, data->OrderLocalID),
                              ErlNifMakeGbkBinary(env, data->ClearingPartID),
                              ErlNifMakeGbkBinary(env, data->BusinessUnit),
                              enif_make_int(env, data->SequenceNo),
                              ErlNifMakeGbkBinary(env, data->TradingDay),
                              enif_make_int(env, data->SettlementID),
                              enif_make_int(env, data->BrokerOrderSeq),
                              ErlNifMakeGbkBinary(env, data->TradeSource)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *data,
                                     CThostFtdcRspInfoField *error, int req_id,
                                     bool last) {
  static CThostFtdcInvestorPositionField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_qry_investor_position"),
              enif_make_tuple(
                  env, 46,
                  enif_make_atom(env, "cthost_ftdc_investor_position_field"),
                  ErlNifMakeGbkBinary(env, data->InstrumentID),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  ErlNifMakeGbkBinary(env, data->PosiDirection),
                  ErlNifMakeGbkBinary(env, data->HedgeFlag),
                  ErlNifMakeGbkBinary(env, data->PositionDate),
                  enif_make_int(env, data->YdPosition),
                  enif_make_int(env, data->Position),
                  enif_make_int(env, data->LongFrozen),
                  enif_make_int(env, data->ShortFrozen),
                  enif_make_double(env, data->LongFrozenAmount),
                  enif_make_double(env, data->ShortFrozenAmount),
                  enif_make_int(env, data->OpenVolume),
                  enif_make_int(env, data->CloseVolume),
                  enif_make_double(env, data->OpenAmount),
                  enif_make_double(env, data->CloseAmount),
                  enif_make_double(env, data->PositionCost),
                  enif_make_double(env, data->PreMargin),
                  enif_make_double(env, data->UseMargin),
                  enif_make_double(env, data->FrozenMargin),
                  enif_make_double(env, data->FrozenCash),
                  enif_make_double(env, data->FrozenCommission),
                  enif_make_double(env, data->CashIn),
                  enif_make_double(env, data->Commission),
                  enif_make_double(env, data->CloseProfit),
                  enif_make_double(env, data->PositionProfit),
                  enif_make_double(env, data->PreSettlementPrice),
                  enif_make_double(env, data->SettlementPrice),
                  ErlNifMakeGbkBinary(env, data->TradingDay),
                  enif_make_int(env, data->SettlementID),
                  enif_make_double(env, data->OpenCost),
                  enif_make_double(env, data->ExchangeMargin),
                  enif_make_int(env, data->CombPosition),
                  enif_make_int(env, data->CombLongFrozen),
                  enif_make_int(env, data->CombShortFrozen),
                  enif_make_double(env, data->CloseProfitByDate),
                  enif_make_double(env, data->CloseProfitByTrade),
                  enif_make_int(env, data->TodayPosition),
                  enif_make_double(env, data->MarginRateByMoney),
                  enif_make_double(env, data->MarginRateByVolume),
                  enif_make_int(env, data->StrikeFrozen),
                  enif_make_double(env, data->StrikeFrozenAmount),
                  enif_make_int(env, data->AbandonFrozen),
                  ErlNifMakeGbkBinary(env, data->ExchangeID),
                  enif_make_int(env, data->YdStrikeFrozen)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQryTradingAccount(CThostFtdcTradingAccountField *data,
                                   CThostFtdcRspInfoField *error, int req_id,
                                   bool last) {
  static CThostFtdcTradingAccountField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_qry_trading_account"),
              enif_make_tuple(
                  env, 48,
                  enif_make_atom(env, "cthost_ftdc_trading_account_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->AccountID),
                  enif_make_double(env, data->PreMortgage),
                  enif_make_double(env, data->PreCredit),
                  enif_make_double(env, data->PreDeposit),
                  enif_make_double(env, data->PreBalance),
                  enif_make_double(env, data->PreMargin),
                  enif_make_double(env, data->InterestBase),
                  enif_make_double(env, data->Interest),
                  enif_make_double(env, data->Deposit),
                  enif_make_double(env, data->Withdraw),
                  enif_make_double(env, data->FrozenMargin),
                  enif_make_double(env, data->FrozenCash),
                  enif_make_double(env, data->FrozenCommission),
                  enif_make_double(env, data->CurrMargin),
                  enif_make_double(env, data->CashIn),
                  enif_make_double(env, data->Commission),
                  enif_make_double(env, data->CloseProfit),
                  enif_make_double(env, data->PositionProfit),
                  enif_make_double(env, data->Balance),
                  enif_make_double(env, data->Available),
                  enif_make_double(env, data->WithdrawQuota),
                  enif_make_double(env, data->Reserve),
                  ErlNifMakeGbkBinary(env, data->TradingDay),
                  enif_make_int(env, data->SettlementID),
                  enif_make_double(env, data->Credit),
                  enif_make_double(env, data->Mortgage),
                  enif_make_double(env, data->ExchangeMargin),
                  enif_make_double(env, data->DeliveryMargin),
                  enif_make_double(env, data->ExchangeDeliveryMargin),
                  enif_make_double(env, data->ReserveBalance),
                  ErlNifMakeGbkBinary(env, data->CurrencyID),
                  enif_make_double(env, data->PreFundMortgageIn),
                  enif_make_double(env, data->PreFundMortgageOut),
                  enif_make_double(env, data->FundMortgageIn),
                  enif_make_double(env, data->FundMortgageOut),
                  enif_make_double(env, data->FundMortgageAvailable),
                  enif_make_double(env, data->MortgageableFund),
                  enif_make_double(env, data->SpecProductMargin),
                  enif_make_double(env, data->SpecProductFrozenMargin),
                  enif_make_double(env, data->SpecProductCommission),
                  enif_make_double(env, data->SpecProductFrozenCommission),
                  enif_make_double(env, data->SpecProductPositionProfit),
                  enif_make_double(env, data->SpecProductCloseProfit),
                  enif_make_double(env, data->SpecProductPositionProfitByAlg),
                  enif_make_double(env, data->SpecProductExchangeMargin),
                  ErlNifMakeGbkBinary(env, data->BizType)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQryInvestor(CThostFtdcInvestorField *data,
                             CThostFtdcRspInfoField *error, int req_id,
                             bool last) {
  static CThostFtdcInvestorField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_qry_investor"),
              enif_make_tuple(
                  env, 14, enif_make_atom(env, "cthost_ftdc_investor_field"),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorGroupID),
                  ErlNifMakeGbkBinary(env, data->InvestorName),
                  ErlNifMakeGbkBinary(env, data->IdentifiedCardType),
                  ErlNifMakeGbkBinary(env, data->IdentifiedCardNo),
                  enif_make_int(env, data->IsActive),
                  ErlNifMakeGbkBinary(env, data->Telephone),
                  ErlNifMakeGbkBinary(env, data->Address),
                  ErlNifMakeGbkBinary(env, data->OpenDate),
                  ErlNifMakeGbkBinary(env, data->Mobile),
                  ErlNifMakeGbkBinary(env, data->CommModelID),
                  ErlNifMakeGbkBinary(env, data->MarginModelID)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQryTradingCode(CThostFtdcTradingCodeField *data,
                                CThostFtdcRspInfoField *error, int req_id,
                                bool last) {
  static CThostFtdcTradingCodeField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_qry_trading_code"),
              enif_make_tuple(
                  env, 9, enif_make_atom(env, "cthost_ftdc_trading_code_field"),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->ExchangeID),
                  ErlNifMakeGbkBinary(env, data->ClientID),
                  enif_make_int(env, data->IsActive),
                  ErlNifMakeGbkBinary(env, data->ClientIDType),
                  ErlNifMakeGbkBinary(env, data->BranchID),
                  ErlNifMakeGbkBinary(env, data->BizType)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQryInstrumentMarginRate(
    CThostFtdcInstrumentMarginRateField *data, CThostFtdcRspInfoField *error,
    int req_id, bool last) {
  static CThostFtdcInstrumentMarginRateField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_qry_instrument_margin_rate"),
              enif_make_tuple(
                  env, 11,
                  enif_make_atom(env,
                                 "cthost_ftdc_instrument_margin_rate_field"),
                  ErlNifMakeGbkBinary(env, data->InstrumentID),
                  ErlNifMakeGbkBinary(env, data->InvestorRange),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  ErlNifMakeGbkBinary(env, data->HedgeFlag),
                  enif_make_double(env, data->LongMarginRatioByMoney),
                  enif_make_double(env, data->LongMarginRatioByVolume),
                  enif_make_double(env, data->ShortMarginRatioByMoney),
                  enif_make_double(env, data->ShortMarginRatioByVolume),
                  enif_make_int(env, data->IsRelative)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQryInstrumentCommissionRate(
    CThostFtdcInstrumentCommissionRateField *data,
    CThostFtdcRspInfoField *error, int req_id, bool last) {
  static CThostFtdcInstrumentCommissionRateField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_qry_instrument_commission_rate"),
              enif_make_tuple(
                  env, 13,
                  enif_make_atom(
                      env, "cthost_ftdc_instrument_commission_rate_field"),
                  ErlNifMakeGbkBinary(env, data->InstrumentID),
                  ErlNifMakeGbkBinary(env, data->InvestorRange),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  enif_make_double(env, data->OpenRatioByMoney),
                  enif_make_double(env, data->OpenRatioByVolume),
                  enif_make_double(env, data->CloseRatioByMoney),
                  enif_make_double(env, data->CloseRatioByVolume),
                  enif_make_double(env, data->CloseTodayRatioByMoney),
                  enif_make_double(env, data->CloseTodayRatioByVolume),
                  ErlNifMakeGbkBinary(env, data->ExchangeID),
                  ErlNifMakeGbkBinary(env, data->BizType)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQryExchange(CThostFtdcExchangeField *data,
                             CThostFtdcRspInfoField *error, int req_id,
                             bool last) {
  static CThostFtdcExchangeField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_qry_exchange"),
              enif_make_tuple(env, 4,
                              enif_make_atom(env, "cthost_ftdc_exchange_field"),
                              ErlNifMakeGbkBinary(env, data->ExchangeID),
                              ErlNifMakeGbkBinary(env, data->ExchangeName),
                              ErlNifMakeGbkBinary(env, data->ExchangeProperty)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQryProduct(CThostFtdcProductField *data,
                            CThostFtdcRspInfoField *error, int req_id,
                            bool last) {
  static CThostFtdcProductField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_qry_product"),
              enif_make_tuple(
                  env, 18, enif_make_atom(env, "cthost_ftdc_product_field"),
                  ErlNifMakeGbkBinary(env, data->ProductID),
                  ErlNifMakeGbkBinary(env, data->ProductName),
                  ErlNifMakeGbkBinary(env, data->ExchangeID),
                  ErlNifMakeGbkBinary(env, data->ProductClass),
                  enif_make_int(env, data->VolumeMultiple),
                  enif_make_double(env, data->PriceTick),
                  enif_make_int(env, data->MaxMarketOrderVolume),
                  enif_make_int(env, data->MinMarketOrderVolume),
                  enif_make_int(env, data->MaxLimitOrderVolume),
                  enif_make_int(env, data->MinLimitOrderVolume),
                  ErlNifMakeGbkBinary(env, data->PositionType),
                  ErlNifMakeGbkBinary(env, data->PositionDateType),
                  ErlNifMakeGbkBinary(env, data->CloseDealType),
                  ErlNifMakeGbkBinary(env, data->TradeCurrencyID),
                  ErlNifMakeGbkBinary(env, data->MortgageFundUseRange),
                  ErlNifMakeGbkBinary(env, data->ExchangeProductID),
                  enif_make_double(env, data->UnderlyingMultiple)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQryInstrument(CThostFtdcInstrumentField *data,
                               CThostFtdcRspInfoField *error, int req_id,
                               bool last) {
  static CThostFtdcInstrumentField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_qry_instrument"),
              enif_make_tuple(
                  env, 35, enif_make_atom(env, "cthost_ftdc_instrument_field"),
                  ErlNifMakeGbkBinary(env, data->InstrumentID),
                  ErlNifMakeGbkBinary(env, data->ExchangeID),
                  ErlNifMakeGbkBinary(env, data->InstrumentName),
                  ErlNifMakeGbkBinary(env, data->ExchangeInstID),
                  ErlNifMakeGbkBinary(env, data->ProductID),
                  ErlNifMakeGbkBinary(env, data->ProductClass),
                  enif_make_int(env, data->DeliveryYear),
                  enif_make_int(env, data->DeliveryMonth),
                  enif_make_int(env, data->MaxMarketOrderVolume),
                  enif_make_int(env, data->MinMarketOrderVolume),
                  enif_make_int(env, data->MaxLimitOrderVolume),
                  enif_make_int(env, data->MinLimitOrderVolume),
                  enif_make_int(env, data->VolumeMultiple),
                  enif_make_double(env, data->PriceTick),
                  ErlNifMakeGbkBinary(env, data->CreateDate),
                  ErlNifMakeGbkBinary(env, data->OpenDate),
                  ErlNifMakeGbkBinary(env, data->ExpireDate),
                  ErlNifMakeGbkBinary(env, data->StartDelivDate),
                  ErlNifMakeGbkBinary(env, data->EndDelivDate),
                  ErlNifMakeGbkBinary(env, data->InstLifePhase),
                  enif_make_int(env, data->IsTrading),
                  ErlNifMakeGbkBinary(env, data->PositionType),
                  ErlNifMakeGbkBinary(env, data->PositionDateType),
                  enif_make_double(env, data->LongMarginRatio),
                  enif_make_double(env, data->ShortMarginRatio),
                  ErlNifMakeGbkBinary(env, data->MaxMarginSideAlgorithm),
                  ErlNifMakeGbkBinary(env, data->UnderlyingInstrID),
                  enif_make_double(env, data->StrikePrice),
                  ErlNifMakeGbkBinary(env, data->OptionsType),
                  enif_make_double(env, data->UnderlyingMultiple),
                  ErlNifMakeGbkBinary(env, data->CombinationType),
                  enif_make_int(env, data->MinBuyVolume),
                  enif_make_int(env, data->MinSellVolume),
                  ErlNifMakeGbkBinary(env, data->InstrumentCode)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *data,
                                    CThostFtdcRspInfoField *error, int req_id,
                                    bool last) {
  static CThostFtdcDepthMarketDataField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_qry_depth_market_data"),
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
                  ErlNifMakeGbkBinary(env, data->ActionDay)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *data,
                                   CThostFtdcRspInfoField *error, int req_id,
                                   bool last) {
  static CThostFtdcSettlementInfoField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_qry_settlement_info"),
              enif_make_tuple(
                  env, 7,
                  enif_make_atom(env, "cthost_ftdc_settlement_info_field"),
                  ErlNifMakeGbkBinary(env, data->TradingDay),
                  enif_make_int(env, data->SettlementID),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  enif_make_int(env, data->SequenceNo),
                  ErlNifMakeGbkBinary(env, data->Content)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQryTransferBank(CThostFtdcTransferBankField *data,
                                 CThostFtdcRspInfoField *error, int req_id,
                                 bool last) {
  static CThostFtdcTransferBankField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_qry_transfer_bank"),
              enif_make_tuple(
                  env, 5,
                  enif_make_atom(env, "cthost_ftdc_transfer_bank_field"),
                  ErlNifMakeGbkBinary(env, data->BankID),
                  ErlNifMakeGbkBinary(env, data->BankBrchID),
                  ErlNifMakeGbkBinary(env, data->BankName),
                  enif_make_int(env, data->IsActive)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQryInvestorPositionDetail(
    CThostFtdcInvestorPositionDetailField *data, CThostFtdcRspInfoField *error,
    int req_id, bool last) {
  static CThostFtdcInvestorPositionDetailField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_qry_investor_position_detail"),
              enif_make_tuple(
                  env, 27,
                  enif_make_atom(env,
                                 "cthost_ftdc_investor_position_detail_field"),
                  ErlNifMakeGbkBinary(env, data->InstrumentID),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  ErlNifMakeGbkBinary(env, data->HedgeFlag),
                  ErlNifMakeGbkBinary(env, data->Direction),
                  ErlNifMakeGbkBinary(env, data->OpenDate),
                  ErlNifMakeGbkBinary(env, data->TradeID),
                  enif_make_int(env, data->Volume),
                  enif_make_double(env, data->OpenPrice),
                  ErlNifMakeGbkBinary(env, data->TradingDay),
                  enif_make_int(env, data->SettlementID),
                  ErlNifMakeGbkBinary(env, data->TradeType),
                  ErlNifMakeGbkBinary(env, data->CombInstrumentID),
                  ErlNifMakeGbkBinary(env, data->ExchangeID),
                  enif_make_double(env, data->CloseProfitByDate),
                  enif_make_double(env, data->CloseProfitByTrade),
                  enif_make_double(env, data->PositionProfitByDate),
                  enif_make_double(env, data->PositionProfitByTrade),
                  enif_make_double(env, data->Margin),
                  enif_make_double(env, data->ExchMargin),
                  enif_make_double(env, data->MarginRateByMoney),
                  enif_make_double(env, data->MarginRateByVolume),
                  enif_make_double(env, data->LastSettlementPrice),
                  enif_make_double(env, data->SettlementPrice),
                  enif_make_int(env, data->CloseVolume),
                  enif_make_double(env, data->CloseAmount)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQryNotice(CThostFtdcNoticeField *data,
                           CThostFtdcRspInfoField *error, int req_id,
                           bool last) {
  static CThostFtdcNoticeField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_qry_notice"),
              enif_make_tuple(env, 4,
                              enif_make_atom(env, "cthost_ftdc_notice_field"),
                              ErlNifMakeGbkBinary(env, data->BrokerID),
                              ErlNifMakeGbkBinary(env, data->Content),
                              ErlNifMakeGbkBinary(env, data->SequenceLabel)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQrySettlementInfoConfirm(
    CThostFtdcSettlementInfoConfirmField *data, CThostFtdcRspInfoField *error,
    int req_id, bool last) {
  static CThostFtdcSettlementInfoConfirmField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_qry_settlement_info_confirm"),
              enif_make_tuple(
                  env, 5,
                  enif_make_atom(env,
                                 "cthost_ftdc_settlement_info_confirm_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  ErlNifMakeGbkBinary(env, data->ConfirmDate),
                  ErlNifMakeGbkBinary(env, data->ConfirmTime)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQryInvestorPositionCombineDetail(
    CThostFtdcInvestorPositionCombineDetailField *data,
    CThostFtdcRspInfoField *error, int req_id, bool last) {
  static CThostFtdcInvestorPositionCombineDetailField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env,
              enif_make_atom(env,
                             "on_rsp_qry_investor_position_combine_detail"),
              enif_make_tuple(
                  env, 21,
                  enif_make_atom(
                      env,
                      "cthost_ftdc_investor_position_combine_detail_field"),
                  ErlNifMakeGbkBinary(env, data->TradingDay),
                  ErlNifMakeGbkBinary(env, data->OpenDate),
                  ErlNifMakeGbkBinary(env, data->ExchangeID),
                  enif_make_int(env, data->SettlementID),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  ErlNifMakeGbkBinary(env, data->ComTradeID),
                  ErlNifMakeGbkBinary(env, data->TradeID),
                  ErlNifMakeGbkBinary(env, data->InstrumentID),
                  ErlNifMakeGbkBinary(env, data->HedgeFlag),
                  ErlNifMakeGbkBinary(env, data->Direction),
                  enif_make_int(env, data->TotalAmt),
                  enif_make_double(env, data->Margin),
                  enif_make_double(env, data->ExchMargin),
                  enif_make_double(env, data->MarginRateByMoney),
                  enif_make_double(env, data->MarginRateByVolume),
                  enif_make_int(env, data->LegID),
                  enif_make_int(env, data->LegMultiple),
                  ErlNifMakeGbkBinary(env, data->CombInstrumentID),
                  enif_make_int(env, data->TradeGroupID)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQryCFMMCTradingAccountKey(
    CThostFtdcCFMMCTradingAccountKeyField *data, CThostFtdcRspInfoField *error,
    int req_id, bool last) {
  static CThostFtdcCFMMCTradingAccountKeyField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_qry_cfmmctrading_account_key"),
              enif_make_tuple(
                  env, 6,
                  enif_make_atom(env,
                                 "cthost_ftdc_cfmmctrading_account_key_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->ParticipantID),
                  ErlNifMakeGbkBinary(env, data->AccountID),
                  enif_make_int(env, data->KeyID),
                  ErlNifMakeGbkBinary(env, data->CurrentKey)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQryEWarrantOffset(CThostFtdcEWarrantOffsetField *data,
                                   CThostFtdcRspInfoField *error, int req_id,
                                   bool last) {
  static CThostFtdcEWarrantOffsetField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_qry_ewarrant_offset"),
              enif_make_tuple(
                  env, 9,
                  enif_make_atom(env, "cthost_ftdc_ewarrant_offset_field"),
                  ErlNifMakeGbkBinary(env, data->TradingDay),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  ErlNifMakeGbkBinary(env, data->ExchangeID),
                  ErlNifMakeGbkBinary(env, data->InstrumentID),
                  ErlNifMakeGbkBinary(env, data->Direction),
                  ErlNifMakeGbkBinary(env, data->HedgeFlag),
                  enif_make_int(env, data->Volume)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQryInvestorProductGroupMargin(
    CThostFtdcInvestorProductGroupMarginField *data,
    CThostFtdcRspInfoField *error, int req_id, bool last) {
  static CThostFtdcInvestorProductGroupMarginField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env,
              enif_make_atom(env, "on_rsp_qry_investor_product_group_margin"),
              enif_make_tuple(
                  env, 28,
                  enif_make_atom(
                      env, "cthost_ftdc_investor_product_group_margin_field"),
                  ErlNifMakeGbkBinary(env, data->ProductGroupID),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  ErlNifMakeGbkBinary(env, data->TradingDay),
                  enif_make_int(env, data->SettlementID),
                  enif_make_double(env, data->FrozenMargin),
                  enif_make_double(env, data->LongFrozenMargin),
                  enif_make_double(env, data->ShortFrozenMargin),
                  enif_make_double(env, data->UseMargin),
                  enif_make_double(env, data->LongUseMargin),
                  enif_make_double(env, data->ShortUseMargin),
                  enif_make_double(env, data->ExchMargin),
                  enif_make_double(env, data->LongExchMargin),
                  enif_make_double(env, data->ShortExchMargin),
                  enif_make_double(env, data->CloseProfit),
                  enif_make_double(env, data->FrozenCommission),
                  enif_make_double(env, data->Commission),
                  enif_make_double(env, data->FrozenCash),
                  enif_make_double(env, data->CashIn),
                  enif_make_double(env, data->PositionProfit),
                  enif_make_double(env, data->OffsetAmount),
                  enif_make_double(env, data->LongOffsetAmount),
                  enif_make_double(env, data->ShortOffsetAmount),
                  enif_make_double(env, data->ExchOffsetAmount),
                  enif_make_double(env, data->LongExchOffsetAmount),
                  enif_make_double(env, data->ShortExchOffsetAmount),
                  ErlNifMakeGbkBinary(env, data->HedgeFlag)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQryExchangeMarginRate(CThostFtdcExchangeMarginRateField *data,
                                       CThostFtdcRspInfoField *error,
                                       int req_id, bool last) {
  static CThostFtdcExchangeMarginRateField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_qry_exchange_margin_rate"),
              enif_make_tuple(
                  env, 8,
                  enif_make_atom(env, "cthost_ftdc_exchange_margin_rate_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InstrumentID),
                  ErlNifMakeGbkBinary(env, data->HedgeFlag),
                  enif_make_double(env, data->LongMarginRatioByMoney),
                  enif_make_double(env, data->LongMarginRatioByVolume),
                  enif_make_double(env, data->ShortMarginRatioByMoney),
                  enif_make_double(env, data->ShortMarginRatioByVolume)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQryExchangeMarginRateAdjust(
    CThostFtdcExchangeMarginRateAdjustField *data,
    CThostFtdcRspInfoField *error, int req_id, bool last) {
  static CThostFtdcExchangeMarginRateAdjustField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env,
              enif_make_atom(env, "on_rsp_qry_exchange_margin_rate_adjust"),
              enif_make_tuple(
                  env, 16,
                  enif_make_atom(
                      env, "cthost_ftdc_exchange_margin_rate_adjust_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InstrumentID),
                  ErlNifMakeGbkBinary(env, data->HedgeFlag),
                  enif_make_double(env, data->LongMarginRatioByMoney),
                  enif_make_double(env, data->LongMarginRatioByVolume),
                  enif_make_double(env, data->ShortMarginRatioByMoney),
                  enif_make_double(env, data->ShortMarginRatioByVolume),
                  enif_make_double(env, data->ExchLongMarginRatioByMoney),
                  enif_make_double(env, data->ExchLongMarginRatioByVolume),
                  enif_make_double(env, data->ExchShortMarginRatioByMoney),
                  enif_make_double(env, data->ExchShortMarginRatioByVolume),
                  enif_make_double(env, data->NoLongMarginRatioByMoney),
                  enif_make_double(env, data->NoLongMarginRatioByVolume),
                  enif_make_double(env, data->NoShortMarginRatioByMoney),
                  enif_make_double(env, data->NoShortMarginRatioByVolume)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQryExchangeRate(CThostFtdcExchangeRateField *data,
                                 CThostFtdcRspInfoField *error, int req_id,
                                 bool last) {
  static CThostFtdcExchangeRateField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_qry_exchange_rate"),
              enif_make_tuple(
                  env, 6,
                  enif_make_atom(env, "cthost_ftdc_exchange_rate_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->FromCurrencyID),
                  enif_make_double(env, data->FromCurrencyUnit),
                  ErlNifMakeGbkBinary(env, data->ToCurrencyID),
                  enif_make_double(env, data->ExchangeRate)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQrySecAgentACIDMap(CThostFtdcSecAgentACIDMapField *data,
                                    CThostFtdcRspInfoField *error, int req_id,
                                    bool last) {
  static CThostFtdcSecAgentACIDMapField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_qry_sec_agent_acidmap"),
              enif_make_tuple(
                  env, 6,
                  enif_make_atom(env, "cthost_ftdc_sec_agent_acidmap_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  ErlNifMakeGbkBinary(env, data->AccountID),
                  ErlNifMakeGbkBinary(env, data->CurrencyID),
                  ErlNifMakeGbkBinary(env, data->BrokerSecAgentID)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQryProductExchRate(CThostFtdcProductExchRateField *data,
                                    CThostFtdcRspInfoField *error, int req_id,
                                    bool last) {
  static CThostFtdcProductExchRateField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_qry_product_exch_rate"),
              enif_make_tuple(
                  env, 4,
                  enif_make_atom(env, "cthost_ftdc_product_exch_rate_field"),
                  ErlNifMakeGbkBinary(env, data->ProductID),
                  ErlNifMakeGbkBinary(env, data->QuoteCurrencyID),
                  enif_make_double(env, data->ExchangeRate)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQryProductGroup(CThostFtdcProductGroupField *data,
                                 CThostFtdcRspInfoField *error, int req_id,
                                 bool last) {
  static CThostFtdcProductGroupField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_qry_product_group"),
              enif_make_tuple(
                  env, 4,
                  enif_make_atom(env, "cthost_ftdc_product_group_field"),
                  ErlNifMakeGbkBinary(env, data->ProductID),
                  ErlNifMakeGbkBinary(env, data->ExchangeID),
                  ErlNifMakeGbkBinary(env, data->ProductGroupID)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQryMMInstrumentCommissionRate(
    CThostFtdcMMInstrumentCommissionRateField *data,
    CThostFtdcRspInfoField *error, int req_id, bool last) {
  static CThostFtdcMMInstrumentCommissionRateField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env,
              enif_make_atom(env, "on_rsp_qry_mminstrument_commission_rate"),
              enif_make_tuple(
                  env, 12,
                  enif_make_atom(
                      env, "cthost_ftdc_mminstrument_commission_rate_field"),
                  ErlNifMakeGbkBinary(env, data->InstrumentID),
                  ErlNifMakeGbkBinary(env, data->InvestorRange),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  enif_make_double(env, data->OpenRatioByMoney),
                  enif_make_double(env, data->OpenRatioByVolume),
                  enif_make_double(env, data->CloseRatioByMoney),
                  enif_make_double(env, data->CloseRatioByVolume),
                  enif_make_double(env, data->CloseTodayRatioByMoney),
                  enif_make_double(env, data->CloseTodayRatioByVolume),
                  ErlNifMakeGbkBinary(env, data->ExchangeID)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQryMMOptionInstrCommRate(
    CThostFtdcMMOptionInstrCommRateField *data, CThostFtdcRspInfoField *error,
    int req_id, bool last) {
  static CThostFtdcMMOptionInstrCommRateField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_qry_mmoption_instr_comm_rate"),
              enif_make_tuple(
                  env, 14,
                  enif_make_atom(env,
                                 "cthost_ftdc_mmoption_instr_comm_rate_field"),
                  ErlNifMakeGbkBinary(env, data->InstrumentID),
                  ErlNifMakeGbkBinary(env, data->InvestorRange),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  enif_make_double(env, data->OpenRatioByMoney),
                  enif_make_double(env, data->OpenRatioByVolume),
                  enif_make_double(env, data->CloseRatioByMoney),
                  enif_make_double(env, data->CloseRatioByVolume),
                  enif_make_double(env, data->CloseTodayRatioByMoney),
                  enif_make_double(env, data->CloseTodayRatioByVolume),
                  enif_make_double(env, data->StrikeRatioByMoney),
                  enif_make_double(env, data->StrikeRatioByVolume),
                  ErlNifMakeGbkBinary(env, data->ExchangeID)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQryInstrumentOrderCommRate(
    CThostFtdcInstrumentOrderCommRateField *data, CThostFtdcRspInfoField *error,
    int req_id, bool last) {
  static CThostFtdcInstrumentOrderCommRateField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_qry_instrument_order_comm_rate"),
              enif_make_tuple(
                  env, 9,
                  enif_make_atom(
                      env, "cthost_ftdc_instrument_order_comm_rate_field"),
                  ErlNifMakeGbkBinary(env, data->InstrumentID),
                  ErlNifMakeGbkBinary(env, data->InvestorRange),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  ErlNifMakeGbkBinary(env, data->ExchangeID),
                  ErlNifMakeGbkBinary(env, data->HedgeFlag),
                  enif_make_double(env, data->OrderCommByVolume),
                  enif_make_double(env, data->OrderActionCommByVolume)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQryOptionInstrTradeCost(
    CThostFtdcOptionInstrTradeCostField *data, CThostFtdcRspInfoField *error,
    int req_id, bool last) {
  static CThostFtdcOptionInstrTradeCostField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_qry_option_instr_trade_cost"),
              enif_make_tuple(
                  env, 11,
                  enif_make_atom(env,
                                 "cthost_ftdc_option_instr_trade_cost_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  ErlNifMakeGbkBinary(env, data->InstrumentID),
                  ErlNifMakeGbkBinary(env, data->HedgeFlag),
                  enif_make_double(env, data->FixedMargin),
                  enif_make_double(env, data->MiniMargin),
                  enif_make_double(env, data->Royalty),
                  enif_make_double(env, data->ExchFixedMargin),
                  enif_make_double(env, data->ExchMiniMargin),
                  ErlNifMakeGbkBinary(env, data->ExchangeID)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQryOptionInstrCommRate(
    CThostFtdcOptionInstrCommRateField *data, CThostFtdcRspInfoField *error,
    int req_id, bool last) {
  static CThostFtdcOptionInstrCommRateField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_qry_option_instr_comm_rate"),
              enif_make_tuple(
                  env, 14,
                  enif_make_atom(env,
                                 "cthost_ftdc_option_instr_comm_rate_field"),
                  ErlNifMakeGbkBinary(env, data->InstrumentID),
                  ErlNifMakeGbkBinary(env, data->InvestorRange),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  enif_make_double(env, data->OpenRatioByMoney),
                  enif_make_double(env, data->OpenRatioByVolume),
                  enif_make_double(env, data->CloseRatioByMoney),
                  enif_make_double(env, data->CloseRatioByVolume),
                  enif_make_double(env, data->CloseTodayRatioByMoney),
                  enif_make_double(env, data->CloseTodayRatioByVolume),
                  enif_make_double(env, data->StrikeRatioByMoney),
                  enif_make_double(env, data->StrikeRatioByVolume),
                  ErlNifMakeGbkBinary(env, data->ExchangeID)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQryExecOrder(CThostFtdcExecOrderField *data,
                              CThostFtdcRspInfoField *error, int req_id,
                              bool last) {
  static CThostFtdcExecOrderField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_qry_exec_order"),
              enif_make_tuple(
                  env, 45, enif_make_atom(env, "cthost_ftdc_exec_order_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  ErlNifMakeGbkBinary(env, data->InstrumentID),
                  ErlNifMakeGbkBinary(env, data->ExecOrderRef),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  enif_make_int(env, data->Volume),
                  enif_make_int(env, data->RequestID),
                  ErlNifMakeGbkBinary(env, data->BusinessUnit),
                  ErlNifMakeGbkBinary(env, data->OffsetFlag),
                  ErlNifMakeGbkBinary(env, data->HedgeFlag),
                  ErlNifMakeGbkBinary(env, data->ActionType),
                  ErlNifMakeGbkBinary(env, data->PosiDirection),
                  ErlNifMakeGbkBinary(env, data->ReservePositionFlag),
                  ErlNifMakeGbkBinary(env, data->CloseFlag),
                  ErlNifMakeGbkBinary(env, data->ExecOrderLocalID),
                  ErlNifMakeGbkBinary(env, data->ExchangeID),
                  ErlNifMakeGbkBinary(env, data->ParticipantID),
                  ErlNifMakeGbkBinary(env, data->ClientID),
                  ErlNifMakeGbkBinary(env, data->ExchangeInstID),
                  ErlNifMakeGbkBinary(env, data->TraderID),
                  enif_make_int(env, data->InstallID),
                  ErlNifMakeGbkBinary(env, data->OrderSubmitStatus),
                  enif_make_int(env, data->NotifySequence),
                  ErlNifMakeGbkBinary(env, data->TradingDay),
                  enif_make_int(env, data->SettlementID),
                  ErlNifMakeGbkBinary(env, data->ExecOrderSysID),
                  ErlNifMakeGbkBinary(env, data->InsertDate),
                  ErlNifMakeGbkBinary(env, data->InsertTime),
                  ErlNifMakeGbkBinary(env, data->CancelTime),
                  ErlNifMakeGbkBinary(env, data->ExecResult),
                  ErlNifMakeGbkBinary(env, data->ClearingPartID),
                  enif_make_int(env, data->SequenceNo),
                  enif_make_int(env, data->FrontID),
                  enif_make_int(env, data->SessionID),
                  ErlNifMakeGbkBinary(env, data->UserProductInfo),
                  ErlNifMakeGbkBinary(env, data->StatusMsg),
                  ErlNifMakeGbkBinary(env, data->ActiveUserID),
                  enif_make_int(env, data->BrokerExecOrderSeq),
                  ErlNifMakeGbkBinary(env, data->BranchID),
                  ErlNifMakeGbkBinary(env, data->InvestUnitID),
                  ErlNifMakeGbkBinary(env, data->AccountID),
                  ErlNifMakeGbkBinary(env, data->CurrencyID),
                  ErlNifMakeGbkBinary(env, data->IPAddress),
                  ErlNifMakeGbkBinary(env, data->MacAddress)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQryForQuote(CThostFtdcForQuoteField *data,
                             CThostFtdcRspInfoField *error, int req_id,
                             bool last) {
  static CThostFtdcForQuoteField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_qry_for_quote"),
              enif_make_tuple(
                  env, 25, enif_make_atom(env, "cthost_ftdc_for_quote_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  ErlNifMakeGbkBinary(env, data->InstrumentID),
                  ErlNifMakeGbkBinary(env, data->ForQuoteRef),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  ErlNifMakeGbkBinary(env, data->ForQuoteLocalID),
                  ErlNifMakeGbkBinary(env, data->ExchangeID),
                  ErlNifMakeGbkBinary(env, data->ParticipantID),
                  ErlNifMakeGbkBinary(env, data->ClientID),
                  ErlNifMakeGbkBinary(env, data->ExchangeInstID),
                  ErlNifMakeGbkBinary(env, data->TraderID),
                  enif_make_int(env, data->InstallID),
                  ErlNifMakeGbkBinary(env, data->InsertDate),
                  ErlNifMakeGbkBinary(env, data->InsertTime),
                  ErlNifMakeGbkBinary(env, data->ForQuoteStatus),
                  enif_make_int(env, data->FrontID),
                  enif_make_int(env, data->SessionID),
                  ErlNifMakeGbkBinary(env, data->StatusMsg),
                  ErlNifMakeGbkBinary(env, data->ActiveUserID),
                  enif_make_int(env, data->BrokerForQutoSeq),
                  ErlNifMakeGbkBinary(env, data->InvestUnitID),
                  ErlNifMakeGbkBinary(env, data->IPAddress),
                  ErlNifMakeGbkBinary(env, data->MacAddress),
                  ErlNifMakeGbkBinary(env, data->BranchID)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQryQuote(CThostFtdcQuoteField *data,
                          CThostFtdcRspInfoField *error, int req_id,
                          bool last) {
  static CThostFtdcQuoteField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_qry_quote"),
              enif_make_tuple(env, 51,
                              enif_make_atom(env, "cthost_ftdc_quote_field"),
                              ErlNifMakeGbkBinary(env, data->BrokerID),
                              ErlNifMakeGbkBinary(env, data->InvestorID),
                              ErlNifMakeGbkBinary(env, data->InstrumentID),
                              ErlNifMakeGbkBinary(env, data->QuoteRef),
                              ErlNifMakeGbkBinary(env, data->UserID),
                              enif_make_double(env, data->AskPrice),
                              enif_make_double(env, data->BidPrice),
                              enif_make_int(env, data->AskVolume),
                              enif_make_int(env, data->BidVolume),
                              enif_make_int(env, data->RequestID),
                              ErlNifMakeGbkBinary(env, data->BusinessUnit),
                              ErlNifMakeGbkBinary(env, data->AskOffsetFlag),
                              ErlNifMakeGbkBinary(env, data->BidOffsetFlag),
                              ErlNifMakeGbkBinary(env, data->AskHedgeFlag),
                              ErlNifMakeGbkBinary(env, data->BidHedgeFlag),
                              ErlNifMakeGbkBinary(env, data->QuoteLocalID),
                              ErlNifMakeGbkBinary(env, data->ExchangeID),
                              ErlNifMakeGbkBinary(env, data->ParticipantID),
                              ErlNifMakeGbkBinary(env, data->ClientID),
                              ErlNifMakeGbkBinary(env, data->ExchangeInstID),
                              ErlNifMakeGbkBinary(env, data->TraderID),
                              enif_make_int(env, data->InstallID),
                              enif_make_int(env, data->NotifySequence),
                              ErlNifMakeGbkBinary(env, data->OrderSubmitStatus),
                              ErlNifMakeGbkBinary(env, data->TradingDay),
                              enif_make_int(env, data->SettlementID),
                              ErlNifMakeGbkBinary(env, data->QuoteSysID),
                              ErlNifMakeGbkBinary(env, data->InsertDate),
                              ErlNifMakeGbkBinary(env, data->InsertTime),
                              ErlNifMakeGbkBinary(env, data->CancelTime),
                              ErlNifMakeGbkBinary(env, data->QuoteStatus),
                              ErlNifMakeGbkBinary(env, data->ClearingPartID),
                              enif_make_int(env, data->SequenceNo),
                              ErlNifMakeGbkBinary(env, data->AskOrderSysID),
                              ErlNifMakeGbkBinary(env, data->BidOrderSysID),
                              enif_make_int(env, data->FrontID),
                              enif_make_int(env, data->SessionID),
                              ErlNifMakeGbkBinary(env, data->UserProductInfo),
                              ErlNifMakeGbkBinary(env, data->StatusMsg),
                              ErlNifMakeGbkBinary(env, data->ActiveUserID),
                              enif_make_int(env, data->BrokerQuoteSeq),
                              ErlNifMakeGbkBinary(env, data->AskOrderRef),
                              ErlNifMakeGbkBinary(env, data->BidOrderRef),
                              ErlNifMakeGbkBinary(env, data->ForQuoteSysID),
                              ErlNifMakeGbkBinary(env, data->BranchID),
                              ErlNifMakeGbkBinary(env, data->InvestUnitID),
                              ErlNifMakeGbkBinary(env, data->AccountID),
                              ErlNifMakeGbkBinary(env, data->CurrencyID),
                              ErlNifMakeGbkBinary(env, data->IPAddress),
                              ErlNifMakeGbkBinary(env, data->MacAddress)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQryLock(CThostFtdcLockField *data,
                         CThostFtdcRspInfoField *error, int req_id, bool last) {
  static CThostFtdcLockField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_qry_lock"),
              enif_make_tuple(env, 37,
                              enif_make_atom(env, "cthost_ftdc_lock_field"),
                              ErlNifMakeGbkBinary(env, data->BrokerID),
                              ErlNifMakeGbkBinary(env, data->InvestorID),
                              ErlNifMakeGbkBinary(env, data->InstrumentID),
                              ErlNifMakeGbkBinary(env, data->LockRef),
                              ErlNifMakeGbkBinary(env, data->UserID),
                              enif_make_int(env, data->Volume),
                              enif_make_int(env, data->RequestID),
                              ErlNifMakeGbkBinary(env, data->BusinessUnit),
                              ErlNifMakeGbkBinary(env, data->LockType),
                              ErlNifMakeGbkBinary(env, data->LockLocalID),
                              ErlNifMakeGbkBinary(env, data->ExchangeID),
                              ErlNifMakeGbkBinary(env, data->ParticipantID),
                              ErlNifMakeGbkBinary(env, data->ClientID),
                              ErlNifMakeGbkBinary(env, data->ExchangeInstID),
                              ErlNifMakeGbkBinary(env, data->TraderID),
                              enif_make_int(env, data->InstallID),
                              ErlNifMakeGbkBinary(env, data->OrderSubmitStatus),
                              enif_make_int(env, data->NotifySequence),
                              ErlNifMakeGbkBinary(env, data->TradingDay),
                              enif_make_int(env, data->SettlementID),
                              ErlNifMakeGbkBinary(env, data->LockSysID),
                              ErlNifMakeGbkBinary(env, data->InsertDate),
                              ErlNifMakeGbkBinary(env, data->InsertTime),
                              ErlNifMakeGbkBinary(env, data->CancelTime),
                              ErlNifMakeGbkBinary(env, data->LockStatus),
                              ErlNifMakeGbkBinary(env, data->ClearingPartID),
                              enif_make_int(env, data->SequenceNo),
                              enif_make_int(env, data->FrontID),
                              enif_make_int(env, data->SessionID),
                              ErlNifMakeGbkBinary(env, data->UserProductInfo),
                              ErlNifMakeGbkBinary(env, data->StatusMsg),
                              ErlNifMakeGbkBinary(env, data->ActiveUserID),
                              enif_make_int(env, data->BrokerLockSeq),
                              ErlNifMakeGbkBinary(env, data->BranchID),
                              ErlNifMakeGbkBinary(env, data->IPAddress),
                              ErlNifMakeGbkBinary(env, data->MacAddress)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQryLockPosition(CThostFtdcLockPositionField *data,
                                 CThostFtdcRspInfoField *error, int req_id,
                                 bool last) {
  static CThostFtdcLockPositionField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_qry_lock_position"),
              enif_make_tuple(
                  env, 7,
                  enif_make_atom(env, "cthost_ftdc_lock_position_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  ErlNifMakeGbkBinary(env, data->InstrumentID),
                  ErlNifMakeGbkBinary(env, data->ExchangeID),
                  enif_make_int(env, data->Volume),
                  enif_make_int(env, data->FrozenVolume)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQryETFOptionInstrCommRate(
    CThostFtdcETFOptionInstrCommRateField *data, CThostFtdcRspInfoField *error,
    int req_id, bool last) {
  static CThostFtdcETFOptionInstrCommRateField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_qry_etfoption_instr_comm_rate"),
              enif_make_tuple(
                  env, 16,
                  enif_make_atom(env,
                                 "cthost_ftdc_etfoption_instr_comm_rate_field"),
                  ErlNifMakeGbkBinary(env, data->InstrumentID),
                  ErlNifMakeGbkBinary(env, data->InvestorRange),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  enif_make_double(env, data->OpenRatioByMoney),
                  enif_make_double(env, data->OpenRatioByVolume),
                  enif_make_double(env, data->CloseRatioByMoney),
                  enif_make_double(env, data->CloseRatioByVolume),
                  enif_make_double(env, data->CloseTodayRatioByMoney),
                  enif_make_double(env, data->CloseTodayRatioByVolume),
                  enif_make_double(env, data->StrikeRatioByMoney),
                  enif_make_double(env, data->StrikeRatioByVolume),
                  ErlNifMakeGbkBinary(env, data->ExchangeID),
                  ErlNifMakeGbkBinary(env, data->HedgeFlag),
                  ErlNifMakeGbkBinary(env, data->PosiDirection)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQryInvestorLevel(CThostFtdcInvestorLevelField *data,
                                  CThostFtdcRspInfoField *error, int req_id,
                                  bool last) {
  static CThostFtdcInvestorLevelField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_qry_investor_level"),
              enif_make_tuple(
                  env, 5,
                  enif_make_atom(env, "cthost_ftdc_investor_level_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  ErlNifMakeGbkBinary(env, data->ExchangeID),
                  ErlNifMakeGbkBinary(env, data->LevelType)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQryExecFreeze(CThostFtdcExecFreezeField *data,
                               CThostFtdcRspInfoField *error, int req_id,
                               bool last) {
  static CThostFtdcExecFreezeField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_qry_exec_freeze"),
              enif_make_tuple(
                  env, 9, enif_make_atom(env, "cthost_ftdc_exec_freeze_field"),
                  ErlNifMakeGbkBinary(env, data->InstrumentID),
                  ErlNifMakeGbkBinary(env, data->ExchangeID),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  ErlNifMakeGbkBinary(env, data->PosiDirection),
                  ErlNifMakeGbkBinary(env, data->OptionsType),
                  enif_make_int(env, data->Volume),
                  enif_make_double(env, data->FrozenAmount)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQryCombInstrumentGuard(
    CThostFtdcCombInstrumentGuardField *data, CThostFtdcRspInfoField *error,
    int req_id, bool last) {
  static CThostFtdcCombInstrumentGuardField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_qry_comb_instrument_guard"),
              enif_make_tuple(
                  env, 4,
                  enif_make_atom(env,
                                 "cthost_ftdc_comb_instrument_guard_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InstrumentID),
                  enif_make_double(env, data->GuarantRatio)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQryCombAction(CThostFtdcCombActionField *data,
                               CThostFtdcRspInfoField *error, int req_id,
                               bool last) {
  static CThostFtdcCombActionField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_qry_comb_action"),
              enif_make_tuple(
                  env, 30, enif_make_atom(env, "cthost_ftdc_comb_action_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  ErlNifMakeGbkBinary(env, data->InstrumentID),
                  ErlNifMakeGbkBinary(env, data->CombActionRef),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  ErlNifMakeGbkBinary(env, data->Direction),
                  enif_make_int(env, data->Volume),
                  ErlNifMakeGbkBinary(env, data->CombDirection),
                  ErlNifMakeGbkBinary(env, data->HedgeFlag),
                  ErlNifMakeGbkBinary(env, data->ActionLocalID),
                  ErlNifMakeGbkBinary(env, data->ExchangeID),
                  ErlNifMakeGbkBinary(env, data->ParticipantID),
                  ErlNifMakeGbkBinary(env, data->ClientID),
                  ErlNifMakeGbkBinary(env, data->ExchangeInstID),
                  ErlNifMakeGbkBinary(env, data->TraderID),
                  enif_make_int(env, data->InstallID),
                  ErlNifMakeGbkBinary(env, data->ActionStatus),
                  enif_make_int(env, data->NotifySequence),
                  ErlNifMakeGbkBinary(env, data->TradingDay),
                  enif_make_int(env, data->SettlementID),
                  enif_make_int(env, data->SequenceNo),
                  enif_make_int(env, data->FrontID),
                  enif_make_int(env, data->SessionID),
                  ErlNifMakeGbkBinary(env, data->UserProductInfo),
                  ErlNifMakeGbkBinary(env, data->StatusMsg),
                  ErlNifMakeGbkBinary(env, data->IPAddress),
                  ErlNifMakeGbkBinary(env, data->MacAddress),
                  ErlNifMakeGbkBinary(env, data->ComTradeID),
                  ErlNifMakeGbkBinary(env, data->BranchID)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQryTransferSerial(CThostFtdcTransferSerialField *data,
                                   CThostFtdcRspInfoField *error, int req_id,
                                   bool last) {
  static CThostFtdcTransferSerialField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_qry_transfer_serial"),
              enif_make_tuple(
                  env, 29,
                  enif_make_atom(env, "cthost_ftdc_transfer_serial_field"),
                  enif_make_int(env, data->PlateSerial),
                  ErlNifMakeGbkBinary(env, data->TradeDate),
                  ErlNifMakeGbkBinary(env, data->TradingDay),
                  ErlNifMakeGbkBinary(env, data->TradeTime),
                  ErlNifMakeGbkBinary(env, data->TradeCode),
                  enif_make_int(env, data->SessionID),
                  ErlNifMakeGbkBinary(env, data->BankID),
                  ErlNifMakeGbkBinary(env, data->BankBranchID),
                  ErlNifMakeGbkBinary(env, data->BankAccType),
                  ErlNifMakeGbkBinary(env, data->BankAccount),
                  ErlNifMakeGbkBinary(env, data->BankSerial),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->BrokerBranchID),
                  ErlNifMakeGbkBinary(env, data->FutureAccType),
                  ErlNifMakeGbkBinary(env, data->AccountID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  enif_make_int(env, data->FutureSerial),
                  ErlNifMakeGbkBinary(env, data->IdCardType),
                  ErlNifMakeGbkBinary(env, data->IdentifiedCardNo),
                  ErlNifMakeGbkBinary(env, data->CurrencyID),
                  enif_make_double(env, data->TradeAmount),
                  enif_make_double(env, data->CustFee),
                  enif_make_double(env, data->BrokerFee),
                  ErlNifMakeGbkBinary(env, data->AvailabilityFlag),
                  ErlNifMakeGbkBinary(env, data->OperatorCode),
                  ErlNifMakeGbkBinary(env, data->BankNewAccount),
                  enif_make_int(env, data->ErrorID),
                  ErlNifMakeGbkBinary(env, data->ErrorMsg)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQryAccountregister(CThostFtdcAccountregisterField *data,
                                    CThostFtdcRspInfoField *error, int req_id,
                                    bool last) {
  static CThostFtdcAccountregisterField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_qry_accountregister"),
              enif_make_tuple(
                  env, 18,
                  enif_make_atom(env, "cthost_ftdc_accountregister_field"),
                  ErlNifMakeGbkBinary(env, data->TradeDay),
                  ErlNifMakeGbkBinary(env, data->BankID),
                  ErlNifMakeGbkBinary(env, data->BankBranchID),
                  ErlNifMakeGbkBinary(env, data->BankAccount),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->BrokerBranchID),
                  ErlNifMakeGbkBinary(env, data->AccountID),
                  ErlNifMakeGbkBinary(env, data->IdCardType),
                  ErlNifMakeGbkBinary(env, data->IdentifiedCardNo),
                  ErlNifMakeGbkBinary(env, data->CustomerName),
                  ErlNifMakeGbkBinary(env, data->CurrencyID),
                  ErlNifMakeGbkBinary(env, data->OpenOrDestroy),
                  ErlNifMakeGbkBinary(env, data->RegDate),
                  ErlNifMakeGbkBinary(env, data->OutDate),
                  enif_make_int(env, data->TID),
                  ErlNifMakeGbkBinary(env, data->CustType),
                  ErlNifMakeGbkBinary(env, data->BankAccType)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspError(CThostFtdcRspInfoField *error, int req_id, bool last) {
  static CThostFtdcRspInfoField empty_error = {};

  if (!error) {
    error = &empty_error;
  }

  ErlNifEnv *env = enif_alloc_env();
  enif_send(
      NULL, &this->pid_, env,
      enif_make_tuple2(
          env, enif_make_atom(env, "ctp_td"),
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

void CtpTd::OnRtnOrder(CThostFtdcOrderField *data) {
  static CThostFtdcOrderField empty_data = {};

  if (!data) {
    data = &empty_data;
  }

  ErlNifEnv *env = enif_alloc_env();
  enif_send(NULL, &this->pid_, env,
            enif_make_tuple2(
                env, enif_make_atom(env, "ctp_td"),
                enif_make_tuple2(
                    env, enif_make_atom(env, "on_rtn_order"),
                    enif_make_tuple(
                        env, 64, enif_make_atom(env, "cthost_ftdc_order_field"),
                        ErlNifMakeGbkBinary(env, data->BrokerID),
                        ErlNifMakeGbkBinary(env, data->InvestorID),
                        ErlNifMakeGbkBinary(env, data->InstrumentID),
                        ErlNifMakeGbkBinary(env, data->OrderRef),
                        ErlNifMakeGbkBinary(env, data->UserID),
                        ErlNifMakeGbkBinary(env, data->OrderPriceType),
                        ErlNifMakeGbkBinary(env, data->Direction),
                        ErlNifMakeGbkBinary(env, data->CombOffsetFlag),
                        ErlNifMakeGbkBinary(env, data->CombHedgeFlag),
                        enif_make_double(env, data->LimitPrice),
                        enif_make_int(env, data->VolumeTotalOriginal),
                        ErlNifMakeGbkBinary(env, data->TimeCondition),
                        ErlNifMakeGbkBinary(env, data->GTDDate),
                        ErlNifMakeGbkBinary(env, data->VolumeCondition),
                        enif_make_int(env, data->MinVolume),
                        ErlNifMakeGbkBinary(env, data->ContingentCondition),
                        enif_make_double(env, data->StopPrice),
                        ErlNifMakeGbkBinary(env, data->ForceCloseReason),
                        enif_make_int(env, data->IsAutoSuspend),
                        ErlNifMakeGbkBinary(env, data->BusinessUnit),
                        enif_make_int(env, data->RequestID),
                        ErlNifMakeGbkBinary(env, data->OrderLocalID),
                        ErlNifMakeGbkBinary(env, data->ExchangeID),
                        ErlNifMakeGbkBinary(env, data->ParticipantID),
                        ErlNifMakeGbkBinary(env, data->ClientID),
                        ErlNifMakeGbkBinary(env, data->ExchangeInstID),
                        ErlNifMakeGbkBinary(env, data->TraderID),
                        enif_make_int(env, data->InstallID),
                        ErlNifMakeGbkBinary(env, data->OrderSubmitStatus),
                        enif_make_int(env, data->NotifySequence),
                        ErlNifMakeGbkBinary(env, data->TradingDay),
                        enif_make_int(env, data->SettlementID),
                        ErlNifMakeGbkBinary(env, data->OrderSysID),
                        ErlNifMakeGbkBinary(env, data->OrderSource),
                        ErlNifMakeGbkBinary(env, data->OrderStatus),
                        ErlNifMakeGbkBinary(env, data->OrderType),
                        enif_make_int(env, data->VolumeTraded),
                        enif_make_int(env, data->VolumeTotal),
                        ErlNifMakeGbkBinary(env, data->InsertDate),
                        ErlNifMakeGbkBinary(env, data->InsertTime),
                        ErlNifMakeGbkBinary(env, data->ActiveTime),
                        ErlNifMakeGbkBinary(env, data->SuspendTime),
                        ErlNifMakeGbkBinary(env, data->UpdateTime),
                        ErlNifMakeGbkBinary(env, data->CancelTime),
                        ErlNifMakeGbkBinary(env, data->ActiveTraderID),
                        ErlNifMakeGbkBinary(env, data->ClearingPartID),
                        enif_make_int(env, data->SequenceNo),
                        enif_make_int(env, data->FrontID),
                        enif_make_int(env, data->SessionID),
                        ErlNifMakeGbkBinary(env, data->UserProductInfo),
                        ErlNifMakeGbkBinary(env, data->StatusMsg),
                        enif_make_int(env, data->UserForceClose),
                        ErlNifMakeGbkBinary(env, data->ActiveUserID),
                        enif_make_int(env, data->BrokerOrderSeq),
                        ErlNifMakeGbkBinary(env, data->RelativeOrderSysID),
                        enif_make_int(env, data->ZCETotalTradedVolume),
                        enif_make_int(env, data->IsSwapOrder),
                        ErlNifMakeGbkBinary(env, data->BranchID),
                        ErlNifMakeGbkBinary(env, data->InvestUnitID),
                        ErlNifMakeGbkBinary(env, data->AccountID),
                        ErlNifMakeGbkBinary(env, data->CurrencyID),
                        ErlNifMakeGbkBinary(env, data->IPAddress),
                        ErlNifMakeGbkBinary(env, data->MacAddress)))));
  enif_free_env(env);
}

void CtpTd::OnRtnTrade(CThostFtdcTradeField *data) {
  static CThostFtdcTradeField empty_data = {};

  if (!data) {
    data = &empty_data;
  }

  ErlNifEnv *env = enif_alloc_env();
  enif_send(NULL, &this->pid_, env,
            enif_make_tuple2(
                env, enif_make_atom(env, "ctp_td"),
                enif_make_tuple2(
                    env, enif_make_atom(env, "on_rtn_trade"),
                    enif_make_tuple(
                        env, 31, enif_make_atom(env, "cthost_ftdc_trade_field"),
                        ErlNifMakeGbkBinary(env, data->BrokerID),
                        ErlNifMakeGbkBinary(env, data->InvestorID),
                        ErlNifMakeGbkBinary(env, data->InstrumentID),
                        ErlNifMakeGbkBinary(env, data->OrderRef),
                        ErlNifMakeGbkBinary(env, data->UserID),
                        ErlNifMakeGbkBinary(env, data->ExchangeID),
                        ErlNifMakeGbkBinary(env, data->TradeID),
                        ErlNifMakeGbkBinary(env, data->Direction),
                        ErlNifMakeGbkBinary(env, data->OrderSysID),
                        ErlNifMakeGbkBinary(env, data->ParticipantID),
                        ErlNifMakeGbkBinary(env, data->ClientID),
                        ErlNifMakeGbkBinary(env, data->TradingRole),
                        ErlNifMakeGbkBinary(env, data->ExchangeInstID),
                        ErlNifMakeGbkBinary(env, data->OffsetFlag),
                        ErlNifMakeGbkBinary(env, data->HedgeFlag),
                        enif_make_double(env, data->Price),
                        enif_make_int(env, data->Volume),
                        ErlNifMakeGbkBinary(env, data->TradeDate),
                        ErlNifMakeGbkBinary(env, data->TradeTime),
                        ErlNifMakeGbkBinary(env, data->TradeType),
                        ErlNifMakeGbkBinary(env, data->PriceSource),
                        ErlNifMakeGbkBinary(env, data->TraderID),
                        ErlNifMakeGbkBinary(env, data->OrderLocalID),
                        ErlNifMakeGbkBinary(env, data->ClearingPartID),
                        ErlNifMakeGbkBinary(env, data->BusinessUnit),
                        enif_make_int(env, data->SequenceNo),
                        ErlNifMakeGbkBinary(env, data->TradingDay),
                        enif_make_int(env, data->SettlementID),
                        enif_make_int(env, data->BrokerOrderSeq),
                        ErlNifMakeGbkBinary(env, data->TradeSource)))));
  enif_free_env(env);
}

void CtpTd::OnErrRtnOrderInsert(CThostFtdcInputOrderField *data,
                                CThostFtdcRspInfoField *error) {
  static CThostFtdcInputOrderField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple3(
              env, enif_make_atom(env, "on_err_rtn_order_insert"),
              enif_make_tuple(
                  env, 31, enif_make_atom(env, "cthost_ftdc_input_order_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  ErlNifMakeGbkBinary(env, data->InstrumentID),
                  ErlNifMakeGbkBinary(env, data->OrderRef),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  ErlNifMakeGbkBinary(env, data->OrderPriceType),
                  ErlNifMakeGbkBinary(env, data->Direction),
                  ErlNifMakeGbkBinary(env, data->CombOffsetFlag),
                  ErlNifMakeGbkBinary(env, data->CombHedgeFlag),
                  enif_make_double(env, data->LimitPrice),
                  enif_make_int(env, data->VolumeTotalOriginal),
                  ErlNifMakeGbkBinary(env, data->TimeCondition),
                  ErlNifMakeGbkBinary(env, data->GTDDate),
                  ErlNifMakeGbkBinary(env, data->VolumeCondition),
                  enif_make_int(env, data->MinVolume),
                  ErlNifMakeGbkBinary(env, data->ContingentCondition),
                  enif_make_double(env, data->StopPrice),
                  ErlNifMakeGbkBinary(env, data->ForceCloseReason),
                  enif_make_int(env, data->IsAutoSuspend),
                  ErlNifMakeGbkBinary(env, data->BusinessUnit),
                  enif_make_int(env, data->RequestID),
                  enif_make_int(env, data->UserForceClose),
                  enif_make_int(env, data->IsSwapOrder),
                  ErlNifMakeGbkBinary(env, data->ExchangeID),
                  ErlNifMakeGbkBinary(env, data->InvestUnitID),
                  ErlNifMakeGbkBinary(env, data->AccountID),
                  ErlNifMakeGbkBinary(env, data->CurrencyID),
                  ErlNifMakeGbkBinary(env, data->ClientID),
                  ErlNifMakeGbkBinary(env, data->IPAddress),
                  ErlNifMakeGbkBinary(env, data->MacAddress)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)))));
  enif_free_env(env);
}

void CtpTd::OnErrRtnOrderAction(CThostFtdcOrderActionField *data,
                                CThostFtdcRspInfoField *error) {
  static CThostFtdcOrderActionField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple3(
              env, enif_make_atom(env, "on_err_rtn_order_action"),
              enif_make_tuple(
                  env, 30,
                  enif_make_atom(env, "cthost_ftdc_order_action_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  enif_make_int(env, data->OrderActionRef),
                  ErlNifMakeGbkBinary(env, data->OrderRef),
                  enif_make_int(env, data->RequestID),
                  enif_make_int(env, data->FrontID),
                  enif_make_int(env, data->SessionID),
                  ErlNifMakeGbkBinary(env, data->ExchangeID),
                  ErlNifMakeGbkBinary(env, data->OrderSysID),
                  ErlNifMakeGbkBinary(env, data->ActionFlag),
                  enif_make_double(env, data->LimitPrice),
                  enif_make_int(env, data->VolumeChange),
                  ErlNifMakeGbkBinary(env, data->ActionDate),
                  ErlNifMakeGbkBinary(env, data->ActionTime),
                  ErlNifMakeGbkBinary(env, data->TraderID),
                  enif_make_int(env, data->InstallID),
                  ErlNifMakeGbkBinary(env, data->OrderLocalID),
                  ErlNifMakeGbkBinary(env, data->ActionLocalID),
                  ErlNifMakeGbkBinary(env, data->ParticipantID),
                  ErlNifMakeGbkBinary(env, data->ClientID),
                  ErlNifMakeGbkBinary(env, data->BusinessUnit),
                  ErlNifMakeGbkBinary(env, data->OrderActionStatus),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  ErlNifMakeGbkBinary(env, data->StatusMsg),
                  ErlNifMakeGbkBinary(env, data->InstrumentID),
                  ErlNifMakeGbkBinary(env, data->BranchID),
                  ErlNifMakeGbkBinary(env, data->InvestUnitID),
                  ErlNifMakeGbkBinary(env, data->IPAddress),
                  ErlNifMakeGbkBinary(env, data->MacAddress)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)))));
  enif_free_env(env);
}

void CtpTd::OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *data) {
  static CThostFtdcInstrumentStatusField empty_data = {};

  if (!data) {
    data = &empty_data;
  }

  ErlNifEnv *env = enif_alloc_env();
  enif_send(
      NULL, &this->pid_, env,
      enif_make_tuple2(
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple2(
              env, enif_make_atom(env, "on_rtn_instrument_status"),
              enif_make_tuple(
                  env, 9,
                  enif_make_atom(env, "cthost_ftdc_instrument_status_field"),
                  ErlNifMakeGbkBinary(env, data->ExchangeID),
                  ErlNifMakeGbkBinary(env, data->ExchangeInstID),
                  ErlNifMakeGbkBinary(env, data->SettlementGroupID),
                  ErlNifMakeGbkBinary(env, data->InstrumentID),
                  ErlNifMakeGbkBinary(env, data->InstrumentStatus),
                  enif_make_int(env, data->TradingSegmentSN),
                  ErlNifMakeGbkBinary(env, data->EnterTime),
                  ErlNifMakeGbkBinary(env, data->EnterReason)))));
  enif_free_env(env);
}

void CtpTd::OnRtnBulletin(CThostFtdcBulletinField *data) {
  static CThostFtdcBulletinField empty_data = {};

  if (!data) {
    data = &empty_data;
  }

  ErlNifEnv *env = enif_alloc_env();
  enif_send(
      NULL, &this->pid_, env,
      enif_make_tuple2(
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple2(
              env, enif_make_atom(env, "on_rtn_bulletin"),
              enif_make_tuple(env, 13,
                              enif_make_atom(env, "cthost_ftdc_bulletin_field"),
                              ErlNifMakeGbkBinary(env, data->ExchangeID),
                              ErlNifMakeGbkBinary(env, data->TradingDay),
                              enif_make_int(env, data->BulletinID),
                              enif_make_int(env, data->SequenceNo),
                              ErlNifMakeGbkBinary(env, data->NewsType),
                              ErlNifMakeGbkBinary(env, data->NewsUrgency),
                              ErlNifMakeGbkBinary(env, data->SendTime),
                              ErlNifMakeGbkBinary(env, data->Abstract),
                              ErlNifMakeGbkBinary(env, data->ComeFrom),
                              ErlNifMakeGbkBinary(env, data->Content),
                              ErlNifMakeGbkBinary(env, data->URLLink),
                              ErlNifMakeGbkBinary(env, data->MarketID)))));
  enif_free_env(env);
}

void CtpTd::OnRtnTradingNotice(CThostFtdcTradingNoticeInfoField *data) {
  static CThostFtdcTradingNoticeInfoField empty_data = {};

  if (!data) {
    data = &empty_data;
  }

  ErlNifEnv *env = enif_alloc_env();
  enif_send(
      NULL, &this->pid_, env,
      enif_make_tuple2(
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple2(
              env, enif_make_atom(env, "on_rtn_trading_notice"),
              enif_make_tuple(
                  env, 7,
                  enif_make_atom(env, "cthost_ftdc_trading_notice_info_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  ErlNifMakeGbkBinary(env, data->SendTime),
                  ErlNifMakeGbkBinary(env, data->FieldContent),
                  enif_make_int(env, data->SequenceSeries),
                  enif_make_int(env, data->SequenceNo)))));
  enif_free_env(env);
}

void CtpTd::OnRtnErrorConditionalOrder(
    CThostFtdcErrorConditionalOrderField *data) {
  static CThostFtdcErrorConditionalOrderField empty_data = {};

  if (!data) {
    data = &empty_data;
  }

  ErlNifEnv *env = enif_alloc_env();
  enif_send(NULL, &this->pid_, env,
            enif_make_tuple2(
                env, enif_make_atom(env, "ctp_td"),
                enif_make_tuple2(
                    env, enif_make_atom(env, "on_rtn_error_conditional_order"),
                    enif_make_tuple(
                        env, 66,
                        enif_make_atom(
                            env, "cthost_ftdc_error_conditional_order_field"),
                        ErlNifMakeGbkBinary(env, data->BrokerID),
                        ErlNifMakeGbkBinary(env, data->InvestorID),
                        ErlNifMakeGbkBinary(env, data->InstrumentID),
                        ErlNifMakeGbkBinary(env, data->OrderRef),
                        ErlNifMakeGbkBinary(env, data->UserID),
                        ErlNifMakeGbkBinary(env, data->OrderPriceType),
                        ErlNifMakeGbkBinary(env, data->Direction),
                        ErlNifMakeGbkBinary(env, data->CombOffsetFlag),
                        ErlNifMakeGbkBinary(env, data->CombHedgeFlag),
                        enif_make_double(env, data->LimitPrice),
                        enif_make_int(env, data->VolumeTotalOriginal),
                        ErlNifMakeGbkBinary(env, data->TimeCondition),
                        ErlNifMakeGbkBinary(env, data->GTDDate),
                        ErlNifMakeGbkBinary(env, data->VolumeCondition),
                        enif_make_int(env, data->MinVolume),
                        ErlNifMakeGbkBinary(env, data->ContingentCondition),
                        enif_make_double(env, data->StopPrice),
                        ErlNifMakeGbkBinary(env, data->ForceCloseReason),
                        enif_make_int(env, data->IsAutoSuspend),
                        ErlNifMakeGbkBinary(env, data->BusinessUnit),
                        enif_make_int(env, data->RequestID),
                        ErlNifMakeGbkBinary(env, data->OrderLocalID),
                        ErlNifMakeGbkBinary(env, data->ExchangeID),
                        ErlNifMakeGbkBinary(env, data->ParticipantID),
                        ErlNifMakeGbkBinary(env, data->ClientID),
                        ErlNifMakeGbkBinary(env, data->ExchangeInstID),
                        ErlNifMakeGbkBinary(env, data->TraderID),
                        enif_make_int(env, data->InstallID),
                        ErlNifMakeGbkBinary(env, data->OrderSubmitStatus),
                        enif_make_int(env, data->NotifySequence),
                        ErlNifMakeGbkBinary(env, data->TradingDay),
                        enif_make_int(env, data->SettlementID),
                        ErlNifMakeGbkBinary(env, data->OrderSysID),
                        ErlNifMakeGbkBinary(env, data->OrderSource),
                        ErlNifMakeGbkBinary(env, data->OrderStatus),
                        ErlNifMakeGbkBinary(env, data->OrderType),
                        enif_make_int(env, data->VolumeTraded),
                        enif_make_int(env, data->VolumeTotal),
                        ErlNifMakeGbkBinary(env, data->InsertDate),
                        ErlNifMakeGbkBinary(env, data->InsertTime),
                        ErlNifMakeGbkBinary(env, data->ActiveTime),
                        ErlNifMakeGbkBinary(env, data->SuspendTime),
                        ErlNifMakeGbkBinary(env, data->UpdateTime),
                        ErlNifMakeGbkBinary(env, data->CancelTime),
                        ErlNifMakeGbkBinary(env, data->ActiveTraderID),
                        ErlNifMakeGbkBinary(env, data->ClearingPartID),
                        enif_make_int(env, data->SequenceNo),
                        enif_make_int(env, data->FrontID),
                        enif_make_int(env, data->SessionID),
                        ErlNifMakeGbkBinary(env, data->UserProductInfo),
                        ErlNifMakeGbkBinary(env, data->StatusMsg),
                        enif_make_int(env, data->UserForceClose),
                        ErlNifMakeGbkBinary(env, data->ActiveUserID),
                        enif_make_int(env, data->BrokerOrderSeq),
                        ErlNifMakeGbkBinary(env, data->RelativeOrderSysID),
                        enif_make_int(env, data->ZCETotalTradedVolume),
                        enif_make_int(env, data->ErrorID),
                        ErlNifMakeGbkBinary(env, data->ErrorMsg),
                        enif_make_int(env, data->IsSwapOrder),
                        ErlNifMakeGbkBinary(env, data->BranchID),
                        ErlNifMakeGbkBinary(env, data->InvestUnitID),
                        ErlNifMakeGbkBinary(env, data->AccountID),
                        ErlNifMakeGbkBinary(env, data->CurrencyID),
                        ErlNifMakeGbkBinary(env, data->IPAddress),
                        ErlNifMakeGbkBinary(env, data->MacAddress)))));
  enif_free_env(env);
}

void CtpTd::OnRtnExecOrder(CThostFtdcExecOrderField *data) {
  static CThostFtdcExecOrderField empty_data = {};

  if (!data) {
    data = &empty_data;
  }

  ErlNifEnv *env = enif_alloc_env();
  enif_send(
      NULL, &this->pid_, env,
      enif_make_tuple2(
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple2(
              env, enif_make_atom(env, "on_rtn_exec_order"),
              enif_make_tuple(
                  env, 45, enif_make_atom(env, "cthost_ftdc_exec_order_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  ErlNifMakeGbkBinary(env, data->InstrumentID),
                  ErlNifMakeGbkBinary(env, data->ExecOrderRef),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  enif_make_int(env, data->Volume),
                  enif_make_int(env, data->RequestID),
                  ErlNifMakeGbkBinary(env, data->BusinessUnit),
                  ErlNifMakeGbkBinary(env, data->OffsetFlag),
                  ErlNifMakeGbkBinary(env, data->HedgeFlag),
                  ErlNifMakeGbkBinary(env, data->ActionType),
                  ErlNifMakeGbkBinary(env, data->PosiDirection),
                  ErlNifMakeGbkBinary(env, data->ReservePositionFlag),
                  ErlNifMakeGbkBinary(env, data->CloseFlag),
                  ErlNifMakeGbkBinary(env, data->ExecOrderLocalID),
                  ErlNifMakeGbkBinary(env, data->ExchangeID),
                  ErlNifMakeGbkBinary(env, data->ParticipantID),
                  ErlNifMakeGbkBinary(env, data->ClientID),
                  ErlNifMakeGbkBinary(env, data->ExchangeInstID),
                  ErlNifMakeGbkBinary(env, data->TraderID),
                  enif_make_int(env, data->InstallID),
                  ErlNifMakeGbkBinary(env, data->OrderSubmitStatus),
                  enif_make_int(env, data->NotifySequence),
                  ErlNifMakeGbkBinary(env, data->TradingDay),
                  enif_make_int(env, data->SettlementID),
                  ErlNifMakeGbkBinary(env, data->ExecOrderSysID),
                  ErlNifMakeGbkBinary(env, data->InsertDate),
                  ErlNifMakeGbkBinary(env, data->InsertTime),
                  ErlNifMakeGbkBinary(env, data->CancelTime),
                  ErlNifMakeGbkBinary(env, data->ExecResult),
                  ErlNifMakeGbkBinary(env, data->ClearingPartID),
                  enif_make_int(env, data->SequenceNo),
                  enif_make_int(env, data->FrontID),
                  enif_make_int(env, data->SessionID),
                  ErlNifMakeGbkBinary(env, data->UserProductInfo),
                  ErlNifMakeGbkBinary(env, data->StatusMsg),
                  ErlNifMakeGbkBinary(env, data->ActiveUserID),
                  enif_make_int(env, data->BrokerExecOrderSeq),
                  ErlNifMakeGbkBinary(env, data->BranchID),
                  ErlNifMakeGbkBinary(env, data->InvestUnitID),
                  ErlNifMakeGbkBinary(env, data->AccountID),
                  ErlNifMakeGbkBinary(env, data->CurrencyID),
                  ErlNifMakeGbkBinary(env, data->IPAddress),
                  ErlNifMakeGbkBinary(env, data->MacAddress)))));
  enif_free_env(env);
}

void CtpTd::OnErrRtnExecOrderInsert(CThostFtdcInputExecOrderField *data,
                                    CThostFtdcRspInfoField *error) {
  static CThostFtdcInputExecOrderField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple3(
              env, enif_make_atom(env, "on_err_rtn_exec_order_insert"),
              enif_make_tuple(
                  env, 22,
                  enif_make_atom(env, "cthost_ftdc_input_exec_order_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  ErlNifMakeGbkBinary(env, data->InstrumentID),
                  ErlNifMakeGbkBinary(env, data->ExecOrderRef),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  enif_make_int(env, data->Volume),
                  enif_make_int(env, data->RequestID),
                  ErlNifMakeGbkBinary(env, data->BusinessUnit),
                  ErlNifMakeGbkBinary(env, data->OffsetFlag),
                  ErlNifMakeGbkBinary(env, data->HedgeFlag),
                  ErlNifMakeGbkBinary(env, data->ActionType),
                  ErlNifMakeGbkBinary(env, data->PosiDirection),
                  ErlNifMakeGbkBinary(env, data->ReservePositionFlag),
                  ErlNifMakeGbkBinary(env, data->CloseFlag),
                  ErlNifMakeGbkBinary(env, data->ExchangeID),
                  ErlNifMakeGbkBinary(env, data->InvestUnitID),
                  ErlNifMakeGbkBinary(env, data->AccountID),
                  ErlNifMakeGbkBinary(env, data->CurrencyID),
                  ErlNifMakeGbkBinary(env, data->ClientID),
                  ErlNifMakeGbkBinary(env, data->IPAddress),
                  ErlNifMakeGbkBinary(env, data->MacAddress)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)))));
  enif_free_env(env);
}

void CtpTd::OnErrRtnExecOrderAction(CThostFtdcExecOrderActionField *data,
                                    CThostFtdcRspInfoField *error) {
  static CThostFtdcExecOrderActionField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple3(
              env, enif_make_atom(env, "on_err_rtn_exec_order_action"),
              enif_make_tuple(
                  env, 29,
                  enif_make_atom(env, "cthost_ftdc_exec_order_action_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  enif_make_int(env, data->ExecOrderActionRef),
                  ErlNifMakeGbkBinary(env, data->ExecOrderRef),
                  enif_make_int(env, data->RequestID),
                  enif_make_int(env, data->FrontID),
                  enif_make_int(env, data->SessionID),
                  ErlNifMakeGbkBinary(env, data->ExchangeID),
                  ErlNifMakeGbkBinary(env, data->ExecOrderSysID),
                  ErlNifMakeGbkBinary(env, data->ActionFlag),
                  ErlNifMakeGbkBinary(env, data->ActionDate),
                  ErlNifMakeGbkBinary(env, data->ActionTime),
                  ErlNifMakeGbkBinary(env, data->TraderID),
                  enif_make_int(env, data->InstallID),
                  ErlNifMakeGbkBinary(env, data->ExecOrderLocalID),
                  ErlNifMakeGbkBinary(env, data->ActionLocalID),
                  ErlNifMakeGbkBinary(env, data->ParticipantID),
                  ErlNifMakeGbkBinary(env, data->ClientID),
                  ErlNifMakeGbkBinary(env, data->BusinessUnit),
                  ErlNifMakeGbkBinary(env, data->OrderActionStatus),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  ErlNifMakeGbkBinary(env, data->ActionType),
                  ErlNifMakeGbkBinary(env, data->StatusMsg),
                  ErlNifMakeGbkBinary(env, data->InstrumentID),
                  ErlNifMakeGbkBinary(env, data->BranchID),
                  ErlNifMakeGbkBinary(env, data->InvestUnitID),
                  ErlNifMakeGbkBinary(env, data->IPAddress),
                  ErlNifMakeGbkBinary(env, data->MacAddress)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)))));
  enif_free_env(env);
}

void CtpTd::OnErrRtnForQuoteInsert(CThostFtdcInputForQuoteField *data,
                                   CThostFtdcRspInfoField *error) {
  static CThostFtdcInputForQuoteField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple3(
              env, enif_make_atom(env, "on_err_rtn_for_quote_insert"),
              enif_make_tuple(
                  env, 10,
                  enif_make_atom(env, "cthost_ftdc_input_for_quote_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  ErlNifMakeGbkBinary(env, data->InstrumentID),
                  ErlNifMakeGbkBinary(env, data->ForQuoteRef),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  ErlNifMakeGbkBinary(env, data->ExchangeID),
                  ErlNifMakeGbkBinary(env, data->InvestUnitID),
                  ErlNifMakeGbkBinary(env, data->IPAddress),
                  ErlNifMakeGbkBinary(env, data->MacAddress)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)))));
  enif_free_env(env);
}

void CtpTd::OnRtnQuote(CThostFtdcQuoteField *data) {
  static CThostFtdcQuoteField empty_data = {};

  if (!data) {
    data = &empty_data;
  }

  ErlNifEnv *env = enif_alloc_env();
  enif_send(NULL, &this->pid_, env,
            enif_make_tuple2(
                env, enif_make_atom(env, "ctp_td"),
                enif_make_tuple2(
                    env, enif_make_atom(env, "on_rtn_quote"),
                    enif_make_tuple(
                        env, 51, enif_make_atom(env, "cthost_ftdc_quote_field"),
                        ErlNifMakeGbkBinary(env, data->BrokerID),
                        ErlNifMakeGbkBinary(env, data->InvestorID),
                        ErlNifMakeGbkBinary(env, data->InstrumentID),
                        ErlNifMakeGbkBinary(env, data->QuoteRef),
                        ErlNifMakeGbkBinary(env, data->UserID),
                        enif_make_double(env, data->AskPrice),
                        enif_make_double(env, data->BidPrice),
                        enif_make_int(env, data->AskVolume),
                        enif_make_int(env, data->BidVolume),
                        enif_make_int(env, data->RequestID),
                        ErlNifMakeGbkBinary(env, data->BusinessUnit),
                        ErlNifMakeGbkBinary(env, data->AskOffsetFlag),
                        ErlNifMakeGbkBinary(env, data->BidOffsetFlag),
                        ErlNifMakeGbkBinary(env, data->AskHedgeFlag),
                        ErlNifMakeGbkBinary(env, data->BidHedgeFlag),
                        ErlNifMakeGbkBinary(env, data->QuoteLocalID),
                        ErlNifMakeGbkBinary(env, data->ExchangeID),
                        ErlNifMakeGbkBinary(env, data->ParticipantID),
                        ErlNifMakeGbkBinary(env, data->ClientID),
                        ErlNifMakeGbkBinary(env, data->ExchangeInstID),
                        ErlNifMakeGbkBinary(env, data->TraderID),
                        enif_make_int(env, data->InstallID),
                        enif_make_int(env, data->NotifySequence),
                        ErlNifMakeGbkBinary(env, data->OrderSubmitStatus),
                        ErlNifMakeGbkBinary(env, data->TradingDay),
                        enif_make_int(env, data->SettlementID),
                        ErlNifMakeGbkBinary(env, data->QuoteSysID),
                        ErlNifMakeGbkBinary(env, data->InsertDate),
                        ErlNifMakeGbkBinary(env, data->InsertTime),
                        ErlNifMakeGbkBinary(env, data->CancelTime),
                        ErlNifMakeGbkBinary(env, data->QuoteStatus),
                        ErlNifMakeGbkBinary(env, data->ClearingPartID),
                        enif_make_int(env, data->SequenceNo),
                        ErlNifMakeGbkBinary(env, data->AskOrderSysID),
                        ErlNifMakeGbkBinary(env, data->BidOrderSysID),
                        enif_make_int(env, data->FrontID),
                        enif_make_int(env, data->SessionID),
                        ErlNifMakeGbkBinary(env, data->UserProductInfo),
                        ErlNifMakeGbkBinary(env, data->StatusMsg),
                        ErlNifMakeGbkBinary(env, data->ActiveUserID),
                        enif_make_int(env, data->BrokerQuoteSeq),
                        ErlNifMakeGbkBinary(env, data->AskOrderRef),
                        ErlNifMakeGbkBinary(env, data->BidOrderRef),
                        ErlNifMakeGbkBinary(env, data->ForQuoteSysID),
                        ErlNifMakeGbkBinary(env, data->BranchID),
                        ErlNifMakeGbkBinary(env, data->InvestUnitID),
                        ErlNifMakeGbkBinary(env, data->AccountID),
                        ErlNifMakeGbkBinary(env, data->CurrencyID),
                        ErlNifMakeGbkBinary(env, data->IPAddress),
                        ErlNifMakeGbkBinary(env, data->MacAddress)))));
  enif_free_env(env);
}

void CtpTd::OnErrRtnQuoteInsert(CThostFtdcInputQuoteField *data,
                                CThostFtdcRspInfoField *error) {
  static CThostFtdcInputQuoteField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple3(
              env, enif_make_atom(env, "on_err_rtn_quote_insert"),
              enif_make_tuple(
                  env, 24, enif_make_atom(env, "cthost_ftdc_input_quote_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  ErlNifMakeGbkBinary(env, data->InstrumentID),
                  ErlNifMakeGbkBinary(env, data->QuoteRef),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  enif_make_double(env, data->AskPrice),
                  enif_make_double(env, data->BidPrice),
                  enif_make_int(env, data->AskVolume),
                  enif_make_int(env, data->BidVolume),
                  enif_make_int(env, data->RequestID),
                  ErlNifMakeGbkBinary(env, data->BusinessUnit),
                  ErlNifMakeGbkBinary(env, data->AskOffsetFlag),
                  ErlNifMakeGbkBinary(env, data->BidOffsetFlag),
                  ErlNifMakeGbkBinary(env, data->AskHedgeFlag),
                  ErlNifMakeGbkBinary(env, data->BidHedgeFlag),
                  ErlNifMakeGbkBinary(env, data->AskOrderRef),
                  ErlNifMakeGbkBinary(env, data->BidOrderRef),
                  ErlNifMakeGbkBinary(env, data->ForQuoteSysID),
                  ErlNifMakeGbkBinary(env, data->ExchangeID),
                  ErlNifMakeGbkBinary(env, data->InvestUnitID),
                  ErlNifMakeGbkBinary(env, data->ClientID),
                  ErlNifMakeGbkBinary(env, data->IPAddress),
                  ErlNifMakeGbkBinary(env, data->MacAddress)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)))));
  enif_free_env(env);
}

void CtpTd::OnErrRtnQuoteAction(CThostFtdcQuoteActionField *data,
                                CThostFtdcRspInfoField *error) {
  static CThostFtdcQuoteActionField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple3(
              env, enif_make_atom(env, "on_err_rtn_quote_action"),
              enif_make_tuple(
                  env, 28,
                  enif_make_atom(env, "cthost_ftdc_quote_action_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  enif_make_int(env, data->QuoteActionRef),
                  ErlNifMakeGbkBinary(env, data->QuoteRef),
                  enif_make_int(env, data->RequestID),
                  enif_make_int(env, data->FrontID),
                  enif_make_int(env, data->SessionID),
                  ErlNifMakeGbkBinary(env, data->ExchangeID),
                  ErlNifMakeGbkBinary(env, data->QuoteSysID),
                  ErlNifMakeGbkBinary(env, data->ActionFlag),
                  ErlNifMakeGbkBinary(env, data->ActionDate),
                  ErlNifMakeGbkBinary(env, data->ActionTime),
                  ErlNifMakeGbkBinary(env, data->TraderID),
                  enif_make_int(env, data->InstallID),
                  ErlNifMakeGbkBinary(env, data->QuoteLocalID),
                  ErlNifMakeGbkBinary(env, data->ActionLocalID),
                  ErlNifMakeGbkBinary(env, data->ParticipantID),
                  ErlNifMakeGbkBinary(env, data->ClientID),
                  ErlNifMakeGbkBinary(env, data->BusinessUnit),
                  ErlNifMakeGbkBinary(env, data->OrderActionStatus),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  ErlNifMakeGbkBinary(env, data->StatusMsg),
                  ErlNifMakeGbkBinary(env, data->InstrumentID),
                  ErlNifMakeGbkBinary(env, data->BranchID),
                  ErlNifMakeGbkBinary(env, data->InvestUnitID),
                  ErlNifMakeGbkBinary(env, data->IPAddress),
                  ErlNifMakeGbkBinary(env, data->MacAddress)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)))));
  enif_free_env(env);
}

void CtpTd::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *data) {
  static CThostFtdcForQuoteRspField empty_data = {};

  if (!data) {
    data = &empty_data;
  }

  ErlNifEnv *env = enif_alloc_env();
  enif_send(NULL, &this->pid_, env,
            enif_make_tuple2(
                env, enif_make_atom(env, "ctp_td"),
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

void CtpTd::OnRtnCFMMCTradingAccountToken(
    CThostFtdcCFMMCTradingAccountTokenField *data) {
  static CThostFtdcCFMMCTradingAccountTokenField empty_data = {};

  if (!data) {
    data = &empty_data;
  }

  ErlNifEnv *env = enif_alloc_env();
  enif_send(
      NULL, &this->pid_, env,
      enif_make_tuple2(
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple2(
              env, enif_make_atom(env, "on_rtn_cfmmctrading_account_token"),
              enif_make_tuple(
                  env, 6,
                  enif_make_atom(
                      env, "cthost_ftdc_cfmmctrading_account_token_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->ParticipantID),
                  ErlNifMakeGbkBinary(env, data->AccountID),
                  enif_make_int(env, data->KeyID),
                  ErlNifMakeGbkBinary(env, data->Token)))));
  enif_free_env(env);
}

void CtpTd::OnRtnLock(CThostFtdcLockField *data) {
  static CThostFtdcLockField empty_data = {};

  if (!data) {
    data = &empty_data;
  }

  ErlNifEnv *env = enif_alloc_env();
  enif_send(NULL, &this->pid_, env,
            enif_make_tuple2(
                env, enif_make_atom(env, "ctp_td"),
                enif_make_tuple2(
                    env, enif_make_atom(env, "on_rtn_lock"),
                    enif_make_tuple(
                        env, 37, enif_make_atom(env, "cthost_ftdc_lock_field"),
                        ErlNifMakeGbkBinary(env, data->BrokerID),
                        ErlNifMakeGbkBinary(env, data->InvestorID),
                        ErlNifMakeGbkBinary(env, data->InstrumentID),
                        ErlNifMakeGbkBinary(env, data->LockRef),
                        ErlNifMakeGbkBinary(env, data->UserID),
                        enif_make_int(env, data->Volume),
                        enif_make_int(env, data->RequestID),
                        ErlNifMakeGbkBinary(env, data->BusinessUnit),
                        ErlNifMakeGbkBinary(env, data->LockType),
                        ErlNifMakeGbkBinary(env, data->LockLocalID),
                        ErlNifMakeGbkBinary(env, data->ExchangeID),
                        ErlNifMakeGbkBinary(env, data->ParticipantID),
                        ErlNifMakeGbkBinary(env, data->ClientID),
                        ErlNifMakeGbkBinary(env, data->ExchangeInstID),
                        ErlNifMakeGbkBinary(env, data->TraderID),
                        enif_make_int(env, data->InstallID),
                        ErlNifMakeGbkBinary(env, data->OrderSubmitStatus),
                        enif_make_int(env, data->NotifySequence),
                        ErlNifMakeGbkBinary(env, data->TradingDay),
                        enif_make_int(env, data->SettlementID),
                        ErlNifMakeGbkBinary(env, data->LockSysID),
                        ErlNifMakeGbkBinary(env, data->InsertDate),
                        ErlNifMakeGbkBinary(env, data->InsertTime),
                        ErlNifMakeGbkBinary(env, data->CancelTime),
                        ErlNifMakeGbkBinary(env, data->LockStatus),
                        ErlNifMakeGbkBinary(env, data->ClearingPartID),
                        enif_make_int(env, data->SequenceNo),
                        enif_make_int(env, data->FrontID),
                        enif_make_int(env, data->SessionID),
                        ErlNifMakeGbkBinary(env, data->UserProductInfo),
                        ErlNifMakeGbkBinary(env, data->StatusMsg),
                        ErlNifMakeGbkBinary(env, data->ActiveUserID),
                        enif_make_int(env, data->BrokerLockSeq),
                        ErlNifMakeGbkBinary(env, data->BranchID),
                        ErlNifMakeGbkBinary(env, data->IPAddress),
                        ErlNifMakeGbkBinary(env, data->MacAddress)))));
  enif_free_env(env);
}

void CtpTd::OnErrRtnLockInsert(CThostFtdcInputLockField *data,
                               CThostFtdcRspInfoField *error) {
  static CThostFtdcInputLockField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple3(
              env, enif_make_atom(env, "on_err_rtn_lock_insert"),
              enif_make_tuple(
                  env, 13, enif_make_atom(env, "cthost_ftdc_input_lock_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  ErlNifMakeGbkBinary(env, data->InstrumentID),
                  ErlNifMakeGbkBinary(env, data->LockRef),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  enif_make_int(env, data->Volume),
                  enif_make_int(env, data->RequestID),
                  ErlNifMakeGbkBinary(env, data->BusinessUnit),
                  ErlNifMakeGbkBinary(env, data->LockType),
                  ErlNifMakeGbkBinary(env, data->ExchangeID),
                  ErlNifMakeGbkBinary(env, data->IPAddress),
                  ErlNifMakeGbkBinary(env, data->MacAddress)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)))));
  enif_free_env(env);
}

void CtpTd::OnErrRtnBatchOrderAction(CThostFtdcBatchOrderActionField *data,
                                     CThostFtdcRspInfoField *error) {
  static CThostFtdcBatchOrderActionField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple3(
              env, enif_make_atom(env, "on_err_rtn_batch_order_action"),
              enif_make_tuple(
                  env, 22,
                  enif_make_atom(env, "cthost_ftdc_batch_order_action_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  enif_make_int(env, data->OrderActionRef),
                  enif_make_int(env, data->RequestID),
                  enif_make_int(env, data->FrontID),
                  enif_make_int(env, data->SessionID),
                  ErlNifMakeGbkBinary(env, data->ExchangeID),
                  ErlNifMakeGbkBinary(env, data->ActionDate),
                  ErlNifMakeGbkBinary(env, data->ActionTime),
                  ErlNifMakeGbkBinary(env, data->TraderID),
                  enif_make_int(env, data->InstallID),
                  ErlNifMakeGbkBinary(env, data->ActionLocalID),
                  ErlNifMakeGbkBinary(env, data->ParticipantID),
                  ErlNifMakeGbkBinary(env, data->ClientID),
                  ErlNifMakeGbkBinary(env, data->BusinessUnit),
                  ErlNifMakeGbkBinary(env, data->OrderActionStatus),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  ErlNifMakeGbkBinary(env, data->StatusMsg),
                  ErlNifMakeGbkBinary(env, data->InvestUnitID),
                  ErlNifMakeGbkBinary(env, data->IPAddress),
                  ErlNifMakeGbkBinary(env, data->MacAddress)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)))));
  enif_free_env(env);
}

void CtpTd::OnRtnCombAction(CThostFtdcCombActionField *data) {
  static CThostFtdcCombActionField empty_data = {};

  if (!data) {
    data = &empty_data;
  }

  ErlNifEnv *env = enif_alloc_env();
  enif_send(
      NULL, &this->pid_, env,
      enif_make_tuple2(
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple2(
              env, enif_make_atom(env, "on_rtn_comb_action"),
              enif_make_tuple(
                  env, 30, enif_make_atom(env, "cthost_ftdc_comb_action_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  ErlNifMakeGbkBinary(env, data->InstrumentID),
                  ErlNifMakeGbkBinary(env, data->CombActionRef),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  ErlNifMakeGbkBinary(env, data->Direction),
                  enif_make_int(env, data->Volume),
                  ErlNifMakeGbkBinary(env, data->CombDirection),
                  ErlNifMakeGbkBinary(env, data->HedgeFlag),
                  ErlNifMakeGbkBinary(env, data->ActionLocalID),
                  ErlNifMakeGbkBinary(env, data->ExchangeID),
                  ErlNifMakeGbkBinary(env, data->ParticipantID),
                  ErlNifMakeGbkBinary(env, data->ClientID),
                  ErlNifMakeGbkBinary(env, data->ExchangeInstID),
                  ErlNifMakeGbkBinary(env, data->TraderID),
                  enif_make_int(env, data->InstallID),
                  ErlNifMakeGbkBinary(env, data->ActionStatus),
                  enif_make_int(env, data->NotifySequence),
                  ErlNifMakeGbkBinary(env, data->TradingDay),
                  enif_make_int(env, data->SettlementID),
                  enif_make_int(env, data->SequenceNo),
                  enif_make_int(env, data->FrontID),
                  enif_make_int(env, data->SessionID),
                  ErlNifMakeGbkBinary(env, data->UserProductInfo),
                  ErlNifMakeGbkBinary(env, data->StatusMsg),
                  ErlNifMakeGbkBinary(env, data->IPAddress),
                  ErlNifMakeGbkBinary(env, data->MacAddress),
                  ErlNifMakeGbkBinary(env, data->ComTradeID),
                  ErlNifMakeGbkBinary(env, data->BranchID)))));
  enif_free_env(env);
}

void CtpTd::OnErrRtnCombActionInsert(CThostFtdcInputCombActionField *data,
                                     CThostFtdcRspInfoField *error) {
  static CThostFtdcInputCombActionField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple3(
              env, enif_make_atom(env, "on_err_rtn_comb_action_insert"),
              enif_make_tuple(
                  env, 13,
                  enif_make_atom(env, "cthost_ftdc_input_comb_action_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  ErlNifMakeGbkBinary(env, data->InstrumentID),
                  ErlNifMakeGbkBinary(env, data->CombActionRef),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  ErlNifMakeGbkBinary(env, data->Direction),
                  enif_make_int(env, data->Volume),
                  ErlNifMakeGbkBinary(env, data->CombDirection),
                  ErlNifMakeGbkBinary(env, data->HedgeFlag),
                  ErlNifMakeGbkBinary(env, data->ExchangeID),
                  ErlNifMakeGbkBinary(env, data->IPAddress),
                  ErlNifMakeGbkBinary(env, data->MacAddress)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)))));
  enif_free_env(env);
}

void CtpTd::OnRspQryContractBank(CThostFtdcContractBankField *data,
                                 CThostFtdcRspInfoField *error, int req_id,
                                 bool last) {
  static CThostFtdcContractBankField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_qry_contract_bank"),
              enif_make_tuple(
                  env, 5,
                  enif_make_atom(env, "cthost_ftdc_contract_bank_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->BankID),
                  ErlNifMakeGbkBinary(env, data->BankBrchID),
                  ErlNifMakeGbkBinary(env, data->BankName)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQryParkedOrder(CThostFtdcParkedOrderField *data,
                                CThostFtdcRspInfoField *error, int req_id,
                                bool last) {
  static CThostFtdcParkedOrderField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_qry_parked_order"),
              enif_make_tuple(
                  env, 36,
                  enif_make_atom(env, "cthost_ftdc_parked_order_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  ErlNifMakeGbkBinary(env, data->InstrumentID),
                  ErlNifMakeGbkBinary(env, data->OrderRef),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  ErlNifMakeGbkBinary(env, data->OrderPriceType),
                  ErlNifMakeGbkBinary(env, data->Direction),
                  ErlNifMakeGbkBinary(env, data->CombOffsetFlag),
                  ErlNifMakeGbkBinary(env, data->CombHedgeFlag),
                  enif_make_double(env, data->LimitPrice),
                  enif_make_int(env, data->VolumeTotalOriginal),
                  ErlNifMakeGbkBinary(env, data->TimeCondition),
                  ErlNifMakeGbkBinary(env, data->GTDDate),
                  ErlNifMakeGbkBinary(env, data->VolumeCondition),
                  enif_make_int(env, data->MinVolume),
                  ErlNifMakeGbkBinary(env, data->ContingentCondition),
                  enif_make_double(env, data->StopPrice),
                  ErlNifMakeGbkBinary(env, data->ForceCloseReason),
                  enif_make_int(env, data->IsAutoSuspend),
                  ErlNifMakeGbkBinary(env, data->BusinessUnit),
                  enif_make_int(env, data->RequestID),
                  enif_make_int(env, data->UserForceClose),
                  ErlNifMakeGbkBinary(env, data->ExchangeID),
                  ErlNifMakeGbkBinary(env, data->ParkedOrderID),
                  ErlNifMakeGbkBinary(env, data->UserType),
                  ErlNifMakeGbkBinary(env, data->Status),
                  enif_make_int(env, data->ErrorID),
                  ErlNifMakeGbkBinary(env, data->ErrorMsg),
                  enif_make_int(env, data->IsSwapOrder),
                  ErlNifMakeGbkBinary(env, data->AccountID),
                  ErlNifMakeGbkBinary(env, data->CurrencyID),
                  ErlNifMakeGbkBinary(env, data->ClientID),
                  ErlNifMakeGbkBinary(env, data->InvestUnitID),
                  ErlNifMakeGbkBinary(env, data->IPAddress),
                  ErlNifMakeGbkBinary(env, data->MacAddress)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQryParkedOrderAction(CThostFtdcParkedOrderActionField *data,
                                      CThostFtdcRspInfoField *error, int req_id,
                                      bool last) {
  static CThostFtdcParkedOrderActionField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_qry_parked_order_action"),
              enif_make_tuple(
                  env, 23,
                  enif_make_atom(env, "cthost_ftdc_parked_order_action_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  enif_make_int(env, data->OrderActionRef),
                  ErlNifMakeGbkBinary(env, data->OrderRef),
                  enif_make_int(env, data->RequestID),
                  enif_make_int(env, data->FrontID),
                  enif_make_int(env, data->SessionID),
                  ErlNifMakeGbkBinary(env, data->ExchangeID),
                  ErlNifMakeGbkBinary(env, data->OrderSysID),
                  ErlNifMakeGbkBinary(env, data->ActionFlag),
                  enif_make_double(env, data->LimitPrice),
                  enif_make_int(env, data->VolumeChange),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  ErlNifMakeGbkBinary(env, data->InstrumentID),
                  ErlNifMakeGbkBinary(env, data->ParkedOrderActionID),
                  ErlNifMakeGbkBinary(env, data->UserType),
                  ErlNifMakeGbkBinary(env, data->Status),
                  enif_make_int(env, data->ErrorID),
                  ErlNifMakeGbkBinary(env, data->ErrorMsg),
                  ErlNifMakeGbkBinary(env, data->InvestUnitID),
                  ErlNifMakeGbkBinary(env, data->IPAddress),
                  ErlNifMakeGbkBinary(env, data->MacAddress)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQryTradingNotice(CThostFtdcTradingNoticeField *data,
                                  CThostFtdcRspInfoField *error, int req_id,
                                  bool last) {
  static CThostFtdcTradingNoticeField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_qry_trading_notice"),
              enif_make_tuple(
                  env, 9,
                  enif_make_atom(env, "cthost_ftdc_trading_notice_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorRange),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  enif_make_int(env, data->SequenceSeries),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  ErlNifMakeGbkBinary(env, data->SendTime),
                  enif_make_int(env, data->SequenceNo),
                  ErlNifMakeGbkBinary(env, data->FieldContent)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQryBrokerTradingParams(
    CThostFtdcBrokerTradingParamsField *data, CThostFtdcRspInfoField *error,
    int req_id, bool last) {
  static CThostFtdcBrokerTradingParamsField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_qry_broker_trading_params"),
              enif_make_tuple(
                  env, 8,
                  enif_make_atom(env,
                                 "cthost_ftdc_broker_trading_params_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID),
                  ErlNifMakeGbkBinary(env, data->MarginPriceType),
                  ErlNifMakeGbkBinary(env, data->Algorithm),
                  ErlNifMakeGbkBinary(env, data->AvailIncludeCloseProfit),
                  ErlNifMakeGbkBinary(env, data->CurrencyID),
                  ErlNifMakeGbkBinary(env, data->OptionRoyaltyPriceType)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQryBrokerTradingAlgos(CThostFtdcBrokerTradingAlgosField *data,
                                       CThostFtdcRspInfoField *error,
                                       int req_id, bool last) {
  static CThostFtdcBrokerTradingAlgosField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_qry_broker_trading_algos"),
              enif_make_tuple(
                  env, 7,
                  enif_make_atom(env, "cthost_ftdc_broker_trading_algos_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->ExchangeID),
                  ErlNifMakeGbkBinary(env, data->InstrumentID),
                  ErlNifMakeGbkBinary(env, data->HandlePositionAlgoID),
                  ErlNifMakeGbkBinary(env, data->FindMarginRateAlgoID),
                  ErlNifMakeGbkBinary(env, data->HandleTradingAccountAlgoID)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQueryCFMMCTradingAccountToken(
    CThostFtdcQueryCFMMCTradingAccountTokenField *data,
    CThostFtdcRspInfoField *error, int req_id, bool last) {
  static CThostFtdcQueryCFMMCTradingAccountTokenField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env,
              enif_make_atom(env, "on_rsp_query_cfmmctrading_account_token"),
              enif_make_tuple(
                  env, 3,
                  enif_make_atom(
                      env,
                      "cthost_ftdc_query_cfmmctrading_account_token_field"),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->InvestorID)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRtnFromBankToFutureByBank(CThostFtdcRspTransferField *data) {
  static CThostFtdcRspTransferField empty_data = {};

  if (!data) {
    data = &empty_data;
  }

  ErlNifEnv *env = enif_alloc_env();
  enif_send(
      NULL, &this->pid_, env,
      enif_make_tuple2(
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple2(
              env, enif_make_atom(env, "on_rtn_from_bank_to_future_by_bank"),
              enif_make_tuple(
                  env, 46,
                  enif_make_atom(env, "cthost_ftdc_rsp_transfer_field"),
                  ErlNifMakeGbkBinary(env, data->TradeCode),
                  ErlNifMakeGbkBinary(env, data->BankID),
                  ErlNifMakeGbkBinary(env, data->BankBranchID),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->BrokerBranchID),
                  ErlNifMakeGbkBinary(env, data->TradeDate),
                  ErlNifMakeGbkBinary(env, data->TradeTime),
                  ErlNifMakeGbkBinary(env, data->BankSerial),
                  ErlNifMakeGbkBinary(env, data->TradingDay),
                  enif_make_int(env, data->PlateSerial),
                  ErlNifMakeGbkBinary(env, data->LastFragment),
                  enif_make_int(env, data->SessionID),
                  ErlNifMakeGbkBinary(env, data->CustomerName),
                  ErlNifMakeGbkBinary(env, data->IdCardType),
                  ErlNifMakeGbkBinary(env, data->IdentifiedCardNo),
                  ErlNifMakeGbkBinary(env, data->CustType),
                  ErlNifMakeGbkBinary(env, data->BankAccount),
                  ErlNifMakeGbkBinary(env, data->BankPassWord),
                  ErlNifMakeGbkBinary(env, data->AccountID),
                  ErlNifMakeGbkBinary(env, data->Password),
                  enif_make_int(env, data->InstallID),
                  enif_make_int(env, data->FutureSerial),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  ErlNifMakeGbkBinary(env, data->VerifyCertNoFlag),
                  ErlNifMakeGbkBinary(env, data->CurrencyID),
                  enif_make_double(env, data->TradeAmount),
                  enif_make_double(env, data->FutureFetchAmount),
                  ErlNifMakeGbkBinary(env, data->FeePayFlag),
                  enif_make_double(env, data->CustFee),
                  enif_make_double(env, data->BrokerFee),
                  ErlNifMakeGbkBinary(env, data->Message),
                  ErlNifMakeGbkBinary(env, data->Digest),
                  ErlNifMakeGbkBinary(env, data->BankAccType),
                  ErlNifMakeGbkBinary(env, data->DeviceID),
                  ErlNifMakeGbkBinary(env, data->BankSecuAccType),
                  ErlNifMakeGbkBinary(env, data->BrokerIDByBank),
                  ErlNifMakeGbkBinary(env, data->BankSecuAcc),
                  ErlNifMakeGbkBinary(env, data->BankPwdFlag),
                  ErlNifMakeGbkBinary(env, data->SecuPwdFlag),
                  ErlNifMakeGbkBinary(env, data->OperNo),
                  enif_make_int(env, data->RequestID),
                  enif_make_int(env, data->TID),
                  ErlNifMakeGbkBinary(env, data->TransferStatus),
                  enif_make_int(env, data->ErrorID),
                  ErlNifMakeGbkBinary(env, data->ErrorMsg)))));
  enif_free_env(env);
}

void CtpTd::OnRtnFromFutureToBankByBank(CThostFtdcRspTransferField *data) {
  static CThostFtdcRspTransferField empty_data = {};

  if (!data) {
    data = &empty_data;
  }

  ErlNifEnv *env = enif_alloc_env();
  enif_send(
      NULL, &this->pid_, env,
      enif_make_tuple2(
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple2(
              env, enif_make_atom(env, "on_rtn_from_future_to_bank_by_bank"),
              enif_make_tuple(
                  env, 46,
                  enif_make_atom(env, "cthost_ftdc_rsp_transfer_field"),
                  ErlNifMakeGbkBinary(env, data->TradeCode),
                  ErlNifMakeGbkBinary(env, data->BankID),
                  ErlNifMakeGbkBinary(env, data->BankBranchID),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->BrokerBranchID),
                  ErlNifMakeGbkBinary(env, data->TradeDate),
                  ErlNifMakeGbkBinary(env, data->TradeTime),
                  ErlNifMakeGbkBinary(env, data->BankSerial),
                  ErlNifMakeGbkBinary(env, data->TradingDay),
                  enif_make_int(env, data->PlateSerial),
                  ErlNifMakeGbkBinary(env, data->LastFragment),
                  enif_make_int(env, data->SessionID),
                  ErlNifMakeGbkBinary(env, data->CustomerName),
                  ErlNifMakeGbkBinary(env, data->IdCardType),
                  ErlNifMakeGbkBinary(env, data->IdentifiedCardNo),
                  ErlNifMakeGbkBinary(env, data->CustType),
                  ErlNifMakeGbkBinary(env, data->BankAccount),
                  ErlNifMakeGbkBinary(env, data->BankPassWord),
                  ErlNifMakeGbkBinary(env, data->AccountID),
                  ErlNifMakeGbkBinary(env, data->Password),
                  enif_make_int(env, data->InstallID),
                  enif_make_int(env, data->FutureSerial),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  ErlNifMakeGbkBinary(env, data->VerifyCertNoFlag),
                  ErlNifMakeGbkBinary(env, data->CurrencyID),
                  enif_make_double(env, data->TradeAmount),
                  enif_make_double(env, data->FutureFetchAmount),
                  ErlNifMakeGbkBinary(env, data->FeePayFlag),
                  enif_make_double(env, data->CustFee),
                  enif_make_double(env, data->BrokerFee),
                  ErlNifMakeGbkBinary(env, data->Message),
                  ErlNifMakeGbkBinary(env, data->Digest),
                  ErlNifMakeGbkBinary(env, data->BankAccType),
                  ErlNifMakeGbkBinary(env, data->DeviceID),
                  ErlNifMakeGbkBinary(env, data->BankSecuAccType),
                  ErlNifMakeGbkBinary(env, data->BrokerIDByBank),
                  ErlNifMakeGbkBinary(env, data->BankSecuAcc),
                  ErlNifMakeGbkBinary(env, data->BankPwdFlag),
                  ErlNifMakeGbkBinary(env, data->SecuPwdFlag),
                  ErlNifMakeGbkBinary(env, data->OperNo),
                  enif_make_int(env, data->RequestID),
                  enif_make_int(env, data->TID),
                  ErlNifMakeGbkBinary(env, data->TransferStatus),
                  enif_make_int(env, data->ErrorID),
                  ErlNifMakeGbkBinary(env, data->ErrorMsg)))));
  enif_free_env(env);
}

void CtpTd::OnRtnRepealFromBankToFutureByBank(CThostFtdcRspRepealField *data) {
  static CThostFtdcRspRepealField empty_data = {};

  if (!data) {
    data = &empty_data;
  }

  ErlNifEnv *env = enif_alloc_env();
  enif_send(
      NULL, &this->pid_, env,
      enif_make_tuple2(
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple2(
              env,
              enif_make_atom(env, "on_rtn_repeal_from_bank_to_future_by_bank"),
              enif_make_tuple(
                  env, 53, enif_make_atom(env, "cthost_ftdc_rsp_repeal_field"),
                  enif_make_int(env, data->RepealTimeInterval),
                  enif_make_int(env, data->RepealedTimes),
                  ErlNifMakeGbkBinary(env, data->BankRepealFlag),
                  ErlNifMakeGbkBinary(env, data->BrokerRepealFlag),
                  enif_make_int(env, data->PlateRepealSerial),
                  ErlNifMakeGbkBinary(env, data->BankRepealSerial),
                  enif_make_int(env, data->FutureRepealSerial),
                  ErlNifMakeGbkBinary(env, data->TradeCode),
                  ErlNifMakeGbkBinary(env, data->BankID),
                  ErlNifMakeGbkBinary(env, data->BankBranchID),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->BrokerBranchID),
                  ErlNifMakeGbkBinary(env, data->TradeDate),
                  ErlNifMakeGbkBinary(env, data->TradeTime),
                  ErlNifMakeGbkBinary(env, data->BankSerial),
                  ErlNifMakeGbkBinary(env, data->TradingDay),
                  enif_make_int(env, data->PlateSerial),
                  ErlNifMakeGbkBinary(env, data->LastFragment),
                  enif_make_int(env, data->SessionID),
                  ErlNifMakeGbkBinary(env, data->CustomerName),
                  ErlNifMakeGbkBinary(env, data->IdCardType),
                  ErlNifMakeGbkBinary(env, data->IdentifiedCardNo),
                  ErlNifMakeGbkBinary(env, data->CustType),
                  ErlNifMakeGbkBinary(env, data->BankAccount),
                  ErlNifMakeGbkBinary(env, data->BankPassWord),
                  ErlNifMakeGbkBinary(env, data->AccountID),
                  ErlNifMakeGbkBinary(env, data->Password),
                  enif_make_int(env, data->InstallID),
                  enif_make_int(env, data->FutureSerial),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  ErlNifMakeGbkBinary(env, data->VerifyCertNoFlag),
                  ErlNifMakeGbkBinary(env, data->CurrencyID),
                  enif_make_double(env, data->TradeAmount),
                  enif_make_double(env, data->FutureFetchAmount),
                  ErlNifMakeGbkBinary(env, data->FeePayFlag),
                  enif_make_double(env, data->CustFee),
                  enif_make_double(env, data->BrokerFee),
                  ErlNifMakeGbkBinary(env, data->Message),
                  ErlNifMakeGbkBinary(env, data->Digest),
                  ErlNifMakeGbkBinary(env, data->BankAccType),
                  ErlNifMakeGbkBinary(env, data->DeviceID),
                  ErlNifMakeGbkBinary(env, data->BankSecuAccType),
                  ErlNifMakeGbkBinary(env, data->BrokerIDByBank),
                  ErlNifMakeGbkBinary(env, data->BankSecuAcc),
                  ErlNifMakeGbkBinary(env, data->BankPwdFlag),
                  ErlNifMakeGbkBinary(env, data->SecuPwdFlag),
                  ErlNifMakeGbkBinary(env, data->OperNo),
                  enif_make_int(env, data->RequestID),
                  enif_make_int(env, data->TID),
                  ErlNifMakeGbkBinary(env, data->TransferStatus),
                  enif_make_int(env, data->ErrorID),
                  ErlNifMakeGbkBinary(env, data->ErrorMsg)))));
  enif_free_env(env);
}

void CtpTd::OnRtnRepealFromFutureToBankByBank(CThostFtdcRspRepealField *data) {
  static CThostFtdcRspRepealField empty_data = {};

  if (!data) {
    data = &empty_data;
  }

  ErlNifEnv *env = enif_alloc_env();
  enif_send(
      NULL, &this->pid_, env,
      enif_make_tuple2(
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple2(
              env,
              enif_make_atom(env, "on_rtn_repeal_from_future_to_bank_by_bank"),
              enif_make_tuple(
                  env, 53, enif_make_atom(env, "cthost_ftdc_rsp_repeal_field"),
                  enif_make_int(env, data->RepealTimeInterval),
                  enif_make_int(env, data->RepealedTimes),
                  ErlNifMakeGbkBinary(env, data->BankRepealFlag),
                  ErlNifMakeGbkBinary(env, data->BrokerRepealFlag),
                  enif_make_int(env, data->PlateRepealSerial),
                  ErlNifMakeGbkBinary(env, data->BankRepealSerial),
                  enif_make_int(env, data->FutureRepealSerial),
                  ErlNifMakeGbkBinary(env, data->TradeCode),
                  ErlNifMakeGbkBinary(env, data->BankID),
                  ErlNifMakeGbkBinary(env, data->BankBranchID),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->BrokerBranchID),
                  ErlNifMakeGbkBinary(env, data->TradeDate),
                  ErlNifMakeGbkBinary(env, data->TradeTime),
                  ErlNifMakeGbkBinary(env, data->BankSerial),
                  ErlNifMakeGbkBinary(env, data->TradingDay),
                  enif_make_int(env, data->PlateSerial),
                  ErlNifMakeGbkBinary(env, data->LastFragment),
                  enif_make_int(env, data->SessionID),
                  ErlNifMakeGbkBinary(env, data->CustomerName),
                  ErlNifMakeGbkBinary(env, data->IdCardType),
                  ErlNifMakeGbkBinary(env, data->IdentifiedCardNo),
                  ErlNifMakeGbkBinary(env, data->CustType),
                  ErlNifMakeGbkBinary(env, data->BankAccount),
                  ErlNifMakeGbkBinary(env, data->BankPassWord),
                  ErlNifMakeGbkBinary(env, data->AccountID),
                  ErlNifMakeGbkBinary(env, data->Password),
                  enif_make_int(env, data->InstallID),
                  enif_make_int(env, data->FutureSerial),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  ErlNifMakeGbkBinary(env, data->VerifyCertNoFlag),
                  ErlNifMakeGbkBinary(env, data->CurrencyID),
                  enif_make_double(env, data->TradeAmount),
                  enif_make_double(env, data->FutureFetchAmount),
                  ErlNifMakeGbkBinary(env, data->FeePayFlag),
                  enif_make_double(env, data->CustFee),
                  enif_make_double(env, data->BrokerFee),
                  ErlNifMakeGbkBinary(env, data->Message),
                  ErlNifMakeGbkBinary(env, data->Digest),
                  ErlNifMakeGbkBinary(env, data->BankAccType),
                  ErlNifMakeGbkBinary(env, data->DeviceID),
                  ErlNifMakeGbkBinary(env, data->BankSecuAccType),
                  ErlNifMakeGbkBinary(env, data->BrokerIDByBank),
                  ErlNifMakeGbkBinary(env, data->BankSecuAcc),
                  ErlNifMakeGbkBinary(env, data->BankPwdFlag),
                  ErlNifMakeGbkBinary(env, data->SecuPwdFlag),
                  ErlNifMakeGbkBinary(env, data->OperNo),
                  enif_make_int(env, data->RequestID),
                  enif_make_int(env, data->TID),
                  ErlNifMakeGbkBinary(env, data->TransferStatus),
                  enif_make_int(env, data->ErrorID),
                  ErlNifMakeGbkBinary(env, data->ErrorMsg)))));
  enif_free_env(env);
}

void CtpTd::OnRtnFromBankToFutureByFuture(CThostFtdcRspTransferField *data) {
  static CThostFtdcRspTransferField empty_data = {};

  if (!data) {
    data = &empty_data;
  }

  ErlNifEnv *env = enif_alloc_env();
  enif_send(
      NULL, &this->pid_, env,
      enif_make_tuple2(
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple2(
              env, enif_make_atom(env, "on_rtn_from_bank_to_future_by_future"),
              enif_make_tuple(
                  env, 46,
                  enif_make_atom(env, "cthost_ftdc_rsp_transfer_field"),
                  ErlNifMakeGbkBinary(env, data->TradeCode),
                  ErlNifMakeGbkBinary(env, data->BankID),
                  ErlNifMakeGbkBinary(env, data->BankBranchID),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->BrokerBranchID),
                  ErlNifMakeGbkBinary(env, data->TradeDate),
                  ErlNifMakeGbkBinary(env, data->TradeTime),
                  ErlNifMakeGbkBinary(env, data->BankSerial),
                  ErlNifMakeGbkBinary(env, data->TradingDay),
                  enif_make_int(env, data->PlateSerial),
                  ErlNifMakeGbkBinary(env, data->LastFragment),
                  enif_make_int(env, data->SessionID),
                  ErlNifMakeGbkBinary(env, data->CustomerName),
                  ErlNifMakeGbkBinary(env, data->IdCardType),
                  ErlNifMakeGbkBinary(env, data->IdentifiedCardNo),
                  ErlNifMakeGbkBinary(env, data->CustType),
                  ErlNifMakeGbkBinary(env, data->BankAccount),
                  ErlNifMakeGbkBinary(env, data->BankPassWord),
                  ErlNifMakeGbkBinary(env, data->AccountID),
                  ErlNifMakeGbkBinary(env, data->Password),
                  enif_make_int(env, data->InstallID),
                  enif_make_int(env, data->FutureSerial),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  ErlNifMakeGbkBinary(env, data->VerifyCertNoFlag),
                  ErlNifMakeGbkBinary(env, data->CurrencyID),
                  enif_make_double(env, data->TradeAmount),
                  enif_make_double(env, data->FutureFetchAmount),
                  ErlNifMakeGbkBinary(env, data->FeePayFlag),
                  enif_make_double(env, data->CustFee),
                  enif_make_double(env, data->BrokerFee),
                  ErlNifMakeGbkBinary(env, data->Message),
                  ErlNifMakeGbkBinary(env, data->Digest),
                  ErlNifMakeGbkBinary(env, data->BankAccType),
                  ErlNifMakeGbkBinary(env, data->DeviceID),
                  ErlNifMakeGbkBinary(env, data->BankSecuAccType),
                  ErlNifMakeGbkBinary(env, data->BrokerIDByBank),
                  ErlNifMakeGbkBinary(env, data->BankSecuAcc),
                  ErlNifMakeGbkBinary(env, data->BankPwdFlag),
                  ErlNifMakeGbkBinary(env, data->SecuPwdFlag),
                  ErlNifMakeGbkBinary(env, data->OperNo),
                  enif_make_int(env, data->RequestID),
                  enif_make_int(env, data->TID),
                  ErlNifMakeGbkBinary(env, data->TransferStatus),
                  enif_make_int(env, data->ErrorID),
                  ErlNifMakeGbkBinary(env, data->ErrorMsg)))));
  enif_free_env(env);
}

void CtpTd::OnRtnFromFutureToBankByFuture(CThostFtdcRspTransferField *data) {
  static CThostFtdcRspTransferField empty_data = {};

  if (!data) {
    data = &empty_data;
  }

  ErlNifEnv *env = enif_alloc_env();
  enif_send(
      NULL, &this->pid_, env,
      enif_make_tuple2(
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple2(
              env, enif_make_atom(env, "on_rtn_from_future_to_bank_by_future"),
              enif_make_tuple(
                  env, 46,
                  enif_make_atom(env, "cthost_ftdc_rsp_transfer_field"),
                  ErlNifMakeGbkBinary(env, data->TradeCode),
                  ErlNifMakeGbkBinary(env, data->BankID),
                  ErlNifMakeGbkBinary(env, data->BankBranchID),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->BrokerBranchID),
                  ErlNifMakeGbkBinary(env, data->TradeDate),
                  ErlNifMakeGbkBinary(env, data->TradeTime),
                  ErlNifMakeGbkBinary(env, data->BankSerial),
                  ErlNifMakeGbkBinary(env, data->TradingDay),
                  enif_make_int(env, data->PlateSerial),
                  ErlNifMakeGbkBinary(env, data->LastFragment),
                  enif_make_int(env, data->SessionID),
                  ErlNifMakeGbkBinary(env, data->CustomerName),
                  ErlNifMakeGbkBinary(env, data->IdCardType),
                  ErlNifMakeGbkBinary(env, data->IdentifiedCardNo),
                  ErlNifMakeGbkBinary(env, data->CustType),
                  ErlNifMakeGbkBinary(env, data->BankAccount),
                  ErlNifMakeGbkBinary(env, data->BankPassWord),
                  ErlNifMakeGbkBinary(env, data->AccountID),
                  ErlNifMakeGbkBinary(env, data->Password),
                  enif_make_int(env, data->InstallID),
                  enif_make_int(env, data->FutureSerial),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  ErlNifMakeGbkBinary(env, data->VerifyCertNoFlag),
                  ErlNifMakeGbkBinary(env, data->CurrencyID),
                  enif_make_double(env, data->TradeAmount),
                  enif_make_double(env, data->FutureFetchAmount),
                  ErlNifMakeGbkBinary(env, data->FeePayFlag),
                  enif_make_double(env, data->CustFee),
                  enif_make_double(env, data->BrokerFee),
                  ErlNifMakeGbkBinary(env, data->Message),
                  ErlNifMakeGbkBinary(env, data->Digest),
                  ErlNifMakeGbkBinary(env, data->BankAccType),
                  ErlNifMakeGbkBinary(env, data->DeviceID),
                  ErlNifMakeGbkBinary(env, data->BankSecuAccType),
                  ErlNifMakeGbkBinary(env, data->BrokerIDByBank),
                  ErlNifMakeGbkBinary(env, data->BankSecuAcc),
                  ErlNifMakeGbkBinary(env, data->BankPwdFlag),
                  ErlNifMakeGbkBinary(env, data->SecuPwdFlag),
                  ErlNifMakeGbkBinary(env, data->OperNo),
                  enif_make_int(env, data->RequestID),
                  enif_make_int(env, data->TID),
                  ErlNifMakeGbkBinary(env, data->TransferStatus),
                  enif_make_int(env, data->ErrorID),
                  ErlNifMakeGbkBinary(env, data->ErrorMsg)))));
  enif_free_env(env);
}

void CtpTd::OnRtnRepealFromBankToFutureByFutureManual(
    CThostFtdcRspRepealField *data) {
  static CThostFtdcRspRepealField empty_data = {};

  if (!data) {
    data = &empty_data;
  }

  ErlNifEnv *env = enif_alloc_env();
  enif_send(
      NULL, &this->pid_, env,
      enif_make_tuple2(
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple2(
              env,
              enif_make_atom(
                  env, "on_rtn_repeal_from_bank_to_future_by_future_manual"),
              enif_make_tuple(
                  env, 53, enif_make_atom(env, "cthost_ftdc_rsp_repeal_field"),
                  enif_make_int(env, data->RepealTimeInterval),
                  enif_make_int(env, data->RepealedTimes),
                  ErlNifMakeGbkBinary(env, data->BankRepealFlag),
                  ErlNifMakeGbkBinary(env, data->BrokerRepealFlag),
                  enif_make_int(env, data->PlateRepealSerial),
                  ErlNifMakeGbkBinary(env, data->BankRepealSerial),
                  enif_make_int(env, data->FutureRepealSerial),
                  ErlNifMakeGbkBinary(env, data->TradeCode),
                  ErlNifMakeGbkBinary(env, data->BankID),
                  ErlNifMakeGbkBinary(env, data->BankBranchID),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->BrokerBranchID),
                  ErlNifMakeGbkBinary(env, data->TradeDate),
                  ErlNifMakeGbkBinary(env, data->TradeTime),
                  ErlNifMakeGbkBinary(env, data->BankSerial),
                  ErlNifMakeGbkBinary(env, data->TradingDay),
                  enif_make_int(env, data->PlateSerial),
                  ErlNifMakeGbkBinary(env, data->LastFragment),
                  enif_make_int(env, data->SessionID),
                  ErlNifMakeGbkBinary(env, data->CustomerName),
                  ErlNifMakeGbkBinary(env, data->IdCardType),
                  ErlNifMakeGbkBinary(env, data->IdentifiedCardNo),
                  ErlNifMakeGbkBinary(env, data->CustType),
                  ErlNifMakeGbkBinary(env, data->BankAccount),
                  ErlNifMakeGbkBinary(env, data->BankPassWord),
                  ErlNifMakeGbkBinary(env, data->AccountID),
                  ErlNifMakeGbkBinary(env, data->Password),
                  enif_make_int(env, data->InstallID),
                  enif_make_int(env, data->FutureSerial),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  ErlNifMakeGbkBinary(env, data->VerifyCertNoFlag),
                  ErlNifMakeGbkBinary(env, data->CurrencyID),
                  enif_make_double(env, data->TradeAmount),
                  enif_make_double(env, data->FutureFetchAmount),
                  ErlNifMakeGbkBinary(env, data->FeePayFlag),
                  enif_make_double(env, data->CustFee),
                  enif_make_double(env, data->BrokerFee),
                  ErlNifMakeGbkBinary(env, data->Message),
                  ErlNifMakeGbkBinary(env, data->Digest),
                  ErlNifMakeGbkBinary(env, data->BankAccType),
                  ErlNifMakeGbkBinary(env, data->DeviceID),
                  ErlNifMakeGbkBinary(env, data->BankSecuAccType),
                  ErlNifMakeGbkBinary(env, data->BrokerIDByBank),
                  ErlNifMakeGbkBinary(env, data->BankSecuAcc),
                  ErlNifMakeGbkBinary(env, data->BankPwdFlag),
                  ErlNifMakeGbkBinary(env, data->SecuPwdFlag),
                  ErlNifMakeGbkBinary(env, data->OperNo),
                  enif_make_int(env, data->RequestID),
                  enif_make_int(env, data->TID),
                  ErlNifMakeGbkBinary(env, data->TransferStatus),
                  enif_make_int(env, data->ErrorID),
                  ErlNifMakeGbkBinary(env, data->ErrorMsg)))));
  enif_free_env(env);
}

void CtpTd::OnRtnRepealFromFutureToBankByFutureManual(
    CThostFtdcRspRepealField *data) {
  static CThostFtdcRspRepealField empty_data = {};

  if (!data) {
    data = &empty_data;
  }

  ErlNifEnv *env = enif_alloc_env();
  enif_send(
      NULL, &this->pid_, env,
      enif_make_tuple2(
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple2(
              env,
              enif_make_atom(
                  env, "on_rtn_repeal_from_future_to_bank_by_future_manual"),
              enif_make_tuple(
                  env, 53, enif_make_atom(env, "cthost_ftdc_rsp_repeal_field"),
                  enif_make_int(env, data->RepealTimeInterval),
                  enif_make_int(env, data->RepealedTimes),
                  ErlNifMakeGbkBinary(env, data->BankRepealFlag),
                  ErlNifMakeGbkBinary(env, data->BrokerRepealFlag),
                  enif_make_int(env, data->PlateRepealSerial),
                  ErlNifMakeGbkBinary(env, data->BankRepealSerial),
                  enif_make_int(env, data->FutureRepealSerial),
                  ErlNifMakeGbkBinary(env, data->TradeCode),
                  ErlNifMakeGbkBinary(env, data->BankID),
                  ErlNifMakeGbkBinary(env, data->BankBranchID),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->BrokerBranchID),
                  ErlNifMakeGbkBinary(env, data->TradeDate),
                  ErlNifMakeGbkBinary(env, data->TradeTime),
                  ErlNifMakeGbkBinary(env, data->BankSerial),
                  ErlNifMakeGbkBinary(env, data->TradingDay),
                  enif_make_int(env, data->PlateSerial),
                  ErlNifMakeGbkBinary(env, data->LastFragment),
                  enif_make_int(env, data->SessionID),
                  ErlNifMakeGbkBinary(env, data->CustomerName),
                  ErlNifMakeGbkBinary(env, data->IdCardType),
                  ErlNifMakeGbkBinary(env, data->IdentifiedCardNo),
                  ErlNifMakeGbkBinary(env, data->CustType),
                  ErlNifMakeGbkBinary(env, data->BankAccount),
                  ErlNifMakeGbkBinary(env, data->BankPassWord),
                  ErlNifMakeGbkBinary(env, data->AccountID),
                  ErlNifMakeGbkBinary(env, data->Password),
                  enif_make_int(env, data->InstallID),
                  enif_make_int(env, data->FutureSerial),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  ErlNifMakeGbkBinary(env, data->VerifyCertNoFlag),
                  ErlNifMakeGbkBinary(env, data->CurrencyID),
                  enif_make_double(env, data->TradeAmount),
                  enif_make_double(env, data->FutureFetchAmount),
                  ErlNifMakeGbkBinary(env, data->FeePayFlag),
                  enif_make_double(env, data->CustFee),
                  enif_make_double(env, data->BrokerFee),
                  ErlNifMakeGbkBinary(env, data->Message),
                  ErlNifMakeGbkBinary(env, data->Digest),
                  ErlNifMakeGbkBinary(env, data->BankAccType),
                  ErlNifMakeGbkBinary(env, data->DeviceID),
                  ErlNifMakeGbkBinary(env, data->BankSecuAccType),
                  ErlNifMakeGbkBinary(env, data->BrokerIDByBank),
                  ErlNifMakeGbkBinary(env, data->BankSecuAcc),
                  ErlNifMakeGbkBinary(env, data->BankPwdFlag),
                  ErlNifMakeGbkBinary(env, data->SecuPwdFlag),
                  ErlNifMakeGbkBinary(env, data->OperNo),
                  enif_make_int(env, data->RequestID),
                  enif_make_int(env, data->TID),
                  ErlNifMakeGbkBinary(env, data->TransferStatus),
                  enif_make_int(env, data->ErrorID),
                  ErlNifMakeGbkBinary(env, data->ErrorMsg)))));
  enif_free_env(env);
}

void CtpTd::OnRtnQueryBankBalanceByFuture(
    CThostFtdcNotifyQueryAccountField *data) {
  static CThostFtdcNotifyQueryAccountField empty_data = {};

  if (!data) {
    data = &empty_data;
  }

  ErlNifEnv *env = enif_alloc_env();
  enif_send(
      NULL, &this->pid_, env,
      enif_make_tuple2(
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple2(
              env, enif_make_atom(env, "on_rtn_query_bank_balance_by_future"),
              enif_make_tuple(
                  env, 41,
                  enif_make_atom(env, "cthost_ftdc_notify_query_account_field"),
                  ErlNifMakeGbkBinary(env, data->TradeCode),
                  ErlNifMakeGbkBinary(env, data->BankID),
                  ErlNifMakeGbkBinary(env, data->BankBranchID),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->BrokerBranchID),
                  ErlNifMakeGbkBinary(env, data->TradeDate),
                  ErlNifMakeGbkBinary(env, data->TradeTime),
                  ErlNifMakeGbkBinary(env, data->BankSerial),
                  ErlNifMakeGbkBinary(env, data->TradingDay),
                  enif_make_int(env, data->PlateSerial),
                  ErlNifMakeGbkBinary(env, data->LastFragment),
                  enif_make_int(env, data->SessionID),
                  ErlNifMakeGbkBinary(env, data->CustomerName),
                  ErlNifMakeGbkBinary(env, data->IdCardType),
                  ErlNifMakeGbkBinary(env, data->IdentifiedCardNo),
                  ErlNifMakeGbkBinary(env, data->CustType),
                  ErlNifMakeGbkBinary(env, data->BankAccount),
                  ErlNifMakeGbkBinary(env, data->BankPassWord),
                  ErlNifMakeGbkBinary(env, data->AccountID),
                  ErlNifMakeGbkBinary(env, data->Password),
                  enif_make_int(env, data->FutureSerial),
                  enif_make_int(env, data->InstallID),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  ErlNifMakeGbkBinary(env, data->VerifyCertNoFlag),
                  ErlNifMakeGbkBinary(env, data->CurrencyID),
                  ErlNifMakeGbkBinary(env, data->Digest),
                  ErlNifMakeGbkBinary(env, data->BankAccType),
                  ErlNifMakeGbkBinary(env, data->DeviceID),
                  ErlNifMakeGbkBinary(env, data->BankSecuAccType),
                  ErlNifMakeGbkBinary(env, data->BrokerIDByBank),
                  ErlNifMakeGbkBinary(env, data->BankSecuAcc),
                  ErlNifMakeGbkBinary(env, data->BankPwdFlag),
                  ErlNifMakeGbkBinary(env, data->SecuPwdFlag),
                  ErlNifMakeGbkBinary(env, data->OperNo),
                  enif_make_int(env, data->RequestID),
                  enif_make_int(env, data->TID),
                  enif_make_double(env, data->BankUseAmount),
                  enif_make_double(env, data->BankFetchAmount),
                  enif_make_int(env, data->ErrorID),
                  ErlNifMakeGbkBinary(env, data->ErrorMsg)))));
  enif_free_env(env);
}

void CtpTd::OnErrRtnBankToFutureByFuture(CThostFtdcReqTransferField *data,
                                         CThostFtdcRspInfoField *error) {
  static CThostFtdcReqTransferField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple3(
              env, enif_make_atom(env, "on_err_rtn_bank_to_future_by_future"),
              enif_make_tuple(
                  env, 44,
                  enif_make_atom(env, "cthost_ftdc_req_transfer_field"),
                  ErlNifMakeGbkBinary(env, data->TradeCode),
                  ErlNifMakeGbkBinary(env, data->BankID),
                  ErlNifMakeGbkBinary(env, data->BankBranchID),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->BrokerBranchID),
                  ErlNifMakeGbkBinary(env, data->TradeDate),
                  ErlNifMakeGbkBinary(env, data->TradeTime),
                  ErlNifMakeGbkBinary(env, data->BankSerial),
                  ErlNifMakeGbkBinary(env, data->TradingDay),
                  enif_make_int(env, data->PlateSerial),
                  ErlNifMakeGbkBinary(env, data->LastFragment),
                  enif_make_int(env, data->SessionID),
                  ErlNifMakeGbkBinary(env, data->CustomerName),
                  ErlNifMakeGbkBinary(env, data->IdCardType),
                  ErlNifMakeGbkBinary(env, data->IdentifiedCardNo),
                  ErlNifMakeGbkBinary(env, data->CustType),
                  ErlNifMakeGbkBinary(env, data->BankAccount),
                  ErlNifMakeGbkBinary(env, data->BankPassWord),
                  ErlNifMakeGbkBinary(env, data->AccountID),
                  ErlNifMakeGbkBinary(env, data->Password),
                  enif_make_int(env, data->InstallID),
                  enif_make_int(env, data->FutureSerial),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  ErlNifMakeGbkBinary(env, data->VerifyCertNoFlag),
                  ErlNifMakeGbkBinary(env, data->CurrencyID),
                  enif_make_double(env, data->TradeAmount),
                  enif_make_double(env, data->FutureFetchAmount),
                  ErlNifMakeGbkBinary(env, data->FeePayFlag),
                  enif_make_double(env, data->CustFee),
                  enif_make_double(env, data->BrokerFee),
                  ErlNifMakeGbkBinary(env, data->Message),
                  ErlNifMakeGbkBinary(env, data->Digest),
                  ErlNifMakeGbkBinary(env, data->BankAccType),
                  ErlNifMakeGbkBinary(env, data->DeviceID),
                  ErlNifMakeGbkBinary(env, data->BankSecuAccType),
                  ErlNifMakeGbkBinary(env, data->BrokerIDByBank),
                  ErlNifMakeGbkBinary(env, data->BankSecuAcc),
                  ErlNifMakeGbkBinary(env, data->BankPwdFlag),
                  ErlNifMakeGbkBinary(env, data->SecuPwdFlag),
                  ErlNifMakeGbkBinary(env, data->OperNo),
                  enif_make_int(env, data->RequestID),
                  enif_make_int(env, data->TID),
                  ErlNifMakeGbkBinary(env, data->TransferStatus)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)))));
  enif_free_env(env);
}

void CtpTd::OnErrRtnFutureToBankByFuture(CThostFtdcReqTransferField *data,
                                         CThostFtdcRspInfoField *error) {
  static CThostFtdcReqTransferField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple3(
              env, enif_make_atom(env, "on_err_rtn_future_to_bank_by_future"),
              enif_make_tuple(
                  env, 44,
                  enif_make_atom(env, "cthost_ftdc_req_transfer_field"),
                  ErlNifMakeGbkBinary(env, data->TradeCode),
                  ErlNifMakeGbkBinary(env, data->BankID),
                  ErlNifMakeGbkBinary(env, data->BankBranchID),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->BrokerBranchID),
                  ErlNifMakeGbkBinary(env, data->TradeDate),
                  ErlNifMakeGbkBinary(env, data->TradeTime),
                  ErlNifMakeGbkBinary(env, data->BankSerial),
                  ErlNifMakeGbkBinary(env, data->TradingDay),
                  enif_make_int(env, data->PlateSerial),
                  ErlNifMakeGbkBinary(env, data->LastFragment),
                  enif_make_int(env, data->SessionID),
                  ErlNifMakeGbkBinary(env, data->CustomerName),
                  ErlNifMakeGbkBinary(env, data->IdCardType),
                  ErlNifMakeGbkBinary(env, data->IdentifiedCardNo),
                  ErlNifMakeGbkBinary(env, data->CustType),
                  ErlNifMakeGbkBinary(env, data->BankAccount),
                  ErlNifMakeGbkBinary(env, data->BankPassWord),
                  ErlNifMakeGbkBinary(env, data->AccountID),
                  ErlNifMakeGbkBinary(env, data->Password),
                  enif_make_int(env, data->InstallID),
                  enif_make_int(env, data->FutureSerial),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  ErlNifMakeGbkBinary(env, data->VerifyCertNoFlag),
                  ErlNifMakeGbkBinary(env, data->CurrencyID),
                  enif_make_double(env, data->TradeAmount),
                  enif_make_double(env, data->FutureFetchAmount),
                  ErlNifMakeGbkBinary(env, data->FeePayFlag),
                  enif_make_double(env, data->CustFee),
                  enif_make_double(env, data->BrokerFee),
                  ErlNifMakeGbkBinary(env, data->Message),
                  ErlNifMakeGbkBinary(env, data->Digest),
                  ErlNifMakeGbkBinary(env, data->BankAccType),
                  ErlNifMakeGbkBinary(env, data->DeviceID),
                  ErlNifMakeGbkBinary(env, data->BankSecuAccType),
                  ErlNifMakeGbkBinary(env, data->BrokerIDByBank),
                  ErlNifMakeGbkBinary(env, data->BankSecuAcc),
                  ErlNifMakeGbkBinary(env, data->BankPwdFlag),
                  ErlNifMakeGbkBinary(env, data->SecuPwdFlag),
                  ErlNifMakeGbkBinary(env, data->OperNo),
                  enif_make_int(env, data->RequestID),
                  enif_make_int(env, data->TID),
                  ErlNifMakeGbkBinary(env, data->TransferStatus)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)))));
  enif_free_env(env);
}

void CtpTd::OnErrRtnRepealBankToFutureByFutureManual(
    CThostFtdcReqRepealField *data, CThostFtdcRspInfoField *error) {
  static CThostFtdcReqRepealField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple3(
              env,
              enif_make_atom(
                  env, "on_err_rtn_repeal_bank_to_future_by_future_manual"),
              enif_make_tuple(
                  env, 51, enif_make_atom(env, "cthost_ftdc_req_repeal_field"),
                  enif_make_int(env, data->RepealTimeInterval),
                  enif_make_int(env, data->RepealedTimes),
                  ErlNifMakeGbkBinary(env, data->BankRepealFlag),
                  ErlNifMakeGbkBinary(env, data->BrokerRepealFlag),
                  enif_make_int(env, data->PlateRepealSerial),
                  ErlNifMakeGbkBinary(env, data->BankRepealSerial),
                  enif_make_int(env, data->FutureRepealSerial),
                  ErlNifMakeGbkBinary(env, data->TradeCode),
                  ErlNifMakeGbkBinary(env, data->BankID),
                  ErlNifMakeGbkBinary(env, data->BankBranchID),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->BrokerBranchID),
                  ErlNifMakeGbkBinary(env, data->TradeDate),
                  ErlNifMakeGbkBinary(env, data->TradeTime),
                  ErlNifMakeGbkBinary(env, data->BankSerial),
                  ErlNifMakeGbkBinary(env, data->TradingDay),
                  enif_make_int(env, data->PlateSerial),
                  ErlNifMakeGbkBinary(env, data->LastFragment),
                  enif_make_int(env, data->SessionID),
                  ErlNifMakeGbkBinary(env, data->CustomerName),
                  ErlNifMakeGbkBinary(env, data->IdCardType),
                  ErlNifMakeGbkBinary(env, data->IdentifiedCardNo),
                  ErlNifMakeGbkBinary(env, data->CustType),
                  ErlNifMakeGbkBinary(env, data->BankAccount),
                  ErlNifMakeGbkBinary(env, data->BankPassWord),
                  ErlNifMakeGbkBinary(env, data->AccountID),
                  ErlNifMakeGbkBinary(env, data->Password),
                  enif_make_int(env, data->InstallID),
                  enif_make_int(env, data->FutureSerial),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  ErlNifMakeGbkBinary(env, data->VerifyCertNoFlag),
                  ErlNifMakeGbkBinary(env, data->CurrencyID),
                  enif_make_double(env, data->TradeAmount),
                  enif_make_double(env, data->FutureFetchAmount),
                  ErlNifMakeGbkBinary(env, data->FeePayFlag),
                  enif_make_double(env, data->CustFee),
                  enif_make_double(env, data->BrokerFee),
                  ErlNifMakeGbkBinary(env, data->Message),
                  ErlNifMakeGbkBinary(env, data->Digest),
                  ErlNifMakeGbkBinary(env, data->BankAccType),
                  ErlNifMakeGbkBinary(env, data->DeviceID),
                  ErlNifMakeGbkBinary(env, data->BankSecuAccType),
                  ErlNifMakeGbkBinary(env, data->BrokerIDByBank),
                  ErlNifMakeGbkBinary(env, data->BankSecuAcc),
                  ErlNifMakeGbkBinary(env, data->BankPwdFlag),
                  ErlNifMakeGbkBinary(env, data->SecuPwdFlag),
                  ErlNifMakeGbkBinary(env, data->OperNo),
                  enif_make_int(env, data->RequestID),
                  enif_make_int(env, data->TID),
                  ErlNifMakeGbkBinary(env, data->TransferStatus)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)))));
  enif_free_env(env);
}

void CtpTd::OnErrRtnRepealFutureToBankByFutureManual(
    CThostFtdcReqRepealField *data, CThostFtdcRspInfoField *error) {
  static CThostFtdcReqRepealField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple3(
              env,
              enif_make_atom(
                  env, "on_err_rtn_repeal_future_to_bank_by_future_manual"),
              enif_make_tuple(
                  env, 51, enif_make_atom(env, "cthost_ftdc_req_repeal_field"),
                  enif_make_int(env, data->RepealTimeInterval),
                  enif_make_int(env, data->RepealedTimes),
                  ErlNifMakeGbkBinary(env, data->BankRepealFlag),
                  ErlNifMakeGbkBinary(env, data->BrokerRepealFlag),
                  enif_make_int(env, data->PlateRepealSerial),
                  ErlNifMakeGbkBinary(env, data->BankRepealSerial),
                  enif_make_int(env, data->FutureRepealSerial),
                  ErlNifMakeGbkBinary(env, data->TradeCode),
                  ErlNifMakeGbkBinary(env, data->BankID),
                  ErlNifMakeGbkBinary(env, data->BankBranchID),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->BrokerBranchID),
                  ErlNifMakeGbkBinary(env, data->TradeDate),
                  ErlNifMakeGbkBinary(env, data->TradeTime),
                  ErlNifMakeGbkBinary(env, data->BankSerial),
                  ErlNifMakeGbkBinary(env, data->TradingDay),
                  enif_make_int(env, data->PlateSerial),
                  ErlNifMakeGbkBinary(env, data->LastFragment),
                  enif_make_int(env, data->SessionID),
                  ErlNifMakeGbkBinary(env, data->CustomerName),
                  ErlNifMakeGbkBinary(env, data->IdCardType),
                  ErlNifMakeGbkBinary(env, data->IdentifiedCardNo),
                  ErlNifMakeGbkBinary(env, data->CustType),
                  ErlNifMakeGbkBinary(env, data->BankAccount),
                  ErlNifMakeGbkBinary(env, data->BankPassWord),
                  ErlNifMakeGbkBinary(env, data->AccountID),
                  ErlNifMakeGbkBinary(env, data->Password),
                  enif_make_int(env, data->InstallID),
                  enif_make_int(env, data->FutureSerial),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  ErlNifMakeGbkBinary(env, data->VerifyCertNoFlag),
                  ErlNifMakeGbkBinary(env, data->CurrencyID),
                  enif_make_double(env, data->TradeAmount),
                  enif_make_double(env, data->FutureFetchAmount),
                  ErlNifMakeGbkBinary(env, data->FeePayFlag),
                  enif_make_double(env, data->CustFee),
                  enif_make_double(env, data->BrokerFee),
                  ErlNifMakeGbkBinary(env, data->Message),
                  ErlNifMakeGbkBinary(env, data->Digest),
                  ErlNifMakeGbkBinary(env, data->BankAccType),
                  ErlNifMakeGbkBinary(env, data->DeviceID),
                  ErlNifMakeGbkBinary(env, data->BankSecuAccType),
                  ErlNifMakeGbkBinary(env, data->BrokerIDByBank),
                  ErlNifMakeGbkBinary(env, data->BankSecuAcc),
                  ErlNifMakeGbkBinary(env, data->BankPwdFlag),
                  ErlNifMakeGbkBinary(env, data->SecuPwdFlag),
                  ErlNifMakeGbkBinary(env, data->OperNo),
                  enif_make_int(env, data->RequestID),
                  enif_make_int(env, data->TID),
                  ErlNifMakeGbkBinary(env, data->TransferStatus)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)))));
  enif_free_env(env);
}

void CtpTd::OnErrRtnQueryBankBalanceByFuture(
    CThostFtdcReqQueryAccountField *data, CThostFtdcRspInfoField *error) {
  static CThostFtdcReqQueryAccountField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple3(
              env,
              enif_make_atom(env, "on_err_rtn_query_bank_balance_by_future"),
              enif_make_tuple(
                  env, 37,
                  enif_make_atom(env, "cthost_ftdc_req_query_account_field"),
                  ErlNifMakeGbkBinary(env, data->TradeCode),
                  ErlNifMakeGbkBinary(env, data->BankID),
                  ErlNifMakeGbkBinary(env, data->BankBranchID),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->BrokerBranchID),
                  ErlNifMakeGbkBinary(env, data->TradeDate),
                  ErlNifMakeGbkBinary(env, data->TradeTime),
                  ErlNifMakeGbkBinary(env, data->BankSerial),
                  ErlNifMakeGbkBinary(env, data->TradingDay),
                  enif_make_int(env, data->PlateSerial),
                  ErlNifMakeGbkBinary(env, data->LastFragment),
                  enif_make_int(env, data->SessionID),
                  ErlNifMakeGbkBinary(env, data->CustomerName),
                  ErlNifMakeGbkBinary(env, data->IdCardType),
                  ErlNifMakeGbkBinary(env, data->IdentifiedCardNo),
                  ErlNifMakeGbkBinary(env, data->CustType),
                  ErlNifMakeGbkBinary(env, data->BankAccount),
                  ErlNifMakeGbkBinary(env, data->BankPassWord),
                  ErlNifMakeGbkBinary(env, data->AccountID),
                  ErlNifMakeGbkBinary(env, data->Password),
                  enif_make_int(env, data->FutureSerial),
                  enif_make_int(env, data->InstallID),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  ErlNifMakeGbkBinary(env, data->VerifyCertNoFlag),
                  ErlNifMakeGbkBinary(env, data->CurrencyID),
                  ErlNifMakeGbkBinary(env, data->Digest),
                  ErlNifMakeGbkBinary(env, data->BankAccType),
                  ErlNifMakeGbkBinary(env, data->DeviceID),
                  ErlNifMakeGbkBinary(env, data->BankSecuAccType),
                  ErlNifMakeGbkBinary(env, data->BrokerIDByBank),
                  ErlNifMakeGbkBinary(env, data->BankSecuAcc),
                  ErlNifMakeGbkBinary(env, data->BankPwdFlag),
                  ErlNifMakeGbkBinary(env, data->SecuPwdFlag),
                  ErlNifMakeGbkBinary(env, data->OperNo),
                  enif_make_int(env, data->RequestID),
                  enif_make_int(env, data->TID)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)))));
  enif_free_env(env);
}

void CtpTd::OnRtnRepealFromBankToFutureByFuture(
    CThostFtdcRspRepealField *data) {
  static CThostFtdcRspRepealField empty_data = {};

  if (!data) {
    data = &empty_data;
  }

  ErlNifEnv *env = enif_alloc_env();
  enif_send(
      NULL, &this->pid_, env,
      enif_make_tuple2(
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple2(
              env,
              enif_make_atom(env,
                             "on_rtn_repeal_from_bank_to_future_by_future"),
              enif_make_tuple(
                  env, 53, enif_make_atom(env, "cthost_ftdc_rsp_repeal_field"),
                  enif_make_int(env, data->RepealTimeInterval),
                  enif_make_int(env, data->RepealedTimes),
                  ErlNifMakeGbkBinary(env, data->BankRepealFlag),
                  ErlNifMakeGbkBinary(env, data->BrokerRepealFlag),
                  enif_make_int(env, data->PlateRepealSerial),
                  ErlNifMakeGbkBinary(env, data->BankRepealSerial),
                  enif_make_int(env, data->FutureRepealSerial),
                  ErlNifMakeGbkBinary(env, data->TradeCode),
                  ErlNifMakeGbkBinary(env, data->BankID),
                  ErlNifMakeGbkBinary(env, data->BankBranchID),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->BrokerBranchID),
                  ErlNifMakeGbkBinary(env, data->TradeDate),
                  ErlNifMakeGbkBinary(env, data->TradeTime),
                  ErlNifMakeGbkBinary(env, data->BankSerial),
                  ErlNifMakeGbkBinary(env, data->TradingDay),
                  enif_make_int(env, data->PlateSerial),
                  ErlNifMakeGbkBinary(env, data->LastFragment),
                  enif_make_int(env, data->SessionID),
                  ErlNifMakeGbkBinary(env, data->CustomerName),
                  ErlNifMakeGbkBinary(env, data->IdCardType),
                  ErlNifMakeGbkBinary(env, data->IdentifiedCardNo),
                  ErlNifMakeGbkBinary(env, data->CustType),
                  ErlNifMakeGbkBinary(env, data->BankAccount),
                  ErlNifMakeGbkBinary(env, data->BankPassWord),
                  ErlNifMakeGbkBinary(env, data->AccountID),
                  ErlNifMakeGbkBinary(env, data->Password),
                  enif_make_int(env, data->InstallID),
                  enif_make_int(env, data->FutureSerial),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  ErlNifMakeGbkBinary(env, data->VerifyCertNoFlag),
                  ErlNifMakeGbkBinary(env, data->CurrencyID),
                  enif_make_double(env, data->TradeAmount),
                  enif_make_double(env, data->FutureFetchAmount),
                  ErlNifMakeGbkBinary(env, data->FeePayFlag),
                  enif_make_double(env, data->CustFee),
                  enif_make_double(env, data->BrokerFee),
                  ErlNifMakeGbkBinary(env, data->Message),
                  ErlNifMakeGbkBinary(env, data->Digest),
                  ErlNifMakeGbkBinary(env, data->BankAccType),
                  ErlNifMakeGbkBinary(env, data->DeviceID),
                  ErlNifMakeGbkBinary(env, data->BankSecuAccType),
                  ErlNifMakeGbkBinary(env, data->BrokerIDByBank),
                  ErlNifMakeGbkBinary(env, data->BankSecuAcc),
                  ErlNifMakeGbkBinary(env, data->BankPwdFlag),
                  ErlNifMakeGbkBinary(env, data->SecuPwdFlag),
                  ErlNifMakeGbkBinary(env, data->OperNo),
                  enif_make_int(env, data->RequestID),
                  enif_make_int(env, data->TID),
                  ErlNifMakeGbkBinary(env, data->TransferStatus),
                  enif_make_int(env, data->ErrorID),
                  ErlNifMakeGbkBinary(env, data->ErrorMsg)))));
  enif_free_env(env);
}

void CtpTd::OnRtnRepealFromFutureToBankByFuture(
    CThostFtdcRspRepealField *data) {
  static CThostFtdcRspRepealField empty_data = {};

  if (!data) {
    data = &empty_data;
  }

  ErlNifEnv *env = enif_alloc_env();
  enif_send(
      NULL, &this->pid_, env,
      enif_make_tuple2(
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple2(
              env,
              enif_make_atom(env,
                             "on_rtn_repeal_from_future_to_bank_by_future"),
              enif_make_tuple(
                  env, 53, enif_make_atom(env, "cthost_ftdc_rsp_repeal_field"),
                  enif_make_int(env, data->RepealTimeInterval),
                  enif_make_int(env, data->RepealedTimes),
                  ErlNifMakeGbkBinary(env, data->BankRepealFlag),
                  ErlNifMakeGbkBinary(env, data->BrokerRepealFlag),
                  enif_make_int(env, data->PlateRepealSerial),
                  ErlNifMakeGbkBinary(env, data->BankRepealSerial),
                  enif_make_int(env, data->FutureRepealSerial),
                  ErlNifMakeGbkBinary(env, data->TradeCode),
                  ErlNifMakeGbkBinary(env, data->BankID),
                  ErlNifMakeGbkBinary(env, data->BankBranchID),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->BrokerBranchID),
                  ErlNifMakeGbkBinary(env, data->TradeDate),
                  ErlNifMakeGbkBinary(env, data->TradeTime),
                  ErlNifMakeGbkBinary(env, data->BankSerial),
                  ErlNifMakeGbkBinary(env, data->TradingDay),
                  enif_make_int(env, data->PlateSerial),
                  ErlNifMakeGbkBinary(env, data->LastFragment),
                  enif_make_int(env, data->SessionID),
                  ErlNifMakeGbkBinary(env, data->CustomerName),
                  ErlNifMakeGbkBinary(env, data->IdCardType),
                  ErlNifMakeGbkBinary(env, data->IdentifiedCardNo),
                  ErlNifMakeGbkBinary(env, data->CustType),
                  ErlNifMakeGbkBinary(env, data->BankAccount),
                  ErlNifMakeGbkBinary(env, data->BankPassWord),
                  ErlNifMakeGbkBinary(env, data->AccountID),
                  ErlNifMakeGbkBinary(env, data->Password),
                  enif_make_int(env, data->InstallID),
                  enif_make_int(env, data->FutureSerial),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  ErlNifMakeGbkBinary(env, data->VerifyCertNoFlag),
                  ErlNifMakeGbkBinary(env, data->CurrencyID),
                  enif_make_double(env, data->TradeAmount),
                  enif_make_double(env, data->FutureFetchAmount),
                  ErlNifMakeGbkBinary(env, data->FeePayFlag),
                  enif_make_double(env, data->CustFee),
                  enif_make_double(env, data->BrokerFee),
                  ErlNifMakeGbkBinary(env, data->Message),
                  ErlNifMakeGbkBinary(env, data->Digest),
                  ErlNifMakeGbkBinary(env, data->BankAccType),
                  ErlNifMakeGbkBinary(env, data->DeviceID),
                  ErlNifMakeGbkBinary(env, data->BankSecuAccType),
                  ErlNifMakeGbkBinary(env, data->BrokerIDByBank),
                  ErlNifMakeGbkBinary(env, data->BankSecuAcc),
                  ErlNifMakeGbkBinary(env, data->BankPwdFlag),
                  ErlNifMakeGbkBinary(env, data->SecuPwdFlag),
                  ErlNifMakeGbkBinary(env, data->OperNo),
                  enif_make_int(env, data->RequestID),
                  enif_make_int(env, data->TID),
                  ErlNifMakeGbkBinary(env, data->TransferStatus),
                  enif_make_int(env, data->ErrorID),
                  ErlNifMakeGbkBinary(env, data->ErrorMsg)))));
  enif_free_env(env);
}

void CtpTd::OnRspFromBankToFutureByFuture(CThostFtdcReqTransferField *data,
                                          CThostFtdcRspInfoField *error,
                                          int req_id, bool last) {
  static CThostFtdcReqTransferField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_from_bank_to_future_by_future"),
              enif_make_tuple(
                  env, 44,
                  enif_make_atom(env, "cthost_ftdc_req_transfer_field"),
                  ErlNifMakeGbkBinary(env, data->TradeCode),
                  ErlNifMakeGbkBinary(env, data->BankID),
                  ErlNifMakeGbkBinary(env, data->BankBranchID),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->BrokerBranchID),
                  ErlNifMakeGbkBinary(env, data->TradeDate),
                  ErlNifMakeGbkBinary(env, data->TradeTime),
                  ErlNifMakeGbkBinary(env, data->BankSerial),
                  ErlNifMakeGbkBinary(env, data->TradingDay),
                  enif_make_int(env, data->PlateSerial),
                  ErlNifMakeGbkBinary(env, data->LastFragment),
                  enif_make_int(env, data->SessionID),
                  ErlNifMakeGbkBinary(env, data->CustomerName),
                  ErlNifMakeGbkBinary(env, data->IdCardType),
                  ErlNifMakeGbkBinary(env, data->IdentifiedCardNo),
                  ErlNifMakeGbkBinary(env, data->CustType),
                  ErlNifMakeGbkBinary(env, data->BankAccount),
                  ErlNifMakeGbkBinary(env, data->BankPassWord),
                  ErlNifMakeGbkBinary(env, data->AccountID),
                  ErlNifMakeGbkBinary(env, data->Password),
                  enif_make_int(env, data->InstallID),
                  enif_make_int(env, data->FutureSerial),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  ErlNifMakeGbkBinary(env, data->VerifyCertNoFlag),
                  ErlNifMakeGbkBinary(env, data->CurrencyID),
                  enif_make_double(env, data->TradeAmount),
                  enif_make_double(env, data->FutureFetchAmount),
                  ErlNifMakeGbkBinary(env, data->FeePayFlag),
                  enif_make_double(env, data->CustFee),
                  enif_make_double(env, data->BrokerFee),
                  ErlNifMakeGbkBinary(env, data->Message),
                  ErlNifMakeGbkBinary(env, data->Digest),
                  ErlNifMakeGbkBinary(env, data->BankAccType),
                  ErlNifMakeGbkBinary(env, data->DeviceID),
                  ErlNifMakeGbkBinary(env, data->BankSecuAccType),
                  ErlNifMakeGbkBinary(env, data->BrokerIDByBank),
                  ErlNifMakeGbkBinary(env, data->BankSecuAcc),
                  ErlNifMakeGbkBinary(env, data->BankPwdFlag),
                  ErlNifMakeGbkBinary(env, data->SecuPwdFlag),
                  ErlNifMakeGbkBinary(env, data->OperNo),
                  enif_make_int(env, data->RequestID),
                  enif_make_int(env, data->TID),
                  ErlNifMakeGbkBinary(env, data->TransferStatus)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspFromFutureToBankByFuture(CThostFtdcReqTransferField *data,
                                          CThostFtdcRspInfoField *error,
                                          int req_id, bool last) {
  static CThostFtdcReqTransferField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env, enif_make_atom(env, "on_rsp_from_future_to_bank_by_future"),
              enif_make_tuple(
                  env, 44,
                  enif_make_atom(env, "cthost_ftdc_req_transfer_field"),
                  ErlNifMakeGbkBinary(env, data->TradeCode),
                  ErlNifMakeGbkBinary(env, data->BankID),
                  ErlNifMakeGbkBinary(env, data->BankBranchID),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->BrokerBranchID),
                  ErlNifMakeGbkBinary(env, data->TradeDate),
                  ErlNifMakeGbkBinary(env, data->TradeTime),
                  ErlNifMakeGbkBinary(env, data->BankSerial),
                  ErlNifMakeGbkBinary(env, data->TradingDay),
                  enif_make_int(env, data->PlateSerial),
                  ErlNifMakeGbkBinary(env, data->LastFragment),
                  enif_make_int(env, data->SessionID),
                  ErlNifMakeGbkBinary(env, data->CustomerName),
                  ErlNifMakeGbkBinary(env, data->IdCardType),
                  ErlNifMakeGbkBinary(env, data->IdentifiedCardNo),
                  ErlNifMakeGbkBinary(env, data->CustType),
                  ErlNifMakeGbkBinary(env, data->BankAccount),
                  ErlNifMakeGbkBinary(env, data->BankPassWord),
                  ErlNifMakeGbkBinary(env, data->AccountID),
                  ErlNifMakeGbkBinary(env, data->Password),
                  enif_make_int(env, data->InstallID),
                  enif_make_int(env, data->FutureSerial),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  ErlNifMakeGbkBinary(env, data->VerifyCertNoFlag),
                  ErlNifMakeGbkBinary(env, data->CurrencyID),
                  enif_make_double(env, data->TradeAmount),
                  enif_make_double(env, data->FutureFetchAmount),
                  ErlNifMakeGbkBinary(env, data->FeePayFlag),
                  enif_make_double(env, data->CustFee),
                  enif_make_double(env, data->BrokerFee),
                  ErlNifMakeGbkBinary(env, data->Message),
                  ErlNifMakeGbkBinary(env, data->Digest),
                  ErlNifMakeGbkBinary(env, data->BankAccType),
                  ErlNifMakeGbkBinary(env, data->DeviceID),
                  ErlNifMakeGbkBinary(env, data->BankSecuAccType),
                  ErlNifMakeGbkBinary(env, data->BrokerIDByBank),
                  ErlNifMakeGbkBinary(env, data->BankSecuAcc),
                  ErlNifMakeGbkBinary(env, data->BankPwdFlag),
                  ErlNifMakeGbkBinary(env, data->SecuPwdFlag),
                  ErlNifMakeGbkBinary(env, data->OperNo),
                  enif_make_int(env, data->RequestID),
                  enif_make_int(env, data->TID),
                  ErlNifMakeGbkBinary(env, data->TransferStatus)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRspQueryBankAccountMoneyByFuture(
    CThostFtdcReqQueryAccountField *data, CThostFtdcRspInfoField *error,
    int req_id, bool last) {
  static CThostFtdcReqQueryAccountField empty_data = {};
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
          env, enif_make_atom(env, "ctp_td"),
          enif_make_tuple5(
              env,
              enif_make_atom(env, "on_rsp_query_bank_account_money_by_future"),
              enif_make_tuple(
                  env, 37,
                  enif_make_atom(env, "cthost_ftdc_req_query_account_field"),
                  ErlNifMakeGbkBinary(env, data->TradeCode),
                  ErlNifMakeGbkBinary(env, data->BankID),
                  ErlNifMakeGbkBinary(env, data->BankBranchID),
                  ErlNifMakeGbkBinary(env, data->BrokerID),
                  ErlNifMakeGbkBinary(env, data->BrokerBranchID),
                  ErlNifMakeGbkBinary(env, data->TradeDate),
                  ErlNifMakeGbkBinary(env, data->TradeTime),
                  ErlNifMakeGbkBinary(env, data->BankSerial),
                  ErlNifMakeGbkBinary(env, data->TradingDay),
                  enif_make_int(env, data->PlateSerial),
                  ErlNifMakeGbkBinary(env, data->LastFragment),
                  enif_make_int(env, data->SessionID),
                  ErlNifMakeGbkBinary(env, data->CustomerName),
                  ErlNifMakeGbkBinary(env, data->IdCardType),
                  ErlNifMakeGbkBinary(env, data->IdentifiedCardNo),
                  ErlNifMakeGbkBinary(env, data->CustType),
                  ErlNifMakeGbkBinary(env, data->BankAccount),
                  ErlNifMakeGbkBinary(env, data->BankPassWord),
                  ErlNifMakeGbkBinary(env, data->AccountID),
                  ErlNifMakeGbkBinary(env, data->Password),
                  enif_make_int(env, data->FutureSerial),
                  enif_make_int(env, data->InstallID),
                  ErlNifMakeGbkBinary(env, data->UserID),
                  ErlNifMakeGbkBinary(env, data->VerifyCertNoFlag),
                  ErlNifMakeGbkBinary(env, data->CurrencyID),
                  ErlNifMakeGbkBinary(env, data->Digest),
                  ErlNifMakeGbkBinary(env, data->BankAccType),
                  ErlNifMakeGbkBinary(env, data->DeviceID),
                  ErlNifMakeGbkBinary(env, data->BankSecuAccType),
                  ErlNifMakeGbkBinary(env, data->BrokerIDByBank),
                  ErlNifMakeGbkBinary(env, data->BankSecuAcc),
                  ErlNifMakeGbkBinary(env, data->BankPwdFlag),
                  ErlNifMakeGbkBinary(env, data->SecuPwdFlag),
                  ErlNifMakeGbkBinary(env, data->OperNo),
                  enif_make_int(env, data->RequestID),
                  enif_make_int(env, data->TID)),
              enif_make_tuple(env, 3,
                              enif_make_atom(env, "cthost_ftdc_rsp_info_field"),
                              enif_make_int(env, error->ErrorID),
                              ErlNifMakeGbkBinary(env, error->ErrorMsg)),
              enif_make_int(env, req_id),
              enif_make_atom(env, last ? "true" : "false"))));
  enif_free_env(env);
}

void CtpTd::OnRtnOpenAccountByBank(CThostFtdcOpenAccountField *data) {
  static CThostFtdcOpenAccountField empty_data = {};

  if (!data) {
    data = &empty_data;
  }

  ErlNifEnv *env = enif_alloc_env();
  enif_send(NULL, &this->pid_, env,
            enif_make_tuple2(
                env, enif_make_atom(env, "ctp_td"),
                enif_make_tuple2(
                    env, enif_make_atom(env, "on_rtn_open_account_by_bank"),
                    enif_make_tuple(
                        env, 47,
                        enif_make_atom(env, "cthost_ftdc_open_account_field"),
                        ErlNifMakeGbkBinary(env, data->TradeCode),
                        ErlNifMakeGbkBinary(env, data->BankID),
                        ErlNifMakeGbkBinary(env, data->BankBranchID),
                        ErlNifMakeGbkBinary(env, data->BrokerID),
                        ErlNifMakeGbkBinary(env, data->BrokerBranchID),
                        ErlNifMakeGbkBinary(env, data->TradeDate),
                        ErlNifMakeGbkBinary(env, data->TradeTime),
                        ErlNifMakeGbkBinary(env, data->BankSerial),
                        ErlNifMakeGbkBinary(env, data->TradingDay),
                        enif_make_int(env, data->PlateSerial),
                        ErlNifMakeGbkBinary(env, data->LastFragment),
                        enif_make_int(env, data->SessionID),
                        ErlNifMakeGbkBinary(env, data->CustomerName),
                        ErlNifMakeGbkBinary(env, data->IdCardType),
                        ErlNifMakeGbkBinary(env, data->IdentifiedCardNo),
                        ErlNifMakeGbkBinary(env, data->Gender),
                        ErlNifMakeGbkBinary(env, data->CountryCode),
                        ErlNifMakeGbkBinary(env, data->CustType),
                        ErlNifMakeGbkBinary(env, data->Address),
                        ErlNifMakeGbkBinary(env, data->ZipCode),
                        ErlNifMakeGbkBinary(env, data->Telephone),
                        ErlNifMakeGbkBinary(env, data->MobilePhone),
                        ErlNifMakeGbkBinary(env, data->Fax),
                        ErlNifMakeGbkBinary(env, data->EMail),
                        ErlNifMakeGbkBinary(env, data->MoneyAccountStatus),
                        ErlNifMakeGbkBinary(env, data->BankAccount),
                        ErlNifMakeGbkBinary(env, data->BankPassWord),
                        ErlNifMakeGbkBinary(env, data->AccountID),
                        ErlNifMakeGbkBinary(env, data->Password),
                        enif_make_int(env, data->InstallID),
                        ErlNifMakeGbkBinary(env, data->VerifyCertNoFlag),
                        ErlNifMakeGbkBinary(env, data->CurrencyID),
                        ErlNifMakeGbkBinary(env, data->CashExchangeCode),
                        ErlNifMakeGbkBinary(env, data->Digest),
                        ErlNifMakeGbkBinary(env, data->BankAccType),
                        ErlNifMakeGbkBinary(env, data->DeviceID),
                        ErlNifMakeGbkBinary(env, data->BankSecuAccType),
                        ErlNifMakeGbkBinary(env, data->BrokerIDByBank),
                        ErlNifMakeGbkBinary(env, data->BankSecuAcc),
                        ErlNifMakeGbkBinary(env, data->BankPwdFlag),
                        ErlNifMakeGbkBinary(env, data->SecuPwdFlag),
                        ErlNifMakeGbkBinary(env, data->OperNo),
                        enif_make_int(env, data->TID),
                        ErlNifMakeGbkBinary(env, data->UserID),
                        enif_make_int(env, data->ErrorID),
                        ErlNifMakeGbkBinary(env, data->ErrorMsg)))));
  enif_free_env(env);
}

void CtpTd::OnRtnCancelAccountByBank(CThostFtdcCancelAccountField *data) {
  static CThostFtdcCancelAccountField empty_data = {};

  if (!data) {
    data = &empty_data;
  }

  ErlNifEnv *env = enif_alloc_env();
  enif_send(NULL, &this->pid_, env,
            enif_make_tuple2(
                env, enif_make_atom(env, "ctp_td"),
                enif_make_tuple2(
                    env, enif_make_atom(env, "on_rtn_cancel_account_by_bank"),
                    enif_make_tuple(
                        env, 47,
                        enif_make_atom(env, "cthost_ftdc_cancel_account_field"),
                        ErlNifMakeGbkBinary(env, data->TradeCode),
                        ErlNifMakeGbkBinary(env, data->BankID),
                        ErlNifMakeGbkBinary(env, data->BankBranchID),
                        ErlNifMakeGbkBinary(env, data->BrokerID),
                        ErlNifMakeGbkBinary(env, data->BrokerBranchID),
                        ErlNifMakeGbkBinary(env, data->TradeDate),
                        ErlNifMakeGbkBinary(env, data->TradeTime),
                        ErlNifMakeGbkBinary(env, data->BankSerial),
                        ErlNifMakeGbkBinary(env, data->TradingDay),
                        enif_make_int(env, data->PlateSerial),
                        ErlNifMakeGbkBinary(env, data->LastFragment),
                        enif_make_int(env, data->SessionID),
                        ErlNifMakeGbkBinary(env, data->CustomerName),
                        ErlNifMakeGbkBinary(env, data->IdCardType),
                        ErlNifMakeGbkBinary(env, data->IdentifiedCardNo),
                        ErlNifMakeGbkBinary(env, data->Gender),
                        ErlNifMakeGbkBinary(env, data->CountryCode),
                        ErlNifMakeGbkBinary(env, data->CustType),
                        ErlNifMakeGbkBinary(env, data->Address),
                        ErlNifMakeGbkBinary(env, data->ZipCode),
                        ErlNifMakeGbkBinary(env, data->Telephone),
                        ErlNifMakeGbkBinary(env, data->MobilePhone),
                        ErlNifMakeGbkBinary(env, data->Fax),
                        ErlNifMakeGbkBinary(env, data->EMail),
                        ErlNifMakeGbkBinary(env, data->MoneyAccountStatus),
                        ErlNifMakeGbkBinary(env, data->BankAccount),
                        ErlNifMakeGbkBinary(env, data->BankPassWord),
                        ErlNifMakeGbkBinary(env, data->AccountID),
                        ErlNifMakeGbkBinary(env, data->Password),
                        enif_make_int(env, data->InstallID),
                        ErlNifMakeGbkBinary(env, data->VerifyCertNoFlag),
                        ErlNifMakeGbkBinary(env, data->CurrencyID),
                        ErlNifMakeGbkBinary(env, data->CashExchangeCode),
                        ErlNifMakeGbkBinary(env, data->Digest),
                        ErlNifMakeGbkBinary(env, data->BankAccType),
                        ErlNifMakeGbkBinary(env, data->DeviceID),
                        ErlNifMakeGbkBinary(env, data->BankSecuAccType),
                        ErlNifMakeGbkBinary(env, data->BrokerIDByBank),
                        ErlNifMakeGbkBinary(env, data->BankSecuAcc),
                        ErlNifMakeGbkBinary(env, data->BankPwdFlag),
                        ErlNifMakeGbkBinary(env, data->SecuPwdFlag),
                        ErlNifMakeGbkBinary(env, data->OperNo),
                        enif_make_int(env, data->TID),
                        ErlNifMakeGbkBinary(env, data->UserID),
                        enif_make_int(env, data->ErrorID),
                        ErlNifMakeGbkBinary(env, data->ErrorMsg)))));
  enif_free_env(env);
}

void CtpTd::OnRtnChangeAccountByBank(CThostFtdcChangeAccountField *data) {
  static CThostFtdcChangeAccountField empty_data = {};

  if (!data) {
    data = &empty_data;
  }

  ErlNifEnv *env = enif_alloc_env();
  enif_send(NULL, &this->pid_, env,
            enif_make_tuple2(
                env, enif_make_atom(env, "ctp_td"),
                enif_make_tuple2(
                    env, enif_make_atom(env, "on_rtn_change_account_by_bank"),
                    enif_make_tuple(
                        env, 43,
                        enif_make_atom(env, "cthost_ftdc_change_account_field"),
                        ErlNifMakeGbkBinary(env, data->TradeCode),
                        ErlNifMakeGbkBinary(env, data->BankID),
                        ErlNifMakeGbkBinary(env, data->BankBranchID),
                        ErlNifMakeGbkBinary(env, data->BrokerID),
                        ErlNifMakeGbkBinary(env, data->BrokerBranchID),
                        ErlNifMakeGbkBinary(env, data->TradeDate),
                        ErlNifMakeGbkBinary(env, data->TradeTime),
                        ErlNifMakeGbkBinary(env, data->BankSerial),
                        ErlNifMakeGbkBinary(env, data->TradingDay),
                        enif_make_int(env, data->PlateSerial),
                        ErlNifMakeGbkBinary(env, data->LastFragment),
                        enif_make_int(env, data->SessionID),
                        ErlNifMakeGbkBinary(env, data->CustomerName),
                        ErlNifMakeGbkBinary(env, data->IdCardType),
                        ErlNifMakeGbkBinary(env, data->IdentifiedCardNo),
                        ErlNifMakeGbkBinary(env, data->Gender),
                        ErlNifMakeGbkBinary(env, data->CountryCode),
                        ErlNifMakeGbkBinary(env, data->CustType),
                        ErlNifMakeGbkBinary(env, data->Address),
                        ErlNifMakeGbkBinary(env, data->ZipCode),
                        ErlNifMakeGbkBinary(env, data->Telephone),
                        ErlNifMakeGbkBinary(env, data->MobilePhone),
                        ErlNifMakeGbkBinary(env, data->Fax),
                        ErlNifMakeGbkBinary(env, data->EMail),
                        ErlNifMakeGbkBinary(env, data->MoneyAccountStatus),
                        ErlNifMakeGbkBinary(env, data->BankAccount),
                        ErlNifMakeGbkBinary(env, data->BankPassWord),
                        ErlNifMakeGbkBinary(env, data->NewBankAccount),
                        ErlNifMakeGbkBinary(env, data->NewBankPassWord),
                        ErlNifMakeGbkBinary(env, data->AccountID),
                        ErlNifMakeGbkBinary(env, data->Password),
                        ErlNifMakeGbkBinary(env, data->BankAccType),
                        enif_make_int(env, data->InstallID),
                        ErlNifMakeGbkBinary(env, data->VerifyCertNoFlag),
                        ErlNifMakeGbkBinary(env, data->CurrencyID),
                        ErlNifMakeGbkBinary(env, data->BrokerIDByBank),
                        ErlNifMakeGbkBinary(env, data->BankPwdFlag),
                        ErlNifMakeGbkBinary(env, data->SecuPwdFlag),
                        enif_make_int(env, data->TID),
                        ErlNifMakeGbkBinary(env, data->Digest),
                        enif_make_int(env, data->ErrorID),
                        ErlNifMakeGbkBinary(env, data->ErrorMsg)))));
  enif_free_env(env);
}
