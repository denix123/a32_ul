// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_DRIVE_LOCAL_FILE_READER_H_
#define CHROME_BROWSER_CHROMEOS_DRIVE_LOCAL_FILE_READER_H_

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "net/base/completion_callback.h"
#include "net/base/file_stream.h"

namespace base {
class FilePath;
class SequencedTaskRunner;
}  

namespace net {
class IOBuffer;
}  

namespace drive {
namespace util {

class LocalFileReader {
 public:
  explicit LocalFileReader(base::SequencedTaskRunner* sequenced_task_runner);
  ~LocalFileReader();

  
  
  
  
  void Open(const base::FilePath& file_path,
            int64 offset,
            const net::CompletionCallback& callback);

  
  
  
  
  void Read(net::IOBuffer* buffer,
            int buffer_length,
            const net::CompletionCallback& callback);

 private:
  void DidOpen(const net::CompletionCallback& callback,
               int64 offset,
               int error);
  void DidSeek(const net::CompletionCallback& callback,
               int64 offset,
               int64 error);

  net::FileStream file_stream_;

  
  
  base::WeakPtrFactory<LocalFileReader> weak_ptr_factory_;
  DISALLOW_COPY_AND_ASSIGN(LocalFileReader);
};

}  
}  

#endif  
