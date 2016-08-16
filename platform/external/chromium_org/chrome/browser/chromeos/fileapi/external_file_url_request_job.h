// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_FILEAPI_EXTERNAL_FILE_URL_REQUEST_JOB_H_
#define CHROME_BROWSER_CHROMEOS_FILEAPI_EXTERNAL_FILE_URL_REQUEST_JOB_H_

#include <string>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/memory/weak_ptr.h"
#include "chrome/browser/chromeos/drive/file_errors.h"
#include "net/base/net_errors.h"
#include "net/http/http_byte_range.h"
#include "net/url_request/url_request_job.h"
#include "storage/browser/blob/file_stream_reader.h"
#include "storage/browser/fileapi/file_system_url.h"

namespace net {
class IOBuffer;
class NetworkDelegate;
class URLRequest;
}  

namespace chromeos {

class ExternalFileURLRequestJob : public net::URLRequestJob {
 public:
  
  
  typedef base::Callback<
      void(net::Error,
           const scoped_refptr<storage::FileSystemContext>& file_system_context,
           const storage::FileSystemURL& file_system_url,
           const std::string& mime_type)> HelperCallback;

  ExternalFileURLRequestJob(void* profile_id,
                            net::URLRequest* request,
                            net::NetworkDelegate* network_delegate);

  
  virtual void SetExtraRequestHeaders(
      const net::HttpRequestHeaders& headers) OVERRIDE;
  virtual void Start() OVERRIDE;
  virtual void Kill() OVERRIDE;
  virtual bool GetMimeType(std::string* mime_type) const OVERRIDE;
  virtual bool IsRedirectResponse(GURL* location,
                                  int* http_status_code) OVERRIDE;
  virtual bool ReadRawData(net::IOBuffer* buf,
                           int buf_size,
                           int* bytes_read) OVERRIDE;

 protected:
  virtual ~ExternalFileURLRequestJob();

 private:
  
  
  void OnHelperResultObtained(
      net::Error error,
      const scoped_refptr<storage::FileSystemContext>& file_system_context,
      const storage::FileSystemURL& file_system_url,
      const std::string& mime_type);

  
  void OnRedirectURLObtained(const GURL& redirect_url);

  
  void OnFileInfoObtained(base::File::Error result,
                          const base::File::Info& file_info);

  
  void OnReadCompleted(int read_result);

  void* const profile_id_;

  
  net::HttpByteRange byte_range_;
  int64 remaining_bytes_;

  scoped_refptr<storage::FileSystemContext> file_system_context_;
  storage::FileSystemURL file_system_url_;
  std::string mime_type_;
  scoped_ptr<storage::FileStreamReader> stream_reader_;
  GURL redirect_url_;

  
  
  base::WeakPtrFactory<ExternalFileURLRequestJob> weak_ptr_factory_;
  DISALLOW_COPY_AND_ASSIGN(ExternalFileURLRequestJob);
};

}  

#endif  
