// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_HOST_GNUBBY_SOCKET_H_
#define REMOTING_HOST_GNUBBY_SOCKET_H_

#include <string>
#include <vector>

#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "base/threading/non_thread_safe.h"

namespace base {
class Timer;
}  

namespace net {
class StreamListenSocket;
}  

namespace remoting {

class GnubbySocket : public base::NonThreadSafe {
 public:
  GnubbySocket(scoped_ptr<net::StreamListenSocket> socket,
               const base::Closure& timeout_callback);
  ~GnubbySocket();

  
  void AddRequestData(const char* data, int data_len);

  
  void GetAndClearRequestData(std::string* data_out);

  
  bool IsRequestComplete() const;

  
  bool IsRequestTooLarge() const;

  
  void SendResponse(const std::string& data);

  
  void SendSshError();

  
  bool IsSocket(net::StreamListenSocket* socket) const;

  
  void SetTimerForTesting(scoped_ptr<base::Timer> timer);

 private:
  
  size_t GetRequestLength() const;

  
  std::string GetResponseLengthAsBytes(const std::string& response) const;

  
  void ResetTimer();

  
  scoped_ptr<net::StreamListenSocket> socket_;

  
  std::vector<char> request_data_;

  
  scoped_ptr<base::Timer> timer_;

  DISALLOW_COPY_AND_ASSIGN(GnubbySocket);
};

}  

#endif  
