// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_MEDIA_CDM_BROWSER_CDM_MANAGER_H_
#define CONTENT_BROWSER_MEDIA_CDM_BROWSER_CDM_MANAGER_H_

#include <map>
#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/containers/scoped_ptr_hash_map.h"
#include "base/memory/scoped_ptr.h"
#include "content/common/content_export.h"
#include "content/common/media/cdm_messages_enums.h"
#include "content/public/browser/browser_message_filter.h"
#include "ipc/ipc_message.h"
#include "media/base/media_keys.h"
#include "url/gurl.h"

namespace media {
class BrowserCdm;
}

namespace content {

class CONTENT_EXPORT BrowserCdmManager : public BrowserMessageFilter {
 public:
  
  
  static BrowserCdmManager* FromProcess(int render_process_id);

  
  
  
  
  BrowserCdmManager(int render_process_id,
                    const scoped_refptr<base::TaskRunner>& task_runner);

  
  virtual void OnDestruct() const OVERRIDE;
  virtual base::TaskRunner* OverrideTaskRunnerForMessage(
      const IPC::Message& message) OVERRIDE;
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;

  media::BrowserCdm* GetCdm(int render_frame_id, int cdm_id);

  
  
  
  
  void RenderFrameDeleted(int render_frame_id);

 protected:
  friend class base::RefCountedThreadSafe<BrowserCdmManager>;
  friend class base::DeleteHelper<BrowserCdmManager>;
  virtual ~BrowserCdmManager();

 private:
  
  void OnSessionCreated(int render_frame_id,
                        int cdm_id,
                        uint32 session_id,
                        const std::string& web_session_id);
  void OnSessionMessage(int render_frame_id,
                        int cdm_id,
                        uint32 session_id,
                        const std::vector<uint8>& message,
                        const GURL& destination_url);
  void OnSessionReady(int render_frame_id, int cdm_id, uint32 session_id);
  void OnSessionClosed(int render_frame_id, int cdm_id, uint32 session_id);
  void OnSessionError(int render_frame_id,
                      int cdm_id,
                      uint32 session_id,
                      media::MediaKeys::KeyError error_code,
                      uint32 system_code);

  
  void OnInitializeCdm(int render_frame_id,
                       int cdm_id,
                       const std::string& key_system,
                       const GURL& frame_url);
  void OnCreateSession(int render_frame_id,
                       int cdm_id,
                       uint32 session_id,
                       CdmHostMsg_CreateSession_ContentType content_type,
                       const std::vector<uint8>& init_data);
  void OnUpdateSession(int render_frame_id,
                       int cdm_id,
                       uint32 session_id,
                       const std::vector<uint8>& response);
  void OnReleaseSession(int render_frame_id,
                        int cdm_id, uint32 session_id);
  void OnDestroyCdm(int render_frame_id, int cdm_id);

  void SendSessionError(int render_frame_id, int cdm_id, uint32 session_id);

  
  
  void AddCdm(int render_frame_id,
              int cdm_id,
              const std::string& key_system,
              const GURL& security_origin);

  
  void RemoveCdm(uint64 id);

  
  
  
  
  
  void CreateSessionIfPermitted(int render_frame_id,
                                int cdm_id,
                                uint32 session_id,
                                const std::string& content_type,
                                const std::vector<uint8>& init_data,
                                bool permitted);

  const int render_process_id_;

  
  
  scoped_refptr<base::TaskRunner> task_runner_;

  
  

  
  typedef base::ScopedPtrHashMap<uint64, media::BrowserCdm> CdmMap;
  CdmMap cdm_map_;

  
  std::map<uint64, GURL> cdm_security_origin_map_;

  
  std::map<uint64, base::Closure> cdm_cancel_permission_map_;

  DISALLOW_COPY_AND_ASSIGN(BrowserCdmManager);
};

}  

#endif  
