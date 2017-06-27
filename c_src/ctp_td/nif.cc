#include "common/common.h"
#include "ctp_td.h"
#include "erl_nif.h"
#include <iostream>
#include <new>

struct CtpState {
  ERL_NIF_TERM atom_ok;
  ERL_NIF_TERM atom_error;
  ERL_NIF_TERM atom_bad_alloc;

  ErlNifResourceType *res_td;
};

/* -----------------------------------------------------------------------------
 * API函数
 * -----------------------------------------------------------------------------
 */

static ERL_NIF_TERM New(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));

  CtpTd **obj =
      static_cast<CtpTd **>(enif_alloc_resource(st->res_td, sizeof(CtpTd *)));
  if (!obj) {
    return enif_make_tuple2(env, st->atom_error, st->atom_bad_alloc);
  }

  ErlNifPid pid;
  if (argc != 1 ||
      !enif_get_local_pid(env, argv[0], &pid)) {
    return enif_make_badarg(env);
  }

  CtpTd *td = new (std::nothrow) CtpTd(pid);
  if (!td) {
    enif_release_resource(obj);
    return enif_make_tuple2(env, st->atom_error, st->atom_bad_alloc);
  }

  *obj = td;
  ERL_NIF_TERM term = enif_make_resource(env, obj);
  enif_release_resource(obj);

  return enif_make_tuple2(env, st->atom_ok, term);
}

static ERL_NIF_TERM CreateApi(ErlNifEnv *env, int argc,
                              const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  ErlNifBinary flow_path;

  if (argc != 2 ||
      !enif_get_resource(env, argv[0], st->res_td,
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
  CtpTd **obj;

  if (argc != 1 || !enif_get_resource(env, argv[0], st->res_td,
                                      reinterpret_cast<void **>(&obj))) {
    return enif_make_badarg(env);
  }

  return enif_make_tuple2(env, st->atom_ok, (*obj)->GetApiVersion(env));
}

static ERL_NIF_TERM Init(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;

  if (argc != 1 || !enif_get_resource(env, argv[0], st->res_td,
                                      reinterpret_cast<void **>(&obj))) {
    return enif_make_badarg(env);
  }

  (*obj)->Init();

  return st->atom_ok;
}

static ERL_NIF_TERM Exit(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;

  if (argc != 1 || !enif_get_resource(env, argv[0], st->res_td,
                                      reinterpret_cast<void **>(&obj))) {
    return enif_make_badarg(env);
  }

  (*obj)->Exit();

  return st->atom_ok;
}

static ERL_NIF_TERM GetTradingDay(ErlNifEnv *env, int argc,
                                  const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;

  if (argc != 1 || !enif_get_resource(env, argv[0], st->res_td,
                                      reinterpret_cast<void **>(&obj))) {
    return enif_make_badarg(env);
  }

  return enif_make_tuple2(env, st->atom_ok, (*obj)->GetTradingDay(env));
}

static ERL_NIF_TERM RegisterFront(ErlNifEnv *env, int argc,
                                  const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  ErlNifBinary front_address;

  if (argc != 2 ||
      !enif_get_resource(env, argv[0], st->res_td,
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
  CtpTd **obj;
  ErlNifBinary ns_address;

  if (argc != 2 ||
      !enif_get_resource(env, argv[0], st->res_td,
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
  CtpTd **obj;
  NifRecord req;

  if (argc != 2 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms))) {
    return enif_make_badarg(env);
  }

  (*obj)->RegisterFensUserInfo(env, &req);

  return st->atom_ok;
}

static ERL_NIF_TERM SubscribePrivateTopic(ErlNifEnv *env, int argc,
                                          const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  int resume_type;

  if (argc != 2 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_int(env, argv[1], &resume_type)) {
    return enif_make_badarg(env);
  }

  (*obj)->SubscribePrivateTopic(resume_type);

  return st->atom_ok;
}

static ERL_NIF_TERM SubscribePublicTopic(ErlNifEnv *env, int argc,
                                         const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  int resume_type;

  if (argc != 2 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_int(env, argv[1], &resume_type)) {
    return enif_make_badarg(env);
  }

  (*obj)->SubscribePublicTopic(resume_type);

  return st->atom_ok;
}

static ERL_NIF_TERM ReqAuthenticate(ErlNifEnv *env, int argc,
                                    const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqAuthenticate(env, &req, req_id) ? st->atom_error
                                                    : st->atom_ok;
}

static ERL_NIF_TERM ReqUserLogin(ErlNifEnv *env, int argc,
                                 const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
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
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqUserLogout(env, &req, req_id) ? st->atom_error
                                                  : st->atom_ok;
}

static ERL_NIF_TERM ReqUserPasswordUpdate(ErlNifEnv *env, int argc,
                                          const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqUserPasswordUpdate(env, &req, req_id) ? st->atom_error
                                                          : st->atom_ok;
}

static ERL_NIF_TERM ReqTradingAccountPasswordUpdate(ErlNifEnv *env, int argc,
                                                    const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqTradingAccountPasswordUpdate(env, &req, req_id)
             ? st->atom_error
             : st->atom_ok;
}

static ERL_NIF_TERM ReqOrderInsert(ErlNifEnv *env, int argc,
                                   const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqOrderInsert(env, &req, req_id) ? st->atom_error
                                                   : st->atom_ok;
}

static ERL_NIF_TERM ReqParkedOrderInsert(ErlNifEnv *env, int argc,
                                         const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqParkedOrderInsert(env, &req, req_id) ? st->atom_error
                                                         : st->atom_ok;
}

static ERL_NIF_TERM ReqParkedOrderAction(ErlNifEnv *env, int argc,
                                         const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqParkedOrderAction(env, &req, req_id) ? st->atom_error
                                                         : st->atom_ok;
}

static ERL_NIF_TERM ReqOrderAction(ErlNifEnv *env, int argc,
                                   const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqOrderAction(env, &req, req_id) ? st->atom_error
                                                   : st->atom_ok;
}

static ERL_NIF_TERM ReqQueryMaxOrderVolume(ErlNifEnv *env, int argc,
                                           const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQueryMaxOrderVolume(env, &req, req_id) ? st->atom_error
                                                           : st->atom_ok;
}

static ERL_NIF_TERM ReqSettlementInfoConfirm(ErlNifEnv *env, int argc,
                                             const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqSettlementInfoConfirm(env, &req, req_id) ? st->atom_error
                                                             : st->atom_ok;
}

static ERL_NIF_TERM ReqRemoveParkedOrder(ErlNifEnv *env, int argc,
                                         const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqRemoveParkedOrder(env, &req, req_id) ? st->atom_error
                                                         : st->atom_ok;
}

static ERL_NIF_TERM ReqRemoveParkedOrderAction(ErlNifEnv *env, int argc,
                                               const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqRemoveParkedOrderAction(env, &req, req_id) ? st->atom_error
                                                               : st->atom_ok;
}

static ERL_NIF_TERM ReqExecOrderInsert(ErlNifEnv *env, int argc,
                                       const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqExecOrderInsert(env, &req, req_id) ? st->atom_error
                                                       : st->atom_ok;
}

static ERL_NIF_TERM ReqExecOrderAction(ErlNifEnv *env, int argc,
                                       const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqExecOrderAction(env, &req, req_id) ? st->atom_error
                                                       : st->atom_ok;
}

static ERL_NIF_TERM ReqForQuoteInsert(ErlNifEnv *env, int argc,
                                      const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqForQuoteInsert(env, &req, req_id) ? st->atom_error
                                                      : st->atom_ok;
}

static ERL_NIF_TERM ReqQuoteInsert(ErlNifEnv *env, int argc,
                                   const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQuoteInsert(env, &req, req_id) ? st->atom_error
                                                   : st->atom_ok;
}

static ERL_NIF_TERM ReqQuoteAction(ErlNifEnv *env, int argc,
                                   const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQuoteAction(env, &req, req_id) ? st->atom_error
                                                   : st->atom_ok;
}

static ERL_NIF_TERM ReqLockInsert(ErlNifEnv *env, int argc,
                                  const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqLockInsert(env, &req, req_id) ? st->atom_error
                                                  : st->atom_ok;
}

static ERL_NIF_TERM ReqBatchOrderAction(ErlNifEnv *env, int argc,
                                        const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqBatchOrderAction(env, &req, req_id) ? st->atom_error
                                                        : st->atom_ok;
}

static ERL_NIF_TERM ReqCombActionInsert(ErlNifEnv *env, int argc,
                                        const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqCombActionInsert(env, &req, req_id) ? st->atom_error
                                                        : st->atom_ok;
}

static ERL_NIF_TERM ReqQryOrder(ErlNifEnv *env, int argc,
                                const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQryOrder(env, &req, req_id) ? st->atom_error : st->atom_ok;
}

static ERL_NIF_TERM ReqQryTrade(ErlNifEnv *env, int argc,
                                const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQryTrade(env, &req, req_id) ? st->atom_error : st->atom_ok;
}

static ERL_NIF_TERM ReqQryInvestorPosition(ErlNifEnv *env, int argc,
                                           const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQryInvestorPosition(env, &req, req_id) ? st->atom_error
                                                           : st->atom_ok;
}

static ERL_NIF_TERM ReqQryTradingAccount(ErlNifEnv *env, int argc,
                                         const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQryTradingAccount(env, &req, req_id) ? st->atom_error
                                                         : st->atom_ok;
}

static ERL_NIF_TERM ReqQryInvestor(ErlNifEnv *env, int argc,
                                   const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQryInvestor(env, &req, req_id) ? st->atom_error
                                                   : st->atom_ok;
}

static ERL_NIF_TERM ReqQryTradingCode(ErlNifEnv *env, int argc,
                                      const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQryTradingCode(env, &req, req_id) ? st->atom_error
                                                      : st->atom_ok;
}

static ERL_NIF_TERM ReqQryInstrumentMarginRate(ErlNifEnv *env, int argc,
                                               const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQryInstrumentMarginRate(env, &req, req_id) ? st->atom_error
                                                               : st->atom_ok;
}

static ERL_NIF_TERM ReqQryInstrumentCommissionRate(ErlNifEnv *env, int argc,
                                                   const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQryInstrumentCommissionRate(env, &req, req_id)
             ? st->atom_error
             : st->atom_ok;
}

static ERL_NIF_TERM ReqQryExchange(ErlNifEnv *env, int argc,
                                   const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQryExchange(env, &req, req_id) ? st->atom_error
                                                   : st->atom_ok;
}

static ERL_NIF_TERM ReqQryProduct(ErlNifEnv *env, int argc,
                                  const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQryProduct(env, &req, req_id) ? st->atom_error
                                                  : st->atom_ok;
}

static ERL_NIF_TERM ReqQryInstrument(ErlNifEnv *env, int argc,
                                     const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQryInstrument(env, &req, req_id) ? st->atom_error
                                                     : st->atom_ok;
}

static ERL_NIF_TERM ReqQryDepthMarketData(ErlNifEnv *env, int argc,
                                          const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQryDepthMarketData(env, &req, req_id) ? st->atom_error
                                                          : st->atom_ok;
}

static ERL_NIF_TERM ReqQrySettlementInfo(ErlNifEnv *env, int argc,
                                         const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQrySettlementInfo(env, &req, req_id) ? st->atom_error
                                                         : st->atom_ok;
}

static ERL_NIF_TERM ReqQryTransferBank(ErlNifEnv *env, int argc,
                                       const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQryTransferBank(env, &req, req_id) ? st->atom_error
                                                       : st->atom_ok;
}

static ERL_NIF_TERM ReqQryInvestorPositionDetail(ErlNifEnv *env, int argc,
                                                 const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQryInvestorPositionDetail(env, &req, req_id)
             ? st->atom_error
             : st->atom_ok;
}

static ERL_NIF_TERM ReqQryNotice(ErlNifEnv *env, int argc,
                                 const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQryNotice(env, &req, req_id) ? st->atom_error : st->atom_ok;
}

static ERL_NIF_TERM ReqQrySettlementInfoConfirm(ErlNifEnv *env, int argc,
                                                const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQrySettlementInfoConfirm(env, &req, req_id) ? st->atom_error
                                                                : st->atom_ok;
}

static ERL_NIF_TERM
ReqQryInvestorPositionCombineDetail(ErlNifEnv *env, int argc,
                                    const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQryInvestorPositionCombineDetail(env, &req, req_id)
             ? st->atom_error
             : st->atom_ok;
}

static ERL_NIF_TERM ReqQryCFMMCTradingAccountKey(ErlNifEnv *env, int argc,
                                                 const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQryCFMMCTradingAccountKey(env, &req, req_id)
             ? st->atom_error
             : st->atom_ok;
}

static ERL_NIF_TERM ReqQryEWarrantOffset(ErlNifEnv *env, int argc,
                                         const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQryEWarrantOffset(env, &req, req_id) ? st->atom_error
                                                         : st->atom_ok;
}

static ERL_NIF_TERM
ReqQryInvestorProductGroupMargin(ErlNifEnv *env, int argc,
                                 const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQryInvestorProductGroupMargin(env, &req, req_id)
             ? st->atom_error
             : st->atom_ok;
}

static ERL_NIF_TERM ReqQryExchangeMarginRate(ErlNifEnv *env, int argc,
                                             const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQryExchangeMarginRate(env, &req, req_id) ? st->atom_error
                                                             : st->atom_ok;
}

static ERL_NIF_TERM ReqQryExchangeMarginRateAdjust(ErlNifEnv *env, int argc,
                                                   const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQryExchangeMarginRateAdjust(env, &req, req_id)
             ? st->atom_error
             : st->atom_ok;
}

static ERL_NIF_TERM ReqQryExchangeRate(ErlNifEnv *env, int argc,
                                       const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQryExchangeRate(env, &req, req_id) ? st->atom_error
                                                       : st->atom_ok;
}

static ERL_NIF_TERM ReqQrySecAgentACIDMap(ErlNifEnv *env, int argc,
                                          const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQrySecAgentACIDMap(env, &req, req_id) ? st->atom_error
                                                          : st->atom_ok;
}

static ERL_NIF_TERM ReqQryProductExchRate(ErlNifEnv *env, int argc,
                                          const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQryProductExchRate(env, &req, req_id) ? st->atom_error
                                                          : st->atom_ok;
}

static ERL_NIF_TERM ReqQryProductGroup(ErlNifEnv *env, int argc,
                                       const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQryProductGroup(env, &req, req_id) ? st->atom_error
                                                       : st->atom_ok;
}

static ERL_NIF_TERM
ReqQryMMInstrumentCommissionRate(ErlNifEnv *env, int argc,
                                 const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQryMMInstrumentCommissionRate(env, &req, req_id)
             ? st->atom_error
             : st->atom_ok;
}

static ERL_NIF_TERM ReqQryMMOptionInstrCommRate(ErlNifEnv *env, int argc,
                                                const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQryMMOptionInstrCommRate(env, &req, req_id) ? st->atom_error
                                                                : st->atom_ok;
}

static ERL_NIF_TERM ReqQryInstrumentOrderCommRate(ErlNifEnv *env, int argc,
                                                  const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQryInstrumentOrderCommRate(env, &req, req_id)
             ? st->atom_error
             : st->atom_ok;
}

static ERL_NIF_TERM ReqQryOptionInstrTradeCost(ErlNifEnv *env, int argc,
                                               const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQryOptionInstrTradeCost(env, &req, req_id) ? st->atom_error
                                                               : st->atom_ok;
}

static ERL_NIF_TERM ReqQryOptionInstrCommRate(ErlNifEnv *env, int argc,
                                              const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQryOptionInstrCommRate(env, &req, req_id) ? st->atom_error
                                                              : st->atom_ok;
}

static ERL_NIF_TERM ReqQryExecOrder(ErlNifEnv *env, int argc,
                                    const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQryExecOrder(env, &req, req_id) ? st->atom_error
                                                    : st->atom_ok;
}

static ERL_NIF_TERM ReqQryForQuote(ErlNifEnv *env, int argc,
                                   const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQryForQuote(env, &req, req_id) ? st->atom_error
                                                   : st->atom_ok;
}

static ERL_NIF_TERM ReqQryQuote(ErlNifEnv *env, int argc,
                                const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQryQuote(env, &req, req_id) ? st->atom_error : st->atom_ok;
}

static ERL_NIF_TERM ReqQryLock(ErlNifEnv *env, int argc,
                               const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQryLock(env, &req, req_id) ? st->atom_error : st->atom_ok;
}

static ERL_NIF_TERM ReqQryLockPosition(ErlNifEnv *env, int argc,
                                       const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQryLockPosition(env, &req, req_id) ? st->atom_error
                                                       : st->atom_ok;
}

static ERL_NIF_TERM ReqQryETFOptionInstrCommRate(ErlNifEnv *env, int argc,
                                                 const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQryETFOptionInstrCommRate(env, &req, req_id)
             ? st->atom_error
             : st->atom_ok;
}

static ERL_NIF_TERM ReqQryInvestorLevel(ErlNifEnv *env, int argc,
                                        const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQryInvestorLevel(env, &req, req_id) ? st->atom_error
                                                        : st->atom_ok;
}

static ERL_NIF_TERM ReqQryExecFreeze(ErlNifEnv *env, int argc,
                                     const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQryExecFreeze(env, &req, req_id) ? st->atom_error
                                                     : st->atom_ok;
}

static ERL_NIF_TERM ReqQryCombInstrumentGuard(ErlNifEnv *env, int argc,
                                              const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQryCombInstrumentGuard(env, &req, req_id) ? st->atom_error
                                                              : st->atom_ok;
}

static ERL_NIF_TERM ReqQryCombAction(ErlNifEnv *env, int argc,
                                     const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQryCombAction(env, &req, req_id) ? st->atom_error
                                                     : st->atom_ok;
}

static ERL_NIF_TERM ReqQryTransferSerial(ErlNifEnv *env, int argc,
                                         const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQryTransferSerial(env, &req, req_id) ? st->atom_error
                                                         : st->atom_ok;
}

static ERL_NIF_TERM ReqQryAccountregister(ErlNifEnv *env, int argc,
                                          const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQryAccountregister(env, &req, req_id) ? st->atom_error
                                                          : st->atom_ok;
}

static ERL_NIF_TERM ReqQryContractBank(ErlNifEnv *env, int argc,
                                       const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQryContractBank(env, &req, req_id) ? st->atom_error
                                                       : st->atom_ok;
}

static ERL_NIF_TERM ReqQryParkedOrder(ErlNifEnv *env, int argc,
                                      const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQryParkedOrder(env, &req, req_id) ? st->atom_error
                                                      : st->atom_ok;
}

static ERL_NIF_TERM ReqQryParkedOrderAction(ErlNifEnv *env, int argc,
                                            const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQryParkedOrderAction(env, &req, req_id) ? st->atom_error
                                                            : st->atom_ok;
}

static ERL_NIF_TERM ReqQryTradingNotice(ErlNifEnv *env, int argc,
                                        const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQryTradingNotice(env, &req, req_id) ? st->atom_error
                                                        : st->atom_ok;
}

static ERL_NIF_TERM ReqQryBrokerTradingParams(ErlNifEnv *env, int argc,
                                              const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQryBrokerTradingParams(env, &req, req_id) ? st->atom_error
                                                              : st->atom_ok;
}

static ERL_NIF_TERM ReqQryBrokerTradingAlgos(ErlNifEnv *env, int argc,
                                             const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQryBrokerTradingAlgos(env, &req, req_id) ? st->atom_error
                                                             : st->atom_ok;
}

static ERL_NIF_TERM
ReqQueryCFMMCTradingAccountToken(ErlNifEnv *env, int argc,
                                 const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQueryCFMMCTradingAccountToken(env, &req, req_id)
             ? st->atom_error
             : st->atom_ok;
}

static ERL_NIF_TERM ReqFromBankToFutureByFuture(ErlNifEnv *env, int argc,
                                                const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqFromBankToFutureByFuture(env, &req, req_id) ? st->atom_error
                                                                : st->atom_ok;
}

static ERL_NIF_TERM ReqFromFutureToBankByFuture(ErlNifEnv *env, int argc,
                                                const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqFromFutureToBankByFuture(env, &req, req_id) ? st->atom_error
                                                                : st->atom_ok;
}

static ERL_NIF_TERM
ReqQueryBankAccountMoneyByFuture(ErlNifEnv *env, int argc,
                                 const ERL_NIF_TERM argv[]) {
  CtpState *st = static_cast<CtpState *>(enif_priv_data(env));
  CtpTd **obj;
  NifRecord req;
  int req_id;

  if (argc != 3 ||
      !enif_get_resource(env, argv[0], st->res_td,
                         reinterpret_cast<void **>(&obj)) ||
      !enif_get_tuple(env, argv[1], &req.arity,
                      const_cast<const ERL_NIF_TERM **>(&req.terms)) ||
      !enif_get_int(env, argv[2], &req_id)) {
    return enif_make_badarg(env);
  }

  return (*obj)->ReqQueryBankAccountMoneyByFuture(env, &req, req_id)
             ? st->atom_error
             : st->atom_ok;
}

/* -----------------------------------------------------------------------------
 * 工具函数
 * -----------------------------------------------------------------------------
 */

static void CtpTdResDtor(ErlNifEnv *env, void *obj) {
  delete *(static_cast<CtpTd **>(obj));
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

  st->res_td = enif_open_resource_type(
      env, NULL, "ctp_td", CtpTdResDtor,
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
    {"subscribe_private_topic", 2, SubscribePrivateTopic},
    {"subscribe_public_topic", 2, SubscribePublicTopic},
    {"req_authenticate", 3, ReqAuthenticate},
    {"req_user_login", 3, ReqUserLogin},
    {"req_user_logout", 3, ReqUserLogout},
    {"req_user_password_update", 3, ReqUserPasswordUpdate},
    {"req_trading_account_password_update", 3, ReqTradingAccountPasswordUpdate},
    {"req_order_insert", 3, ReqOrderInsert},
    {"req_parked_order_insert", 3, ReqParkedOrderInsert},
    {"req_parked_order_action", 3, ReqParkedOrderAction},
    {"req_order_action", 3, ReqOrderAction},
    {"req_query_max_order_volume", 3, ReqQueryMaxOrderVolume},
    {"req_settlement_info_confirm", 3, ReqSettlementInfoConfirm},
    {"req_remove_parked_order", 3, ReqRemoveParkedOrder},
    {"req_remove_parked_order_action", 3, ReqRemoveParkedOrderAction},
    {"req_exec_order_insert", 3, ReqExecOrderInsert},
    {"req_exec_order_action", 3, ReqExecOrderAction},
    {"req_for_quote_insert", 3, ReqForQuoteInsert},
    {"req_quote_insert", 3, ReqQuoteInsert},
    {"req_quote_action", 3, ReqQuoteAction},
    {"req_lock_insert", 3, ReqLockInsert},
    {"req_batch_order_action", 3, ReqBatchOrderAction},
    {"req_comb_action_insert", 3, ReqCombActionInsert},
    {"req_qry_order", 3, ReqQryOrder},
    {"req_qry_trade", 3, ReqQryTrade},
    {"req_qry_investor_position", 3, ReqQryInvestorPosition},
    {"req_qry_trading_account", 3, ReqQryTradingAccount},
    {"req_qry_investor", 3, ReqQryInvestor},
    {"req_qry_trading_code", 3, ReqQryTradingCode},
    {"req_qry_instrument_margin_rate", 3, ReqQryInstrumentMarginRate},
    {"req_qry_instrument_commission_rate", 3, ReqQryInstrumentCommissionRate},
    {"req_qry_exchange", 3, ReqQryExchange},
    {"req_qry_product", 3, ReqQryProduct},
    {"req_qry_instrument", 3, ReqQryInstrument},
    {"req_qry_depth_market_data", 3, ReqQryDepthMarketData},
    {"req_qry_settlement_info", 3, ReqQrySettlementInfo},
    {"req_qry_transfer_bank", 3, ReqQryTransferBank},
    {"req_qry_investor_position_detail", 3, ReqQryInvestorPositionDetail},
    {"req_qry_notice", 3, ReqQryNotice},
    {"req_qry_settlement_info_confirm", 3, ReqQrySettlementInfoConfirm},
    {"req_qry_investor_position_combine_detail", 3,
     ReqQryInvestorPositionCombineDetail},
    {"req_qry_cfmmctrading_account_key", 3, ReqQryCFMMCTradingAccountKey},
    {"req_qry_ewarrant_offset", 3, ReqQryEWarrantOffset},
    {"req_qry_investor_product_group_margin", 3,
     ReqQryInvestorProductGroupMargin},
    {"req_qry_exchange_margin_rate", 3, ReqQryExchangeMarginRate},
    {"req_qry_exchange_margin_rate_adjust", 3, ReqQryExchangeMarginRateAdjust},
    {"req_qry_exchange_rate", 3, ReqQryExchangeRate},
    {"req_qry_sec_agent_acidmap", 3, ReqQrySecAgentACIDMap},
    {"req_qry_product_exch_rate", 3, ReqQryProductExchRate},
    {"req_qry_product_group", 3, ReqQryProductGroup},
    {"req_qry_mminstrument_commission_rate", 3,
     ReqQryMMInstrumentCommissionRate},
    {"req_qry_mmoption_instr_comm_rate", 3, ReqQryMMOptionInstrCommRate},
    {"req_qry_instrument_order_comm_rate", 3, ReqQryInstrumentOrderCommRate},
    {"req_qry_option_instr_trade_cost", 3, ReqQryOptionInstrTradeCost},
    {"req_qry_option_instr_comm_rate", 3, ReqQryOptionInstrCommRate},
    {"req_qry_exec_order", 3, ReqQryExecOrder},
    {"req_qry_for_quote", 3, ReqQryForQuote},
    {"req_qry_quote", 3, ReqQryQuote},
    {"req_qry_lock", 3, ReqQryLock},
    {"req_qry_lock_position", 3, ReqQryLockPosition},
    {"req_qry_etfoption_instr_comm_rate", 3, ReqQryETFOptionInstrCommRate},
    {"req_qry_investor_level", 3, ReqQryInvestorLevel},
    {"req_qry_exec_freeze", 3, ReqQryExecFreeze},
    {"req_qry_comb_instrument_guard", 3, ReqQryCombInstrumentGuard},
    {"req_qry_comb_action", 3, ReqQryCombAction},
    {"req_qry_transfer_serial", 3, ReqQryTransferSerial},
    {"req_qry_accountregister", 3, ReqQryAccountregister},
    {"req_qry_contract_bank", 3, ReqQryContractBank},
    {"req_qry_parked_order", 3, ReqQryParkedOrder},
    {"req_qry_parked_order_action", 3, ReqQryParkedOrderAction},
    {"req_qry_trading_notice", 3, ReqQryTradingNotice},
    {"req_qry_broker_trading_params", 3, ReqQryBrokerTradingParams},
    {"req_qry_broker_trading_algos", 3, ReqQryBrokerTradingAlgos},
    {"req_query_cfmmctrading_account_token", 3,
     ReqQueryCFMMCTradingAccountToken},
    {"req_from_bank_to_future_by_future", 3, ReqFromBankToFutureByFuture},
    {"req_from_future_to_bank_by_future", 3, ReqFromFutureToBankByFuture},
    {"req_query_bank_account_money_by_future", 3,
     ReqQueryBankAccountMoneyByFuture}};

ERL_NIF_INIT(ctp_td_nif, nif_funcs, Load, NULL, Upgrade, Unload)
