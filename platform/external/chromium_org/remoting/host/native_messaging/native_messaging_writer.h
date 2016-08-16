// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_HOST_NATIVE_MESSAGING_NATIVE_MESSAGING_WRITER_H_
#define REMOTING_HOST_NATIVE_MESSAGING_NATIVE_MESSAGING_WRITER_H_

#include "base/files/file.h"

namespace base {
class Value;
}  

namespace remoting {

class NativeMessagingWriter {
 public:
  explicit NativeMessagingWriter(base::File file);
  ~NativeMessagingWriter();

  
  
  bool WriteMessage(const base::Value& message);

 private:
  base::File write_stream_;
  bool fail_;

  DISALLOW_COPY_AND_ASSIGN(NativeMessagingWriter);
};

}  

#endif  
