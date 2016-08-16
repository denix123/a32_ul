// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_DRIVE_FILEAPI_WEBKIT_FILE_STREAM_WRITER_IMPL_H_
#define CHROME_BROWSER_CHROMEOS_DRIVE_FILEAPI_WEBKIT_FILE_STREAM_WRITER_IMPL_H_

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/files/file.h"
#include "base/files/file_path.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "storage/browser/fileapi/file_stream_writer.h"

namespace base {
class TaskRunner;
}  

namespace net {
class IOBuffer;
}  

namespace drive {

class FileSystemInterface;

namespace internal {

class WebkitFileStreamWriterImpl : public storage::FileStreamWriter {
 public:
  
  
  
  
  typedef base::Callback<FileSystemInterface*()> FileSystemGetter;

  
  
  
  
  WebkitFileStreamWriterImpl(const FileSystemGetter& file_system_getter,
                             base::TaskRunner* file_task_runner,
                             const base::FilePath& file_path,
                             int64 offset);
  virtual ~WebkitFileStreamWriterImpl();

  
  virtual int Write(net::IOBuffer* buf, int buf_len,
                    const net::CompletionCallback& callback) OVERRIDE;
  virtual int Cancel(const net::CompletionCallback& callback) OVERRIDE;
  virtual int Flush(const net::CompletionCallback& callback) OVERRIDE;

 private:
  
  void WriteAfterCreateWritableSnapshotFile(
      net::IOBuffer* buf,
      int buf_len,
      base::File::Error open_result,
      const base::FilePath& local_path,
      const base::Closure& close_callback_on_ui_thread);

  FileSystemGetter file_system_getter_;
  scoped_refptr<base::TaskRunner> file_task_runner_;
  const base::FilePath file_path_;
  const int64 offset_;

  scoped_ptr<storage::FileStreamWriter> local_file_writer_;
  base::Closure close_callback_on_ui_thread_;
  net::CompletionCallback pending_write_callback_;
  net::CompletionCallback pending_cancel_callback_;

  
  
  base::WeakPtrFactory<WebkitFileStreamWriterImpl> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(WebkitFileStreamWriterImpl);
};

}  
}  

#endif  
