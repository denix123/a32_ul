// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_LOADER_REDIRECT_TO_FILE_RESOURCE_HANDLER_H_
#define CONTENT_BROWSER_LOADER_REDIRECT_TO_FILE_RESOURCE_HANDLER_H_

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/compiler_specific.h"
#include "base/files/file.h"
#include "base/files/file_path.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "content/browser/loader/layered_resource_handler.h"
#include "content/browser/loader/temporary_file_stream.h"
#include "content/common/content_export.h"
#include "net/url_request/url_request.h"
#include "net/url_request/url_request_status.h"
#include "url/gurl.h"

namespace net {
class FileStream;
class GrowableIOBuffer;
}

namespace storage {
class ShareableFileReference;
}

namespace content {

class CONTENT_EXPORT RedirectToFileResourceHandler
    : public LayeredResourceHandler {
 public:
  typedef base::Callback<void(const CreateTemporaryFileStreamCallback&)>
      CreateTemporaryFileStreamFunction;

  
  
  RedirectToFileResourceHandler(scoped_ptr<ResourceHandler> next_handler,
                                net::URLRequest* request);
  virtual ~RedirectToFileResourceHandler();

  
  
  
  
  void SetCreateTemporaryFileStreamFunctionForTesting(
      const CreateTemporaryFileStreamFunction& create_temporary_file_stream);

  
  virtual bool OnResponseStarted(ResourceResponse* response,
                                 bool* defer) OVERRIDE;
  virtual bool OnWillStart(const GURL& url, bool* defer) OVERRIDE;
  virtual bool OnWillRead(scoped_refptr<net::IOBuffer>* buf,
                          int* buf_size,
                          int min_size) OVERRIDE;
  virtual bool OnReadCompleted(int bytes_read, bool* defer) OVERRIDE;
  virtual void OnResponseCompleted(const net::URLRequestStatus& status,
                                   const std::string& security_info,
                                   bool* defer) OVERRIDE;

 private:
  void DidCreateTemporaryFile(base::File::Error error_code,
                              scoped_ptr<net::FileStream> file_stream,
                              storage::ShareableFileReference* deletable_file);

  
  void DidWriteToFile(int result);

  bool WriteMore();
  bool BufIsFull() const;
  void ResumeIfDeferred();

  CreateTemporaryFileStreamFunction create_temporary_file_stream_;

  
  
  
  
  
  

  scoped_refptr<net::GrowableIOBuffer> buf_;
  bool buf_write_pending_;
  int write_cursor_;

  
  
  
  class Writer;
  Writer* writer_;

  
  
  
  
  
  int next_buffer_size_;

  bool did_defer_;

  bool completed_during_write_;
  GURL will_start_url_;
  net::URLRequestStatus completed_status_;
  std::string completed_security_info_;

  base::WeakPtrFactory<RedirectToFileResourceHandler> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(RedirectToFileResourceHandler);
};

}  

#endif  
