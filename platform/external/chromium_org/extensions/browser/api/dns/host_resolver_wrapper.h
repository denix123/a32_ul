// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_API_DNS_HOST_RESOLVER_WRAPPER_H_
#define EXTENSIONS_BROWSER_API_DNS_HOST_RESOLVER_WRAPPER_H_

#include "base/memory/singleton.h"

namespace content {
class ResourceContext;
}

namespace net {
class HostResolver;
}

namespace extensions {

class HostResolverWrapper {
 public:
  static HostResolverWrapper* GetInstance();

  
  
  
  net::HostResolver* GetHostResolver(content::ResourceContext* context);

  
  void SetHostResolverForTesting(net::HostResolver* mock_resolver);

 private:
  HostResolverWrapper();
  friend struct DefaultSingletonTraits<HostResolverWrapper>;

  net::HostResolver* resolver_;

  DISALLOW_COPY_AND_ASSIGN(HostResolverWrapper);
};

}  

#endif  
