// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_INTERNAL_API_PUBLIC_ATTACHMENTS_ATTACHMENT_DOWNLOADER_H_
#define SYNC_INTERNAL_API_PUBLIC_ATTACHMENTS_ATTACHMENT_DOWNLOADER_H_

#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "google_apis/gaia/oauth2_token_service_request.h"
#include "sync/api/attachments/attachment.h"
#include "sync/base/sync_export.h"

namespace net {
class URLRequestContextGetter;
}  

namespace syncer {

class SYNC_EXPORT AttachmentDownloader {
 public:
  
  enum DownloadResult {
    DOWNLOAD_SUCCESS,            
                                 
    DOWNLOAD_TRANSIENT_ERROR,    
    DOWNLOAD_UNSPECIFIED_ERROR,  
  };

  typedef base::Callback<void(const DownloadResult&, scoped_ptr<Attachment>)>
      DownloadCallback;

  virtual ~AttachmentDownloader();

  
  
  
  
  
  virtual void DownloadAttachment(const AttachmentId& attachment_id,
                                  const DownloadCallback& callback) = 0;

  
  
  
  
  
  
  
  
  
  
  static scoped_ptr<AttachmentDownloader> Create(
      const GURL& sync_service_url,
      const scoped_refptr<net::URLRequestContextGetter>&
          url_request_context_getter,
      const std::string& account_id,
      const OAuth2TokenService::ScopeSet scopes,
      const scoped_refptr<OAuth2TokenServiceRequest::TokenServiceProvider>&
          token_service_provider);
};

}  

#endif  
