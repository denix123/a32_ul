// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NATIVE_CLIENT_SRC_TRUSTED_PLUGIN_PNACL_COORDINATOR_H_
#define NATIVE_CLIENT_SRC_TRUSTED_PLUGIN_PNACL_COORDINATOR_H_

#include <vector>

#include "native_client/src/include/nacl_macros.h"
#include "native_client/src/shared/platform/nacl_sync_raii.h"
#include "native_client/src/shared/srpc/nacl_srpc.h"
#include "native_client/src/trusted/desc/nacl_desc_wrapper.h"

#include "ppapi/cpp/completion_callback.h"

#include "ppapi/native_client/src/trusted/plugin/nacl_subprocess.h"
#include "ppapi/native_client/src/trusted/plugin/plugin_error.h"
#include "ppapi/native_client/src/trusted/plugin/pnacl_resources.h"

#include "ppapi/utility/completion_callback_factory.h"

struct PP_PNaClOptions;

namespace plugin {

class Plugin;
class PnaclCoordinator;
class PnaclTranslateThread;
class TempFile;

class PnaclCoordinator {
 public:
  
  
  const static size_t kMaxTranslatorObjectFiles = 16;
  virtual ~PnaclCoordinator();

  
  static PnaclCoordinator* BitcodeToNative(
      Plugin* plugin,
      const std::string& pexe_url,
      const PP_PNaClOptions& pnacl_options,
      const pp::CompletionCallback& translate_notify_callback);

  
  
  PP_FileHandle TakeTranslatedFileHandle();

  
  
  pp::CompletionCallback GetCompileProgressCallback(int64_t bytes_compiled);

  
  void GetCurrentProgress(int64_t* bytes_loaded, int64_t* bytes_total);

  
  
  
  
  bool ShouldDelayProgressEvent() {
    const uint32_t kProgressEventSlopPct = 5;
    return ((expected_pexe_size_ - pexe_bytes_compiled_) * 100 /
            expected_pexe_size_) < kProgressEventSlopPct;
  }


  void BitcodeStreamCacheHit(PP_FileHandle handle);
  void BitcodeStreamCacheMiss(int64_t expected_pexe_size,
                              PP_FileHandle handle);

  
  void BitcodeStreamGotData(const void* data, int32_t length);

  
  void BitcodeStreamDidFinish(int32_t pp_error);

 private:
  NACL_DISALLOW_COPY_AND_ASSIGN(PnaclCoordinator);

  
  
  PnaclCoordinator(Plugin* plugin,
                   const std::string& pexe_url,
                   const PP_PNaClOptions& pnacl_options,
                   const pp::CompletionCallback& translate_notify_callback);

  
  void OpenBitcodeStream();

  
  void BitcodeGotCompiled(int32_t pp_error, int64_t bytes_compiled);
  
  
  
  void RunTranslate(int32_t pp_error);

  
  void TranslateFinished(int32_t pp_error);

  
  void NexeReadDidOpen(int32_t pp_error);

  
  
  
  void ExitWithError();
  
  
  void ReportNonPpapiError(PP_NaClError err, const std::string& message);
  
  
  
  void ReportPpapiError(PP_NaClError err,
                        int32_t pp_error, const std::string& message);


  
  
  int32_t translate_finish_error_;

  
  Plugin* plugin_;

  pp::CompletionCallback translate_notify_callback_;
  
  
  
  
  
  bool translation_finished_reported_;
  
  pp::CompletionCallbackFactory<PnaclCoordinator,
                                pp::ThreadSafeThreadTraits> callback_factory_;

  
  nacl::scoped_ptr<PnaclResources> resources_;

  
  std::string pexe_url_;
  
  PP_PNaClOptions pnacl_options_;
  
  
  
  std::string architecture_attributes_;

  
  std::vector<TempFile*> obj_files_;
  nacl::scoped_ptr<nacl::DescWrapper> invalid_desc_wrapper_;
  
  int split_module_count_;

  
  nacl::scoped_ptr<TempFile> temp_nexe_file_;

  
  ErrorInfo error_info_;

  
  
  bool error_already_reported_;

  
  int64_t pexe_size_;  
  int64_t pexe_bytes_compiled_;  
  int64_t expected_pexe_size_;   

  
  
  
  nacl::scoped_ptr<PnaclTranslateThread> translate_thread_;
};


}  
#endif  
