// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_PEPPER_CONTENT_DECRYPTOR_DELEGATE_H_
#define CONTENT_RENDERER_PEPPER_CONTENT_DECRYPTOR_DELEGATE_H_

#include <map>
#include <queue>
#include <string>

#include "base/basictypes.h"
#include "base/callback_helpers.h"
#include "base/compiler_specific.h"
#include "base/containers/scoped_ptr_hash_map.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "media/base/cdm_promise.h"
#include "media/base/channel_layout.h"
#include "media/base/decryptor.h"
#include "media/base/media_keys.h"
#include "media/base/sample_format.h"
#include "ppapi/c/pp_time.h"
#include "ppapi/c/private/pp_content_decryptor.h"
#include "ppapi/c/private/ppp_content_decryptor_private.h"
#include "ui/gfx/size.h"

namespace media {
class AudioDecoderConfig;
class DecoderBuffer;
class VideoDecoderConfig;
}

namespace content {

class PPB_Buffer_Impl;

class ContentDecryptorDelegate {
 public:
  
  
  
  ContentDecryptorDelegate(
      PP_Instance pp_instance,
      const PPP_ContentDecryptor_Private* plugin_decryption_interface);
  ~ContentDecryptorDelegate();

  
  void Initialize(
      const std::string& key_system,
      const media::SessionMessageCB& session_message_cb,
      const media::SessionReadyCB& session_ready_cb,
      const media::SessionClosedCB& session_closed_cb,
      const media::SessionErrorCB& session_error_cb,
      const media::SessionKeysChangeCB& session_keys_change_cb,
      const media::SessionExpirationUpdateCB& session_expiration_update_cb,
      const base::Closure& fatal_plugin_error_cb);

  void InstanceCrashed();

  
  void SetServerCertificate(const uint8_t* certificate,
                            uint32_t certificate_length,
                            scoped_ptr<media::SimpleCdmPromise> promise);
  void CreateSession(const std::string& init_data_type,
                     const uint8* init_data,
                     int init_data_length,
                     media::MediaKeys::SessionType session_type,
                     scoped_ptr<media::NewSessionCdmPromise> promise);
  void LoadSession(const std::string& web_session_id,
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
  bool Decrypt(media::Decryptor::StreamType stream_type,
               const scoped_refptr<media::DecoderBuffer>& encrypted_buffer,
               const media::Decryptor::DecryptCB& decrypt_cb);
  bool CancelDecrypt(media::Decryptor::StreamType stream_type);
  bool InitializeAudioDecoder(
      const media::AudioDecoderConfig& decoder_config,
      const media::Decryptor::DecoderInitCB& decoder_init_cb);
  bool InitializeVideoDecoder(
      const media::VideoDecoderConfig& decoder_config,
      const media::Decryptor::DecoderInitCB& decoder_init_cb);
  
  
  bool DeinitializeDecoder(media::Decryptor::StreamType stream_type);
  bool ResetDecoder(media::Decryptor::StreamType stream_type);
  
  bool DecryptAndDecodeAudio(
      const scoped_refptr<media::DecoderBuffer>& encrypted_buffer,
      const media::Decryptor::AudioDecodeCB& audio_decode_cb);
  bool DecryptAndDecodeVideo(
      const scoped_refptr<media::DecoderBuffer>& encrypted_buffer,
      const media::Decryptor::VideoDecodeCB& video_decode_cb);

  
  void OnPromiseResolved(uint32 promise_id);
  void OnPromiseResolvedWithSession(uint32 promise_id, PP_Var web_session_id);
  void OnPromiseResolvedWithKeyIds(uint32 promise_id, PP_Var key_ids_array);
  void OnPromiseRejected(uint32 promise_id,
                         PP_CdmExceptionCode exception_code,
                         uint32 system_code,
                         PP_Var error_description);
  void OnSessionMessage(PP_Var web_session_id,
                        PP_Var message,
                        PP_Var destination_url);
  void OnSessionKeysChange(PP_Var web_session_id,
                           PP_Bool has_additional_usable_key);
  void OnSessionExpirationChange(PP_Var web_session_id,
                                 PP_Time new_expiry_time);
  void OnSessionReady(PP_Var web_session_id);
  void OnSessionClosed(PP_Var web_session_id);
  void OnSessionError(PP_Var web_session_id,
                      PP_CdmExceptionCode exception_code,
                      uint32 system_code,
                      PP_Var error_description);
  void DeliverBlock(PP_Resource decrypted_block,
                    const PP_DecryptedBlockInfo* block_info);
  void DecoderInitializeDone(PP_DecryptorStreamType decoder_type,
                             uint32_t request_id,
                             PP_Bool success);
  void DecoderDeinitializeDone(PP_DecryptorStreamType decoder_type,
                               uint32_t request_id);
  void DecoderResetDone(PP_DecryptorStreamType decoder_type,
                        uint32_t request_id);
  void DeliverFrame(PP_Resource decrypted_frame,
                    const PP_DecryptedFrameInfo* frame_info);
  void DeliverSamples(PP_Resource audio_frames,
                      const PP_DecryptedSampleInfo* sample_info);

 private:
  
  
  typedef base::ScopedPtrHashMap<uint32_t, media::CdmPromise> PromiseMap;

  template <typename Callback>
  class TrackableCallback {
   public:
    TrackableCallback() : id_(0u) {}
    ~TrackableCallback() {
      
      DCHECK_EQ(id_, 0u);
      DCHECK(is_null());
    };

    bool Matches(uint32_t id) const { return id == id_; }

    bool is_null() const { return cb_.is_null(); }

    void Set(uint32_t id, const Callback& cb) {
      DCHECK_EQ(id_, 0u);
      DCHECK(cb_.is_null());
      id_ = id;
      cb_ = cb;
    }

    Callback ResetAndReturn() {
      id_ = 0;
      return base::ResetAndReturn(&cb_);
    }

   private:
    uint32_t id_;
    Callback cb_;
  };

  
  void CancelDecode(media::Decryptor::StreamType stream_type);

  
  
  
  
  
  
  
  
  
  
  bool MakeMediaBufferResource(
      media::Decryptor::StreamType stream_type,
      const scoped_refptr<media::DecoderBuffer>& encrypted_buffer,
      scoped_refptr<PPB_Buffer_Impl>* resource);

  void FreeBuffer(uint32_t buffer_id);

  void SetBufferToFreeInTrackingInfo(PP_DecryptTrackingInfo* tracking_info);

  
  
  bool DeserializeAudioFrames(PP_Resource audio_frames,
                              size_t data_size,
                              media::SampleFormat sample_format,
                              media::Decryptor::AudioBuffers* frames);

  void SatisfyAllPendingCallbacksOnError();

  
  
  uint32_t SavePromise(scoped_ptr<media::CdmPromise> promise);

  
  
  scoped_ptr<media::CdmPromise> TakePromise(uint32_t promise_id);

  const PP_Instance pp_instance_;
  const PPP_ContentDecryptor_Private* const plugin_decryption_interface_;

  
  std::string key_system_;

  
  media::SessionMessageCB session_message_cb_;
  media::SessionReadyCB session_ready_cb_;
  media::SessionClosedCB session_closed_cb_;
  media::SessionErrorCB session_error_cb_;
  media::SessionKeysChangeCB session_keys_change_cb_;
  media::SessionExpirationUpdateCB session_expiration_update_cb_;

  
  
  base::Closure fatal_plugin_error_cb_;

  gfx::Size natural_size_;

  
  
  
  
  uint32_t next_decryption_request_id_;

  TrackableCallback<media::Decryptor::DecryptCB> audio_decrypt_cb_;
  TrackableCallback<media::Decryptor::DecryptCB> video_decrypt_cb_;
  TrackableCallback<media::Decryptor::DecoderInitCB> audio_decoder_init_cb_;
  TrackableCallback<media::Decryptor::DecoderInitCB> video_decoder_init_cb_;
  TrackableCallback<media::Decryptor::AudioDecodeCB> audio_decode_cb_;
  TrackableCallback<media::Decryptor::VideoDecodeCB> video_decode_cb_;

  
  scoped_refptr<PPB_Buffer_Impl> audio_input_resource_;
  scoped_refptr<PPB_Buffer_Impl> video_input_resource_;

  std::queue<uint32_t> free_buffers_;

  
  int audio_samples_per_second_;
  int audio_channel_count_;
  media::ChannelLayout audio_channel_layout_;

  
  uint32_t next_promise_id_;
  PromiseMap promises_;

  base::WeakPtr<ContentDecryptorDelegate> weak_this_;
  base::WeakPtrFactory<ContentDecryptorDelegate> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(ContentDecryptorDelegate);
};

}  

#endif  
