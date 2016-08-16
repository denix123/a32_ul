// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SIGNIN_CORE_BROWSER_SIGNIN_MANAGER_COOKIE_HELPER_H_
#define COMPONENTS_SIGNIN_CORE_BROWSER_SIGNIN_MANAGER_COOKIE_HELPER_H_

#include "base/callback_helpers.h"
#include "base/memory/ref_counted.h"
#include "net/cookies/canonical_cookie.h"
#include "net/url_request/url_request_context_getter.h"

namespace base {
class MessageLoopProxy;
}

namespace net {
class URLRequestContextGetter;
}

class SigninManagerCookieHelper
    : public base::RefCountedThreadSafe<SigninManagerCookieHelper> {
 public:
  explicit SigninManagerCookieHelper(
      net::URLRequestContextGetter* request_context_getter,
      scoped_refptr<base::MessageLoopProxy> ui_thread,
      scoped_refptr<base::MessageLoopProxy> io_thread);

  
  
  void StartFetchingGaiaCookiesOnUIThread(
      const base::Callback<void(const net::CookieList& cookies)>& callback);

  
  
  void StartFetchingCookiesOnUIThread(
      const GURL& url,
      const base::Callback<void(const net::CookieList& cookies)>& callback);

 private:
  friend class base::RefCountedThreadSafe<SigninManagerCookieHelper>;
  ~SigninManagerCookieHelper();

  
  void FetchCookiesOnIOThread(const GURL& url);

  
  void OnCookiesFetched(const net::CookieList& cookies);

  
  void NotifyOnUIThread(const net::CookieList& cookies);

  scoped_refptr<net::URLRequestContextGetter> request_context_getter_;
  
  base::Callback<void(const net::CookieList& cookies)> completion_callback_;

  
  scoped_refptr<base::MessageLoopProxy> ui_thread_;
  
  scoped_refptr<base::MessageLoopProxy> io_thread_;
  DISALLOW_COPY_AND_ASSIGN(SigninManagerCookieHelper);
};

#endif  
