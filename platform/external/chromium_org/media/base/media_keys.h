// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_BASE_MEDIA_KEYS_H_
#define MEDIA_BASE_MEDIA_KEYS_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "media/base/media_export.h"
#include "url/gurl.h"

namespace base {
class Time;
}

namespace media {

class Decryptor;

template <typename T>
class CdmPromiseTemplate;

typedef CdmPromiseTemplate<std::string> NewSessionCdmPromise;
typedef CdmPromiseTemplate<void> SimpleCdmPromise;
typedef std::vector<std::vector<uint8> > KeyIdsVector;
typedef CdmPromiseTemplate<KeyIdsVector> KeyIdsPromise;

class MEDIA_EXPORT MediaKeys {
 public:
  
  
  
  
  
  enum KeyError {
    kUnknownError = 1,
    kClientError,
    
    
    kOutputError = 4,
    
    
    kMaxKeyError  
  };

  
  enum Exception {
    NOT_SUPPORTED_ERROR,
    INVALID_STATE_ERROR,
    INVALID_ACCESS_ERROR,
    QUOTA_EXCEEDED_ERROR,
    UNKNOWN_ERROR,
    CLIENT_ERROR,
    OUTPUT_ERROR
  };

  // Type of license required when creating/loading a session.
  
  
  enum SessionType {
    TEMPORARY_SESSION,
    PERSISTENT_SESSION
  };

  const static uint32 kInvalidSessionId = 0;

  MediaKeys();
  virtual ~MediaKeys();

  
  // license server.
  virtual void SetServerCertificate(const uint8* certificate_data,
                                    int certificate_data_length,
                                    scoped_ptr<SimpleCdmPromise> promise) = 0;

  
  
  
  
  virtual void CreateSession(const std::string& init_data_type,
                             const uint8* init_data,
                             int init_data_length,
                             SessionType session_type,
                             scoped_ptr<NewSessionCdmPromise> promise) = 0;

  
  
  
  virtual void LoadSession(const std::string& web_session_id,
                           scoped_ptr<NewSessionCdmPromise> promise) = 0;

  
  virtual void UpdateSession(const std::string& web_session_id,
                             const uint8* response,
                             int response_length,
                             scoped_ptr<SimpleCdmPromise> promise) = 0;

  
  virtual void CloseSession(const std::string& web_session_id,
                            scoped_ptr<SimpleCdmPromise> promise) = 0;

  
  
  virtual void RemoveSession(const std::string& web_session_id,
                             scoped_ptr<SimpleCdmPromise> promise) = 0;

  
  
  virtual void GetUsableKeyIds(const std::string& web_session_id,
                               scoped_ptr<KeyIdsPromise> promise) = 0;

  
  
  
  virtual Decryptor* GetDecryptor();

 private:
  DISALLOW_COPY_AND_ASSIGN(MediaKeys);
};

typedef base::Callback<void(const std::string& web_session_id,
                            const std::vector<uint8>& message,
                            const GURL& destination_url)> SessionMessageCB;

typedef base::Callback<void(const std::string& web_session_id)> SessionReadyCB;

typedef base::Callback<void(const std::string& web_session_id)> SessionClosedCB;

typedef base::Callback<void(const std::string& web_session_id,
                            MediaKeys::Exception exception_code,
                            uint32 system_code,
                            const std::string& error_message)> SessionErrorCB;

typedef base::Callback<void(const std::string& web_session_id,
                            bool has_additional_usable_key)>
    SessionKeysChangeCB;

typedef base::Callback<void(const std::string& web_session_id,
                            const base::Time& new_expiry_time)>
    SessionExpirationUpdateCB;

}  

#endif  
