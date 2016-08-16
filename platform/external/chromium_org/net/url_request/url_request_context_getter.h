// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_URL_REQUEST_URL_REQUEST_CONTEXT_GETTER_H_
#define NET_URL_REQUEST_URL_REQUEST_CONTEXT_GETTER_H_

#include "base/memory/ref_counted.h"
#include "base/sequenced_task_runner_helpers.h"
#include "net/base/net_export.h"

namespace base {
class SingleThreadTaskRunner;
}  

namespace net {
class CookieStore;
class URLRequestContext;

struct URLRequestContextGetterTraits;

class NET_EXPORT URLRequestContextGetter
    : public base::RefCountedThreadSafe<URLRequestContextGetter,
                                        URLRequestContextGetterTraits> {
 public:
  virtual URLRequestContext* GetURLRequestContext() = 0;

  
  
  
  virtual scoped_refptr<base::SingleThreadTaskRunner>
      GetNetworkTaskRunner() const = 0;

 protected:
  friend class base::RefCountedThreadSafe<URLRequestContextGetter,
                                          URLRequestContextGetterTraits>;
  friend class base::DeleteHelper<URLRequestContextGetter>;
  friend struct URLRequestContextGetterTraits;

  URLRequestContextGetter();
  virtual ~URLRequestContextGetter();

 private:
  
  
  void OnDestruct() const;
};

struct URLRequestContextGetterTraits {
  static void Destruct(const URLRequestContextGetter* context_getter) {
    context_getter->OnDestruct();
  }
};

class NET_EXPORT TrivialURLRequestContextGetter
    : public URLRequestContextGetter {
public:
  TrivialURLRequestContextGetter(
      net::URLRequestContext* context,
      const scoped_refptr<base::SingleThreadTaskRunner>& main_task_runner);

  
  virtual net::URLRequestContext* GetURLRequestContext() OVERRIDE;

  virtual scoped_refptr<base::SingleThreadTaskRunner>
      GetNetworkTaskRunner() const OVERRIDE;

private:
  virtual ~TrivialURLRequestContextGetter();

  net::URLRequestContext* context_;
  const scoped_refptr<base::SingleThreadTaskRunner> main_task_runner_;

  DISALLOW_COPY_AND_ASSIGN(TrivialURLRequestContextGetter);
};

}  

#endif  
