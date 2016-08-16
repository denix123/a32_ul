// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PROFILES_PROFILE_IMPL_IO_DATA_H_
#define CHROME_BROWSER_PROFILES_PROFILE_IMPL_IO_DATA_H_

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/containers/hash_tables.h"
#include "base/memory/ref_counted.h"
#include "chrome/browser/custom_handlers/protocol_handler_registry.h"
#include "chrome/browser/net/chrome_url_request_context_getter.h"
#include "chrome/browser/profiles/profile_io_data.h"
#include "content/public/browser/cookie_store_factory.h"

namespace chrome_browser_net {
class Predictor;
}  

namespace content {
class CookieCryptoDelegate;
}  

namespace domain_reliability {
class DomainReliabilityMonitor;
}  

namespace net {
class FtpTransactionFactory;
class HttpServerProperties;
class HttpServerPropertiesManager;
class HttpTransactionFactory;
class ProxyConfig;
class SDCHManager;
}  

namespace storage {
class SpecialStoragePolicy;
}  

class ProfileImplIOData : public ProfileIOData {
 public:
  class Handle {
   public:
    explicit Handle(Profile* profile);
    ~Handle();

    
    
    void Init(
        const base::FilePath& cookie_path,
        const base::FilePath& channel_id_path,
        const base::FilePath& cache_path,
        int cache_max_size,
        const base::FilePath& media_cache_path,
        int media_cache_max_size,
        const base::FilePath& extensions_cookie_path,
        const base::FilePath& profile_path,
        const base::FilePath& infinite_cache_path,
        chrome_browser_net::Predictor* predictor,
        content::CookieStoreConfig::SessionCookieMode session_cookie_mode,
        storage::SpecialStoragePolicy* special_storage_policy,
        scoped_ptr<domain_reliability::DomainReliabilityMonitor>
            domain_reliability_monitor,
        const base::Callback<void(bool)>& data_reduction_proxy_unavailable,
        scoped_ptr<DataReductionProxyChromeConfigurator>
            data_reduction_proxy_chrome_configurator,
        scoped_ptr<data_reduction_proxy::DataReductionProxyParams>
            data_reduction_proxy_params,
        scoped_ptr<data_reduction_proxy::DataReductionProxyStatisticsPrefs>
            data_reduction_proxy_statistics_prefs);

    
    
    
    
    scoped_refptr<ChromeURLRequestContextGetter> CreateMainRequestContextGetter(
        content::ProtocolHandlerMap* protocol_handlers,
        content::URLRequestInterceptorScopedVector request_interceptors,
        PrefService* local_state,
        IOThread* io_thread) const;
    scoped_refptr<ChromeURLRequestContextGetter>
        CreateIsolatedAppRequestContextGetter(
            const base::FilePath& partition_path,
            bool in_memory,
            content::ProtocolHandlerMap* protocol_handlers,
            content::URLRequestInterceptorScopedVector
                request_interceptors) const;

    content::ResourceContext* GetResourceContext() const;
    
    
    content::ResourceContext* GetResourceContextNoInit() const;
    scoped_refptr<ChromeURLRequestContextGetter>
        GetMediaRequestContextGetter() const;
    scoped_refptr<ChromeURLRequestContextGetter>
        GetExtensionsRequestContextGetter() const;
    scoped_refptr<ChromeURLRequestContextGetter>
        GetIsolatedMediaRequestContextGetter(
            const base::FilePath& partition_path,
            bool in_memory) const;

    
    DevToolsNetworkController* GetDevToolsNetworkController() const;

    
    
    
    
    void ClearNetworkingHistorySince(base::Time time,
                                     const base::Closure& completion);

   private:
    typedef std::map<StoragePartitionDescriptor,
                     scoped_refptr<ChromeURLRequestContextGetter>,
                     StoragePartitionDescriptorLess>
      ChromeURLRequestContextGetterMap;

    
    
    
    
    
    void LazyInitialize() const;

    
    
    
    scoped_ptr<ChromeURLRequestContextGetterVector> GetAllContextGetters();

    
    
    mutable scoped_refptr<ChromeURLRequestContextGetter>
        main_request_context_getter_;
    mutable scoped_refptr<ChromeURLRequestContextGetter>
        media_request_context_getter_;
    mutable scoped_refptr<ChromeURLRequestContextGetter>
        extensions_request_context_getter_;
    mutable ChromeURLRequestContextGetterMap app_request_context_getter_map_;
    mutable ChromeURLRequestContextGetterMap
        isolated_media_request_context_getter_map_;
    ProfileImplIOData* const io_data_;

    Profile* const profile_;

    mutable bool initialized_;

    DISALLOW_COPY_AND_ASSIGN(Handle);
  };

 private:
  friend class base::RefCountedThreadSafe<ProfileImplIOData>;

  struct LazyParams {
    LazyParams();
    ~LazyParams();

    
    base::FilePath cookie_path;
    base::FilePath channel_id_path;
    base::FilePath cache_path;
    int cache_max_size;
    base::FilePath media_cache_path;
    int media_cache_max_size;
    base::FilePath extensions_cookie_path;
    base::FilePath infinite_cache_path;
    content::CookieStoreConfig::SessionCookieMode session_cookie_mode;
    scoped_refptr<storage::SpecialStoragePolicy> special_storage_policy;
  };

  ProfileImplIOData();
  virtual ~ProfileImplIOData();

  virtual void InitializeInternal(
      ProfileParams* profile_params,
      content::ProtocolHandlerMap* protocol_handlers,
      content::URLRequestInterceptorScopedVector request_interceptors)
          const OVERRIDE;
  virtual void InitializeExtensionsRequestContext(
      ProfileParams* profile_params) const OVERRIDE;
  virtual net::URLRequestContext* InitializeAppRequestContext(
      net::URLRequestContext* main_context,
      const StoragePartitionDescriptor& partition_descriptor,
      scoped_ptr<ProtocolHandlerRegistry::JobInterceptorFactory>
          protocol_handler_interceptor,
      content::ProtocolHandlerMap* protocol_handlers,
      content::URLRequestInterceptorScopedVector request_interceptors)
          const OVERRIDE;
  virtual net::URLRequestContext* InitializeMediaRequestContext(
      net::URLRequestContext* original_context,
      const StoragePartitionDescriptor& partition_descriptor) const OVERRIDE;
  virtual net::URLRequestContext*
      AcquireMediaRequestContext() const OVERRIDE;
  virtual net::URLRequestContext* AcquireIsolatedAppRequestContext(
      net::URLRequestContext* main_context,
      const StoragePartitionDescriptor& partition_descriptor,
      scoped_ptr<ProtocolHandlerRegistry::JobInterceptorFactory>
          protocol_handler_interceptor,
      content::ProtocolHandlerMap* protocol_handlers,
      content::URLRequestInterceptorScopedVector request_interceptors)
          const OVERRIDE;
  virtual net::URLRequestContext*
      AcquireIsolatedMediaRequestContext(
          net::URLRequestContext* app_context,
          const StoragePartitionDescriptor& partition_descriptor)
              const OVERRIDE;

  
  
  
  
  void ClearNetworkingHistorySinceOnIOThread(base::Time time,
                                             const base::Closure& completion);

  
  mutable scoped_ptr<LazyParams> lazy_params_;

  mutable scoped_ptr<net::HttpTransactionFactory> main_http_factory_;
  mutable scoped_ptr<net::FtpTransactionFactory> ftp_factory_;

  
  
  mutable net::HttpServerPropertiesManager* http_server_properties_manager_;

  mutable scoped_ptr<chrome_browser_net::Predictor> predictor_;

  mutable scoped_ptr<net::URLRequestContext> media_request_context_;

  mutable scoped_ptr<net::URLRequestJobFactory> main_job_factory_;
  mutable scoped_ptr<net::URLRequestJobFactory> extensions_job_factory_;

  mutable scoped_ptr<domain_reliability::DomainReliabilityMonitor>
      domain_reliability_monitor_;

  mutable scoped_ptr<net::SdchManager> sdch_manager_;

  
  base::FilePath profile_path_;
  int app_cache_max_size_;
  int app_media_cache_max_size_;

  DISALLOW_COPY_AND_ASSIGN(ProfileImplIOData);
};

#endif  
