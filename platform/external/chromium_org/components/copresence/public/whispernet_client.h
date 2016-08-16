// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_COPRESENCE_PUBLIC_WHISPERNET_CLIENT_H_
#define COMPONENTS_COPRESENCE_PUBLIC_WHISPERNET_CLIENT_H_

#include <string>
#include <vector>

#include "base/callback.h"
#include "base/macros.h"
#include "base/memory/ref_counted.h"

namespace media {
class AudioBusRefCounted;
}

namespace copresence {

struct AudioToken {
  AudioToken(const std::string& token, bool audible)
      : token(token), audible(audible) {}
  std::string token;
  bool audible;
};

class WhispernetClient {
 public:
  
  typedef base::Callback<void(bool)> SuccessCallback;
  
  typedef base::Callback<void(const std::vector<AudioToken>&)> TokensCallback;
  
  typedef base::Callback<void(const std::string&,
                              bool,
                              const scoped_refptr<media::AudioBusRefCounted>&)>
      SamplesCallback;

  
  
  virtual void Initialize(const SuccessCallback& init_callback) = 0;
  
  virtual void Shutdown() = 0;

  
  virtual void EncodeToken(const std::string& token, bool audible) = 0;
  
  virtual void DecodeSamples(const std::string& samples) = 0;
  
  virtual void DetectBroadcast() = 0;

  
  
  virtual void RegisterTokensCallback(
      const TokensCallback& tokens_callback) = 0;
  virtual void RegisterSamplesCallback(
      const SamplesCallback& samples_callback) = 0;
  virtual void RegisterDetectBroadcastCallback(
      const SuccessCallback& db_callback) = 0;

  
  
  virtual TokensCallback GetTokensCallback() = 0;
  virtual SamplesCallback GetSamplesCallback() = 0;
  virtual SuccessCallback GetDetectBroadcastCallback() = 0;
  virtual SuccessCallback GetInitializedCallback() = 0;

  virtual ~WhispernetClient() {}
};

}  

#endif  
