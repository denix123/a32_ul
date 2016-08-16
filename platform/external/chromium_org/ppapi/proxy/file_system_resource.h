// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PPAPI_PROXY_FILE_SYSTEM_RESOURCE_H_
#define PPAPI_PROXY_FILE_SYSTEM_RESOURCE_H_

#include <map>
#include <queue>
#include <string>

#include "base/memory/ref_counted.h"
#include "ppapi/c/pp_file_info.h"
#include "ppapi/c/pp_resource.h"
#include "ppapi/c/private/ppb_isolated_file_system_private.h"
#include "ppapi/proxy/connection.h"
#include "ppapi/proxy/plugin_resource.h"
#include "ppapi/proxy/ppapi_proxy_export.h"
#include "ppapi/proxy/resource_message_params.h"
#include "ppapi/thunk/ppb_file_system_api.h"

namespace ppapi {

class TrackedCallback;

namespace proxy {

class PPAPI_PROXY_EXPORT FileSystemResource
    : public PluginResource,
      public NON_EXPORTED_BASE(thunk::PPB_FileSystem_API) {
 public:
  
  
  FileSystemResource(Connection connection,
                     PP_Instance instance,
                     PP_FileSystemType type);
  
  
  
  FileSystemResource(Connection connection,
                     PP_Instance instance,
                     int pending_renderer_id,
                     int pending_browser_id,
                     PP_FileSystemType type);
  virtual ~FileSystemResource();

  
  virtual thunk::PPB_FileSystem_API* AsPPB_FileSystem_API() OVERRIDE;

  
  virtual int32_t Open(int64_t expected_size,
                       scoped_refptr<TrackedCallback> callback) OVERRIDE;
  virtual PP_FileSystemType GetType() OVERRIDE;
  virtual void OpenQuotaFile(PP_Resource file_io) OVERRIDE;
  virtual void CloseQuotaFile(PP_Resource file_io) OVERRIDE;
  typedef base::Callback<void(int64_t)> RequestQuotaCallback;
  virtual int64_t RequestQuota(int64_t amount,
                               const RequestQuotaCallback& callback) OVERRIDE;

  int32_t InitIsolatedFileSystem(const std::string& fsid,
                                 PP_IsolatedFileSystemType_Private type,
                                 const base::Callback<void(int32_t)>& callback);
 private:
  struct QuotaRequest {
    QuotaRequest(int64_t amount,
                 const RequestQuotaCallback& callback);
    ~QuotaRequest();

    int64_t amount;
    RequestQuotaCallback callback;
  };

  
  void OpenComplete(scoped_refptr<TrackedCallback> callback,
                    const ResourceMessageReplyParams& params);

  
  void InitIsolatedFileSystemComplete(
      const base::Callback<void(int32_t)>& callback,
      const ResourceMessageReplyParams& params);

  void ReserveQuota(int64_t amount);
  typedef std::map<int32_t, int64_t> OffsetMap;
  void ReserveQuotaComplete(const ResourceMessageReplyParams& params,
                            int64_t amount,
                            const OffsetMap& max_written_offsets);

  PP_FileSystemType type_;
  bool called_open_;
  uint32_t callback_count_;
  int32_t callback_result_;

  std::set<PP_Resource> files_;
  std::queue<QuotaRequest> pending_quota_requests_;
  int64_t reserved_quota_;
  bool reserving_quota_;

  DISALLOW_COPY_AND_ASSIGN(FileSystemResource);
};

}  
}  

#endif  