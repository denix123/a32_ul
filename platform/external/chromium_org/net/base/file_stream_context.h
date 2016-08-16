// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef NET_BASE_FILE_STREAM_CONTEXT_H_
#define NET_BASE_FILE_STREAM_CONTEXT_H_

#include "base/files/file.h"
#include "base/message_loop/message_loop.h"
#include "base/move.h"
#include "base/task_runner.h"
#include "net/base/completion_callback.h"
#include "net/base/file_stream.h"

#if defined(OS_POSIX)
#include <errno.h>
#endif

namespace base {
class FilePath;
}

namespace net {

class IOBuffer;

#if defined(OS_WIN)
class FileStream::Context : public base::MessageLoopForIO::IOHandler {
#elif defined(OS_POSIX)
class FileStream::Context {
#endif
 public:
  
  
  
  

  explicit Context(const scoped_refptr<base::TaskRunner>& task_runner);
  Context(base::File file, const scoped_refptr<base::TaskRunner>& task_runner);
#if defined(OS_WIN)
  virtual ~Context();
#elif defined(OS_POSIX)
  ~Context();
#endif

  int Read(IOBuffer* buf,
           int buf_len,
           const CompletionCallback& callback);

  int Write(IOBuffer* buf,
            int buf_len,
            const CompletionCallback& callback);

  const base::File& file() const { return file_; }
  bool async_in_progress() const { return async_in_progress_; }

  
  
  

  
  
  
  void Orphan();

  void Open(const base::FilePath& path,
            int open_flags,
            const CompletionCallback& callback);

  void Close(const CompletionCallback& callback);

  void Seek(base::File::Whence whence,
            int64 offset,
            const Int64CompletionCallback& callback);

  void Flush(const CompletionCallback& callback);

 private:
  struct IOResult {
    IOResult();
    IOResult(int64 result, int os_error);
    static IOResult FromOSError(int64 os_error);

    int64 result;
    int os_error;  
  };

  struct OpenResult {
    MOVE_ONLY_TYPE_FOR_CPP_03(OpenResult, RValue)
   public:
    OpenResult();
    OpenResult(base::File file, IOResult error_code);
    
    OpenResult(RValue other);
    OpenResult& operator=(RValue other);

    base::File file;
    IOResult error_code;
  };

  
  
  

  OpenResult OpenFileImpl(const base::FilePath& path, int open_flags);

  IOResult CloseFileImpl();

  IOResult FlushFileImpl();

  void OnOpenCompleted(const CompletionCallback& callback,
                       OpenResult open_result);

  void CloseAndDelete();

  Int64CompletionCallback IntToInt64(const CompletionCallback& callback);

  
  
  void OnAsyncCompleted(const Int64CompletionCallback& callback,
                        const IOResult& result);

  
  
  
  

  
  IOResult SeekFileImpl(base::File::Whence whence, int64 offset);

  void OnFileOpened();

#if defined(OS_WIN)
  void IOCompletionIsPending(const CompletionCallback& callback, IOBuffer* buf);

  
  virtual void OnIOCompleted(base::MessageLoopForIO::IOContext* context,
                             DWORD bytes_read,
                             DWORD error) OVERRIDE;
#elif defined(OS_POSIX)
  
  
  IOResult ReadFileImpl(scoped_refptr<IOBuffer> buf, int buf_len);

  
  
  
  IOResult WriteFileImpl(scoped_refptr<IOBuffer> buf, int buf_len);
#endif

  base::File file_;
  bool async_in_progress_;
  bool orphaned_;
  scoped_refptr<base::TaskRunner> task_runner_;

#if defined(OS_WIN)
  base::MessageLoopForIO::IOContext io_context_;
  CompletionCallback callback_;
  scoped_refptr<IOBuffer> in_flight_buf_;
#endif

  DISALLOW_COPY_AND_ASSIGN(Context);
};

}  

#endif  
