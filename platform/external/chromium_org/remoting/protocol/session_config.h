// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_PROTOCOL_SESSION_CONFIG_H_
#define REMOTING_PROTOCOL_SESSION_CONFIG_H_

#include <list>
#include <string>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"

namespace remoting {
namespace protocol {

extern const int kDefaultStreamVersion;

struct ChannelConfig {
  enum TransportType {
    TRANSPORT_STREAM,
    TRANSPORT_MUX_STREAM,
    TRANSPORT_DATAGRAM,
    TRANSPORT_NONE,
  };

  enum Codec {
    CODEC_UNDEFINED,  
    CODEC_VERBATIM,
    CODEC_ZIP,
    CODEC_VP8,
    CODEC_VP9,
    CODEC_OPUS,
    CODEC_SPEEX,
  };

  
  
  static ChannelConfig None();

  
  ChannelConfig();

  
  ChannelConfig(TransportType transport, int version, Codec codec);

  
  
  bool operator==(const ChannelConfig& b) const;

  TransportType transport;
  int version;
  Codec codec;
};

class SessionConfig {
 public:
  SessionConfig();

  void set_control_config(const ChannelConfig& control_config) {
    control_config_ = control_config;
  }
  const ChannelConfig& control_config() const { return control_config_; }
  void set_event_config(const ChannelConfig& event_config) {
    event_config_ = event_config;
  }
  const ChannelConfig& event_config() const { return event_config_; }
  void set_video_config(const ChannelConfig& video_config) {
    video_config_ = video_config;
  }
  const ChannelConfig& video_config() const { return video_config_; }
  void set_audio_config(const ChannelConfig& audio_config) {
    audio_config_ = audio_config;
  }
  const ChannelConfig& audio_config() const { return audio_config_; }

  bool is_audio_enabled() const {
    return audio_config_.transport != ChannelConfig::TRANSPORT_NONE;
  }

  
  static SessionConfig ForTest();

 private:
  ChannelConfig control_config_;
  ChannelConfig event_config_;
  ChannelConfig video_config_;
  ChannelConfig audio_config_;
};

class CandidateSessionConfig {
 public:
  static scoped_ptr<CandidateSessionConfig> CreateEmpty();
  static scoped_ptr<CandidateSessionConfig> CreateFrom(
      const SessionConfig& config);
  static scoped_ptr<CandidateSessionConfig> CreateDefault();

  ~CandidateSessionConfig();

  const std::list<ChannelConfig>& control_configs() const {
    return control_configs_;
  }

  std::list<ChannelConfig>* mutable_control_configs() {
    return &control_configs_;
  }

  const std::list<ChannelConfig>& event_configs() const {
    return event_configs_;
  }

  std::list<ChannelConfig>* mutable_event_configs() {
    return &event_configs_;
  }

  const std::list<ChannelConfig>& video_configs() const {
    return video_configs_;
  }

  std::list<ChannelConfig>* mutable_video_configs() {
    return &video_configs_;
  }

  const std::list<ChannelConfig>& audio_configs() const {
    return audio_configs_;
  }

  std::list<ChannelConfig>* mutable_audio_configs() {
    return &audio_configs_;
  }

  
  
  
  
  bool Select(const CandidateSessionConfig* client_config,
              SessionConfig* result);

  
  bool IsSupported(const SessionConfig& config) const;

  
  
  
  
  bool GetFinalConfig(SessionConfig* result) const;

  scoped_ptr<CandidateSessionConfig> Clone() const;

  
  void DisableAudioChannel();
  void EnableVideoCodec(ChannelConfig::Codec codec);

 private:
  CandidateSessionConfig();
  explicit CandidateSessionConfig(const CandidateSessionConfig& config);
  CandidateSessionConfig& operator=(const CandidateSessionConfig& b);

  static bool SelectCommonChannelConfig(
      const std::list<ChannelConfig>& host_configs_,
      const std::list<ChannelConfig>& client_configs_,
      ChannelConfig* config);
  static bool IsChannelConfigSupported(const std::list<ChannelConfig>& list,
                                       const ChannelConfig& value);

  std::list<ChannelConfig> control_configs_;
  std::list<ChannelConfig> event_configs_;
  std::list<ChannelConfig> video_configs_;
  std::list<ChannelConfig> audio_configs_;
};

}  
}  

#endif  