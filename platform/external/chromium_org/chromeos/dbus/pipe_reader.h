// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_DBUS_PIPE_READER_H_
#define CHROMEOS_DBUS_PIPE_READER_H_

#include <string>

#include "base/callback.h"
#include "base/files/file.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"

namespace base {
class TaskRunner;
}

namespace net {
class FileStream;
class IOBufferWithSize;
}

namespace chromeos {

class PipeReader {
 public:
  typedef base::Callback<void(void)> IOCompleteCallback;

  PipeReader(const scoped_refptr<base::TaskRunner>& task_runner,
             const IOCompleteCallback& callback);
  virtual ~PipeReader();

  
  
  
  
  
  base::File StartIO();

  
  
  void OnDataReady(int byte_count);

  
  
  virtual void AcceptData(const char *data, int length) = 0;

 private:
  scoped_ptr<net::FileStream> data_stream_;
  scoped_refptr<net::IOBufferWithSize> io_buffer_;
  scoped_refptr<base::TaskRunner> task_runner_;
  IOCompleteCallback callback_;

  
  
  base::WeakPtrFactory<PipeReader> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(PipeReader);
};

class PipeReaderForString : public PipeReader {
 public:
  PipeReaderForString(const scoped_refptr<base::TaskRunner>& task_runner,
                      const IOCompleteCallback& callback);

  virtual void AcceptData(const char *data, int length) OVERRIDE;

  
  void GetData(std::string* data);

 private:
  std::string data_;

  DISALLOW_COPY_AND_ASSIGN(PipeReaderForString);
};

}  

#endif  
