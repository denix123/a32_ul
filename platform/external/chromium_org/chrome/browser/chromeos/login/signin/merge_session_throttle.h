// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_LOGIN_SIGNIN_MERGE_SESSION_THROTTLE_H_
#define CHROME_BROWSER_CHROMEOS_LOGIN_SIGNIN_MERGE_SESSION_THROTTLE_H_

#include <set>

#include "base/atomic_ref_count.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "content/public/browser/resource_throttle.h"
#include "content/public/common/resource_type.h"
#include "net/base/completion_callback.h"

class Profile;

namespace net {
class URLRequest;
}

namespace chromeos {
class OAuth2LoginManager;
}

class MergeSessionThrottle
    : public content::ResourceThrottle,
      public base::SupportsWeakPtr<MergeSessionThrottle> {
 public:
  
  
  typedef base::Closure CompletionCallback;

  explicit MergeSessionThrottle(net::URLRequest* request,
                                content::ResourceType resource_type);
  virtual ~MergeSessionThrottle();

  
  virtual void WillStartRequest(bool* defer) OVERRIDE;
  virtual const char* GetNameForLogging() const OVERRIDE;

  
  static bool AreAllSessionMergedAlready();

 private:

  
  void OnBlockingPageComplete();

  
  void ClearRequestInfo();
  bool IsRemote(const GURL& url) const;

  
  
  bool ShouldDelayUrl(const GURL& url) const;

  
  static void BlockProfile(Profile* profile);
  static void UnblockProfile(Profile* profile);

  
  
  
  static bool ShouldDelayRequest(int render_process_id,
                                 int render_view_id);

  
  
  
  
  static void DeleayResourceLoadingOnUIThread(
      content::ResourceType resource_type,
      int render_process_id,
      int render_view_id,
      const GURL& url,
      const MergeSessionThrottle::CompletionCallback& callback);

  net::URLRequest* request_;
  content::ResourceType resource_type_;

  
  
  
  
  
  static base::AtomicRefCount all_profiles_restored_;

  DISALLOW_COPY_AND_ASSIGN(MergeSessionThrottle);
};

#endif  
