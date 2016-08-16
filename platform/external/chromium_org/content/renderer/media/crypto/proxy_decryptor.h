// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_MEDIA_CRYPTO_PROXY_DECRYPTOR_H_
#define CONTENT_RENDERER_MEDIA_CRYPTO_PROXY_DECRYPTOR_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/containers/hash_tables.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "media/base/decryptor.h"
#include "media/base/media_keys.h"

#if defined(ENABLE_PEPPER_CDMS)
#include "content/renderer/media/crypto/pepper_cdm_wrapper.h"
#endif

class GURL;

namespace content {

#if defined(ENABLE_BROWSER_CDMS)
class RendererCdmManager;
#endif  

class ProxyDecryptor {
 public:
  
  
  typedef base::Callback<void(const std::string& session_id)> KeyAddedCB;
  typedef base::Callback<void(const std::string& session_id,
                              media::MediaKeys::KeyError error_code,
                              uint32 system_code)> KeyErrorCB;
  typedef base::Callback<void(const std::string& session_id,
                              const std::vector<uint8>& message,
                              const GURL& destination_url)> KeyMessageCB;

  ProxyDecryptor(
#if defined(ENABLE_PEPPER_CDMS)
      const CreatePepperCdmCB& create_pepper_cdm_cb,
#elif defined(ENABLE_BROWSER_CDMS)
      RendererCdmManager* manager,
#endif  
      const KeyAddedCB& key_added_cb,
      const KeyErrorCB& key_error_cb,
      const KeyMessageCB& key_message_cb);
  virtual ~ProxyDecryptor();

  
  
  media::Decryptor* GetDecryptor();

#if defined(ENABLE_BROWSER_CDMS)
  
  
  int GetCdmId();
#endif

  
  bool InitializeCDM(const std::string& key_system,
                     const GURL& security_origin);

  
  bool GenerateKeyRequest(const std::string& type,
                          const uint8* init_data,
                          int init_data_length);
  void AddKey(const uint8* key, int key_length,
              const uint8* init_data, int init_data_length,
              const std::string& session_id);
  void CancelKeyRequest(const std::string& session_id);

 private:
  
  scoped_ptr<media::MediaKeys> CreateMediaKeys(const std::string& key_system,
                                               const GURL& security_origin);

  
  void OnSessionMessage(const std::string& web_session_id,
                        const std::vector<uint8>& message,
                        const GURL& default_url);
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

  enum SessionCreationType {
    TemporarySession,
    PersistentSession,
    LoadSession
  };

  
  void SetSessionId(SessionCreationType session_type,
                    const std::string& web_session_id);

#if defined(ENABLE_PEPPER_CDMS)
  
  CreatePepperCdmCB create_pepper_cdm_cb_;
#elif defined(ENABLE_BROWSER_CDMS)
  RendererCdmManager* manager_;
  int cdm_id_;
#endif  

  
  scoped_ptr<media::MediaKeys> media_keys_;

  
  KeyAddedCB key_added_cb_;
  KeyErrorCB key_error_cb_;
  KeyMessageCB key_message_cb_;

  
  base::hash_map<std::string, bool> active_sessions_;

  bool is_clear_key_;

  
  base::WeakPtrFactory<ProxyDecryptor> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(ProxyDecryptor);
};

}  

#endif  
