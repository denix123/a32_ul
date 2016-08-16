// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_FILE_SYSTEM_PROVIDER_FILEAPI_FILE_STREAM_READER_H_
#define CHROME_BROWSER_CHROMEOS_FILE_SYSTEM_PROVIDER_FILEAPI_FILE_STREAM_READER_H_

#include "base/basictypes.h"
#include "base/files/file_path.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "storage/browser/blob/file_stream_reader.h"
#include "storage/browser/fileapi/file_system_url.h"

namespace chromeos {
namespace file_system_provider {

struct EntryMetadata;
class ProvidedFileSystemInterface;

class FileStreamReader : public storage::FileStreamReader {
 public:
  typedef base::Callback<
      void(base::WeakPtr<ProvidedFileSystemInterface> file_system,
           const base::FilePath& file_path,
           int file_handle,
           base::File::Error result)> OpenFileCompletedCallback;

  FileStreamReader(storage::FileSystemContext* context,
                   const storage::FileSystemURL& url,
                   int64 initial_offset,
                   const base::Time& expected_modification_time);

  virtual ~FileStreamReader();

  
  virtual int Read(net::IOBuffer* buf,
                   int buf_len,
                   const net::CompletionCallback& callback) OVERRIDE;
  virtual int64 GetLength(
      const net::Int64CompletionCallback& callback) OVERRIDE;

 private:
  
  
  
  class OperationRunner;

  
  enum State { NOT_INITIALIZED, INITIALIZING, INITIALIZED, FAILED };

  
  
  void OnReadCompleted(net::CompletionCallback callback, int result);

  
  
  void Initialize(const base::Closure& pending_closure,
                  const net::Int64CompletionCallback& error_callback);

  
  void OnOpenFileCompleted(
      const base::Closure& pending_closure,
      const net::Int64CompletionCallback& error_callback,
      base::File::Error result);

  
  void OnInitializeCompleted(const base::Closure& pending_closure,
                             const net::Int64CompletionCallback& error_callback,
                             scoped_ptr<EntryMetadata> metadata,
                             base::File::Error result);

  
  
  
  
  void OnReadChunkReceived(const net::CompletionCallback& callback,
                           int chunk_length,
                           bool has_more,
                           base::File::Error result);

  
  
  void OnGetMetadataForGetLengthReceived(
      const net::Int64CompletionCallback& callback,
      scoped_ptr<EntryMetadata> metadata,
      base::File::Error result);

  
  void ReadAfterInitialized(scoped_refptr<net::IOBuffer> buffer,
                            int buffer_length,
                            const net::CompletionCallback& callback);

  
  void GetLengthAfterInitialized(const net::Int64CompletionCallback& callback);

  storage::FileSystemURL url_;
  int64 current_offset_;
  int64 current_length_;
  base::Time expected_modification_time_;
  scoped_refptr<OperationRunner> runner_;
  State state_;

  base::WeakPtrFactory<FileStreamReader> weak_ptr_factory_;
  DISALLOW_COPY_AND_ASSIGN(FileStreamReader);
};

}  
}  

#endif  
