%%% -*- coding: utf-8 -*-

-record(cthost_ftdc_dissemination_field, {
          %% 序列系列号
          sequence_series,
          %% 序列号
          sequence_no
         }).

-record(cthost_ftdc_req_user_login_field, {
          %% 交易日
          trading_day,
          %% 经纪公司代码
          broker_id,
          %% 用户代码
          user_id,
          %% 密码
          password,
          %% 用户端产品信息
          user_product_info,
          %% 接口端产品信息
          interface_product_info,
          %% 协议信息
          protocol_info,
          %% Mac地址
          mac_address,
          %% 动态密码
          one_time_password,
          %% 终端IP地址
          client_ipaddress,
          %% 登录备注
          login_remark
         }).

-record(cthost_ftdc_rsp_user_login_field, {
          %% 交易日
          trading_day,
          %% 登录成功时间
          login_time,
          %% 经纪公司代码
          broker_id,
          %% 用户代码
          user_id,
          %% 交易系统名称
          system_name,
          %% 前置编号
          front_id,
          %% 会话编号
          session_id,
          %% 最大报单引用
          max_order_ref,
          %% 上期所时间
          shfetime,
          %% 大商所时间
          dcetime,
          %% 郑商所时间
          czcetime,
          %% 中金所时间
          ffextime,
          %% 能源中心时间
          inetime
         }).

-record(cthost_ftdc_user_logout_field, {
          %% 经纪公司代码
          broker_id,
          %% 用户代码
          user_id
         }).

-record(cthost_ftdc_force_user_logout_field, {
          %% 经纪公司代码
          broker_id,
          %% 用户代码
          user_id
         }).

-record(cthost_ftdc_req_authenticate_field, {
          %% 经纪公司代码
          broker_id,
          %% 用户代码
          user_id,
          %% 用户端产品信息
          user_product_info,
          %% 认证码
          auth_code
         }).

-record(cthost_ftdc_rsp_authenticate_field, {
          %% 经纪公司代码
          broker_id,
          %% 用户代码
          user_id,
          %% 用户端产品信息
          user_product_info
         }).

-record(cthost_ftdc_authentication_info_field, {
          %% 经纪公司代码
          broker_id,
          %% 用户代码
          user_id,
          %% 用户端产品信息
          user_product_info,
          %% 认证信息
          auth_info,
          %% 是否为认证结果
          is_result
         }).

-record(cthost_ftdc_transfer_header_field, {
          %% 版本号，常量，1.0
          version,
          %% 交易代码，必填
          trade_code,
          %% 交易日期，必填，格式：yyyymmdd
          trade_date,
          %% 交易时间，必填，格式：hhmmss
          trade_time,
          %% 发起方流水号，N/A
          trade_serial,
          %% 期货公司代码，必填
          future_id,
          %% 银行代码，根据查询银行得到，必填
          bank_id,
          %% 银行分中心代码，根据查询银行得到，必填
          bank_brch_id,
          %% 操作员，N/A
          oper_no,
          %% 交易设备类型，N/A
          device_id,
          %% 记录数，N/A
          record_num,
          %% 会话编号，N/A
          session_id,
          %% 请求编号，N/A
          request_id
         }).

-record(cthost_ftdc_transfer_bank_to_future_req_field, {
          %% 期货资金账户
          future_account,
          %% 密码标志
          future_pwd_flag,
          %% 密码
          future_acc_pwd,
          %% 转账金额
          trade_amt,
          %% 客户手续费
          cust_fee,
          %% 币种：RMB-人民币 USD-美圆 HKD-港元
          currency_code
         }).

-record(cthost_ftdc_transfer_bank_to_future_rsp_field, {
          %% 响应代码
          ret_code,
          %% 响应信息
          ret_info,
          %% 资金账户
          future_account,
          %% 转帐金额
          trade_amt,
          %% 应收客户手续费
          cust_fee,
          %% 币种
          currency_code
         }).

-record(cthost_ftdc_transfer_future_to_bank_req_field, {
          %% 期货资金账户
          future_account,
          %% 密码标志
          future_pwd_flag,
          %% 密码
          future_acc_pwd,
          %% 转账金额
          trade_amt,
          %% 客户手续费
          cust_fee,
          %% 币种：RMB-人民币 USD-美圆 HKD-港元
          currency_code
         }).

-record(cthost_ftdc_transfer_future_to_bank_rsp_field, {
          %% 响应代码
          ret_code,
          %% 响应信息
          ret_info,
          %% 资金账户
          future_account,
          %% 转帐金额
          trade_amt,
          %% 应收客户手续费
          cust_fee,
          %% 币种
          currency_code
         }).

-record(cthost_ftdc_transfer_qry_bank_req_field, {
          %% 期货资金账户
          future_account,
          %% 密码标志
          future_pwd_flag,
          %% 密码
          future_acc_pwd,
          %% 币种：RMB-人民币 USD-美圆 HKD-港元
          currency_code
         }).

-record(cthost_ftdc_transfer_qry_bank_rsp_field, {
          %% 响应代码
          ret_code,
          %% 响应信息
          ret_info,
          %% 资金账户
          future_account,
          %% 银行余额
          trade_amt,
          %% 银行可用余额
          use_amt,
          %% 银行可取余额
          fetch_amt,
          %% 币种
          currency_code
         }).

-record(cthost_ftdc_transfer_qry_detail_req_field, {
          %% 期货资金账户
          future_account
         }).

-record(cthost_ftdc_transfer_qry_detail_rsp_field, {
          %% 交易日期
          trade_date,
          %% 交易时间
          trade_time,
          %% 交易代码
          trade_code,
          %% 期货流水号
          future_serial,
          %% 期货公司代码
          future_id,
          %% 资金帐号
          future_account,
          %% 银行流水号
          bank_serial,
          %% 银行代码
          bank_id,
          %% 银行分中心代码
          bank_brch_id,
          %% 银行账号
          bank_account,
          %% 证件号码
          cert_code,
          %% 货币代码
          currency_code,
          %% 发生金额
          tx_amount,
          %% 有效标志
          flag
         }).

-record(cthost_ftdc_rsp_info_field, {
          %% 错误代码
          error_id,
          %% 错误信息
          error_msg
         }).

-record(cthost_ftdc_exchange_field, {
          %% 交易所代码
          exchange_id,
          %% 交易所名称
          exchange_name,
          %% 交易所属性
          exchange_property
         }).

-record(cthost_ftdc_product_field, {
          %% 产品代码
          product_id,
          %% 产品名称
          product_name,
          %% 交易所代码
          exchange_id,
          %% 产品类型
          product_class,
          %% 合约数量乘数
          volume_multiple,
          %% 最小变动价位
          price_tick,
          %% 市价单最大下单量
          max_market_order_volume,
          %% 市价单最小下单量
          min_market_order_volume,
          %% 限价单最大下单量
          max_limit_order_volume,
          %% 限价单最小下单量
          min_limit_order_volume,
          %% 持仓类型
          position_type,
          %% 持仓日期类型
          position_date_type,
          %% 平仓处理类型
          close_deal_type,
          %% 交易币种类型
          trade_currency_id,
          %% 质押资金可用范围
          mortgage_fund_use_range,
          %% 交易所产品代码
          exchange_product_id,
          %% 合约基础商品乘数
          underlying_multiple
         }).

-record(cthost_ftdc_instrument_field, {
          %% 合约代码
          instrument_id,
          %% 交易所代码
          exchange_id,
          %% 合约名称
          instrument_name,
          %% 合约在交易所的代码
          exchange_inst_id,
          %% 产品代码
          product_id,
          %% 产品类型
          product_class,
          %% 交割年份
          delivery_year,
          %% 交割月
          delivery_month,
          %% 市价单最大下单量
          max_market_order_volume,
          %% 市价单最小下单量
          min_market_order_volume,
          %% 限价单最大下单量
          max_limit_order_volume,
          %% 限价单最小下单量
          min_limit_order_volume,
          %% 合约数量乘数
          volume_multiple,
          %% 最小变动价位
          price_tick,
          %% 创建日
          create_date,
          %% 上市日
          open_date,
          %% 到期日
          expire_date,
          %% 开始交割日
          start_deliv_date,
          %% 结束交割日
          end_deliv_date,
          %% 合约生命周期状态
          inst_life_phase,
          %% 当前是否交易
          is_trading,
          %% 持仓类型
          position_type,
          %% 持仓日期类型
          position_date_type,
          %% 多头保证金率
          long_margin_ratio,
          %% 空头保证金率
          short_margin_ratio,
          %% 是否使用大额单边保证金算法
          max_margin_side_algorithm,
          %% 基础商品代码
          underlying_instr_id,
          %% 执行价
          strike_price,
          %% 期权类型
          options_type,
          %% 合约基础商品乘数
          underlying_multiple,
          %% 组合类型
          combination_type,
          %% 最小买下单单位
          min_buy_volume,
          %% 最小卖下单单位
          min_sell_volume,
          %% 合约标识码
          instrument_code
         }).

-record(cthost_ftdc_broker_field, {
          %% 经纪公司代码
          broker_id,
          %% 经纪公司简称
          broker_abbr,
          %% 经纪公司名称
          broker_name,
          %% 是否活跃
          is_active
         }).

-record(cthost_ftdc_trader_field, {
          %% 交易所代码
          exchange_id,
          %% 交易所交易员代码
          trader_id,
          %% 会员代码
          participant_id,
          %% 密码
          password,
          %% 安装数量
          install_count,
          %% 经纪公司代码
          broker_id
         }).

-record(cthost_ftdc_investor_field, {
          %% 投资者代码
          investor_id,
          %% 经纪公司代码
          broker_id,
          %% 投资者分组代码
          investor_group_id,
          %% 投资者名称
          investor_name,
          %% 证件类型
          identified_card_type,
          %% 证件号码
          identified_card_no,
          %% 是否活跃
          is_active,
          %% 联系电话
          telephone,
          %% 通讯地址
          address,
          %% 开户日期
          open_date,
          %% 手机
          mobile,
          %% 手续费率模板代码
          comm_model_id,
          %% 保证金率模板代码
          margin_model_id
         }).

-record(cthost_ftdc_trading_code_field, {
          %% 投资者代码
          investor_id,
          %% 经纪公司代码
          broker_id,
          %% 交易所代码
          exchange_id,
          %% 客户代码
          client_id,
          %% 是否活跃
          is_active,
          %% 交易编码类型
          client_idtype,
          %% 营业部编号
          branch_id,
          %% 业务类型
          biz_type
         }).

-record(cthost_ftdc_part_broker_field, {
          %% 经纪公司代码
          broker_id,
          %% 交易所代码
          exchange_id,
          %% 会员代码
          participant_id,
          %% 是否活跃
          is_active
         }).

-record(cthost_ftdc_super_user_field, {
          %% 用户代码
          user_id,
          %% 用户名称
          user_name,
          %% 密码
          password,
          %% 是否活跃
          is_active
         }).

-record(cthost_ftdc_super_user_function_field, {
          %% 用户代码
          user_id,
          %% 功能代码
          function_code
         }).

-record(cthost_ftdc_investor_group_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者分组代码
          investor_group_id,
          %% 投资者分组名称
          investor_group_name
         }).

-record(cthost_ftdc_trading_account_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者帐号
          account_id,
          %% 上次质押金额
          pre_mortgage,
          %% 上次信用额度
          pre_credit,
          %% 上次存款额
          pre_deposit,
          %% 上次结算准备金
          pre_balance,
          %% 上次占用的保证金
          pre_margin,
          %% 利息基数
          interest_base,
          %% 利息收入
          interest,
          %% 入金金额
          deposit,
          %% 出金金额
          withdraw,
          %% 冻结的保证金
          frozen_margin,
          %% 冻结的资金
          frozen_cash,
          %% 冻结的手续费
          frozen_commission,
          %% 当前保证金总额
          curr_margin,
          %% 资金差额
          cash_in,
          %% 手续费
          commission,
          %% 平仓盈亏
          close_profit,
          %% 持仓盈亏
          position_profit,
          %% 期货结算准备金
          balance,
          %% 可用资金
          available,
          %% 可取资金
          withdraw_quota,
          %% 基本准备金
          reserve,
          %% 交易日
          trading_day,
          %% 结算编号
          settlement_id,
          %% 信用额度
          credit,
          %% 质押金额
          mortgage,
          %% 交易所保证金
          exchange_margin,
          %% 投资者交割保证金
          delivery_margin,
          %% 交易所交割保证金
          exchange_delivery_margin,
          %% 保底期货结算准备金
          reserve_balance,
          %% 币种代码
          currency_id,
          %% 上次货币质入金额
          pre_fund_mortgage_in,
          %% 上次货币质出金额
          pre_fund_mortgage_out,
          %% 货币质入金额
          fund_mortgage_in,
          %% 货币质出金额
          fund_mortgage_out,
          %% 货币质押余额
          fund_mortgage_available,
          %% 可质押货币金额
          mortgageable_fund,
          %% 特殊产品占用保证金
          spec_product_margin,
          %% 特殊产品冻结保证金
          spec_product_frozen_margin,
          %% 特殊产品手续费
          spec_product_commission,
          %% 特殊产品冻结手续费
          spec_product_frozen_commission,
          %% 特殊产品持仓盈亏
          spec_product_position_profit,
          %% 特殊产品平仓盈亏
          spec_product_close_profit,
          %% 根据持仓盈亏算法计算的特殊产品持仓盈亏
          spec_product_position_profit_by_alg,
          %% 特殊产品交易所保证金
          spec_product_exchange_margin,
          %% 业务类型
          biz_type
         }).

-record(cthost_ftdc_investor_position_field, {
          %% 合约代码
          instrument_id,
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 持仓多空方向
          posi_direction,
          %% 投机套保标志
          hedge_flag,
          %% 持仓日期
          position_date,
          %% 上日持仓
          yd_position,
          %% 今日持仓
          position,
          %% 多头冻结
          long_frozen,
          %% 空头冻结
          short_frozen,
          %% 开仓冻结金额
          long_frozen_amount,
          %% 开仓冻结金额
          short_frozen_amount,
          %% 开仓量
          open_volume,
          %% 平仓量
          close_volume,
          %% 开仓金额
          open_amount,
          %% 平仓金额
          close_amount,
          %% 持仓成本
          position_cost,
          %% 上次占用的保证金
          pre_margin,
          %% 占用的保证金
          use_margin,
          %% 冻结的保证金
          frozen_margin,
          %% 冻结的资金
          frozen_cash,
          %% 冻结的手续费
          frozen_commission,
          %% 资金差额
          cash_in,
          %% 手续费
          commission,
          %% 平仓盈亏
          close_profit,
          %% 持仓盈亏
          position_profit,
          %% 上次结算价
          pre_settlement_price,
          %% 本次结算价
          settlement_price,
          %% 交易日
          trading_day,
          %% 结算编号
          settlement_id,
          %% 开仓成本
          open_cost,
          %% 交易所保证金
          exchange_margin,
          %% 组合成交形成的持仓
          comb_position,
          %% 组合多头冻结
          comb_long_frozen,
          %% 组合空头冻结
          comb_short_frozen,
          %% 逐日盯市平仓盈亏
          close_profit_by_date,
          %% 逐笔对冲平仓盈亏
          close_profit_by_trade,
          %% 今日持仓
          today_position,
          %% 保证金率
          margin_rate_by_money,
          %% 保证金率(按手数)
          margin_rate_by_volume,
          %% 执行冻结
          strike_frozen,
          %% 执行冻结金额
          strike_frozen_amount,
          %% 放弃执行冻结
          abandon_frozen,
          %% 交易所代码
          exchange_id,
          %% 执行冻结的昨仓
          yd_strike_frozen
         }).

-record(cthost_ftdc_instrument_margin_rate_field, {
          %% 合约代码
          instrument_id,
          %% 投资者范围
          investor_range,
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 投机套保标志
          hedge_flag,
          %% 多头保证金率
          long_margin_ratio_by_money,
          %% 多头保证金费
          long_margin_ratio_by_volume,
          %% 空头保证金率
          short_margin_ratio_by_money,
          %% 空头保证金费
          short_margin_ratio_by_volume,
          %% 是否相对交易所收取
          is_relative
         }).

-record(cthost_ftdc_instrument_commission_rate_field, {
          %% 合约代码
          instrument_id,
          %% 投资者范围
          investor_range,
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 开仓手续费率
          open_ratio_by_money,
          %% 开仓手续费
          open_ratio_by_volume,
          %% 平仓手续费率
          close_ratio_by_money,
          %% 平仓手续费
          close_ratio_by_volume,
          %% 平今手续费率
          close_today_ratio_by_money,
          %% 平今手续费
          close_today_ratio_by_volume,
          %% 交易所代码
          exchange_id,
          %% 业务类型
          biz_type
         }).

-record(cthost_ftdc_depth_market_data_field, {
          %% 交易日
          trading_day,
          %% 合约代码
          instrument_id,
          %% 交易所代码
          exchange_id,
          %% 合约在交易所的代码
          exchange_inst_id,
          %% 最新价
          last_price,
          %% 上次结算价
          pre_settlement_price,
          %% 昨收盘
          pre_close_price,
          %% 昨持仓量
          pre_open_interest,
          %% 今开盘
          open_price,
          %% 最高价
          highest_price,
          %% 最低价
          lowest_price,
          %% 数量
          volume,
          %% 成交金额
          turnover,
          %% 持仓量
          open_interest,
          %% 今收盘
          close_price,
          %% 本次结算价
          settlement_price,
          %% 涨停板价
          upper_limit_price,
          %% 跌停板价
          lower_limit_price,
          %% 昨虚实度
          pre_delta,
          %% 今虚实度
          curr_delta,
          %% 最后修改时间
          update_time,
          %% 最后修改毫秒
          update_millisec,
          %% 申买价一
          bid_price1,
          %% 申买量一
          bid_volume1,
          %% 申卖价一
          ask_price1,
          %% 申卖量一
          ask_volume1,
          %% 申买价二
          bid_price2,
          %% 申买量二
          bid_volume2,
          %% 申卖价二
          ask_price2,
          %% 申卖量二
          ask_volume2,
          %% 申买价三
          bid_price3,
          %% 申买量三
          bid_volume3,
          %% 申卖价三
          ask_price3,
          %% 申卖量三
          ask_volume3,
          %% 申买价四
          bid_price4,
          %% 申买量四
          bid_volume4,
          %% 申卖价四
          ask_price4,
          %% 申卖量四
          ask_volume4,
          %% 申买价五
          bid_price5,
          %% 申买量五
          bid_volume5,
          %% 申卖价五
          ask_price5,
          %% 申卖量五
          ask_volume5,
          %% 当日均价
          average_price,
          %% 业务日期
          action_day
         }).

-record(cthost_ftdc_instrument_trading_right_field, {
          %% 合约代码
          instrument_id,
          %% 投资者范围
          investor_range,
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 交易权限
          trading_right,
          %% 交易所代码
          exchange_id,
          %% 业务类型
          biz_type
         }).

-record(cthost_ftdc_broker_user_field, {
          %% 经纪公司代码
          broker_id,
          %% 用户代码
          user_id,
          %% 用户名称
          user_name,
          %% 用户类型
          user_type,
          %% 是否活跃
          is_active,
          %% 是否使用令牌
          is_using_otp
         }).

-record(cthost_ftdc_broker_user_password_field, {
          %% 经纪公司代码
          broker_id,
          %% 用户代码
          user_id,
          %% 密码
          password
         }).

-record(cthost_ftdc_broker_user_function_field, {
          %% 经纪公司代码
          broker_id,
          %% 用户代码
          user_id,
          %% 经纪公司功能代码
          broker_function_code
         }).

-record(cthost_ftdc_trader_offer_field, {
          %% 交易所代码
          exchange_id,
          %% 交易所交易员代码
          trader_id,
          %% 会员代码
          participant_id,
          %% 密码
          password,
          %% 安装编号
          install_id,
          %% 本地报单编号
          order_local_id,
          %% 交易所交易员连接状态
          trader_connect_status,
          %% 发出连接请求的日期
          connect_request_date,
          %% 发出连接请求的时间
          connect_request_time,
          %% 上次报告日期
          last_report_date,
          %% 上次报告时间
          last_report_time,
          %% 完成连接日期
          connect_date,
          %% 完成连接时间
          connect_time,
          %% 启动日期
          start_date,
          %% 启动时间
          start_time,
          %% 交易日
          trading_day,
          %% 经纪公司代码
          broker_id,
          %% 本席位最大成交编号
          max_trade_id,
          %% 本席位最大报单备拷
          max_order_message_reference,
          %% 业务类型
          biz_type
         }).

-record(cthost_ftdc_settlement_info_field, {
          %% 交易日
          trading_day,
          %% 结算编号
          settlement_id,
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 序号
          sequence_no,
          %% 消息正文
          content
         }).

-record(cthost_ftdc_instrument_margin_rate_adjust_field, {
          %% 合约代码
          instrument_id,
          %% 投资者范围
          investor_range,
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 投机套保标志
          hedge_flag,
          %% 多头保证金率
          long_margin_ratio_by_money,
          %% 多头保证金费
          long_margin_ratio_by_volume,
          %% 空头保证金率
          short_margin_ratio_by_money,
          %% 空头保证金费
          short_margin_ratio_by_volume,
          %% 是否相对交易所收取
          is_relative
         }).

-record(cthost_ftdc_exchange_margin_rate_field, {
          %% 经纪公司代码
          broker_id,
          %% 合约代码
          instrument_id,
          %% 投机套保标志
          hedge_flag,
          %% 多头保证金率
          long_margin_ratio_by_money,
          %% 多头保证金费
          long_margin_ratio_by_volume,
          %% 空头保证金率
          short_margin_ratio_by_money,
          %% 空头保证金费
          short_margin_ratio_by_volume
         }).

-record(cthost_ftdc_exchange_margin_rate_adjust_field, {
          %% 经纪公司代码
          broker_id,
          %% 合约代码
          instrument_id,
          %% 投机套保标志
          hedge_flag,
          %% 跟随交易所投资者多头保证金率
          long_margin_ratio_by_money,
          %% 跟随交易所投资者多头保证金费
          long_margin_ratio_by_volume,
          %% 跟随交易所投资者空头保证金率
          short_margin_ratio_by_money,
          %% 跟随交易所投资者空头保证金费
          short_margin_ratio_by_volume,
          %% 交易所多头保证金率
          exch_long_margin_ratio_by_money,
          %% 交易所多头保证金费
          exch_long_margin_ratio_by_volume,
          %% 交易所空头保证金率
          exch_short_margin_ratio_by_money,
          %% 交易所空头保证金费
          exch_short_margin_ratio_by_volume,
          %% 不跟随交易所投资者多头保证金率
          no_long_margin_ratio_by_money,
          %% 不跟随交易所投资者多头保证金费
          no_long_margin_ratio_by_volume,
          %% 不跟随交易所投资者空头保证金率
          no_short_margin_ratio_by_money,
          %% 不跟随交易所投资者空头保证金费
          no_short_margin_ratio_by_volume
         }).

-record(cthost_ftdc_exchange_rate_field, {
          %% 经纪公司代码
          broker_id,
          %% 源币种
          from_currency_id,
          %% 源币种单位数量
          from_currency_unit,
          %% 目标币种
          to_currency_id,
          %% 汇率
          exchange_rate
         }).

-record(cthost_ftdc_settlement_ref_field, {
          %% 交易日
          trading_day,
          %% 结算编号
          settlement_id
         }).

-record(cthost_ftdc_current_time_field, {
          %% 当前日期
          curr_date,
          %% 当前时间
          curr_time,
          %% 当前时间（毫秒）
          curr_millisec,
          %% 业务日期
          action_day
         }).

-record(cthost_ftdc_comm_phase_field, {
          %% 交易日
          trading_day,
          %% 通讯时段编号
          comm_phase_no,
          %% 系统编号
          system_id
         }).

-record(cthost_ftdc_login_info_field, {
          %% 前置编号
          front_id,
          %% 会话编号
          session_id,
          %% 经纪公司代码
          broker_id,
          %% 用户代码
          user_id,
          %% 登录日期
          login_date,
          %% 登录时间
          login_time,
          %% IP地址
          ipaddress,
          %% 用户端产品信息
          user_product_info,
          %% 接口端产品信息
          interface_product_info,
          %% 协议信息
          protocol_info,
          %% 系统名称
          system_name,
          %% 密码
          password,
          %% 最大报单引用
          max_order_ref,
          %% 上期所时间
          shfetime,
          %% 大商所时间
          dcetime,
          %% 郑商所时间
          czcetime,
          %% 中金所时间
          ffextime,
          %% Mac地址
          mac_address,
          %% 动态密码
          one_time_password,
          %% 能源中心时间
          inetime,
          %% 登录备注
          login_remark
         }).

-record(cthost_ftdc_logout_all_field, {
          %% 前置编号
          front_id,
          %% 会话编号
          session_id,
          %% 系统名称
          system_name
         }).

-record(cthost_ftdc_front_status_field, {
          %% 前置编号
          front_id,
          %% 上次报告日期
          last_report_date,
          %% 上次报告时间
          last_report_time,
          %% 是否活跃
          is_active
         }).

-record(cthost_ftdc_user_password_update_field, {
          %% 经纪公司代码
          broker_id,
          %% 用户代码
          user_id,
          %% 原来的口令
          old_password,
          %% 新的口令
          new_password
         }).

-record(cthost_ftdc_input_order_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id,
          %% 报单引用
          order_ref,
          %% 用户代码
          user_id,
          %% 报单价格条件
          order_price_type,
          %% 买卖方向
          direction,
          %% 组合开平标志
          comb_offset_flag,
          %% 组合投机套保标志
          comb_hedge_flag,
          %% 价格
          limit_price,
          %% 数量
          volume_total_original,
          %% 有效期类型
          time_condition,
          %% GTD日期
          gtddate,
          %% 成交量类型
          volume_condition,
          %% 最小成交量
          min_volume,
          %% 触发条件
          contingent_condition,
          %% 止损价
          stop_price,
          %% 强平原因
          force_close_reason,
          %% 自动挂起标志
          is_auto_suspend,
          %% 业务单元
          business_unit,
          %% 请求编号
          request_id,
          %% 用户强评标志
          user_force_close,
          %% 互换单标志
          is_swap_order,
          %% 交易所代码
          exchange_id,
          %% 投资单元代码
          invest_unit_id,
          %% 资金账号
          account_id,
          %% 币种代码
          currency_id,
          %% 交易编码
          client_id,
          %% IP地址
          ipaddress,
          %% Mac地址
          mac_address
         }).

-record(cthost_ftdc_order_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id,
          %% 报单引用
          order_ref,
          %% 用户代码
          user_id,
          %% 报单价格条件
          order_price_type,
          %% 买卖方向
          direction,
          %% 组合开平标志
          comb_offset_flag,
          %% 组合投机套保标志
          comb_hedge_flag,
          %% 价格
          limit_price,
          %% 数量
          volume_total_original,
          %% 有效期类型
          time_condition,
          %% GTD日期
          gtddate,
          %% 成交量类型
          volume_condition,
          %% 最小成交量
          min_volume,
          %% 触发条件
          contingent_condition,
          %% 止损价
          stop_price,
          %% 强平原因
          force_close_reason,
          %% 自动挂起标志
          is_auto_suspend,
          %% 业务单元
          business_unit,
          %% 请求编号
          request_id,
          %% 本地报单编号
          order_local_id,
          %% 交易所代码
          exchange_id,
          %% 会员代码
          participant_id,
          %% 客户代码
          client_id,
          %% 合约在交易所的代码
          exchange_inst_id,
          %% 交易所交易员代码
          trader_id,
          %% 安装编号
          install_id,
          %% 报单提交状态
          order_submit_status,
          %% 报单提示序号
          notify_sequence,
          %% 交易日
          trading_day,
          %% 结算编号
          settlement_id,
          %% 报单编号
          order_sys_id,
          %% 报单来源
          order_source,
          %% 报单状态
          order_status,
          %% 报单类型
          order_type,
          %% 今成交数量
          volume_traded,
          %% 剩余数量
          volume_total,
          %% 报单日期
          insert_date,
          %% 委托时间
          insert_time,
          %% 激活时间
          active_time,
          %% 挂起时间
          suspend_time,
          %% 最后修改时间
          update_time,
          %% 撤销时间
          cancel_time,
          %% 最后修改交易所交易员代码
          active_trader_id,
          %% 结算会员编号
          clearing_part_id,
          %% 序号
          sequence_no,
          %% 前置编号
          front_id,
          %% 会话编号
          session_id,
          %% 用户端产品信息
          user_product_info,
          %% 状态信息
          status_msg,
          %% 用户强评标志
          user_force_close,
          %% 操作用户代码
          active_user_id,
          %% 经纪公司报单编号
          broker_order_seq,
          %% 相关报单
          relative_order_sys_id,
          %% 郑商所成交数量
          zcetotal_traded_volume,
          %% 互换单标志
          is_swap_order,
          %% 营业部编号
          branch_id,
          %% 投资单元代码
          invest_unit_id,
          %% 资金账号
          account_id,
          %% 币种代码
          currency_id,
          %% IP地址
          ipaddress,
          %% Mac地址
          mac_address
         }).

-record(cthost_ftdc_exchange_order_field, {
          %% 报单价格条件
          order_price_type,
          %% 买卖方向
          direction,
          %% 组合开平标志
          comb_offset_flag,
          %% 组合投机套保标志
          comb_hedge_flag,
          %% 价格
          limit_price,
          %% 数量
          volume_total_original,
          %% 有效期类型
          time_condition,
          %% GTD日期
          gtddate,
          %% 成交量类型
          volume_condition,
          %% 最小成交量
          min_volume,
          %% 触发条件
          contingent_condition,
          %% 止损价
          stop_price,
          %% 强平原因
          force_close_reason,
          %% 自动挂起标志
          is_auto_suspend,
          %% 业务单元
          business_unit,
          %% 请求编号
          request_id,
          %% 本地报单编号
          order_local_id,
          %% 交易所代码
          exchange_id,
          %% 会员代码
          participant_id,
          %% 客户代码
          client_id,
          %% 合约在交易所的代码
          exchange_inst_id,
          %% 交易所交易员代码
          trader_id,
          %% 安装编号
          install_id,
          %% 报单提交状态
          order_submit_status,
          %% 报单提示序号
          notify_sequence,
          %% 交易日
          trading_day,
          %% 结算编号
          settlement_id,
          %% 报单编号
          order_sys_id,
          %% 报单来源
          order_source,
          %% 报单状态
          order_status,
          %% 报单类型
          order_type,
          %% 今成交数量
          volume_traded,
          %% 剩余数量
          volume_total,
          %% 报单日期
          insert_date,
          %% 委托时间
          insert_time,
          %% 激活时间
          active_time,
          %% 挂起时间
          suspend_time,
          %% 最后修改时间
          update_time,
          %% 撤销时间
          cancel_time,
          %% 最后修改交易所交易员代码
          active_trader_id,
          %% 结算会员编号
          clearing_part_id,
          %% 序号
          sequence_no,
          %% 营业部编号
          branch_id,
          %% IP地址
          ipaddress,
          %% Mac地址
          mac_address
         }).

-record(cthost_ftdc_exchange_order_insert_error_field, {
          %% 交易所代码
          exchange_id,
          %% 会员代码
          participant_id,
          %% 交易所交易员代码
          trader_id,
          %% 安装编号
          install_id,
          %% 本地报单编号
          order_local_id,
          %% 错误代码
          error_id,
          %% 错误信息
          error_msg
         }).

-record(cthost_ftdc_input_order_action_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 报单操作引用
          order_action_ref,
          %% 报单引用
          order_ref,
          %% 请求编号
          request_id,
          %% 前置编号
          front_id,
          %% 会话编号
          session_id,
          %% 交易所代码
          exchange_id,
          %% 报单编号
          order_sys_id,
          %% 操作标志
          action_flag,
          %% 价格
          limit_price,
          %% 数量变化
          volume_change,
          %% 用户代码
          user_id,
          %% 合约代码
          instrument_id,
          %% 投资单元代码
          invest_unit_id,
          %% IP地址
          ipaddress,
          %% Mac地址
          mac_address
         }).

-record(cthost_ftdc_order_action_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 报单操作引用
          order_action_ref,
          %% 报单引用
          order_ref,
          %% 请求编号
          request_id,
          %% 前置编号
          front_id,
          %% 会话编号
          session_id,
          %% 交易所代码
          exchange_id,
          %% 报单编号
          order_sys_id,
          %% 操作标志
          action_flag,
          %% 价格
          limit_price,
          %% 数量变化
          volume_change,
          %% 操作日期
          action_date,
          %% 操作时间
          action_time,
          %% 交易所交易员代码
          trader_id,
          %% 安装编号
          install_id,
          %% 本地报单编号
          order_local_id,
          %% 操作本地编号
          action_local_id,
          %% 会员代码
          participant_id,
          %% 客户代码
          client_id,
          %% 业务单元
          business_unit,
          %% 报单操作状态
          order_action_status,
          %% 用户代码
          user_id,
          %% 状态信息
          status_msg,
          %% 合约代码
          instrument_id,
          %% 营业部编号
          branch_id,
          %% 投资单元代码
          invest_unit_id,
          %% IP地址
          ipaddress,
          %% Mac地址
          mac_address
         }).

-record(cthost_ftdc_exchange_order_action_field, {
          %% 交易所代码
          exchange_id,
          %% 报单编号
          order_sys_id,
          %% 操作标志
          action_flag,
          %% 价格
          limit_price,
          %% 数量变化
          volume_change,
          %% 操作日期
          action_date,
          %% 操作时间
          action_time,
          %% 交易所交易员代码
          trader_id,
          %% 安装编号
          install_id,
          %% 本地报单编号
          order_local_id,
          %% 操作本地编号
          action_local_id,
          %% 会员代码
          participant_id,
          %% 客户代码
          client_id,
          %% 业务单元
          business_unit,
          %% 报单操作状态
          order_action_status,
          %% 用户代码
          user_id,
          %% 营业部编号
          branch_id,
          %% IP地址
          ipaddress,
          %% Mac地址
          mac_address
         }).

-record(cthost_ftdc_exchange_order_action_error_field, {
          %% 交易所代码
          exchange_id,
          %% 报单编号
          order_sys_id,
          %% 交易所交易员代码
          trader_id,
          %% 安装编号
          install_id,
          %% 本地报单编号
          order_local_id,
          %% 操作本地编号
          action_local_id,
          %% 错误代码
          error_id,
          %% 错误信息
          error_msg,
          %% 经纪公司代码
          broker_id
         }).

-record(cthost_ftdc_exchange_trade_field, {
          %% 交易所代码
          exchange_id,
          %% 成交编号
          trade_id,
          %% 买卖方向
          direction,
          %% 报单编号
          order_sys_id,
          %% 会员代码
          participant_id,
          %% 客户代码
          client_id,
          %% 交易角色
          trading_role,
          %% 合约在交易所的代码
          exchange_inst_id,
          %% 开平标志
          offset_flag,
          %% 投机套保标志
          hedge_flag,
          %% 价格
          price,
          %% 数量
          volume,
          %% 成交时期
          trade_date,
          %% 成交时间
          trade_time,
          %% 成交类型
          trade_type,
          %% 成交价来源
          price_source,
          %% 交易所交易员代码
          trader_id,
          %% 本地报单编号
          order_local_id,
          %% 结算会员编号
          clearing_part_id,
          %% 业务单元
          business_unit,
          %% 序号
          sequence_no,
          %% 成交来源
          trade_source
         }).

-record(cthost_ftdc_trade_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id,
          %% 报单引用
          order_ref,
          %% 用户代码
          user_id,
          %% 交易所代码
          exchange_id,
          %% 成交编号
          trade_id,
          %% 买卖方向
          direction,
          %% 报单编号
          order_sys_id,
          %% 会员代码
          participant_id,
          %% 客户代码
          client_id,
          %% 交易角色
          trading_role,
          %% 合约在交易所的代码
          exchange_inst_id,
          %% 开平标志
          offset_flag,
          %% 投机套保标志
          hedge_flag,
          %% 价格
          price,
          %% 数量
          volume,
          %% 成交时期
          trade_date,
          %% 成交时间
          trade_time,
          %% 成交类型
          trade_type,
          %% 成交价来源
          price_source,
          %% 交易所交易员代码
          trader_id,
          %% 本地报单编号
          order_local_id,
          %% 结算会员编号
          clearing_part_id,
          %% 业务单元
          business_unit,
          %% 序号
          sequence_no,
          %% 交易日
          trading_day,
          %% 结算编号
          settlement_id,
          %% 经纪公司报单编号
          broker_order_seq,
          %% 成交来源
          trade_source
         }).

-record(cthost_ftdc_user_session_field, {
          %% 前置编号
          front_id,
          %% 会话编号
          session_id,
          %% 经纪公司代码
          broker_id,
          %% 用户代码
          user_id,
          %% 登录日期
          login_date,
          %% 登录时间
          login_time,
          %% IP地址
          ipaddress,
          %% 用户端产品信息
          user_product_info,
          %% 接口端产品信息
          interface_product_info,
          %% 协议信息
          protocol_info,
          %% Mac地址
          mac_address,
          %% 登录备注
          login_remark
         }).

-record(cthost_ftdc_query_max_order_volume_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id,
          %% 买卖方向
          direction,
          %% 开平标志
          offset_flag,
          %% 投机套保标志
          hedge_flag,
          %% 最大允许报单数量
          max_volume,
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_settlement_info_confirm_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 确认日期
          confirm_date,
          %% 确认时间
          confirm_time
         }).

-record(cthost_ftdc_sync_deposit_field, {
          %% 出入金流水号
          deposit_seq_no,
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 入金金额
          deposit,
          %% 是否强制进行
          is_force,
          %% 币种代码
          currency_id,
          %% 业务类型
          biz_type
         }).

-record(cthost_ftdc_sync_fund_mortgage_field, {
          %% 货币质押流水号
          mortgage_seq_no,
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 源币种
          from_currency_id,
          %% 质押金额
          mortgage_amount,
          %% 目标币种
          to_currency_id
         }).

-record(cthost_ftdc_broker_sync_field, {
          %% 经纪公司代码
          broker_id
         }).

-record(cthost_ftdc_syncing_investor_field, {
          %% 投资者代码
          investor_id,
          %% 经纪公司代码
          broker_id,
          %% 投资者分组代码
          investor_group_id,
          %% 投资者名称
          investor_name,
          %% 证件类型
          identified_card_type,
          %% 证件号码
          identified_card_no,
          %% 是否活跃
          is_active,
          %% 联系电话
          telephone,
          %% 通讯地址
          address,
          %% 开户日期
          open_date,
          %% 手机
          mobile,
          %% 手续费率模板代码
          comm_model_id,
          %% 保证金率模板代码
          margin_model_id
         }).

-record(cthost_ftdc_syncing_trading_code_field, {
          %% 投资者代码
          investor_id,
          %% 经纪公司代码
          broker_id,
          %% 交易所代码
          exchange_id,
          %% 客户代码
          client_id,
          %% 是否活跃
          is_active,
          %% 交易编码类型
          client_idtype,
          %% 营业部编号
          branch_id
         }).

-record(cthost_ftdc_syncing_investor_group_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者分组代码
          investor_group_id,
          %% 投资者分组名称
          investor_group_name
         }).

-record(cthost_ftdc_syncing_trading_account_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者帐号
          account_id,
          %% 上次质押金额
          pre_mortgage,
          %% 上次信用额度
          pre_credit,
          %% 上次存款额
          pre_deposit,
          %% 上次结算准备金
          pre_balance,
          %% 上次占用的保证金
          pre_margin,
          %% 利息基数
          interest_base,
          %% 利息收入
          interest,
          %% 入金金额
          deposit,
          %% 出金金额
          withdraw,
          %% 冻结的保证金
          frozen_margin,
          %% 冻结的资金
          frozen_cash,
          %% 冻结的手续费
          frozen_commission,
          %% 当前保证金总额
          curr_margin,
          %% 资金差额
          cash_in,
          %% 手续费
          commission,
          %% 平仓盈亏
          close_profit,
          %% 持仓盈亏
          position_profit,
          %% 期货结算准备金
          balance,
          %% 可用资金
          available,
          %% 可取资金
          withdraw_quota,
          %% 基本准备金
          reserve,
          %% 交易日
          trading_day,
          %% 结算编号
          settlement_id,
          %% 信用额度
          credit,
          %% 质押金额
          mortgage,
          %% 交易所保证金
          exchange_margin,
          %% 投资者交割保证金
          delivery_margin,
          %% 交易所交割保证金
          exchange_delivery_margin,
          %% 保底期货结算准备金
          reserve_balance,
          %% 币种代码
          currency_id,
          %% 上次货币质入金额
          pre_fund_mortgage_in,
          %% 上次货币质出金额
          pre_fund_mortgage_out,
          %% 货币质入金额
          fund_mortgage_in,
          %% 货币质出金额
          fund_mortgage_out,
          %% 货币质押余额
          fund_mortgage_available,
          %% 可质押货币金额
          mortgageable_fund,
          %% 特殊产品占用保证金
          spec_product_margin,
          %% 特殊产品冻结保证金
          spec_product_frozen_margin,
          %% 特殊产品手续费
          spec_product_commission,
          %% 特殊产品冻结手续费
          spec_product_frozen_commission,
          %% 特殊产品持仓盈亏
          spec_product_position_profit,
          %% 特殊产品平仓盈亏
          spec_product_close_profit,
          %% 根据持仓盈亏算法计算的特殊产品持仓盈亏
          spec_product_position_profit_by_alg,
          %% 特殊产品交易所保证金
          spec_product_exchange_margin
         }).

-record(cthost_ftdc_syncing_investor_position_field, {
          %% 合约代码
          instrument_id,
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 持仓多空方向
          posi_direction,
          %% 投机套保标志
          hedge_flag,
          %% 持仓日期
          position_date,
          %% 上日持仓
          yd_position,
          %% 今日持仓
          position,
          %% 多头冻结
          long_frozen,
          %% 空头冻结
          short_frozen,
          %% 开仓冻结金额
          long_frozen_amount,
          %% 开仓冻结金额
          short_frozen_amount,
          %% 开仓量
          open_volume,
          %% 平仓量
          close_volume,
          %% 开仓金额
          open_amount,
          %% 平仓金额
          close_amount,
          %% 持仓成本
          position_cost,
          %% 上次占用的保证金
          pre_margin,
          %% 占用的保证金
          use_margin,
          %% 冻结的保证金
          frozen_margin,
          %% 冻结的资金
          frozen_cash,
          %% 冻结的手续费
          frozen_commission,
          %% 资金差额
          cash_in,
          %% 手续费
          commission,
          %% 平仓盈亏
          close_profit,
          %% 持仓盈亏
          position_profit,
          %% 上次结算价
          pre_settlement_price,
          %% 本次结算价
          settlement_price,
          %% 交易日
          trading_day,
          %% 结算编号
          settlement_id,
          %% 开仓成本
          open_cost,
          %% 交易所保证金
          exchange_margin,
          %% 组合成交形成的持仓
          comb_position,
          %% 组合多头冻结
          comb_long_frozen,
          %% 组合空头冻结
          comb_short_frozen,
          %% 逐日盯市平仓盈亏
          close_profit_by_date,
          %% 逐笔对冲平仓盈亏
          close_profit_by_trade,
          %% 今日持仓
          today_position,
          %% 保证金率
          margin_rate_by_money,
          %% 保证金率(按手数)
          margin_rate_by_volume,
          %% 执行冻结
          strike_frozen,
          %% 执行冻结金额
          strike_frozen_amount,
          %% 放弃执行冻结
          abandon_frozen,
          %% 交易所代码
          exchange_id,
          %% 执行冻结的昨仓
          yd_strike_frozen
         }).

-record(cthost_ftdc_syncing_instrument_margin_rate_field, {
          %% 合约代码
          instrument_id,
          %% 投资者范围
          investor_range,
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 投机套保标志
          hedge_flag,
          %% 多头保证金率
          long_margin_ratio_by_money,
          %% 多头保证金费
          long_margin_ratio_by_volume,
          %% 空头保证金率
          short_margin_ratio_by_money,
          %% 空头保证金费
          short_margin_ratio_by_volume,
          %% 是否相对交易所收取
          is_relative
         }).

-record(cthost_ftdc_syncing_instrument_commission_rate_field, {
          %% 合约代码
          instrument_id,
          %% 投资者范围
          investor_range,
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 开仓手续费率
          open_ratio_by_money,
          %% 开仓手续费
          open_ratio_by_volume,
          %% 平仓手续费率
          close_ratio_by_money,
          %% 平仓手续费
          close_ratio_by_volume,
          %% 平今手续费率
          close_today_ratio_by_money,
          %% 平今手续费
          close_today_ratio_by_volume,
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_syncing_instrument_trading_right_field, {
          %% 合约代码
          instrument_id,
          %% 投资者范围
          investor_range,
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 交易权限
          trading_right,
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_qry_order_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id,
          %% 交易所代码
          exchange_id,
          %% 报单编号
          order_sys_id,
          %% 开始时间
          insert_time_start,
          %% 结束时间
          insert_time_end
         }).

-record(cthost_ftdc_qry_trade_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id,
          %% 交易所代码
          exchange_id,
          %% 成交编号
          trade_id,
          %% 开始时间
          trade_time_start,
          %% 结束时间
          trade_time_end
         }).

-record(cthost_ftdc_qry_investor_position_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id,
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_qry_trading_account_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 币种代码
          currency_id,
          %% 业务类型
          biz_type
         }).

-record(cthost_ftdc_qry_investor_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id
         }).

-record(cthost_ftdc_qry_trading_code_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 交易所代码
          exchange_id,
          %% 客户代码
          client_id,
          %% 交易编码类型
          client_idtype
         }).

-record(cthost_ftdc_qry_investor_group_field, {
          %% 经纪公司代码
          broker_id
         }).

-record(cthost_ftdc_qry_instrument_margin_rate_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id,
          %% 投机套保标志
          hedge_flag
         }).

-record(cthost_ftdc_qry_instrument_commission_rate_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id,
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_qry_instrument_trading_right_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id,
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_qry_broker_field, {
          %% 经纪公司代码
          broker_id
         }).

-record(cthost_ftdc_qry_trader_field, {
          %% 交易所代码
          exchange_id,
          %% 会员代码
          participant_id,
          %% 交易所交易员代码
          trader_id
         }).

-record(cthost_ftdc_qry_super_user_function_field, {
          %% 用户代码
          user_id
         }).

-record(cthost_ftdc_qry_user_session_field, {
          %% 前置编号
          front_id,
          %% 会话编号
          session_id,
          %% 经纪公司代码
          broker_id,
          %% 用户代码
          user_id
         }).

-record(cthost_ftdc_qry_part_broker_field, {
          %% 交易所代码
          exchange_id,
          %% 经纪公司代码
          broker_id,
          %% 会员代码
          participant_id
         }).

-record(cthost_ftdc_qry_front_status_field, {
          %% 前置编号
          front_id
         }).

-record(cthost_ftdc_qry_exchange_order_field, {
          %% 会员代码
          participant_id,
          %% 客户代码
          client_id,
          %% 合约在交易所的代码
          exchange_inst_id,
          %% 交易所代码
          exchange_id,
          %% 交易所交易员代码
          trader_id
         }).

-record(cthost_ftdc_qry_order_action_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_qry_exchange_order_action_field, {
          %% 会员代码
          participant_id,
          %% 客户代码
          client_id,
          %% 交易所代码
          exchange_id,
          %% 交易所交易员代码
          trader_id
         }).

-record(cthost_ftdc_qry_super_user_field, {
          %% 用户代码
          user_id
         }).

-record(cthost_ftdc_qry_exchange_field, {
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_qry_product_field, {
          %% 产品代码
          product_id,
          %% 产品类型
          product_class,
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_qry_instrument_field, {
          %% 合约代码
          instrument_id,
          %% 交易所代码
          exchange_id,
          %% 合约在交易所的代码
          exchange_inst_id,
          %% 产品代码
          product_id
         }).

-record(cthost_ftdc_qry_depth_market_data_field, {
          %% 合约代码
          instrument_id,
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_qry_broker_user_field, {
          %% 经纪公司代码
          broker_id,
          %% 用户代码
          user_id
         }).

-record(cthost_ftdc_qry_broker_user_function_field, {
          %% 经纪公司代码
          broker_id,
          %% 用户代码
          user_id
         }).

-record(cthost_ftdc_qry_trader_offer_field, {
          %% 交易所代码
          exchange_id,
          %% 会员代码
          participant_id,
          %% 交易所交易员代码
          trader_id
         }).

-record(cthost_ftdc_qry_sync_deposit_field, {
          %% 经纪公司代码
          broker_id,
          %% 出入金流水号
          deposit_seq_no
         }).

-record(cthost_ftdc_qry_settlement_info_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 交易日
          trading_day
         }).

-record(cthost_ftdc_qry_exchange_margin_rate_field, {
          %% 经纪公司代码
          broker_id,
          %% 合约代码
          instrument_id,
          %% 投机套保标志
          hedge_flag
         }).

-record(cthost_ftdc_qry_exchange_margin_rate_adjust_field, {
          %% 经纪公司代码
          broker_id,
          %% 合约代码
          instrument_id,
          %% 投机套保标志
          hedge_flag
         }).

-record(cthost_ftdc_qry_exchange_rate_field, {
          %% 经纪公司代码
          broker_id,
          %% 源币种
          from_currency_id,
          %% 目标币种
          to_currency_id
         }).

-record(cthost_ftdc_qry_sync_fund_mortgage_field, {
          %% 经纪公司代码
          broker_id,
          %% 货币质押流水号
          mortgage_seq_no
         }).

-record(cthost_ftdc_qry_his_order_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id,
          %% 交易所代码
          exchange_id,
          %% 报单编号
          order_sys_id,
          %% 开始时间
          insert_time_start,
          %% 结束时间
          insert_time_end,
          %% 交易日
          trading_day,
          %% 结算编号
          settlement_id
         }).

-record(cthost_ftdc_option_instr_mini_margin_field, {
          %% 合约代码
          instrument_id,
          %% 投资者范围
          investor_range,
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 单位（手）期权合约最小保证金
          min_margin,
          %% 取值方式
          value_method,
          %% 是否跟随交易所收取
          is_relative,
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_option_instr_margin_adjust_field, {
          %% 合约代码
          instrument_id,
          %% 投资者范围
          investor_range,
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 投机空头保证金调整系数
          sshort_margin_ratio_by_money,
          %% 投机空头保证金调整系数
          sshort_margin_ratio_by_volume,
          %% 保值空头保证金调整系数
          hshort_margin_ratio_by_money,
          %% 保值空头保证金调整系数
          hshort_margin_ratio_by_volume,
          %% 套利空头保证金调整系数
          ashort_margin_ratio_by_money,
          %% 套利空头保证金调整系数
          ashort_margin_ratio_by_volume,
          %% 是否跟随交易所收取
          is_relative,
          %% 交易所代码
          exchange_id,
          %% 做市商空头保证金调整系数
          mshort_margin_ratio_by_money,
          %% 做市商空头保证金调整系数
          mshort_margin_ratio_by_volume
         }).

-record(cthost_ftdc_option_instr_comm_rate_field, {
          %% 合约代码
          instrument_id,
          %% 投资者范围
          investor_range,
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 开仓手续费率
          open_ratio_by_money,
          %% 开仓手续费
          open_ratio_by_volume,
          %% 平仓手续费率
          close_ratio_by_money,
          %% 平仓手续费
          close_ratio_by_volume,
          %% 平今手续费率
          close_today_ratio_by_money,
          %% 平今手续费
          close_today_ratio_by_volume,
          %% 执行手续费率
          strike_ratio_by_money,
          %% 执行手续费
          strike_ratio_by_volume,
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_option_instr_trade_cost_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id,
          %% 投机套保标志
          hedge_flag,
          %% 期权合约保证金不变部分
          fixed_margin,
          %% 期权合约最小保证金
          mini_margin,
          %% 期权合约权利金
          royalty,
          %% 交易所期权合约保证金不变部分
          exch_fixed_margin,
          %% 交易所期权合约最小保证金
          exch_mini_margin,
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_qry_option_instr_trade_cost_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id,
          %% 投机套保标志
          hedge_flag,
          %% 期权合约报价
          input_price,
          %% 标的价格,填0则用昨结算价
          underlying_price,
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_qry_option_instr_comm_rate_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id,
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_index_price_field, {
          %% 经纪公司代码
          broker_id,
          %% 合约代码
          instrument_id,
          %% 指数现货收盘价
          close_price,
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_input_exec_order_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id,
          %% 执行宣告引用
          exec_order_ref,
          %% 用户代码
          user_id,
          %% 数量
          volume,
          %% 请求编号
          request_id,
          %% 业务单元
          business_unit,
          %% 开平标志
          offset_flag,
          %% 投机套保标志
          hedge_flag,
          %% 执行类型
          action_type,
          %% 保留头寸申请的持仓方向
          posi_direction,
          %% 期权行权后是否保留期货头寸的标记
          reserve_position_flag,
          %% 期权行权后生成的头寸是否自动平仓
          close_flag,
          %% 交易所代码
          exchange_id,
          %% 投资单元代码
          invest_unit_id,
          %% 资金账号
          account_id,
          %% 币种代码
          currency_id,
          %% 交易编码
          client_id,
          %% IP地址
          ipaddress,
          %% Mac地址
          mac_address
         }).

-record(cthost_ftdc_input_exec_order_action_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 执行宣告操作引用
          exec_order_action_ref,
          %% 执行宣告引用
          exec_order_ref,
          %% 请求编号
          request_id,
          %% 前置编号
          front_id,
          %% 会话编号
          session_id,
          %% 交易所代码
          exchange_id,
          %% 执行宣告操作编号
          exec_order_sys_id,
          %% 操作标志
          action_flag,
          %% 用户代码
          user_id,
          %% 合约代码
          instrument_id,
          %% 投资单元代码
          invest_unit_id,
          %% IP地址
          ipaddress,
          %% Mac地址
          mac_address
         }).

-record(cthost_ftdc_exec_order_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id,
          %% 执行宣告引用
          exec_order_ref,
          %% 用户代码
          user_id,
          %% 数量
          volume,
          %% 请求编号
          request_id,
          %% 业务单元
          business_unit,
          %% 开平标志
          offset_flag,
          %% 投机套保标志
          hedge_flag,
          %% 执行类型
          action_type,
          %% 保留头寸申请的持仓方向
          posi_direction,
          %% 期权行权后是否保留期货头寸的标记
          reserve_position_flag,
          %% 期权行权后生成的头寸是否自动平仓
          close_flag,
          %% 本地执行宣告编号
          exec_order_local_id,
          %% 交易所代码
          exchange_id,
          %% 会员代码
          participant_id,
          %% 客户代码
          client_id,
          %% 合约在交易所的代码
          exchange_inst_id,
          %% 交易所交易员代码
          trader_id,
          %% 安装编号
          install_id,
          %% 执行宣告提交状态
          order_submit_status,
          %% 报单提示序号
          notify_sequence,
          %% 交易日
          trading_day,
          %% 结算编号
          settlement_id,
          %% 执行宣告编号
          exec_order_sys_id,
          %% 报单日期
          insert_date,
          %% 插入时间
          insert_time,
          %% 撤销时间
          cancel_time,
          %% 执行结果
          exec_result,
          %% 结算会员编号
          clearing_part_id,
          %% 序号
          sequence_no,
          %% 前置编号
          front_id,
          %% 会话编号
          session_id,
          %% 用户端产品信息
          user_product_info,
          %% 状态信息
          status_msg,
          %% 操作用户代码
          active_user_id,
          %% 经纪公司报单编号
          broker_exec_order_seq,
          %% 营业部编号
          branch_id,
          %% 投资单元代码
          invest_unit_id,
          %% 资金账号
          account_id,
          %% 币种代码
          currency_id,
          %% IP地址
          ipaddress,
          %% Mac地址
          mac_address
         }).

-record(cthost_ftdc_exec_order_action_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 执行宣告操作引用
          exec_order_action_ref,
          %% 执行宣告引用
          exec_order_ref,
          %% 请求编号
          request_id,
          %% 前置编号
          front_id,
          %% 会话编号
          session_id,
          %% 交易所代码
          exchange_id,
          %% 执行宣告操作编号
          exec_order_sys_id,
          %% 操作标志
          action_flag,
          %% 操作日期
          action_date,
          %% 操作时间
          action_time,
          %% 交易所交易员代码
          trader_id,
          %% 安装编号
          install_id,
          %% 本地执行宣告编号
          exec_order_local_id,
          %% 操作本地编号
          action_local_id,
          %% 会员代码
          participant_id,
          %% 客户代码
          client_id,
          %% 业务单元
          business_unit,
          %% 报单操作状态
          order_action_status,
          %% 用户代码
          user_id,
          %% 执行类型
          action_type,
          %% 状态信息
          status_msg,
          %% 合约代码
          instrument_id,
          %% 营业部编号
          branch_id,
          %% 投资单元代码
          invest_unit_id,
          %% IP地址
          ipaddress,
          %% Mac地址
          mac_address
         }).

-record(cthost_ftdc_qry_exec_order_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id,
          %% 交易所代码
          exchange_id,
          %% 执行宣告编号
          exec_order_sys_id,
          %% 开始时间
          insert_time_start,
          %% 结束时间
          insert_time_end
         }).

-record(cthost_ftdc_exchange_exec_order_field, {
          %% 数量
          volume,
          %% 请求编号
          request_id,
          %% 业务单元
          business_unit,
          %% 开平标志
          offset_flag,
          %% 投机套保标志
          hedge_flag,
          %% 执行类型
          action_type,
          %% 保留头寸申请的持仓方向
          posi_direction,
          %% 期权行权后是否保留期货头寸的标记
          reserve_position_flag,
          %% 期权行权后生成的头寸是否自动平仓
          close_flag,
          %% 本地执行宣告编号
          exec_order_local_id,
          %% 交易所代码
          exchange_id,
          %% 会员代码
          participant_id,
          %% 客户代码
          client_id,
          %% 合约在交易所的代码
          exchange_inst_id,
          %% 交易所交易员代码
          trader_id,
          %% 安装编号
          install_id,
          %% 执行宣告提交状态
          order_submit_status,
          %% 报单提示序号
          notify_sequence,
          %% 交易日
          trading_day,
          %% 结算编号
          settlement_id,
          %% 执行宣告编号
          exec_order_sys_id,
          %% 报单日期
          insert_date,
          %% 插入时间
          insert_time,
          %% 撤销时间
          cancel_time,
          %% 执行结果
          exec_result,
          %% 结算会员编号
          clearing_part_id,
          %% 序号
          sequence_no,
          %% 营业部编号
          branch_id,
          %% IP地址
          ipaddress,
          %% Mac地址
          mac_address
         }).

-record(cthost_ftdc_qry_exchange_exec_order_field, {
          %% 会员代码
          participant_id,
          %% 客户代码
          client_id,
          %% 合约在交易所的代码
          exchange_inst_id,
          %% 交易所代码
          exchange_id,
          %% 交易所交易员代码
          trader_id
         }).

-record(cthost_ftdc_qry_exec_order_action_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_exchange_exec_order_action_field, {
          %% 交易所代码
          exchange_id,
          %% 执行宣告操作编号
          exec_order_sys_id,
          %% 操作标志
          action_flag,
          %% 操作日期
          action_date,
          %% 操作时间
          action_time,
          %% 交易所交易员代码
          trader_id,
          %% 安装编号
          install_id,
          %% 本地执行宣告编号
          exec_order_local_id,
          %% 操作本地编号
          action_local_id,
          %% 会员代码
          participant_id,
          %% 客户代码
          client_id,
          %% 业务单元
          business_unit,
          %% 报单操作状态
          order_action_status,
          %% 用户代码
          user_id,
          %% 执行类型
          action_type,
          %% 营业部编号
          branch_id,
          %% IP地址
          ipaddress,
          %% Mac地址
          mac_address
         }).

-record(cthost_ftdc_qry_exchange_exec_order_action_field, {
          %% 会员代码
          participant_id,
          %% 客户代码
          client_id,
          %% 交易所代码
          exchange_id,
          %% 交易所交易员代码
          trader_id
         }).

-record(cthost_ftdc_err_exec_order_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id,
          %% 执行宣告引用
          exec_order_ref,
          %% 用户代码
          user_id,
          %% 数量
          volume,
          %% 请求编号
          request_id,
          %% 业务单元
          business_unit,
          %% 开平标志
          offset_flag,
          %% 投机套保标志
          hedge_flag,
          %% 执行类型
          action_type,
          %% 保留头寸申请的持仓方向
          posi_direction,
          %% 期权行权后是否保留期货头寸的标记
          reserve_position_flag,
          %% 期权行权后生成的头寸是否自动平仓
          close_flag,
          %% 交易所代码
          exchange_id,
          %% 投资单元代码
          invest_unit_id,
          %% 资金账号
          account_id,
          %% 币种代码
          currency_id,
          %% 交易编码
          client_id,
          %% IP地址
          ipaddress,
          %% Mac地址
          mac_address,
          %% 错误代码
          error_id,
          %% 错误信息
          error_msg
         }).

-record(cthost_ftdc_qry_err_exec_order_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id
         }).

-record(cthost_ftdc_err_exec_order_action_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 执行宣告操作引用
          exec_order_action_ref,
          %% 执行宣告引用
          exec_order_ref,
          %% 请求编号
          request_id,
          %% 前置编号
          front_id,
          %% 会话编号
          session_id,
          %% 交易所代码
          exchange_id,
          %% 执行宣告操作编号
          exec_order_sys_id,
          %% 操作标志
          action_flag,
          %% 用户代码
          user_id,
          %% 合约代码
          instrument_id,
          %% 投资单元代码
          invest_unit_id,
          %% IP地址
          ipaddress,
          %% Mac地址
          mac_address,
          %% 错误代码
          error_id,
          %% 错误信息
          error_msg
         }).

-record(cthost_ftdc_qry_err_exec_order_action_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id
         }).

-record(cthost_ftdc_option_instr_trading_right_field, {
          %% 合约代码
          instrument_id,
          %% 投资者范围
          investor_range,
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 买卖方向
          direction,
          %% 交易权限
          trading_right,
          %% 交易所代码
          exchange_id,
          %% 投机套保标志
          hedge_flag
         }).

-record(cthost_ftdc_qry_option_instr_trading_right_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id,
          %% 买卖方向
          direction,
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_input_for_quote_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id,
          %% 询价引用
          for_quote_ref,
          %% 用户代码
          user_id,
          %% 交易所代码
          exchange_id,
          %% 投资单元代码
          invest_unit_id,
          %% IP地址
          ipaddress,
          %% Mac地址
          mac_address
         }).

-record(cthost_ftdc_for_quote_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id,
          %% 询价引用
          for_quote_ref,
          %% 用户代码
          user_id,
          %% 本地询价编号
          for_quote_local_id,
          %% 交易所代码
          exchange_id,
          %% 会员代码
          participant_id,
          %% 客户代码
          client_id,
          %% 合约在交易所的代码
          exchange_inst_id,
          %% 交易所交易员代码
          trader_id,
          %% 安装编号
          install_id,
          %% 报单日期
          insert_date,
          %% 插入时间
          insert_time,
          %% 询价状态
          for_quote_status,
          %% 前置编号
          front_id,
          %% 会话编号
          session_id,
          %% 状态信息
          status_msg,
          %% 操作用户代码
          active_user_id,
          %% 经纪公司询价编号
          broker_for_quto_seq,
          %% 投资单元代码
          invest_unit_id,
          %% IP地址
          ipaddress,
          %% Mac地址
          mac_address,
          %% 营业部编号
          branch_id
         }).

-record(cthost_ftdc_qry_for_quote_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id,
          %% 交易所代码
          exchange_id,
          %% 开始时间
          insert_time_start,
          %% 结束时间
          insert_time_end
         }).

-record(cthost_ftdc_exchange_for_quote_field, {
          %% 本地询价编号
          for_quote_local_id,
          %% 交易所代码
          exchange_id,
          %% 会员代码
          participant_id,
          %% 客户代码
          client_id,
          %% 合约在交易所的代码
          exchange_inst_id,
          %% 交易所交易员代码
          trader_id,
          %% 安装编号
          install_id,
          %% 报单日期
          insert_date,
          %% 插入时间
          insert_time,
          %% 询价状态
          for_quote_status,
          %% IP地址
          ipaddress,
          %% Mac地址
          mac_address,
          %% 营业部编号
          branch_id
         }).

-record(cthost_ftdc_qry_exchange_for_quote_field, {
          %% 会员代码
          participant_id,
          %% 客户代码
          client_id,
          %% 合约在交易所的代码
          exchange_inst_id,
          %% 交易所代码
          exchange_id,
          %% 交易所交易员代码
          trader_id
         }).

-record(cthost_ftdc_input_quote_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id,
          %% 报价引用
          quote_ref,
          %% 用户代码
          user_id,
          %% 卖价格
          ask_price,
          %% 买价格
          bid_price,
          %% 卖数量
          ask_volume,
          %% 买数量
          bid_volume,
          %% 请求编号
          request_id,
          %% 业务单元
          business_unit,
          %% 卖开平标志
          ask_offset_flag,
          %% 买开平标志
          bid_offset_flag,
          %% 卖投机套保标志
          ask_hedge_flag,
          %% 买投机套保标志
          bid_hedge_flag,
          %% 衍生卖报单引用
          ask_order_ref,
          %% 衍生买报单引用
          bid_order_ref,
          %% 应价编号
          for_quote_sys_id,
          %% 交易所代码
          exchange_id,
          %% 投资单元代码
          invest_unit_id,
          %% 交易编码
          client_id,
          %% IP地址
          ipaddress,
          %% Mac地址
          mac_address
         }).

-record(cthost_ftdc_input_quote_action_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 报价操作引用
          quote_action_ref,
          %% 报价引用
          quote_ref,
          %% 请求编号
          request_id,
          %% 前置编号
          front_id,
          %% 会话编号
          session_id,
          %% 交易所代码
          exchange_id,
          %% 报价操作编号
          quote_sys_id,
          %% 操作标志
          action_flag,
          %% 用户代码
          user_id,
          %% 合约代码
          instrument_id,
          %% 投资单元代码
          invest_unit_id,
          %% 交易编码
          client_id,
          %% IP地址
          ipaddress,
          %% Mac地址
          mac_address
         }).

-record(cthost_ftdc_quote_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id,
          %% 报价引用
          quote_ref,
          %% 用户代码
          user_id,
          %% 卖价格
          ask_price,
          %% 买价格
          bid_price,
          %% 卖数量
          ask_volume,
          %% 买数量
          bid_volume,
          %% 请求编号
          request_id,
          %% 业务单元
          business_unit,
          %% 卖开平标志
          ask_offset_flag,
          %% 买开平标志
          bid_offset_flag,
          %% 卖投机套保标志
          ask_hedge_flag,
          %% 买投机套保标志
          bid_hedge_flag,
          %% 本地报价编号
          quote_local_id,
          %% 交易所代码
          exchange_id,
          %% 会员代码
          participant_id,
          %% 客户代码
          client_id,
          %% 合约在交易所的代码
          exchange_inst_id,
          %% 交易所交易员代码
          trader_id,
          %% 安装编号
          install_id,
          %% 报价提示序号
          notify_sequence,
          %% 报价提交状态
          order_submit_status,
          %% 交易日
          trading_day,
          %% 结算编号
          settlement_id,
          %% 报价编号
          quote_sys_id,
          %% 报单日期
          insert_date,
          %% 插入时间
          insert_time,
          %% 撤销时间
          cancel_time,
          %% 报价状态
          quote_status,
          %% 结算会员编号
          clearing_part_id,
          %% 序号
          sequence_no,
          %% 卖方报单编号
          ask_order_sys_id,
          %% 买方报单编号
          bid_order_sys_id,
          %% 前置编号
          front_id,
          %% 会话编号
          session_id,
          %% 用户端产品信息
          user_product_info,
          %% 状态信息
          status_msg,
          %% 操作用户代码
          active_user_id,
          %% 经纪公司报价编号
          broker_quote_seq,
          %% 衍生卖报单引用
          ask_order_ref,
          %% 衍生买报单引用
          bid_order_ref,
          %% 应价编号
          for_quote_sys_id,
          %% 营业部编号
          branch_id,
          %% 投资单元代码
          invest_unit_id,
          %% 资金账号
          account_id,
          %% 币种代码
          currency_id,
          %% IP地址
          ipaddress,
          %% Mac地址
          mac_address
         }).

-record(cthost_ftdc_quote_action_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 报价操作引用
          quote_action_ref,
          %% 报价引用
          quote_ref,
          %% 请求编号
          request_id,
          %% 前置编号
          front_id,
          %% 会话编号
          session_id,
          %% 交易所代码
          exchange_id,
          %% 报价操作编号
          quote_sys_id,
          %% 操作标志
          action_flag,
          %% 操作日期
          action_date,
          %% 操作时间
          action_time,
          %% 交易所交易员代码
          trader_id,
          %% 安装编号
          install_id,
          %% 本地报价编号
          quote_local_id,
          %% 操作本地编号
          action_local_id,
          %% 会员代码
          participant_id,
          %% 客户代码
          client_id,
          %% 业务单元
          business_unit,
          %% 报单操作状态
          order_action_status,
          %% 用户代码
          user_id,
          %% 状态信息
          status_msg,
          %% 合约代码
          instrument_id,
          %% 营业部编号
          branch_id,
          %% 投资单元代码
          invest_unit_id,
          %% IP地址
          ipaddress,
          %% Mac地址
          mac_address
         }).

-record(cthost_ftdc_qry_quote_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id,
          %% 交易所代码
          exchange_id,
          %% 报价编号
          quote_sys_id,
          %% 开始时间
          insert_time_start,
          %% 结束时间
          insert_time_end
         }).

-record(cthost_ftdc_exchange_quote_field, {
          %% 卖价格
          ask_price,
          %% 买价格
          bid_price,
          %% 卖数量
          ask_volume,
          %% 买数量
          bid_volume,
          %% 请求编号
          request_id,
          %% 业务单元
          business_unit,
          %% 卖开平标志
          ask_offset_flag,
          %% 买开平标志
          bid_offset_flag,
          %% 卖投机套保标志
          ask_hedge_flag,
          %% 买投机套保标志
          bid_hedge_flag,
          %% 本地报价编号
          quote_local_id,
          %% 交易所代码
          exchange_id,
          %% 会员代码
          participant_id,
          %% 客户代码
          client_id,
          %% 合约在交易所的代码
          exchange_inst_id,
          %% 交易所交易员代码
          trader_id,
          %% 安装编号
          install_id,
          %% 报价提示序号
          notify_sequence,
          %% 报价提交状态
          order_submit_status,
          %% 交易日
          trading_day,
          %% 结算编号
          settlement_id,
          %% 报价编号
          quote_sys_id,
          %% 报单日期
          insert_date,
          %% 插入时间
          insert_time,
          %% 撤销时间
          cancel_time,
          %% 报价状态
          quote_status,
          %% 结算会员编号
          clearing_part_id,
          %% 序号
          sequence_no,
          %% 卖方报单编号
          ask_order_sys_id,
          %% 买方报单编号
          bid_order_sys_id,
          %% 应价编号
          for_quote_sys_id,
          %% 营业部编号
          branch_id,
          %% IP地址
          ipaddress,
          %% Mac地址
          mac_address
         }).

-record(cthost_ftdc_qry_exchange_quote_field, {
          %% 会员代码
          participant_id,
          %% 客户代码
          client_id,
          %% 合约在交易所的代码
          exchange_inst_id,
          %% 交易所代码
          exchange_id,
          %% 交易所交易员代码
          trader_id
         }).

-record(cthost_ftdc_qry_quote_action_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_exchange_quote_action_field, {
          %% 交易所代码
          exchange_id,
          %% 报价操作编号
          quote_sys_id,
          %% 操作标志
          action_flag,
          %% 操作日期
          action_date,
          %% 操作时间
          action_time,
          %% 交易所交易员代码
          trader_id,
          %% 安装编号
          install_id,
          %% 本地报价编号
          quote_local_id,
          %% 操作本地编号
          action_local_id,
          %% 会员代码
          participant_id,
          %% 客户代码
          client_id,
          %% 业务单元
          business_unit,
          %% 报单操作状态
          order_action_status,
          %% 用户代码
          user_id,
          %% IP地址
          ipaddress,
          %% Mac地址
          mac_address,
          %% 营业部编号
          branch_id
         }).

-record(cthost_ftdc_qry_exchange_quote_action_field, {
          %% 会员代码
          participant_id,
          %% 客户代码
          client_id,
          %% 交易所代码
          exchange_id,
          %% 交易所交易员代码
          trader_id
         }).

-record(cthost_ftdc_option_instr_delta_field, {
          %% 合约代码
          instrument_id,
          %% 投资者范围
          investor_range,
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% Delta值
          delta,
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_for_quote_rsp_field, {
          %% 交易日
          trading_day,
          %% 合约代码
          instrument_id,
          %% 询价编号
          for_quote_sys_id,
          %% 询价时间
          for_quote_time,
          %% 业务日期
          action_day,
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_strike_offset_field, {
          %% 合约代码
          instrument_id,
          %% 投资者范围
          investor_range,
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 执行偏移值
          offset,
          %% 行权偏移类型
          offset_type,
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_qry_strike_offset_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id
         }).

-record(cthost_ftdc_input_lock_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id,
          %% 锁定引用
          lock_ref,
          %% 用户代码
          user_id,
          %% 数量
          volume,
          %% 请求编号
          request_id,
          %% 业务单元
          business_unit,
          %% 锁定类型
          lock_type,
          %% 交易所代码
          exchange_id,
          %% IP地址
          ipaddress,
          %% Mac地址
          mac_address
         }).

-record(cthost_ftdc_lock_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id,
          %% 锁定引用
          lock_ref,
          %% 用户代码
          user_id,
          %% 数量
          volume,
          %% 请求编号
          request_id,
          %% 业务单元
          business_unit,
          %% 锁定类型
          lock_type,
          %% 本地锁定编号
          lock_local_id,
          %% 交易所代码
          exchange_id,
          %% 会员代码
          participant_id,
          %% 客户代码
          client_id,
          %% 合约在交易所的代码
          exchange_inst_id,
          %% 交易所交易员代码
          trader_id,
          %% 安装编号
          install_id,
          %% 执行宣告提交状态
          order_submit_status,
          %% 报单提示序号
          notify_sequence,
          %% 交易日
          trading_day,
          %% 结算编号
          settlement_id,
          %% 锁定编号
          lock_sys_id,
          %% 报单日期
          insert_date,
          %% 插入时间
          insert_time,
          %% 撤销时间
          cancel_time,
          %% 锁定状态
          lock_status,
          %% 结算会员编号
          clearing_part_id,
          %% 序号
          sequence_no,
          %% 前置编号
          front_id,
          %% 会话编号
          session_id,
          %% 用户端产品信息
          user_product_info,
          %% 状态信息
          status_msg,
          %% 操作用户代码
          active_user_id,
          %% 经纪公司报单编号
          broker_lock_seq,
          %% 营业部编号
          branch_id,
          %% IP地址
          ipaddress,
          %% Mac地址
          mac_address
         }).

-record(cthost_ftdc_qry_lock_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id,
          %% 交易所代码
          exchange_id,
          %% 锁定编号
          lock_sys_id,
          %% 开始时间
          insert_time_start,
          %% 结束时间
          insert_time_end
         }).

-record(cthost_ftdc_lock_position_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id,
          %% 交易所代码
          exchange_id,
          %% 数量
          volume,
          %% 冻结数量
          frozen_volume
         }).

-record(cthost_ftdc_qry_lock_position_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id,
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_etfoption_instr_comm_rate_field, {
          %% 合约代码
          instrument_id,
          %% 投资者范围
          investor_range,
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 开仓手续费率
          open_ratio_by_money,
          %% 开仓手续费
          open_ratio_by_volume,
          %% 平仓手续费率
          close_ratio_by_money,
          %% 平仓手续费
          close_ratio_by_volume,
          %% 平今手续费率
          close_today_ratio_by_money,
          %% 平今手续费
          close_today_ratio_by_volume,
          %% 执行手续费率
          strike_ratio_by_money,
          %% 执行手续费
          strike_ratio_by_volume,
          %% 交易所代码
          exchange_id,
          %% 投机套保标志
          hedge_flag,
          %% 持仓方向
          posi_direction
         }).

-record(cthost_ftdc_qry_etfoption_instr_comm_rate_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id,
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_posi_freeze_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id,
          %% 交易所代码
          exchange_id,
          %% 本地报单编号
          order_local_id,
          %% 交易所交易员代码
          trader_id,
          %% 会员代码
          participant_id,
          %% 安装编号
          install_id,
          %% 数量
          volume,
          %% 冻结原因
          freeze_reason_type,
          %% 冻结类型
          freeze_type
         }).

-record(cthost_ftdc_qry_exchange_lock_field, {
          %% 会员代码
          participant_id,
          %% 客户代码
          client_id,
          %% 合约在交易所的代码
          exchange_inst_id,
          %% 交易所代码
          exchange_id,
          %% 交易所交易员代码
          trader_id
         }).

-record(cthost_ftdc_exchange_lock_field, {
          %% 数量
          volume,
          %% 请求编号
          request_id,
          %% 业务单元
          business_unit,
          %% 锁定类型
          lock_type,
          %% 本地锁定编号
          lock_local_id,
          %% 交易所代码
          exchange_id,
          %% 会员代码
          participant_id,
          %% 客户代码
          client_id,
          %% 合约在交易所的代码
          exchange_inst_id,
          %% 交易所交易员代码
          trader_id,
          %% 安装编号
          install_id,
          %% 执行宣告提交状态
          order_submit_status,
          %% 报单提示序号
          notify_sequence,
          %% 交易日
          trading_day,
          %% 结算编号
          settlement_id,
          %% 锁定编号
          lock_sys_id,
          %% 报单日期
          insert_date,
          %% 插入时间
          insert_time,
          %% 撤销时间
          cancel_time,
          %% 锁定状态
          lock_status,
          %% 结算会员编号
          clearing_part_id,
          %% 序号
          sequence_no,
          %% 营业部编号
          branch_id,
          %% IP地址
          ipaddress,
          %% Mac地址
          mac_address
         }).

-record(cthost_ftdc_exchange_exec_order_action_error_field, {
          %% 交易所代码
          exchange_id,
          %% 执行宣告编号
          exec_order_sys_id,
          %% 交易所交易员代码
          trader_id,
          %% 安装编号
          install_id,
          %% 本地执行宣告编号
          exec_order_local_id,
          %% 操作本地编号
          action_local_id,
          %% 错误代码
          error_id,
          %% 错误信息
          error_msg,
          %% 经纪公司代码
          broker_id
         }).

-record(cthost_ftdc_input_batch_order_action_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 报单操作引用
          order_action_ref,
          %% 请求编号
          request_id,
          %% 前置编号
          front_id,
          %% 会话编号
          session_id,
          %% 交易所代码
          exchange_id,
          %% 用户代码
          user_id,
          %% 投资单元代码
          invest_unit_id,
          %% IP地址
          ipaddress,
          %% Mac地址
          mac_address
         }).

-record(cthost_ftdc_batch_order_action_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 报单操作引用
          order_action_ref,
          %% 请求编号
          request_id,
          %% 前置编号
          front_id,
          %% 会话编号
          session_id,
          %% 交易所代码
          exchange_id,
          %% 操作日期
          action_date,
          %% 操作时间
          action_time,
          %% 交易所交易员代码
          trader_id,
          %% 安装编号
          install_id,
          %% 操作本地编号
          action_local_id,
          %% 会员代码
          participant_id,
          %% 客户代码
          client_id,
          %% 业务单元
          business_unit,
          %% 报单操作状态
          order_action_status,
          %% 用户代码
          user_id,
          %% 状态信息
          status_msg,
          %% 投资单元代码
          invest_unit_id,
          %% IP地址
          ipaddress,
          %% Mac地址
          mac_address
         }).

-record(cthost_ftdc_exchange_batch_order_action_field, {
          %% 交易所代码
          exchange_id,
          %% 操作日期
          action_date,
          %% 操作时间
          action_time,
          %% 交易所交易员代码
          trader_id,
          %% 安装编号
          install_id,
          %% 操作本地编号
          action_local_id,
          %% 会员代码
          participant_id,
          %% 客户代码
          client_id,
          %% 业务单元
          business_unit,
          %% 报单操作状态
          order_action_status,
          %% 用户代码
          user_id,
          %% IP地址
          ipaddress,
          %% Mac地址
          mac_address
         }).

-record(cthost_ftdc_qry_batch_order_action_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_limit_posi_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id,
          %% 交易所代码
          exchange_id,
          %% 总数量限制
          total_volume,
          %% 多头数量限制
          long_volume,
          %% 当日多头开仓数量限制
          open_volume,
          %% 多头持仓金额限制,不再使用
          long_amount,
          %% 总数量冻结
          total_volume_frozen,
          %% 多头数量冻结
          long_volume_frozen,
          %% 当日开仓数量冻结
          open_volume_frozen,
          %% 多头持仓金额冻结,不再使用
          long_amount_frozen
         }).

-record(cthost_ftdc_qry_limit_posi_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id,
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_broker_limit_posi_field, {
          %% 经纪公司代码
          broker_id,
          %% 合约代码
          instrument_id,
          %% 交易所代码
          exchange_id,
          %% 总数量限制
          total_volume,
          %% 多头数量限制
          long_volume,
          %% 总数量冻结
          total_volume_frozen,
          %% 多头数量冻结
          long_volume_frozen
         }).

-record(cthost_ftdc_qry_broker_limit_posi_field, {
          %% 经纪公司代码
          broker_id,
          %% 合约代码
          instrument_id,
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_limit_posi_sfield, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id,
          %% 交易所代码
          exchange_id,
          %% 总数量限制
          total_volume,
          %% 当日开仓数量限制
          open_volume,
          %% 总数量冻结
          total_volume_frozen,
          %% 当日开仓数量冻结
          open_volume_frozen
         }).

-record(cthost_ftdc_qry_limit_posi_sfield, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id,
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_limit_posi_param_field, {
          %% 合约代码
          instrument_id,
          %% 投资者范围
          investor_range,
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 交易所代码
          exchange_id,
          %% 总数量限制
          total_volume,
          %% 多头数量限制
          long_volume,
          %% 当日开仓数量限制
          open_volume,
          %% 多头持仓金额限制,不再使用
          long_amount
         }).

-record(cthost_ftdc_broker_limit_posi_param_field, {
          %% 经纪公司代码
          broker_id,
          %% 合约代码
          instrument_id,
          %% 交易所代码
          exchange_id,
          %% 总数量限制
          total_volume,
          %% 多头数量限制
          long_volume
         }).

-record(cthost_ftdc_limit_posi_param_sfield, {
          %% 合约代码
          instrument_id,
          %% 投资者范围
          investor_range,
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 交易所代码
          exchange_id,
          %% 总数量限制
          total_volume,
          %% 当日开仓数量限制
          open_volume
         }).

-record(cthost_ftdc_input_stock_disposal_action_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 证券处置操作引用
          stock_disposal_action_ref,
          %% 证券处置引用
          stock_disposal_ref,
          %% 请求编号
          request_id,
          %% 前置编号
          front_id,
          %% 会话编号
          session_id,
          %% 交易所代码
          exchange_id,
          %% 证券处置操作编号
          stock_disposal_sys_id,
          %% 操作标志
          action_flag,
          %% 用户代码
          user_id,
          %% 合约代码
          instrument_id
         }).

-record(cthost_ftdc_stock_disposal_action_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 证券处置操作引用
          stock_disposal_action_ref,
          %% 证券处置引用
          stock_disposal_ref,
          %% 请求编号
          request_id,
          %% 前置编号
          front_id,
          %% 会话编号
          session_id,
          %% 交易所代码
          exchange_id,
          %% 证券处置操作编号
          stock_disposal_sys_id,
          %% 操作标志
          action_flag,
          %% 操作日期
          action_date,
          %% 操作时间
          action_time,
          %% 交易所交易员代码
          trader_id,
          %% 安装编号
          install_id,
          %% 本地证券处置编号
          stock_disposal_local_id,
          %% 操作本地编号
          action_local_id,
          %% 会员代码
          participant_id,
          %% 客户代码
          client_id,
          %% 业务单元
          business_unit,
          %% 报单操作状态
          order_action_status,
          %% 用户代码
          user_id,
          %% 执行类型
          action_type,
          %% 状态信息
          status_msg,
          %% 合约代码
          instrument_id,
          %% 营业部编号
          branch_id
         }).

-record(cthost_ftdc_qry_stock_disposal_action_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_exchange_stock_disposal_action_field, {
          %% 交易所代码
          exchange_id,
          %% 证券处置操作编号
          stock_disposal_sys_id,
          %% 操作标志
          action_flag,
          %% 操作日期
          action_date,
          %% 操作时间
          action_time,
          %% 交易所交易员代码
          trader_id,
          %% 安装编号
          install_id,
          %% 本地证券处置编号
          stock_disposal_local_id,
          %% 操作本地编号
          action_local_id,
          %% 会员代码
          participant_id,
          %% 客户代码
          client_id,
          %% 业务单元
          business_unit,
          %% 报单操作状态
          order_action_status,
          %% 用户代码
          user_id,
          %% 执行类型
          action_type,
          %% 营业部编号
          branch_id
         }).

-record(cthost_ftdc_qry_exchange_stock_disposal_action_field, {
          %% 会员代码
          participant_id,
          %% 客户代码
          client_id,
          %% 交易所代码
          exchange_id,
          %% 交易所交易员代码
          trader_id
         }).

-record(cthost_ftdc_qry_err_stock_disposal_action_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id
         }).

-record(cthost_ftdc_exchange_stock_disposal_action_error_field, {
          %% 交易所代码
          exchange_id,
          %% 证券处置编号
          stock_disposal_sys_id,
          %% 交易所交易员代码
          trader_id,
          %% 安装编号
          install_id,
          %% 本地证券处置编号
          stock_disposal_local_id,
          %% 操作本地编号
          action_local_id,
          %% 错误代码
          error_id,
          %% 错误信息
          error_msg,
          %% 经纪公司代码
          broker_id
         }).

-record(cthost_ftdc_err_stock_disposal_action_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 证券处置操作引用
          stock_disposal_action_ref,
          %% 证券处置引用
          stock_disposal_ref,
          %% 请求编号
          request_id,
          %% 前置编号
          front_id,
          %% 会话编号
          session_id,
          %% 交易所代码
          exchange_id,
          %% 证券处置操作编号
          stock_disposal_sys_id,
          %% 操作标志
          action_flag,
          %% 用户代码
          user_id,
          %% 合约代码
          instrument_id,
          %% 错误代码
          error_id,
          %% 错误信息
          error_msg
         }).

-record(cthost_ftdc_investor_level_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 交易所代码
          exchange_id,
          %% 投资者分级类型
          level_type
         }).

-record(cthost_ftdc_comb_instrument_guard_field, {
          %% 经纪公司代码
          broker_id,
          %% 合约代码
          instrument_id,
          %%
          guarant_ratio
         }).

-record(cthost_ftdc_qry_comb_instrument_guard_field, {
          %% 经纪公司代码
          broker_id,
          %% 合约代码
          instrument_id
         }).

-record(cthost_ftdc_input_comb_action_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id,
          %% 组合引用
          comb_action_ref,
          %% 用户代码
          user_id,
          %% 买卖方向
          direction,
          %% 数量
          volume,
          %% 组合指令方向
          comb_direction,
          %% 投机套保标志
          hedge_flag,
          %% 交易所代码
          exchange_id,
          %% IP地址
          ipaddress,
          %% Mac地址
          mac_address
         }).

-record(cthost_ftdc_comb_action_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id,
          %% 组合引用
          comb_action_ref,
          %% 用户代码
          user_id,
          %% 买卖方向
          direction,
          %% 数量
          volume,
          %% 组合指令方向
          comb_direction,
          %% 投机套保标志
          hedge_flag,
          %% 本地申请组合编号
          action_local_id,
          %% 交易所代码
          exchange_id,
          %% 会员代码
          participant_id,
          %% 客户代码
          client_id,
          %% 合约在交易所的代码
          exchange_inst_id,
          %% 交易所交易员代码
          trader_id,
          %% 安装编号
          install_id,
          %% 组合状态
          action_status,
          %% 报单提示序号
          notify_sequence,
          %% 交易日
          trading_day,
          %% 结算编号
          settlement_id,
          %% 序号
          sequence_no,
          %% 前置编号
          front_id,
          %% 会话编号
          session_id,
          %% 用户端产品信息
          user_product_info,
          %% 状态信息
          status_msg,
          %% IP地址
          ipaddress,
          %% Mac地址
          mac_address,
          %% 组合编号
          com_trade_id,
          %% 营业部编号
          branch_id
         }).

-record(cthost_ftdc_qry_comb_action_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id,
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_exchange_comb_action_field, {
          %% 买卖方向
          direction,
          %% 数量
          volume,
          %% 组合指令方向
          comb_direction,
          %% 投机套保标志
          hedge_flag,
          %% 本地申请组合编号
          action_local_id,
          %% 交易所代码
          exchange_id,
          %% 会员代码
          participant_id,
          %% 客户代码
          client_id,
          %% 合约在交易所的代码
          exchange_inst_id,
          %% 交易所交易员代码
          trader_id,
          %% 安装编号
          install_id,
          %% 组合状态
          action_status,
          %% 报单提示序号
          notify_sequence,
          %% 交易日
          trading_day,
          %% 结算编号
          settlement_id,
          %% 序号
          sequence_no,
          %% IP地址
          ipaddress,
          %% Mac地址
          mac_address,
          %% 组合编号
          com_trade_id,
          %% 营业部编号
          branch_id
         }).

-record(cthost_ftdc_qry_exchange_comb_action_field, {
          %% 会员代码
          participant_id,
          %% 客户代码
          client_id,
          %% 合约在交易所的代码
          exchange_inst_id,
          %% 交易所代码
          exchange_id,
          %% 交易所交易员代码
          trader_id
         }).

-record(cthost_ftdc_product_exch_rate_field, {
          %% 产品代码
          product_id,
          %% 报价币种类型
          quote_currency_id,
          %% 汇率
          exchange_rate
         }).

-record(cthost_ftdc_qry_product_exch_rate_field, {
          %% 产品代码
          product_id
         }).

-record(cthost_ftdc_input_designate_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 指定登记引用
          designate_ref,
          %% 用户代码
          user_id,
          %% 指定方向
          designate_type,
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_designate_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 指定登记引用
          designate_ref,
          %% 用户代码
          user_id,
          %% 指定方向
          designate_type,
          %% 本地指定编号
          designate_local_id,
          %% 交易所代码
          exchange_id,
          %% 会员代码
          participant_id,
          %% 客户代码
          client_id,
          %% 交易所交易员代码
          trader_id,
          %% 安装编号
          install_id,
          %% 指定状态
          designate_status,
          %% 报单提示序号
          notify_sequence,
          %% 交易日
          trading_day,
          %% 结算编号
          settlement_id,
          %% 报单日期
          insert_date,
          %% 插入时间
          insert_time,
          %% 前置编号
          front_id,
          %% 会话编号
          session_id,
          %% 用户端产品信息
          user_product_info,
          %% 状态信息
          status_msg,
          %% 营业部编号
          branch_id
         }).

-record(cthost_ftdc_qry_designate_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_exchange_designate_field, {
          %% 指定方向
          designate_type,
          %% 本地指定编号
          designate_local_id,
          %% 交易所代码
          exchange_id,
          %% 会员代码
          participant_id,
          %% 客户代码
          client_id,
          %% 交易所交易员代码
          trader_id,
          %% 安装编号
          install_id,
          %% 指定状态
          designate_status,
          %% 报单提示序号
          notify_sequence,
          %% 交易日
          trading_day,
          %% 结算编号
          settlement_id,
          %% 报单日期
          insert_date,
          %% 插入时间
          insert_time,
          %% 营业部编号
          branch_id
         }).

-record(cthost_ftdc_input_stock_disposal_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 证券处置登记引用
          stock_disposal_ref,
          %% 用户代码
          user_id,
          %% 合约代码
          instrument_id,
          %% 数量
          volume,
          %% 证券处置方向
          stock_disposal_type,
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_stock_disposal_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 证券处置登记引用
          stock_disposal_ref,
          %% 用户代码
          user_id,
          %% 合约代码
          instrument_id,
          %% 数量
          volume,
          %% 证券处置方向
          stock_disposal_type,
          %% 本地证券处置编号
          stock_disposal_local_id,
          %% 交易所代码
          exchange_id,
          %% 合约在交易所的代码
          exchange_inst_id,
          %% 会员代码
          participant_id,
          %% 客户代码
          client_id,
          %% 交易所交易员代码
          trader_id,
          %% 安装编号
          install_id,
          %% 证券处置状态
          stock_disposal_status,
          %% 报单提示序号
          notify_sequence,
          %% 交易日
          trading_day,
          %% 结算编号
          settlement_id,
          %% 报单日期
          insert_date,
          %% 插入时间
          insert_time,
          %% 前置编号
          front_id,
          %% 会话编号
          session_id,
          %% 用户端产品信息
          user_product_info,
          %% 状态信息
          status_msg,
          %% 营业部编号
          branch_id,
          %% 证券处置操作编号
          stock_disposal_sys_id,
          %% 业务单元
          business_unit
         }).

-record(cthost_ftdc_qry_stock_disposal_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_exchange_stock_disposal_field, {
          %% 数量
          volume,
          %% 证券处置方向
          stock_disposal_type,
          %% 本地证券处置编号
          stock_disposal_local_id,
          %% 交易所代码
          exchange_id,
          %% 合约在交易所的代码
          exchange_inst_id,
          %% 会员代码
          participant_id,
          %% 客户代码
          client_id,
          %% 交易所交易员代码
          trader_id,
          %% 安装编号
          install_id,
          %% 证券处置状态
          stock_disposal_status,
          %% 报单提示序号
          notify_sequence,
          %% 交易日
          trading_day,
          %% 结算编号
          settlement_id,
          %% 报单日期
          insert_date,
          %% 插入时间
          insert_time,
          %% 营业部编号
          branch_id,
          %% 证券处置操作编号
          stock_disposal_sys_id,
          %% 业务单元
          business_unit
         }).

-record(cthost_ftdc_qry_investor_level_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_qry_for_quote_param_field, {
          %% 经纪公司代码
          broker_id,
          %% 合约代码
          instrument_id,
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_for_quote_param_field, {
          %% 经纪公司代码
          broker_id,
          %% 合约代码
          instrument_id,
          %% 交易所代码
          exchange_id,
          %% 最新价
          last_price,
          %% 价差
          price_interval
         }).

-record(cthost_ftdc_qry_exec_freeze_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id,
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_exec_freeze_field, {
          %% 标的合约代码
          instrument_id,
          %% 交易所代码
          exchange_id,
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 持仓多空方向
          posi_direction,
          %% 期权类型
          options_type,
          %% 冻结的数量_单位股
          volume,
          %% 冻结金额
          frozen_amount
         }).

-record(cthost_ftdc_mmoption_instr_comm_rate_field, {
          %% 合约代码
          instrument_id,
          %% 投资者范围
          investor_range,
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 开仓手续费率
          open_ratio_by_money,
          %% 开仓手续费
          open_ratio_by_volume,
          %% 平仓手续费率
          close_ratio_by_money,
          %% 平仓手续费
          close_ratio_by_volume,
          %% 平今手续费率
          close_today_ratio_by_money,
          %% 平今手续费
          close_today_ratio_by_volume,
          %% 执行手续费率
          strike_ratio_by_money,
          %% 执行手续费
          strike_ratio_by_volume,
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_qry_mmoption_instr_comm_rate_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id,
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_mminstrument_commission_rate_field, {
          %% 合约代码
          instrument_id,
          %% 投资者范围
          investor_range,
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 开仓手续费率
          open_ratio_by_money,
          %% 开仓手续费
          open_ratio_by_volume,
          %% 平仓手续费率
          close_ratio_by_money,
          %% 平仓手续费
          close_ratio_by_volume,
          %% 平今手续费率
          close_today_ratio_by_money,
          %% 平今手续费
          close_today_ratio_by_volume,
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_qry_mminstrument_commission_rate_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id,
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_instrument_order_comm_rate_field, {
          %% 合约代码
          instrument_id,
          %% 投资者范围
          investor_range,
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 交易所代码
          exchange_id,
          %% 投机套保标志
          hedge_flag,
          %% 报单手续费
          order_comm_by_volume,
          %% 撤单手续费
          order_action_comm_by_volume
         }).

-record(cthost_ftdc_qry_instrument_order_comm_rate_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id,
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_limit_amount_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 交易所代码
          exchange_id,
          %% 多头持仓金额限制
          long_amount,
          %% 多头持仓金额冻结
          long_amount_frozen
         }).

-record(cthost_ftdc_qry_limit_amount_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_limit_amount_param_field, {
          %% 投资者范围
          investor_range,
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 交易所代码
          exchange_id,
          %% 多头持仓金额限制
          long_amount
         }).

-record(cthost_ftdc_option_instr_margin_guard_field, {
          %% 合约代码
          instrument_id,
          %% 投资者范围
          investor_range,
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 投机空头保证金调整系数
          sshort_margin_ratio_by_money,
          %% 投机空头保证金调整系数
          sshort_margin_ratio_by_volume,
          %% 保值空头保证金调整系数
          hshort_margin_ratio_by_money,
          %% 保值空头保证金调整系数
          hshort_margin_ratio_by_volume,
          %% 套利空头保证金调整系数
          ashort_margin_ratio_by_money,
          %% 套利空头保证金调整系数
          ashort_margin_ratio_by_volume,
          %% 是否跟随交易所收取
          is_relative,
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_market_data_field, {
          %% 交易日
          trading_day,
          %% 合约代码
          instrument_id,
          %% 交易所代码
          exchange_id,
          %% 合约在交易所的代码
          exchange_inst_id,
          %% 最新价
          last_price,
          %% 上次结算价
          pre_settlement_price,
          %% 昨收盘
          pre_close_price,
          %% 昨持仓量
          pre_open_interest,
          %% 今开盘
          open_price,
          %% 最高价
          highest_price,
          %% 最低价
          lowest_price,
          %% 数量
          volume,
          %% 成交金额
          turnover,
          %% 持仓量
          open_interest,
          %% 今收盘
          close_price,
          %% 本次结算价
          settlement_price,
          %% 涨停板价
          upper_limit_price,
          %% 跌停板价
          lower_limit_price,
          %% 昨虚实度
          pre_delta,
          %% 今虚实度
          curr_delta,
          %% 最后修改时间
          update_time,
          %% 最后修改毫秒
          update_millisec,
          %% 业务日期
          action_day
         }).

-record(cthost_ftdc_market_data_base_field, {
          %% 交易日
          trading_day,
          %% 上次结算价
          pre_settlement_price,
          %% 昨收盘
          pre_close_price,
          %% 昨持仓量
          pre_open_interest,
          %% 昨虚实度
          pre_delta
         }).

-record(cthost_ftdc_market_data_static_field, {
          %% 今开盘
          open_price,
          %% 最高价
          highest_price,
          %% 最低价
          lowest_price,
          %% 今收盘
          close_price,
          %% 涨停板价
          upper_limit_price,
          %% 跌停板价
          lower_limit_price,
          %% 本次结算价
          settlement_price,
          %% 今虚实度
          curr_delta
         }).

-record(cthost_ftdc_market_data_last_match_field, {
          %% 最新价
          last_price,
          %% 数量
          volume,
          %% 成交金额
          turnover,
          %% 持仓量
          open_interest
         }).

-record(cthost_ftdc_market_data_best_price_field, {
          %% 申买价一
          bid_price1,
          %% 申买量一
          bid_volume1,
          %% 申卖价一
          ask_price1,
          %% 申卖量一
          ask_volume1
         }).

-record(cthost_ftdc_market_data_bid23_field, {
          %% 申买价二
          bid_price2,
          %% 申买量二
          bid_volume2,
          %% 申买价三
          bid_price3,
          %% 申买量三
          bid_volume3
         }).

-record(cthost_ftdc_market_data_ask23_field, {
          %% 申卖价二
          ask_price2,
          %% 申卖量二
          ask_volume2,
          %% 申卖价三
          ask_price3,
          %% 申卖量三
          ask_volume3
         }).

-record(cthost_ftdc_market_data_bid45_field, {
          %% 申买价四
          bid_price4,
          %% 申买量四
          bid_volume4,
          %% 申买价五
          bid_price5,
          %% 申买量五
          bid_volume5
         }).

-record(cthost_ftdc_market_data_ask45_field, {
          %% 申卖价四
          ask_price4,
          %% 申卖量四
          ask_volume4,
          %% 申卖价五
          ask_price5,
          %% 申卖量五
          ask_volume5
         }).

-record(cthost_ftdc_market_data_update_time_field, {
          %% 合约代码
          instrument_id,
          %% 最后修改时间
          update_time,
          %% 最后修改毫秒
          update_millisec,
          %% 业务日期
          action_day,
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_market_data_exchange_field, {
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_specific_instrument_field, {
          %% 合约代码
          instrument_id
         }).

-record(cthost_ftdc_instrument_status_field, {
          %% 交易所代码
          exchange_id,
          %% 合约在交易所的代码
          exchange_inst_id,
          %% 结算组代码
          settlement_group_id,
          %% 合约代码
          instrument_id,
          %% 合约交易状态
          instrument_status,
          %% 交易阶段编号
          trading_segment_sn,
          %% 进入本状态时间
          enter_time,
          %% 进入本状态原因
          enter_reason
         }).

-record(cthost_ftdc_qry_instrument_status_field, {
          %% 交易所代码
          exchange_id,
          %% 合约在交易所的代码
          exchange_inst_id
         }).

-record(cthost_ftdc_investor_account_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 投资者帐号
          account_id,
          %% 币种代码
          currency_id,
          %% 业务类型
          biz_type
         }).

-record(cthost_ftdc_position_profit_algorithm_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者帐号
          account_id,
          %% 盈亏算法
          algorithm,
          %% 备注
          memo,
          %% 币种代码
          currency_id
         }).

-record(cthost_ftdc_discount_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者范围
          investor_range,
          %% 投资者代码
          investor_id,
          %% 资金折扣比例
          discount
         }).

-record(cthost_ftdc_qry_transfer_bank_field, {
          %% 银行代码
          bank_id,
          %% 银行分中心代码
          bank_brch_id
         }).

-record(cthost_ftdc_transfer_bank_field, {
          %% 银行代码
          bank_id,
          %% 银行分中心代码
          bank_brch_id,
          %% 银行名称
          bank_name,
          %% 是否活跃
          is_active
         }).

-record(cthost_ftdc_qry_investor_position_detail_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id,
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_investor_position_detail_field, {
          %% 合约代码
          instrument_id,
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 投机套保标志
          hedge_flag,
          %% 买卖
          direction,
          %% 开仓日期
          open_date,
          %% 成交编号
          trade_id,
          %% 数量
          volume,
          %% 开仓价
          open_price,
          %% 交易日
          trading_day,
          %% 结算编号
          settlement_id,
          %% 成交类型
          trade_type,
          %% 组合合约代码
          comb_instrument_id,
          %% 交易所代码
          exchange_id,
          %% 逐日盯市平仓盈亏
          close_profit_by_date,
          %% 逐笔对冲平仓盈亏
          close_profit_by_trade,
          %% 逐日盯市持仓盈亏
          position_profit_by_date,
          %% 逐笔对冲持仓盈亏
          position_profit_by_trade,
          %% 投资者保证金
          margin,
          %% 交易所保证金
          exch_margin,
          %% 保证金率
          margin_rate_by_money,
          %% 保证金率(按手数)
          margin_rate_by_volume,
          %% 昨结算价
          last_settlement_price,
          %% 结算价
          settlement_price,
          %% 平仓量
          close_volume,
          %% 平仓金额
          close_amount
         }).

-record(cthost_ftdc_trading_account_password_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者帐号
          account_id,
          %% 密码
          password,
          %% 币种代码
          currency_id
         }).

-record(cthost_ftdc_mdtrader_offer_field, {
          %% 交易所代码
          exchange_id,
          %% 交易所交易员代码
          trader_id,
          %% 会员代码
          participant_id,
          %% 密码
          password,
          %% 安装编号
          install_id,
          %% 本地报单编号
          order_local_id,
          %% 交易所交易员连接状态
          trader_connect_status,
          %% 发出连接请求的日期
          connect_request_date,
          %% 发出连接请求的时间
          connect_request_time,
          %% 上次报告日期
          last_report_date,
          %% 上次报告时间
          last_report_time,
          %% 完成连接日期
          connect_date,
          %% 完成连接时间
          connect_time,
          %% 启动日期
          start_date,
          %% 启动时间
          start_time,
          %% 交易日
          trading_day,
          %% 经纪公司代码
          broker_id,
          %% 本席位最大成交编号
          max_trade_id,
          %% 本席位最大报单备拷
          max_order_message_reference,
          %% 业务类型
          biz_type
         }).

-record(cthost_ftdc_qry_mdtrader_offer_field, {
          %% 交易所代码
          exchange_id,
          %% 会员代码
          participant_id,
          %% 交易所交易员代码
          trader_id
         }).

-record(cthost_ftdc_qry_notice_field, {
          %% 经纪公司代码
          broker_id
         }).

-record(cthost_ftdc_notice_field, {
          %% 经纪公司代码
          broker_id,
          %% 消息正文
          content,
          %% 经纪公司通知内容序列号
          sequence_label
         }).

-record(cthost_ftdc_user_right_field, {
          %% 经纪公司代码
          broker_id,
          %% 用户代码
          user_id,
          %% 客户权限类型
          user_right_type,
          %% 是否禁止
          is_forbidden
         }).

-record(cthost_ftdc_qry_settlement_info_confirm_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id
         }).

-record(cthost_ftdc_load_settlement_info_field, {
          %% 经纪公司代码
          broker_id
         }).

-record(cthost_ftdc_broker_withdraw_algorithm_field, {
          %% 经纪公司代码
          broker_id,
          %% 可提资金算法
          withdraw_algorithm,
          %% 资金使用率
          using_ratio,
          %% 可提是否包含平仓盈利
          include_close_profit,
          %% 本日无仓且无成交客户是否受可提比例限制
          all_without_trade,
          %% 可用是否包含平仓盈利
          avail_include_close_profit,
          %% 是否启用用户事件
          is_broker_user_event,
          %% 币种代码
          currency_id,
          %% 货币质押比率
          fund_mortgage_ratio,
          %% 权益算法
          balance_algorithm
         }).

-record(cthost_ftdc_trading_account_password_update_v1_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 原来的口令
          old_password,
          %% 新的口令
          new_password
         }).

-record(cthost_ftdc_trading_account_password_update_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者帐号
          account_id,
          %% 原来的口令
          old_password,
          %% 新的口令
          new_password,
          %% 币种代码
          currency_id
         }).

-record(cthost_ftdc_qry_combination_leg_field, {
          %% 组合合约代码
          comb_instrument_id,
          %% 单腿编号
          leg_id,
          %% 单腿合约代码
          leg_instrument_id
         }).

-record(cthost_ftdc_qry_sync_status_field, {
          %% 交易日
          trading_day
         }).

-record(cthost_ftdc_combination_leg_field, {
          %% 组合合约代码
          comb_instrument_id,
          %% 单腿编号
          leg_id,
          %% 单腿合约代码
          leg_instrument_id,
          %% 买卖方向
          direction,
          %% 单腿乘数
          leg_multiple,
          %% 派生层数
          imply_level
         }).

-record(cthost_ftdc_sync_status_field, {
          %% 交易日
          trading_day,
          %% 数据同步状态
          data_sync_status
         }).

-record(cthost_ftdc_qry_link_man_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id
         }).

-record(cthost_ftdc_link_man_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 联系人类型
          person_type,
          %% 证件类型
          identified_card_type,
          %% 证件号码
          identified_card_no,
          %% 名称
          person_name,
          %% 联系电话
          telephone,
          %% 通讯地址
          address,
          %% 邮政编码
          zip_code,
          %% 优先级
          priority,
          %% 开户邮政编码
          uoazip_code,
          %% 全称
          person_full_name
         }).

-record(cthost_ftdc_qry_broker_user_event_field, {
          %% 经纪公司代码
          broker_id,
          %% 用户代码
          user_id,
          %% 用户事件类型
          user_event_type
         }).

-record(cthost_ftdc_broker_user_event_field, {
          %% 经纪公司代码
          broker_id,
          %% 用户代码
          user_id,
          %% 用户事件类型
          user_event_type,
          %% 用户事件序号
          event_sequence_no,
          %% 事件发生日期
          event_date,
          %% 事件发生时间
          event_time,
          %% 用户事件信息
          user_event_info,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id,
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_qry_contract_bank_field, {
          %% 经纪公司代码
          broker_id,
          %% 银行代码
          bank_id,
          %% 银行分中心代码
          bank_brch_id
         }).

-record(cthost_ftdc_contract_bank_field, {
          %% 经纪公司代码
          broker_id,
          %% 银行代码
          bank_id,
          %% 银行分中心代码
          bank_brch_id,
          %% 银行名称
          bank_name
         }).

-record(cthost_ftdc_investor_position_combine_detail_field, {
          %% 交易日
          trading_day,
          %% 开仓日期
          open_date,
          %% 交易所代码
          exchange_id,
          %% 结算编号
          settlement_id,
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 组合编号
          com_trade_id,
          %% 撮合编号
          trade_id,
          %% 合约代码
          instrument_id,
          %% 投机套保标志
          hedge_flag,
          %% 买卖
          direction,
          %% 持仓量
          total_amt,
          %% 投资者保证金
          margin,
          %% 交易所保证金
          exch_margin,
          %% 保证金率
          margin_rate_by_money,
          %% 保证金率(按手数)
          margin_rate_by_volume,
          %% 单腿编号
          leg_id,
          %% 单腿乘数
          leg_multiple,
          %% 组合持仓合约编码
          comb_instrument_id,
          %% 成交组号
          trade_group_id
         }).

-record(cthost_ftdc_parked_order_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id,
          %% 报单引用
          order_ref,
          %% 用户代码
          user_id,
          %% 报单价格条件
          order_price_type,
          %% 买卖方向
          direction,
          %% 组合开平标志
          comb_offset_flag,
          %% 组合投机套保标志
          comb_hedge_flag,
          %% 价格
          limit_price,
          %% 数量
          volume_total_original,
          %% 有效期类型
          time_condition,
          %% GTD日期
          gtddate,
          %% 成交量类型
          volume_condition,
          %% 最小成交量
          min_volume,
          %% 触发条件
          contingent_condition,
          %% 止损价
          stop_price,
          %% 强平原因
          force_close_reason,
          %% 自动挂起标志
          is_auto_suspend,
          %% 业务单元
          business_unit,
          %% 请求编号
          request_id,
          %% 用户强评标志
          user_force_close,
          %% 交易所代码
          exchange_id,
          %% 预埋报单编号
          parked_order_id,
          %% 用户类型
          user_type,
          %% 预埋单状态
          status,
          %% 错误代码
          error_id,
          %% 错误信息
          error_msg,
          %% 互换单标志
          is_swap_order,
          %% 资金账号
          account_id,
          %% 币种代码
          currency_id,
          %% 交易编码
          client_id,
          %% 投资单元代码
          invest_unit_id,
          %% IP地址
          ipaddress,
          %% Mac地址
          mac_address
         }).

-record(cthost_ftdc_parked_order_action_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 报单操作引用
          order_action_ref,
          %% 报单引用
          order_ref,
          %% 请求编号
          request_id,
          %% 前置编号
          front_id,
          %% 会话编号
          session_id,
          %% 交易所代码
          exchange_id,
          %% 报单编号
          order_sys_id,
          %% 操作标志
          action_flag,
          %% 价格
          limit_price,
          %% 数量变化
          volume_change,
          %% 用户代码
          user_id,
          %% 合约代码
          instrument_id,
          %% 预埋撤单单编号
          parked_order_action_id,
          %% 用户类型
          user_type,
          %% 预埋撤单状态
          status,
          %% 错误代码
          error_id,
          %% 错误信息
          error_msg,
          %% 投资单元代码
          invest_unit_id,
          %% IP地址
          ipaddress,
          %% Mac地址
          mac_address
         }).

-record(cthost_ftdc_qry_parked_order_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id,
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_qry_parked_order_action_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id,
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_remove_parked_order_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 预埋报单编号
          parked_order_id
         }).

-record(cthost_ftdc_remove_parked_order_action_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 预埋撤单编号
          parked_order_action_id
         }).

-record(cthost_ftdc_investor_withdraw_algorithm_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者范围
          investor_range,
          %% 投资者代码
          investor_id,
          %% 可提资金比例
          using_ratio,
          %% 币种代码
          currency_id,
          %% 货币质押比率
          fund_mortgage_ratio
         }).

-record(cthost_ftdc_qry_investor_position_combine_detail_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 组合持仓合约编码
          comb_instrument_id
         }).

-record(cthost_ftdc_market_data_average_price_field, {
          %% 当日均价
          average_price
         }).

-record(cthost_ftdc_verify_investor_password_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 密码
          password
         }).

-record(cthost_ftdc_user_ipfield, {
          %% 经纪公司代码
          broker_id,
          %% 用户代码
          user_id,
          %% IP地址
          ipaddress,
          %% IP地址掩码
          ipmask,
          %% Mac地址
          mac_address
         }).

-record(cthost_ftdc_trading_notice_info_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 发送时间
          send_time,
          %% 消息正文
          field_content,
          %% 序列系列号
          sequence_series,
          %% 序列号
          sequence_no
         }).

-record(cthost_ftdc_trading_notice_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者范围
          investor_range,
          %% 投资者代码
          investor_id,
          %% 序列系列号
          sequence_series,
          %% 用户代码
          user_id,
          %% 发送时间
          send_time,
          %% 序列号
          sequence_no,
          %% 消息正文
          field_content
         }).

-record(cthost_ftdc_qry_trading_notice_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id
         }).

-record(cthost_ftdc_qry_err_order_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id
         }).

-record(cthost_ftdc_err_order_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id,
          %% 报单引用
          order_ref,
          %% 用户代码
          user_id,
          %% 报单价格条件
          order_price_type,
          %% 买卖方向
          direction,
          %% 组合开平标志
          comb_offset_flag,
          %% 组合投机套保标志
          comb_hedge_flag,
          %% 价格
          limit_price,
          %% 数量
          volume_total_original,
          %% 有效期类型
          time_condition,
          %% GTD日期
          gtddate,
          %% 成交量类型
          volume_condition,
          %% 最小成交量
          min_volume,
          %% 触发条件
          contingent_condition,
          %% 止损价
          stop_price,
          %% 强平原因
          force_close_reason,
          %% 自动挂起标志
          is_auto_suspend,
          %% 业务单元
          business_unit,
          %% 请求编号
          request_id,
          %% 用户强评标志
          user_force_close,
          %% 错误代码
          error_id,
          %% 错误信息
          error_msg,
          %% 互换单标志
          is_swap_order,
          %% 交易所代码
          exchange_id,
          %% 投资单元代码
          invest_unit_id,
          %% 资金账号
          account_id,
          %% 币种代码
          currency_id,
          %% 交易编码
          client_id,
          %% IP地址
          ipaddress,
          %% Mac地址
          mac_address
         }).

-record(cthost_ftdc_error_conditional_order_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id,
          %% 报单引用
          order_ref,
          %% 用户代码
          user_id,
          %% 报单价格条件
          order_price_type,
          %% 买卖方向
          direction,
          %% 组合开平标志
          comb_offset_flag,
          %% 组合投机套保标志
          comb_hedge_flag,
          %% 价格
          limit_price,
          %% 数量
          volume_total_original,
          %% 有效期类型
          time_condition,
          %% GTD日期
          gtddate,
          %% 成交量类型
          volume_condition,
          %% 最小成交量
          min_volume,
          %% 触发条件
          contingent_condition,
          %% 止损价
          stop_price,
          %% 强平原因
          force_close_reason,
          %% 自动挂起标志
          is_auto_suspend,
          %% 业务单元
          business_unit,
          %% 请求编号
          request_id,
          %% 本地报单编号
          order_local_id,
          %% 交易所代码
          exchange_id,
          %% 会员代码
          participant_id,
          %% 客户代码
          client_id,
          %% 合约在交易所的代码
          exchange_inst_id,
          %% 交易所交易员代码
          trader_id,
          %% 安装编号
          install_id,
          %% 报单提交状态
          order_submit_status,
          %% 报单提示序号
          notify_sequence,
          %% 交易日
          trading_day,
          %% 结算编号
          settlement_id,
          %% 报单编号
          order_sys_id,
          %% 报单来源
          order_source,
          %% 报单状态
          order_status,
          %% 报单类型
          order_type,
          %% 今成交数量
          volume_traded,
          %% 剩余数量
          volume_total,
          %% 报单日期
          insert_date,
          %% 委托时间
          insert_time,
          %% 激活时间
          active_time,
          %% 挂起时间
          suspend_time,
          %% 最后修改时间
          update_time,
          %% 撤销时间
          cancel_time,
          %% 最后修改交易所交易员代码
          active_trader_id,
          %% 结算会员编号
          clearing_part_id,
          %% 序号
          sequence_no,
          %% 前置编号
          front_id,
          %% 会话编号
          session_id,
          %% 用户端产品信息
          user_product_info,
          %% 状态信息
          status_msg,
          %% 用户强评标志
          user_force_close,
          %% 操作用户代码
          active_user_id,
          %% 经纪公司报单编号
          broker_order_seq,
          %% 相关报单
          relative_order_sys_id,
          %% 郑商所成交数量
          zcetotal_traded_volume,
          %% 错误代码
          error_id,
          %% 错误信息
          error_msg,
          %% 互换单标志
          is_swap_order,
          %% 营业部编号
          branch_id,
          %% 投资单元代码
          invest_unit_id,
          %% 资金账号
          account_id,
          %% 币种代码
          currency_id,
          %% IP地址
          ipaddress,
          %% Mac地址
          mac_address
         }).

-record(cthost_ftdc_qry_err_order_action_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id
         }).

-record(cthost_ftdc_err_order_action_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 报单操作引用
          order_action_ref,
          %% 报单引用
          order_ref,
          %% 请求编号
          request_id,
          %% 前置编号
          front_id,
          %% 会话编号
          session_id,
          %% 交易所代码
          exchange_id,
          %% 报单编号
          order_sys_id,
          %% 操作标志
          action_flag,
          %% 价格
          limit_price,
          %% 数量变化
          volume_change,
          %% 操作日期
          action_date,
          %% 操作时间
          action_time,
          %% 交易所交易员代码
          trader_id,
          %% 安装编号
          install_id,
          %% 本地报单编号
          order_local_id,
          %% 操作本地编号
          action_local_id,
          %% 会员代码
          participant_id,
          %% 客户代码
          client_id,
          %% 业务单元
          business_unit,
          %% 报单操作状态
          order_action_status,
          %% 用户代码
          user_id,
          %% 状态信息
          status_msg,
          %% 合约代码
          instrument_id,
          %% 营业部编号
          branch_id,
          %% 投资单元代码
          invest_unit_id,
          %% IP地址
          ipaddress,
          %% Mac地址
          mac_address,
          %% 错误代码
          error_id,
          %% 错误信息
          error_msg
         }).

-record(cthost_ftdc_qry_exchange_sequence_field, {
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_exchange_sequence_field, {
          %% 交易所代码
          exchange_id,
          %% 序号
          sequence_no,
          %% 合约交易状态
          market_status
         }).

-record(cthost_ftdc_query_max_order_volume_with_price_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 合约代码
          instrument_id,
          %% 买卖方向
          direction,
          %% 开平标志
          offset_flag,
          %% 投机套保标志
          hedge_flag,
          %% 最大允许报单数量
          max_volume,
          %% 报单价格
          price,
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_qry_broker_trading_params_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 币种代码
          currency_id
         }).

-record(cthost_ftdc_broker_trading_params_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 保证金价格类型
          margin_price_type,
          %% 盈亏算法
          algorithm,
          %% 可用是否包含平仓盈利
          avail_include_close_profit,
          %% 币种代码
          currency_id,
          %% 期权权利金价格类型
          option_royalty_price_type
         }).

-record(cthost_ftdc_qry_broker_trading_algos_field, {
          %% 经纪公司代码
          broker_id,
          %% 交易所代码
          exchange_id,
          %% 合约代码
          instrument_id
         }).

-record(cthost_ftdc_broker_trading_algos_field, {
          %% 经纪公司代码
          broker_id,
          %% 交易所代码
          exchange_id,
          %% 合约代码
          instrument_id,
          %% 持仓处理算法编号
          handle_position_algo_id,
          %% 寻找保证金率算法编号
          find_margin_rate_algo_id,
          %% 资金处理算法编号
          handle_trading_account_algo_id
         }).

-record(cthost_ftdc_query_broker_deposit_field, {
          %% 经纪公司代码
          broker_id,
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_broker_deposit_field, {
          %% 交易日期
          trading_day,
          %% 经纪公司代码
          broker_id,
          %% 会员代码
          participant_id,
          %% 交易所代码
          exchange_id,
          %% 上次结算准备金
          pre_balance,
          %% 当前保证金总额
          curr_margin,
          %% 平仓盈亏
          close_profit,
          %% 期货结算准备金
          balance,
          %% 入金金额
          deposit,
          %% 出金金额
          withdraw,
          %% 可提资金
          available,
          %% 基本准备金
          reserve,
          %% 冻结的保证金
          frozen_margin
         }).

-record(cthost_ftdc_qry_cfmmcbroker_key_field, {
          %% 经纪公司代码
          broker_id
         }).

-record(cthost_ftdc_cfmmcbroker_key_field, {
          %% 经纪公司代码
          broker_id,
          %% 经纪公司统一编码
          participant_id,
          %% 密钥生成日期
          create_date,
          %% 密钥生成时间
          create_time,
          %% 密钥编号
          key_id,
          %% 动态密钥
          current_key,
          %% 动态密钥类型
          key_kind
         }).

-record(cthost_ftdc_cfmmctrading_account_key_field, {
          %% 经纪公司代码
          broker_id,
          %% 经纪公司统一编码
          participant_id,
          %% 投资者帐号
          account_id,
          %% 密钥编号
          key_id,
          %% 动态密钥
          current_key
         }).

-record(cthost_ftdc_qry_cfmmctrading_account_key_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id
         }).

-record(cthost_ftdc_broker_user_otpparam_field, {
          %% 经纪公司代码
          broker_id,
          %% 用户代码
          user_id,
          %% 动态令牌提供商
          otpvendors_id,
          %% 动态令牌序列号
          serial_number,
          %% 令牌密钥
          auth_key,
          %% 漂移值
          last_drift,
          %% 成功值
          last_success,
          %% 动态令牌类型
          otptype
         }).

-record(cthost_ftdc_manual_sync_broker_user_otpfield, {
          %% 经纪公司代码
          broker_id,
          %% 用户代码
          user_id,
          %% 动态令牌类型
          otptype,
          %% 第一个动态密码
          first_otp,
          %% 第二个动态密码
          second_otp
         }).

-record(cthost_ftdc_comm_rate_model_field, {
          %% 经纪公司代码
          broker_id,
          %% 手续费率模板代码
          comm_model_id,
          %% 模板名称
          comm_model_name
         }).

-record(cthost_ftdc_qry_comm_rate_model_field, {
          %% 经纪公司代码
          broker_id,
          %% 手续费率模板代码
          comm_model_id
         }).

-record(cthost_ftdc_margin_model_field, {
          %% 经纪公司代码
          broker_id,
          %% 保证金率模板代码
          margin_model_id,
          %% 模板名称
          margin_model_name
         }).

-record(cthost_ftdc_qry_margin_model_field, {
          %% 经纪公司代码
          broker_id,
          %% 保证金率模板代码
          margin_model_id
         }).

-record(cthost_ftdc_ewarrant_offset_field, {
          %% 交易日期
          trading_day,
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 交易所代码
          exchange_id,
          %% 合约代码
          instrument_id,
          %% 买卖方向
          direction,
          %% 投机套保标志
          hedge_flag,
          %% 数量
          volume
         }).

-record(cthost_ftdc_qry_ewarrant_offset_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 交易所代码
          exchange_id,
          %% 合约代码
          instrument_id
         }).

-record(cthost_ftdc_qry_investor_product_group_margin_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 品种/跨品种标示
          product_group_id,
          %% 投机套保标志
          hedge_flag
         }).

-record(cthost_ftdc_investor_product_group_margin_field, {
          %% 品种/跨品种标示
          product_group_id,
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 交易日
          trading_day,
          %% 结算编号
          settlement_id,
          %% 冻结的保证金
          frozen_margin,
          %% 多头冻结的保证金
          long_frozen_margin,
          %% 空头冻结的保证金
          short_frozen_margin,
          %% 占用的保证金
          use_margin,
          %% 多头保证金
          long_use_margin,
          %% 空头保证金
          short_use_margin,
          %% 交易所保证金
          exch_margin,
          %% 交易所多头保证金
          long_exch_margin,
          %% 交易所空头保证金
          short_exch_margin,
          %% 平仓盈亏
          close_profit,
          %% 冻结的手续费
          frozen_commission,
          %% 手续费
          commission,
          %% 冻结的资金
          frozen_cash,
          %% 资金差额
          cash_in,
          %% 持仓盈亏
          position_profit,
          %% 折抵总金额
          offset_amount,
          %% 多头折抵总金额
          long_offset_amount,
          %% 空头折抵总金额
          short_offset_amount,
          %% 交易所折抵总金额
          exch_offset_amount,
          %% 交易所多头折抵总金额
          long_exch_offset_amount,
          %% 交易所空头折抵总金额
          short_exch_offset_amount,
          %% 投机套保标志
          hedge_flag
         }).

-record(cthost_ftdc_query_cfmmctrading_account_token_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id
         }).

-record(cthost_ftdc_cfmmctrading_account_token_field, {
          %% 经纪公司代码
          broker_id,
          %% 经纪公司统一编码
          participant_id,
          %% 投资者帐号
          account_id,
          %% 密钥编号
          key_id,
          %% 动态令牌
          token
         }).

-record(cthost_ftdc_instruction_right_field, {
          %% 经纪公司代码
          broker_id,
          %% 交易所代码
          exchange_id,
          %% 投资者代码
          investor_id,
          %% 指令权限类型
          instruction_right,
          %% 是否禁止
          is_forbidden
         }).

-record(cthost_ftdc_qry_product_group_field, {
          %% 产品代码
          product_id,
          %% 交易所代码
          exchange_id
         }).

-record(cthost_ftdc_product_group_field, {
          %% 产品代码
          product_id,
          %% 交易所代码
          exchange_id,
          %% 产品组代码
          product_group_id
         }).

-record(cthost_ftdc_bulletin_field, {
          %% 交易所代码
          exchange_id,
          %% 交易日
          trading_day,
          %% 公告编号
          bulletin_id,
          %% 序列号
          sequence_no,
          %% 公告类型
          news_type,
          %% 紧急程度
          news_urgency,
          %% 发送时间
          send_time,
          %% 消息摘要
          abstract,
          %% 消息来源
          come_from,
          %% 消息正文
          content,
          %% WEB地址
          urllink,
          %% 市场代码
          market_id
         }).

-record(cthost_ftdc_qry_bulletin_field, {
          %% 交易所代码
          exchange_id,
          %% 公告编号
          bulletin_id,
          %% 序列号
          sequence_no,
          %% 公告类型
          news_type,
          %% 紧急程度
          news_urgency
         }).

-record(cthost_ftdc_req_open_account_field, {
          %% 业务功能码
          trade_code,
          %% 银行代码
          bank_id,
          %% 银行分支机构代码
          bank_branch_id,
          %% 期商代码
          broker_id,
          %% 期商分支机构代码
          broker_branch_id,
          %% 交易日期
          trade_date,
          %% 交易时间
          trade_time,
          %% 银行流水号
          bank_serial,
          %% 交易系统日期
          trading_day,
          %% 银期平台消息流水号
          plate_serial,
          %% 最后分片标志
          last_fragment,
          %% 会话号
          session_id,
          %% 客户姓名
          customer_name,
          %% 证件类型
          id_card_type,
          %% 证件号码
          identified_card_no,
          %% 性别
          gender,
          %% 国家代码
          country_code,
          %% 客户类型
          cust_type,
          %% 地址
          address,
          %% 邮编
          zip_code,
          %% 电话号码
          telephone,
          %% 手机
          mobile_phone,
          %% 传真
          fax,
          %% 电子邮件
          email,
          %% 资金账户状态
          money_account_status,
          %% 银行帐号
          bank_account,
          %% 银行密码
          bank_pass_word,
          %% 投资者帐号
          account_id,
          %% 期货密码
          password,
          %% 安装编号
          install_id,
          %% 验证客户证件号码标志
          verify_cert_no_flag,
          %% 币种代码
          currency_id,
          %% 汇钞标志
          cash_exchange_code,
          %% 摘要
          digest,
          %% 银行帐号类型
          bank_acc_type,
          %% 渠道标志
          device_id,
          %% 期货单位帐号类型
          bank_secu_acc_type,
          %% 期货公司银行编码
          broker_idby_bank,
          %% 期货单位帐号
          bank_secu_acc,
          %% 银行密码标志
          bank_pwd_flag,
          %% 期货资金密码核对标志
          secu_pwd_flag,
          %% 交易柜员
          oper_no,
          %% 交易ID
          tid,
          %% 用户标识
          user_id
         }).

-record(cthost_ftdc_req_cancel_account_field, {
          %% 业务功能码
          trade_code,
          %% 银行代码
          bank_id,
          %% 银行分支机构代码
          bank_branch_id,
          %% 期商代码
          broker_id,
          %% 期商分支机构代码
          broker_branch_id,
          %% 交易日期
          trade_date,
          %% 交易时间
          trade_time,
          %% 银行流水号
          bank_serial,
          %% 交易系统日期
          trading_day,
          %% 银期平台消息流水号
          plate_serial,
          %% 最后分片标志
          last_fragment,
          %% 会话号
          session_id,
          %% 客户姓名
          customer_name,
          %% 证件类型
          id_card_type,
          %% 证件号码
          identified_card_no,
          %% 性别
          gender,
          %% 国家代码
          country_code,
          %% 客户类型
          cust_type,
          %% 地址
          address,
          %% 邮编
          zip_code,
          %% 电话号码
          telephone,
          %% 手机
          mobile_phone,
          %% 传真
          fax,
          %% 电子邮件
          email,
          %% 资金账户状态
          money_account_status,
          %% 银行帐号
          bank_account,
          %% 银行密码
          bank_pass_word,
          %% 投资者帐号
          account_id,
          %% 期货密码
          password,
          %% 安装编号
          install_id,
          %% 验证客户证件号码标志
          verify_cert_no_flag,
          %% 币种代码
          currency_id,
          %% 汇钞标志
          cash_exchange_code,
          %% 摘要
          digest,
          %% 银行帐号类型
          bank_acc_type,
          %% 渠道标志
          device_id,
          %% 期货单位帐号类型
          bank_secu_acc_type,
          %% 期货公司银行编码
          broker_idby_bank,
          %% 期货单位帐号
          bank_secu_acc,
          %% 银行密码标志
          bank_pwd_flag,
          %% 期货资金密码核对标志
          secu_pwd_flag,
          %% 交易柜员
          oper_no,
          %% 交易ID
          tid,
          %% 用户标识
          user_id
         }).

-record(cthost_ftdc_req_change_account_field, {
          %% 业务功能码
          trade_code,
          %% 银行代码
          bank_id,
          %% 银行分支机构代码
          bank_branch_id,
          %% 期商代码
          broker_id,
          %% 期商分支机构代码
          broker_branch_id,
          %% 交易日期
          trade_date,
          %% 交易时间
          trade_time,
          %% 银行流水号
          bank_serial,
          %% 交易系统日期
          trading_day,
          %% 银期平台消息流水号
          plate_serial,
          %% 最后分片标志
          last_fragment,
          %% 会话号
          session_id,
          %% 客户姓名
          customer_name,
          %% 证件类型
          id_card_type,
          %% 证件号码
          identified_card_no,
          %% 性别
          gender,
          %% 国家代码
          country_code,
          %% 客户类型
          cust_type,
          %% 地址
          address,
          %% 邮编
          zip_code,
          %% 电话号码
          telephone,
          %% 手机
          mobile_phone,
          %% 传真
          fax,
          %% 电子邮件
          email,
          %% 资金账户状态
          money_account_status,
          %% 银行帐号
          bank_account,
          %% 银行密码
          bank_pass_word,
          %% 新银行帐号
          new_bank_account,
          %% 新银行密码
          new_bank_pass_word,
          %% 投资者帐号
          account_id,
          %% 期货密码
          password,
          %% 银行帐号类型
          bank_acc_type,
          %% 安装编号
          install_id,
          %% 验证客户证件号码标志
          verify_cert_no_flag,
          %% 币种代码
          currency_id,
          %% 期货公司银行编码
          broker_idby_bank,
          %% 银行密码标志
          bank_pwd_flag,
          %% 期货资金密码核对标志
          secu_pwd_flag,
          %% 交易ID
          tid,
          %% 摘要
          digest
         }).

-record(cthost_ftdc_req_transfer_field, {
          %% 业务功能码
          trade_code,
          %% 银行代码
          bank_id,
          %% 银行分支机构代码
          bank_branch_id,
          %% 期商代码
          broker_id,
          %% 期商分支机构代码
          broker_branch_id,
          %% 交易日期
          trade_date,
          %% 交易时间
          trade_time,
          %% 银行流水号
          bank_serial,
          %% 交易系统日期
          trading_day,
          %% 银期平台消息流水号
          plate_serial,
          %% 最后分片标志
          last_fragment,
          %% 会话号
          session_id,
          %% 客户姓名
          customer_name,
          %% 证件类型
          id_card_type,
          %% 证件号码
          identified_card_no,
          %% 客户类型
          cust_type,
          %% 银行帐号
          bank_account,
          %% 银行密码
          bank_pass_word,
          %% 投资者帐号
          account_id,
          %% 期货密码
          password,
          %% 安装编号
          install_id,
          %% 期货公司流水号
          future_serial,
          %% 用户标识
          user_id,
          %% 验证客户证件号码标志
          verify_cert_no_flag,
          %% 币种代码
          currency_id,
          %% 转帐金额
          trade_amount,
          %% 期货可取金额
          future_fetch_amount,
          %% 费用支付标志
          fee_pay_flag,
          %% 应收客户费用
          cust_fee,
          %% 应收期货公司费用
          broker_fee,
          %% 发送方给接收方的消息
          message,
          %% 摘要
          digest,
          %% 银行帐号类型
          bank_acc_type,
          %% 渠道标志
          device_id,
          %% 期货单位帐号类型
          bank_secu_acc_type,
          %% 期货公司银行编码
          broker_idby_bank,
          %% 期货单位帐号
          bank_secu_acc,
          %% 银行密码标志
          bank_pwd_flag,
          %% 期货资金密码核对标志
          secu_pwd_flag,
          %% 交易柜员
          oper_no,
          %% 请求编号
          request_id,
          %% 交易ID
          tid,
          %% 转账交易状态
          transfer_status
         }).

-record(cthost_ftdc_rsp_transfer_field, {
          %% 业务功能码
          trade_code,
          %% 银行代码
          bank_id,
          %% 银行分支机构代码
          bank_branch_id,
          %% 期商代码
          broker_id,
          %% 期商分支机构代码
          broker_branch_id,
          %% 交易日期
          trade_date,
          %% 交易时间
          trade_time,
          %% 银行流水号
          bank_serial,
          %% 交易系统日期
          trading_day,
          %% 银期平台消息流水号
          plate_serial,
          %% 最后分片标志
          last_fragment,
          %% 会话号
          session_id,
          %% 客户姓名
          customer_name,
          %% 证件类型
          id_card_type,
          %% 证件号码
          identified_card_no,
          %% 客户类型
          cust_type,
          %% 银行帐号
          bank_account,
          %% 银行密码
          bank_pass_word,
          %% 投资者帐号
          account_id,
          %% 期货密码
          password,
          %% 安装编号
          install_id,
          %% 期货公司流水号
          future_serial,
          %% 用户标识
          user_id,
          %% 验证客户证件号码标志
          verify_cert_no_flag,
          %% 币种代码
          currency_id,
          %% 转帐金额
          trade_amount,
          %% 期货可取金额
          future_fetch_amount,
          %% 费用支付标志
          fee_pay_flag,
          %% 应收客户费用
          cust_fee,
          %% 应收期货公司费用
          broker_fee,
          %% 发送方给接收方的消息
          message,
          %% 摘要
          digest,
          %% 银行帐号类型
          bank_acc_type,
          %% 渠道标志
          device_id,
          %% 期货单位帐号类型
          bank_secu_acc_type,
          %% 期货公司银行编码
          broker_idby_bank,
          %% 期货单位帐号
          bank_secu_acc,
          %% 银行密码标志
          bank_pwd_flag,
          %% 期货资金密码核对标志
          secu_pwd_flag,
          %% 交易柜员
          oper_no,
          %% 请求编号
          request_id,
          %% 交易ID
          tid,
          %% 转账交易状态
          transfer_status,
          %% 错误代码
          error_id,
          %% 错误信息
          error_msg
         }).

-record(cthost_ftdc_req_repeal_field, {
          %% 冲正时间间隔
          repeal_time_interval,
          %% 已经冲正次数
          repealed_times,
          %% 银行冲正标志
          bank_repeal_flag,
          %% 期商冲正标志
          broker_repeal_flag,
          %% 被冲正平台流水号
          plate_repeal_serial,
          %% 被冲正银行流水号
          bank_repeal_serial,
          %% 被冲正期货流水号
          future_repeal_serial,
          %% 业务功能码
          trade_code,
          %% 银行代码
          bank_id,
          %% 银行分支机构代码
          bank_branch_id,
          %% 期商代码
          broker_id,
          %% 期商分支机构代码
          broker_branch_id,
          %% 交易日期
          trade_date,
          %% 交易时间
          trade_time,
          %% 银行流水号
          bank_serial,
          %% 交易系统日期
          trading_day,
          %% 银期平台消息流水号
          plate_serial,
          %% 最后分片标志
          last_fragment,
          %% 会话号
          session_id,
          %% 客户姓名
          customer_name,
          %% 证件类型
          id_card_type,
          %% 证件号码
          identified_card_no,
          %% 客户类型
          cust_type,
          %% 银行帐号
          bank_account,
          %% 银行密码
          bank_pass_word,
          %% 投资者帐号
          account_id,
          %% 期货密码
          password,
          %% 安装编号
          install_id,
          %% 期货公司流水号
          future_serial,
          %% 用户标识
          user_id,
          %% 验证客户证件号码标志
          verify_cert_no_flag,
          %% 币种代码
          currency_id,
          %% 转帐金额
          trade_amount,
          %% 期货可取金额
          future_fetch_amount,
          %% 费用支付标志
          fee_pay_flag,
          %% 应收客户费用
          cust_fee,
          %% 应收期货公司费用
          broker_fee,
          %% 发送方给接收方的消息
          message,
          %% 摘要
          digest,
          %% 银行帐号类型
          bank_acc_type,
          %% 渠道标志
          device_id,
          %% 期货单位帐号类型
          bank_secu_acc_type,
          %% 期货公司银行编码
          broker_idby_bank,
          %% 期货单位帐号
          bank_secu_acc,
          %% 银行密码标志
          bank_pwd_flag,
          %% 期货资金密码核对标志
          secu_pwd_flag,
          %% 交易柜员
          oper_no,
          %% 请求编号
          request_id,
          %% 交易ID
          tid,
          %% 转账交易状态
          transfer_status
         }).

-record(cthost_ftdc_rsp_repeal_field, {
          %% 冲正时间间隔
          repeal_time_interval,
          %% 已经冲正次数
          repealed_times,
          %% 银行冲正标志
          bank_repeal_flag,
          %% 期商冲正标志
          broker_repeal_flag,
          %% 被冲正平台流水号
          plate_repeal_serial,
          %% 被冲正银行流水号
          bank_repeal_serial,
          %% 被冲正期货流水号
          future_repeal_serial,
          %% 业务功能码
          trade_code,
          %% 银行代码
          bank_id,
          %% 银行分支机构代码
          bank_branch_id,
          %% 期商代码
          broker_id,
          %% 期商分支机构代码
          broker_branch_id,
          %% 交易日期
          trade_date,
          %% 交易时间
          trade_time,
          %% 银行流水号
          bank_serial,
          %% 交易系统日期
          trading_day,
          %% 银期平台消息流水号
          plate_serial,
          %% 最后分片标志
          last_fragment,
          %% 会话号
          session_id,
          %% 客户姓名
          customer_name,
          %% 证件类型
          id_card_type,
          %% 证件号码
          identified_card_no,
          %% 客户类型
          cust_type,
          %% 银行帐号
          bank_account,
          %% 银行密码
          bank_pass_word,
          %% 投资者帐号
          account_id,
          %% 期货密码
          password,
          %% 安装编号
          install_id,
          %% 期货公司流水号
          future_serial,
          %% 用户标识
          user_id,
          %% 验证客户证件号码标志
          verify_cert_no_flag,
          %% 币种代码
          currency_id,
          %% 转帐金额
          trade_amount,
          %% 期货可取金额
          future_fetch_amount,
          %% 费用支付标志
          fee_pay_flag,
          %% 应收客户费用
          cust_fee,
          %% 应收期货公司费用
          broker_fee,
          %% 发送方给接收方的消息
          message,
          %% 摘要
          digest,
          %% 银行帐号类型
          bank_acc_type,
          %% 渠道标志
          device_id,
          %% 期货单位帐号类型
          bank_secu_acc_type,
          %% 期货公司银行编码
          broker_idby_bank,
          %% 期货单位帐号
          bank_secu_acc,
          %% 银行密码标志
          bank_pwd_flag,
          %% 期货资金密码核对标志
          secu_pwd_flag,
          %% 交易柜员
          oper_no,
          %% 请求编号
          request_id,
          %% 交易ID
          tid,
          %% 转账交易状态
          transfer_status,
          %% 错误代码
          error_id,
          %% 错误信息
          error_msg
         }).

-record(cthost_ftdc_req_query_account_field, {
          %% 业务功能码
          trade_code,
          %% 银行代码
          bank_id,
          %% 银行分支机构代码
          bank_branch_id,
          %% 期商代码
          broker_id,
          %% 期商分支机构代码
          broker_branch_id,
          %% 交易日期
          trade_date,
          %% 交易时间
          trade_time,
          %% 银行流水号
          bank_serial,
          %% 交易系统日期
          trading_day,
          %% 银期平台消息流水号
          plate_serial,
          %% 最后分片标志
          last_fragment,
          %% 会话号
          session_id,
          %% 客户姓名
          customer_name,
          %% 证件类型
          id_card_type,
          %% 证件号码
          identified_card_no,
          %% 客户类型
          cust_type,
          %% 银行帐号
          bank_account,
          %% 银行密码
          bank_pass_word,
          %% 投资者帐号
          account_id,
          %% 期货密码
          password,
          %% 期货公司流水号
          future_serial,
          %% 安装编号
          install_id,
          %% 用户标识
          user_id,
          %% 验证客户证件号码标志
          verify_cert_no_flag,
          %% 币种代码
          currency_id,
          %% 摘要
          digest,
          %% 银行帐号类型
          bank_acc_type,
          %% 渠道标志
          device_id,
          %% 期货单位帐号类型
          bank_secu_acc_type,
          %% 期货公司银行编码
          broker_idby_bank,
          %% 期货单位帐号
          bank_secu_acc,
          %% 银行密码标志
          bank_pwd_flag,
          %% 期货资金密码核对标志
          secu_pwd_flag,
          %% 交易柜员
          oper_no,
          %% 请求编号
          request_id,
          %% 交易ID
          tid
         }).

-record(cthost_ftdc_rsp_query_account_field, {
          %% 业务功能码
          trade_code,
          %% 银行代码
          bank_id,
          %% 银行分支机构代码
          bank_branch_id,
          %% 期商代码
          broker_id,
          %% 期商分支机构代码
          broker_branch_id,
          %% 交易日期
          trade_date,
          %% 交易时间
          trade_time,
          %% 银行流水号
          bank_serial,
          %% 交易系统日期
          trading_day,
          %% 银期平台消息流水号
          plate_serial,
          %% 最后分片标志
          last_fragment,
          %% 会话号
          session_id,
          %% 客户姓名
          customer_name,
          %% 证件类型
          id_card_type,
          %% 证件号码
          identified_card_no,
          %% 客户类型
          cust_type,
          %% 银行帐号
          bank_account,
          %% 银行密码
          bank_pass_word,
          %% 投资者帐号
          account_id,
          %% 期货密码
          password,
          %% 期货公司流水号
          future_serial,
          %% 安装编号
          install_id,
          %% 用户标识
          user_id,
          %% 验证客户证件号码标志
          verify_cert_no_flag,
          %% 币种代码
          currency_id,
          %% 摘要
          digest,
          %% 银行帐号类型
          bank_acc_type,
          %% 渠道标志
          device_id,
          %% 期货单位帐号类型
          bank_secu_acc_type,
          %% 期货公司银行编码
          broker_idby_bank,
          %% 期货单位帐号
          bank_secu_acc,
          %% 银行密码标志
          bank_pwd_flag,
          %% 期货资金密码核对标志
          secu_pwd_flag,
          %% 交易柜员
          oper_no,
          %% 请求编号
          request_id,
          %% 交易ID
          tid,
          %% 银行可用金额
          bank_use_amount,
          %% 银行可取金额
          bank_fetch_amount
         }).

-record(cthost_ftdc_future_sign_iofield, {
          %% 业务功能码
          trade_code,
          %% 银行代码
          bank_id,
          %% 银行分支机构代码
          bank_branch_id,
          %% 期商代码
          broker_id,
          %% 期商分支机构代码
          broker_branch_id,
          %% 交易日期
          trade_date,
          %% 交易时间
          trade_time,
          %% 银行流水号
          bank_serial,
          %% 交易系统日期
          trading_day,
          %% 银期平台消息流水号
          plate_serial,
          %% 最后分片标志
          last_fragment,
          %% 会话号
          session_id,
          %% 安装编号
          install_id,
          %% 用户标识
          user_id,
          %% 摘要
          digest,
          %% 币种代码
          currency_id,
          %% 渠道标志
          device_id,
          %% 期货公司银行编码
          broker_idby_bank,
          %% 交易柜员
          oper_no,
          %% 请求编号
          request_id,
          %% 交易ID
          tid
         }).

-record(cthost_ftdc_rsp_future_sign_in_field, {
          %% 业务功能码
          trade_code,
          %% 银行代码
          bank_id,
          %% 银行分支机构代码
          bank_branch_id,
          %% 期商代码
          broker_id,
          %% 期商分支机构代码
          broker_branch_id,
          %% 交易日期
          trade_date,
          %% 交易时间
          trade_time,
          %% 银行流水号
          bank_serial,
          %% 交易系统日期
          trading_day,
          %% 银期平台消息流水号
          plate_serial,
          %% 最后分片标志
          last_fragment,
          %% 会话号
          session_id,
          %% 安装编号
          install_id,
          %% 用户标识
          user_id,
          %% 摘要
          digest,
          %% 币种代码
          currency_id,
          %% 渠道标志
          device_id,
          %% 期货公司银行编码
          broker_idby_bank,
          %% 交易柜员
          oper_no,
          %% 请求编号
          request_id,
          %% 交易ID
          tid,
          %% 错误代码
          error_id,
          %% 错误信息
          error_msg,
          %% PIN密钥
          pin_key,
          %% MAC密钥
          mac_key
         }).

-record(cthost_ftdc_req_future_sign_out_field, {
          %% 业务功能码
          trade_code,
          %% 银行代码
          bank_id,
          %% 银行分支机构代码
          bank_branch_id,
          %% 期商代码
          broker_id,
          %% 期商分支机构代码
          broker_branch_id,
          %% 交易日期
          trade_date,
          %% 交易时间
          trade_time,
          %% 银行流水号
          bank_serial,
          %% 交易系统日期
          trading_day,
          %% 银期平台消息流水号
          plate_serial,
          %% 最后分片标志
          last_fragment,
          %% 会话号
          session_id,
          %% 安装编号
          install_id,
          %% 用户标识
          user_id,
          %% 摘要
          digest,
          %% 币种代码
          currency_id,
          %% 渠道标志
          device_id,
          %% 期货公司银行编码
          broker_idby_bank,
          %% 交易柜员
          oper_no,
          %% 请求编号
          request_id,
          %% 交易ID
          tid
         }).

-record(cthost_ftdc_rsp_future_sign_out_field, {
          %% 业务功能码
          trade_code,
          %% 银行代码
          bank_id,
          %% 银行分支机构代码
          bank_branch_id,
          %% 期商代码
          broker_id,
          %% 期商分支机构代码
          broker_branch_id,
          %% 交易日期
          trade_date,
          %% 交易时间
          trade_time,
          %% 银行流水号
          bank_serial,
          %% 交易系统日期
          trading_day,
          %% 银期平台消息流水号
          plate_serial,
          %% 最后分片标志
          last_fragment,
          %% 会话号
          session_id,
          %% 安装编号
          install_id,
          %% 用户标识
          user_id,
          %% 摘要
          digest,
          %% 币种代码
          currency_id,
          %% 渠道标志
          device_id,
          %% 期货公司银行编码
          broker_idby_bank,
          %% 交易柜员
          oper_no,
          %% 请求编号
          request_id,
          %% 交易ID
          tid,
          %% 错误代码
          error_id,
          %% 错误信息
          error_msg
         }).

-record(cthost_ftdc_req_query_trade_result_by_serial_field, {
          %% 业务功能码
          trade_code,
          %% 银行代码
          bank_id,
          %% 银行分支机构代码
          bank_branch_id,
          %% 期商代码
          broker_id,
          %% 期商分支机构代码
          broker_branch_id,
          %% 交易日期
          trade_date,
          %% 交易时间
          trade_time,
          %% 银行流水号
          bank_serial,
          %% 交易系统日期
          trading_day,
          %% 银期平台消息流水号
          plate_serial,
          %% 最后分片标志
          last_fragment,
          %% 会话号
          session_id,
          %% 流水号
          reference,
          %% 本流水号发布者的机构类型
          refrence_issure_type,
          %% 本流水号发布者机构编码
          refrence_issure,
          %% 客户姓名
          customer_name,
          %% 证件类型
          id_card_type,
          %% 证件号码
          identified_card_no,
          %% 客户类型
          cust_type,
          %% 银行帐号
          bank_account,
          %% 银行密码
          bank_pass_word,
          %% 投资者帐号
          account_id,
          %% 期货密码
          password,
          %% 币种代码
          currency_id,
          %% 转帐金额
          trade_amount,
          %% 摘要
          digest
         }).

-record(cthost_ftdc_rsp_query_trade_result_by_serial_field, {
          %% 业务功能码
          trade_code,
          %% 银行代码
          bank_id,
          %% 银行分支机构代码
          bank_branch_id,
          %% 期商代码
          broker_id,
          %% 期商分支机构代码
          broker_branch_id,
          %% 交易日期
          trade_date,
          %% 交易时间
          trade_time,
          %% 银行流水号
          bank_serial,
          %% 交易系统日期
          trading_day,
          %% 银期平台消息流水号
          plate_serial,
          %% 最后分片标志
          last_fragment,
          %% 会话号
          session_id,
          %% 错误代码
          error_id,
          %% 错误信息
          error_msg,
          %% 流水号
          reference,
          %% 本流水号发布者的机构类型
          refrence_issure_type,
          %% 本流水号发布者机构编码
          refrence_issure,
          %% 原始返回代码
          origin_return_code,
          %% 原始返回码描述
          origin_descr_info_for_return_code,
          %% 银行帐号
          bank_account,
          %% 银行密码
          bank_pass_word,
          %% 投资者帐号
          account_id,
          %% 期货密码
          password,
          %% 币种代码
          currency_id,
          %% 转帐金额
          trade_amount,
          %% 摘要
          digest
         }).

-record(cthost_ftdc_req_day_end_file_ready_field, {
          %% 业务功能码
          trade_code,
          %% 银行代码
          bank_id,
          %% 银行分支机构代码
          bank_branch_id,
          %% 期商代码
          broker_id,
          %% 期商分支机构代码
          broker_branch_id,
          %% 交易日期
          trade_date,
          %% 交易时间
          trade_time,
          %% 银行流水号
          bank_serial,
          %% 交易系统日期
          trading_day,
          %% 银期平台消息流水号
          plate_serial,
          %% 最后分片标志
          last_fragment,
          %% 会话号
          session_id,
          %% 文件业务功能
          file_business_code,
          %% 摘要
          digest
         }).

-record(cthost_ftdc_return_result_field, {
          %% 返回代码
          return_code,
          %% 返回码描述
          descr_info_for_return_code
         }).

-record(cthost_ftdc_verify_future_password_field, {
          %% 业务功能码
          trade_code,
          %% 银行代码
          bank_id,
          %% 银行分支机构代码
          bank_branch_id,
          %% 期商代码
          broker_id,
          %% 期商分支机构代码
          broker_branch_id,
          %% 交易日期
          trade_date,
          %% 交易时间
          trade_time,
          %% 银行流水号
          bank_serial,
          %% 交易系统日期
          trading_day,
          %% 银期平台消息流水号
          plate_serial,
          %% 最后分片标志
          last_fragment,
          %% 会话号
          session_id,
          %% 投资者帐号
          account_id,
          %% 期货密码
          password,
          %% 银行帐号
          bank_account,
          %% 银行密码
          bank_pass_word,
          %% 安装编号
          install_id,
          %% 交易ID
          tid,
          %% 币种代码
          currency_id
         }).

-record(cthost_ftdc_verify_cust_info_field, {
          %% 客户姓名
          customer_name,
          %% 证件类型
          id_card_type,
          %% 证件号码
          identified_card_no,
          %% 客户类型
          cust_type
         }).

-record(cthost_ftdc_verify_future_password_and_cust_info_field, {
          %% 客户姓名
          customer_name,
          %% 证件类型
          id_card_type,
          %% 证件号码
          identified_card_no,
          %% 客户类型
          cust_type,
          %% 投资者帐号
          account_id,
          %% 期货密码
          password,
          %% 币种代码
          currency_id
         }).

-record(cthost_ftdc_deposit_result_inform_field, {
          %% 出入金流水号，该流水号为银期报盘返回的流水号
          deposit_seq_no,
          %% 经纪公司代码
          broker_id,
          %% 投资者代码
          investor_id,
          %% 入金金额
          deposit,
          %% 请求编号
          request_id,
          %% 返回代码
          return_code,
          %% 返回码描述
          descr_info_for_return_code
         }).

-record(cthost_ftdc_req_sync_key_field, {
          %% 业务功能码
          trade_code,
          %% 银行代码
          bank_id,
          %% 银行分支机构代码
          bank_branch_id,
          %% 期商代码
          broker_id,
          %% 期商分支机构代码
          broker_branch_id,
          %% 交易日期
          trade_date,
          %% 交易时间
          trade_time,
          %% 银行流水号
          bank_serial,
          %% 交易系统日期
          trading_day,
          %% 银期平台消息流水号
          plate_serial,
          %% 最后分片标志
          last_fragment,
          %% 会话号
          session_id,
          %% 安装编号
          install_id,
          %% 用户标识
          user_id,
          %% 交易核心给银期报盘的消息
          message,
          %% 渠道标志
          device_id,
          %% 期货公司银行编码
          broker_idby_bank,
          %% 交易柜员
          oper_no,
          %% 请求编号
          request_id,
          %% 交易ID
          tid
         }).

-record(cthost_ftdc_rsp_sync_key_field, {
          %% 业务功能码
          trade_code,
          %% 银行代码
          bank_id,
          %% 银行分支机构代码
          bank_branch_id,
          %% 期商代码
          broker_id,
          %% 期商分支机构代码
          broker_branch_id,
          %% 交易日期
          trade_date,
          %% 交易时间
          trade_time,
          %% 银行流水号
          bank_serial,
          %% 交易系统日期
          trading_day,
          %% 银期平台消息流水号
          plate_serial,
          %% 最后分片标志
          last_fragment,
          %% 会话号
          session_id,
          %% 安装编号
          install_id,
          %% 用户标识
          user_id,
          %% 交易核心给银期报盘的消息
          message,
          %% 渠道标志
          device_id,
          %% 期货公司银行编码
          broker_idby_bank,
          %% 交易柜员
          oper_no,
          %% 请求编号
          request_id,
          %% 交易ID
          tid,
          %% 错误代码
          error_id,
          %% 错误信息
          error_msg
         }).

-record(cthost_ftdc_notify_query_account_field, {
          %% 业务功能码
          trade_code,
          %% 银行代码
          bank_id,
          %% 银行分支机构代码
          bank_branch_id,
          %% 期商代码
          broker_id,
          %% 期商分支机构代码
          broker_branch_id,
          %% 交易日期
          trade_date,
          %% 交易时间
          trade_time,
          %% 银行流水号
          bank_serial,
          %% 交易系统日期
          trading_day,
          %% 银期平台消息流水号
          plate_serial,
          %% 最后分片标志
          last_fragment,
          %% 会话号
          session_id,
          %% 客户姓名
          customer_name,
          %% 证件类型
          id_card_type,
          %% 证件号码
          identified_card_no,
          %% 客户类型
          cust_type,
          %% 银行帐号
          bank_account,
          %% 银行密码
          bank_pass_word,
          %% 投资者帐号
          account_id,
          %% 期货密码
          password,
          %% 期货公司流水号
          future_serial,
          %% 安装编号
          install_id,
          %% 用户标识
          user_id,
          %% 验证客户证件号码标志
          verify_cert_no_flag,
          %% 币种代码
          currency_id,
          %% 摘要
          digest,
          %% 银行帐号类型
          bank_acc_type,
          %% 渠道标志
          device_id,
          %% 期货单位帐号类型
          bank_secu_acc_type,
          %% 期货公司银行编码
          broker_idby_bank,
          %% 期货单位帐号
          bank_secu_acc,
          %% 银行密码标志
          bank_pwd_flag,
          %% 期货资金密码核对标志
          secu_pwd_flag,
          %% 交易柜员
          oper_no,
          %% 请求编号
          request_id,
          %% 交易ID
          tid,
          %% 银行可用金额
          bank_use_amount,
          %% 银行可取金额
          bank_fetch_amount,
          %% 错误代码
          error_id,
          %% 错误信息
          error_msg
         }).

-record(cthost_ftdc_transfer_serial_field, {
          %% 平台流水号
          plate_serial,
          %% 交易发起方日期
          trade_date,
          %% 交易日期
          trading_day,
          %% 交易时间
          trade_time,
          %% 交易代码
          trade_code,
          %% 会话编号
          session_id,
          %% 银行编码
          bank_id,
          %% 银行分支机构编码
          bank_branch_id,
          %% 银行帐号类型
          bank_acc_type,
          %% 银行帐号
          bank_account,
          %% 银行流水号
          bank_serial,
          %% 期货公司编码
          broker_id,
          %% 期商分支机构代码
          broker_branch_id,
          %% 期货公司帐号类型
          future_acc_type,
          %% 投资者帐号
          account_id,
          %% 投资者代码
          investor_id,
          %% 期货公司流水号
          future_serial,
          %% 证件类型
          id_card_type,
          %% 证件号码
          identified_card_no,
          %% 币种代码
          currency_id,
          %% 交易金额
          trade_amount,
          %% 应收客户费用
          cust_fee,
          %% 应收期货公司费用
          broker_fee,
          %% 有效标志
          availability_flag,
          %% 操作员
          operator_code,
          %% 新银行帐号
          bank_new_account,
          %% 错误代码
          error_id,
          %% 错误信息
          error_msg
         }).

-record(cthost_ftdc_qry_transfer_serial_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者帐号
          account_id,
          %% 银行编码
          bank_id,
          %% 币种代码
          currency_id
         }).

-record(cthost_ftdc_notify_future_sign_in_field, {
          %% 业务功能码
          trade_code,
          %% 银行代码
          bank_id,
          %% 银行分支机构代码
          bank_branch_id,
          %% 期商代码
          broker_id,
          %% 期商分支机构代码
          broker_branch_id,
          %% 交易日期
          trade_date,
          %% 交易时间
          trade_time,
          %% 银行流水号
          bank_serial,
          %% 交易系统日期
          trading_day,
          %% 银期平台消息流水号
          plate_serial,
          %% 最后分片标志
          last_fragment,
          %% 会话号
          session_id,
          %% 安装编号
          install_id,
          %% 用户标识
          user_id,
          %% 摘要
          digest,
          %% 币种代码
          currency_id,
          %% 渠道标志
          device_id,
          %% 期货公司银行编码
          broker_idby_bank,
          %% 交易柜员
          oper_no,
          %% 请求编号
          request_id,
          %% 交易ID
          tid,
          %% 错误代码
          error_id,
          %% 错误信息
          error_msg,
          %% PIN密钥
          pin_key,
          %% MAC密钥
          mac_key
         }).

-record(cthost_ftdc_notify_future_sign_out_field, {
          %% 业务功能码
          trade_code,
          %% 银行代码
          bank_id,
          %% 银行分支机构代码
          bank_branch_id,
          %% 期商代码
          broker_id,
          %% 期商分支机构代码
          broker_branch_id,
          %% 交易日期
          trade_date,
          %% 交易时间
          trade_time,
          %% 银行流水号
          bank_serial,
          %% 交易系统日期
          trading_day,
          %% 银期平台消息流水号
          plate_serial,
          %% 最后分片标志
          last_fragment,
          %% 会话号
          session_id,
          %% 安装编号
          install_id,
          %% 用户标识
          user_id,
          %% 摘要
          digest,
          %% 币种代码
          currency_id,
          %% 渠道标志
          device_id,
          %% 期货公司银行编码
          broker_idby_bank,
          %% 交易柜员
          oper_no,
          %% 请求编号
          request_id,
          %% 交易ID
          tid,
          %% 错误代码
          error_id,
          %% 错误信息
          error_msg
         }).

-record(cthost_ftdc_notify_sync_key_field, {
          %% 业务功能码
          trade_code,
          %% 银行代码
          bank_id,
          %% 银行分支机构代码
          bank_branch_id,
          %% 期商代码
          broker_id,
          %% 期商分支机构代码
          broker_branch_id,
          %% 交易日期
          trade_date,
          %% 交易时间
          trade_time,
          %% 银行流水号
          bank_serial,
          %% 交易系统日期
          trading_day,
          %% 银期平台消息流水号
          plate_serial,
          %% 最后分片标志
          last_fragment,
          %% 会话号
          session_id,
          %% 安装编号
          install_id,
          %% 用户标识
          user_id,
          %% 交易核心给银期报盘的消息
          message,
          %% 渠道标志
          device_id,
          %% 期货公司银行编码
          broker_idby_bank,
          %% 交易柜员
          oper_no,
          %% 请求编号
          request_id,
          %% 交易ID
          tid,
          %% 错误代码
          error_id,
          %% 错误信息
          error_msg
         }).

-record(cthost_ftdc_qry_accountregister_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者帐号
          account_id,
          %% 银行编码
          bank_id,
          %% 银行分支机构编码
          bank_branch_id,
          %% 币种代码
          currency_id
         }).

-record(cthost_ftdc_accountregister_field, {
          %% 交易日期
          trade_day,
          %% 银行编码
          bank_id,
          %% 银行分支机构编码
          bank_branch_id,
          %% 银行帐号
          bank_account,
          %% 期货公司编码
          broker_id,
          %% 期货公司分支机构编码
          broker_branch_id,
          %% 投资者帐号
          account_id,
          %% 证件类型
          id_card_type,
          %% 证件号码
          identified_card_no,
          %% 客户姓名
          customer_name,
          %% 币种代码
          currency_id,
          %% 开销户类别
          open_or_destroy,
          %% 签约日期
          reg_date,
          %% 解约日期
          out_date,
          %% 交易ID
          tid,
          %% 客户类型
          cust_type,
          %% 银行帐号类型
          bank_acc_type
         }).

-record(cthost_ftdc_open_account_field, {
          %% 业务功能码
          trade_code,
          %% 银行代码
          bank_id,
          %% 银行分支机构代码
          bank_branch_id,
          %% 期商代码
          broker_id,
          %% 期商分支机构代码
          broker_branch_id,
          %% 交易日期
          trade_date,
          %% 交易时间
          trade_time,
          %% 银行流水号
          bank_serial,
          %% 交易系统日期
          trading_day,
          %% 银期平台消息流水号
          plate_serial,
          %% 最后分片标志
          last_fragment,
          %% 会话号
          session_id,
          %% 客户姓名
          customer_name,
          %% 证件类型
          id_card_type,
          %% 证件号码
          identified_card_no,
          %% 性别
          gender,
          %% 国家代码
          country_code,
          %% 客户类型
          cust_type,
          %% 地址
          address,
          %% 邮编
          zip_code,
          %% 电话号码
          telephone,
          %% 手机
          mobile_phone,
          %% 传真
          fax,
          %% 电子邮件
          email,
          %% 资金账户状态
          money_account_status,
          %% 银行帐号
          bank_account,
          %% 银行密码
          bank_pass_word,
          %% 投资者帐号
          account_id,
          %% 期货密码
          password,
          %% 安装编号
          install_id,
          %% 验证客户证件号码标志
          verify_cert_no_flag,
          %% 币种代码
          currency_id,
          %% 汇钞标志
          cash_exchange_code,
          %% 摘要
          digest,
          %% 银行帐号类型
          bank_acc_type,
          %% 渠道标志
          device_id,
          %% 期货单位帐号类型
          bank_secu_acc_type,
          %% 期货公司银行编码
          broker_idby_bank,
          %% 期货单位帐号
          bank_secu_acc,
          %% 银行密码标志
          bank_pwd_flag,
          %% 期货资金密码核对标志
          secu_pwd_flag,
          %% 交易柜员
          oper_no,
          %% 交易ID
          tid,
          %% 用户标识
          user_id,
          %% 错误代码
          error_id,
          %% 错误信息
          error_msg
         }).

-record(cthost_ftdc_cancel_account_field, {
          %% 业务功能码
          trade_code,
          %% 银行代码
          bank_id,
          %% 银行分支机构代码
          bank_branch_id,
          %% 期商代码
          broker_id,
          %% 期商分支机构代码
          broker_branch_id,
          %% 交易日期
          trade_date,
          %% 交易时间
          trade_time,
          %% 银行流水号
          bank_serial,
          %% 交易系统日期
          trading_day,
          %% 银期平台消息流水号
          plate_serial,
          %% 最后分片标志
          last_fragment,
          %% 会话号
          session_id,
          %% 客户姓名
          customer_name,
          %% 证件类型
          id_card_type,
          %% 证件号码
          identified_card_no,
          %% 性别
          gender,
          %% 国家代码
          country_code,
          %% 客户类型
          cust_type,
          %% 地址
          address,
          %% 邮编
          zip_code,
          %% 电话号码
          telephone,
          %% 手机
          mobile_phone,
          %% 传真
          fax,
          %% 电子邮件
          email,
          %% 资金账户状态
          money_account_status,
          %% 银行帐号
          bank_account,
          %% 银行密码
          bank_pass_word,
          %% 投资者帐号
          account_id,
          %% 期货密码
          password,
          %% 安装编号
          install_id,
          %% 验证客户证件号码标志
          verify_cert_no_flag,
          %% 币种代码
          currency_id,
          %% 汇钞标志
          cash_exchange_code,
          %% 摘要
          digest,
          %% 银行帐号类型
          bank_acc_type,
          %% 渠道标志
          device_id,
          %% 期货单位帐号类型
          bank_secu_acc_type,
          %% 期货公司银行编码
          broker_idby_bank,
          %% 期货单位帐号
          bank_secu_acc,
          %% 银行密码标志
          bank_pwd_flag,
          %% 期货资金密码核对标志
          secu_pwd_flag,
          %% 交易柜员
          oper_no,
          %% 交易ID
          tid,
          %% 用户标识
          user_id,
          %% 错误代码
          error_id,
          %% 错误信息
          error_msg
         }).

-record(cthost_ftdc_change_account_field, {
          %% 业务功能码
          trade_code,
          %% 银行代码
          bank_id,
          %% 银行分支机构代码
          bank_branch_id,
          %% 期商代码
          broker_id,
          %% 期商分支机构代码
          broker_branch_id,
          %% 交易日期
          trade_date,
          %% 交易时间
          trade_time,
          %% 银行流水号
          bank_serial,
          %% 交易系统日期
          trading_day,
          %% 银期平台消息流水号
          plate_serial,
          %% 最后分片标志
          last_fragment,
          %% 会话号
          session_id,
          %% 客户姓名
          customer_name,
          %% 证件类型
          id_card_type,
          %% 证件号码
          identified_card_no,
          %% 性别
          gender,
          %% 国家代码
          country_code,
          %% 客户类型
          cust_type,
          %% 地址
          address,
          %% 邮编
          zip_code,
          %% 电话号码
          telephone,
          %% 手机
          mobile_phone,
          %% 传真
          fax,
          %% 电子邮件
          email,
          %% 资金账户状态
          money_account_status,
          %% 银行帐号
          bank_account,
          %% 银行密码
          bank_pass_word,
          %% 新银行帐号
          new_bank_account,
          %% 新银行密码
          new_bank_pass_word,
          %% 投资者帐号
          account_id,
          %% 期货密码
          password,
          %% 银行帐号类型
          bank_acc_type,
          %% 安装编号
          install_id,
          %% 验证客户证件号码标志
          verify_cert_no_flag,
          %% 币种代码
          currency_id,
          %% 期货公司银行编码
          broker_idby_bank,
          %% 银行密码标志
          bank_pwd_flag,
          %% 期货资金密码核对标志
          secu_pwd_flag,
          %% 交易ID
          tid,
          %% 摘要
          digest,
          %% 错误代码
          error_id,
          %% 错误信息
          error_msg
         }).

-record(cthost_ftdc_sec_agent_acidmap_field, {
          %% 经纪公司代码
          broker_id,
          %% 用户代码
          user_id,
          %% 资金账户
          account_id,
          %% 币种
          currency_id,
          %% 境外中介机构资金帐号
          broker_sec_agent_id
         }).

-record(cthost_ftdc_qry_sec_agent_acidmap_field, {
          %% 经纪公司代码
          broker_id,
          %% 用户代码
          user_id,
          %% 资金账户
          account_id,
          %% 币种
          currency_id
         }).

-record(cthost_ftdc_user_rights_assign_field, {
          %% 应用单元代码
          broker_id,
          %% 用户代码
          user_id,
          %% 交易中心代码
          dridentity_id
         }).

-record(cthost_ftdc_broker_user_right_assign_field, {
          %% 应用单元代码
          broker_id,
          %% 交易中心代码
          dridentity_id,
          %% 能否交易
          tradeable
         }).

-record(cthost_ftdc_drtransfer_field, {
          %% 原交易中心代码
          orig_dridentity_id,
          %% 目标交易中心代码
          dest_dridentity_id,
          %% 原应用单元代码
          orig_broker_id,
          %% 目标易用单元代码
          dest_broker_id
         }).

-record(cthost_ftdc_fens_user_info_field, {
          %% 经纪公司代码
          broker_id,
          %% 用户代码
          user_id,
          %% 登录模式
          login_mode
         }).

-record(cthost_ftdc_curr_transfer_identity_field, {
          %% 交易中心代码
          identity_id
         }).

-record(cthost_ftdc_login_forbidden_user_field, {
          %% 经纪公司代码
          broker_id,
          %% 用户代码
          user_id,
          %% IP地址
          ipaddress
         }).

-record(cthost_ftdc_qry_login_forbidden_user_field, {
          %% 经纪公司代码
          broker_id,
          %% 用户代码
          user_id
         }).

-record(cthost_ftdc_multicast_group_info_field, {
          %% 组播组IP地址
          group_ip,
          %% 组播组IP端口
          group_port,
          %% 源地址
          source_ip
         }).

-record(cthost_ftdc_trading_account_reserve_field, {
          %% 经纪公司代码
          broker_id,
          %% 投资者帐号
          account_id,
          %% 基本准备金
          reserve,
          %% 币种代码
          currency_id
         }).

-record(cthost_ftdc_dbfrecord_field, {
          %% DBF命令类型
          dbfcomd_type,
          %% DBF时间类型
          dbfcom_time,
          %% DBF原始流水号类型
          dbfocom_no,
          %% DBF流水号类型
          dbfcom_no,
          %% DBF字段类型
          dbffd_name1,
          %% DBF字段内容类型
          dbffd_content1,
          %% DBF字段类型
          dbffd_name2,
          %% DBF字段内容类型
          dbffd_content2,
          %% DBF字段类型
          dbffd_name3,
          %% DBF字段内容类型
          dbffd_content3,
          %% DBF字段类型
          dbffd_name4,
          %% DBF字段内容类型
          dbffd_content4
         }).
