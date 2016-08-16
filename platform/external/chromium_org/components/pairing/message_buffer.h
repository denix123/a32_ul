// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_PAIRING_MESSAGE_BUFFER_H_
#define COMPONENTS_PAIRING_MESSAGE_BUFFER_H_

#include <deque>

#include "base/logging.h"
#include "base/macros.h"
#include "base/memory/ref_counted.h"

namespace net {
class IOBuffer;
}

namespace pairing_chromeos {

class MessageBuffer {
 public:
  MessageBuffer();
  ~MessageBuffer();

  
  int AvailableBytes();

  
  
  void ReadBytes(char* buffer, int size);

  
  
  void AddIOBuffer(scoped_refptr<net::IOBuffer> io_buffer, int size);

 private:
  
  int buffer_offset_;
  
  
  int total_buffer_size_;
  std::deque<std::pair<scoped_refptr<net::IOBuffer>, int> > pending_data_;

  DISALLOW_COPY_AND_ASSIGN(MessageBuffer);
};

}  

#endif  
