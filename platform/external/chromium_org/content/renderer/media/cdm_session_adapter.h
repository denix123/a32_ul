// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_MEDIA_CDM_SESSION_ADAPTER_H_
#define CONTENT_RENDERER_MEDIA_CDM_SESSION_ADAPTER_H_

#include <map>
#include <string>

#include "base/basictypes.h"
#include "base/containers/hash_tables.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "media/base/media_keys.h"
#include "third_party/WebKit/public/platform/WebContentDecryptionModuleSession.h"

#if defined(ENABLE_PEPPER_CDMS)
#include "content/renderer/media/crypto/pepper_cdm_wrapper.h"
#endif

class GURL;

namespace content {

#if defined(ENABLE_BROWSER_CDMS)
class RendererCdmManager;
#endif

class WebContentDecryptionModuleSessionImpl;

class CdmSessionAdapter : public base::RefCounted<CdmSessionAdapter> {
 public:
  CdmSessionAdapter();

  
  bool Initialize(
#if defined(ENABLE_PEPPER_CDMS)
      const CreatePepperCdmCB& create_pepper_cdm_cb,
#elif defined(ENABLE_BROWSER_CDMS)
      RendererCdmManager* manager,
#endif
      const std::string& key_system,
      const GURL& security_origin);

  
  // license server.
  void SetServerCertificate(const uint8* server_certificate,
                            int server_certificate_length,
                            scoped_ptr<media::SimpleCdmPromise> promise);

  
  
  
  WebContentDecryptionModuleSessionImpl* CreateSession();

  
  
  
  bool RegisterSession(
      const std::string& web_session_id,
      base::WeakPtr<WebContentDecryptionModuleSessionImpl> session);

  
  void UnregisterSession(const std::string& web_session_id);

  
  
  void InitializeNewSession(const std::string& init_data_type,
                            const uint8* init_data,
                            int init_data_length,
                            media::MediaKeys::SessionType session_type,
                            scoped_ptr<media::NewSessionCdmPromise> promise);

  
  void UpdateSession(const std::string& web_session_id,
                     const uint8* response,
                     int response_length,
                     scoped_ptr<media::SimpleCdmPromise> promise);

  
  void CloseSession(const std::string& web_session_id,
                    scoped_ptr<media::SimpleCdmPromise> promise);

  
  
  void RemoveSession(const std::string& web_session_id,
                     scoped_ptr<media::SimpleCdmPromise> promise);

  
  
  void GetUsableKeyIds(const std::string& web_session_id,
                       scoped_ptr<media::KeyIdsPromise> promise);

  
  
  
  
  media::Decryptor* GetDecryptor();

  
  const std::string& GetKeySystemUMAPrefix() const;

#if defined(ENABLE_BROWSER_CDMS)
  
  
  int GetCdmId() const;
#endif

 private:
  friend class base::RefCounted<CdmSessionAdapter>;
  typedef base::hash_map<std::string,
                         base::WeakPtr<WebContentDecryptionModuleSessionImpl> >
      SessionMap;

  ~CdmSessionAdapter();

  
  void OnSessionMessage(const std::string& web_session_id,
                        const std::vector<uint8>& message,
                        const GURL& destination_url);
  void OnSessionKeysChange(const std::string& web_session_id,
                           bool has_additional_usable_key);
  void OnSessionExpirationUpdate(const std::string& web_session_id,
                                 const base::Time& new_expiry_time);
  void OnSessionReady(const std::string& web_session_id);
  void OnSessionClosed(const std::string& web_session_id);
  void OnSessionError(const std::string& web_session_id,
                      media::MediaKeys::Exception exception_code,
                      uint32 system_code,
                      const std::string& error_message);

  
  WebContentDecryptionModuleSessionImpl* GetSession(
      const std::string& web_session_id);

  scoped_ptr<media::MediaKeys> media_keys_;

  SessionMap sessions_;

#if defined(ENABLE_BROWSER_CDMS)
  int cdm_id_;
#endif

  std::string key_system_uma_prefix_;

  
  base::WeakPtrFactory<CdmSessionAdapter> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(CdmSessionAdapter);
};

}  

#endif  
