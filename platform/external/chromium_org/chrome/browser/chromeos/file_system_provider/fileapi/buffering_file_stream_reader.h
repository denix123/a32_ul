// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_FILE_SYSTEM_PROVIDER_FILEAPI_BUFFERING_FILE_STREAM_READER_H_
#define CHROME_BROWSER_CHROMEOS_FILE_SYSTEM_PROVIDER_FILEAPI_BUFFERING_FILE_STREAM_READER_H_

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "storage/browser/blob/file_stream_reader.h"

namespace net {
class IOBuffer;
}  

namespace chromeos {
namespace file_system_provider {

class BufferingFileStreamReader : public storage::FileStreamReader {
 public:
  BufferingFileStreamReader(
      scoped_ptr<storage::FileStreamReader> file_stream_reader,
      int preloading_buffer_length,
      int64 max_bytes_to_read);

  virtual ~BufferingFileStreamReader();

  
  virtual int Read(net::IOBuffer* buf,
                   int buf_len,
                   const net::CompletionCallback& callback) OVERRIDE;
  virtual int64 GetLength(
      const net::Int64CompletionCallback& callback) OVERRIDE;

 private:
  
  
  int CopyFromPreloadingBuffer(scoped_refptr<net::IOBuffer> buffer,
                               int buffer_length);

  
  void Preload(const net::CompletionCallback& callback);

  void OnReadCompleted(const net::CompletionCallback& callback, int result);

  
  
  void OnPreloadCompleted(scoped_refptr<net::IOBuffer> buffer,
                          int buffer_length,
                          const net::CompletionCallback& callback,
                          int result);

  scoped_ptr<storage::FileStreamReader> file_stream_reader_;
  int preloading_buffer_length_;
  int64 max_bytes_to_read_;
  int64 bytes_read_;
  scoped_refptr<net::IOBuffer> preloading_buffer_;
  int preloading_buffer_offset_;
  int preloaded_bytes_;

  base::WeakPtrFactory<BufferingFileStreamReader> weak_ptr_factory_;
  DISALLOW_COPY_AND_ASSIGN(BufferingFileStreamReader);
};

}  
}  

#endif  
