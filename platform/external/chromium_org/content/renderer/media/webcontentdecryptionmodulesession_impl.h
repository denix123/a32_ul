// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_MEDIA_WEBCONTENTDECRYPTIONMODULESESSION_IMPL_H_
#define CONTENT_RENDERER_MEDIA_WEBCONTENTDECRYPTIONMODULESESSION_IMPL_H_

#include <map>
#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "media/base/media_keys.h"
#include "third_party/WebKit/public/platform/WebContentDecryptionModuleSession.h"
#include "third_party/WebKit/public/platform/WebString.h"

namespace media {
class MediaKeys;
}

namespace content {
class CdmSessionAdapter;

class WebContentDecryptionModuleSessionImpl
    : public blink::WebContentDecryptionModuleSession {
 public:
  WebContentDecryptionModuleSessionImpl(
      const scoped_refptr<CdmSessionAdapter>& adapter);
  virtual ~WebContentDecryptionModuleSessionImpl();

  
  virtual void setClientInterface(Client* client);
  virtual blink::WebString sessionId() const;
  
  virtual void initializeNewSession(const blink::WebString& mime_type,
                                    const uint8* init_data,
                                    size_t init_data_length);
  virtual void update(const uint8* response, size_t response_length);
  virtual void release();
  virtual void initializeNewSession(
      const blink::WebString& init_data_type,
      const uint8* init_data,
      size_t init_data_length,
      const blink::WebString& session_type,
      blink::WebContentDecryptionModuleResult result);
  virtual void update(const uint8* response,
                      size_t response_length,
                      blink::WebContentDecryptionModuleResult result);
  virtual void close(blink::WebContentDecryptionModuleResult result);
  virtual void remove(blink::WebContentDecryptionModuleResult result);
  virtual void getUsableKeyIds(blink::WebContentDecryptionModuleResult result);

  
  virtual void release(blink::WebContentDecryptionModuleResult result);

  
  void OnSessionMessage(const std::vector<uint8>& message,
                        const GURL& destination_url);
  void OnSessionKeysChange(bool has_additional_usable_key);
  void OnSessionExpirationUpdate(const base::Time& new_expiry_time);
  void OnSessionReady();
  void OnSessionClosed();
  void OnSessionError(media::MediaKeys::Exception exception_code,
                      uint32 system_code,
                      const std::string& error_message);

 private:
  
  blink::WebContentDecryptionModuleResult::SessionStatus OnSessionInitialized(
      const std::string& web_session_id);

  scoped_refptr<CdmSessionAdapter> adapter_;

  
  Client* client_;

  
  
  
  std::string web_session_id_;

  
  
  
  bool is_closed_;

  
  
  
  base::WeakPtrFactory<WebContentDecryptionModuleSessionImpl> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(WebContentDecryptionModuleSessionImpl);
};

}  

#endif  
