// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_SERVICE_WORKER_SERVICE_WORKER_URL_REQUEST_JOB_H_
#define CONTENT_BROWSER_SERVICE_WORKER_SERVICE_WORKER_URL_REQUEST_JOB_H_

#include <map>
#include <string>

#include "base/memory/weak_ptr.h"
#include "base/time/time.h"
#include "content/common/content_export.h"
#include "content/common/service_worker/service_worker_status_code.h"
#include "content/common/service_worker/service_worker_types.h"
#include "net/http/http_byte_range.h"
#include "net/url_request/url_request.h"
#include "net/url_request/url_request_job.h"

namespace storage {
class BlobDataHandle;
class BlobStorageContext;
}

namespace content {

class ResourceRequestBody;
class ServiceWorkerContextCore;
class ServiceWorkerFetchDispatcher;
class ServiceWorkerProviderHost;

class CONTENT_EXPORT ServiceWorkerURLRequestJob
    : public net::URLRequestJob,
      public net::URLRequest::Delegate {
 public:
  ServiceWorkerURLRequestJob(
      net::URLRequest* request,
      net::NetworkDelegate* network_delegate,
      base::WeakPtr<ServiceWorkerProviderHost> provider_host,
      base::WeakPtr<storage::BlobStorageContext> blob_storage_context,
      scoped_refptr<ResourceRequestBody> body);

  
  void FallbackToNetwork();
  void ForwardToServiceWorker();

  bool ShouldFallbackToNetwork() const {
    return response_type_ == FALLBACK_TO_NETWORK;
  }
  bool ShouldForwardToServiceWorker() const {
    return response_type_ == FORWARD_TO_SERVICE_WORKER;
  }

  
  virtual void Start() OVERRIDE;
  virtual void Kill() OVERRIDE;
  virtual net::LoadState GetLoadState() const OVERRIDE;
  virtual bool GetCharset(std::string* charset) OVERRIDE;
  virtual bool GetMimeType(std::string* mime_type) const OVERRIDE;
  virtual void GetResponseInfo(net::HttpResponseInfo* info) OVERRIDE;
  virtual void GetLoadTimingInfo(
      net::LoadTimingInfo* load_timing_info) const OVERRIDE;
  virtual int GetResponseCode() const OVERRIDE;
  virtual void SetExtraRequestHeaders(
      const net::HttpRequestHeaders& headers) OVERRIDE;
  virtual bool ReadRawData(net::IOBuffer* buf,
                           int buf_size,
                           int *bytes_read) OVERRIDE;

  
  
  virtual void OnReceivedRedirect(net::URLRequest* request,
                                  const net::RedirectInfo& redirect_info,
                                  bool* defer_redirect) OVERRIDE;
  virtual void OnAuthRequired(net::URLRequest* request,
                              net::AuthChallengeInfo* auth_info) OVERRIDE;
  virtual void OnCertificateRequested(
      net::URLRequest* request,
      net::SSLCertRequestInfo* cert_request_info) OVERRIDE;
  virtual void OnSSLCertificateError(net::URLRequest* request,
                                     const net::SSLInfo& ssl_info,
                                     bool fatal) OVERRIDE;
  virtual void OnBeforeNetworkStart(net::URLRequest* request,
                                    bool* defer) OVERRIDE;
  virtual void OnResponseStarted(net::URLRequest* request) OVERRIDE;
  virtual void OnReadCompleted(net::URLRequest* request,
                               int bytes_read) OVERRIDE;

  const net::HttpResponseInfo* http_info() const;

  void GetExtraResponseInfo(bool* was_fetched_via_service_worker,
                            GURL* original_url_via_service_worker,
                            base::TimeTicks* fetch_start_time,
                            base::TimeTicks* fetch_ready_time,
                            base::TimeTicks* fetch_end_time) const;

 protected:
  virtual ~ServiceWorkerURLRequestJob();

 private:
  enum ResponseType {
    NOT_DETERMINED,
    FALLBACK_TO_NETWORK,
    FORWARD_TO_SERVICE_WORKER,
  };

  
  
  void MaybeStartRequest();
  void StartRequest();

  
  scoped_ptr<ServiceWorkerFetchRequest> CreateFetchRequest();

  
  
  
  bool CreateRequestBodyBlob(std::string* blob_uuid, uint64* blob_size);

  
  void DidPrepareFetchEvent();
  void DidDispatchFetchEvent(ServiceWorkerStatusCode status,
                             ServiceWorkerFetchEventResult fetch_result,
                             const ServiceWorkerResponse& response);

  
  void CreateResponseHeader(int status_code,
                            const std::string& status_text,
                            const ServiceWorkerHeaderMap& headers);

  
  
  void CommitResponseHeader();

  
  void DeliverErrorResponse();

  base::WeakPtr<ServiceWorkerProviderHost> provider_host_;

  
  net::LoadTimingInfo load_timing_info_;
  base::TimeTicks fetch_start_time_;
  base::TimeTicks fetch_ready_time_;
  base::TimeTicks fetch_end_time_;
  base::Time response_time_;

  ResponseType response_type_;
  bool is_started_;

  net::HttpByteRange byte_range_;
  scoped_ptr<net::HttpResponseInfo> range_response_info_;
  scoped_ptr<net::HttpResponseInfo> http_response_info_;
  
  scoped_refptr<net::HttpResponseHeaders> http_response_headers_;
  GURL response_url_;

  
  scoped_ptr<ServiceWorkerFetchDispatcher> fetch_dispatcher_;
  base::WeakPtr<storage::BlobStorageContext> blob_storage_context_;
  scoped_ptr<net::URLRequest> blob_request_;
  
  
  scoped_refptr<ResourceRequestBody> body_;
  scoped_ptr<storage::BlobDataHandle> request_body_blob_data_handle_;

  base::WeakPtrFactory<ServiceWorkerURLRequestJob> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(ServiceWorkerURLRequestJob);
};

}  

#endif  
