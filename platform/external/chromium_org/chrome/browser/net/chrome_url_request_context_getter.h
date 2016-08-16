// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_NET_CHROME_URL_REQUEST_CONTEXT_GETTER_H_
#define CHROME_BROWSER_NET_CHROME_URL_REQUEST_CONTEXT_GETTER_H_

#include <string>

#include "base/memory/scoped_ptr.h"
#include "chrome/browser/custom_handlers/protocol_handler_registry.h"
#include "net/url_request/url_request_context.h"
#include "net/url_request/url_request_context_getter.h"
#include "net/url_request/url_request_job_factory.h"

class ChromeURLRequestContextFactory;
class IOThread;
class Profile;
class ProfileIOData;
struct StoragePartitionDescriptor;

class ChromeURLRequestContextGetter : public net::URLRequestContextGetter {
 public:
  
  
  explicit ChromeURLRequestContextGetter(
      ChromeURLRequestContextFactory* factory);

  
  
  
  
  
  virtual net::URLRequestContext* GetURLRequestContext() OVERRIDE;
  virtual scoped_refptr<base::SingleThreadTaskRunner>
      GetNetworkTaskRunner() const OVERRIDE;

  
  
  static ChromeURLRequestContextGetter* Create(
      Profile* profile,
      const ProfileIOData* profile_io_data,
      content::ProtocolHandlerMap* protocol_handlers,
      content::URLRequestInterceptorScopedVector request_interceptors);

  
  
  
  static ChromeURLRequestContextGetter* CreateForMedia(
      Profile* profile, const ProfileIOData* profile_io_data);

  
  
  static ChromeURLRequestContextGetter* CreateForExtensions(
      Profile* profile, const ProfileIOData* profile_io_data);

  
  
  static ChromeURLRequestContextGetter* CreateForIsolatedApp(
      Profile* profile,
      const ProfileIOData* profile_io_data,
      const StoragePartitionDescriptor& partition_descriptor,
      scoped_ptr<ProtocolHandlerRegistry::JobInterceptorFactory>
          protocol_handler_interceptor,
      content::ProtocolHandlerMap* protocol_handlers,
      content::URLRequestInterceptorScopedVector request_interceptors);

  
  
  static ChromeURLRequestContextGetter* CreateForIsolatedMedia(
      Profile* profile,
      ChromeURLRequestContextGetter* app_context,
      const ProfileIOData* profile_io_data,
      const StoragePartitionDescriptor& partition_descriptor);

  
  
  void Invalidate();

 private:
  virtual ~ChromeURLRequestContextGetter();

  
  
  scoped_ptr<ChromeURLRequestContextFactory> factory_;

  
  
  
  
  net::URLRequestContext* url_request_context_;

  DISALLOW_COPY_AND_ASSIGN(ChromeURLRequestContextGetter);
};

#endif  
