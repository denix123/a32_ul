// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_HTTP_HTTP_TRANSACTION_FACTORY_H_
#define NET_HTTP_HTTP_TRANSACTION_FACTORY_H_

#include "base/memory/scoped_ptr.h"
#include "net/base/net_export.h"
#include "net/base/request_priority.h"

namespace net {

class HttpCache;
class HttpNetworkSession;
class HttpTransaction;

class NET_EXPORT HttpTransactionFactory {
 public:
  virtual ~HttpTransactionFactory() {}

  
  
  virtual int CreateTransaction(RequestPriority priority,
                                scoped_ptr<HttpTransaction>* trans) = 0;

  
  virtual HttpCache* GetCache() = 0;

  
  virtual HttpNetworkSession* GetSession() = 0;
};

}  

#endif  
