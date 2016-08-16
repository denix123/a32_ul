// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_SSL_SSL_CONFIG_SERVICE_H_
#define NET_SSL_SSL_CONFIG_SERVICE_H_

#include <vector>

#include "base/memory/ref_counted.h"
#include "base/observer_list.h"
#include "net/base/net_export.h"
#include "net/cert/crl_set.h"
#include "net/ssl/ssl_config.h"

namespace net {

class NET_EXPORT SSLConfigService
    : public base::RefCountedThreadSafe<SSLConfigService> {
 public:
  
  class NET_EXPORT Observer {
   public:
    
    
    
    
    
    
    
    
    
    
    virtual void OnSSLConfigChanged() = 0;

   protected:
    virtual ~Observer() {}
  };

  SSLConfigService();

  
  virtual void GetSSLConfig(SSLConfig* config) = 0;

  
  static void SetCRLSet(scoped_refptr<CRLSet> crl_set);
  static scoped_refptr<CRLSet> GetCRLSet();

  
  void AddObserver(Observer* observer);

  
  void RemoveObserver(Observer* observer);

  
  
  void NotifySSLConfigChange();

 protected:
  friend class base::RefCountedThreadSafe<SSLConfigService>;

  virtual ~SSLConfigService();

  
  void ProcessConfigUpdate(const SSLConfig& orig_config,
                           const SSLConfig& new_config);

 private:
  ObserverList<Observer> observer_list_;
};

}  

#endif  
