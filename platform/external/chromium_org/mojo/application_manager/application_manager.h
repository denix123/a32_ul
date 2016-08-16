// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_APPLICATION_MANAGER_APPLICATION_MANAGER_H_
#define MOJO_APPLICATION_MANAGER_APPLICATION_MANAGER_H_

#include <map>

#include "base/basictypes.h"
#include "base/gtest_prod_util.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "mojo/application_manager/application_loader.h"
#include "mojo/application_manager/application_manager_export.h"
#include "mojo/public/interfaces/application/service_provider.mojom.h"
#include "url/gurl.h"

namespace mojo {

class MOJO_APPLICATION_MANAGER_EXPORT ApplicationManager {
 public:
  class MOJO_APPLICATION_MANAGER_EXPORT Delegate {
   public:
    virtual ~Delegate();
    
    
    virtual void OnApplicationError(const GURL& url) = 0;
  };

  
  class MOJO_APPLICATION_MANAGER_EXPORT TestAPI {
   public:
    explicit TestAPI(ApplicationManager* manager);
    ~TestAPI();

    
    static bool HasCreatedInstance();
    
    bool HasFactoryForURL(const GURL& url) const;

   private:
    ApplicationManager* manager_;

    DISALLOW_COPY_AND_ASSIGN(TestAPI);
  };

  
  class Interceptor {
   public:
    virtual ~Interceptor() {}
    
    virtual ServiceProviderPtr OnConnectToClient(
        const GURL& url,
        ServiceProviderPtr service_provider) = 0;
  };

  ApplicationManager();
  ~ApplicationManager();

  
  static ApplicationManager* GetInstance();

  void SetDelegate(Delegate* delegate) { delegate_ = delegate; }

  
  void ConnectToApplication(const GURL& application_url,
                            const GURL& requestor_url,
                            ServiceProviderPtr service_provider);

  template <typename Interface>
  inline void ConnectToService(const GURL& application_url,
                               InterfacePtr<Interface>* ptr) {
    ScopedMessagePipeHandle service_handle =
        ConnectToServiceByName(application_url, Interface::Name_);
    ptr->Bind(service_handle.Pass());
  }

  ScopedMessagePipeHandle ConnectToServiceByName(
      const GURL& application_url,
      const std::string& interface_name);

  void set_delegate(Delegate* delegate) { delegate_ = delegate; }

  
  
  void set_default_loader(scoped_ptr<ApplicationLoader> loader) {
    default_loader_ = loader.Pass();
  }
  
  void SetLoaderForURL(scoped_ptr<ApplicationLoader> loader, const GURL& url);
  
  void SetLoaderForScheme(scoped_ptr<ApplicationLoader> loader,
                          const std::string& scheme);
  
  
  void SetArgsForURL(const std::vector<std::string>& args, const GURL& url);

  
  void SetInterceptor(Interceptor* interceptor);

  
  
  
  void TerminateShellConnections();

 private:
  struct ContentHandlerConnection;
  class LoadCallbacksImpl;
  class ShellImpl;

  typedef std::map<std::string, ApplicationLoader*> SchemeToLoaderMap;
  typedef std::map<GURL, ApplicationLoader*> URLToLoaderMap;
  typedef std::map<GURL, ShellImpl*> URLToShellImplMap;
  typedef std::map<GURL, ContentHandlerConnection*> URLToContentHandlerMap;
  typedef std::map<GURL, std::vector<std::string> > URLToArgsMap;

  void ConnectToClient(ShellImpl* shell_impl,
                       const GURL& url,
                       const GURL& requestor_url,
                       ServiceProviderPtr service_provider);

  void RegisterLoadedApplication(const GURL& service_url,
                                 const GURL& requestor_url,
                                 ServiceProviderPtr service_provider,
                                 ScopedMessagePipeHandle* shell_handle);

  void LoadWithContentHandler(const GURL& content_url,
                              const GURL& requestor_url,
                              const GURL& content_handler_url,
                              URLResponsePtr url_response,
                              ServiceProviderPtr service_provider);

  
  
  
  ApplicationLoader* GetLoaderForURL(const GURL& url);

  
  void OnShellImplError(ShellImpl* shell_impl);

  Delegate* delegate_;
  
  URLToLoaderMap url_to_loader_;
  SchemeToLoaderMap scheme_to_loader_;
  scoped_ptr<ApplicationLoader> default_loader_;
  Interceptor* interceptor_;

  URLToShellImplMap url_to_shell_impl_;
  URLToContentHandlerMap url_to_content_handler_;
  URLToArgsMap url_to_args_;

  base::WeakPtrFactory<ApplicationManager> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(ApplicationManager);
};

}  

#endif  
