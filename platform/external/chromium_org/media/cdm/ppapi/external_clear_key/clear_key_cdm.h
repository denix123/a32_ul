// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_CDM_PPAPI_EXTERNAL_CLEAR_KEY_CLEAR_KEY_CDM_H_
#define MEDIA_CDM_PPAPI_EXTERNAL_CLEAR_KEY_CLEAR_KEY_CDM_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/synchronization/lock.h"
#include "media/cdm/aes_decryptor.h"
#include "media/cdm/ppapi/external_clear_key/clear_key_cdm_common.h"

#if 0
#define CLEAR_KEY_CDM_USE_FAKE_AUDIO_DECODER
#endif

namespace media {
class FileIOTestRunner;
class CdmVideoDecoder;
class DecoderBuffer;
class FFmpegCdmAudioDecoder;

class ClearKeyCdm : public ClearKeyCdmInterface {
 public:
  ClearKeyCdm(Host* host, const std::string& key_system);
  virtual ~ClearKeyCdm();

  
  virtual void CreateSession(uint32 promise_id,
                             const char* init_data_type,
                             uint32 init_data_type_size,
                             const uint8* init_data,
                             uint32 init_data_size,
                             cdm::SessionType session_type) OVERRIDE;
  virtual void LoadSession(uint32 promise_id,
                           const char* web_session_id,
                           uint32_t web_session_id_length) OVERRIDE;
  virtual void UpdateSession(uint32 promise_id,
                             const char* web_session_id,
                             uint32_t web_session_id_length,
                             const uint8* response,
                             uint32 response_size) OVERRIDE;
  virtual void CloseSession(uint32 promise_id,
                            const char* web_session_id,
                            uint32_t web_session_id_length) OVERRIDE;
  virtual void RemoveSession(uint32 promise_id,
                             const char* web_session_id,
                             uint32_t web_session_id_length) OVERRIDE;
  virtual void GetUsableKeyIds(uint32_t promise_id,
                               const char* web_session_id,
                               uint32_t web_session_id_length) OVERRIDE;
  virtual void SetServerCertificate(
      uint32 promise_id,
      const uint8_t* server_certificate_data,
      uint32_t server_certificate_data_size) OVERRIDE;
  virtual void TimerExpired(void* context) OVERRIDE;
  virtual cdm::Status Decrypt(const cdm::InputBuffer& encrypted_buffer,
                              cdm::DecryptedBlock* decrypted_block) OVERRIDE;
  virtual cdm::Status InitializeAudioDecoder(
      const cdm::AudioDecoderConfig& audio_decoder_config) OVERRIDE;
  virtual cdm::Status InitializeVideoDecoder(
      const cdm::VideoDecoderConfig& video_decoder_config) OVERRIDE;
  virtual void DeinitializeDecoder(cdm::StreamType decoder_type) OVERRIDE;
  virtual void ResetDecoder(cdm::StreamType decoder_type) OVERRIDE;
  virtual cdm::Status DecryptAndDecodeFrame(
      const cdm::InputBuffer& encrypted_buffer,
      cdm::VideoFrame* video_frame) OVERRIDE;
  virtual cdm::Status DecryptAndDecodeSamples(
      const cdm::InputBuffer& encrypted_buffer,
      cdm::AudioFrames* audio_frames) OVERRIDE;
  virtual void Destroy() OVERRIDE;
  virtual void OnPlatformChallengeResponse(
      const cdm::PlatformChallengeResponse& response) OVERRIDE;
  virtual void OnQueryOutputProtectionStatus(
      uint32_t link_mask, uint32_t output_protection_mask) OVERRIDE;

 private:
  
  
  void LoadLoadableSession();

  
  void OnSessionMessage(const std::string& web_session_id,
                        const std::vector<uint8>& message,
                        const GURL& destination_url);
  void OnSessionKeysChange(const std::string& web_session_id,
                           bool has_additional_usable_key);
  void OnSessionClosed(const std::string& web_session_id);

  
  
  void OnSessionCreated(uint32 promise_id, const std::string& web_session_id);
  void OnSessionLoaded(uint32 promise_id, const std::string& web_session_id);
  void OnSessionUpdated(uint32 promise_id, const std::string& web_session_id);
  void OnUsableKeyIdsObtained(uint32 promise_id, const KeyIdsVector& key_ids);
  void OnPromiseResolved(uint32 promise_id);
  void OnPromiseFailed(uint32 promise_id,
                       MediaKeys::Exception exception_code,
                       uint32 system_code,
                       const std::string& error_message);

  
  void ScheduleNextHeartBeat();

  
  
  
  
  
  
  
  
  cdm::Status DecryptToMediaDecoderBuffer(
      const cdm::InputBuffer& encrypted_buffer,
      scoped_refptr<DecoderBuffer>* decrypted_buffer);

#if defined(CLEAR_KEY_CDM_USE_FAKE_AUDIO_DECODER)
  int64 CurrentTimeStampInMicroseconds() const;

  
  
  int GenerateFakeAudioFramesFromDuration(int64 duration_in_microseconds,
                                          cdm::AudioFrames* audio_frames) const;

  
  
  cdm::Status GenerateFakeAudioFrames(int64 timestamp_in_microseconds,
                                      cdm::AudioFrames* audio_frames);
#endif  

  void StartFileIOTest();

  
  void OnFileIOTestComplete(bool success);

  
  void SetSessionId(const std::string& web_session_id);

  AesDecryptor decryptor_;

  ClearKeyCdmHost* host_;

  const std::string key_system_;

  std::string last_session_id_;
  std::string next_heartbeat_message_;

  
  
  
  
  
  
  
  
  
  
  
  
  std::string session_id_for_emulated_loadsession_;
  uint32_t promise_id_for_emulated_loadsession_;

  
  int64 timer_delay_ms_;

  
  
  bool heartbeat_timer_set_;

#if defined(CLEAR_KEY_CDM_USE_FAKE_AUDIO_DECODER)
  int channel_count_;
  int bits_per_channel_;
  int samples_per_second_;
  int64 output_timestamp_base_in_microseconds_;
  int total_samples_generated_;
#endif  

#if defined(CLEAR_KEY_CDM_USE_FFMPEG_DECODER)
  scoped_ptr<FFmpegCdmAudioDecoder> audio_decoder_;
#endif  

  scoped_ptr<CdmVideoDecoder> video_decoder_;

  scoped_ptr<FileIOTestRunner> file_io_test_runner_;

  DISALLOW_COPY_AND_ASSIGN(ClearKeyCdm);
};

}  

#endif  
