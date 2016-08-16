// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_UTILITY_MEDIA_GALLERIES_IPC_DATA_SOURCE_H_
#define CHROME_UTILITY_MEDIA_GALLERIES_IPC_DATA_SOURCE_H_

#include <map>
#include <string>

#include "base/memory/ref_counted.h"
#include "base/threading/thread_checker.h"
#include "chrome/utility/utility_message_handler.h"
#include "media/base/data_source.h"

namespace base {
class TaskRunner;
}

namespace metadata {

class IPCDataSource: public media::DataSource,
                     public UtilityMessageHandler {
 public:
  
  explicit IPCDataSource(int64 total_size);
  virtual ~IPCDataSource();

  
  
  virtual void Stop() OVERRIDE;
  virtual void Read(int64 position, int size, uint8* data,
                    const ReadCB& read_cb) OVERRIDE;
  virtual bool GetSize(int64* size_out) OVERRIDE;
  virtual bool IsStreaming() OVERRIDE;
  virtual void SetBitrate(int bitrate) OVERRIDE;

  
  
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;

 private:
  struct Request {
    Request();
    ~Request();
    uint8* destination;
    ReadCB callback;
  };

  void ReadOnUtilityThread(int64 position, int size, uint8* data,
                           const ReadCB& read_cb);

  void OnRequestBlobBytesFinished(int64 request_id,
                                  const std::string& bytes);

  const int64 total_size_;

  scoped_refptr<base::TaskRunner> utility_task_runner_;
  std::map<int64, Request> pending_requests_;
  int64 next_request_id_;

  base::ThreadChecker utility_thread_checker_;

  
  base::ThreadChecker data_source_thread_checker_;
};

}  

#endif  
