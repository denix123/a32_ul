// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STORAGE_BROWSER_FILEAPI_LOCAL_FILE_STREAM_WRITER_H_
#define STORAGE_BROWSER_FILEAPI_LOCAL_FILE_STREAM_WRITER_H_

#include <utility>

#include "base/callback.h"
#include "base/compiler_specific.h"
#include "base/files/file_path.h"
#include "base/gtest_prod_util.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/task_runner.h"
#include "storage/browser/fileapi/file_stream_writer.h"
#include "storage/browser/storage_browser_export.h"

namespace content {
class LocalFileStreamWriterTest;
}

namespace net {
class FileStream;
}

namespace storage {

class STORAGE_EXPORT LocalFileStreamWriter
    : public NON_EXPORTED_BASE(FileStreamWriter) {
 public:
  virtual ~LocalFileStreamWriter();

  
  virtual int Write(net::IOBuffer* buf, int buf_len,
                    const net::CompletionCallback& callback) OVERRIDE;
  virtual int Cancel(const net::CompletionCallback& callback) OVERRIDE;
  virtual int Flush(const net::CompletionCallback& callback) OVERRIDE;

 private:
  friend class content::LocalFileStreamWriterTest;
  friend class FileStreamWriter;
  LocalFileStreamWriter(base::TaskRunner* task_runner,
                        const base::FilePath& file_path,
                        int64 initial_offset,
                        OpenOrCreate open_or_create);

  
  
  int InitiateOpen(const net::CompletionCallback& error_callback,
                   const base::Closure& main_operation);
  void DidOpen(const net::CompletionCallback& error_callback,
               const base::Closure& main_operation,
               int result);

  
  
  void InitiateSeek(const net::CompletionCallback& error_callback,
                    const base::Closure& main_operation);
  void DidSeek(const net::CompletionCallback& error_callback,
               const base::Closure& main_operation,
               int64 result);

  
  void ReadyToWrite(net::IOBuffer* buf, int buf_len,
                    const net::CompletionCallback& callback);

  
  int InitiateWrite(net::IOBuffer* buf, int buf_len,
                    const net::CompletionCallback& callback);
  void DidWrite(const net::CompletionCallback& callback, int result);

  
  int InitiateFlush(const net::CompletionCallback& callback);
  void DidFlush(const net::CompletionCallback& callback, int result);

  
  
  bool CancelIfRequested();

  
  const base::FilePath file_path_;
  OpenOrCreate open_or_create_;
  const int64 initial_offset_;
  scoped_refptr<base::TaskRunner> task_runner_;

  
  bool has_pending_operation_;
  scoped_ptr<net::FileStream> stream_impl_;
  net::CompletionCallback cancel_callback_;

  base::WeakPtrFactory<LocalFileStreamWriter> weak_factory_;
  DISALLOW_COPY_AND_ASSIGN(LocalFileStreamWriter);
};

}  

#endif  