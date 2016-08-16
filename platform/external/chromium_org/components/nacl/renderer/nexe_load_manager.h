// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_NACL_RENDERER_NEXE_LOAD_MANAGER_H_
#define COMPONENTS_NACL_RENDERER_NEXE_LOAD_MANAGER_H_

#include <map>
#include <string>

#include "base/files/file.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/shared_memory.h"
#include "base/memory/weak_ptr.h"
#include "base/time/time.h"
#include "ppapi/c/private/ppb_nacl_private.h"
#include "url/gurl.h"

namespace content {
class PepperPluginInstance;
}

namespace nacl {

class ManifestServiceChannel;
class TrustedPluginChannel;

class NexeLoadManager {
 public:
  ~NexeLoadManager();

  static void Create(PP_Instance instance);
  
  static NexeLoadManager* Get(PP_Instance instance);
  static void Delete(PP_Instance instance);

  void NexeFileDidOpen(int32_t pp_error,
                       const base::File& file,
                       int32_t http_status,
                       int64_t nexe_bytes_read,
                       const std::string& url,
                       base::TimeDelta time_since_open);
  void ReportLoadSuccess(const std::string& url,
                         uint64_t loaded_bytes,
                         uint64_t total_bytes);
  void ReportLoadError(PP_NaClError error,
                       const std::string& error_message);

  
  
  
  
  
  void ReportLoadError(PP_NaClError error,
                       const std::string& error_message,
                       const std::string& console_message);
  void ReportLoadAbort();
  void NexeDidCrash();

  
  
  
  
  
  void set_trusted_plugin_channel(scoped_ptr<TrustedPluginChannel> channel);
  void set_manifest_service_channel(
      scoped_ptr<ManifestServiceChannel> channel);

  PP_NaClReadyState nacl_ready_state();
  void set_nacl_ready_state(PP_NaClReadyState ready_state);

  void SetReadOnlyProperty(PP_Var key, PP_Var value);
  void SetLastError(const std::string& error);
  void LogToConsole(const std::string& message);

  bool is_installed() const { return is_installed_; }

  int32_t exit_status() const { return exit_status_; }
  void set_exit_status(int32_t exit_status);

  void InitializePlugin(uint32_t argc, const char* argn[], const char* argv[]);

  void ReportStartupOverhead() const;

  int64_t nexe_size() const { return nexe_size_; }

  bool RequestNaClManifest(const std::string& url);
  void ProcessNaClManifest(const std::string& program_url);

  
  
  
  const GURL& plugin_base_url() const { return plugin_base_url_; }

  
  
  const GURL& manifest_base_url() const { return manifest_base_url_; }

  
  std::string GetManifestURLArgument() const;

  
  
  bool IsPNaCl() const;

  
  bool DevInterfacesEnabled() const;

  
  base::Time pnacl_start_time() const { return pnacl_start_time_; }
  void set_pnacl_start_time(base::Time time) {
    pnacl_start_time_ = time;
  }

  const std::string& program_url() const { return program_url_; }

  void set_crash_info_shmem_handle(base::SharedMemoryHandle h) {
    crash_info_shmem_handle_ = h;
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(NexeLoadManager);

  explicit NexeLoadManager(PP_Instance instance);

  void ReportDeadNexe();

  
  void CopyCrashLogToJsConsole(const std::string& crash_log);

  PP_Instance pp_instance_;
  PP_NaClReadyState nacl_ready_state_;
  bool nexe_error_reported_;

  std::string program_url_;

  
  
  
  
  
  
  
  
  
  bool is_installed_;

  
  base::Time ready_time_;

  
  base::Time init_time_;

  
  base::Time load_start_;

  
  
  
  int32_t exit_status_;

  
  int64_t nexe_size_;

  
  content::PepperPluginInstance* plugin_instance_;

  
  GURL plugin_base_url_;

  GURL manifest_base_url_;

  
  std::map<std::string, std::string> args_;

  
  
  std::string mime_type_;

  base::Time pnacl_start_time_;

  base::SharedMemoryHandle crash_info_shmem_handle_;

  scoped_ptr<TrustedPluginChannel> trusted_plugin_channel_;
  scoped_ptr<ManifestServiceChannel> manifest_service_channel_;
  base::WeakPtrFactory<NexeLoadManager> weak_factory_;
};

}  

#endif  
