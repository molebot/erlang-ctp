#ifndef CTP_TD_H
#define CTP_TD_H

#include "ctp/ThostFtdcTraderApi.h"
#include "common/common.h"
#include "erl_nif.h"

class CtpTd : public CThostFtdcTraderSpi {
public:
  /**
   * 构造函数
   * @param pid: 接收SPI回调消息的Erlang进程PID
   */
  CtpTd(ErlNifPid pid);
  virtual ~CtpTd();

  /* -------------------------------------------------------------------------
   * API接口
   * -------------------------------------------------------------------------
   */

  /**
   * 创建API
   * @param flow_path: 存贮订阅信息文件的目录, 默认为当前目录
   */
  virtual void CreateApi(const ErlNifBinary *flow_path);

  /**
   * 获取API的版本信息
   * @param env: Nif环境
   * @retrun 获取到的版本号
   */
  virtual ERL_NIF_TERM GetApiVersion(ErlNifEnv *env);

  /**
   * 初始化
   * @remark 初始化运行环境,只有调用后,接口才开始工作
   */
  virtual void Init();

  /**
   * 安全退出
   */
  virtual void Exit();

  /**
   * 获取当前交易日
   * @param env: Nif环境
   * @retrun 获取到的交易日
   * @remark 只有登录成功后,才能得到正确的交易日
   */
  virtual ERL_NIF_TERM GetTradingDay(ErlNifEnv *env);

  /**
   * 注册前置机网络地址
   * @param front_address: 前置机网络地址
   * @remark 网络地址的格式为: "protocol: *ipaddress:port", 如: "tcp:
   * 127.0.0.1:17001"
   * @remark "tcp"代表传输协议, "127.0.0.1"代表服务器地址.
   * "17001"代表服务器端口号
   */
  virtual void RegisterFront(const ErlNifBinary *front_address);

  /**
   * 注册名字服务器网络地址
   * @param ns_address: 名字服务器网络地址
   * @remark 网络地址的格式为: "protocol: *ipaddress:port", 如: "tcp:
   * 127.0.0.1:12001"
   * @remark "tcp"代表传输协议, "127.0.0.1"代表服务器地址.
   * "12001"代表服务器端口号
   * @remark RegisterNameServer优先于RegisterFront
   */
  virtual void RegisterNameServer(const ErlNifBinary *ns_address);

  /**
   * 注册名字服务器用户信息
   * @param env: Nif环境
   * @param req: 用户信息
   */
  virtual void RegisterFensUserInfo(ErlNifEnv *env, const NifRecord *req);

  /**
   * 订阅私有流
   * @param resume_type 私有流重传方式
   *         THOST_TERT_RESTART:从本交易日开始重传
   *         THOST_TERT_RESUME:从上次收到的续传
   *         THOST_TERT_QUICK:只传送登录后私有流的内容
   * @remark 该方法要在Init方法前调用. 若不调用则不会收到私有流的数据
   */
  virtual void SubscribePrivateTopic(int resume_type);

  /**
   * 订阅公共流
   * @param resume_type 公共流重传方式
   *         THOST_TERT_RESTART:从本交易日开始重传
   *         THOST_TERT_RESUME:从上次收到的续传
   *         THOST_TERT_QUICK:只传送登录后公共流的内容
   * @remark 该方法要在Init方法前调用. 若不调用则不会收到公共流的数据
   */
  virtual void SubscribePublicTopic(int resume_type);

  /**
   * 客户端认证请求
   */
  virtual int ReqAuthenticate(ErlNifEnv *env, NifRecord *req, int req_id);

  /**
   * 用户登录请求
   */
  virtual int ReqUserLogin(ErlNifEnv *env, NifRecord *req, int req_id);

  /**
   * 登出请求
   */
  virtual int ReqUserLogout(ErlNifEnv *env, NifRecord *req, int req_id);

  /**
   * 用户口令更新请求
   */
  virtual int ReqUserPasswordUpdate(ErlNifEnv *env, NifRecord *req, int req_id);

  /**
   * 资金账户口令更新请求
   */
  virtual int ReqTradingAccountPasswordUpdate(ErlNifEnv *env, NifRecord *req,
                                              int req_id);

  /**
   * 报单录入请求
   */
  virtual int ReqOrderInsert(ErlNifEnv *env, NifRecord *req, int req_id);

  /**
   * 预埋单录入请求
   */
  virtual int ReqParkedOrderInsert(ErlNifEnv *env, NifRecord *req, int req_id);

  /**
   * 预埋撤单录入请求
   */
  virtual int ReqParkedOrderAction(ErlNifEnv *env, NifRecord *req, int req_id);

  /**
   * 报单操作请求
   */
  virtual int ReqOrderAction(ErlNifEnv *env, NifRecord *req, int req_id);

  /**
   * 查询最大报单数量请求
   */
  virtual int ReqQueryMaxOrderVolume(ErlNifEnv *env, NifRecord *req,
                                     int req_id);

  /**
   * 投资者结算结果确认
   */
  virtual int ReqSettlementInfoConfirm(ErlNifEnv *env, NifRecord *req,
                                       int req_id);

  /**
   * 请求删除预埋单
   */
  virtual int ReqRemoveParkedOrder(ErlNifEnv *env, NifRecord *req, int req_id);

  /**
   * 请求删除预埋撤单
   */
  virtual int ReqRemoveParkedOrderAction(ErlNifEnv *env, NifRecord *req,
                                         int req_id);

  /**
   * 执行宣告录入请求
   */
  virtual int ReqExecOrderInsert(ErlNifEnv *env, NifRecord *req, int req_id);

  /**
   * 执行宣告操作请求
   */
  virtual int ReqExecOrderAction(ErlNifEnv *env, NifRecord *req, int req_id);

  /**
   * 询价录入请求
   */
  virtual int ReqForQuoteInsert(ErlNifEnv *env, NifRecord *req, int req_id);

  /**
   * 报价录入请求
   */
  virtual int ReqQuoteInsert(ErlNifEnv *env, NifRecord *req, int req_id);

  /**
   * 报价操作请求
   */
  virtual int ReqQuoteAction(ErlNifEnv *env, NifRecord *req, int req_id);

  /**
   * 锁定请求
   */
  virtual int ReqLockInsert(ErlNifEnv *env, NifRecord *req, int req_id);

  /**
   * 批量报单操作请求
   */
  virtual int ReqBatchOrderAction(ErlNifEnv *env, NifRecord *req, int req_id);

  /**
   * 申请组合录入请求
   */
  virtual int ReqCombActionInsert(ErlNifEnv *env, NifRecord *req, int req_id);

  /**
   * 请求查询报单
   */
  virtual int ReqQryOrder(ErlNifEnv *env, NifRecord *req, int req_id);

  /**
   * 请求查询成交
   */
  virtual int ReqQryTrade(ErlNifEnv *env, NifRecord *req, int req_id);

  /**
   * 请求查询投资者持仓
   */
  virtual int ReqQryInvestorPosition(ErlNifEnv *env, NifRecord *req,
                                     int req_id);

  /**
   * 请求查询资金账户
   */
  virtual int ReqQryTradingAccount(ErlNifEnv *env, NifRecord *req, int req_id);

  /**
   * 请求查询投资者
   */
  virtual int ReqQryInvestor(ErlNifEnv *env, NifRecord *req, int req_id);

  /**
   * 请求查询交易编码
   */
  virtual int ReqQryTradingCode(ErlNifEnv *env, NifRecord *req, int req_id);

  /**
   * 请求查询合约保证金率
   */
  virtual int ReqQryInstrumentMarginRate(ErlNifEnv *env, NifRecord *req,
                                         int req_id);

  /**
   * 请求查询合约手续费率
   */
  virtual int ReqQryInstrumentCommissionRate(ErlNifEnv *env, NifRecord *req,
                                             int req_id);

  /**
   * 请求查询交易所
   */
  virtual int ReqQryExchange(ErlNifEnv *env, NifRecord *req, int req_id);

  /**
   * 请求查询产品
   */
  virtual int ReqQryProduct(ErlNifEnv *env, NifRecord *req, int req_id);

  /**
   * 请求查询合约
   */
  virtual int ReqQryInstrument(ErlNifEnv *env, NifRecord *req, int req_id);

  /**
   * 请求查询行情
   */
  virtual int ReqQryDepthMarketData(ErlNifEnv *env, NifRecord *req, int req_id);

  /**
   * 请求查询投资者结算结果
   */
  virtual int ReqQrySettlementInfo(ErlNifEnv *env, NifRecord *req, int req_id);

  /**
   * 请求查询转帐银行
   */
  virtual int ReqQryTransferBank(ErlNifEnv *env, NifRecord *req, int req_id);

  /**
   * 请求查询投资者持仓明细
   */
  virtual int ReqQryInvestorPositionDetail(ErlNifEnv *env, NifRecord *req,
                                           int req_id);

  /**
   * 请求查询客户通知
   */
  virtual int ReqQryNotice(ErlNifEnv *env, NifRecord *req, int req_id);

  /**
   * 请求查询结算信息确认
   */
  virtual int ReqQrySettlementInfoConfirm(ErlNifEnv *env, NifRecord *req,
                                          int req_id);

  /**
   * 请求查询投资者持仓明细
   */
  virtual int ReqQryInvestorPositionCombineDetail(ErlNifEnv *env,
                                                  NifRecord *req, int req_id);

  /**
   * 请求查询保证金监管系统经纪公司资金账户密钥
   */
  virtual int ReqQryCFMMCTradingAccountKey(ErlNifEnv *env, NifRecord *req,
                                           int req_id);

  /**
   * 请求查询仓单折抵信息
   */
  virtual int ReqQryEWarrantOffset(ErlNifEnv *env, NifRecord *req, int req_id);

  /**
   * 请求查询投资者品种/跨品种保证金
   */
  virtual int ReqQryInvestorProductGroupMargin(ErlNifEnv *env, NifRecord *req,
                                               int req_id);

  /**
   * 请求查询交易所保证金率
   */
  virtual int ReqQryExchangeMarginRate(ErlNifEnv *env, NifRecord *req,
                                       int req_id);

  /**
   * 请求查询交易所调整保证金率
   */
  virtual int ReqQryExchangeMarginRateAdjust(ErlNifEnv *env, NifRecord *req,
                                             int req_id);

  /**
   * 请求查询汇率
   */
  virtual int ReqQryExchangeRate(ErlNifEnv *env, NifRecord *req, int req_id);

  /**
   * 请求查询二级代理操作员银期权限
   */
  virtual int ReqQrySecAgentACIDMap(ErlNifEnv *env, NifRecord *req, int req_id);

  /**
   * 请求查询产品报价汇率
   */
  virtual int ReqQryProductExchRate(ErlNifEnv *env, NifRecord *req, int req_id);

  /**
   * 请求查询产品组
   */
  virtual int ReqQryProductGroup(ErlNifEnv *env, NifRecord *req, int req_id);

  /**
   * 请求查询做市商合约手续费率
   */
  virtual int ReqQryMMInstrumentCommissionRate(ErlNifEnv *env, NifRecord *req,
                                               int req_id);

  /**
   * 请求查询做市商期权合约手续费
   */
  virtual int ReqQryMMOptionInstrCommRate(ErlNifEnv *env, NifRecord *req,
                                          int req_id);

  /**
   * 请求查询报单手续费
   */
  virtual int ReqQryInstrumentOrderCommRate(ErlNifEnv *env, NifRecord *req,
                                            int req_id);

  /**
   * 请求查询期权交易成本
   */
  virtual int ReqQryOptionInstrTradeCost(ErlNifEnv *env, NifRecord *req,
                                         int req_id);

  /**
   * 请求查询期权合约手续费
   */
  virtual int ReqQryOptionInstrCommRate(ErlNifEnv *env, NifRecord *req,
                                        int req_id);

  /**
   * 请求查询执行宣告
   */
  virtual int ReqQryExecOrder(ErlNifEnv *env, NifRecord *req, int req_id);

  /**
   * 请求查询询价
   */
  virtual int ReqQryForQuote(ErlNifEnv *env, NifRecord *req, int req_id);

  /**
   * 请求查询报价
   */
  virtual int ReqQryQuote(ErlNifEnv *env, NifRecord *req, int req_id);

  /**
   * 请求查询锁定
   */
  virtual int ReqQryLock(ErlNifEnv *env, NifRecord *req, int req_id);

  /**
   * 请求查询锁定证券仓位
   */
  virtual int ReqQryLockPosition(ErlNifEnv *env, NifRecord *req, int req_id);

  /**
   * 请求查询ETF期权合约手续费
   */
  virtual int ReqQryETFOptionInstrCommRate(ErlNifEnv *env, NifRecord *req,
                                           int req_id);

  /**
   * 请求查询投资者分级
   */
  virtual int ReqQryInvestorLevel(ErlNifEnv *env, NifRecord *req, int req_id);

  /**
   * 请求查询E+1日行权冻结
   */
  virtual int ReqQryExecFreeze(ErlNifEnv *env, NifRecord *req, int req_id);

  /**
   * 请求查询组合合约安全系数
   */
  virtual int ReqQryCombInstrumentGuard(ErlNifEnv *env, NifRecord *req,
                                        int req_id);

  /**
   * 请求查询申请组合
   */
  virtual int ReqQryCombAction(ErlNifEnv *env, NifRecord *req, int req_id);

  /**
   * 请求查询转帐流水
   */
  virtual int ReqQryTransferSerial(ErlNifEnv *env, NifRecord *req, int req_id);

  /**
   * 请求查询银期签约关系
   */
  virtual int ReqQryAccountregister(ErlNifEnv *env, NifRecord *req, int req_id);

  /**
   * 请求查询签约银行
   */
  virtual int ReqQryContractBank(ErlNifEnv *env, NifRecord *req, int req_id);

  /**
   * 请求查询预埋单
   */
  virtual int ReqQryParkedOrder(ErlNifEnv *env, NifRecord *req, int req_id);

  /**
   * 请求查询预埋撤单
   */
  virtual int ReqQryParkedOrderAction(ErlNifEnv *env, NifRecord *req,
                                      int req_id);

  /**
   * 请求查询交易通知
   */
  virtual int ReqQryTradingNotice(ErlNifEnv *env, NifRecord *req, int req_id);

  /**
   * 请求查询经纪公司交易参数
   */
  virtual int ReqQryBrokerTradingParams(ErlNifEnv *env, NifRecord *req,
                                        int req_id);

  /**
   * 请求查询经纪公司交易算法
   */
  virtual int ReqQryBrokerTradingAlgos(ErlNifEnv *env, NifRecord *req,
                                       int req_id);

  /**
   * 请求查询监控中心用户令牌
   */
  virtual int ReqQueryCFMMCTradingAccountToken(ErlNifEnv *env, NifRecord *req,
                                               int req_id);

  /**
   * 期货发起银行资金转期货请求
   */
  virtual int ReqFromBankToFutureByFuture(ErlNifEnv *env, NifRecord *req,
                                          int req_id);

  /**
   * 期货发起期货资金转银行请求
   */
  virtual int ReqFromFutureToBankByFuture(ErlNifEnv *env, NifRecord *req,
                                          int req_id);

  /**
   * 期货发起查询银行余额请求
   */
  virtual int ReqQueryBankAccountMoneyByFuture(ErlNifEnv *env, NifRecord *req,
                                               int req_id);

  /* -------------------------------------------------------------------------
   * SPI接口
   * -------------------------------------------------------------------------
   */

  /**
   * 当客户端与交易后台建立起通信连接时(还未登录前), 该方法被调用
   */
  virtual void OnFrontConnected();

  /**
   * 当客户端与交易后台通信连接断开时, 该方法被调用. 当发生这个情况后,
   * API会自动重新连接, 客户端可不做处理
   * @param reason 错误原因
   *         0x1001 网络读失败
   *         0x1002 网络写失败
   *         0x2001 接收心跳超时
   *         0x2002 发送心跳失败
   *         0x2003 收到错误报文
   */
  virtual void OnFrontDisconnected(int reason);

  /**
   * 心跳超时警告. 当长时间未收到报文时, 该方法被调用
   * @param time_lapse 距离上次接收报文的时间
   */
  virtual void OnHeartBeatWarning(int time_lapse);

  /**
   * 客户端认证响应
   */
  virtual void OnRspAuthenticate(CThostFtdcRspAuthenticateField *data,
                                 CThostFtdcRspInfoField *error, int req_id,
                                 bool last);

  /**
   * 登录请求响应
   */
  virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *data,
                              CThostFtdcRspInfoField *error, int req_id,
                              bool last);

  /**
   * 登出请求响应
   */
  virtual void OnRspUserLogout(CThostFtdcUserLogoutField *data,
                               CThostFtdcRspInfoField *error, int req_id,
                               bool last);

  /**
   * 用户口令更新请求响应
   */
  virtual void OnRspUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *data,
                                       CThostFtdcRspInfoField *error,
                                       int req_id, bool last);

  /**
   * 资金账户口令更新请求响应
   */
  virtual void OnRspTradingAccountPasswordUpdate(
      CThostFtdcTradingAccountPasswordUpdateField *data,
      CThostFtdcRspInfoField *error, int req_id, bool last);

  /**
   * 报单录入请求响应
   */
  virtual void OnRspOrderInsert(CThostFtdcInputOrderField *data,
                                CThostFtdcRspInfoField *error, int req_id,
                                bool last);

  /**
   * 预埋单录入请求响应
   */
  virtual void OnRspParkedOrderInsert(CThostFtdcParkedOrderField *data,
                                      CThostFtdcRspInfoField *error, int req_id,
                                      bool last);

  /**
   * 预埋撤单录入请求响应
   */
  virtual void OnRspParkedOrderAction(CThostFtdcParkedOrderActionField *data,
                                      CThostFtdcRspInfoField *error, int req_id,
                                      bool last);

  /**
   * 报单操作请求响应
   */
  virtual void OnRspOrderAction(CThostFtdcInputOrderActionField *data,
                                CThostFtdcRspInfoField *error, int req_id,
                                bool last);

  /**
   * 查询最大报单数量响应
   */
  virtual void
  OnRspQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField *data,
                           CThostFtdcRspInfoField *error, int req_id,
                           bool last);

  /**
   * 投资者结算结果确认响应
   */
  virtual void
  OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *data,
                             CThostFtdcRspInfoField *error, int req_id,
                             bool last);

  /**
   * 删除预埋单响应
   */
  virtual void OnRspRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *data,
                                      CThostFtdcRspInfoField *error, int req_id,
                                      bool last);

  /**
   * 删除预埋撤单响应
   */
  virtual void
  OnRspRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField *data,
                               CThostFtdcRspInfoField *error, int req_id,
                               bool last);

  /**
   * 执行宣告录入请求响应
   */
  virtual void OnRspExecOrderInsert(CThostFtdcInputExecOrderField *data,
                                    CThostFtdcRspInfoField *error, int req_id,
                                    bool last);

  /**
   * 执行宣告操作请求响应
   */
  virtual void OnRspExecOrderAction(CThostFtdcInputExecOrderActionField *data,
                                    CThostFtdcRspInfoField *error, int req_id,
                                    bool last);

  /**
   * 询价录入请求响应
   */
  virtual void OnRspForQuoteInsert(CThostFtdcInputForQuoteField *data,
                                   CThostFtdcRspInfoField *error, int req_id,
                                   bool last);

  /**
   * 报价录入请求响应
   */
  virtual void OnRspQuoteInsert(CThostFtdcInputQuoteField *data,
                                CThostFtdcRspInfoField *error, int req_id,
                                bool last);

  /**
   * 报价操作请求响应
   */
  virtual void OnRspQuoteAction(CThostFtdcInputQuoteActionField *data,
                                CThostFtdcRspInfoField *error, int req_id,
                                bool last);

  /**
   * 锁定应答
   */
  virtual void OnRspLockInsert(CThostFtdcInputLockField *data,
                               CThostFtdcRspInfoField *error, int req_id,
                               bool last);

  /**
   * 批量报单操作请求响应
   */
  virtual void OnRspBatchOrderAction(CThostFtdcInputBatchOrderActionField *data,
                                     CThostFtdcRspInfoField *error, int req_id,
                                     bool last);

  /**
   * 申请组合录入请求响应
   */
  virtual void OnRspCombActionInsert(CThostFtdcInputCombActionField *data,
                                     CThostFtdcRspInfoField *error, int req_id,
                                     bool last);

  /**
   * 请求查询报单响应
   */
  virtual void OnRspQryOrder(CThostFtdcOrderField *data,
                             CThostFtdcRspInfoField *error, int req_id,
                             bool last);

  /**
   * 请求查询成交响应
   */
  virtual void OnRspQryTrade(CThostFtdcTradeField *data,
                             CThostFtdcRspInfoField *error, int req_id,
                             bool last);

  /**
   * 请求查询投资者持仓响应
   */
  virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *data,
                                        CThostFtdcRspInfoField *error,
                                        int req_id, bool last);

  /**
   * 请求查询资金账户响应
   */
  virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField *data,
                                      CThostFtdcRspInfoField *error, int req_id,
                                      bool last);

  /**
   * 请求查询投资者响应
   */
  virtual void OnRspQryInvestor(CThostFtdcInvestorField *data,
                                CThostFtdcRspInfoField *error, int req_id,
                                bool last);

  /**
   * 请求查询交易编码响应
   */
  virtual void OnRspQryTradingCode(CThostFtdcTradingCodeField *data,
                                   CThostFtdcRspInfoField *error, int req_id,
                                   bool last);

  /**
   * 请求查询合约保证金率响应
   */
  virtual void
  OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *data,
                               CThostFtdcRspInfoField *error, int req_id,
                               bool last);

  /**
   * 请求查询合约手续费率响应
   */
  virtual void OnRspQryInstrumentCommissionRate(
      CThostFtdcInstrumentCommissionRateField *data,
      CThostFtdcRspInfoField *error, int req_id, bool last);

  /**
   * 请求查询交易所响应
   */
  virtual void OnRspQryExchange(CThostFtdcExchangeField *data,
                                CThostFtdcRspInfoField *error, int req_id,
                                bool last);

  /**
   * 请求查询产品响应
   */
  virtual void OnRspQryProduct(CThostFtdcProductField *data,
                               CThostFtdcRspInfoField *error, int req_id,
                               bool last);

  /**
   * 请求查询合约响应
   */
  virtual void OnRspQryInstrument(CThostFtdcInstrumentField *data,
                                  CThostFtdcRspInfoField *error, int req_id,
                                  bool last);

  /**
   * 请求查询行情响应
   */
  virtual void OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *data,
                                       CThostFtdcRspInfoField *error,
                                       int req_id, bool last);

  /**
   * 请求查询投资者结算结果响应
   */
  virtual void OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *data,
                                      CThostFtdcRspInfoField *error, int req_id,
                                      bool last);

  /**
   * 请求查询转帐银行响应
   */
  virtual void OnRspQryTransferBank(CThostFtdcTransferBankField *data,
                                    CThostFtdcRspInfoField *error, int req_id,
                                    bool last);

  /**
   * 请求查询投资者持仓明细响应
   */
  virtual void
  OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *data,
                                 CThostFtdcRspInfoField *error, int req_id,
                                 bool last);

  /**
   * 请求查询客户通知响应
   */
  virtual void OnRspQryNotice(CThostFtdcNoticeField *data,
                              CThostFtdcRspInfoField *error, int req_id,
                              bool last);

  /**
   * 请求查询结算信息确认响应
   */
  virtual void
  OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *data,
                                CThostFtdcRspInfoField *error, int req_id,
                                bool last);

  /**
   * 请求查询投资者持仓明细响应
   */
  virtual void OnRspQryInvestorPositionCombineDetail(
      CThostFtdcInvestorPositionCombineDetailField *data,
      CThostFtdcRspInfoField *error, int req_id, bool last);

  /**
   * 查询保证金监管系统经纪公司资金账户密钥响应
   */
  virtual void
  OnRspQryCFMMCTradingAccountKey(CThostFtdcCFMMCTradingAccountKeyField *data,
                                 CThostFtdcRspInfoField *error, int req_id,
                                 bool last);

  /**
   * 请求查询仓单折抵信息响应
   */
  virtual void OnRspQryEWarrantOffset(CThostFtdcEWarrantOffsetField *data,
                                      CThostFtdcRspInfoField *error, int req_id,
                                      bool last);

  /**
   * 请求查询投资者品种/跨品种保证金响应
   */
  virtual void OnRspQryInvestorProductGroupMargin(
      CThostFtdcInvestorProductGroupMarginField *data,
      CThostFtdcRspInfoField *error, int req_id, bool last);

  /**
   * 请求查询交易所保证金率响应
   */
  virtual void
  OnRspQryExchangeMarginRate(CThostFtdcExchangeMarginRateField *data,
                             CThostFtdcRspInfoField *error, int req_id,
                             bool last);

  /**
   * 请求查询交易所调整保证金率响应
   */
  virtual void OnRspQryExchangeMarginRateAdjust(
      CThostFtdcExchangeMarginRateAdjustField *data,
      CThostFtdcRspInfoField *error, int req_id, bool last);

  /**
   * 请求查询汇率响应
   */
  virtual void OnRspQryExchangeRate(CThostFtdcExchangeRateField *data,
                                    CThostFtdcRspInfoField *error, int req_id,
                                    bool last);

  /**
   * 请求查询二级代理操作员银期权限响应
   */
  virtual void OnRspQrySecAgentACIDMap(CThostFtdcSecAgentACIDMapField *data,
                                       CThostFtdcRspInfoField *error,
                                       int req_id, bool last);

  /**
   * 请求查询产品报价汇率
   */
  virtual void OnRspQryProductExchRate(CThostFtdcProductExchRateField *data,
                                       CThostFtdcRspInfoField *error,
                                       int req_id, bool last);

  /**
   * 请求查询产品组
   */
  virtual void OnRspQryProductGroup(CThostFtdcProductGroupField *data,
                                    CThostFtdcRspInfoField *error, int req_id,
                                    bool last);

  /**
   * 请求查询做市商合约手续费率响应
   */
  virtual void OnRspQryMMInstrumentCommissionRate(
      CThostFtdcMMInstrumentCommissionRateField *data,
      CThostFtdcRspInfoField *error, int req_id, bool last);

  /**
   * 请求查询做市商期权合约手续费响应
   */
  virtual void
  OnRspQryMMOptionInstrCommRate(CThostFtdcMMOptionInstrCommRateField *data,
                                CThostFtdcRspInfoField *error, int req_id,
                                bool last);

  /**
   * 请求查询报单手续费响应
   */
  virtual void
  OnRspQryInstrumentOrderCommRate(CThostFtdcInstrumentOrderCommRateField *data,
                                  CThostFtdcRspInfoField *error, int req_id,
                                  bool last);

  /**
   * 请求查询期权交易成本响应
   */
  virtual void
  OnRspQryOptionInstrTradeCost(CThostFtdcOptionInstrTradeCostField *data,
                               CThostFtdcRspInfoField *error, int req_id,
                               bool last);

  /**
   * 请求查询期权合约手续费响应
   */
  virtual void
  OnRspQryOptionInstrCommRate(CThostFtdcOptionInstrCommRateField *data,
                              CThostFtdcRspInfoField *error, int req_id,
                              bool last);

  /**
   * 请求查询执行宣告响应
   */
  virtual void OnRspQryExecOrder(CThostFtdcExecOrderField *data,
                                 CThostFtdcRspInfoField *error, int req_id,
                                 bool last);

  /**
   * 请求查询询价响应
   */
  virtual void OnRspQryForQuote(CThostFtdcForQuoteField *data,
                                CThostFtdcRspInfoField *error, int req_id,
                                bool last);

  /**
   * 请求查询报价响应
   */
  virtual void OnRspQryQuote(CThostFtdcQuoteField *data,
                             CThostFtdcRspInfoField *error, int req_id,
                             bool last);

  /**
   * 请求查询锁定应答
   */
  virtual void OnRspQryLock(CThostFtdcLockField *data,
                            CThostFtdcRspInfoField *error, int req_id,
                            bool last);

  /**
   * 请求查询锁定证券仓位应答
   */
  virtual void OnRspQryLockPosition(CThostFtdcLockPositionField *data,
                                    CThostFtdcRspInfoField *error, int req_id,
                                    bool last);

  /**
   * 请求查询ETF期权合约手续费响应
   */
  virtual void
  OnRspQryETFOptionInstrCommRate(CThostFtdcETFOptionInstrCommRateField *data,
                                 CThostFtdcRspInfoField *error, int req_id,
                                 bool last);

  /**
   * 请求查询投资者分级
   */
  virtual void OnRspQryInvestorLevel(CThostFtdcInvestorLevelField *data,
                                     CThostFtdcRspInfoField *error, int req_id,
                                     bool last);

  /**
   * 请求查询E+1日行权冻结响应
   */
  virtual void OnRspQryExecFreeze(CThostFtdcExecFreezeField *data,
                                  CThostFtdcRspInfoField *error, int req_id,
                                  bool last);

  /**
   * 请求查询组合合约安全系数响应
   */
  virtual void
  OnRspQryCombInstrumentGuard(CThostFtdcCombInstrumentGuardField *data,
                              CThostFtdcRspInfoField *error, int req_id,
                              bool last);

  /**
   * 请求查询申请组合响应
   */
  virtual void OnRspQryCombAction(CThostFtdcCombActionField *data,
                                  CThostFtdcRspInfoField *error, int req_id,
                                  bool last);

  /**
   * 请求查询转帐流水响应
   */
  virtual void OnRspQryTransferSerial(CThostFtdcTransferSerialField *data,
                                      CThostFtdcRspInfoField *error, int req_id,
                                      bool last);

  /**
   * 请求查询银期签约关系响应
   */
  virtual void OnRspQryAccountregister(CThostFtdcAccountregisterField *data,
                                       CThostFtdcRspInfoField *error,
                                       int req_id, bool last);

  /**
   * 错误应答
   */
  virtual void OnRspError(CThostFtdcRspInfoField *error, int req_id, bool last);

  /**
   * 报单通知
   */
  virtual void OnRtnOrder(CThostFtdcOrderField *data);

  /**
   * 成交通知
   */
  virtual void OnRtnTrade(CThostFtdcTradeField *data);

  /**
   * 报单录入错误回报
   */
  virtual void OnErrRtnOrderInsert(CThostFtdcInputOrderField *data,
                                   CThostFtdcRspInfoField *error);

  /**
   * 报单操作错误回报
   */
  virtual void OnErrRtnOrderAction(CThostFtdcOrderActionField *data,
                                   CThostFtdcRspInfoField *error);

  /**
   * 合约交易状态通知
   */
  virtual void OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *data);

  /**
   * 交易所公告通知
   */
  virtual void OnRtnBulletin(CThostFtdcBulletinField *data);

  /**
   * 交易通知
   */
  virtual void OnRtnTradingNotice(CThostFtdcTradingNoticeInfoField *data);

  /**
   * 提示条件单校验错误
   */
  virtual void
  OnRtnErrorConditionalOrder(CThostFtdcErrorConditionalOrderField *data);

  /**
   * 执行宣告通知
   */
  virtual void OnRtnExecOrder(CThostFtdcExecOrderField *data);

  /**
   * 执行宣告录入错误回报
   */
  virtual void OnErrRtnExecOrderInsert(CThostFtdcInputExecOrderField *data,
                                       CThostFtdcRspInfoField *error);

  /**
   * 执行宣告操作错误回报
   */
  virtual void OnErrRtnExecOrderAction(CThostFtdcExecOrderActionField *data,
                                       CThostFtdcRspInfoField *error);

  /**
   * 询价录入错误回报
   */
  virtual void OnErrRtnForQuoteInsert(CThostFtdcInputForQuoteField *data,
                                      CThostFtdcRspInfoField *error);

  /**
   * 报价通知
   */
  virtual void OnRtnQuote(CThostFtdcQuoteField *data);

  /**
   * 报价录入错误回报
   */
  virtual void OnErrRtnQuoteInsert(CThostFtdcInputQuoteField *data,
                                   CThostFtdcRspInfoField *error);

  /**
   * 报价操作错误回报
   */
  virtual void OnErrRtnQuoteAction(CThostFtdcQuoteActionField *data,
                                   CThostFtdcRspInfoField *error);

  /**
   * 询价通知
   */
  virtual void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *data);

  /**
   * 保证金监控中心用户令牌
   */
  virtual void
  OnRtnCFMMCTradingAccountToken(CThostFtdcCFMMCTradingAccountTokenField *data);

  /**
   * 锁定通知
   */
  virtual void OnRtnLock(CThostFtdcLockField *data);

  /**
   * 锁定错误通知
   */
  virtual void OnErrRtnLockInsert(CThostFtdcInputLockField *data,
                                  CThostFtdcRspInfoField *error);

  /**
   * 批量报单操作错误回报
   */
  virtual void OnErrRtnBatchOrderAction(CThostFtdcBatchOrderActionField *data,
                                        CThostFtdcRspInfoField *error);

  /**
   * 申请组合通知
   */
  virtual void OnRtnCombAction(CThostFtdcCombActionField *data);

  /**
   * 申请组合录入错误回报
   */
  virtual void OnErrRtnCombActionInsert(CThostFtdcInputCombActionField *data,
                                        CThostFtdcRspInfoField *error);

  /**
   * 请求查询签约银行响应
   */
  virtual void OnRspQryContractBank(CThostFtdcContractBankField *data,
                                    CThostFtdcRspInfoField *error, int req_id,
                                    bool last);

  /**
   * 请求查询预埋单响应
   */
  virtual void OnRspQryParkedOrder(CThostFtdcParkedOrderField *data,
                                   CThostFtdcRspInfoField *error, int req_id,
                                   bool last);

  /**
   * 请求查询预埋撤单响应
   */
  virtual void OnRspQryParkedOrderAction(CThostFtdcParkedOrderActionField *data,
                                         CThostFtdcRspInfoField *error,
                                         int req_id, bool last);

  /**
   * 请求查询交易通知响应
   */
  virtual void OnRspQryTradingNotice(CThostFtdcTradingNoticeField *data,
                                     CThostFtdcRspInfoField *error, int req_id,
                                     bool last);

  /**
   * 请求查询经纪公司交易参数响应
   */
  virtual void
  OnRspQryBrokerTradingParams(CThostFtdcBrokerTradingParamsField *data,
                              CThostFtdcRspInfoField *error, int req_id,
                              bool last);

  /**
   * 请求查询经纪公司交易算法响应
   */
  virtual void
  OnRspQryBrokerTradingAlgos(CThostFtdcBrokerTradingAlgosField *data,
                             CThostFtdcRspInfoField *error, int req_id,
                             bool last);

  /**
   * 请求查询监控中心用户令牌
   */
  virtual void OnRspQueryCFMMCTradingAccountToken(
      CThostFtdcQueryCFMMCTradingAccountTokenField *data,
      CThostFtdcRspInfoField *error, int req_id, bool last);

  /**
   * 银行发起银行资金转期货通知
   */
  virtual void OnRtnFromBankToFutureByBank(CThostFtdcRspTransferField *data);

  /**
   * 银行发起期货资金转银行通知
   */
  virtual void OnRtnFromFutureToBankByBank(CThostFtdcRspTransferField *data);

  /**
   * 银行发起冲正银行转期货通知
   */
  virtual void
  OnRtnRepealFromBankToFutureByBank(CThostFtdcRspRepealField *data);

  /**
   * 银行发起冲正期货转银行通知
   */
  virtual void
  OnRtnRepealFromFutureToBankByBank(CThostFtdcRspRepealField *data);

  /**
   * 期货发起银行资金转期货通知
   */
  virtual void OnRtnFromBankToFutureByFuture(CThostFtdcRspTransferField *data);

  /**
   * 期货发起期货资金转银行通知
   */
  virtual void OnRtnFromFutureToBankByFuture(CThostFtdcRspTransferField *data);

  /**
   * 系统运行时期货端手工发起冲正银行转期货请求, 银行处理完毕后报盘发回的通知
   */
  virtual void
  OnRtnRepealFromBankToFutureByFutureManual(CThostFtdcRspRepealField *data);

  /**
   * 系统运行时期货端手工发起冲正期货转银行请求, 银行处理完毕后报盘发回的通知
   */
  virtual void
  OnRtnRepealFromFutureToBankByFutureManual(CThostFtdcRspRepealField *data);

  /**
   * 期货发起查询银行余额通知
   */
  virtual void
  OnRtnQueryBankBalanceByFuture(CThostFtdcNotifyQueryAccountField *data);

  /**
   * 期货发起银行资金转期货错误回报
   */
  virtual void OnErrRtnBankToFutureByFuture(CThostFtdcReqTransferField *data,
                                            CThostFtdcRspInfoField *error);

  /**
   * 期货发起期货资金转银行错误回报
   */
  virtual void OnErrRtnFutureToBankByFuture(CThostFtdcReqTransferField *data,
                                            CThostFtdcRspInfoField *error);

  /**
   * 系统运行时期货端手工发起冲正银行转期货错误回报
   */
  virtual void
  OnErrRtnRepealBankToFutureByFutureManual(CThostFtdcReqRepealField *data,
                                           CThostFtdcRspInfoField *error);

  /**
   * 系统运行时期货端手工发起冲正期货转银行错误回报
   */
  virtual void
  OnErrRtnRepealFutureToBankByFutureManual(CThostFtdcReqRepealField *data,
                                           CThostFtdcRspInfoField *error);

  /**
   * 期货发起查询银行余额错误回报
   */
  virtual void
  OnErrRtnQueryBankBalanceByFuture(CThostFtdcReqQueryAccountField *data,
                                   CThostFtdcRspInfoField *error);

  /**
   * 期货发起冲正银行转期货请求, 银行处理完毕后报盘发回的通知
   */
  virtual void
  OnRtnRepealFromBankToFutureByFuture(CThostFtdcRspRepealField *data);

  /**
   * 期货发起冲正期货转银行请求, 银行处理完毕后报盘发回的通知
   */
  virtual void
  OnRtnRepealFromFutureToBankByFuture(CThostFtdcRspRepealField *data);

  /**
   * 期货发起银行资金转期货应答
   */
  virtual void OnRspFromBankToFutureByFuture(CThostFtdcReqTransferField *data,
                                             CThostFtdcRspInfoField *error,
                                             int req_id, bool last);

  /**
   * 期货发起期货资金转银行应答
   */
  virtual void OnRspFromFutureToBankByFuture(CThostFtdcReqTransferField *data,
                                             CThostFtdcRspInfoField *error,
                                             int req_id, bool last);

  /**
   * 期货发起查询银行余额应答
   */
  virtual void
  OnRspQueryBankAccountMoneyByFuture(CThostFtdcReqQueryAccountField *data,
                                     CThostFtdcRspInfoField *error, int req_id,
                                     bool last);

  /**
   * 银行发起银期开户通知
   */
  virtual void OnRtnOpenAccountByBank(CThostFtdcOpenAccountField *data);

  /**
   * 银行发起银期销户通知
   */
  virtual void OnRtnCancelAccountByBank(CThostFtdcCancelAccountField *data);

  /**
   * 银行发起变更银行账号通知
   */
  virtual void OnRtnChangeAccountByBank(CThostFtdcChangeAccountField *data);

private:
  ErlNifPid pid_;
  CThostFtdcTraderApi *api_;
};

#endif /* CTP_TD_H */
