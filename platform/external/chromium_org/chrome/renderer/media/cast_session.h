// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_RENDERER_MEDIA_CAST_SESSION_H_
#define CHROME_RENDERER_MEDIA_CAST_SESSION_H_

#include <vector>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "net/base/ip_endpoint.h"

namespace base {
class BinaryValue;
class DictionaryValue;
class MessageLoopProxy;
}  

namespace media {
class VideoFrame;
namespace cast {
class AudioFrameInput;
class VideoFrameInput;
struct AudioSenderConfig;
struct VideoSenderConfig;
}  
}  

namespace content {
class P2PSocketClient;
}  

class CastSessionDelegate;

class CastSession : public base::RefCounted<CastSession> {
 public:
  typedef base::Callback<void(const scoped_refptr<
      media::cast::AudioFrameInput>&)> AudioFrameInputAvailableCallback;
  typedef base::Callback<void(const scoped_refptr<
      media::cast::VideoFrameInput>&)> VideoFrameInputAvailableCallback;
  typedef base::Callback<void(const std::vector<char>&)> SendPacketCallback;
  typedef base::Callback<void(scoped_ptr<base::BinaryValue>)> EventLogsCallback;
  typedef base::Callback<void(scoped_ptr<base::DictionaryValue>)> StatsCallback;
  typedef base::Callback<void(const std::string&)> ErrorCallback;

  CastSession();

  
  
  
  
  
  
  
  
  void StartAudio(const media::cast::AudioSenderConfig& config,
                  const AudioFrameInputAvailableCallback& callback,
                  const ErrorCallback& error_callback);
  void StartVideo(const media::cast::VideoSenderConfig& config,
                  const VideoFrameInputAvailableCallback& callback,
                  const ErrorCallback& error_callback);

  
  
  
  
  void StartUDP(const net::IPEndPoint& remote_endpoint,
                scoped_ptr<base::DictionaryValue> options);

  
  
  
  
  void ToggleLogging(bool is_audio, bool enable);

  
  
  
  void GetEventLogsAndReset(bool is_audio,
      const std::string& extra_data, const EventLogsCallback& callback);

  
  
  void GetStatsAndReset(bool is_audio, const StatsCallback& callback);

 private:
  friend class base::RefCounted<CastSession>;
  virtual ~CastSession();

  
  
  
  
  scoped_ptr<CastSessionDelegate> delegate_;

  
  const scoped_refptr<base::MessageLoopProxy> io_message_loop_proxy_;

  DISALLOW_COPY_AND_ASSIGN(CastSession);
};

#endif  
