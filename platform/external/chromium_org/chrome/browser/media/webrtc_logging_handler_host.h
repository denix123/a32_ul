// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_MEDIA_WEBRTC_LOGGING_HANDLER_HOST_H_
#define CHROME_BROWSER_MEDIA_WEBRTC_LOGGING_HANDLER_HOST_H_

#include "base/basictypes.h"
#include "base/memory/shared_memory.h"
#include "chrome/browser/media/rtp_dump_type.h"
#include "chrome/browser/media/webrtc_rtp_dump_handler.h"
#include "chrome/common/media/webrtc_logging_message_data.h"
#include "content/public/browser/browser_message_filter.h"
#include "content/public/browser/render_process_host.h"
#include "net/base/net_util.h"

namespace net {
class URLRequestContextGetter;
}  

class PartialCircularBuffer;
class Profile;

typedef std::map<std::string, std::string> MetaDataMap;

class WebRtcLoggingHandlerHost : public content::BrowserMessageFilter {
 public:
  typedef base::Callback<void(bool, const std::string&)> GenericDoneCallback;
  typedef base::Callback<void(bool, const std::string&, const std::string&)>
      UploadDoneCallback;

  explicit WebRtcLoggingHandlerHost(Profile* profile);

  // Sets meta data that will be uploaded along with the log and also written
  
  
  void SetMetaData(const MetaDataMap& meta_data,
                   const GenericDoneCallback& callback);

  
  void StartLogging(const GenericDoneCallback& callback);

  
  
  void StopLogging(const GenericDoneCallback& callback);

  
  
  void UploadLog(const UploadDoneCallback& callback);

  
  
  void UploadLogDone();

  
  
  void DiscardLog(const GenericDoneCallback& callback);

  
  void LogMessage(const std::string& message);

  
  
  
  void set_upload_log_on_render_close(bool should_upload) {
    upload_log_on_render_close_ = should_upload;
  }

  
  
  
  
  void StartRtpDump(RtpDumpType type,
                    const GenericDoneCallback& callback,
                    const content::RenderProcessHost::WebRtcStopRtpDumpCallback&
                        stop_callback);

  
  
  
  
  void StopRtpDump(RtpDumpType type, const GenericDoneCallback& callback);

  
  
  void OnRtpPacket(scoped_ptr<uint8[]> packet_header,
                   size_t header_length,
                   size_t packet_length,
                   bool incoming);

 private:
  
  
  
  
  
  
  
  
  
  
  enum LoggingState {
    CLOSED,    
    STARTING,  
    STARTED,   
    STOPPING,  
    STOPPED,   
    UPLOADING  
  };

  friend class content::BrowserThread;
  friend class base::DeleteHelper<WebRtcLoggingHandlerHost>;

  virtual ~WebRtcLoggingHandlerHost();

  
  virtual void OnChannelClosing() OVERRIDE;
  virtual void OnDestruct() const OVERRIDE;
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;

  
  void OnAddLogMessages(const std::vector<WebRtcLoggingMessageData>& messages);
  void OnLoggingStoppedInRenderer();

  
  void AddLogMessageFromBrowser(const WebRtcLoggingMessageData& message);

  void StartLoggingIfAllowed();
  void DoStartLogging();
  void LogInitialInfoOnFileThread();
  void LogInitialInfoOnIOThread(const net::NetworkInterfaceList& network_list);
  void NotifyLoggingStarted();

  
  void LogToCircularBuffer(const std::string& message);

  
  
  base::FilePath GetLogDirectoryAndEnsureExists();

  void TriggerUpload(const base::FilePath& log_directory);

  
  void DoUploadLogAndRtpDumps(const base::FilePath& log_directory);

  void FireGenericDoneCallback(GenericDoneCallback* callback,
                               bool success,
                               const std::string& error_message);

  
  
  void CreateRtpDumpHandlerAndStart(RtpDumpType type,
                                    GenericDoneCallback callback,
                                    const base::FilePath& dump_dir);

  
  
  void DoStartRtpDump(RtpDumpType type, GenericDoneCallback* callback);

  
  void DumpRtpPacketOnIOThread(scoped_ptr<uint8[]> packet_header,
                               size_t header_length,
                               size_t packet_length,
                               bool incoming);

  scoped_ptr<unsigned char[]> log_buffer_;
  scoped_ptr<PartialCircularBuffer> circular_buffer_;

  
  Profile* profile_;

  
  
  
  MetaDataMap meta_data_;

  
  GenericDoneCallback start_callback_;
  GenericDoneCallback stop_callback_;
  UploadDoneCallback upload_callback_;

  
  
  
  
  LoggingState logging_state_;

  
  bool upload_log_on_render_close_;

  
  
  
  base::SharedMemoryHandle foreign_memory_handle_;

  
  
  base::Time logging_started_time_;

  
  scoped_ptr<WebRtcRtpDumpHandler> rtp_dump_handler_;

  
  content::RenderProcessHost::WebRtcStopRtpDumpCallback stop_rtp_dump_callback_;

  DISALLOW_COPY_AND_ASSIGN(WebRtcLoggingHandlerHost);
};

#endif  
