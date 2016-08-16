// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_FILE_SYSTEM_PROVIDER_FILEAPI_FILE_STREAM_WRITER_H_
#define CHROME_BROWSER_CHROMEOS_FILE_SYSTEM_PROVIDER_FILEAPI_FILE_STREAM_WRITER_H_

#include "base/basictypes.h"
#include "base/files/file.h"
#include "base/files/file_path.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "storage/browser/fileapi/file_stream_writer.h"
#include "storage/browser/fileapi/file_system_url.h"

namespace chromeos {
namespace file_system_provider {

class ProvidedFileSystemInterface;

class FileStreamWriter : public storage::FileStreamWriter {
 public:
  FileStreamWriter(const storage::FileSystemURL& url, int64 initial_offset);

  virtual ~FileStreamWriter();

  
  virtual int Write(net::IOBuffer* buf,
                    int buf_len,
                    const net::CompletionCallback& callback) OVERRIDE;
  virtual int Cancel(const net::CompletionCallback& callback) OVERRIDE;
  virtual int Flush(const net::CompletionCallback& callback) OVERRIDE;

 private:
  
  
  
  class OperationRunner;

  
  enum State { NOT_INITIALIZED, INITIALIZING, INITIALIZED, FAILED };

  
  void OnWriteFileCompleted(int buffer_length,
                            const net::CompletionCallback& callback,
                            base::File::Error result);

  
  
  void OnWriteCompleted(net::CompletionCallback callback, int result);

  
  
  void OnAbortCompleted(const net::CompletionCallback& callback,
                        base::File::Error result);

  
  
  void Initialize(const base::Closure& pending_closure,
                  const net::CompletionCallback& error_callback);

  
  void OnOpenFileCompleted(
      const base::Closure& pending_closure,
      const net::CompletionCallback& error_callback,
      base::File::Error result);

  
  void WriteAfterInitialized(scoped_refptr<net::IOBuffer> buffer,
                             int buffer_length,
                             const net::CompletionCallback& callback);

  storage::FileSystemURL url_;
  int64 current_offset_;
  scoped_refptr<OperationRunner> runner_;
  State state_;

  base::WeakPtrFactory<FileStreamWriter> weak_ptr_factory_;
  DISALLOW_COPY_AND_ASSIGN(FileStreamWriter);
};

}  
}  

#endif  
