// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_MEDIA_WEBRTC_RTP_DUMP_WRITER_H_
#define CHROME_BROWSER_MEDIA_WEBRTC_RTP_DUMP_WRITER_H_

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/files/file_path.h"
#include "base/memory/weak_ptr.h"
#include "base/threading/thread_checker.h"
#include "base/time/time.h"
#include "chrome/browser/media/rtp_dump_type.h"

class WebRtcRtpDumpWriter {
 public:
  typedef base::Callback<void(bool incoming_succeeded, bool outgoing_succeeded)>
      EndDumpCallback;

  
  
  
  
  
  WebRtcRtpDumpWriter(const base::FilePath& incoming_dump_path,
                      const base::FilePath& outgoing_dump_path,
                      size_t max_dump_size,
                      const base::Closure& max_dump_size_reached_callback);

  virtual ~WebRtcRtpDumpWriter();

  
  
  virtual void WriteRtpPacket(const uint8* packet_header,
                              size_t header_length,
                              size_t packet_length,
                              bool incoming);

  
  
  
  
  
  virtual void EndDump(RtpDumpType type,
                       const EndDumpCallback& finished_callback);

  size_t max_dump_size() const;

 private:
  enum FlushResult {
    
    FLUSH_RESULT_SUCCESS,
    // Nothing has been written to disk and the dump is empty.
    FLUSH_RESULT_NO_DATA,
    
    FLUSH_RESULT_FAILURE
  };

  class FileThreadWorker;

  typedef base::Callback<void(bool)> FlushDoneCallback;

  
  struct EndDumpContext {
    EndDumpContext(RtpDumpType type, const EndDumpCallback& callback);
    ~EndDumpContext();

    RtpDumpType type;
    bool incoming_succeeded;
    bool outgoing_succeeded;
    EndDumpCallback callback;
  };

  
  
  
  
  void FlushBuffer(bool incoming,
                   bool end_stream,
                   const FlushDoneCallback& callback);

  
  
  
  void OnFlushDone(const FlushDoneCallback& callback,
                   const scoped_ptr<FlushResult>& result,
                   const scoped_ptr<size_t>& bytes_written);

  
  
  
  void OnDumpEnded(EndDumpContext context, bool incoming, bool success);

  
  const size_t max_dump_size_;

  
  const base::Closure max_dump_size_reached_callback_;

  
  std::vector<uint8> incoming_buffer_;
  std::vector<uint8> outgoing_buffer_;

  
  base::TimeTicks start_time_;

  
  size_t total_dump_size_on_disk_;

  
  scoped_ptr<FileThreadWorker> incoming_file_thread_worker_;
  scoped_ptr<FileThreadWorker> outgoing_file_thread_worker_;

  base::ThreadChecker thread_checker_;

  base::WeakPtrFactory<WebRtcRtpDumpWriter> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(WebRtcRtpDumpWriter);
};

#endif  
