// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_UPDATER_EXTENSION_DOWNLOADER_H_
#define CHROME_BROWSER_EXTENSIONS_UPDATER_EXTENSION_DOWNLOADER_H_

#include <deque>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/linked_ptr.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/version.h"
#include "chrome/browser/extensions/updater/extension_downloader_delegate.h"
#include "chrome/browser/extensions/updater/request_queue.h"
#include "extensions/browser/updater/manifest_fetch_data.h"
#include "extensions/common/extension.h"
#include "extensions/common/update_manifest.h"
#include "google_apis/gaia/oauth2_token_service.h"
#include "net/url_request/url_fetcher_delegate.h"
#include "url/gurl.h"

class IdentityProvider;

namespace net {
class URLFetcher;
class URLRequestContextGetter;
class URLRequestStatus;
}

namespace extensions {

struct UpdateDetails {
  UpdateDetails(const std::string& id, const base::Version& version);
  ~UpdateDetails();

  std::string id;
  base::Version version;
};

class ExtensionCache;
class ExtensionUpdaterTest;

class ExtensionDownloader
    : public net::URLFetcherDelegate,
      public OAuth2TokenService::Consumer {
 public:
  
  
  typedef base::Callback<
      scoped_ptr<ExtensionDownloader>(ExtensionDownloaderDelegate* delegate)>
      Factory;

  
  
  ExtensionDownloader(ExtensionDownloaderDelegate* delegate,
                      net::URLRequestContextGetter* request_context);
  virtual ~ExtensionDownloader();

  
  
  
  
  
  
  bool AddExtension(const Extension& extension, int request_id);

  
  
  
  
  
  
  bool AddPendingExtension(const std::string& id,
                           const GURL& update_url,
                           int request_id);

  
  
  void StartAllPending(ExtensionCache* cache);

  
  void StartBlacklistUpdate(const std::string& version,
                            const ManifestFetchData::PingData& ping_data,
                            int request_id);

  
  
  void SetWebstoreIdentityProvider(
      scoped_ptr<IdentityProvider> identity_provider);

  void set_brand_code(const std::string& brand_code) {
    brand_code_ = brand_code;
  }

  void set_manifest_query_params(const std::string& params) {
    manifest_query_params_ = params;
  }

  void set_ping_enabled_domain(const std::string& domain) {
    ping_enabled_domain_ = domain;
  }

  void set_enable_extra_update_metrics(bool enable) {
    enable_extra_update_metrics_ = enable;
  }

  
  
  static const int kManifestFetcherId = 1;
  static const int kExtensionFetcherId = 2;

  
  static const char kBlacklistAppID[];

  static const int kMaxRetries = 10;

 private:
  friend class ExtensionUpdaterTest;

  
  
  struct URLStats {
    URLStats()
        : no_url_count(0),
          google_url_count(0),
          other_url_count(0),
          extension_count(0),
          theme_count(0),
          app_count(0),
          platform_app_count(0),
          pending_count(0) {}

    int no_url_count, google_url_count, other_url_count;
    int extension_count, theme_count, app_count, platform_app_count,
        pending_count;
  };

  
  
  struct ExtensionFetch {
    ExtensionFetch();
    ExtensionFetch(const std::string& id, const GURL& url,
                   const std::string& package_hash, const std::string& version,
                   const std::set<int>& request_ids);
    ~ExtensionFetch();

    std::string id;
    GURL url;
    std::string package_hash;
    std::string version;
    std::set<int> request_ids;

    enum CredentialsMode {
      CREDENTIALS_NONE = 0,
      CREDENTIALS_OAUTH2_TOKEN,
      CREDENTIALS_COOKIES,
    };

    
    CredentialsMode credentials;

    
    
    int oauth2_attempt_count;
  };

  
  bool AddExtensionData(const std::string& id,
                        const base::Version& version,
                        Manifest::Type extension_type,
                        const GURL& extension_update_url,
                        const std::string& update_url_data,
                        int request_id,
                        bool force_update,
                        const std::string& install_source_override);

  
  void ReportStats() const;

  
  void StartUpdateCheck(scoped_ptr<ManifestFetchData> fetch_data);

  
  void CreateManifestFetcher();

  
  virtual void OnURLFetchComplete(const net::URLFetcher* source) OVERRIDE;

  
  void OnManifestFetchComplete(const GURL& url,
                               const net::URLRequestStatus& status,
                               int response_code,
                               const base::TimeDelta& backoff_delay,
                               const std::string& data);

  
  
  void HandleManifestResults(const ManifestFetchData& fetch_data,
                             const UpdateManifest::Results* results);

  
  
  void DetermineUpdates(const ManifestFetchData& fetch_data,
                        const UpdateManifest::Results& possible_updates,
                        std::vector<int>* result);

  
  void FetchUpdatedExtension(scoped_ptr<ExtensionFetch> fetch_data);

  
  void CreateExtensionFetcher();

  
  void OnCRXFetchComplete(const net::URLFetcher* source,
                          const GURL& url,
                          const net::URLRequestStatus& status,
                          int response_code,
                          const base::TimeDelta& backoff_delay);

  
  
  void NotifyExtensionsDownloadFailed(const std::set<std::string>& id_set,
                                      const std::set<int>& request_ids,
                                      ExtensionDownloaderDelegate::Error error);

  
  
  void NotifyUpdateFound(const std::string& id, const std::string& version);

  
  
  void DoStartAllPending();

  
  void NotifyDelegateDownloadFinished(scoped_ptr<ExtensionFetch> fetch_data,
                                      const base::FilePath& crx_path,
                                      bool file_ownership_passed);

  
  
  
  bool IterateFetchCredentialsAfterFailure(ExtensionFetch* fetch,
                                           const net::URLRequestStatus& status,
                                           int response_code);

  
  virtual void OnGetTokenSuccess(const OAuth2TokenService::Request* request,
                                 const std::string& access_token,
                                 const base::Time& expiration_time) OVERRIDE;
  virtual void OnGetTokenFailure(const OAuth2TokenService::Request* request,
                                 const GoogleServiceAuthError& error) OVERRIDE;

  ManifestFetchData* CreateManifestFetchData(const GURL& update_url,
                                             int request_id);

  
  
  ExtensionDownloaderDelegate* delegate_;

  
  scoped_refptr<net::URLRequestContextGetter> request_context_;

  
  URLStats url_stats_;

  
  
  
  
  typedef std::map<std::pair<int, GURL>,
                   std::vector<linked_ptr<ManifestFetchData> > > FetchMap;
  FetchMap fetches_preparing_;

  
  scoped_ptr<net::URLFetcher> manifest_fetcher_;
  scoped_ptr<net::URLFetcher> extension_fetcher_;

  
  
  RequestQueue<ManifestFetchData> manifests_queue_;
  RequestQueue<ExtensionFetch> extensions_queue_;

  
  std::map<std::string, ExtensionDownloaderDelegate::PingResult> ping_results_;

  
  ExtensionCache* extension_cache_;

  
  
  scoped_ptr<IdentityProvider> identity_provider_;

  
  
  std::string access_token_;

  
  scoped_ptr<OAuth2TokenService::Request> access_token_request_;

  
  std::string brand_code_;

  
  std::string manifest_query_params_;

  
  
  std::string ping_enabled_domain_;

  
  
  bool enable_extra_update_metrics_;

  
  base::WeakPtrFactory<ExtensionDownloader> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(ExtensionDownloader);
};

}  

#endif  
