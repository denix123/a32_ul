// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_CRONET_ANDROID_URL_REQUEST_ADAPTER_H_
#define COMPONENTS_CRONET_ANDROID_URL_REQUEST_ADAPTER_H_

#include <jni.h>

#include <string>

#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "net/base/request_priority.h"
#include "net/http/http_request_headers.h"
#include "net/url_request/url_request.h"

namespace net {
class GrowableIOBuffer;
class HttpResponseHeaders;
class UploadDataStream;
}  

namespace cronet {

class URLRequestContextAdapter;

class URLRequestAdapter : public net::URLRequest::Delegate {
 public:
  
  class URLRequestAdapterDelegate
      : public base::RefCountedThreadSafe<URLRequestAdapterDelegate> {
   public:
    virtual void OnResponseStarted(URLRequestAdapter* request) = 0;
    virtual void OnBytesRead(URLRequestAdapter* request) = 0;
    virtual void OnRequestFinished(URLRequestAdapter* request) = 0;
    virtual int ReadFromUploadChannel(net::IOBuffer* buf, int buf_length) = 0;

   protected:
    friend class base::RefCountedThreadSafe<URLRequestAdapterDelegate>;
    virtual ~URLRequestAdapterDelegate() {}
  };

  URLRequestAdapter(URLRequestContextAdapter* context,
                    URLRequestAdapterDelegate* delegate,
                    GURL url,
                    net::RequestPriority priority);
  virtual ~URLRequestAdapter();

  
  void SetMethod(const std::string& method);

  
  void AddHeader(const std::string& name, const std::string& value);

  
  void SetUploadContent(const char* bytes, int bytes_len);

  
  void SetUploadChannel(JNIEnv* env, int64 content_length);

  
  
  void EnableChunkedUpload();

  
  
  void AppendChunk(const char* bytes, int bytes_len, bool is_last_chunk);

  
  void Start();

  
  void Cancel();

  
  void Destroy();

  
  GURL url() const { return url_; }

  
  
  int error_code() const { return error_code_; }

  
  int http_status_code() const {
    return http_status_code_;
  };

  
  int64 content_length() const { return expected_size_; }

  
  std::string content_type() const { return content_type_; }

  
  std::string GetHeader(const std::string& name) const;

  
  net::HttpResponseHeaders* GetResponseHeaders() const;

  
  size_t bytes_read() const { return bytes_read_; }

  
  unsigned char* Data() const;

  
  std::string GetNegotiatedProtocol() const;

  virtual void OnResponseStarted(net::URLRequest* request) OVERRIDE;

  virtual void OnReadCompleted(net::URLRequest* request,
                               int bytes_read) OVERRIDE;

 private:
  static void OnDestroyRequest(URLRequestAdapter* self);

  void OnInitiateConnection();
  void OnCancelRequest();
  void OnRequestSucceeded();
  void OnRequestFailed();
  void OnRequestCompleted();
  void OnRequestCanceled();
  void OnBytesRead(int bytes_read);
  void OnAppendChunk(const scoped_ptr<char[]> bytes, int bytes_len,
                     bool is_last_chunk);

  void Read();

  URLRequestContextAdapter* context_;
  scoped_refptr<URLRequestAdapterDelegate> delegate_;
  GURL url_;
  net::RequestPriority priority_;
  std::string method_;
  net::HttpRequestHeaders headers_;
  scoped_ptr<net::URLRequest> url_request_;
  scoped_ptr<net::UploadDataStream> upload_data_stream_;
  scoped_refptr<net::GrowableIOBuffer> read_buffer_;
  int bytes_read_;
  int total_bytes_read_;
  int error_code_;
  int http_status_code_;
  std::string content_type_;
  bool canceled_;
  int64 expected_size_;
  bool chunked_upload_;

  DISALLOW_COPY_AND_ASSIGN(URLRequestAdapter);
};

}  

#endif  
