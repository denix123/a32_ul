// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SEARCH_PROVIDER_LOGOS_LOGO_TRACKER_H_
#define COMPONENTS_SEARCH_PROVIDER_LOGOS_LOGO_TRACKER_H_

#include <string>
#include <vector>

#include "base/callback.h"
#include "base/files/file_path.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "base/sequenced_task_runner.h"
#include "base/time/clock.h"
#include "base/time/time.h"
#include "components/search_provider_logos/logo_cache.h"
#include "components/search_provider_logos/logo_common.h"
#include "net/url_request/url_fetcher_delegate.h"
#include "url/gurl.h"

namespace net {
class URLFetcher;
class URLRequestContextGetter;
}

namespace search_provider_logos {

class LogoObserver {
 public:
  virtual ~LogoObserver() {}

  
  
  
  
  
  
  virtual void OnLogoAvailable(const Logo* logo, bool from_cache) = 0;

  
  
  
  
  
  virtual void OnObserverRemoved() = 0;
};

class LogoDelegate {
 public:
  virtual ~LogoDelegate() {}

  
  
  
  
  
  virtual void DecodeUntrustedImage(
      const scoped_refptr<base::RefCountedString>& encoded_image,
      base::Callback<void(const SkBitmap&)> image_decoded_callback) = 0;
};

typedef base::Callback<
    scoped_ptr<EncodedLogo>(const scoped_ptr<std::string>& response,
                            base::Time response_time)> ParseLogoResponse;

typedef base::Callback<
    GURL(const GURL& logo_url, const std::string& fingerprint)>
    AppendFingerprintToLogoURL;

class LogoTracker : public net::URLFetcherDelegate {
 public:
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  explicit LogoTracker(
      base::FilePath cached_logo_directory,
      scoped_refptr<base::SequencedTaskRunner> file_task_runner,
      scoped_refptr<base::TaskRunner> background_task_runner,
      scoped_refptr<net::URLRequestContextGetter> request_context_getter,
      scoped_ptr<LogoDelegate> delegate);

  virtual ~LogoTracker();

  
  
  
  
  
  
  
  
  
  
  
  
  
  void SetServerAPI(const GURL& logo_url,
                    const ParseLogoResponse& parse_logo_response_func,
                    const AppendFingerprintToLogoURL& append_fingerprint_func);

  
  
  
  void GetLogo(LogoObserver* observer);

  
  
  void RemoveObserver(LogoObserver* observer);

  
  void SetLogoCacheForTests(scoped_ptr<LogoCache> cache);

  
  void SetClockForTests(scoped_ptr<base::Clock> clock);

 private:
  
  
  void ReturnToIdle();

  
  
  void OnCachedLogoRead(scoped_ptr<EncodedLogo> cached_logo);

  
  
  void OnCachedLogoAvailable(const LogoMetadata& metadata,
                             const SkBitmap& image);

  
  void SetCachedLogo(scoped_ptr<EncodedLogo> logo);

  
  void SetCachedMetadata(const LogoMetadata& metadata);

  
  void FetchLogo();

  
  
  void OnFreshLogoParsed(scoped_ptr<EncodedLogo> logo);

  
  
  void OnFreshLogoAvailable(scoped_ptr<EncodedLogo> logo,
                            const SkBitmap& image);

  
  virtual void OnURLFetchComplete(const net::URLFetcher* source) OVERRIDE;
  virtual void OnURLFetchDownloadProgress(const net::URLFetcher* source,
                                          int64 current,
                                          int64 total) OVERRIDE;

  
  GURL logo_url_;

  
  ParseLogoResponse parse_logo_response_func_;

  
  AppendFingerprintToLogoURL append_fingerprint_func_;

  
  bool is_idle_;

  
  
  scoped_ptr<Logo> cached_logo_;

  
  
  
  
  bool is_cached_logo_valid_;

  
  scoped_ptr<net::URLFetcher> fetcher_;

  
  
  ObserverList<LogoObserver> logo_observers_;

  scoped_ptr<LogoDelegate> logo_delegate_;

  
  LogoCache* logo_cache_;

  
  scoped_ptr<base::Clock> clock_;

  
  scoped_refptr<base::SequencedTaskRunner> file_task_runner_;

  
  scoped_refptr<base::TaskRunner> background_task_runner_;

  
  scoped_refptr<net::URLRequestContextGetter> request_context_getter_;

  base::WeakPtrFactory<LogoTracker> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(LogoTracker);
};

}  

#endif  
