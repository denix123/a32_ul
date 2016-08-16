// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_MEDIA_WEBRTC_RTP_DUMP_HANDLER_H_
#define CHROME_BROWSER_MEDIA_WEBRTC_RTP_DUMP_HANDLER_H_

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/files/file_path.h"
#include "base/memory/weak_ptr.h"
#include "chrome/browser/media/rtp_dump_type.h"

class WebRtcRtpDumpWriter;

class WebRtcRtpDumpHandler {
 public:
  typedef base::Callback<void(bool, const std::string&)> GenericDoneCallback;

  struct ReleasedDumps {
    ReleasedDumps(const base::FilePath& incoming_dump,
                  const base::FilePath& outgoing_dump)
        : incoming_dump_path(incoming_dump),
          outgoing_dump_path(outgoing_dump) {}

    const base::FilePath incoming_dump_path;
    const base::FilePath outgoing_dump_path;
  };

  
  
  
  
  
  
  explicit WebRtcRtpDumpHandler(const base::FilePath& dump_dir);
  ~WebRtcRtpDumpHandler();

  
  
  
  bool StartDump(RtpDumpType type, std::string* error_message);

  
  
  
  
  void StopDump(RtpDumpType type, const GenericDoneCallback& callback);

  
  
  bool ReadyToRelease() const;

  
  
  
  
  
  
  
  ReleasedDumps ReleaseDumps();

  
  
  void OnRtpPacket(const uint8* packet_header,
                   size_t header_length,
                   size_t packet_length,
                   bool incoming);

  
  void StopOngoingDumps(const base::Closure& callback);

 private:
  friend class WebRtcRtpDumpHandlerTest;

  
  
  
  
  
  
  enum State {
    STATE_NONE,
    STATE_STARTED,
    STATE_STOPPING,
    STATE_STOPPED,
  };

  
  void SetDumpWriterForTesting(scoped_ptr<WebRtcRtpDumpWriter> writer);

  
  void OnMaxDumpSizeReached();

  
  
  void OnDumpEnded(const base::Closure& callback,
                   RtpDumpType ended_type,
                   bool incoming_succeeded,
                   bool outgoing_succeeded);

  
  const base::FilePath dump_dir_;

  
  base::FilePath incoming_dump_path_;
  base::FilePath outgoing_dump_path_;

  
  State incoming_state_;
  State outgoing_state_;

  
  scoped_ptr<WebRtcRtpDumpWriter> dump_writer_;

  base::WeakPtrFactory<WebRtcRtpDumpHandler> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(WebRtcRtpDumpHandler);
};

#endif  
