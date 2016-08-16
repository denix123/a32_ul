// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef NATIVE_CLIENT_SRC_TRUSTED_PLUGIN_PLUGIN_H_
#define NATIVE_CLIENT_SRC_TRUSTED_PLUGIN_PLUGIN_H_

#include <stdio.h>

#include <string>

#include "native_client/src/include/nacl_macros.h"
#include "native_client/src/include/nacl_scoped_ptr.h"

#include "ppapi/c/private/ppb_nacl_private.h"
#include "ppapi/cpp/instance.h"
#include "ppapi/cpp/private/uma_private.h"
#include "ppapi/cpp/url_loader.h"
#include "ppapi/cpp/var.h"
#include "ppapi/cpp/view.h"

#include "ppapi/native_client/src/trusted/plugin/nacl_subprocess.h"
#include "ppapi/native_client/src/trusted/plugin/pnacl_coordinator.h"
#include "ppapi/native_client/src/trusted/plugin/service_runtime.h"
#include "ppapi/native_client/src/trusted/plugin/utility.h"

#include "ppapi/utility/completion_callback_factory.h"

namespace nacl {
class DescWrapper;
class DescWrapperFactory;
}  

namespace pp {
class CompletionCallback;
class URLLoader;
class URLUtil_Dev;
}

namespace plugin {

class ErrorInfo;
class Manifest;

int32_t ConvertFileDescriptor(PP_FileHandle handle);

const PP_NaClFileInfo kInvalidNaClFileInfo = {
  PP_kInvalidFileHandle,
  0,  
  0,  
};

class Plugin : public pp::Instance {
 public:
  explicit Plugin(PP_Instance instance);

  

  
  
  
  virtual bool Init(uint32_t argc, const char* argn[], const char* argv[]);

  
  virtual bool HandleDocumentLoad(const pp::URLLoader& url_loader);

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  void LoadNaClModule(PP_NaClFileInfo file_info,
                      bool uses_nonsfi_mode,
                      bool enable_dyncode_syscalls,
                      bool enable_exception_handling,
                      bool enable_crash_throttling,
                      const pp::CompletionCallback& init_done_cb);

  
  
  bool LoadNaClModuleContinuationIntern();

  
  
  
  
  
  
  bool LoadNaClModuleContinuation(int32_t pp_error);

  
  
  
  
  
  NaClSubprocess* LoadHelperNaClModule(const std::string& helper_url,
                                       PP_NaClFileInfo file_info,
                                       ErrorInfo* error_info);

  
  void ReportLoadError(const ErrorInfo& error_info);

  nacl::DescWrapperFactory* wrapper_factory() const { return wrapper_factory_; }

  const PPB_NaCl_Private* nacl_interface() const { return nacl_interface_; }
  pp::UMAPrivate& uma_interface() { return uma_interface_; }

 private:
  NACL_DISALLOW_COPY_AND_ASSIGN(Plugin);
  
  
  ~Plugin();

  
  
  void ShutDownSubprocesses();

  
  
  void HistogramTimeSmall(const std::string& name, int64_t ms);

  
  
  
  
  bool LoadHelperNaClModuleInternal(NaClSubprocess* subprocess,
                                    const SelLdrStartParams& params);

  
  
  void StartSelLdrOnMainThread(int32_t pp_error,
                               ServiceRuntime* service_runtime,
                               const SelLdrStartParams& params,
                               pp::CompletionCallback callback);

  
  
  void SignalStartSelLdrDone(int32_t pp_error,
                             bool* started,
                             ServiceRuntime* service_runtime);

  
  void StartNexe(int32_t pp_error, ServiceRuntime* service_runtime);

  
  
  
  void NexeFileDidOpen(int32_t pp_error);
  void NexeFileDidOpenContinuation(int32_t pp_error);

  
  
  
  void BitcodeDidTranslate(int32_t pp_error);
  void BitcodeDidTranslateContinuation(int32_t pp_error);

  
  
  
  
  

  
  void NaClManifestFileDidOpen(int32_t pp_error);

  
  void ProcessNaClManifest(const std::string& manifest_json);

  
  NaClSubprocess main_subprocess_;

  bool uses_nonsfi_mode_;

  nacl::DescWrapperFactory* wrapper_factory_;

  pp::CompletionCallbackFactory<Plugin> callback_factory_;

  nacl::scoped_ptr<PnaclCoordinator> pnacl_coordinator_;

  int exit_status_;

  PP_NaClFileInfo nexe_file_info_;

  const PPB_NaCl_Private* nacl_interface_;
  pp::UMAPrivate uma_interface_;
};

}  

#endif  
