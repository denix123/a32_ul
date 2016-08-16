// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_CDM_PPAPI_CDM_WRAPPER_H_
#define MEDIA_CDM_PPAPI_CDM_WRAPPER_H_

#include <map>
#include <queue>
#include <string>

#include "base/basictypes.h"
#include "media/cdm/ppapi/api/content_decryption_module.h"
#include "media/cdm/ppapi/cdm_helpers.h"
#include "media/cdm/ppapi/supported_cdm_versions.h"
#include "ppapi/cpp/logging.h"

namespace media {

class CdmWrapper {
 public:
  static CdmWrapper* Create(const char* key_system,
                            uint32_t key_system_size,
                            GetCdmHostFunc get_cdm_host_func,
                            void* user_data);

  virtual ~CdmWrapper() {};

  
  virtual bool SetServerCertificate(uint32_t promise_id,
                                    const uint8_t* server_certificate_data,
                                    uint32_t server_certificate_data_size) = 0;
  virtual void CreateSession(uint32_t promise_id,
                             const char* init_data_type,
                             uint32_t init_data_type_size,
                             const uint8_t* init_data,
                             uint32_t init_data_size,
                             cdm::SessionType session_type) = 0;
  virtual void LoadSession(uint32_t promise_id,
                           const char* web_session_id,
                           uint32_t web_session_id_size) = 0;
  virtual void UpdateSession(uint32_t promise_id,
                             const char* web_session_id,
                             uint32_t web_session_id_size,
                             const uint8_t* response,
                             uint32_t response_size) = 0;
  
  virtual bool CloseSession(uint32_t promise_id,
                            const char* web_session_id,
                            uint32_t web_session_id_size) = 0;
  virtual void RemoveSession(uint32_t promise_id,
                             const char* web_session_id,
                             uint32_t web_session_id_size) = 0;
  
  virtual bool GetUsableKeyIds(uint32_t promise_id,
                               const char* web_session_id,
                               uint32_t web_session_id_size) = 0;
  virtual void TimerExpired(void* context) = 0;
  virtual cdm::Status Decrypt(const cdm::InputBuffer& encrypted_buffer,
                              cdm::DecryptedBlock* decrypted_buffer) = 0;
  virtual cdm::Status InitializeAudioDecoder(
      const cdm::AudioDecoderConfig& audio_decoder_config) = 0;
  virtual cdm::Status InitializeVideoDecoder(
      const cdm::VideoDecoderConfig& video_decoder_config) = 0;
  virtual void DeinitializeDecoder(cdm::StreamType decoder_type) = 0;
  virtual void ResetDecoder(cdm::StreamType decoder_type) = 0;
  virtual cdm::Status DecryptAndDecodeFrame(
      const cdm::InputBuffer& encrypted_buffer,
      cdm::VideoFrame* video_frame) = 0;
  virtual cdm::Status DecryptAndDecodeSamples(
      const cdm::InputBuffer& encrypted_buffer,
      cdm::AudioFrames* audio_frames) = 0;
  virtual void OnPlatformChallengeResponse(
      const cdm::PlatformChallengeResponse& response) = 0;
  virtual void OnQueryOutputProtectionStatus(
      uint32_t link_mask,
      uint32_t output_protection_mask) = 0;

  
  
  
  
  
  
  
  
  virtual uint32_t LookupPromiseId(uint32_t session_id) = 0;
  virtual void AssignWebSessionId(uint32_t session_id,
                                  const char* web_session_id,
                                  uint32_t web_session_id_size) = 0;
  virtual std::string LookupWebSessionId(uint32_t session_id) = 0;
  virtual void DropWebSessionId(std::string web_session_id) = 0;

  
  
  
  
  

  
  
  
  virtual bool SessionUsableKeysEventNeeded(uint32_t promise_id,
                                            std::string* web_session_id) = 0;

  
  
  virtual void SetSessionUsableKeysEventNeeded(
      uint32_t promise_id,
      const char* web_session_id,
      uint32_t web_session_id_size) = 0;

  
  
  
  
  virtual void ConvertInputBuffer(const cdm::InputBuffer& v2,
                                  cdm::InputBuffer_1* v1) = 0;

  
  
  
  virtual std::string ConvertInitDataTypeToContentType(
      const std::string& init_data_type) const = 0;

 protected:
  CdmWrapper() {}

 private:
  DISALLOW_COPY_AND_ASSIGN(CdmWrapper);
};

template <class CdmInterface>
class CdmWrapperImpl : public CdmWrapper {
 public:
  static CdmWrapper* Create(const char* key_system,
                            uint32_t key_system_size,
                            GetCdmHostFunc get_cdm_host_func,
                            void* user_data) {
    void* cdm_instance = ::CreateCdmInstance(
        CdmInterface::kVersion, key_system, key_system_size, get_cdm_host_func,
        user_data);
    if (!cdm_instance)
      return NULL;

    return new CdmWrapperImpl<CdmInterface>(
        static_cast<CdmInterface*>(cdm_instance));
  }

  virtual ~CdmWrapperImpl() {
    cdm_->Destroy();
  }

  
  
  bool HasHeader(const uint8* data,
                 int data_length,
                 const std::string& header) {
    return static_cast<size_t>(data_length) > header.length() &&
           std::equal(data, data + header.length(), header.begin());
  }

  virtual bool SetServerCertificate(
      uint32_t promise_id,
      const uint8_t* server_certificate_data,
      uint32_t server_certificate_data_size) OVERRIDE {
    cdm_->SetServerCertificate(
        promise_id, server_certificate_data, server_certificate_data_size);
    return true;
  }

  virtual void CreateSession(uint32_t promise_id,
                             const char* init_data_type,
                             uint32_t init_data_type_size,
                             const uint8_t* init_data,
                             uint32_t init_data_size,
                             cdm::SessionType session_type) OVERRIDE {
    
    
    PP_DCHECK(session_type == cdm::kTemporary);
    const char kPersistentSessionHeader[] = "PERSISTENT|";
    if (HasHeader(init_data, init_data_size, kPersistentSessionHeader)) {
      cdm_->CreateSession(promise_id,
                          init_data_type,
                          init_data_type_size,
                          init_data + strlen(kPersistentSessionHeader),
                          init_data_size - strlen(kPersistentSessionHeader),
                          cdm::kPersistent);
      return;
    }

    cdm_->CreateSession(promise_id,
                        init_data_type,
                        init_data_type_size,
                        init_data,
                        init_data_size,
                        session_type);
  }

  virtual void LoadSession(uint32_t promise_id,
                           const char* web_session_id,
                           uint32_t web_session_id_size) OVERRIDE {
    cdm_->LoadSession(promise_id, web_session_id, web_session_id_size);
  }

  virtual void UpdateSession(uint32_t promise_id,
                             const char* web_session_id,
                             uint32_t web_session_id_size,
                             const uint8_t* response,
                             uint32_t response_size) OVERRIDE {
    cdm_->UpdateSession(promise_id,
                        web_session_id,
                        web_session_id_size,
                        response,
                        response_size);
  }

  virtual bool CloseSession(uint32_t promise_id,
                            const char* web_session_id,
                            uint32_t web_session_id_size) OVERRIDE {
    cdm_->CloseSession(promise_id, web_session_id, web_session_id_size);
    return true;
  }

  virtual void RemoveSession(uint32_t promise_id,
                             const char* web_session_id,
                             uint32_t web_session_id_size) OVERRIDE {
    cdm_->RemoveSession(promise_id, web_session_id, web_session_id_size);
  }

  virtual bool GetUsableKeyIds(uint32_t promise_id,
                               const char* web_session_id,
                               uint32_t web_session_id_size) OVERRIDE {
    cdm_->GetUsableKeyIds(promise_id, web_session_id, web_session_id_size);
    return true;
  }

  virtual void TimerExpired(void* context) OVERRIDE {
    cdm_->TimerExpired(context);
  }

  virtual cdm::Status Decrypt(const cdm::InputBuffer& encrypted_buffer,
                              cdm::DecryptedBlock* decrypted_buffer) OVERRIDE {
    return cdm_->Decrypt(encrypted_buffer, decrypted_buffer);
  }

  virtual cdm::Status InitializeAudioDecoder(
      const cdm::AudioDecoderConfig& audio_decoder_config) OVERRIDE {
    return cdm_->InitializeAudioDecoder(audio_decoder_config);
  }

  virtual cdm::Status InitializeVideoDecoder(
      const cdm::VideoDecoderConfig& video_decoder_config) OVERRIDE {
    return cdm_->InitializeVideoDecoder(video_decoder_config);
  }

  virtual void DeinitializeDecoder(cdm::StreamType decoder_type) OVERRIDE {
    cdm_->DeinitializeDecoder(decoder_type);
  }

  virtual void ResetDecoder(cdm::StreamType decoder_type) OVERRIDE {
    cdm_->ResetDecoder(decoder_type);
  }

  virtual cdm::Status DecryptAndDecodeFrame(
      const cdm::InputBuffer& encrypted_buffer,
      cdm::VideoFrame* video_frame) OVERRIDE {
    return cdm_->DecryptAndDecodeFrame(encrypted_buffer, video_frame);
  }

  virtual cdm::Status DecryptAndDecodeSamples(
      const cdm::InputBuffer& encrypted_buffer,
      cdm::AudioFrames* audio_frames) OVERRIDE {
    return cdm_->DecryptAndDecodeSamples(encrypted_buffer, audio_frames);
  }

  virtual void OnPlatformChallengeResponse(
      const cdm::PlatformChallengeResponse& response) OVERRIDE {
    cdm_->OnPlatformChallengeResponse(response);
  }

  virtual void OnQueryOutputProtectionStatus(
      uint32_t link_mask,
      uint32_t output_protection_mask) OVERRIDE {
    cdm_->OnQueryOutputProtectionStatus(link_mask, output_protection_mask);
  }

  uint32_t CreateSessionId() {
    return next_session_id_++;
  }

  void RegisterPromise(uint32_t session_id, uint32_t promise_id) {
    PP_DCHECK(promise_to_session_id_map_.find(session_id) ==
              promise_to_session_id_map_.end());
    promise_to_session_id_map_.insert(std::make_pair(session_id, promise_id));
  }

  virtual uint32_t LookupPromiseId(uint32_t session_id) {
    std::map<uint32_t, uint32_t>::iterator it =
        promise_to_session_id_map_.find(session_id);
    if (it == promise_to_session_id_map_.end())
      return 0;
    uint32_t promise_id = it->second;
    promise_to_session_id_map_.erase(it);
    return promise_id;
  }

  virtual void AssignWebSessionId(uint32_t session_id,
                                  const char* web_session_id,
                                  uint32_t web_session_id_size) {
    web_session_to_session_id_map_.insert(std::make_pair(
        std::string(web_session_id, web_session_id_size), session_id));
  }

  uint32_t LookupSessionId(std::string web_session_id) {
    return web_session_to_session_id_map_.find(web_session_id)->second;
  }

  virtual std::string LookupWebSessionId(uint32_t session_id) {
    std::map<std::string, uint32_t>::iterator it;
    for (it = web_session_to_session_id_map_.begin();
         it != web_session_to_session_id_map_.end();
         ++it) {
      if (it->second == session_id)
        return it->first;
    }
    PP_NOTREACHED();
    return std::string();
  }

  virtual void DropWebSessionId(std::string web_session_id) {
    web_session_to_session_id_map_.erase(web_session_id);
  }

  virtual bool SessionUsableKeysEventNeeded(uint32_t promise_id,
                                            std::string* web_session_id) {
    std::map<uint32_t, std::string>::iterator it =
        promises_needing_usable_keys_event_.find(promise_id);
    if (it == promises_needing_usable_keys_event_.end())
      return false;
    web_session_id->swap(it->second);
    promises_needing_usable_keys_event_.erase(it);
    return true;
  }

  virtual void SetSessionUsableKeysEventNeeded(uint32_t promise_id,
                                               const char* web_session_id,
                                               uint32_t web_session_id_size) {
    promises_needing_usable_keys_event_.insert(std::make_pair(
        promise_id, std::string(web_session_id, web_session_id_size)));
  }

  virtual void ConvertInputBuffer(const cdm::InputBuffer& v2,
                                  cdm::InputBuffer_1* v1) {
    v1->data = v2.data;
    v1->data_size = v2.data_size;
    v1->data_offset = 0;
    v1->key_id = v2.key_id;
    v1->key_id_size = v2.key_id_size;
    v1->iv = v2.iv;
    v1->iv_size = v2.iv_size;
    v1->subsamples = v2.subsamples;
    v1->num_subsamples = v2.num_subsamples;
    v1->timestamp = v2.timestamp;
  }

  virtual std::string ConvertInitDataTypeToContentType(
      const std::string& init_data_type) const {
    if (init_data_type == "cenc")
      return "video/mp4";
    if (init_data_type == "webm")
      return "video/webm";
    return init_data_type;
  }

 private:
  CdmWrapperImpl(CdmInterface* cdm) : cdm_(cdm), next_session_id_(100) {
    PP_DCHECK(cdm_);
  }

  CdmInterface* cdm_;

  std::map<uint32_t, uint32_t> promise_to_session_id_map_;
  uint32_t next_session_id_;
  std::map<std::string, uint32_t> web_session_to_session_id_map_;

  std::map<uint32_t, std::string> promises_needing_usable_keys_event_;

  DISALLOW_COPY_AND_ASSIGN(CdmWrapperImpl);
};


template <>
bool CdmWrapperImpl<cdm::ContentDecryptionModule_4>::SetServerCertificate(
    uint32_t promise_id,
    const uint8_t* server_certificate_data,
    uint32_t server_certificate_data_size) {
  return false;
}

template <>
void CdmWrapperImpl<cdm::ContentDecryptionModule_4>::CreateSession(
    uint32_t promise_id,
    const char* init_data_type,
    uint32_t init_data_type_size,
    const uint8_t* init_data,
    uint32_t init_data_size,
    cdm::SessionType session_type) {
  uint32_t session_id = CreateSessionId();
  RegisterPromise(session_id, promise_id);
  std::string converted_init_data_type = ConvertInitDataTypeToContentType(
      std::string(init_data_type, init_data_type_size));
  cdm_->CreateSession(session_id,
                      converted_init_data_type.data(),
                      converted_init_data_type.length(),
                      init_data,
                      init_data_size);
}

template <>
void CdmWrapperImpl<cdm::ContentDecryptionModule_4>::LoadSession(
    uint32_t promise_id,
    const char* web_session_id,
    uint32_t web_session_id_size) {
  uint32_t session_id = CreateSessionId();
  RegisterPromise(session_id, promise_id);
  
  
  SetSessionUsableKeysEventNeeded(
      promise_id, web_session_id, web_session_id_size);
  cdm_->LoadSession(session_id, web_session_id, web_session_id_size);
}

template <>
void CdmWrapperImpl<cdm::ContentDecryptionModule_4>::UpdateSession(
    uint32_t promise_id,
    const char* web_session_id,
    uint32_t web_session_id_size,
    const uint8_t* response,
    uint32_t response_size) {
  std::string web_session_str(web_session_id, web_session_id_size);
  uint32_t session_id = LookupSessionId(web_session_str);
  RegisterPromise(session_id, promise_id);
  
  
  SetSessionUsableKeysEventNeeded(
      promise_id, web_session_id, web_session_id_size);
  cdm_->UpdateSession(session_id, response, response_size);
}

template <>
bool CdmWrapperImpl<cdm::ContentDecryptionModule_4>::CloseSession(
    uint32_t promise_id,
    const char* web_session_id,
    uint32_t web_session_id_size) {
  return false;
}

template <>
void CdmWrapperImpl<cdm::ContentDecryptionModule_4>::RemoveSession(
    uint32_t promise_id,
    const char* web_session_id,
    uint32_t web_session_id_size) {
  std::string web_session_str(web_session_id, web_session_id_size);
  uint32_t session_id = LookupSessionId(web_session_str);
  RegisterPromise(session_id, promise_id);
  cdm_->ReleaseSession(session_id);
}

template <>
bool CdmWrapperImpl<cdm::ContentDecryptionModule_4>::GetUsableKeyIds(
    uint32_t promise_id,
    const char* web_session_id,
    uint32_t web_session_id_size) {
  return false;
}

template <>
cdm::Status CdmWrapperImpl<cdm::ContentDecryptionModule_4>::Decrypt(
    const cdm::InputBuffer& encrypted_buffer,
    cdm::DecryptedBlock* decrypted_buffer) {
  cdm::InputBuffer_1 buffer;
  ConvertInputBuffer(encrypted_buffer, &buffer);
  return cdm_->Decrypt(buffer, decrypted_buffer);
}

template <>
cdm::Status
CdmWrapperImpl<cdm::ContentDecryptionModule_4>::DecryptAndDecodeFrame(
    const cdm::InputBuffer& encrypted_buffer,
    cdm::VideoFrame* video_frame) {
  cdm::InputBuffer_1 buffer;
  ConvertInputBuffer(encrypted_buffer, &buffer);
  return cdm_->DecryptAndDecodeFrame(buffer, video_frame);
}

template <>
cdm::Status
CdmWrapperImpl<cdm::ContentDecryptionModule_4>::DecryptAndDecodeSamples(
    const cdm::InputBuffer& encrypted_buffer,
    cdm::AudioFrames* audio_frames) {
  cdm::InputBuffer_1 buffer;
  ConvertInputBuffer(encrypted_buffer, &buffer);
  return cdm_->DecryptAndDecodeSamples(buffer, audio_frames);
}

CdmWrapper* CdmWrapper::Create(const char* key_system,
                               uint32_t key_system_size,
                               GetCdmHostFunc get_cdm_host_func,
                               void* user_data) {
  COMPILE_ASSERT(cdm::ContentDecryptionModule::kVersion ==
                     cdm::ContentDecryptionModule_6::kVersion,
                 update_code_below);

  
  
  
  
  PP_DCHECK(
      !IsSupportedCdmInterfaceVersion(cdm::ContentDecryptionModule::kVersion +
                                      1) &&
      IsSupportedCdmInterfaceVersion(cdm::ContentDecryptionModule::kVersion) &&
      IsSupportedCdmInterfaceVersion(
          cdm::ContentDecryptionModule_4::kVersion) &&
      !IsSupportedCdmInterfaceVersion(cdm::ContentDecryptionModule_4::kVersion -
                                      1));

  
  CdmWrapper* cdm_wrapper =
      CdmWrapperImpl<cdm::ContentDecryptionModule>::Create(
          key_system, key_system_size, get_cdm_host_func, user_data);
  if (cdm_wrapper)
    return cdm_wrapper;

  
  
  cdm_wrapper = CdmWrapperImpl<cdm::ContentDecryptionModule_4>::Create(
      key_system, key_system_size, get_cdm_host_func, user_data);
  return cdm_wrapper;
}

COMPILE_ASSERT(cdm::ContentDecryptionModule::kVersion ==
                   cdm::ContentDecryptionModule_6::kVersion,
               ensure_cdm_wrapper_templates_have_old_version_support);

}  

#endif  
