// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_RENDERER_PEPPER_PNACL_TRANSLATION_RESOURCE_HOST_H_
#define CHROME_RENDERER_PEPPER_PNACL_TRANSLATION_RESOURCE_HOST_H_

#include <map>

#include "base/callback.h"
#include "base/message_loop/message_loop_proxy.h"
#include "ipc/ipc_platform_file.h"
#include "ipc/message_filter.h"
#include "ppapi/c/pp_bool.h"
#include "ppapi/c/pp_instance.h"
#include "ppapi/c/private/pp_file_handle.h"

namespace nacl {
struct PnaclCacheInfo;
}


class PnaclTranslationResourceHost : public IPC::MessageFilter {
 public:
  typedef base::Callback<void(int32_t, bool, PP_FileHandle)>
          RequestNexeFdCallback;

  explicit PnaclTranslationResourceHost(
      const scoped_refptr<base::MessageLoopProxy>& io_message_loop);
  void RequestNexeFd(int render_view_id,
                     PP_Instance instance,
                     const nacl::PnaclCacheInfo& cache_info,
                     RequestNexeFdCallback callback);
  void ReportTranslationFinished(PP_Instance instance, PP_Bool success);

 protected:
  virtual ~PnaclTranslationResourceHost();

 private:
  
  
  typedef std::map<PP_Instance, RequestNexeFdCallback> CacheRequestInfoMap;

  
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;
  virtual void OnFilterAdded(IPC::Sender* sender) OVERRIDE;
  virtual void OnFilterRemoved() OVERRIDE;
  virtual void OnChannelClosing() OVERRIDE;

  void SendRequestNexeFd(int render_view_id,
                         PP_Instance instance,
                         const nacl::PnaclCacheInfo& cache_info,
                         RequestNexeFdCallback callback);
  void SendReportTranslationFinished(PP_Instance instance,
                                     PP_Bool success);
  void OnNexeTempFileReply(PP_Instance instance,
                           bool is_hit,
                           IPC::PlatformFileForTransit file);
  void CleanupCacheRequests();

  scoped_refptr<base::MessageLoopProxy> io_message_loop_;

  
  IPC::Sender* sender_;
  CacheRequestInfoMap pending_cache_requests_;
  DISALLOW_COPY_AND_ASSIGN(PnaclTranslationResourceHost);
};

#endif  
