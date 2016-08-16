/*
 * Copyright (c) 2014 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include <pthread.h>

#include "irt_syscalls.h"
#include "ppapi/c/pp_module.h"
#include "ppapi/c/ppp.h"

struct PP_StartFunctions {
  int32_t (*PPP_InitializeModule)(PP_Module module_id,
                                  PPB_GetInterface get_browser_interface);
  void (*PPP_ShutdownModule)();
  const void* (*PPP_GetInterface)(const char* interface_name);
};

struct PP_ThreadFunctions {
  int (*thread_create)(uintptr_t* tid,
                       void (*func)(void* thread_argument),
                       void* thread_argument);
  int (*thread_join)(uintptr_t tid);
};

#define NACL_IRT_PPAPIHOOK_v0_1 "nacl-irt-ppapihook-0.1"
struct nacl_irt_ppapihook {
  int (*ppapi_start)(const struct PP_StartFunctions*);
  void (*ppapi_register_thread_creator)(const struct PP_ThreadFunctions*);
};


static int thread_create(uintptr_t *tid,
                         void (*func)(void *thread_argument),
                         void *thread_argument) {
  return pthread_create((pthread_t *) tid, NULL,
                        (void *(*)(void *thread_argument)) func,
                        thread_argument);
}

static int thread_join(uintptr_t tid) {
  return pthread_join((pthread_t) tid, NULL);
}

static const struct PP_StartFunctions ppapi_app_start_callbacks = {
  PPP_InitializeModule,
  PPP_ShutdownModule,
  PPP_GetInterface
};

const static struct PP_ThreadFunctions thread_funcs = {
  thread_create,
  thread_join
};

static void fatal_error(const char *message) {
  write(2, message, strlen(message));
  _exit(127);
}

void __nacl_register_thread_creator(const struct nacl_irt_ppapihook *hooks) {
  hooks->ppapi_register_thread_creator(&thread_funcs);
}

int PpapiPluginStart(const struct PP_StartFunctions *funcs) {
  struct nacl_irt_ppapihook hooks;
  if (sizeof(hooks) != __nacl_irt_query(NACL_IRT_PPAPIHOOK_v0_1,
                                        &hooks, sizeof(hooks))) {
    fatal_error("PpapiPluginStart: PPAPI hooks not found\n");
  }

  __nacl_register_thread_creator(&hooks);
  return hooks.ppapi_start(funcs);
}


int PpapiPluginMain(void) {
  return PpapiPluginStart(&ppapi_app_start_callbacks);
}
