#include "common/common.h"
#include "ctp_md.h"
#include "erl_nif.h"
#include <iostream>
#include <new>

/**
 * 模块私有状态数据
 */
struct CtpState {
  ERL_NIF_TERM atom_ok;
  ERL_NIF_TERM atom_error;
  ERL_NIF_TERM atom_bad_alloc;

  ErlNifResourceType *res_md;
};

/* -----------------------------------------------------------------------------
 * API函数
 * -----------------------------------------------------------------------------
 */

static ERL_NIF_TERM New(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));

  CtpMd **obj =
      static_cast<CtpMd **>(enif_alloc_resource(st->res_md, sizeof(CtpMd *)));
  if (!obj) {
    return enif_make_tuple2(env, st->atom_error, st->atom_bad_alloc);
  }

  ErlNifPid pid;
  if (argc != 1 ||
      !enif_get_local_pid(env, argv[0], &pid)) {
    return enif_make_badarg(env);
  }

  CtpMd *md = new (std::nothrow) CtpMd(pid);
  if (!md) {
    enif_release_resource(obj);
    return enif_make_tuple2(env, st->atom_error, st->atom_bad_alloc);
  }

  *obj = md;
  ERL_NIF_TERM term = enif_make_resource(env, obj);
  enif_release_resource(obj);

  return enif_make_tuple2(env, st->atom_ok, term);
}

static ERL_NIF_TERM CreateApi(ErlNifEnv *env, int argc,
                              const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpMd **obj;
  ErlNifBinary flow_path;

  if (argc != 2 ||
      !enif_get_resource(env, argv[0], st->res_md,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_inspect_binary(env, argv[1], &flow_path)) {
    return enif_make_badarg(env);
  }

  if (!flow_path.size) {
    return enif_make_badarg(env);
  }

  (*obj)->CreateApi(&flow_path);

  return st->atom_ok;
}

static ERL_NIF_TERM GetApiVersion(ErlNifEnv *env, int argc,
                                  const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpMd **obj;

  if (argc != 1 || !enif_get_resource(env, argv[0], st->res_md,
                                      reinterpret_cast<void **>(&obj))) {
    return enif_make_badarg(env);
  }

  return enif_make_tuple2(env, st->atom_ok, (*obj)->GetApiVersion(env));
}

static ERL_NIF_TERM Init(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpMd **obj;

  if (argc != 1 || !enif_get_resource(env, argv[0], st->res_md,
                                      reinterpret_cast<void **>(&obj))) {
    return enif_make_badarg(env);
  }

  (*obj)->Init();

  return st->atom_ok;
}

static ERL_NIF_TERM Exit(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpMd **obj;

  if (argc != 1 || !enif_get_resource(env, argv[0], st->res_md,
                                      reinterpret_cast<void **>(&obj))) {
    return enif_make_badarg(env);
  }

  (*obj)->Exit();

  return st->atom_ok;
}

static ERL_NIF_TERM GetTradingDay(ErlNifEnv *env, int argc,
                                  const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpMd **obj;

  if (argc != 1 || !enif_get_resource(env, argv[0], st->res_md,
                                      reinterpret_cast<void **>(&obj))) {
    return enif_make_badarg(env);
  }

  return enif_make_tuple2(env, st->atom_ok, (*obj)->GetTradingDay(env));
}

static ERL_NIF_TERM RegisterFront(ErlNifEnv *env, int argc,
                                  const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpMd **obj;
  ErlNifBinary front_address;

  if (argc != 2 ||
      !enif_get_resource(env, argv[0], st->res_md,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_inspect_binary(env, argv[1], &front_address)) {
    return enif_make_badarg(env);
  }

  if (!front_address.size) {
    return enif_make_badarg(env);
  }

  (*obj)->RegisterFront(&front_address);

  return st->atom_ok;
}

static ERL_NIF_TERM RegisterNameServer(ErlNifEnv *env, int argc,
                                       const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpMd **obj;
  ErlNifBinary ns_address;

  if (argc != 2 ||
      !enif_get_resource(env, argv[0], st->res_md,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_inspect_binary(env, argv[1], &ns_address)) {
    return enif_make_badarg(env);
  }

  if (!ns_address.size) {
    return enif_make_badarg(env);
  }

  (*obj)->RegisterFront(&ns_address);

  return st->atom_ok;
}

static ERL_NIF_TERM RegisterFensUserInfo(ErlNifEnv *env, int argc,
                                         const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpMd **obj;
  NifRecord req;

  if (argc != 2 ||
      !enif_get_resource(env, argv[0], st->res_md,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms))) {
    return enif_make_badarg(env);
  }

  (*obj)->RegisterFensUserInfo(env, &req);

  return st->atom_ok;
}

static ERL_NIF_TERM SubscribeMarketData(ErlNifEnv *env, int argc,
                                        const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpMd **obj;

  if (argc != 2 ||
      !enif_get_resource(env, argv[0], st->res_md,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_is_list(env, argv[1])) {
    return enif_make_badarg(env);
  }

  return (*obj)->SubscribeMarketData(env, argv[1]) ? st->atom_error
                                                   : st->atom_ok;
}

static ERL_NIF_TERM UnSubscribeMarketData(ErlNifEnv *env, int argc,
                                          const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpMd **obj;

  if (argc != 2 ||
      !enif_get_resource(env, argv[0], st->res_md,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_is_list(env, argv[1])) {
    return enif_make_badarg(env);
  }

  return (*obj)->UnSubscribeMarketData(env, argv[1]) ? st->atom_error
                                                     : st->atom_ok;
}

static ERL_NIF_TERM SubscribeForQuoteRsp(ErlNifEnv *env, int argc,
                                         const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpMd **obj;

  if (argc != 2 ||
      !enif_get_resource(env, argv[0], st->res_md,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_is_list(env, argv[1])) {
    return enif_make_badarg(env);
  }

  return (*obj)->SubscribeForQuoteRsp(env, argv[1]) ? st->atom_error
                                                    : st->atom_ok;
}

static ERL_NIF_TERM UnSubscribeForQuoteRsp(ErlNifEnv *env, int argc,
                                           const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpMd **obj;

  if (argc != 2 ||
      !enif_get_resource(env, argv[0], st->res_md,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_is_list(env, argv[1])) {
    return enif_make_badarg(env);
  }

  return (*obj)->UnSubscribeForQuoteRsp(env, argv[1]) ? st->atom_error
                                                      : st->atom_ok;
}

static ERL_NIF_TERM ReqUserLogin(ErlNifEnv *env, int argc,
                                 const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpMd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_md,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqUserLogin(env, &req, req_id) ? st->atom_error : st->atom_ok;
}

static ERL_NIF_TERM ReqUserLogout(ErlNifEnv *env, int argc,
                                  const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpMd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_md,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqUserLogout(env, &req, req_id) ? st->atom_error
                                                  : st->atom_ok;
}

/* -----------------------------------------------------------------------------
 * 工具函数
 * -----------------------------------------------------------------------------
 */

static void CtpMdResDtor(ErlNifEnv *env, void *obj) {
  delete *(static_cast<CtpMd **>(obj));
}

/* -----------------------------------------------------------------------------
 * NIF库事件函数
 * -----------------------------------------------------------------------------
 */

static int Load(ErlNifEnv *env, void **priv, ERL_NIF_TERM load_info) {
  CtpState *st = static_cast<CtpState *>(enif_alloc(sizeof(CtpState)));
  if (!st) {
    return -1;
  }

  st->atom_ok = enif_make_atom(env, "ok");
  st->atom_error = enif_make_atom(env, "error");
  st->atom_bad_alloc = enif_make_atom(env, "bad_alloc");

  st->res_md = enif_open_resource_type(
      env, NULL, "ctp_md", CtpMdResDtor,
      static_cast<ErlNifResourceFlags>(ERL_NIF_RT_CREATE | ERL_NIF_RT_TAKEOVER),
      NULL);

  *priv = static_cast<void *>(st);
  return 0;
}

static int Upgrade(ErlNifEnv *env, void **priv, void **old_priv,
                   ERL_NIF_TERM load_info) {
  return Load(env, priv, load_info);
}

static void Unload(ErlNifEnv *env, void *priv) { enif_free(priv); }

/* -----------------------------------------------------------------------------
 * NIF库导出
 * -----------------------------------------------------------------------------
 */

static ErlNifFunc nif_funcs[] = {
    {"new", 1, New},
    {"create_api", 2, CreateApi},
    {"get_api_version", 1, GetApiVersion},
    {"init", 1, Init},
    {"exit", 1, Exit},
    {"get_trading_day", 1, GetTradingDay},
    {"register_front", 2, RegisterFront},
    {"register_name_server", 2, RegisterNameServer},
    {"register_fens_user_info", 2, RegisterFensUserInfo},
    {"subscribe_market_data", 2, SubscribeMarketData},
    {"un_subscribe_market_data", 2, UnSubscribeMarketData},
    {"subscribe_for_quote_rsp", 2, SubscribeForQuoteRsp},
    {"un_subscribe_for_quote_rsp", 2, UnSubscribeForQuoteRsp},
    {"req_user_login", 3, ReqUserLogin},
    {"req_user_logout", 3, ReqUserLogout}};

ERL_NIF_INIT(ctp_md_nif, nif_funcs, Load, NULL, Upgrade, Unload)
