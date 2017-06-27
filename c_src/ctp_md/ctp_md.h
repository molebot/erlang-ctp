#ifndef CTP_MD_H
#define CTP_MD_H

#include "ctp/ThostFtdcMdApi.h"
#include "common/common.h"
#include "erl_nif.h"

class CtpMd : public CThostFtdcMdSpi {
public:
  /**
   * 构造函数
   * @param pid: 接收SPI回调消息的Erlang进程PID
   */
  CtpMd(ErlNifPid pid);
  virtual ~CtpMd();

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
   * 订阅行情
   * @param env: Nif环境
   * @param list: 合约ID列表
   * @remark
   */
  virtual int SubscribeMarketData(ErlNifEnv *env, ERL_NIF_TERM list);

  /**
   * 退订行情
   * @param env: Nif环境
   * @param list: 合约ID列表
   * @remark
   */
  virtual int UnSubscribeMarketData(ErlNifEnv *env, ERL_NIF_TERM list);

  /**
   * 订阅询价
   * @param env: Nif环境
   * @param list: 合约ID列表
   * @remark
   */
  virtual int SubscribeForQuoteRsp(ErlNifEnv *env, ERL_NIF_TERM list);

  /**
   * 退订询价
   * @param env: Nif环境
   * @param list: 合约ID列表
   * @remark
   */
  virtual int UnSubscribeForQuoteRsp(ErlNifEnv *env, ERL_NIF_TERM list);

  /**
   * 用户登录请求
   */
  virtual int ReqUserLogin(ErlNifEnv *env, const NifRecord *req, int req_id);

  /**
   * 登出请求
   */
  virtual int ReqUserLogout(ErlNifEnv *env, const NifRecord *req, int req_id);

  /* ---------------------------------------------------------------------------
   * SPI接口
   * ---------------------------------------------------------------------------
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
   * 错误应答
   */
  virtual void OnRspError(CThostFtdcRspInfoField *error, int req_id, bool last);

  /**
   * 订阅行情应答
   */
  virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *data,
                                  CThostFtdcRspInfoField *error, int req_id,
                                  bool last);

  /**
   * 取消订阅行情应答
   */
  virtual void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *data,
                                    CThostFtdcRspInfoField *error, int req_id,
                                    bool last);

  /**
   * 订阅询价应答
   */
  virtual void OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *data,
                                   CThostFtdcRspInfoField *error, int req_id,
                                   bool last);

  /**
   * 取消订阅询价应答
   */
  virtual void OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *data,
                                     CThostFtdcRspInfoField *error, int req_id,
                                     bool last);

  /**
   * 深度行情通知
   */
  virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *data);

  /**
   * 询价通知
   */
  virtual void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *data);

private:
  /**
   * 接收SPI回调消息的Erlang进程PID
   */
  ErlNifPid pid_;

  /**
   * CTP API对象
   */
  CThostFtdcMdApi *api_;
};

#endif /* CTP_MD_H */
