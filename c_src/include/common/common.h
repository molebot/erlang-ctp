#ifndef COMMON_H
#define COMMON_H

#include "erl_nif.h"
#include <iconv.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>

/* -----------------------------------------------------------------------------
 * 宏定义
 * -----------------------------------------------------------------------------
 */

#define MAX_BUF_LEN 4096

/* -----------------------------------------------------------------------------
 * 结构体定义
 * -----------------------------------------------------------------------------
 */

struct NifRecord {
  int arity;
  ERL_NIF_TERM *terms;
};

/* -----------------------------------------------------------------------------
 * Nif转换函数
 * -----------------------------------------------------------------------------
 */

static inline void ErlNifGetString(ErlNifEnv *env, const NifRecord *req,
                                   int nth, size_t size, char *data) {
  if (nth < req->arity) {
    ErlNifBinary bin;
    if (enif_inspect_binary(env, req->terms[nth], &bin)) {
      if (bin.size) {
        std::string str(reinterpret_cast<char *>(bin.data), bin.size);
        snprintf(data, size, "%s", const_cast<char *>(str.c_str()));
      }
    }
  }
}

static inline void ErlNifGetChar(ErlNifEnv *env, const NifRecord *req, int nth,
                                 char *data) {
  if (nth < req->arity) {
    ErlNifBinary bin;
    if (enif_inspect_binary(env, req->terms[nth], &bin)) {
      if (bin.size) {
        data[0] = bin.data[0];
      }
    }
  }
}

static inline void ErlNifGetDouble(ErlNifEnv *env, const NifRecord *req,
                                   int nth, double *data) {
  if (nth < req->arity) {
    enif_get_double(env, req->terms[nth], data);
  }
}

static inline void ErlNifGetInt(ErlNifEnv *env, const NifRecord *req, int nth,
                                int *data) {
  if (nth < req->arity) {
    enif_get_int(env, req->terms[nth], data);
  }
}

static inline ERL_NIF_TERM ErlNifMakeGbkBinary(ErlNifEnv *env, char *str) {
  iconv_t cd = iconv_open("utf-8", "gb2312");
  if (cd != reinterpret_cast<iconv_t>(-1)) {
    char buf[MAX_BUF_LEN];
    char **in = &str;
    char *out = buf;
    size_t inlen = strlen(str), outlen = MAX_BUF_LEN;

    if (iconv(cd, in, &inlen, &out, &outlen) != static_cast<size_t>(-1)) {
      iconv_close(cd);

      ERL_NIF_TERM term;
      size_t len = MAX_BUF_LEN - outlen;
      memcpy(enif_make_new_binary(env, len, &term), buf, len);
      return term;
    } else {
      iconv_close(cd);
    }
  }

  ERL_NIF_TERM term;
  memcpy(enif_make_new_binary(env, strlen(str), &term), str, strlen(str));
  return term;
}

static inline ERL_NIF_TERM ErlNifMakeGbkBinary(ErlNifEnv *env, char ch) {
  ERL_NIF_TERM term;
  memcpy(enif_make_new_binary(env, 1, &term), &ch, 1);
  return term;
}

#endif /* COMMON_H */
