// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ANDROID_WEBVIEW_NATIVE_PERMISSION_PERMISSION_REQUEST_HANDLER_H
#define ANDROID_WEBVIEW_NATIVE_PERMISSION_PERMISSION_REQUEST_HANDLER_H

#include <map>
#include <vector>

#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "content/public/browser/web_contents_observer.h"
#include "url/gurl.h"

namespace android_webview {

class AwPermissionRequest;
class AwPermissionRequestDelegate;
class PermissionRequestHandlerClient;

class PermissionRequestHandler : public content::WebContentsObserver {
 public:
  PermissionRequestHandler(PermissionRequestHandlerClient* client,
                           content::WebContents* aw_contents);
  virtual ~PermissionRequestHandler();

  
  void SendRequest(scoped_ptr<AwPermissionRequestDelegate> request);

  
  void CancelRequest(const GURL& origin, int64 resources);

  
  void PreauthorizePermission(const GURL& origin, int64 resources);

  
  virtual void NavigationEntryCommitted(
      const content::LoadCommittedDetails& load_details) OVERRIDE;

 private:
  friend class TestPermissionRequestHandler;

  typedef std::vector<base::WeakPtr<AwPermissionRequest> >::iterator
      RequestIterator;

  
  RequestIterator FindRequest(const GURL& origin, int64 resources);

  
  void CancelRequest(RequestIterator i);

  void CancelAllRequests();

  
  void PruneRequests();

  
  bool Preauthorized(const GURL& origin, int64 resources);

  PermissionRequestHandlerClient* client_;

  
  std::vector<base::WeakPtr<AwPermissionRequest> > requests_;

  std::map<std::string, int64> preauthorized_permission_;

  
  
  int contents_unique_id_;

  DISALLOW_COPY_AND_ASSIGN(PermissionRequestHandler);
};

}  

#endif  
