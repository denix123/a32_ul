// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NATIVE_CLIENT_SRC_TRUSTED_PLUGIN_PNACL_TRANSLATE_THREAD_H_
#define NATIVE_CLIENT_SRC_TRUSTED_PLUGIN_PNACL_TRANSLATE_THREAD_H_

#include <deque>
#include <vector>

#include "native_client/src/include/nacl_macros.h"
#include "native_client/src/include/nacl_scoped_ptr.h"
#include "native_client/src/shared/platform/nacl_threads.h"
#include "native_client/src/shared/platform/nacl_sync_checked.h"

#include "ppapi/cpp/completion_callback.h"

#include "ppapi/native_client/src/trusted/plugin/plugin_error.h"
#include "ppapi/native_client/src/trusted/plugin/service_runtime.h"

struct PP_PNaClOptions;

namespace nacl {
class DescWrapper;
}


namespace plugin {

class NaClSubprocess;
class Plugin;
class PnaclCoordinator;
class PnaclResources;
class TempFile;

class PnaclTranslateThread {
 public:
  PnaclTranslateThread();
  ~PnaclTranslateThread();

  
  
  void RunTranslate(const pp::CompletionCallback& finish_callback,
                    const std::vector<TempFile*>* obj_files,
                    TempFile* nexe_file,
                    nacl::DescWrapper* invalid_desc_wrapper,
                    ErrorInfo* error_info,
                    PnaclResources* resources,
                    PP_PNaClOptions* pnacl_options,
                    const std::string &architecture_attributes,
                    PnaclCoordinator* coordinator,
                    Plugin* plugin);

  
  
  
  
  
  
  void AbortSubprocesses();

  
  void PutBytes(const void* data, int count);

  
  
  void EndStream();

  int64_t GetCompileTime() const { return compile_time_; }

  
  bool started() const { return plugin_ != NULL; }

 private:
  
  
  static void WINAPI DoTranslateThread(void* arg);
  
  void DoTranslate() ;
  
  void TranslateFailed(PP_NaClError err_code,
                       const std::string& error_string);
  
  
  bool RunLdSubprocess();


  
  pp::CompletionCallback report_translate_finished_;

  nacl::scoped_ptr<NaClThread> translate_thread_;

  
  struct NaClMutex subprocess_mu_;
  nacl::scoped_ptr<NaClSubprocess> llc_subprocess_;
  nacl::scoped_ptr<NaClSubprocess> ld_subprocess_;
  
  bool llc_subprocess_active_;
  bool ld_subprocess_active_;

  bool subprocesses_aborted_;

  
  
  
  
  struct NaClCondVar buffer_cond_;
  
  struct NaClMutex cond_mu_;
  
  
  std::deque<std::vector<char> > data_buffers_;
  
  
  bool done_;

  int64_t compile_time_;

  
  const std::vector<TempFile*>* obj_files_;
  TempFile* nexe_file_;
  nacl::DescWrapper* invalid_desc_wrapper_;
  ErrorInfo* coordinator_error_info_;
  PnaclResources* resources_;
  PP_PNaClOptions* pnacl_options_;
  std::string architecture_attributes_;
  PnaclCoordinator* coordinator_;
  Plugin* plugin_;
 private:
  NACL_DISALLOW_COPY_AND_ASSIGN(PnaclTranslateThread);
};

}
#endif 
