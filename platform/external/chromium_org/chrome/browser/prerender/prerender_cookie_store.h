// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PRERENDER_PRERENDER_COOKIE_STORE_H_
#define CHROME_BROWSER_PRERENDER_PRERENDER_COOKIE_STORE_H_

#include <set>
#include <string>
#include <vector>

#include "base/callback.h"
#include "base/compiler_specific.h"
#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "net/cookies/cookie_monster.h"
#include "net/cookies/cookie_store.h"
#include "url/gurl.h"

namespace prerender {

class PrerenderCookieStore : public net::CookieStore {
 public:
  
  
  
  
  
  
  
  
  PrerenderCookieStore(scoped_refptr<net::CookieMonster> default_cookie_store_,
                       const base::Closure& cookie_conflict_cb);

  
  virtual void SetCookieWithOptionsAsync(
      const GURL& url,
      const std::string& cookie_line,
      const net::CookieOptions& options,
      const SetCookiesCallback& callback) OVERRIDE;

  virtual void GetCookiesWithOptionsAsync(
      const GURL& url,
      const net::CookieOptions& options,
      const GetCookiesCallback& callback) OVERRIDE;

  virtual void GetAllCookiesForURLAsync(
      const GURL& url,
      const GetCookieListCallback& callback) OVERRIDE;

  virtual void DeleteCookieAsync(const GURL& url,
                                 const std::string& cookie_name,
                                 const base::Closure& callback) OVERRIDE;

  
  
  
  
  

  virtual void DeleteAllCreatedBetweenAsync(
      const base::Time& delete_begin,
      const base::Time& delete_end,
      const DeleteCallback& callback) OVERRIDE;

  virtual void DeleteAllCreatedBetweenForHostAsync(
      const base::Time delete_begin,
      const base::Time delete_end,
      const GURL& url,
      const DeleteCallback& callback) OVERRIDE;

  virtual void DeleteSessionCookiesAsync(const DeleteCallback&) OVERRIDE;

  virtual net::CookieMonster* GetCookieMonster() OVERRIDE;

  
  
  
  
  void ApplyChanges(std::vector<GURL>* cookie_change_urls);

  
  
  
  void OnCookieChangedForURL(net::CookieMonster* cookie_monster,
                             const GURL& url);

  net::CookieMonster* default_cookie_monster() {
    return default_cookie_monster_.get();
  }

 private:
  enum CookieOperationType {
    COOKIE_OP_SET_COOKIE_WITH_OPTIONS_ASYNC,
    COOKIE_OP_GET_COOKIES_WITH_OPTIONS_ASYNC,
    COOKIE_OP_GET_ALL_COOKIES_FOR_URL_ASYNC,
    COOKIE_OP_DELETE_COOKIE_ASYNC,
    COOKIE_OP_MAX
  };

  struct CookieOperation {
    CookieOperationType op;
    GURL url;
    net::CookieOptions options;
    std::string cookie_line;
    std::string cookie_name;
    CookieOperation();
    ~CookieOperation();
  };

  virtual ~PrerenderCookieStore();

  
  
  net::CookieStore* GetCookieStoreForCookieOpAndLog(const CookieOperation& op);

  
  
  bool in_forwarding_mode_;

  
  scoped_refptr<net::CookieMonster> default_cookie_monster_;

  
  
  
  scoped_refptr<net::CookieMonster> changes_cookie_monster_;

  
  std::vector<CookieOperation> cookie_ops_;

  
  std::set<std::string> copied_keys_;

  
  std::set<std::string> read_keys_;

  
  base::Closure cookie_conflict_cb_;

  
  bool cookie_conflict_;

  DISALLOW_COPY_AND_ASSIGN(PrerenderCookieStore);
};

}  

#endif  
