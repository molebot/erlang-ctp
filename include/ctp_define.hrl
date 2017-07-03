%%% -*- coding: utf-8 -*-

-ifndef(ctp_define_hrl).
-define(ctp_define_hrl, true).

%% 从当天的第一条记录开始接收数据流
-define(THOST_TERT_RESTART, 0).

%% 接收上次断线以后的数据流
-define(THOST_TERT_RESUME, 1).

%% 接收本次登入以后的数据流
-define(THOST_TERT_QUICK, 2).

%% 正常
-define(THOST_FTDC_EXP_Normal, <<"0">>).

%% 根据成交生成报单
-define(THOST_FTDC_EXP_GenOrderByTrade, <<"1">>).

%% 组织机构代码
-define(THOST_FTDC_ICT_EID, <<"0">>).

%% 中国公民身份证
-define(THOST_FTDC_ICT_IDCard, <<"1">>).

%% 军官证
-define(THOST_FTDC_ICT_OfficerIDCard, <<"2">>).

%% 警官证
-define(THOST_FTDC_ICT_PoliceIDCard, <<"3">>).

%% 士兵证
-define(THOST_FTDC_ICT_SoldierIDCard, <<"4">>).

%% 户口簿
-define(THOST_FTDC_ICT_HouseholdRegister, <<"5">>).

%% 护照
-define(THOST_FTDC_ICT_Passport, <<"6">>).

%% 台胞证
-define(THOST_FTDC_ICT_TaiwanCompatriotIDCard, <<"7">>).

%% 回乡证
-define(THOST_FTDC_ICT_HomeComingCard, <<"8">>).

%% 营业执照号
-define(THOST_FTDC_ICT_LicenseNo, <<"9">>).

%% 税务登记号/当地纳税ID
-define(THOST_FTDC_ICT_TaxNo, <<"A">>).

%% 港澳居民来往内地通行证
-define(THOST_FTDC_ICT_HMMainlandTravelPermit, <<"B">>).

%% 台湾居民来往大陆通行证
-define(THOST_FTDC_ICT_TwMainlandTravelPermit, <<"C">>).

%% 驾照
-define(THOST_FTDC_ICT_DrivingLicense, <<"D">>).

%% 当地社保ID
-define(THOST_FTDC_ICT_SocialID, <<"F">>).

%% 当地身份证
-define(THOST_FTDC_ICT_LocalID, <<"G">>).

%% 商业登记证
-define(THOST_FTDC_ICT_BusinessRegistration, <<"H">>).

%% 港澳永久性居民身份证
-define(THOST_FTDC_ICT_HKMCIDCard, <<"I">>).

%% 人行开户许可证
-define(THOST_FTDC_ICT_AccountsPermits, <<"J">>).

%% 其他证件
-define(THOST_FTDC_ICT_OtherCard, <<"x">>).

%% 所有
-define(THOST_FTDC_IR_All, <<"1">>).

%% 投资者组
-define(THOST_FTDC_IR_Group, <<"2">>).

%% 单一投资者
-define(THOST_FTDC_IR_Single, <<"3">>).

%% 所有
-define(THOST_FTDC_DR_All, <<"1">>).

%% 组织架构
-define(THOST_FTDC_DR_Group, <<"2">>).

%% 单一投资者
-define(THOST_FTDC_DR_Single, <<"3">>).

%% 未同步
-define(THOST_FTDC_DS_Asynchronous, <<"1">>).

%% 同步中
-define(THOST_FTDC_DS_Synchronizing, <<"2">>).

%% 已同步
-define(THOST_FTDC_DS_Synchronized, <<"3">>).

%% 已同步
-define(THOST_FTDC_BDS_Synchronized, <<"1">>).

%% 同步中
-define(THOST_FTDC_BDS_Synchronizing, <<"2">>).

%% 没有任何连接
-define(THOST_FTDC_ECS_NoConnection, <<"1">>).

%% 已经发出合约查询请求
-define(THOST_FTDC_ECS_QryInstrumentSent, <<"2">>).

%% 已经获取信息
-define(THOST_FTDC_ECS_GotInformation, <<"9">>).

%% 没有任何连接
-define(THOST_FTDC_TCS_NotConnected, <<"1">>).

%% 已经连接
-define(THOST_FTDC_TCS_Connected, <<"2">>).

%% 已经发出合约查询请求
-define(THOST_FTDC_TCS_QryInstrumentSent, <<"3">>).

%% 订阅私有流
-define(THOST_FTDC_TCS_SubPrivateFlow, <<"4">>).

%% 数据异步化
-define(THOST_FTDC_FC_DataAsync, <<"1">>).

%% 强制用户登出
-define(THOST_FTDC_FC_ForceUserLogout, <<"2">>).

%% 变更管理用户口令
-define(THOST_FTDC_FC_UserPasswordUpdate, <<"3">>).

%% 变更经纪公司口令
-define(THOST_FTDC_FC_BrokerPasswordUpdate, <<"4">>).

%% 变更投资者口令
-define(THOST_FTDC_FC_InvestorPasswordUpdate, <<"5">>).

%% 报单插入
-define(THOST_FTDC_FC_OrderInsert, <<"6">>).

%% 报单操作
-define(THOST_FTDC_FC_OrderAction, <<"7">>).

%% 同步系统数据
-define(THOST_FTDC_FC_SyncSystemData, <<"8">>).

%% 同步经纪公司数据
-define(THOST_FTDC_FC_SyncBrokerData, <<"9">>).

%% 批量同步经纪公司数据
-define(THOST_FTDC_FC_BachSyncBrokerData, <<"A">>).

%% 超级查询
-define(THOST_FTDC_FC_SuperQuery, <<"B">>).

%% 预埋报单插入
-define(THOST_FTDC_FC_ParkedOrderInsert, <<"C">>).

%% 预埋报单操作
-define(THOST_FTDC_FC_ParkedOrderAction, <<"D">>).

%% 同步动态令牌
-define(THOST_FTDC_FC_SyncOTP, <<"E">>).

%% 删除未知单
-define(THOST_FTDC_FC_DeleteOrder, <<"F">>).

%% 强制用户登出
-define(THOST_FTDC_BFC_ForceUserLogout, <<"1">>).

%% 变更用户口令
-define(THOST_FTDC_BFC_UserPasswordUpdate, <<"2">>).

%% 同步经纪公司数据
-define(THOST_FTDC_BFC_SyncBrokerData, <<"3">>).

%% 批量同步经纪公司数据
-define(THOST_FTDC_BFC_BachSyncBrokerData, <<"4">>).

%% 报单插入
-define(THOST_FTDC_BFC_OrderInsert, <<"5">>).

%% 报单操作
-define(THOST_FTDC_BFC_OrderAction, <<"6">>).

%% 全部查询
-define(THOST_FTDC_BFC_AllQuery, <<"7">>).

%% 系统功能：登入/登出/修改密码等
-define(THOST_FTDC_BFC_log, <<"a">>).

%% 基本查询：查询基础数据，如合约，交易所等常量
-define(THOST_FTDC_BFC_BaseQry, <<"b">>).

%% 交易查询：如查成交，委托
-define(THOST_FTDC_BFC_TradeQry, <<"c">>).

%% 交易功能：报单，撤单
-define(THOST_FTDC_BFC_Trade, <<"d">>).

%% 银期转账
-define(THOST_FTDC_BFC_Virement, <<"e">>).

%% 风险监控
-define(THOST_FTDC_BFC_Risk, <<"f">>).

%% 查询/管理：查询会话，踢人等
-define(THOST_FTDC_BFC_Session, <<"g">>).

%% 风控通知控制
-define(THOST_FTDC_BFC_RiskNoticeCtl, <<"h">>).

%% 风控通知发送
-define(THOST_FTDC_BFC_RiskNotice, <<"i">>).

%% 察看经纪公司资金权限
-define(THOST_FTDC_BFC_BrokerDeposit, <<"j">>).

%% 资金查询
-define(THOST_FTDC_BFC_QueryFund, <<"k">>).

%% 报单查询
-define(THOST_FTDC_BFC_QueryOrder, <<"l">>).

%% 成交查询
-define(THOST_FTDC_BFC_QueryTrade, <<"m">>).

%% 持仓查询
-define(THOST_FTDC_BFC_QueryPosition, <<"n">>).

%% 行情查询
-define(THOST_FTDC_BFC_QueryMarketData, <<"o">>).

%% 用户事件查询
-define(THOST_FTDC_BFC_QueryUserEvent, <<"p">>).

%% 风险通知查询
-define(THOST_FTDC_BFC_QueryRiskNotify, <<"q">>).

%% 出入金查询
-define(THOST_FTDC_BFC_QueryFundChange, <<"r">>).

%% 投资者信息查询
-define(THOST_FTDC_BFC_QueryInvestor, <<"s">>).

%% 交易编码查询
-define(THOST_FTDC_BFC_QueryTradingCode, <<"t">>).

%% 强平
-define(THOST_FTDC_BFC_ForceClose, <<"u">>).

%% 压力测试
-define(THOST_FTDC_BFC_PressTest, <<"v">>).

%% 权益反算
-define(THOST_FTDC_BFC_RemainCalc, <<"w">>).

%% 净持仓保证金指标
-define(THOST_FTDC_BFC_NetPositionInd, <<"x">>).

%% 风险预算
-define(THOST_FTDC_BFC_RiskPredict, <<"y">>).

%% 数据导出
-define(THOST_FTDC_BFC_DataExport, <<"z">>).

%% 风控指标设置
-define(THOST_FTDC_BFC_RiskTargetSetup, <<"A">>).

%% 行情预警
-define(THOST_FTDC_BFC_MarketDataWarn, <<"B">>).

%% 业务通知查询
-define(THOST_FTDC_BFC_QryBizNotice, <<"C">>).

%% 业务通知模板设置
-define(THOST_FTDC_BFC_CfgBizNotice, <<"D">>).

%% 同步动态令牌
-define(THOST_FTDC_BFC_SyncOTP, <<"E">>).

%% 发送业务通知
-define(THOST_FTDC_BFC_SendBizNotice, <<"F">>).

%% 风险级别标准设置
-define(THOST_FTDC_BFC_CfgRiskLevelStd, <<"G">>).

%% 交易终端应急功能
-define(THOST_FTDC_BFC_TbCommand, <<"H">>).

%% 删除未知单
-define(THOST_FTDC_BFC_DeleteOrder, <<"J">>).

%% 预埋报单插入
-define(THOST_FTDC_BFC_ParkedOrderInsert, <<"K">>).

%% 预埋报单操作
-define(THOST_FTDC_BFC_ParkedOrderAction, <<"L">>).

%% 资金不够仍允许行权
-define(THOST_FTDC_BFC_ExecOrderNoCheck, <<"M">>).

%% 已经提交
-define(THOST_FTDC_OAS_Submitted, <<"a">>).

%% 已经接受
-define(THOST_FTDC_OAS_Accepted, <<"b">>).

%% 已经被拒绝
-define(THOST_FTDC_OAS_Rejected, <<"c">>).

%% 全部成交
-define(THOST_FTDC_OST_AllTraded, <<"0">>).

%% 部分成交还在队列中
-define(THOST_FTDC_OST_PartTradedQueueing, <<"1">>).

%% 部分成交不在队列中
-define(THOST_FTDC_OST_PartTradedNotQueueing, <<"2">>).

%% 未成交还在队列中
-define(THOST_FTDC_OST_NoTradeQueueing, <<"3">>).

%% 未成交不在队列中
-define(THOST_FTDC_OST_NoTradeNotQueueing, <<"4">>).

%% 撤单
-define(THOST_FTDC_OST_Canceled, <<"5">>).

%% 未知
-define(THOST_FTDC_OST_Unknown, <<"a">>).

%% 尚未触发
-define(THOST_FTDC_OST_NotTouched, <<"b">>).

%% 已触发
-define(THOST_FTDC_OST_Touched, <<"c">>).

%% 已经提交
-define(THOST_FTDC_OSS_InsertSubmitted, <<"0">>).

%% 撤单已经提交
-define(THOST_FTDC_OSS_CancelSubmitted, <<"1">>).

%% 修改已经提交
-define(THOST_FTDC_OSS_ModifySubmitted, <<"2">>).

%% 已经接受
-define(THOST_FTDC_OSS_Accepted, <<"3">>).

%% 报单已经被拒绝
-define(THOST_FTDC_OSS_InsertRejected, <<"4">>).

%% 撤单已经被拒绝
-define(THOST_FTDC_OSS_CancelRejected, <<"5">>).

%% 改单已经被拒绝
-define(THOST_FTDC_OSS_ModifyRejected, <<"6">>).

%% 今日持仓
-define(THOST_FTDC_PSD_Today, <<"1">>).

%% 历史持仓
-define(THOST_FTDC_PSD_History, <<"2">>).

%% 使用历史持仓
-define(THOST_FTDC_PDT_UseHistory, <<"1">>).

%% 不使用历史持仓
-define(THOST_FTDC_PDT_NoUseHistory, <<"2">>).

%% 代理
-define(THOST_FTDC_ER_Broker, <<"1">>).

%% 自营
-define(THOST_FTDC_ER_Host, <<"2">>).

%% 做市商
-define(THOST_FTDC_ER_Maker, <<"3">>).

%% 期货
-define(THOST_FTDC_PC_Futures, <<"1">>).

%% 期货期权
-define(THOST_FTDC_PC_Options, <<"2">>).

%% 组合
-define(THOST_FTDC_PC_Combination, <<"3">>).

%% 即期
-define(THOST_FTDC_PC_Spot, <<"4">>).

%% 期转现
-define(THOST_FTDC_PC_EFP, <<"5">>).

%% 现货期权
-define(THOST_FTDC_PC_SpotOption, <<"6">>).

%% 个股期权
-define(THOST_FTDC_PC_ETFOption, <<"7">>).

%% 证券
-define(THOST_FTDC_PC_Stock, <<"8">>).

%% 未上市
-define(THOST_FTDC_IP_NotStart, <<"0">>).

%% 上市
-define(THOST_FTDC_IP_Started, <<"1">>).

%% 停牌
-define(THOST_FTDC_IP_Pause, <<"2">>).

%% 到期
-define(THOST_FTDC_IP_Expired, <<"3">>).

%% 买
-define(THOST_FTDC_D_Buy, <<"0">>).

%% 卖
-define(THOST_FTDC_D_Sell, <<"1">>).

%% 净持仓
-define(THOST_FTDC_PT_Net, <<"1">>).

%% 综合持仓
-define(THOST_FTDC_PT_Gross, <<"2">>).

%% 净
-define(THOST_FTDC_PD_Net, <<"1">>).

%% 多头
-define(THOST_FTDC_PD_Long, <<"2">>).

%% 空头
-define(THOST_FTDC_PD_Short, <<"3">>).

%% 不活跃
-define(THOST_FTDC_SS_NonActive, <<"1">>).

%% 启动
-define(THOST_FTDC_SS_Startup, <<"2">>).

%% 操作
-define(THOST_FTDC_SS_Operating, <<"3">>).

%% 结算
-define(THOST_FTDC_SS_Settlement, <<"4">>).

%% 结算完成
-define(THOST_FTDC_SS_SettlementFinished, <<"5">>).

%% 交易费率
-define(THOST_FTDC_RA_Trade, <<"0">>).

%% 结算费率
-define(THOST_FTDC_RA_Settlement, <<"1">>).

%% 投机
-define(THOST_FTDC_HF_Speculation, <<"1">>).

%% 套利
-define(THOST_FTDC_HF_Arbitrage, <<"2">>).

%% 套保
-define(THOST_FTDC_HF_Hedge, <<"3">>).

%% 备兑
-define(THOST_FTDC_HF_Covered, <<"4">>).

%% 做市商
-define(THOST_FTDC_HF_MarketMaker, <<"5">>).

%% 投机
-define(THOST_FTDC_BHF_Speculation, <<"1">>).

%% 套利
-define(THOST_FTDC_BHF_Arbitrage, <<"2">>).

%% 套保
-define(THOST_FTDC_BHF_Hedge, <<"3">>).

%% 投机
-define(THOST_FTDC_CIDT_Speculation, <<"1">>).

%% 套利
-define(THOST_FTDC_CIDT_Arbitrage, <<"2">>).

%% 套保
-define(THOST_FTDC_CIDT_Hedge, <<"3">>).

%% 做市商
-define(THOST_FTDC_CIDT_MarketMaker, <<"5">>).

%% 任意价
-define(THOST_FTDC_OPT_AnyPrice, <<"1">>).

%% 限价
-define(THOST_FTDC_OPT_LimitPrice, <<"2">>).

%% 最优价
-define(THOST_FTDC_OPT_BestPrice, <<"3">>).

%% 最新价
-define(THOST_FTDC_OPT_LastPrice, <<"4">>).

%% 最新价浮动上浮1个ticks
-define(THOST_FTDC_OPT_LastPricePlusOneTicks, <<"5">>).

%% 最新价浮动上浮2个ticks
-define(THOST_FTDC_OPT_LastPricePlusTwoTicks, <<"6">>).

%% 最新价浮动上浮3个ticks
-define(THOST_FTDC_OPT_LastPricePlusThreeTicks, <<"7">>).

%% 卖一价
-define(THOST_FTDC_OPT_AskPrice1, <<"8">>).

%% 卖一价浮动上浮1个ticks
-define(THOST_FTDC_OPT_AskPrice1PlusOneTicks, <<"9">>).

%% 卖一价浮动上浮2个ticks
-define(THOST_FTDC_OPT_AskPrice1PlusTwoTicks, <<"A">>).

%% 卖一价浮动上浮3个ticks
-define(THOST_FTDC_OPT_AskPrice1PlusThreeTicks, <<"B">>).

%% 买一价
-define(THOST_FTDC_OPT_BidPrice1, <<"C">>).

%% 买一价浮动上浮1个ticks
-define(THOST_FTDC_OPT_BidPrice1PlusOneTicks, <<"D">>).

%% 买一价浮动上浮2个ticks
-define(THOST_FTDC_OPT_BidPrice1PlusTwoTicks, <<"E">>).

%% 买一价浮动上浮3个ticks
-define(THOST_FTDC_OPT_BidPrice1PlusThreeTicks, <<"F">>).

%% 五档价
-define(THOST_FTDC_OPT_FiveLevelPrice, <<"G">>).

%% 本方最优价
-define(THOST_FTDC_OPT_BestPriceThisSide, <<"H">>).

%% 开仓
-define(THOST_FTDC_OF_Open, <<"0">>).

%% 平仓
-define(THOST_FTDC_OF_Close, <<"1">>).

%% 强平
-define(THOST_FTDC_OF_ForceClose, <<"2">>).

%% 平今
-define(THOST_FTDC_OF_CloseToday, <<"3">>).

%% 平昨
-define(THOST_FTDC_OF_CloseYesterday, <<"4">>).

%% 强减
-define(THOST_FTDC_OF_ForceOff, <<"5">>).

%% 本地强平
-define(THOST_FTDC_OF_LocalForceClose, <<"6">>).

%% 非强平
-define(THOST_FTDC_FCC_NotForceClose, <<"0">>).

%% 资金不足
-define(THOST_FTDC_FCC_LackDeposit, <<"1">>).

%% 客户超仓
-define(THOST_FTDC_FCC_ClientOverPositionLimit, <<"2">>).

%% 会员超仓
-define(THOST_FTDC_FCC_MemberOverPositionLimit, <<"3">>).

%% 持仓非整数倍
-define(THOST_FTDC_FCC_NotMultiple, <<"4">>).

%% 违规
-define(THOST_FTDC_FCC_Violation, <<"5">>).

%% 其它
-define(THOST_FTDC_FCC_Other, <<"6">>).

%% 自然人临近交割
-define(THOST_FTDC_FCC_PersonDeliv, <<"7">>).

%% 正常
-define(THOST_FTDC_ORDT_Normal, <<"0">>).

%% 报价衍生
-define(THOST_FTDC_ORDT_DeriveFromQuote, <<"1">>).

%% 组合衍生
-define(THOST_FTDC_ORDT_DeriveFromCombination, <<"2">>).

%% 组合报单
-define(THOST_FTDC_ORDT_Combination, <<"3">>).

%% 条件单
-define(THOST_FTDC_ORDT_ConditionalOrder, <<"4">>).

%% 互换单
-define(THOST_FTDC_ORDT_Swap, <<"5">>).

%% 立即完成，否则撤销
-define(THOST_FTDC_TC_IOC, <<"1">>).

%% 本节有效
-define(THOST_FTDC_TC_GFS, <<"2">>).

%% 当日有效
-define(THOST_FTDC_TC_GFD, <<"3">>).

%% 指定日期前有效
-define(THOST_FTDC_TC_GTD, <<"4">>).

%% 撤销前有效
-define(THOST_FTDC_TC_GTC, <<"5">>).

%% 集合竞价有效
-define(THOST_FTDC_TC_GFA, <<"6">>).

%% 任何数量
-define(THOST_FTDC_VC_AV, <<"1">>).

%% 最小数量
-define(THOST_FTDC_VC_MV, <<"2">>).

%% 全部数量
-define(THOST_FTDC_VC_CV, <<"3">>).

%% 立即
-define(THOST_FTDC_CC_Immediately, <<"1">>).

%% 止损
-define(THOST_FTDC_CC_Touch, <<"2">>).

%% 止赢
-define(THOST_FTDC_CC_TouchProfit, <<"3">>).

%% 预埋单
-define(THOST_FTDC_CC_ParkedOrder, <<"4">>).

%% 最新价大于条件价
-define(THOST_FTDC_CC_LastPriceGreaterThanStopPrice, <<"5">>).

%% 最新价大于等于条件价
-define(THOST_FTDC_CC_LastPriceGreaterEqualStopPrice, <<"6">>).

%% 最新价小于条件价
-define(THOST_FTDC_CC_LastPriceLesserThanStopPrice, <<"7">>).

%% 最新价小于等于条件价
-define(THOST_FTDC_CC_LastPriceLesserEqualStopPrice, <<"8">>).

%% 卖一价大于条件价
-define(THOST_FTDC_CC_AskPriceGreaterThanStopPrice, <<"9">>).

%% 卖一价大于等于条件价
-define(THOST_FTDC_CC_AskPriceGreaterEqualStopPrice, <<"A">>).

%% 卖一价小于条件价
-define(THOST_FTDC_CC_AskPriceLesserThanStopPrice, <<"B">>).

%% 卖一价小于等于条件价
-define(THOST_FTDC_CC_AskPriceLesserEqualStopPrice, <<"C">>).

%% 买一价大于条件价
-define(THOST_FTDC_CC_BidPriceGreaterThanStopPrice, <<"D">>).

%% 买一价大于等于条件价
-define(THOST_FTDC_CC_BidPriceGreaterEqualStopPrice, <<"E">>).

%% 买一价小于条件价
-define(THOST_FTDC_CC_BidPriceLesserThanStopPrice, <<"F">>).

%% 买一价小于等于条件价
-define(THOST_FTDC_CC_BidPriceLesserEqualStopPrice, <<"H">>).

%% 删除
-define(THOST_FTDC_AF_Delete, <<"0">>).

%% 修改
-define(THOST_FTDC_AF_Modify, <<"3">>).

%% 可以交易
-define(THOST_FTDC_TR_Allow, <<"0">>).

%% 只能平仓
-define(THOST_FTDC_TR_CloseOnly, <<"1">>).

%% 不能交易
-define(THOST_FTDC_TR_Forbidden, <<"2">>).

%% 来自参与者
-define(THOST_FTDC_OSRC_Participant, <<"0">>).

%% 来自管理员
-define(THOST_FTDC_OSRC_Administrator, <<"1">>).

%% 组合持仓拆分为单一持仓,初始化不应包含该类型的持仓
-define(THOST_FTDC_TRDT_SplitCombination, <<"#">>).

%% 普通成交
-define(THOST_FTDC_TRDT_Common, <<"0">>).

%% 期权执行
-define(THOST_FTDC_TRDT_OptionsExecution, <<"1">>).

%% OTC成交
-define(THOST_FTDC_TRDT_OTC, <<"2">>).

%% 期转现衍生成交
-define(THOST_FTDC_TRDT_EFPDerived, <<"3">>).

%% 组合衍生成交
-define(THOST_FTDC_TRDT_CombinationDerived, <<"4">>).

%% 前成交价
-define(THOST_FTDC_PSRC_LastPrice, <<"0">>).

%% 买委托价
-define(THOST_FTDC_PSRC_Buy, <<"1">>).

%% 卖委托价
-define(THOST_FTDC_PSRC_Sell, <<"2">>).

%% 开盘前
-define(THOST_FTDC_IS_BeforeTrading, <<"0">>).

%% 非交易
-define(THOST_FTDC_IS_NoTrading, <<"1">>).

%% 连续交易
-define(THOST_FTDC_IS_Continous, <<"2">>).

%% 集合竞价报单
-define(THOST_FTDC_IS_AuctionOrdering, <<"3">>).

%% 集合竞价价格平衡
-define(THOST_FTDC_IS_AuctionBalance, <<"4">>).

%% 集合竞价撮合
-define(THOST_FTDC_IS_AuctionMatch, <<"5">>).

%% 收盘
-define(THOST_FTDC_IS_Closed, <<"6">>).

%% 自动切换
-define(THOST_FTDC_IER_Automatic, <<"1">>).

%% 手动切换
-define(THOST_FTDC_IER_Manual, <<"2">>).

%% 熔断
-define(THOST_FTDC_IER_Fuse, <<"3">>).

%% 未上传
-define(THOST_FTDC_BS_NoUpload, <<"1">>).

%% 已上传
-define(THOST_FTDC_BS_Uploaded, <<"2">>).

%% 审核失败
-define(THOST_FTDC_BS_Failed, <<"3">>).

%% 按所有品种
-define(THOST_FTDC_RS_All, <<"1">>).

%% 按品种
-define(THOST_FTDC_RS_ByProduct, <<"2">>).

%% 按成交手数
-define(THOST_FTDC_RP_ByVolume, <<"1">>).

%% 按留存手续费
-define(THOST_FTDC_RP_ByFeeOnHand, <<"2">>).

%% 级别1
-define(THOST_FTDC_RL_Level1, <<"1">>).

%% 级别2
-define(THOST_FTDC_RL_Level2, <<"2">>).

%% 级别3
-define(THOST_FTDC_RL_Level3, <<"3">>).

%% 级别4
-define(THOST_FTDC_RL_Level4, <<"4">>).

%% 级别5
-define(THOST_FTDC_RL_Level5, <<"5">>).

%% 级别6
-define(THOST_FTDC_RL_Level6, <<"6">>).

%% 级别7
-define(THOST_FTDC_RL_Level7, <<"7">>).

%% 级别8
-define(THOST_FTDC_RL_Level8, <<"8">>).

%% 级别9
-define(THOST_FTDC_RL_Level9, <<"9">>).

%% 分阶段返还
-define(THOST_FTDC_RSD_ByPeriod, <<"1">>).

%% 按某一标准
-define(THOST_FTDC_RSD_ByStandard, <<"2">>).

%% 质出
-define(THOST_FTDC_MT_Out, <<"0">>).

%% 质入
-define(THOST_FTDC_MT_In, <<"1">>).

%% 质押比例
-define(THOST_FTDC_ISPI_MortgageRatio, <<"4">>).

%% 保证金算法
-define(THOST_FTDC_ISPI_MarginWay, <<"5">>).

%% 结算单结存是否包含质押
-define(THOST_FTDC_ISPI_BillDeposit, <<"9">>).

%% 质押比例
-define(THOST_FTDC_ESPI_MortgageRatio, <<"1">>).

%% 分项资金导入项
-define(THOST_FTDC_ESPI_OtherFundItem, <<"2">>).

%% 分项资金入交易所出入金
-define(THOST_FTDC_ESPI_OtherFundImport, <<"3">>).

%% 中金所开户最低可用金额
-define(THOST_FTDC_ESPI_CFFEXMinPrepa, <<"6">>).

%% 郑商所结算方式
-define(THOST_FTDC_ESPI_CZCESettlementType, <<"7">>).

%% 交易所交割手续费收取方式
-define(THOST_FTDC_ESPI_ExchDelivFeeMode, <<"9">>).

%% 投资者交割手续费收取方式
-define(THOST_FTDC_ESPI_DelivFeeMode, <<"0">>).

%% 郑商所组合持仓保证金收取方式
-define(THOST_FTDC_ESPI_CZCEComMarginType, <<"A">>).

%% 大商所套利保证金是否优惠
-define(THOST_FTDC_ESPI_DceComMarginType, <<"B">>).

%% 虚值期权保证金优惠比率
-define(THOST_FTDC_ESPI_OptOutDisCountRate, <<"a">>).

%% 最低保障系数
-define(THOST_FTDC_ESPI_OptMiniGuarantee, <<"b">>).

%% 投资者代码最小长度
-define(THOST_FTDC_SPI_InvestorIDMinLength, <<"1">>).

%% 投资者帐号代码最小长度
-define(THOST_FTDC_SPI_AccountIDMinLength, <<"2">>).

%% 投资者开户默认登录权限
-define(THOST_FTDC_SPI_UserRightLogon, <<"3">>).

%% 投资者交易结算单成交汇总方式
-define(THOST_FTDC_SPI_SettlementBillTrade, <<"4">>).

%% 统一开户更新交易编码方式
-define(THOST_FTDC_SPI_TradingCode, <<"5">>).

%% 结算是否判断存在未复核的出入金和分项资金
-define(THOST_FTDC_SPI_CheckFund, <<"6">>).

%% 是否启用手续费模板数据权限
-define(THOST_FTDC_SPI_CommModelRight, <<"7">>).

%% 是否启用保证金率模板数据权限
-define(THOST_FTDC_SPI_MarginModelRight, <<"9">>).

%% 是否规范用户才能激活
-define(THOST_FTDC_SPI_IsStandardActive, <<"8">>).

%% 上传的交易所结算文件路径
-define(THOST_FTDC_SPI_UploadSettlementFile, <<"U">>).

%% 上报保证金监控中心文件路径
-define(THOST_FTDC_SPI_DownloadCSRCFile, <<"D">>).

%% 生成的结算单文件路径
-define(THOST_FTDC_SPI_SettlementBillFile, <<"S">>).

%% 证监会文件标识
-define(THOST_FTDC_SPI_CSRCOthersFile, <<"C">>).

%% 投资者照片路径
-define(THOST_FTDC_SPI_InvestorPhoto, <<"P">>).

%% 全结经纪公司上传文件路径
-define(THOST_FTDC_SPI_CSRCData, <<"R">>).

%% 开户密码录入方式
-define(THOST_FTDC_SPI_InvestorPwdModel, <<"I">>).

%% 投资者中金所结算文件下载路径
-define(THOST_FTDC_SPI_CFFEXInvestorSettleFile, <<"F">>).

%% 投资者代码编码方式
-define(THOST_FTDC_SPI_InvestorIDType, <<"a">>).

%% 休眠户最高权益
-define(THOST_FTDC_SPI_FreezeMaxReMain, <<"r">>).

%% 手续费相关操作实时上场开关
-define(THOST_FTDC_SPI_IsSync, <<"A">>).

%% 解除开仓权限限制
-define(THOST_FTDC_SPI_RelieveOpenLimit, <<"O">>).

%% 是否规范用户才能休眠
-define(THOST_FTDC_SPI_IsStandardFreeze, <<"X">>).

%% 郑商所是否开放所有品种套保交易
-define(THOST_FTDC_SPI_CZCENormalProductHedge, <<"B">>).

%% 系统加密算法
-define(THOST_FTDC_TPID_EncryptionStandard, <<"E">>).

%% 系统风险算法
-define(THOST_FTDC_TPID_RiskMode, <<"R">>).

%% 系统风险算法是否全局 0-否 1-是
-define(THOST_FTDC_TPID_RiskModeGlobal, <<"G">>).

%% 密码加密算法
-define(THOST_FTDC_TPID_modeEncode, <<"P">>).

%% 价格小数位数参数
-define(THOST_FTDC_TPID_tickMode, <<"T">>).

%% 用户最大会话数
-define(THOST_FTDC_TPID_SingleUserSessionMaxNum, <<"S">>).

%% 最大连续登录失败数
-define(THOST_FTDC_TPID_LoginFailMaxNum, <<"L">>).

%% 是否强制认证
-define(THOST_FTDC_TPID_IsAuthForce, <<"A">>).

%% 是否冻结证券持仓
-define(THOST_FTDC_TPID_IsPosiFreeze, <<"F">>).

%% 是否限仓
-define(THOST_FTDC_TPID_IsPosiLimit, <<"M">>).

%% 郑商所询价时间间隔
-define(THOST_FTDC_TPID_ForQuoteTimeInterval, <<"Q">>).

%% 是否期货限仓
-define(THOST_FTDC_TPID_IsFuturePosiLimit, <<"B">>).

%% 是否期货下单频率限制
-define(THOST_FTDC_TPID_IsFutureOrderFreq, <<"C">>).

%% 是否报单类型限制
-define(THOST_FTDC_TPID_IsOrderTypeLimit, <<"D">>).

%% 行权冻结是否计算盈利
-define(THOST_FTDC_TPID_IsExecOrderProfit, <<"H">>).

%% 资金数据
-define(THOST_FTDC_FI_SettlementFund, <<"F">>).

%% 成交数据
-define(THOST_FTDC_FI_Trade, <<"T">>).

%% 投资者持仓数据
-define(THOST_FTDC_FI_InvestorPosition, <<"P">>).

%% 投资者分项资金数据
-define(THOST_FTDC_FI_SubEntryFund, <<"O">>).

%% 组合持仓数据
-define(THOST_FTDC_FI_CZCECombinationPos, <<"C">>).

%% 上报保证金监控中心数据
-define(THOST_FTDC_FI_CSRCData, <<"R">>).

%% 郑商所平仓了结数据
-define(THOST_FTDC_FI_CZCEClose, <<"L">>).

%% 郑商所非平仓了结数据
-define(THOST_FTDC_FI_CZCENoClose, <<"N">>).

%% 持仓明细数据
-define(THOST_FTDC_FI_PositionDtl, <<"D">>).

%% 期权执行文件
-define(THOST_FTDC_FI_OptionStrike, <<"S">>).

%% 结算价比对文件
-define(THOST_FTDC_FI_SettlementPriceComparison, <<"M">>).

%% 上期所非持仓变动明细
-define(THOST_FTDC_FI_NonTradePosChange, <<"B">>).

%% 结算
-define(THOST_FTDC_FUT_Settlement, <<"0">>).

%% 核对
-define(THOST_FTDC_FUT_Check, <<"1">>).

%% 文本文件(.txt)
-define(THOST_FTDC_FFT_Txt, <<"0">>).

%% 压缩文件(.zip)
-define(THOST_FTDC_FFT_Zip, <<"1">>).

%% DBF文件(.dbf)
-define(THOST_FTDC_FFT_DBF, <<"2">>).

%% 上传成功
-define(THOST_FTDC_FUS_SucceedUpload, <<"1">>).

%% 上传失败
-define(THOST_FTDC_FUS_FailedUpload, <<"2">>).

%% 导入成功
-define(THOST_FTDC_FUS_SucceedLoad, <<"3">>).

%% 导入部分成功
-define(THOST_FTDC_FUS_PartSucceedLoad, <<"4">>).

%% 导入失败
-define(THOST_FTDC_FUS_FailedLoad, <<"5">>).

%% 移出
-define(THOST_FTDC_TD_Out, <<"0">>).

%% 移入
-define(THOST_FTDC_TD_In, <<"1">>).

%% 没有特殊创建规则
-define(THOST_FTDC_SC_NoSpecialRule, <<"0">>).

%% 不包含春节
-define(THOST_FTDC_SC_NoSpringFestival, <<"1">>).

%% 上一合约结算价
-define(THOST_FTDC_IPT_LastSettlement, <<"1">>).

%% 上一合约收盘价
-define(THOST_FTDC_IPT_LaseClose, <<"2">>).

%% 活跃
-define(THOST_FTDC_PLP_Active, <<"1">>).

%% 不活跃
-define(THOST_FTDC_PLP_NonActive, <<"2">>).

%% 注销
-define(THOST_FTDC_PLP_Canceled, <<"3">>).

%% 现金交割
-define(THOST_FTDC_DM_CashDeliv, <<"1">>).

%% 实物交割
-define(THOST_FTDC_DM_CommodityDeliv, <<"2">>).

%% 出入金
-define(THOST_FTDC_FIOT_FundIO, <<"1">>).

%% 银期转帐
-define(THOST_FTDC_FIOT_Transfer, <<"2">>).

%% 银期换汇
-define(THOST_FTDC_FIOT_SwapCurrency, <<"3">>).

%% 银行存款
-define(THOST_FTDC_FT_Deposite, <<"1">>).

%% 分项资金
-define(THOST_FTDC_FT_ItemFund, <<"2">>).

%% 公司调整
-define(THOST_FTDC_FT_Company, <<"3">>).

%% 资金内转
-define(THOST_FTDC_FT_InnerTransfer, <<"4">>).

%% 入金
-define(THOST_FTDC_FD_In, <<"1">>).

%% 出金
-define(THOST_FTDC_FD_Out, <<"2">>).

%% 已录入
-define(THOST_FTDC_FS_Record, <<"1">>).

%% 已复核
-define(THOST_FTDC_FS_Check, <<"2">>).

%% 已冲销
-define(THOST_FTDC_FS_Charge, <<"3">>).

%% 未发布
-define(THOST_FTDC_PS_None, <<"1">>).

%% 正在发布
-define(THOST_FTDC_PS_Publishing, <<"2">>).

%% 已发布
-define(THOST_FTDC_PS_Published, <<"3">>).

%% 不活跃
-define(THOST_FTDC_ES_NonActive, <<"1">>).

%% 启动
-define(THOST_FTDC_ES_Startup, <<"2">>).

%% 交易开始初始化
-define(THOST_FTDC_ES_Initialize, <<"3">>).

%% 交易完成初始化
-define(THOST_FTDC_ES_Initialized, <<"4">>).

%% 收市开始
-define(THOST_FTDC_ES_Close, <<"5">>).

%% 收市完成
-define(THOST_FTDC_ES_Closed, <<"6">>).

%% 结算
-define(THOST_FTDC_ES_Settlement, <<"7">>).

%% 初始
-define(THOST_FTDC_STS_Initialize, <<"0">>).

%% 结算中
-define(THOST_FTDC_STS_Settlementing, <<"1">>).

%% 已结算
-define(THOST_FTDC_STS_Settlemented, <<"2">>).

%% 结算完成
-define(THOST_FTDC_STS_Finished, <<"3">>).

%% 自然人
-define(THOST_FTDC_CT_Person, <<"0">>).

%% 法人
-define(THOST_FTDC_CT_Company, <<"1">>).

%% 投资基金
-define(THOST_FTDC_CT_Fund, <<"2">>).

%% 特殊法人
-define(THOST_FTDC_CT_SpecialOrgan, <<"3">>).

%% 资管户
-define(THOST_FTDC_CT_Asset, <<"4">>).

%% 交易会员
-define(THOST_FTDC_BT_Trade, <<"0">>).

%% 交易结算会员
-define(THOST_FTDC_BT_TradeSettle, <<"1">>).

%% 低风险客户
-define(THOST_FTDC_FAS_Low, <<"1">>).

%% 普通客户
-define(THOST_FTDC_FAS_Normal, <<"2">>).

%% 关注客户
-define(THOST_FTDC_FAS_Focus, <<"3">>).

%% 风险客户
-define(THOST_FTDC_FAS_Risk, <<"4">>).

%% 按交易收取
-define(THOST_FTDC_FAS_ByTrade, <<"1">>).

%% 按交割收取
-define(THOST_FTDC_FAS_ByDeliv, <<"2">>).

%% 不收
-define(THOST_FTDC_FAS_None, <<"3">>).

%% 按指定手续费收取
-define(THOST_FTDC_FAS_FixFee, <<"4">>).

%% 交易密码
-define(THOST_FTDC_PWDT_Trade, <<"1">>).

%% 资金密码
-define(THOST_FTDC_PWDT_Account, <<"2">>).

%% 浮盈浮亏都计算
-define(THOST_FTDC_AG_All, <<"1">>).

%% 浮盈不计，浮亏计
-define(THOST_FTDC_AG_OnlyLost, <<"2">>).

%% 浮盈计，浮亏不计
-define(THOST_FTDC_AG_OnlyGain, <<"3">>).

%% 浮盈浮亏都不计算
-define(THOST_FTDC_AG_None, <<"4">>).

%% 包含平仓盈利
-define(THOST_FTDC_ICP_Include, <<"0">>).

%% 不包含平仓盈利
-define(THOST_FTDC_ICP_NotInclude, <<"2">>).

%% 无仓无成交不受可提比例限制
-define(THOST_FTDC_AWT_Enable, <<"0">>).

%% 受可提比例限制
-define(THOST_FTDC_AWT_Disable, <<"2">>).

%% 无仓不受可提比例限制
-define(THOST_FTDC_AWT_NoHoldEnable, <<"3">>).

%% 不核对
-define(THOST_FTDC_FPWD_UnCheck, <<"0">>).

%% 核对
-define(THOST_FTDC_FPWD_Check, <<"1">>).

%% 银行转期货
-define(THOST_FTDC_TT_BankToFuture, <<"0">>).

%% 期货转银行
-define(THOST_FTDC_TT_FutureToBank, <<"1">>).

%% 无效或失败
-define(THOST_FTDC_TVF_Invalid, <<"0">>).

%% 有效
-define(THOST_FTDC_TVF_Valid, <<"1">>).

%% 冲正
-define(THOST_FTDC_TVF_Reverse, <<"2">>).

%% 错单
-define(THOST_FTDC_RN_CD, <<"0">>).

%% 资金在途
-define(THOST_FTDC_RN_ZT, <<"1">>).

%% 其它
-define(THOST_FTDC_RN_QT, <<"2">>).

%% 未知
-define(THOST_FTDC_SEX_None, <<"0">>).

%% 男
-define(THOST_FTDC_SEX_Man, <<"1">>).

%% 女
-define(THOST_FTDC_SEX_Woman, <<"2">>).

%% 投资者
-define(THOST_FTDC_UT_Investor, <<"0">>).

%% 操作员
-define(THOST_FTDC_UT_Operator, <<"1">>).

%% 管理员
-define(THOST_FTDC_UT_SuperUser, <<"2">>).

%% 保证金率
-define(THOST_FTDC_RATETYPE_MarginRate, <<"2">>).

%% 交易结算单
-define(THOST_FTDC_NOTETYPE_TradeSettleBill, <<"1">>).

%% 交易结算月报
-define(THOST_FTDC_NOTETYPE_TradeSettleMonth, <<"2">>).

%% 追加保证金通知书
-define(THOST_FTDC_NOTETYPE_CallMarginNotes, <<"3">>).

%% 强行平仓通知书
-define(THOST_FTDC_NOTETYPE_ForceCloseNotes, <<"4">>).

%% 成交通知书
-define(THOST_FTDC_NOTETYPE_TradeNotes, <<"5">>).

%% 交割通知书
-define(THOST_FTDC_NOTETYPE_DelivNotes, <<"6">>).

%% 逐日盯市
-define(THOST_FTDC_SBS_Day, <<"1">>).

%% 逐笔对冲
-define(THOST_FTDC_SBS_Volume, <<"2">>).

%% 日报
-define(THOST_FTDC_ST_Day, <<"0">>).

%% 月报
-define(THOST_FTDC_ST_Month, <<"1">>).

%% 登录
-define(THOST_FTDC_URT_Logon, <<"1">>).

%% 银期转帐
-define(THOST_FTDC_URT_Transfer, <<"2">>).

%% 邮寄结算单
-define(THOST_FTDC_URT_EMail, <<"3">>).

%% 传真结算单
-define(THOST_FTDC_URT_Fax, <<"4">>).

%% 条件单
-define(THOST_FTDC_URT_ConditionOrder, <<"5">>).

%% 昨结算价
-define(THOST_FTDC_MPT_PreSettlementPrice, <<"1">>).

%% 最新价
-define(THOST_FTDC_MPT_SettlementPrice, <<"2">>).

%% 成交均价
-define(THOST_FTDC_MPT_AveragePrice, <<"3">>).

%% 开仓价
-define(THOST_FTDC_MPT_OpenPrice, <<"4">>).

%% 未生成
-define(THOST_FTDC_BGS_None, <<"0">>).

%% 生成中
-define(THOST_FTDC_BGS_NoGenerated, <<"1">>).

%% 已生成
-define(THOST_FTDC_BGS_Generated, <<"2">>).

%% 持仓处理算法
-define(THOST_FTDC_AT_HandlePositionAlgo, <<"1">>).

%% 寻找保证金率算法
-define(THOST_FTDC_AT_FindMarginRateAlgo, <<"2">>).

%% 基本
-define(THOST_FTDC_HPA_Base, <<"1">>).

%% 大连商品交易所
-define(THOST_FTDC_HPA_DCE, <<"2">>).

%% 郑州商品交易所
-define(THOST_FTDC_HPA_CZCE, <<"3">>).

%% 基本
-define(THOST_FTDC_FMRA_Base, <<"1">>).

%% 大连商品交易所
-define(THOST_FTDC_FMRA_DCE, <<"2">>).

%% 郑州商品交易所
-define(THOST_FTDC_FMRA_CZCE, <<"3">>).

%% 基本
-define(THOST_FTDC_HTAA_Base, <<"1">>).

%% 大连商品交易所
-define(THOST_FTDC_HTAA_DCE, <<"2">>).

%% 郑州商品交易所
-define(THOST_FTDC_HTAA_CZCE, <<"3">>).

%% 指定下单人
-define(THOST_FTDC_PST_Order, <<"1">>).

%% 开户授权人
-define(THOST_FTDC_PST_Open, <<"2">>).

%% 资金调拨人
-define(THOST_FTDC_PST_Fund, <<"3">>).

%% 结算单确认人
-define(THOST_FTDC_PST_Settlement, <<"4">>).

%% 法人
-define(THOST_FTDC_PST_Company, <<"5">>).

%% 法人代表
-define(THOST_FTDC_PST_Corporation, <<"6">>).

%% 投资者联系人
-define(THOST_FTDC_PST_LinkMan, <<"7">>).

%% 分户管理资产负责人
-define(THOST_FTDC_PST_Ledger, <<"8">>).

%% 托（保）管人
-define(THOST_FTDC_PST_Trustee, <<"9">>).

%% 托（保）管机构法人代表
-define(THOST_FTDC_PST_TrusteeCorporation, <<"A">>).

%% 托（保）管机构开户授权人
-define(THOST_FTDC_PST_TrusteeOpen, <<"B">>).

%% 托（保）管机构联系人
-define(THOST_FTDC_PST_TrusteeContact, <<"C">>).

%% 境外自然人参考证件
-define(THOST_FTDC_PST_ForeignerRefer, <<"D">>).

%% 法人代表参考证件
-define(THOST_FTDC_PST_CorporationRefer, <<"E">>).

%% 所有
-define(THOST_FTDC_QIR_All, <<"1">>).

%% 查询分类
-define(THOST_FTDC_QIR_Group, <<"2">>).

%% 单一投资者
-define(THOST_FTDC_QIR_Single, <<"3">>).

%% 正常
-define(THOST_FTDC_IRS_Normal, <<"1">>).

%% 警告
-define(THOST_FTDC_IRS_Warn, <<"2">>).

%% 追保
-define(THOST_FTDC_IRS_Call, <<"3">>).

%% 强平
-define(THOST_FTDC_IRS_Force, <<"4">>).

%% 异常
-define(THOST_FTDC_IRS_Exception, <<"5">>).

%% 登录
-define(THOST_FTDC_UET_Login, <<"1">>).

%% 登出
-define(THOST_FTDC_UET_Logout, <<"2">>).

%% 交易成功
-define(THOST_FTDC_UET_Trading, <<"3">>).

%% 交易失败
-define(THOST_FTDC_UET_TradingError, <<"4">>).

%% 修改密码
-define(THOST_FTDC_UET_UpdatePassword, <<"5">>).

%% 客户端认证
-define(THOST_FTDC_UET_Authenticate, <<"6">>).

%% 其他
-define(THOST_FTDC_UET_Other, <<"9">>).

%% 先开先平
-define(THOST_FTDC_ICS_Close, <<"0">>).

%% 先平今再平昨
-define(THOST_FTDC_ICS_CloseToday, <<"1">>).

%% ----
-define(THOST_FTDC_SM_Non, <<"0">>).

%% 按合约统计
-define(THOST_FTDC_SM_Instrument, <<"1">>).

%% 按产品统计
-define(THOST_FTDC_SM_Product, <<"2">>).

%% 按投资者统计
-define(THOST_FTDC_SM_Investor, <<"3">>).

%% 未发送
-define(THOST_FTDC_PAOS_NotSend, <<"1">>).

%% 已发送
-define(THOST_FTDC_PAOS_Send, <<"2">>).

%% 已删除
-define(THOST_FTDC_PAOS_Deleted, <<"3">>).

%% 正在处理
-define(THOST_FTDC_VDS_Dealing, <<"1">>).

%% 处理成功
-define(THOST_FTDC_VDS_DeaclSucceed, <<"2">>).

%% 综合交易平台
-define(THOST_FTDC_ORGS_Standard, <<"0">>).

%% 易盛系统
-define(THOST_FTDC_ORGS_ESunny, <<"1">>).

%% 金仕达V6系统
-define(THOST_FTDC_ORGS_KingStarV6, <<"2">>).

%% 正常处理中
-define(THOST_FTDC_VTS_NaturalDeal, <<"0">>).

%% 成功结束
-define(THOST_FTDC_VTS_SucceedEnd, <<"1">>).

%% 失败结束
-define(THOST_FTDC_VTS_FailedEND, <<"2">>).

%% 异常中
-define(THOST_FTDC_VTS_Exception, <<"3">>).

%% 已人工异常处理
-define(THOST_FTDC_VTS_ManualDeal, <<"4">>).

%% 通讯异常 ，请人工处理
-define(THOST_FTDC_VTS_MesException, <<"5">>).

%% 系统出错，请人工处理
-define(THOST_FTDC_VTS_SysException, <<"6">>).

%% 存折
-define(THOST_FTDC_VBAT_BankBook, <<"1">>).

%% 储蓄卡
-define(THOST_FTDC_VBAT_BankCard, <<"2">>).

%% 信用卡
-define(THOST_FTDC_VBAT_CreditCard, <<"3">>).

%% 正常
-define(THOST_FTDC_VMS_Natural, <<"0">>).

%% 销户
-define(THOST_FTDC_VMS_Canceled, <<"9">>).

%% 未确认
-define(THOST_FTDC_VAA_NoAvailAbility, <<"0">>).

%% 有效
-define(THOST_FTDC_VAA_AvailAbility, <<"1">>).

%% 冲正
-define(THOST_FTDC_VAA_Repeal, <<"2">>).

%% 银行发起银行资金转期货
-define(THOST_FTDC_VTC_BankBankToFuture, <<"102001">>).

%% 银行发起期货资金转银行
-define(THOST_FTDC_VTC_BankFutureToBank, <<"102002">>).

%% 期货发起银行资金转期货
-define(THOST_FTDC_VTC_FutureBankToFuture, <<"202001">>).

%% 期货发起期货资金转银行
-define(THOST_FTDC_VTC_FutureFutureToBank, <<"202002">>).

%% 程序生成
-define(THOST_FTDC_GEN_Program, <<"0">>).

%% 人工生成
-define(THOST_FTDC_GEN_HandWork, <<"1">>).

%% 主动请求更新
-define(THOST_FTDC_CFMMCKK_REQUEST, <<"R">>).

%% CFMMC自动更新
-define(THOST_FTDC_CFMMCKK_AUTO, <<"A">>).

%% CFMMC手动更新
-define(THOST_FTDC_CFMMCKK_MANUAL, <<"M">>).

%% 身份证
-define(THOST_FTDC_CFT_IDCard, <<"0">>).

%% 护照
-define(THOST_FTDC_CFT_Passport, <<"1">>).

%% 军官证
-define(THOST_FTDC_CFT_OfficerIDCard, <<"2">>).

%% 士兵证
-define(THOST_FTDC_CFT_SoldierIDCard, <<"3">>).

%% 回乡证
-define(THOST_FTDC_CFT_HomeComingCard, <<"4">>).

%% 户口簿
-define(THOST_FTDC_CFT_HouseholdRegister, <<"5">>).

%% 营业执照号
-define(THOST_FTDC_CFT_LicenseNo, <<"6">>).

%% 组织机构代码证
-define(THOST_FTDC_CFT_InstitutionCodeCard, <<"7">>).

%% 临时营业执照号
-define(THOST_FTDC_CFT_TempLicenseNo, <<"8">>).

%% 民办非企业登记证书
-define(THOST_FTDC_CFT_NoEnterpriseLicenseNo, <<"9">>).

%% 其他证件
-define(THOST_FTDC_CFT_OtherCard, <<"x">>).

%% 主管部门批文
-define(THOST_FTDC_CFT_SuperDepAgree, <<"a">>).

%% 其他
-define(THOST_FTDC_FBC_Others, <<"0">>).

%% 转账交易明细对账
-define(THOST_FTDC_FBC_TransferDetails, <<"1">>).

%% 客户账户状态对账
-define(THOST_FTDC_FBC_CustAccStatus, <<"2">>).

%% 账户类交易明细对账
-define(THOST_FTDC_FBC_AccountTradeDetails, <<"3">>).

%% 期货账户信息变更明细对账
-define(THOST_FTDC_FBC_FutureAccountChangeInfoDetails, <<"4">>).

%% 客户资金台账余额明细对账
-define(THOST_FTDC_FBC_CustMoneyDetail, <<"5">>).

%% 客户销户结息明细对账
-define(THOST_FTDC_FBC_CustCancelAccountInfo, <<"6">>).

%% 客户资金余额对账结果
-define(THOST_FTDC_FBC_CustMoneyResult, <<"7">>).

%% 其它对账异常结果文件
-define(THOST_FTDC_FBC_OthersExceptionResult, <<"8">>).

%% 客户结息净额明细
-define(THOST_FTDC_FBC_CustInterestNetMoneyDetails, <<"9">>).

%% 客户资金交收明细
-define(THOST_FTDC_FBC_CustMoneySendAndReceiveDetails, <<"a">>).

%% 法人存管银行资金交收汇总
-define(THOST_FTDC_FBC_CorporationMoneyTotal, <<"b">>).

%% 主体间资金交收汇总
-define(THOST_FTDC_FBC_MainbodyMoneyTotal, <<"c">>).

%% 总分平衡监管数据
-define(THOST_FTDC_FBC_MainPartMonitorData, <<"d">>).

%% 存管银行备付金余额
-define(THOST_FTDC_FBC_PreparationMoney, <<"e">>).

%% 协办存管银行资金监管数据
-define(THOST_FTDC_FBC_BankMoneyMonitorData, <<"f">>).

%% 汇
-define(THOST_FTDC_CEC_Exchange, <<"1">>).

%% 钞
-define(THOST_FTDC_CEC_Cash, <<"2">>).

%% 是
-define(THOST_FTDC_YNI_Yes, <<"0">>).

%% 否
-define(THOST_FTDC_YNI_No, <<"1">>).

%% 当前余额
-define(THOST_FTDC_BLT_CurrentMoney, <<"0">>).

%% 可用余额
-define(THOST_FTDC_BLT_UsableMoney, <<"1">>).

%% 可取余额
-define(THOST_FTDC_BLT_FetchableMoney, <<"2">>).

%% 冻结余额
-define(THOST_FTDC_BLT_FreezeMoney, <<"3">>).

%% 未知状态
-define(THOST_FTDC_GD_Unknown, <<"0">>).

%% 男
-define(THOST_FTDC_GD_Male, <<"1">>).

%% 女
-define(THOST_FTDC_GD_Female, <<"2">>).

%% 由受益方支付费用
-define(THOST_FTDC_FPF_BEN, <<"0">>).

%% 由发送方支付费用
-define(THOST_FTDC_FPF_OUR, <<"1">>).

%% 由发送方支付发起的费用，受益方支付接受的费用
-define(THOST_FTDC_FPF_SHA, <<"2">>).

%% 交换密钥
-define(THOST_FTDC_PWKT_ExchangeKey, <<"0">>).

%% 密码密钥
-define(THOST_FTDC_PWKT_PassWordKey, <<"1">>).

%% MAC密钥
-define(THOST_FTDC_PWKT_MACKey, <<"2">>).

%% 报文密钥
-define(THOST_FTDC_PWKT_MessageKey, <<"3">>).

%% 查询
-define(THOST_FTDC_PWT_Query, <<"0">>).

%% 取款
-define(THOST_FTDC_PWT_Fetch, <<"1">>).

%% 转帐
-define(THOST_FTDC_PWT_Transfer, <<"2">>).

%% 交易
-define(THOST_FTDC_PWT_Trade, <<"3">>).

%% 不加密
-define(THOST_FTDC_EM_NoEncry, <<"0">>).

%% DES
-define(THOST_FTDC_EM_DES, <<"1">>).

%% 3DES
-define(THOST_FTDC_EM_3DES, <<"2">>).

%% 银行无需自动冲正
-define(THOST_FTDC_BRF_BankNotNeedRepeal, <<"0">>).

%% 银行待自动冲正
-define(THOST_FTDC_BRF_BankWaitingRepeal, <<"1">>).

%% 银行已自动冲正
-define(THOST_FTDC_BRF_BankBeenRepealed, <<"2">>).

%% 期商无需自动冲正
-define(THOST_FTDC_BRORF_BrokerNotNeedRepeal, <<"0">>).

%% 期商待自动冲正
-define(THOST_FTDC_BRORF_BrokerWaitingRepeal, <<"1">>).

%% 期商已自动冲正
-define(THOST_FTDC_BRORF_BrokerBeenRepealed, <<"2">>).

%% 银行
-define(THOST_FTDC_TS_Bank, <<"0">>).

%% 期商
-define(THOST_FTDC_TS_Future, <<"1">>).

%% 券商
-define(THOST_FTDC_TS_Store, <<"2">>).

%% 是最后分片
-define(THOST_FTDC_LF_Yes, <<"0">>).

%% 不是最后分片
-define(THOST_FTDC_LF_No, <<"1">>).

%% 正常
-define(THOST_FTDC_BAS_Normal, <<"0">>).

%% 冻结
-define(THOST_FTDC_BAS_Freeze, <<"1">>).

%% 挂失
-define(THOST_FTDC_BAS_ReportLoss, <<"2">>).

%% 正常
-define(THOST_FTDC_MAS_Normal, <<"0">>).

%% 销户
-define(THOST_FTDC_MAS_Cancel, <<"1">>).

%% 指定存管
-define(THOST_FTDC_MSS_Point, <<"0">>).

%% 预指定
-define(THOST_FTDC_MSS_PrePoint, <<"1">>).

%% 撤销指定
-define(THOST_FTDC_MSS_CancelPoint, <<"2">>).

%% 银期转帐
-define(THOST_FTDC_SYT_FutureBankTransfer, <<"0">>).

%% 银证转帐
-define(THOST_FTDC_SYT_StockBankTransfer, <<"1">>).

%% 第三方存管
-define(THOST_FTDC_SYT_TheThirdPartStore, <<"2">>).

%% 正常处理中
-define(THOST_FTDC_TEF_NormalProcessing, <<"0">>).

%% 成功结束
-define(THOST_FTDC_TEF_Success, <<"1">>).

%% 失败结束
-define(THOST_FTDC_TEF_Failed, <<"2">>).

%% 异常中
-define(THOST_FTDC_TEF_Abnormal, <<"3">>).

%% 已人工异常处理
-define(THOST_FTDC_TEF_ManualProcessedForException, <<"4">>).

%% 通讯异常 ，请人工处理
-define(THOST_FTDC_TEF_CommuFailedNeedManualProcess, <<"5">>).

%% 系统出错，请人工处理
-define(THOST_FTDC_TEF_SysErrorNeedManualProcess, <<"6">>).

%% 未处理
-define(THOST_FTDC_PSS_NotProcess, <<"0">>).

%% 开始处理
-define(THOST_FTDC_PSS_StartProcess, <<"1">>).

%% 处理完成
-define(THOST_FTDC_PSS_Finished, <<"2">>).

%% 自然人
-define(THOST_FTDC_CUSTT_Person, <<"0">>).

%% 机构户
-define(THOST_FTDC_CUSTT_Institution, <<"1">>).

%% 入金，银行转期货
-define(THOST_FTDC_FBTTD_FromBankToFuture, <<"1">>).

%% 出金，期货转银行
-define(THOST_FTDC_FBTTD_FromFutureToBank, <<"2">>).

%% 开户
-define(THOST_FTDC_OOD_Open, <<"1">>).

%% 销户
-define(THOST_FTDC_OOD_Destroy, <<"0">>).

%% 未确认
-define(THOST_FTDC_AVAF_Invalid, <<"0">>).

%% 有效
-define(THOST_FTDC_AVAF_Valid, <<"1">>).

%% 冲正
-define(THOST_FTDC_AVAF_Repeal, <<"2">>).

%% 银行代理
-define(THOST_FTDC_OT_Bank, <<"1">>).

%% 交易前置
-define(THOST_FTDC_OT_Future, <<"2">>).

%% 银期转帐平台管理
-define(THOST_FTDC_OT_PlateForm, <<"9">>).

%% 银行总行或期商总部
-define(THOST_FTDC_OL_HeadQuarters, <<"1">>).

%% 银行分中心或期货公司营业部
-define(THOST_FTDC_OL_Branch, <<"2">>).

%% 期商协议
-define(THOST_FTDC_PID_FutureProtocal, <<"0">>).

%% 工行协议
-define(THOST_FTDC_PID_ICBCProtocal, <<"1">>).

%% 农行协议
-define(THOST_FTDC_PID_ABCProtocal, <<"2">>).

%% 中国银行协议
-define(THOST_FTDC_PID_CBCProtocal, <<"3">>).

%% 建行协议
-define(THOST_FTDC_PID_CCBProtocal, <<"4">>).

%% 交行协议
-define(THOST_FTDC_PID_BOCOMProtocal, <<"5">>).

%% 银期转帐平台协议
-define(THOST_FTDC_PID_FBTPlateFormProtocal, <<"X">>).

%% 短连接
-define(THOST_FTDC_CM_ShortConnect, <<"0">>).

%% 长连接
-define(THOST_FTDC_CM_LongConnect, <<"1">>).

%% 异步
-define(THOST_FTDC_SRM_ASync, <<"0">>).

%% 同步
-define(THOST_FTDC_SRM_Sync, <<"1">>).

%% 银行存折
-define(THOST_FTDC_BAT_BankBook, <<"1">>).

%% 储蓄卡
-define(THOST_FTDC_BAT_SavingCard, <<"2">>).

%% 信用卡
-define(THOST_FTDC_BAT_CreditCard, <<"3">>).

%% 银行存折
-define(THOST_FTDC_FAT_BankBook, <<"1">>).

%% 储蓄卡
-define(THOST_FTDC_FAT_SavingCard, <<"2">>).

%% 信用卡
-define(THOST_FTDC_FAT_CreditCard, <<"3">>).

%% 启用
-define(THOST_FTDC_OS_Ready, <<"0">>).

%% 签到
-define(THOST_FTDC_OS_CheckIn, <<"1">>).

%% 签退
-define(THOST_FTDC_OS_CheckOut, <<"2">>).

%% 对帐文件到达
-define(THOST_FTDC_OS_CheckFileArrived, <<"3">>).

%% 对帐
-define(THOST_FTDC_OS_CheckDetail, <<"4">>).

%% 日终清理
-define(THOST_FTDC_OS_DayEndClean, <<"5">>).

%% 注销
-define(THOST_FTDC_OS_Invalid, <<"9">>).

%% 按金额扣收
-define(THOST_FTDC_CCBFM_ByAmount, <<"1">>).

%% 按月扣收
-define(THOST_FTDC_CCBFM_ByMonth, <<"2">>).

%% 客户端
-define(THOST_FTDC_CAPIT_Client, <<"1">>).

%% 服务端
-define(THOST_FTDC_CAPIT_Server, <<"2">>).

%% 交易系统的UserApi
-define(THOST_FTDC_CAPIT_UserApi, <<"3">>).

%% 已经连接
-define(THOST_FTDC_LS_Connected, <<"1">>).

%% 没有连接
-define(THOST_FTDC_LS_Disconnected, <<"2">>).

%% 不核对
-define(THOST_FTDC_BPWDF_NoCheck, <<"0">>).

%% 明文核对
-define(THOST_FTDC_BPWDF_BlankCheck, <<"1">>).

%% 密文核对
-define(THOST_FTDC_BPWDF_EncryptCheck, <<"2">>).

%% 资金帐号
-define(THOST_FTDC_SAT_AccountID, <<"1">>).

%% 资金卡号
-define(THOST_FTDC_SAT_CardID, <<"2">>).

%% 上海股东帐号
-define(THOST_FTDC_SAT_SHStockholderID, <<"3">>).

%% 深圳股东帐号
-define(THOST_FTDC_SAT_SZStockholderID, <<"4">>).

%% 正常
-define(THOST_FTDC_TRFS_Normal, <<"0">>).

%% 被冲正
-define(THOST_FTDC_TRFS_Repealed, <<"1">>).

%% 期商
-define(THOST_FTDC_SPTYPE_Broker, <<"0">>).

%% 银行
-define(THOST_FTDC_SPTYPE_Bank, <<"1">>).

%% 请求
-define(THOST_FTDC_REQRSP_Request, <<"0">>).

%% 响应
-define(THOST_FTDC_REQRSP_Response, <<"1">>).

%% 签到
-define(THOST_FTDC_FBTUET_SignIn, <<"0">>).

%% 银行转期货
-define(THOST_FTDC_FBTUET_FromBankToFuture, <<"1">>).

%% 期货转银行
-define(THOST_FTDC_FBTUET_FromFutureToBank, <<"2">>).

%% 开户
-define(THOST_FTDC_FBTUET_OpenAccount, <<"3">>).

%% 销户
-define(THOST_FTDC_FBTUET_CancelAccount, <<"4">>).

%% 变更银行账户
-define(THOST_FTDC_FBTUET_ChangeAccount, <<"5">>).

%% 冲正银行转期货
-define(THOST_FTDC_FBTUET_RepealFromBankToFuture, <<"6">>).

%% 冲正期货转银行
-define(THOST_FTDC_FBTUET_RepealFromFutureToBank, <<"7">>).

%% 查询银行账户
-define(THOST_FTDC_FBTUET_QueryBankAccount, <<"8">>).

%% 查询期货账户
-define(THOST_FTDC_FBTUET_QueryFutureAccount, <<"9">>).

%% 签退
-define(THOST_FTDC_FBTUET_SignOut, <<"A">>).

%% 密钥同步
-define(THOST_FTDC_FBTUET_SyncKey, <<"B">>).

%% 其他
-define(THOST_FTDC_FBTUET_Other, <<"Z">>).

%% 插入
-define(THOST_FTDC_DBOP_Insert, <<"0">>).

%% 更新
-define(THOST_FTDC_DBOP_Update, <<"1">>).

%% 删除
-define(THOST_FTDC_DBOP_Delete, <<"2">>).

%% 已同步
-define(THOST_FTDC_SYNF_Yes, <<"0">>).

%% 未同步
-define(THOST_FTDC_SYNF_No, <<"1">>).

%% 一次同步
-define(THOST_FTDC_SYNT_OneOffSync, <<"0">>).

%% 定时同步
-define(THOST_FTDC_SYNT_TimerSync, <<"1">>).

%% 定时完全同步
-define(THOST_FTDC_SYNT_TimerFullSync, <<"2">>).

%% 结汇
-define(THOST_FTDC_FBEDIR_Settlement, <<"0">>).

%% 售汇
-define(THOST_FTDC_FBEDIR_Sale, <<"1">>).

%% 成功
-define(THOST_FTDC_FBERES_Success, <<"0">>).

%% 账户余额不足
-define(THOST_FTDC_FBERES_InsufficientBalance, <<"1">>).

%% 交易结果未知
-define(THOST_FTDC_FBERES_UnknownTrading, <<"8">>).

%% 失败
-define(THOST_FTDC_FBERES_Fail, <<"x">>).

%% 正常
-define(THOST_FTDC_FBEES_Normal, <<"0">>).

%% 交易重发
-define(THOST_FTDC_FBEES_ReExchange, <<"1">>).

%% 数据包
-define(THOST_FTDC_FBEFG_DataPackage, <<"0">>).

%% 文件
-define(THOST_FTDC_FBEFG_File, <<"1">>).

%% 未交易
-define(THOST_FTDC_FBEAT_NotTrade, <<"0">>).

%% 已交易
-define(THOST_FTDC_FBEAT_Trade, <<"1">>).

%% 签到
-define(THOST_FTDC_FBEUET_SignIn, <<"0">>).

%% 换汇
-define(THOST_FTDC_FBEUET_Exchange, <<"1">>).

%% 换汇重发
-define(THOST_FTDC_FBEUET_ReExchange, <<"2">>).

%% 银行账户查询
-define(THOST_FTDC_FBEUET_QueryBankAccount, <<"3">>).

%% 换汇明细查询
-define(THOST_FTDC_FBEUET_QueryExchDetial, <<"4">>).

%% 换汇汇总查询
-define(THOST_FTDC_FBEUET_QueryExchSummary, <<"5">>).

%% 换汇汇率查询
-define(THOST_FTDC_FBEUET_QueryExchRate, <<"6">>).

%% 对账文件通知
-define(THOST_FTDC_FBEUET_CheckBankAccount, <<"7">>).

%% 签退
-define(THOST_FTDC_FBEUET_SignOut, <<"8">>).

%% 其他
-define(THOST_FTDC_FBEUET_Other, <<"Z">>).

%% 未处理
-define(THOST_FTDC_FBERF_UnProcessed, <<"0">>).

%% 等待发送
-define(THOST_FTDC_FBERF_WaitSend, <<"1">>).

%% 发送成功
-define(THOST_FTDC_FBERF_SendSuccess, <<"2">>).

%% 发送失败
-define(THOST_FTDC_FBERF_SendFailed, <<"3">>).

%% 等待重发
-define(THOST_FTDC_FBERF_WaitReSend, <<"4">>).

%% 正常
-define(THOST_FTDC_NC_NOERROR, <<"0">>).

%% 警示
-define(THOST_FTDC_NC_Warn, <<"1">>).

%% 追保
-define(THOST_FTDC_NC_Call, <<"2">>).

%% 强平
-define(THOST_FTDC_NC_Force, <<"3">>).

%% 穿仓
-define(THOST_FTDC_NC_CHUANCANG, <<"4">>).

%% 异常
-define(THOST_FTDC_NC_Exception, <<"5">>).

%% 手工强平
-define(THOST_FTDC_FCT_Manual, <<"0">>).

%% 单一投资者辅助强平
-define(THOST_FTDC_FCT_Single, <<"1">>).

%% 批量投资者辅助强平
-define(THOST_FTDC_FCT_Group, <<"2">>).

%% 系统通知
-define(THOST_FTDC_RNM_System, <<"0">>).

%% 短信通知
-define(THOST_FTDC_RNM_SMS, <<"1">>).

%% 邮件通知
-define(THOST_FTDC_RNM_EMail, <<"2">>).

%% 人工通知
-define(THOST_FTDC_RNM_Manual, <<"3">>).

%% 未生成
-define(THOST_FTDC_RNS_NotGen, <<"0">>).

%% 已生成未发送
-define(THOST_FTDC_RNS_Generated, <<"1">>).

%% 发送失败
-define(THOST_FTDC_RNS_SendError, <<"2">>).

%% 已发送未接收
-define(THOST_FTDC_RNS_SendOk, <<"3">>).

%% 已接收未确认
-define(THOST_FTDC_RNS_Received, <<"4">>).

%% 已确认
-define(THOST_FTDC_RNS_Confirmed, <<"5">>).

%% 导出数据
-define(THOST_FTDC_RUE_ExportData, <<"0">>).

%% 使用最新价升序
-define(THOST_FTDC_COST_LastPriceAsc, <<"0">>).

%% 使用最新价降序
-define(THOST_FTDC_COST_LastPriceDesc, <<"1">>).

%% 使用卖价升序
-define(THOST_FTDC_COST_AskPriceAsc, <<"2">>).

%% 使用卖价降序
-define(THOST_FTDC_COST_AskPriceDesc, <<"3">>).

%% 使用买价升序
-define(THOST_FTDC_COST_BidPriceAsc, <<"4">>).

%% 使用买价降序
-define(THOST_FTDC_COST_BidPriceDesc, <<"5">>).

%% 未发送
-define(THOST_FTDC_UOAST_NoSend, <<"0">>).

%% 已发送
-define(THOST_FTDC_UOAST_Sended, <<"1">>).

%% 已生成
-define(THOST_FTDC_UOAST_Generated, <<"2">>).

%% 报送失败
-define(THOST_FTDC_UOAST_SendFail, <<"3">>).

%% 接收成功
-define(THOST_FTDC_UOAST_Success, <<"4">>).

%% 接收失败
-define(THOST_FTDC_UOAST_Fail, <<"5">>).

%% 取消报送
-define(THOST_FTDC_UOAST_Cancel, <<"6">>).

%% 未申请
-define(THOST_FTDC_UOACS_NoApply, <<"1">>).

%% 已提交申请
-define(THOST_FTDC_UOACS_Submited, <<"2">>).

%% 已发送申请
-define(THOST_FTDC_UOACS_Sended, <<"3">>).

%% 完成
-define(THOST_FTDC_UOACS_Success, <<"4">>).

%% 拒绝
-define(THOST_FTDC_UOACS_Refuse, <<"5">>).

%% 已撤销编码
-define(THOST_FTDC_UOACS_Cancel, <<"6">>).

%% 单选
-define(THOST_FTDC_QT_Radio, <<"1">>).

%% 多选
-define(THOST_FTDC_QT_Option, <<"2">>).

%% 填空
-define(THOST_FTDC_QT_Blank, <<"3">>).

%% 请求
-define(THOST_FTDC_BT_Request, <<"1">>).

%% 应答
-define(THOST_FTDC_BT_Response, <<"2">>).

%% 通知
-define(THOST_FTDC_BT_Notice, <<"3">>).

%% 成功
-define(THOST_FTDC_CRC_Success, <<"0">>).

%% 该客户已经有流程在处理中
-define(THOST_FTDC_CRC_Working, <<"1">>).

%% 监控中客户资料检查失败
-define(THOST_FTDC_CRC_InfoFail, <<"2">>).

%% 监控中实名制检查失败
-define(THOST_FTDC_CRC_IDCardFail, <<"3">>).

%% 其他错误
-define(THOST_FTDC_CRC_OtherFail, <<"4">>).

%% 所有
-define(THOST_FTDC_CfMMCCT_All, <<"0">>).

%% 个人
-define(THOST_FTDC_CfMMCCT_Person, <<"1">>).

%% 单位
-define(THOST_FTDC_CfMMCCT_Company, <<"2">>).

%% 其他
-define(THOST_FTDC_CfMMCCT_Other, <<"3">>).

%% 特殊法人
-define(THOST_FTDC_CfMMCCT_SpecialOrgan, <<"4">>).

%% 资管户
-define(THOST_FTDC_CfMMCCT_Asset, <<"5">>).

%% 上海期货交易所
-define(THOST_FTDC_EIDT_SHFE, <<"S">>).

%% 郑州商品交易所
-define(THOST_FTDC_EIDT_CZCE, <<"Z">>).

%% 大连商品交易所
-define(THOST_FTDC_EIDT_DCE, <<"D">>).

%% 中国金融期货交易所
-define(THOST_FTDC_EIDT_CFFEX, <<"J">>).

%% 上海国际能源交易中心股份有限公司
-define(THOST_FTDC_EIDT_INE, <<"N">>).

%% 上海证券交易所
-define(THOST_FTDC_EIDT_SSE, <<"A">>).

%% 深圳证券交易所
-define(THOST_FTDC_EIDT_SZSE, <<"E">>).

%% 套保
-define(THOST_FTDC_ECIDT_Hedge, <<"1">>).

%% 套利
-define(THOST_FTDC_ECIDT_Arbitrage, <<"2">>).

%% 投机
-define(THOST_FTDC_ECIDT_Speculation, <<"3">>).

%% 未更新
-define(THOST_FTDC_UF_NoUpdate, <<"0">>).

%% 更新全部信息成功
-define(THOST_FTDC_UF_Success, <<"1">>).

%% 更新全部信息失败
-define(THOST_FTDC_UF_Fail, <<"2">>).

%% 更新交易编码成功
-define(THOST_FTDC_UF_TCSuccess, <<"3">>).

%% 更新交易编码失败
-define(THOST_FTDC_UF_TCFail, <<"4">>).

%% 已丢弃
-define(THOST_FTDC_UF_Cancel, <<"5">>).

%% 开户
-define(THOST_FTDC_AOID_OpenInvestor, <<"1">>).

%% 修改身份信息
-define(THOST_FTDC_AOID_ModifyIDCard, <<"2">>).

%% 修改一般信息
-define(THOST_FTDC_AOID_ModifyNoIDCard, <<"3">>).

%% 申请交易编码
-define(THOST_FTDC_AOID_ApplyTradingCode, <<"4">>).

%% 撤销交易编码
-define(THOST_FTDC_AOID_CancelTradingCode, <<"5">>).

%% 销户
-define(THOST_FTDC_AOID_CancelInvestor, <<"6">>).

%% 账户休眠
-define(THOST_FTDC_AOID_FreezeAccount, <<"8">>).

%% 激活休眠账户
-define(THOST_FTDC_AOID_ActiveFreezeAccount, <<"9">>).

%% 未补全
-define(THOST_FTDC_ASID_NoComplete, <<"1">>).

%% 已提交
-define(THOST_FTDC_ASID_Submited, <<"2">>).

%% 已审核
-define(THOST_FTDC_ASID_Checked, <<"3">>).

%% 已拒绝
-define(THOST_FTDC_ASID_Refused, <<"4">>).

%% 已删除
-define(THOST_FTDC_ASID_Deleted, <<"5">>).

%% 文件发送
-define(THOST_FTDC_UOASM_ByAPI, <<"1">>).

%% 电子发送
-define(THOST_FTDC_UOASM_ByFile, <<"2">>).

%% 增加
-define(THOST_FTDC_EvM_ADD, <<"1">>).

%% 修改
-define(THOST_FTDC_EvM_UPDATE, <<"2">>).

%% 删除
-define(THOST_FTDC_EvM_DELETE, <<"3">>).

%% 复核
-define(THOST_FTDC_EvM_CHECK, <<"4">>).

%% 复制
-define(THOST_FTDC_EvM_COPY, <<"5">>).

%% 注销
-define(THOST_FTDC_EvM_CANCEL, <<"6">>).

%% 冲销
-define(THOST_FTDC_EvM_Reverse, <<"7">>).

%% 自动发送并接收
-define(THOST_FTDC_UOAA_ASR, <<"1">>).

%% 自动发送，不自动接收
-define(THOST_FTDC_UOAA_ASNR, <<"2">>).

%% 不自动发送，自动接收
-define(THOST_FTDC_UOAA_NSAR, <<"3">>).

%% 不自动发送，也不自动接收
-define(THOST_FTDC_UOAA_NSR, <<"4">>).

%% 投资者对应投资者组设置
-define(THOST_FTDC_EvM_InvestorGroupFlow, <<"1">>).

%% 投资者手续费率设置
-define(THOST_FTDC_EvM_InvestorRate, <<"2">>).

%% 投资者手续费率模板关系设置
-define(THOST_FTDC_EvM_InvestorCommRateModel, <<"3">>).

%% 零级复核
-define(THOST_FTDC_CL_Zero, <<"0">>).

%% 一级复核
-define(THOST_FTDC_CL_One, <<"1">>).

%% 二级复核
-define(THOST_FTDC_CL_Two, <<"2">>).

%% 未复核
-define(THOST_FTDC_CHS_Init, <<"0">>).

%% 复核中
-define(THOST_FTDC_CHS_Checking, <<"1">>).

%% 已复核
-define(THOST_FTDC_CHS_Checked, <<"2">>).

%% 拒绝
-define(THOST_FTDC_CHS_Refuse, <<"3">>).

%% 作废
-define(THOST_FTDC_CHS_Cancel, <<"4">>).

%% 未生效
-define(THOST_FTDC_CHU_Unused, <<"0">>).

%% 已生效
-define(THOST_FTDC_CHU_Used, <<"1">>).

%% 生效失败
-define(THOST_FTDC_CHU_Fail, <<"2">>).

%% 手工录入
-define(THOST_FTDC_BAO_ByAccProperty, <<"0">>).

%% 银期转账
-define(THOST_FTDC_BAO_ByFBTransfer, <<"1">>).

%% 同日同合约
-define(THOST_FTDC_MBTS_ByInstrument, <<"0">>).

%% 同日同合约同价格
-define(THOST_FTDC_MBTS_ByDayInsPrc, <<"1">>).

%% 同合约
-define(THOST_FTDC_MBTS_ByDayIns, <<"2">>).

%% 银行发起银行转期货
-define(THOST_FTDC_FTC_BankLaunchBankToBroker, <<"102001">>).

%% 期货发起银行转期货
-define(THOST_FTDC_FTC_BrokerLaunchBankToBroker, <<"202001">>).

%% 银行发起期货转银行
-define(THOST_FTDC_FTC_BankLaunchBrokerToBank, <<"102002">>).

%% 期货发起期货转银行
-define(THOST_FTDC_FTC_BrokerLaunchBrokerToBank, <<"202002">>).

%% 无动态令牌
-define(THOST_FTDC_OTP_NONE, <<"0">>).

%% 时间令牌
-define(THOST_FTDC_OTP_TOTP, <<"1">>).

%% 未使用
-define(THOST_FTDC_OTPS_Unused, <<"0">>).

%% 已使用
-define(THOST_FTDC_OTPS_Used, <<"1">>).

%% 注销
-define(THOST_FTDC_OTPS_Disuse, <<"2">>).

%% 投资者
-define(THOST_FTDC_BUT_Investor, <<"1">>).

%% 操作员
-define(THOST_FTDC_BUT_BrokerUser, <<"2">>).

%% 商品期货
-define(THOST_FTDC_FUTT_Commodity, <<"1">>).

%% 金融期货
-define(THOST_FTDC_FUTT_Financial, <<"2">>).

%% 转账限额
-define(THOST_FTDC_FET_Restriction, <<"0">>).

%% 当日转账限额
-define(THOST_FTDC_FET_TodayRestriction, <<"1">>).

%% 期商流水
-define(THOST_FTDC_FET_Transfer, <<"2">>).

%% 资金冻结
-define(THOST_FTDC_FET_Credit, <<"3">>).

%% 投资者可提资金比例
-define(THOST_FTDC_FET_InvestorWithdrawAlm, <<"4">>).

%% 单个银行帐户转账限额
-define(THOST_FTDC_FET_BankRestriction, <<"5">>).

%% 银期签约账户
-define(THOST_FTDC_FET_Accountregister, <<"6">>).

%% 交易所出入金
-define(THOST_FTDC_FET_ExchangeFundIO, <<"7">>).

%% 投资者出入金
-define(THOST_FTDC_FET_InvestorFundIO, <<"8">>).

%% 银期同步
-define(THOST_FTDC_AST_FBTransfer, <<"0">>).

%% 手工录入
-define(THOST_FTDC_AST_ManualEntry, <<"1">>).

%% 统一开户(已规范)
-define(THOST_FTDC_CST_UnifyAccount, <<"0">>).

%% 手工录入(未规范)
-define(THOST_FTDC_CST_ManualEntry, <<"1">>).

%% 所有
-define(THOST_FTDC_UR_All, <<"0">>).

%% 单一操作员
-define(THOST_FTDC_UR_Single, <<"1">>).

%% 按投资者统计
-define(THOST_FTDC_BG_Investor, <<"2">>).

%% 按类统计
-define(THOST_FTDC_BG_Group, <<"1">>).

%% 按合约统计
-define(THOST_FTDC_TSSM_Instrument, <<"1">>).

%% 按产品统计
-define(THOST_FTDC_TSSM_Product, <<"2">>).

%% 按交易所统计
-define(THOST_FTDC_TSSM_Exchange, <<"3">>).

%% 相对已有规则设置
-define(THOST_FTDC_ESM_Relative, <<"1">>).

%% 典型设置
-define(THOST_FTDC_ESM_Typical, <<"2">>).

%% 公司标准
-define(THOST_FTDC_RIR_All, <<"1">>).

%% 模板
-define(THOST_FTDC_RIR_Model, <<"2">>).

%% 单一投资者
-define(THOST_FTDC_RIR_Single, <<"3">>).

%% 未同步
-define(THOST_FTDC_SDS_Initialize, <<"0">>).

%% 同步中
-define(THOST_FTDC_SDS_Settlementing, <<"1">>).

%% 已同步
-define(THOST_FTDC_SDS_Settlemented, <<"2">>).

%% 来自交易所普通回报
-define(THOST_FTDC_TSRC_NORMAL, <<"0">>).

%% 来自查询
-define(THOST_FTDC_TSRC_QUERY, <<"1">>).

%% 产品统计
-define(THOST_FTDC_FSM_Product, <<"1">>).

%% 交易所统计
-define(THOST_FTDC_FSM_Exchange, <<"2">>).

%% 统计所有
-define(THOST_FTDC_FSM_All, <<"3">>).

%% 属性统计
-define(THOST_FTDC_BIR_Property, <<"1">>).

%% 统计所有
-define(THOST_FTDC_BIR_All, <<"2">>).

%% 所有
-define(THOST_FTDC_PIR_All, <<"1">>).

%% 投资者属性
-define(THOST_FTDC_PIR_Property, <<"2">>).

%% 单一投资者
-define(THOST_FTDC_PIR_Single, <<"3">>).

%% 未生成
-define(THOST_FTDC_FIS_NoCreate, <<"0">>).

%% 已生成
-define(THOST_FTDC_FIS_Created, <<"1">>).

%% 生成失败
-define(THOST_FTDC_FIS_Failed, <<"2">>).

%% 下发
-define(THOST_FTDC_FGS_FileTransmit, <<"0">>).

%% 生成
-define(THOST_FTDC_FGS_FileGen, <<"1">>).

%% 增加
-define(THOST_FTDC_SoM_Add, <<"1">>).

%% 修改
-define(THOST_FTDC_SoM_Update, <<"2">>).

%% 删除
-define(THOST_FTDC_SoM_Delete, <<"3">>).

%% 复制
-define(THOST_FTDC_SoM_Copy, <<"4">>).

%% 激活
-define(THOST_FTDC_SoM_AcTive, <<"5">>).

%% 注销
-define(THOST_FTDC_SoM_CanCel, <<"6">>).

%% 重置
-define(THOST_FTDC_SoM_ReSet, <<"7">>).

%% 修改操作员密码
-define(THOST_FTDC_SoT_UpdatePassword, <<"0">>).

%% 操作员组织架构关系
-define(THOST_FTDC_SoT_UserDepartment, <<"1">>).

%% 角色管理
-define(THOST_FTDC_SoT_RoleManager, <<"2">>).

%% 角色功能设置
-define(THOST_FTDC_SoT_RoleFunction, <<"3">>).

%% 基础参数设置
-define(THOST_FTDC_SoT_BaseParam, <<"4">>).

%% 设置操作员
-define(THOST_FTDC_SoT_SetUserID, <<"5">>).

%% 用户角色设置
-define(THOST_FTDC_SoT_SetUserRole, <<"6">>).

%% 用户IP限制
-define(THOST_FTDC_SoT_UserIpRestriction, <<"7">>).

%% 组织架构管理
-define(THOST_FTDC_SoT_DepartmentManager, <<"8">>).

%% 组织架构向查询分类复制
-define(THOST_FTDC_SoT_DepartmentCopy, <<"9">>).

%% 交易编码管理
-define(THOST_FTDC_SoT_Tradingcode, <<"A">>).

%% 投资者状态维护
-define(THOST_FTDC_SoT_InvestorStatus, <<"B">>).

%% 投资者权限管理
-define(THOST_FTDC_SoT_InvestorAuthority, <<"C">>).

%% 属性设置
-define(THOST_FTDC_SoT_PropertySet, <<"D">>).

%% 重置投资者密码
-define(THOST_FTDC_SoT_ReSetInvestorPasswd, <<"E">>).

%% 投资者个性信息维护
-define(THOST_FTDC_SoT_InvestorPersonalityInfo, <<"F">>).

%% 查询当前交易日报送的数据
-define(THOST_FTDC_CSRCQ_Current, <<"0">>).

%% 查询历史报送的代理经纪公司的数据
-define(THOST_FTDC_CSRCQ_History, <<"1">>).

%% 活跃
-define(THOST_FTDC_FRS_Normal, <<"1">>).

%% 休眠
-define(THOST_FTDC_FRS_Freeze, <<"0">>).

%% 已规范
-define(THOST_FTDC_STST_Standard, <<"0">>).

%% 未规范
-define(THOST_FTDC_STST_NonStandard, <<"1">>).

%% 休眠户
-define(THOST_FTDC_RPT_Freeze, <<"1">>).

%% 激活休眠户
-define(THOST_FTDC_RPT_FreezeActive, <<"2">>).

%% 开仓权限限制
-define(THOST_FTDC_RPT_OpenLimit, <<"3">>).

%% 解除开仓权限限制
-define(THOST_FTDC_RPT_RelieveOpenLimit, <<"4">>).

%% 正常
-define(THOST_FTDC_AMLDS_Normal, <<"0">>).

%% 已删除
-define(THOST_FTDC_AMLDS_Deleted, <<"1">>).

%% 未复核
-define(THOST_FTDC_AMLCHS_Init, <<"0">>).

%% 复核中
-define(THOST_FTDC_AMLCHS_Checking, <<"1">>).

%% 已复核
-define(THOST_FTDC_AMLCHS_Checked, <<"2">>).

%% 拒绝上报
-define(THOST_FTDC_AMLCHS_RefuseReport, <<"3">>).

%% 检查日期
-define(THOST_FTDC_AMLDT_DrawDay, <<"0">>).

%% 发生日期
-define(THOST_FTDC_AMLDT_TouchDay, <<"1">>).

%% 零级审核
-define(THOST_FTDC_AMLCL_CheckLevel0, <<"0">>).

%% 一级审核
-define(THOST_FTDC_AMLCL_CheckLevel1, <<"1">>).

%% 二级审核
-define(THOST_FTDC_AMLCL_CheckLevel2, <<"2">>).

%% 三级审核
-define(THOST_FTDC_AMLCL_CheckLevel3, <<"3">>).

%% CSV
-define(THOST_FTDC_EFT_CSV, <<"0">>).

%% Excel
-define(THOST_FTDC_EFT_EXCEL, <<"1">>).

%% DBF
-define(THOST_FTDC_EFT_DBF, <<"2">>).

%% 结算前准备
-define(THOST_FTDC_SMT_Before, <<"1">>).

%% 结算
-define(THOST_FTDC_SMT_Settlement, <<"2">>).

%% 结算后核对
-define(THOST_FTDC_SMT_After, <<"3">>).

%% 结算后处理
-define(THOST_FTDC_SMT_Settlemented, <<"4">>).

%% 必要
-define(THOST_FTDC_SML_Must, <<"1">>).

%% 警告
-define(THOST_FTDC_SML_Alarm, <<"2">>).

%% 提示
-define(THOST_FTDC_SML_Prompt, <<"3">>).

%% 不检查
-define(THOST_FTDC_SML_Ignore, <<"4">>).

%% 交易所核对
-define(THOST_FTDC_SMG_Exhcange, <<"1">>).

%% 内部核对
-define(THOST_FTDC_SMG_ASP, <<"2">>).

%% 上报数据核对
-define(THOST_FTDC_SMG_CSRC, <<"3">>).

%% 可重复使用
-define(THOST_FTDC_LUT_Repeatable, <<"1">>).

%% 不可重复使用
-define(THOST_FTDC_LUT_Unrepeatable, <<"2">>).

%% 本系统
-define(THOST_FTDC_DAR_Settle, <<"1">>).

%% 交易所
-define(THOST_FTDC_DAR_Exchange, <<"2">>).

%% 报送数据
-define(THOST_FTDC_DAR_CSRC, <<"3">>).

%% 交易所保证金率
-define(THOST_FTDC_MGT_ExchMarginRate, <<"0">>).

%% 投资者保证金率
-define(THOST_FTDC_MGT_InstrMarginRate, <<"1">>).

%% 投资者交易保证金率
-define(THOST_FTDC_MGT_InstrMarginRateTrade, <<"2">>).

%% 仅当日生效
-define(THOST_FTDC_ACT_Intraday, <<"1">>).

%% 长期生效
-define(THOST_FTDC_ACT_Long, <<"2">>).

%% 交易所保证金率
-define(THOST_FTDC_MRT_Exchange, <<"1">>).

%% 投资者保证金率
-define(THOST_FTDC_MRT_Investor, <<"2">>).

%% 投资者交易保证金率
-define(THOST_FTDC_MRT_InvestorTrade, <<"3">>).

%% 未生成备份数据
-define(THOST_FTDC_BUS_UnBak, <<"0">>).

%% 备份数据生成中
-define(THOST_FTDC_BUS_BakUp, <<"1">>).

%% 已生成备份数据
-define(THOST_FTDC_BUS_BakUped, <<"2">>).

%% 备份数据失败
-define(THOST_FTDC_BUS_BakFail, <<"3">>).

%% 结算初始化未开始
-define(THOST_FTDC_SIS_UnInitialize, <<"0">>).

%% 结算初始化中
-define(THOST_FTDC_SIS_Initialize, <<"1">>).

%% 结算初始化完成
-define(THOST_FTDC_SIS_Initialized, <<"2">>).

%% 未生成报表数据
-define(THOST_FTDC_SRS_NoCreate, <<"0">>).

%% 报表数据生成中
-define(THOST_FTDC_SRS_Create, <<"1">>).

%% 已生成报表数据
-define(THOST_FTDC_SRS_Created, <<"2">>).

%% 生成报表数据失败
-define(THOST_FTDC_SRS_CreateFail, <<"3">>).

%% 归档未完成
-define(THOST_FTDC_SSS_UnSaveData, <<"0">>).

%% 归档完成
-define(THOST_FTDC_SSS_SaveDatad, <<"1">>).

%% 未归档数据
-define(THOST_FTDC_SAS_UnArchived, <<"0">>).

%% 数据归档中
-define(THOST_FTDC_SAS_Archiving, <<"1">>).

%% 已归档数据
-define(THOST_FTDC_SAS_Archived, <<"2">>).

%% 归档数据失败
-define(THOST_FTDC_SAS_ArchiveFail, <<"3">>).

%% 未知类型
-define(THOST_FTDC_CTPT_Unkown, <<"0">>).

%% 主中心
-define(THOST_FTDC_CTPT_MainCenter, <<"1">>).

%% 备中心
-define(THOST_FTDC_CTPT_BackUp, <<"2">>).

%% 正常
-define(THOST_FTDC_CDT_Normal, <<"0">>).

%% 投机平仓优先
-define(THOST_FTDC_CDT_SpecFirst, <<"1">>).

%% 不能使用
-define(THOST_FTDC_MFUR_None, <<"0">>).

%% 用于保证金
-define(THOST_FTDC_MFUR_Margin, <<"1">>).

%% 用于手续费、盈亏、保证金
-define(THOST_FTDC_MFUR_All, <<"2">>).

%% 郑商所套保产品
-define(THOST_FTDC_SPT_CzceHedge, <<"1">>).

%% 货币质押产品
-define(THOST_FTDC_SPT_IneForeignCurrency, <<"2">>).

%% 大连短线开平仓产品
-define(THOST_FTDC_SPT_DceOpenClose, <<"3">>).

%% 质押
-define(THOST_FTDC_FMT_Mortgage, <<"1">>).

%% 解质
-define(THOST_FTDC_FMT_Redemption, <<"2">>).

%% 基础保证金
-define(THOST_FTDC_ASPI_BaseMargin, <<"1">>).

%% 最低权益标准
-define(THOST_FTDC_ASPI_LowestInterest, <<"2">>).

%% 货币质入
-define(THOST_FTDC_FMD_In, <<"1">>).

%% 货币质出
-define(THOST_FTDC_FMD_Out, <<"2">>).

%% 盈利
-define(THOST_FTDC_BT_Profit, <<"0">>).

%% 亏损
-define(THOST_FTDC_BT_Loss, <<"1">>).

%% 其他
-define(THOST_FTDC_BT_Other, <<"Z">>).

%% 手工
-define(THOST_FTDC_SST_Manual, <<"0">>).

%% 自动生成
-define(THOST_FTDC_SST_Automatic, <<"1">>).

%% 结汇
-define(THOST_FTDC_CED_Settlement, <<"0">>).

%% 售汇
-define(THOST_FTDC_CED_Sale, <<"1">>).

%% 已录入
-define(THOST_FTDC_CSS_Entry, <<"1">>).

%% 已审核
-define(THOST_FTDC_CSS_Approve, <<"2">>).

%% 已拒绝
-define(THOST_FTDC_CSS_Refuse, <<"3">>).

%% 已撤销
-define(THOST_FTDC_CSS_Revoke, <<"4">>).

%% 已发送
-define(THOST_FTDC_CSS_Send, <<"5">>).

%% 换汇成功
-define(THOST_FTDC_CSS_Success, <<"6">>).

%% 换汇失败
-define(THOST_FTDC_CSS_Failure, <<"7">>).

%% 未发送
-define(THOST_FTDC_REQF_NoSend, <<"0">>).

%% 发送成功
-define(THOST_FTDC_REQF_SendSuccess, <<"1">>).

%% 发送失败
-define(THOST_FTDC_REQF_SendFailed, <<"2">>).

%% 等待重发
-define(THOST_FTDC_REQF_WaitReSend, <<"3">>).

%% 成功
-define(THOST_FTDC_RESF_Success, <<"0">>).

%% 账户余额不足
-define(THOST_FTDC_RESF_InsuffiCient, <<"1">>).

%% 交易结果未知
-define(THOST_FTDC_RESF_UnKnown, <<"8">>).

%% 修改前
-define(THOST_FTDC_EXS_Before, <<"0">>).

%% 修改后
-define(THOST_FTDC_EXS_After, <<"1">>).

%% 国内客户
-define(THOST_FTDC_CR_Domestic, <<"1">>).

%% 港澳台客户
-define(THOST_FTDC_CR_GMT, <<"2">>).

%% 国外客户
-define(THOST_FTDC_CR_Foreign, <<"3">>).

%% 没有
-define(THOST_FTDC_HB_No, <<"0">>).

%% 有
-define(THOST_FTDC_HB_Yes, <<"1">>).

%% 正常
-define(THOST_FTDC_SM_Normal, <<"1">>).

%% 应急
-define(THOST_FTDC_SM_Emerge, <<"2">>).

%% 恢复
-define(THOST_FTDC_SM_Restore, <<"3">>).

%% 全量
-define(THOST_FTDC_TPT_Full, <<"1">>).

%% 增量
-define(THOST_FTDC_TPT_Increment, <<"2">>).

%% 备份
-define(THOST_FTDC_TPT_BackUp, <<"3">>).

%% 交易
-define(THOST_FTDC_LM_Trade, <<"0">>).

%% 转账
-define(THOST_FTDC_LM_Transfer, <<"1">>).

%% 合约上下市
-define(THOST_FTDC_CPT_Instrument, <<"1">>).

%% 保证金分段生效
-define(THOST_FTDC_CPT_Margin, <<"2">>).

%% 有
-define(THOST_FTDC_HT_Yes, <<"1">>).

%% 没有
-define(THOST_FTDC_HT_No, <<"0">>).

%% 银行
-define(THOST_FTDC_AMT_Bank, <<"1">>).

%% 证券公司
-define(THOST_FTDC_AMT_Securities, <<"2">>).

%% 基金公司
-define(THOST_FTDC_AMT_Fund, <<"3">>).

%% 保险公司
-define(THOST_FTDC_AMT_Insurance, <<"4">>).

%% 信托公司
-define(THOST_FTDC_AMT_Trust, <<"5">>).

%% 其他
-define(THOST_FTDC_AMT_Other, <<"9">>).

%% 出入金
-define(THOST_FTDC_CFIOT_FundIO, <<"0">>).

%% 银期换汇
-define(THOST_FTDC_CFIOT_SwapCurrency, <<"1">>).

%% 期货结算账户
-define(THOST_FTDC_CAT_Futures, <<"1">>).

%% 纯期货资管业务下的资管结算账户
-define(THOST_FTDC_CAT_AssetmgrFuture, <<"2">>).

%% 综合类资管业务下的期货资管托管账户
-define(THOST_FTDC_CAT_AssetmgrTrustee, <<"3">>).

%% 综合类资管业务下的资金中转账户
-define(THOST_FTDC_CAT_AssetmgrTransfer, <<"4">>).

%% 中文
-define(THOST_FTDC_LT_Chinese, <<"1">>).

%% 英文
-define(THOST_FTDC_LT_English, <<"2">>).

%% 个人资管客户
-define(THOST_FTDC_AMCT_Person, <<"1">>).

%% 单位资管客户
-define(THOST_FTDC_AMCT_Organ, <<"2">>).

%% 特殊单位资管客户
-define(THOST_FTDC_AMCT_SpecialOrgan, <<"4">>).

%% 期货类
-define(THOST_FTDC_ASST_Futures, <<"3">>).

%% 综合类
-define(THOST_FTDC_ASST_SpecialOrgan, <<"4">>).

%% 合约交易所不存在
-define(THOST_FTDC_CIT_HasExch, <<"0">>).

%% 合约本系统不存在
-define(THOST_FTDC_CIT_HasATP, <<"1">>).

%% 合约比较不一致
-define(THOST_FTDC_CIT_HasDiff, <<"2">>).

%% 手工交割
-define(THOST_FTDC_DT_HandDeliv, <<"1">>).

%% 到期交割
-define(THOST_FTDC_DT_PersonDeliv, <<"2">>).

%% 不使用大额单边保证金算法
-define(THOST_FTDC_MMSA_NO, <<"0">>).

%% 使用大额单边保证金算法
-define(THOST_FTDC_MMSA_YES, <<"1">>).

%% 自然人
-define(THOST_FTDC_CACT_Person, <<"0">>).

%% 法人
-define(THOST_FTDC_CACT_Company, <<"1">>).

%% 其他
-define(THOST_FTDC_CACT_Other, <<"2">>).

%% 期货类
-define(THOST_FTDC_UOAAT_Futures, <<"1">>).

%% 综合类
-define(THOST_FTDC_UOAAT_SpecialOrgan, <<"2">>).

%% Buy
-define(THOST_FTDC_DEN_Buy, <<"0">>).

%% Sell
-define(THOST_FTDC_DEN_Sell, <<"1">>).

%% Position Opening
-define(THOST_FTDC_OFEN_Open, <<"0">>).

%% Position Close
-define(THOST_FTDC_OFEN_Close, <<"1">>).

%% Forced Liquidation
-define(THOST_FTDC_OFEN_ForceClose, <<"2">>).

%% Close Today
-define(THOST_FTDC_OFEN_CloseToday, <<"3">>).

%% Close Prev.
-define(THOST_FTDC_OFEN_CloseYesterday, <<"4">>).

%% Forced Reduction
-define(THOST_FTDC_OFEN_ForceOff, <<"5">>).

%% Local Forced Liquidation
-define(THOST_FTDC_OFEN_LocalForceClose, <<"6">>).

%% Speculation
-define(THOST_FTDC_HFEN_Speculation, <<"1">>).

%% Arbitrage
-define(THOST_FTDC_HFEN_Arbitrage, <<"2">>).

%% Hedge
-define(THOST_FTDC_HFEN_Hedge, <<"3">>).

%% Deposit/Withdrawal
-define(THOST_FTDC_FIOTEN_FundIO, <<"1">>).

%% Bank-Futures Transfer
-define(THOST_FTDC_FIOTEN_Transfer, <<"2">>).

%% Bank-Futures FX Exchange
-define(THOST_FTDC_FIOTEN_SwapCurrency, <<"3">>).

%% Bank Deposit
-define(THOST_FTDC_FTEN_Deposite, <<"1">>).

%% Payment/Fee
-define(THOST_FTDC_FTEN_ItemFund, <<"2">>).

%% Brokerage Adj
-define(THOST_FTDC_FTEN_Company, <<"3">>).

%% Internal Transfer
-define(THOST_FTDC_FTEN_InnerTransfer, <<"4">>).

%% Deposit
-define(THOST_FTDC_FDEN_In, <<"1">>).

%% Withdrawal
-define(THOST_FTDC_FDEN_Out, <<"2">>).

%% Pledge
-define(THOST_FTDC_FMDEN_In, <<"1">>).

%% Redemption
-define(THOST_FTDC_FMDEN_Out, <<"2">>).

%% 看涨
-define(THOST_FTDC_CP_CallOptions, <<"1">>).

%% 看跌
-define(THOST_FTDC_CP_PutOptions, <<"2">>).

%% 欧式
-define(THOST_FTDC_STM_Continental, <<"0">>).

%% 美式
-define(THOST_FTDC_STM_American, <<"1">>).

%% 百慕大
-define(THOST_FTDC_STM_Bermuda, <<"2">>).

%% 自身对冲
-define(THOST_FTDC_STT_Hedge, <<"0">>).

%% 匹配执行
-define(THOST_FTDC_STT_Match, <<"1">>).

%% 不执行数量
-define(THOST_FTDC_APPT_NotStrikeNum, <<"4">>).

%% 系统生成
-define(THOST_FTDC_GUDS_Gen, <<"0">>).

%% 手工添加
-define(THOST_FTDC_GUDS_Hand, <<"1">>).

%% 没有执行
-define(THOST_FTDC_OER_NoExec, <<"n">>).

%% 已经取消
-define(THOST_FTDC_OER_Canceled, <<"c">>).

%% 执行成功
-define(THOST_FTDC_OER_OK, <<"0">>).

%% 期权持仓不够
-define(THOST_FTDC_OER_NoPosition, <<"1">>).

%% 资金不够
-define(THOST_FTDC_OER_NoDeposit, <<"2">>).

%% 会员不存在
-define(THOST_FTDC_OER_NoParticipant, <<"3">>).

%% 客户不存在
-define(THOST_FTDC_OER_NoClient, <<"4">>).

%% 合约不存在
-define(THOST_FTDC_OER_NoInstrument, <<"6">>).

%% 没有执行权限
-define(THOST_FTDC_OER_NoRight, <<"7">>).

%% 不合理的数量
-define(THOST_FTDC_OER_InvalidVolume, <<"8">>).

%% 没有足够的历史成交
-define(THOST_FTDC_OER_NoEnoughHistoryTrade, <<"9">>).

%% 未知
-define(THOST_FTDC_OER_Unknown, <<"a">>).

%% 期货组合
-define(THOST_FTDC_COMBT_Future, <<"0">>).

%% 垂直价差BUL
-define(THOST_FTDC_COMBT_BUL, <<"1">>).

%% 垂直价差BER
-define(THOST_FTDC_COMBT_BER, <<"2">>).

%% 跨式组合
-define(THOST_FTDC_COMBT_STD, <<"3">>).

%% 宽跨式组合
-define(THOST_FTDC_COMBT_STG, <<"4">>).

%% 备兑组合
-define(THOST_FTDC_COMBT_PRT, <<"5">>).

%% 时间价差组合
-define(THOST_FTDC_COMBT_CLD, <<"6">>).

%% 昨结算价
-define(THOST_FTDC_ORPT_PreSettlementPrice, <<"1">>).

%% 开仓价
-define(THOST_FTDC_ORPT_OpenPrice, <<"4">>).

%% 不计算期权市值盈亏
-define(THOST_FTDC_BLAG_Default, <<"1">>).

%% 计算期权市值亏损
-define(THOST_FTDC_BLAG_IncludeOptValLost, <<"2">>).

%% 执行
-define(THOST_FTDC_ACTP_Exec, <<"1">>).

%% 放弃
-define(THOST_FTDC_ACTP_Abandon, <<"2">>).

%% 已经提交
-define(THOST_FTDC_FQST_Submitted, <<"a">>).

%% 已经接受
-define(THOST_FTDC_FQST_Accepted, <<"b">>).

%% 已经被拒绝
-define(THOST_FTDC_FQST_Rejected, <<"c">>).

%% 按绝对值
-define(THOST_FTDC_VM_Absolute, <<"0">>).

%% 按比率
-define(THOST_FTDC_VM_Ratio, <<"1">>).

%% 保留
-define(THOST_FTDC_EOPF_Reserve, <<"0">>).

%% 不保留
-define(THOST_FTDC_EOPF_UnReserve, <<"1">>).

%% 自动平仓
-define(THOST_FTDC_EOCF_AutoClose, <<"0">>).

%% 免于自动平仓
-define(THOST_FTDC_EOCF_NotToClose, <<"1">>).

%% 期货
-define(THOST_FTDC_PTE_Futures, <<"1">>).

%% 期权
-define(THOST_FTDC_PTE_Options, <<"2">>).

%% ^\d{8}_zz_\d{4}
-define(THOST_FTDC_CUFN_CUFN_O, <<"O">>).

%% ^\d{8}成交表
-define(THOST_FTDC_CUFN_CUFN_T, <<"T">>).

%% ^\d{8}单腿持仓表new
-define(THOST_FTDC_CUFN_CUFN_P, <<"P">>).

%% ^\d{8}非平仓了结表
-define(THOST_FTDC_CUFN_CUFN_N, <<"N">>).

%% ^\d{8}平仓表
-define(THOST_FTDC_CUFN_CUFN_L, <<"L">>).

%% ^\d{8}资金表
-define(THOST_FTDC_CUFN_CUFN_F, <<"F">>).

%% ^\d{8}组合持仓表
-define(THOST_FTDC_CUFN_CUFN_C, <<"C">>).

%% ^\d{8}保证金参数表
-define(THOST_FTDC_CUFN_CUFN_M, <<"M">>).

%% ^\d{8}_dl_\d{3}
-define(THOST_FTDC_DUFN_DUFN_O, <<"O">>).

%% ^\d{8}_成交表
-define(THOST_FTDC_DUFN_DUFN_T, <<"T">>).

%% ^\d{8}_持仓表
-define(THOST_FTDC_DUFN_DUFN_P, <<"P">>).

%% ^\d{8}_资金结算表
-define(THOST_FTDC_DUFN_DUFN_F, <<"F">>).

%% ^\d{8}_优惠组合持仓明细表
-define(THOST_FTDC_DUFN_DUFN_C, <<"C">>).

%% ^\d{8}_持仓明细表
-define(THOST_FTDC_DUFN_DUFN_D, <<"D">>).

%% ^\d{8}_保证金参数表
-define(THOST_FTDC_DUFN_DUFN_M, <<"M">>).

%% ^\d{8}_期权执行表
-define(THOST_FTDC_DUFN_DUFN_S, <<"S">>).

%% ^\d{4}_\d{8}_\d{8}_DailyFundChg
-define(THOST_FTDC_SUFN_SUFN_O, <<"O">>).

%% ^\d{4}_\d{8}_\d{8}_Trade
-define(THOST_FTDC_SUFN_SUFN_T, <<"T">>).

%% ^\d{4}_\d{8}_\d{8}_SettlementDetail
-define(THOST_FTDC_SUFN_SUFN_P, <<"P">>).

%% ^\d{4}_\d{8}_\d{8}_Capital
-define(THOST_FTDC_SUFN_SUFN_F, <<"F">>).

%% ^\d{4}_SG\d{1}_\d{8}_\d{1}_Trade
-define(THOST_FTDC_CFUFN_SUFN_T, <<"T">>).

%% ^\d{4}_SG\d{1}_\d{8}_\d{1}_SettlementDetail
-define(THOST_FTDC_CFUFN_SUFN_P, <<"P">>).

%% ^\d{4}_SG\d{1}_\d{8}_\d{1}_Capital
-define(THOST_FTDC_CFUFN_SUFN_F, <<"F">>).

%% ^\d{4}_SG\d{1}_\d{8}_\d{1}_OptionExec
-define(THOST_FTDC_CFUFN_SUFN_S, <<"S">>).

%% 申请组合
-define(THOST_FTDC_CMDR_Comb, <<"0">>).

%% 申请拆分
-define(THOST_FTDC_CMDR_UnComb, <<"1">>).

%% 锁定
-define(THOST_FTDC_LCKT_Lock, <<"1">>).

%% 解锁
-define(THOST_FTDC_LCKT_Unlock, <<"2">>).

%% 期货
-define(THOST_FTDC_BZTP_Future, <<"1">>).

%% 证券
-define(THOST_FTDC_BZTP_Stock, <<"2">>).

%% 指定登记
-define(THOST_FTDC_DSTP_Register, <<"1">>).

%% 指定撤销
-define(THOST_FTDC_DSTP_Cancel, <<"2">>).

%% 初始化
-define(THOST_FTDC_FRTP_Init, <<"1">>).

%% 锁定
-define(THOST_FTDC_FRTP_Lock, <<"2">>).

%% 执行
-define(THOST_FTDC_FRTP_Exec, <<"3">>).

%% 仓位校验
-define(THOST_FTDC_FRTP_Check, <<"4">>).

%% E+1日执行冻结
-define(THOST_FTDC_FRTP_ExecFreeze, <<"5">>).

%% 冻结
-define(THOST_FTDC_FZTP_Freeze, <<"1">>).

%% 解冻
-define(THOST_FTDC_FZTP_Unfreeze, <<"2">>).

%% 强制执行
-define(THOST_FTDC_FZTP_Force, <<"3">>).

%% 未知系统
-define(THOST_FTDC_TSTP_Unknow, <<"0">>).

%% 期货系统
-define(THOST_FTDC_TSTP_Future, <<"1">>).

%% 个股系统
-define(THOST_FTDC_TSTP_IShare, <<"2">>).

%% 划入经纪公司账户
-define(THOST_FTDC_STPT_ToBroker, <<"1">>).

%% 划入投资者账户
-define(THOST_FTDC_STPT_ToInvestor, <<"2">>).

%% 已经提交
-define(THOST_FTDC_SDPS_Submitted, <<"a">>).

%% 已经接受
-define(THOST_FTDC_SDPS_Accepted, <<"b">>).

%% 已经被拒绝
-define(THOST_FTDC_SDPS_Rejected, <<"c">>).

%% 已经被撤销
-define(THOST_FTDC_SDPS_Cancelled, <<"d">>).

%% 限价单
-define(THOST_FTDC_ISTR_Limit, <<"1">>).

%% 限价全额成交否则取消
-define(THOST_FTDC_ISTR_Limit_FOK, <<"2">>).

%% 市价订单剩余转限价
-define(THOST_FTDC_ISTR_Market_RemainLimit, <<"3">>).

%% 市价订单剩余撤销
-define(THOST_FTDC_ISTR_Market_FAK, <<"4">>).

%% 市价全额成交否则取消
-define(THOST_FTDC_ISTR_Market_FOK, <<"5">>).

%% 证券锁定
-define(THOST_FTDC_ISTR_Lock, <<"6">>).

%% 证券解锁
-define(THOST_FTDC_ISTR_Unlock, <<"7">>).

%% 一级投资者
-define(THOST_FTDC_IVLV_FirstLevel, <<"1">>).

%% 二级投资者
-define(THOST_FTDC_IVLV_SecondLevel, <<"2">>).

%% 三级投资者
-define(THOST_FTDC_IVLV_ThirdLevel, <<"3">>).

%% 实值额
-define(THOST_FTDC_STOV_RealValue, <<"1">>).

%% 盈利额
-define(THOST_FTDC_STOV_ProfitValue, <<"2">>).

%% 实值比例
-define(THOST_FTDC_STOV_RealRatio, <<"3">>).

%% 盈利比例
-define(THOST_FTDC_STOV_ProfitRatio, <<"4">>).

-endif. % -ifndef(ctp_define_hrl).
