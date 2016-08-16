// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_RENDERER_MEDIA_CAST_RTP_STREAM_H_
#define CHROME_RENDERER_MEDIA_CAST_RTP_STREAM_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "third_party/WebKit/public/platform/WebMediaStreamTrack.h"

namespace base {
class BinaryValue;
class DictionaryValue;
}

class CastAudioSink;
class CastSession;
class CastVideoSink;

struct CastCodecSpecificParams {
  std::string key;
  std::string value;

  CastCodecSpecificParams();
  ~CastCodecSpecificParams();
};

struct CastRtpPayloadParams {
  
  int payload_type;

  
  
  int max_latency_ms;

  
  
  int min_latency_ms;

  
  int ssrc;

  
  int feedback_ssrc;

  
  int clock_rate;

  
  int max_bitrate;

  
  int min_bitrate;

  
  int channels;

  
  double max_frame_rate;

  
  int width;
  int height;

  
  std::string codec_name;

  
  std::string aes_key;

  
  std::string aes_iv_mask;

  
  std::vector<CastCodecSpecificParams> codec_specific_params;

  CastRtpPayloadParams();
  ~CastRtpPayloadParams();
};

struct CastRtpParams {
  explicit CastRtpParams(const CastRtpPayloadParams& payload_params);

  
  CastRtpPayloadParams payload;

  
  std::vector<std::string> rtcp_features;

  CastRtpParams();
  ~CastRtpParams();
};

class CastRtpStream {
 public:
  typedef base::Callback<void(const std::string&)> ErrorCallback;

  CastRtpStream(const blink::WebMediaStreamTrack& track,
                const scoped_refptr<CastSession>& session);
  ~CastRtpStream();

  
  std::vector<CastRtpParams> GetSupportedParams();

  
  CastRtpParams GetParams();

  
  
  
  
  
  void Start(const CastRtpParams& params,
             const base::Closure& start_callback,
             const base::Closure& stop_callback,
             const ErrorCallback& error_callback);

  
  void Stop();

  
  void ToggleLogging(bool enable);

  
  
  void GetRawEvents(
      const base::Callback<void(scoped_ptr<base::BinaryValue>)>& callback,
      const std::string& extra_data);

  
  
  void GetStats(const base::Callback<void(
      scoped_ptr<base::DictionaryValue>)>& callback);

 private:
  
  
  bool IsAudio() const;

  void DidEncounterError(const std::string& message);

  blink::WebMediaStreamTrack track_;
  const scoped_refptr<CastSession> cast_session_;
  scoped_ptr<CastAudioSink> audio_sink_;
  scoped_ptr<CastVideoSink> video_sink_;
  CastRtpParams params_;
  base::Closure stop_callback_;
  ErrorCallback error_callback_;

  base::WeakPtrFactory<CastRtpStream> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(CastRtpStream);
};

#endif  
