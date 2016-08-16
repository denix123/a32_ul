// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_BLINK_NULL_ENCRYPTED_MEDIA_PLAYER_SUPPORT_H_
#define MEDIA_BLINK_NULL_ENCRYPTED_MEDIA_PLAYER_SUPPORT_H_

#include "media/base/media_export.h"
#include "media/blink/encrypted_media_player_support.h"

namespace media {

class MEDIA_EXPORT NullEncryptedMediaPlayerSupport
    : public EncryptedMediaPlayerSupport {
 public:
  static scoped_ptr<EncryptedMediaPlayerSupport> Create(
      blink::WebMediaPlayerClient* client);

  virtual ~NullEncryptedMediaPlayerSupport();

  
  virtual blink::WebMediaPlayer::MediaKeyException GenerateKeyRequest(
      blink::WebLocalFrame* frame,
      const blink::WebString& key_system,
      const unsigned char* init_data,
      unsigned init_data_length) OVERRIDE;

  virtual blink::WebMediaPlayer::MediaKeyException AddKey(
      const blink::WebString& key_system,
      const unsigned char* key,
      unsigned key_length,
      const unsigned char* init_data,
      unsigned init_data_length,
      const blink::WebString& session_id) OVERRIDE;

  virtual blink::WebMediaPlayer::MediaKeyException CancelKeyRequest(
      const blink::WebString& key_system,
      const blink::WebString& session_id) OVERRIDE;


  
  virtual void SetInitialContentDecryptionModule(
      blink::WebContentDecryptionModule* initial_cdm) OVERRIDE;
  virtual void SetContentDecryptionModule(
      blink::WebContentDecryptionModule* cdm) OVERRIDE;
  virtual void SetContentDecryptionModule(
      blink::WebContentDecryptionModule* cdm,
      blink::WebContentDecryptionModuleResult result) OVERRIDE;


  

  
  
  
  virtual Demuxer::NeedKeyCB CreateNeedKeyCB() OVERRIDE;

  
  
  
  virtual SetDecryptorReadyCB CreateSetDecryptorReadyCB() OVERRIDE;

  
  
  virtual void OnPipelineDecryptError() OVERRIDE;

 private:
  NullEncryptedMediaPlayerSupport();

  DISALLOW_COPY_AND_ASSIGN(NullEncryptedMediaPlayerSupport);
};

}  

#endif  
