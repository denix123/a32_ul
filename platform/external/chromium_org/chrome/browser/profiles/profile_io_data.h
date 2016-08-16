// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PROFILES_PROFILE_IO_DATA_H_
#define CHROME_BROWSER_PROFILES_PROFILE_IO_DATA_H_

#include <map>
#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/callback_forward.h"
#include "base/files/file_path.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/prefs/pref_member.h"
#include "base/synchronization/lock.h"
#include "chrome/browser/custom_handlers/protocol_handler_registry.h"
#include "chrome/browser/io_thread.h"
#include "chrome/browser/net/spdyproxy/data_reduction_proxy_chrome_configurator.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/profiles/storage_partition_descriptor.h"
#include "components/content_settings/core/common/content_settings_types.h"
#include "components/data_reduction_proxy/browser/data_reduction_proxy_auth_request_handler.h"
#include "components/data_reduction_proxy/browser/data_reduction_proxy_statistics_prefs.h"
#include "components/data_reduction_proxy/browser/data_reduction_proxy_usage_stats.h"
#include "content/public/browser/content_browser_client.h"
#include "content/public/browser/resource_context.h"
#include "net/cookies/cookie_monster.h"
#include "net/http/http_cache.h"
#include "net/http/http_network_session.h"
#include "net/url_request/url_request_context.h"
#include "net/url_request/url_request_job_factory.h"

class ChromeHttpUserAgentSettings;
class ChromeNetworkDelegate;
class ChromeURLRequestContextGetter;
class CookieSettings;
class DevToolsNetworkController;
class HostContentSettingsMap;
class MediaDeviceIDSalt;
class ProtocolHandlerRegistry;
class SigninNamesOnIOThread;
class SupervisedUserURLFilter;

namespace chrome_browser_net {
class ResourcePrefetchPredictorObserver;
}

namespace extensions {
class InfoMap;
}

namespace net {
class CertVerifier;
class ChannelIDService;
class CookieStore;
class FraudulentCertificateReporter;
class FtpTransactionFactory;
class HttpServerProperties;
class HttpTransactionFactory;
class ProxyConfigService;
class ProxyService;
class SSLConfigService;
class TransportSecurityPersister;
class TransportSecurityState;
class URLRequestJobFactoryImpl;
}  

namespace policy {
class PolicyCertVerifier;
class PolicyHeaderIOHelper;
class URLBlacklistManager;
}  

namespace prerender {
class PrerenderTracker;
}

class ProfileIOData {
 public:
  typedef std::vector<scoped_refptr<ChromeURLRequestContextGetter>>
      ChromeURLRequestContextGetterVector;

  virtual ~ProfileIOData();

  static ProfileIOData* FromResourceContext(content::ResourceContext* rc);

  
  
  static bool IsHandledProtocol(const std::string& scheme);

  
  
  static bool IsHandledURL(const GURL& url);

  
  
  
  static void InstallProtocolHandlers(
      net::URLRequestJobFactoryImpl* job_factory,
      content::ProtocolHandlerMap* protocol_handlers);

  
  content::ResourceContext* GetResourceContext() const;

  
  
  
  void Init(
      content::ProtocolHandlerMap* protocol_handlers,
      content::URLRequestInterceptorScopedVector request_interceptors) const;

  net::URLRequestContext* GetMainRequestContext() const;
  net::URLRequestContext* GetMediaRequestContext() const;
  net::URLRequestContext* GetExtensionsRequestContext() const;
  net::URLRequestContext* GetIsolatedAppRequestContext(
      net::URLRequestContext* main_context,
      const StoragePartitionDescriptor& partition_descriptor,
      scoped_ptr<ProtocolHandlerRegistry::JobInterceptorFactory>
          protocol_handler_interceptor,
      content::ProtocolHandlerMap* protocol_handlers,
      content::URLRequestInterceptorScopedVector request_interceptors) const;
  net::URLRequestContext* GetIsolatedMediaRequestContext(
      net::URLRequestContext* app_context,
      const StoragePartitionDescriptor& partition_descriptor) const;

  
  
  
  extensions::InfoMap* GetExtensionInfoMap() const;
  CookieSettings* GetCookieSettings() const;
  HostContentSettingsMap* GetHostContentSettingsMap() const;

  IntegerPrefMember* session_startup_pref() const {
    return &session_startup_pref_;
  }

  SigninNamesOnIOThread* signin_names() const {
    return signin_names_.get();
  }

  StringPrefMember* google_services_account_id() const {
    return &google_services_user_account_id_;
  }

  StringPrefMember* google_services_username() const {
    return &google_services_username_;
  }

  StringPrefMember* google_services_username_pattern() const {
    return &google_services_username_pattern_;
  }

  BooleanPrefMember* reverse_autologin_enabled() const {
    return &reverse_autologin_enabled_;
  }

  const std::string& reverse_autologin_pending_email() const {
    return reverse_autologin_pending_email_;
  }

  void set_reverse_autologin_pending_email(const std::string& email) {
    reverse_autologin_pending_email_ = email;
  }

  StringListPrefMember* one_click_signin_rejected_email_list() const {
    return &one_click_signin_rejected_email_list_;
  }

  net::URLRequestContext* extensions_request_context() const {
    return extensions_request_context_.get();
  }

  BooleanPrefMember* safe_browsing_enabled() const {
    return &safe_browsing_enabled_;
  }

  
  
  BooleanPrefMember* data_reduction_proxy_enabled() const {
    return &data_reduction_proxy_enabled_;
  }

  BooleanPrefMember* printing_enabled() const {
    return &printing_enabled_;
  }

  BooleanPrefMember* sync_disabled() const {
    return &sync_disabled_;
  }

  BooleanPrefMember* signin_allowed() const {
    return &signin_allowed_;
  }

  IntegerPrefMember* network_prediction_options() const {
    return &network_prediction_options_;
  }

  content::ResourceContext::SaltCallback GetMediaDeviceIDSalt() const;

  DevToolsNetworkController* network_controller() const {
    return network_controller_.get();
  }

  net::TransportSecurityState* transport_security_state() const {
    return transport_security_state_.get();
  }

#if defined(OS_CHROMEOS)
  std::string username_hash() const {
    return username_hash_;
  }

  bool use_system_key_slot() const { return use_system_key_slot_; }
#endif

  Profile::ProfileType profile_type() const {
    return profile_type_;
  }

  bool IsOffTheRecord() const;

  IntegerPrefMember* incognito_availibility() const {
    return &incognito_availibility_pref_;
  }

  chrome_browser_net::ResourcePrefetchPredictorObserver*
      resource_prefetch_predictor_observer() const {
    return resource_prefetch_predictor_observer_.get();
  }

#if defined(ENABLE_CONFIGURATION_POLICY)
  policy::PolicyHeaderIOHelper* policy_header_helper() const {
    return policy_header_helper_.get();
  }
#endif

#if defined(ENABLE_MANAGED_USERS)
  const SupervisedUserURLFilter* supervised_user_url_filter() const {
    return supervised_user_url_filter_.get();
  }
#endif

  
  
  void InitializeMetricsEnabledStateOnUIThread();

  
  
  
  bool GetMetricsEnabledStateOnIOThread() const;

  
  
  bool IsDataReductionProxyEnabled() const;

  void set_client_cert_store_factory_for_testing(
    const base::Callback<scoped_ptr<net::ClientCertStore>()>& factory) {
      client_cert_store_factory_ = factory;
  }

 protected:
  
  
  class MediaRequestContext : public net::URLRequestContext {
   public:
    MediaRequestContext();

    void SetHttpTransactionFactory(
        scoped_ptr<net::HttpTransactionFactory> http_factory);

   private:
    virtual ~MediaRequestContext();

    scoped_ptr<net::HttpTransactionFactory> http_factory_;
  };

  
  
  class AppRequestContext : public net::URLRequestContext {
   public:
    AppRequestContext();

    void SetCookieStore(net::CookieStore* cookie_store);
    void SetHttpTransactionFactory(
        scoped_ptr<net::HttpTransactionFactory> http_factory);
    void SetJobFactory(scoped_ptr<net::URLRequestJobFactory> job_factory);

   private:
    virtual ~AppRequestContext();

    scoped_refptr<net::CookieStore> cookie_store_;
    scoped_ptr<net::HttpTransactionFactory> http_factory_;
    scoped_ptr<net::URLRequestJobFactory> job_factory_;
  };

  
  
  struct ProfileParams {
    ProfileParams();
    ~ProfileParams();

    base::FilePath path;
    IOThread* io_thread;
    scoped_refptr<CookieSettings> cookie_settings;
    scoped_refptr<HostContentSettingsMap> host_content_settings_map;
    scoped_refptr<net::SSLConfigService> ssl_config_service;
    scoped_refptr<net::CookieMonster::Delegate> cookie_monster_delegate;
#if defined(ENABLE_EXTENSIONS)
    scoped_refptr<extensions::InfoMap> extension_info_map;
#endif
    scoped_ptr<chrome_browser_net::ResourcePrefetchPredictorObserver>
        resource_prefetch_predictor_observer_;

    
    
    
    
    scoped_ptr<ProtocolHandlerRegistry::JobInterceptorFactory>
        protocol_handler_interceptor;

    
    
    
    scoped_ptr<net::ProxyConfigService> proxy_config_service;

#if defined(ENABLE_MANAGED_USERS)
    scoped_refptr<const SupervisedUserURLFilter> supervised_user_url_filter;
#endif

#if defined(OS_CHROMEOS)
    std::string username_hash;
    bool use_system_key_slot;
#endif

    
    
    
    void* profile;

    prerender::PrerenderTracker* prerender_tracker;
  };

  explicit ProfileIOData(Profile::ProfileType profile_type);

  static std::string GetSSLSessionCacheShard();

  void InitializeOnUIThread(Profile* profile);
  void ApplyProfileParamsToContext(net::URLRequestContext* context) const;

  scoped_ptr<net::URLRequestJobFactory> SetUpJobFactoryDefaults(
      scoped_ptr<net::URLRequestJobFactoryImpl> job_factory,
      content::URLRequestInterceptorScopedVector request_interceptors,
      scoped_ptr<ProtocolHandlerRegistry::JobInterceptorFactory>
          protocol_handler_interceptor,
      net::NetworkDelegate* network_delegate,
      net::FtpTransactionFactory* ftp_transaction_factory) const;

  
  void ShutdownOnUIThread(
      scoped_ptr<ChromeURLRequestContextGetterVector> context_getters);

  
  
  
  
  void set_channel_id_service(
      net::ChannelIDService* channel_id_service) const;

  data_reduction_proxy::DataReductionProxyParams* data_reduction_proxy_params()
      const {
    return data_reduction_proxy_params_.get();
  }

  void set_data_reduction_proxy_params(
      scoped_ptr<data_reduction_proxy::DataReductionProxyParams>
          data_reduction_proxy_params) const {
    data_reduction_proxy_params_ = data_reduction_proxy_params.Pass();
  }

  data_reduction_proxy::DataReductionProxyUsageStats*
      data_reduction_proxy_usage_stats() const {
    return data_reduction_proxy_usage_stats_.get();
  }

  void set_data_reduction_proxy_statistics_prefs(
      scoped_ptr<data_reduction_proxy::DataReductionProxyStatisticsPrefs>
          data_reduction_proxy_statistics_prefs) {
    data_reduction_proxy_statistics_prefs_ =
        data_reduction_proxy_statistics_prefs.Pass();
  }

  data_reduction_proxy::DataReductionProxyStatisticsPrefs*
      data_reduction_proxy_statistics_prefs() const {
    return data_reduction_proxy_statistics_prefs_.get();
  }

  void set_data_reduction_proxy_usage_stats(
      scoped_ptr<data_reduction_proxy::DataReductionProxyUsageStats>
          data_reduction_proxy_usage_stats) const {
     data_reduction_proxy_usage_stats_ =
         data_reduction_proxy_usage_stats.Pass();
  }

  base::Callback<void(bool)> data_reduction_proxy_unavailable_callback() const {
    return data_reduction_proxy_unavailable_callback_;
  }

  void set_data_reduction_proxy_unavailable_callback(
      const base::Callback<void(bool)>& unavailable_callback) const {
    data_reduction_proxy_unavailable_callback_ = unavailable_callback;
  }

  DataReductionProxyChromeConfigurator*
      data_reduction_proxy_chrome_configurator() const {
    return data_reduction_proxy_chrome_configurator_.get();
  }

  void set_data_reduction_proxy_chrome_configurator(
      scoped_ptr<DataReductionProxyChromeConfigurator>
          data_reduction_proxy_chrome_configurator) const {
    data_reduction_proxy_chrome_configurator_ =
        data_reduction_proxy_chrome_configurator.Pass();
  }

  data_reduction_proxy::DataReductionProxyAuthRequestHandler*
      data_reduction_proxy_auth_request_handler() const {
    return data_reduction_proxy_auth_request_handler_.get();
  }

  void set_data_reduction_proxy_auth_request_handler(
      scoped_ptr<data_reduction_proxy::DataReductionProxyAuthRequestHandler>
          data_reduction_proxy_auth_request_handler) const {
    data_reduction_proxy_auth_request_handler_ =
        data_reduction_proxy_auth_request_handler.Pass();
  }

  ChromeNetworkDelegate* network_delegate() const {
    return network_delegate_.get();
  }

  net::FraudulentCertificateReporter* fraudulent_certificate_reporter() const {
    return fraudulent_certificate_reporter_.get();
  }

  net::ProxyService* proxy_service() const {
    return proxy_service_.get();
  }

  base::WeakPtr<net::HttpServerProperties> http_server_properties() const;

  void set_http_server_properties(
      scoped_ptr<net::HttpServerProperties> http_server_properties) const;

  net::URLRequestContext* main_request_context() const {
    return main_request_context_.get();
  }

  bool initialized() const {
    return initialized_;
  }

  
  
  
  void DestroyResourceContext();

  
  scoped_ptr<net::HttpCache> CreateMainHttpFactory(
      const ProfileParams* profile_params,
      net::HttpCache::BackendFactory* main_backend) const;

  
  scoped_ptr<net::HttpCache> CreateHttpFactory(
      net::HttpNetworkSession* shared_session,
      net::HttpCache::BackendFactory* backend) const;

  void SetCookieSettingsForTesting(CookieSettings* cookie_settings);

  void set_signin_names_for_testing(SigninNamesOnIOThread* signin_names);

 private:
  class ResourceContext : public content::ResourceContext {
   public:
    explicit ResourceContext(ProfileIOData* io_data);
    virtual ~ResourceContext();

    
    virtual net::HostResolver* GetHostResolver() OVERRIDE;
    virtual net::URLRequestContext* GetRequestContext() OVERRIDE;
    virtual scoped_ptr<net::ClientCertStore> CreateClientCertStore() OVERRIDE;
    virtual void CreateKeygenHandler(
        uint32 key_size_in_bits,
        const std::string& challenge_string,
        const GURL& url,
        const base::Callback<void(scoped_ptr<net::KeygenHandler>)>& callback)
        OVERRIDE;
    virtual SaltCallback GetMediaDeviceIDSalt() OVERRIDE;

   private:
    friend class ProfileIOData;

    ProfileIOData* const io_data_;

    net::HostResolver* host_resolver_;
    net::URLRequestContext* request_context_;
  };

  typedef std::map<StoragePartitionDescriptor,
                   net::URLRequestContext*,
                   StoragePartitionDescriptorLess>
      URLRequestContextMap;

  
  
  

  
  
  virtual void InitializeInternal(
      ProfileParams* profile_params,
      content::ProtocolHandlerMap* protocol_handlers,
      content::URLRequestInterceptorScopedVector
          request_interceptors) const = 0;

  
  virtual void InitializeExtensionsRequestContext(
      ProfileParams* profile_params) const = 0;
  
  
  virtual net::URLRequestContext* InitializeAppRequestContext(
      net::URLRequestContext* main_context,
      const StoragePartitionDescriptor& details,
      scoped_ptr<ProtocolHandlerRegistry::JobInterceptorFactory>
          protocol_handler_interceptor,
      content::ProtocolHandlerMap* protocol_handlers,
      content::URLRequestInterceptorScopedVector
          request_interceptors) const = 0;

  
  
  virtual net::URLRequestContext* InitializeMediaRequestContext(
      net::URLRequestContext* original_context,
      const StoragePartitionDescriptor& details) const = 0;

  
  
  virtual net::URLRequestContext*
      AcquireMediaRequestContext() const = 0;
  virtual net::URLRequestContext* AcquireIsolatedAppRequestContext(
      net::URLRequestContext* main_context,
      const StoragePartitionDescriptor& partition_descriptor,
      scoped_ptr<ProtocolHandlerRegistry::JobInterceptorFactory>
          protocol_handler_interceptor,
      content::ProtocolHandlerMap* protocol_handlers,
      content::URLRequestInterceptorScopedVector
          request_interceptors) const = 0;
  virtual net::URLRequestContext*
      AcquireIsolatedMediaRequestContext(
          net::URLRequestContext* app_context,
          const StoragePartitionDescriptor& partition_descriptor) const = 0;

  
  
  
  
  
  
  
  
  
  
  
  

  
  mutable bool initialized_;

  
  
  mutable scoped_ptr<ProfileParams> profile_params_;

  
  mutable scoped_ptr<SigninNamesOnIOThread> signin_names_;

  
  mutable base::Callback<scoped_ptr<net::ClientCertStore>()>
      client_cert_store_factory_;

  mutable StringPrefMember google_services_user_account_id_;
  mutable StringPrefMember google_services_username_;
  mutable StringPrefMember google_services_username_pattern_;
  mutable BooleanPrefMember reverse_autologin_enabled_;

  
  
  std::string reverse_autologin_pending_email_;

  mutable StringListPrefMember one_click_signin_rejected_email_list_;

  mutable scoped_refptr<MediaDeviceIDSalt> media_device_id_salt_;

  
  mutable BooleanPrefMember enable_referrers_;
  mutable BooleanPrefMember enable_do_not_track_;
  mutable BooleanPrefMember force_safesearch_;
  mutable BooleanPrefMember safe_browsing_enabled_;
  mutable BooleanPrefMember data_reduction_proxy_enabled_;
  mutable BooleanPrefMember printing_enabled_;
  mutable BooleanPrefMember sync_disabled_;
  mutable BooleanPrefMember signin_allowed_;
  mutable IntegerPrefMember network_prediction_options_;
  
  mutable IntegerPrefMember session_startup_pref_;
  mutable BooleanPrefMember quick_check_enabled_;
  mutable IntegerPrefMember incognito_availibility_pref_;

  
  
  
#if defined(OS_CHROMEOS)
  bool enable_metrics_;
#else
  BooleanPrefMember enable_metrics_;
#endif

#if defined(ENABLE_CONFIGURATION_POLICY)
  
  mutable scoped_ptr<policy::URLBlacklistManager> url_blacklist_manager_;
  mutable scoped_ptr<policy::PolicyHeaderIOHelper> policy_header_helper_;
#endif

  
#if defined(ENABLE_EXTENSIONS)
  mutable scoped_refptr<extensions::InfoMap> extension_info_map_;
#endif
  mutable scoped_ptr<net::ChannelIDService> channel_id_service_;

  
  
  
  
  mutable scoped_ptr<data_reduction_proxy::DataReductionProxyParams>
      data_reduction_proxy_params_;
  mutable scoped_ptr<data_reduction_proxy::DataReductionProxyUsageStats>
      data_reduction_proxy_usage_stats_;
  mutable scoped_ptr<data_reduction_proxy::DataReductionProxyStatisticsPrefs>
            data_reduction_proxy_statistics_prefs_;
  mutable base::Callback<void(bool)> data_reduction_proxy_unavailable_callback_;
  mutable scoped_ptr<DataReductionProxyChromeConfigurator>
      data_reduction_proxy_chrome_configurator_;
  mutable scoped_ptr<data_reduction_proxy::DataReductionProxyAuthRequestHandler>
      data_reduction_proxy_auth_request_handler_;

  mutable scoped_ptr<ChromeNetworkDelegate> network_delegate_;
  mutable scoped_ptr<net::FraudulentCertificateReporter>
      fraudulent_certificate_reporter_;
  mutable scoped_ptr<net::ProxyService> proxy_service_;
  mutable scoped_ptr<net::TransportSecurityState> transport_security_state_;
  mutable scoped_ptr<net::HttpServerProperties>
      http_server_properties_;
#if defined(OS_CHROMEOS)
  
  
  mutable policy::PolicyCertVerifier* policy_cert_verifier_;
  mutable scoped_ptr<net::CertVerifier> cert_verifier_;
  mutable std::string username_hash_;
  mutable bool use_system_key_slot_;
#endif

  mutable scoped_ptr<net::TransportSecurityPersister>
      transport_security_persister_;

  
  
  mutable scoped_ptr<net::URLRequestContext> main_request_context_;
  mutable scoped_ptr<net::URLRequestContext> extensions_request_context_;
  
  mutable URLRequestContextMap app_request_context_map_;
  mutable URLRequestContextMap isolated_media_request_context_map_;

  mutable scoped_ptr<ResourceContext> resource_context_;

  mutable scoped_refptr<CookieSettings> cookie_settings_;

  mutable scoped_refptr<HostContentSettingsMap> host_content_settings_map_;

  mutable scoped_ptr<chrome_browser_net::ResourcePrefetchPredictorObserver>
      resource_prefetch_predictor_observer_;

  mutable scoped_ptr<ChromeHttpUserAgentSettings>
      chrome_http_user_agent_settings_;

#if defined(ENABLE_MANAGED_USERS)
  mutable scoped_refptr<const SupervisedUserURLFilter>
      supervised_user_url_filter_;
#endif

  mutable scoped_ptr<DevToolsNetworkController> network_controller_;

  
  bool initialized_on_UI_thread_;

  const Profile::ProfileType profile_type_;

  DISALLOW_COPY_AND_ASSIGN(ProfileIOData);
};

#endif  