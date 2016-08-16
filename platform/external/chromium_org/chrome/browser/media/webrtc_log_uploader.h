// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_MEDIA_WEBRTC_LOG_UPLOADER_H_
#define CHROME_BROWSER_MEDIA_WEBRTC_LOG_UPLOADER_H_

#include <map>
#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/gtest_prod_util.h"
#include "base/threading/thread_checker.h"
#include "chrome/browser/media/webrtc_logging_handler_host.h"
#include "net/url_request/url_fetcher_delegate.h"

class Profile;

namespace base {
class SharedMemory;
}

namespace net {
class URLFetcher;
}

typedef struct z_stream_s z_stream;

struct WebRtcLogUploadDoneData {
  WebRtcLogUploadDoneData();
  ~WebRtcLogUploadDoneData();

  base::FilePath log_path;
  base::FilePath incoming_rtp_dump;
  base::FilePath outgoing_rtp_dump;
  WebRtcLoggingHandlerHost::UploadDoneCallback callback;
  scoped_refptr<WebRtcLoggingHandlerHost> host;
  std::string local_log_id;
};

class WebRtcLogUploader : public net::URLFetcherDelegate {
 public:
  WebRtcLogUploader();
  virtual ~WebRtcLogUploader();

  
  virtual void OnURLFetchComplete(const net::URLFetcher* source) OVERRIDE;
  virtual void OnURLFetchUploadProgress(const net::URLFetcher* source,
                                        int64 current, int64 total) OVERRIDE;

  
  
  bool ApplyForStartLogging();

  
  
  
  
  
  void LoggingStoppedDontUpload();

  
  
  
  
  
  
  
  void LoggingStoppedDoUpload(
      scoped_ptr<unsigned char[]> log_buffer,
      uint32 length,
      const std::map<std::string, std::string>& meta_data,
      const WebRtcLogUploadDoneData& upload_done_data);

  
  
  
  void StartShutdown();

  
  // written to |post_data_| instead.
  void OverrideUploadWithBufferForTesting(std::string* post_data) {
    DCHECK((post_data && !post_data_) || (!post_data && post_data_));
    post_data_ = post_data;
  }

 private:
  FRIEND_TEST_ALL_PREFIXES(WebRtcLogUploaderTest,
                           AddLocallyStoredLogInfoToUploadListFile);
  FRIEND_TEST_ALL_PREFIXES(WebRtcLogUploaderTest,
                           AddUploadedLogInfoToUploadListFile);

  
  
  void SetupMultipart(std::string* post_data,
                      const std::vector<uint8>& compressed_log,
                      const base::FilePath& incoming_rtp_dump,
                      const base::FilePath& outgoing_rtp_dump,
                      const std::map<std::string, std::string>& meta_data);

  void CompressLog(std::vector<uint8>* compressed_log,
                   uint8* input,
                   uint32 input_size);

  void ResizeForNextOutput(std::vector<uint8>* compressed_log,
                           z_stream* stream);

  void CreateAndStartURLFetcher(
      const WebRtcLogUploadDoneData& upload_done_data,
      scoped_ptr<std::string> post_data);

  void DecreaseLogCount();

  
  void WriteCompressedLogToFile(const std::vector<uint8>& compressed_log,
                                const base::FilePath& log_file_path);

  
  
  
  
  
  
  
  
  
  
  
  
  // "upload_time" and "report_id" is the left empty in the entry written to the
  
  
  
  void AddLocallyStoredLogInfoToUploadListFile(
      const base::FilePath& upload_list_path,
      const std::string& local_log_id);
  void AddUploadedLogInfoToUploadListFile(
      const base::FilePath& upload_list_path,
      const std::string& local_log_id,
      const std::string& report_id);

  void NotifyUploadDone(int response_code,
                        const std::string& report_id,
                        const WebRtcLogUploadDoneData& upload_done_data);

  
  base::ThreadChecker create_thread_checker_;

  
  base::ThreadChecker file_thread_checker_;

  
  
  int log_count_;

  
  
  std::string* post_data_;

  typedef std::map<const net::URLFetcher*, WebRtcLogUploadDoneData>
      UploadDoneDataMap;
  
  UploadDoneDataMap upload_done_data_;

  
  bool shutting_down_;

  DISALLOW_COPY_AND_ASSIGN(WebRtcLogUploader);
};

#endif  
