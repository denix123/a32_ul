// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_MEDIA_GALLERIES_FILEAPI_READAHEAD_FILE_STREAM_READER_H_
#define CHROME_BROWSER_MEDIA_GALLERIES_FILEAPI_READAHEAD_FILE_STREAM_READER_H_

#include <queue>

#include "base/memory/weak_ptr.h"
#include "net/base/io_buffer.h"
#include "storage/browser/blob/file_stream_reader.h"

class ReadaheadFileStreamReader
    : public NON_EXPORTED_BASE(storage::FileStreamReader) {
 public:
  
  explicit ReadaheadFileStreamReader(storage::FileStreamReader* source);

  virtual ~ReadaheadFileStreamReader();

  
  virtual int Read(net::IOBuffer* buf, int buf_len,
                   const net::CompletionCallback& callback) OVERRIDE;
  virtual int64 GetLength(
      const net::Int64CompletionCallback& callback) OVERRIDE;

 private:
  
  
  int FinishReadFromCacheOrStoredError(net::DrainableIOBuffer* sink);

  
  
  
  void ReadFromSourceIfNeeded();
  void OnFinishReadFromSource(net::IOBuffer* buffer, int result);

  
  scoped_ptr<storage::FileStreamReader> source_;

  
  
  int source_error_;
  bool source_has_pending_read_;

  
  
  std::queue<scoped_refptr<net::DrainableIOBuffer> > buffers_;

  
  
  scoped_refptr<net::DrainableIOBuffer> pending_sink_buffer_;
  net::CompletionCallback pending_read_callback_;

  base::WeakPtrFactory<ReadaheadFileStreamReader> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(ReadaheadFileStreamReader);
};

#endif  
