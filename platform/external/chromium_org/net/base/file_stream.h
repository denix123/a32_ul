// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef NET_BASE_FILE_STREAM_H_
#define NET_BASE_FILE_STREAM_H_

#include "base/files/file.h"
#include "net/base/completion_callback.h"
#include "net/base/net_export.h"

namespace base {
class FilePath;
class TaskRunner;
}

namespace net {

class IOBuffer;

class NET_EXPORT FileStream {
 public:
  
  
  explicit FileStream(const scoped_refptr<base::TaskRunner>& task_runner);

  
  
  FileStream(base::File file,
             const scoped_refptr<base::TaskRunner>& task_runner);

  
  virtual ~FileStream();

  
  
  
  
  
  
  
  
  
  
  
  
  
  virtual int Open(const base::FilePath& path, int open_flags,
                   const CompletionCallback& callback);

  
  
  
  
  virtual int Close(const CompletionCallback& callback);

  
  virtual bool IsOpen() const;

  
  
  
  
  
  
  virtual int Seek(base::File::Whence whence, int64 offset,
                   const Int64CompletionCallback& callback);

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  virtual int Read(IOBuffer* buf, int buf_len,
                   const CompletionCallback& callback);

  
  // asynchronously.  Up to buf_len bytes will be written from buf. (In
  
  // bytes written, or an error code if the operation could not be
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  virtual int Write(IOBuffer* buf, int buf_len,
                    const CompletionCallback& callback);

  
  // written out to disk and is not currently sitting in the buffer. This does
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  virtual int Flush(const CompletionCallback& callback);

  
  const base::File& GetFileForTesting() const;

 private:
  class Context;

  
  
  
  
  
  scoped_ptr<Context> context_;

  DISALLOW_COPY_AND_ASSIGN(FileStream);
};

}  

#endif  
