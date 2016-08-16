// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_BROWSER_COOKIE_STORE_FACTORY_H_
#define CONTENT_PUBLIC_BROWSER_COOKIE_STORE_FACTORY_H_

#include "base/files/file_path.h"
#include "base/memory/ref_counted.h"
#include "content/common/content_export.h"

namespace base {
class SequencedTaskRunner;
}

namespace net {
class CookieMonsterDelegate;
class CookieStore;
}

namespace storage {
class SpecialStoragePolicy;
}

namespace content {
class CookieCryptoDelegate;

struct CONTENT_EXPORT CookieStoreConfig {
  
  
  // EPHEMERAL_SESSION_COOKIES specifies session cookies will not be written
  
  
  
  // when the cookie store is opened, however they will be written in a manner
  
  
  
  
  // except when the cookie store is opened, the previously written session
  
  enum SessionCookieMode {
    EPHEMERAL_SESSION_COOKIES,
    PERSISTANT_SESSION_COOKIES,
    RESTORED_SESSION_COOKIES
  };

  
  CookieStoreConfig();

  
  
  
  
  
  
  CookieStoreConfig(const base::FilePath& path,
                    SessionCookieMode session_cookie_mode,
                    storage::SpecialStoragePolicy* storage_policy,
                    net::CookieMonsterDelegate* cookie_delegate);
  ~CookieStoreConfig();

  const base::FilePath path;
  const SessionCookieMode session_cookie_mode;
  const scoped_refptr<storage::SpecialStoragePolicy> storage_policy;
  const scoped_refptr<net::CookieMonsterDelegate> cookie_delegate;

  
  
  
  

  
  
  
  content::CookieCryptoDelegate* crypto_delegate;

  
  
  
  
  scoped_refptr<base::SequencedTaskRunner> client_task_runner;

  
  
  
  
  
  scoped_refptr<base::SequencedTaskRunner> background_task_runner;
};

CONTENT_EXPORT net::CookieStore* CreateCookieStore(
    const CookieStoreConfig& config);

}  

#endif  
