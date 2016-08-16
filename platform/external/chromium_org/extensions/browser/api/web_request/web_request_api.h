// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_API_WEB_REQUEST_WEB_REQUEST_API_H_
#define EXTENSIONS_BROWSER_API_WEB_REQUEST_WEB_REQUEST_API_H_

#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "base/memory/singleton.h"
#include "base/memory/weak_ptr.h"
#include "base/time/time.h"
#include "content/public/common/resource_type.h"
#include "extensions/browser/api/declarative/rules_registry.h"
#include "extensions/browser/api/declarative_webrequest/request_stage.h"
#include "extensions/browser/api/web_request/web_request_api_helpers.h"
#include "extensions/browser/api/web_request/web_request_permissions.h"
#include "extensions/browser/browser_context_keyed_api_factory.h"
#include "extensions/browser/event_router.h"
#include "extensions/browser/extension_function.h"
#include "extensions/common/url_pattern_set.h"
#include "ipc/ipc_sender.h"
#include "net/base/completion_callback.h"
#include "net/base/network_delegate.h"
#include "net/http/http_request_headers.h"

class ExtensionWebRequestTimeTracker;
class GURL;

namespace base {
class DictionaryValue;
class ListValue;
class StringValue;
}

namespace content {
class BrowserContext;
}

namespace net {
class AuthCredentials;
class AuthChallengeInfo;
class HttpRequestHeaders;
class HttpResponseHeaders;
class URLRequest;
}

namespace extensions {

class InfoMap;
class WebRequestRulesRegistry;
class WebRequestEventRouterDelegate;

class WebRequestAPI : public BrowserContextKeyedAPI,
                      public EventRouter::Observer {
 public:
  explicit WebRequestAPI(content::BrowserContext* context);
  virtual ~WebRequestAPI();

  
  static BrowserContextKeyedAPIFactory<WebRequestAPI>* GetFactoryInstance();

  
  virtual void OnListenerRemoved(const EventListenerInfo& details) OVERRIDE;

 private:
  friend class BrowserContextKeyedAPIFactory<WebRequestAPI>;

  
  static const char* service_name() { return "WebRequestAPI"; }
  static const bool kServiceRedirectedInIncognito = true;
  static const bool kServiceIsNULLWhileTesting = true;

  content::BrowserContext* browser_context_;

  DISALLOW_COPY_AND_ASSIGN(WebRequestAPI);
};

}  

class ExtensionWebRequestEventRouter
    : public base::SupportsWeakPtr<ExtensionWebRequestEventRouter> {
 public:
  struct BlockedRequest;

  enum EventTypes {
    kInvalidEvent = 0,
    kOnBeforeRequest = 1 << 0,
    kOnBeforeSendHeaders = 1 << 1,
    kOnSendHeaders = 1 << 2,
    kOnHeadersReceived = 1 << 3,
    kOnBeforeRedirect = 1 << 4,
    kOnAuthRequired = 1 << 5,
    kOnResponseStarted = 1 << 6,
    kOnErrorOccurred = 1 << 7,
    kOnCompleted = 1 << 8,
  };

  
  
  struct RequestFilter {
    RequestFilter();
    ~RequestFilter();

    
    
    
    bool InitFromValue(const base::DictionaryValue& value, std::string* error);

    extensions::URLPatternSet urls;
    std::vector<content::ResourceType> types;
    int tab_id;
    int window_id;
  };

  
  
  
  struct ExtraInfoSpec {
    enum Flags {
      REQUEST_HEADERS = 1<<0,
      RESPONSE_HEADERS = 1<<1,
      BLOCKING = 1<<2,
      ASYNC_BLOCKING = 1<<3,
      REQUEST_BODY = 1<<4,
    };

    static bool InitFromValue(const base::ListValue& value,
                              int* extra_info_spec);
  };

  
  struct EventResponse {
    EventResponse(const std::string& extension_id,
                  const base::Time& extension_install_time);
    ~EventResponse();

    
    std::string extension_id;

    
    
    
    base::Time extension_install_time;

    
    bool cancel;
    GURL new_url;
    scoped_ptr<net::HttpRequestHeaders> request_headers;
    scoped_ptr<extension_web_request_api_helpers::ResponseHeaders>
        response_headers;

    scoped_ptr<net::AuthCredentials> auth_credentials;

    DISALLOW_COPY_AND_ASSIGN(EventResponse);
  };

  static ExtensionWebRequestEventRouter* GetInstance();

  
  
  void RegisterRulesRegistry(
      void* browser_context,
      const extensions::RulesRegistry::WebViewKey& webview_key,
      scoped_refptr<extensions::WebRequestRulesRegistry> rules_registry);

  
  
  
  int OnBeforeRequest(void* browser_context,
                      extensions::InfoMap* extension_info_map,
                      net::URLRequest* request,
                      const net::CompletionCallback& callback,
                      GURL* new_url);

  
  
  
  
  int OnBeforeSendHeaders(void* browser_context,
                          extensions::InfoMap* extension_info_map,
                          net::URLRequest* request,
                          const net::CompletionCallback& callback,
                          net::HttpRequestHeaders* headers);

  
  
  void OnSendHeaders(void* browser_context,
                     extensions::InfoMap* extension_info_map,
                     net::URLRequest* request,
                     const net::HttpRequestHeaders& headers);

  
  
  
  
  
  
  
  
  
  int OnHeadersReceived(
      void* browser_context,
      extensions::InfoMap* extension_info_map,
      net::URLRequest* request,
      const net::CompletionCallback& callback,
      const net::HttpResponseHeaders* original_response_headers,
      scoped_refptr<net::HttpResponseHeaders>* override_response_headers,
      GURL* allowed_unsafe_redirect_url);

  
  
  
  
  
  net::NetworkDelegate::AuthRequiredResponse OnAuthRequired(
      void* browser_context,
      extensions::InfoMap* extension_info_map,
      net::URLRequest* request,
      const net::AuthChallengeInfo& auth_info,
      const net::NetworkDelegate::AuthCallback& callback,
      net::AuthCredentials* credentials);

  
  
  void OnBeforeRedirect(void* browser_context,
                        extensions::InfoMap* extension_info_map,
                        net::URLRequest* request,
                        const GURL& new_location);

  
  
  void OnResponseStarted(void* browser_context,
                         extensions::InfoMap* extension_info_map,
                         net::URLRequest* request);

  
  void OnCompleted(void* browser_context,
                   extensions::InfoMap* extension_info_map,
                   net::URLRequest* request);

  
  void OnErrorOccurred(void* browser_context,
                       extensions::InfoMap* extension_info_map,
                       net::URLRequest* request,
                       bool started);

  
  void OnURLRequestDestroyed(void* browser_context, net::URLRequest* request);

  
  void OnEventHandled(
      void* browser_context,
      const std::string& extension_id,
      const std::string& event_name,
      const std::string& sub_event_name,
      uint64 request_id,
      EventResponse* response);

  
  
  
  
  bool AddEventListener(
      void* browser_context,
      const std::string& extension_id,
      const std::string& extension_name,
      const std::string& event_name,
      const std::string& sub_event_name,
      const RequestFilter& filter,
      int extra_info_spec,
      int embedder_process_id,
      int web_view_instance_id,
      base::WeakPtr<IPC::Sender> ipc_sender);

  
  void RemoveEventListener(
      void* browser_context,
      const std::string& extension_id,
      const std::string& sub_event_name);

  
  void RemoveWebViewEventListeners(
      void* browser_context,
      const std::string& extension_id,
      int embedder_process_id,
      int web_view_instance_id);

  
  void OnOTRBrowserContextCreated(void* original_browser_context,
                                  void* otr_browser_context);
  void OnOTRBrowserContextDestroyed(void* original_browser_context,
                                    void* otr_browser_context);

  
  
  void AddCallbackForPageLoad(const base::Closure& callback);

 private:
  friend struct DefaultSingletonTraits<ExtensionWebRequestEventRouter>;

  struct EventListener;
  typedef std::map<std::string, std::set<EventListener> >
      ListenerMapForBrowserContext;
  typedef std::map<void*, ListenerMapForBrowserContext> ListenerMap;
  typedef std::map<uint64, BlockedRequest> BlockedRequestMap;
  
  typedef std::map<uint64, int> SignaledRequestMap;
  
  
  
  typedef std::map<void*, std::pair<bool, void*> > CrossBrowserContextMap;
  typedef std::list<base::Closure> CallbacksForPageLoad;

  ExtensionWebRequestEventRouter();
  ~ExtensionWebRequestEventRouter();

  
  
  void ClearPendingCallbacks(net::URLRequest* request);

  bool DispatchEvent(
      void* browser_context,
      net::URLRequest* request,
      const std::vector<const EventListener*>& listeners,
      const base::ListValue& args);

  
  
  
  std::vector<const EventListener*> GetMatchingListeners(
      void* browser_context,
      extensions::InfoMap* extension_info_map,
      const std::string& event_name,
      net::URLRequest* request,
      int* extra_info_spec);

  
  
  
  
  void GetMatchingListenersImpl(
      void* browser_context,
      net::URLRequest* request,
      extensions::InfoMap* extension_info_map,
      bool crosses_incognito,
      const std::string& event_name,
      const GURL& url,
      int render_process_host_id,
      int routing_id,
      content::ResourceType resource_type,
      bool is_async_request,
      bool is_request_from_extension,
      int* extra_info_spec,
      std::vector<const ExtensionWebRequestEventRouter::EventListener*>*
          matching_listeners);

  
  
  
  
  
  void DecrementBlockCount(
      void* browser_context,
      const std::string& extension_id,
      const std::string& event_name,
      uint64 request_id,
      EventResponse* response);

  
  void LogExtensionActivity(
      void* browser_context_id,
      bool is_incognito,
      const std::string& extension_id,
      const GURL& url,
      const std::string& api_call,
      scoped_ptr<base::DictionaryValue> details);

  
  
  
  
  
  
  int ExecuteDeltas(
      void* browser_context, uint64 request_id, bool call_callback);

  
  
  
  
  
  bool ProcessDeclarativeRules(
      void* browser_context,
      extensions::InfoMap* extension_info_map,
      const std::string& event_name,
      net::URLRequest* request,
      extensions::RequestStage request_stage,
      const net::HttpResponseHeaders* original_response_headers);

  
  
  
  void SendMessages(
      void* browser_context, const BlockedRequest& blocked_request);

  
  
  void OnRulesRegistryReady(
      void* browser_context,
      const std::string& event_name,
      uint64 request_id,
      extensions::RequestStage request_stage);

  
  
  
  void ExtractRequestInfo(net::URLRequest* request, base::DictionaryValue* out);

  
  
  bool GetAndSetSignaled(uint64 request_id, EventTypes event_type);

  
  void ClearSignaled(uint64 request_id, EventTypes event_type);

  
  bool IsPageLoad(net::URLRequest* request) const;

  
  void NotifyPageLoad();

  
  
  void* GetCrossBrowserContext(void* browser_context) const;

  
  
  
  bool IsIncognitoBrowserContext(void* browser_context) const;

  
  bool WasSignaled(const net::URLRequest& request) const;

  
  
  ListenerMap listeners_;

  
  
  BlockedRequestMap blocked_requests_;

  
  
  SignaledRequestMap signaled_requests_;

  
  
  CrossBrowserContextMap cross_browser_context_map_;

  
  
  scoped_ptr<ExtensionWebRequestTimeTracker> request_time_tracker_;

  CallbacksForPageLoad callbacks_for_page_load_;

  typedef std::pair<void*, extensions::RulesRegistry::WebViewKey>
      RulesRegistryKey;
  
  
  std::map<RulesRegistryKey,
      scoped_refptr<extensions::WebRequestRulesRegistry> > rules_registries_;

  scoped_ptr<extensions::WebRequestEventRouterDelegate>
      web_request_event_router_delegate_;

  DISALLOW_COPY_AND_ASSIGN(ExtensionWebRequestEventRouter);
};

class WebRequestInternalAddEventListenerFunction
    : public SyncIOThreadExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("webRequestInternal.addEventListener",
                             WEBREQUESTINTERNAL_ADDEVENTLISTENER)

 protected:
  virtual ~WebRequestInternalAddEventListenerFunction() {}

  
  virtual bool RunSync() OVERRIDE;
};

class WebRequestInternalEventHandledFunction
    : public SyncIOThreadExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("webRequestInternal.eventHandled",
                             WEBREQUESTINTERNAL_EVENTHANDLED)

 protected:
  virtual ~WebRequestInternalEventHandledFunction() {}

  
  
  
  
  void RespondWithError(
      const std::string& event_name,
      const std::string& sub_event_name,
      uint64 request_id,
      scoped_ptr<ExtensionWebRequestEventRouter::EventResponse> response,
      const std::string& error);

  
  virtual bool RunSync() OVERRIDE;
};

class WebRequestHandlerBehaviorChangedFunction
    : public SyncIOThreadExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("webRequest.handlerBehaviorChanged",
                             WEBREQUEST_HANDLERBEHAVIORCHANGED)

 protected:
  virtual ~WebRequestHandlerBehaviorChangedFunction() {}

  
  virtual void GetQuotaLimitHeuristics(
      extensions::QuotaLimitHeuristics* heuristics) const OVERRIDE;
  
  
  virtual void OnQuotaExceeded(const std::string& error) OVERRIDE;
  virtual bool RunSync() OVERRIDE;
};

#endif  
