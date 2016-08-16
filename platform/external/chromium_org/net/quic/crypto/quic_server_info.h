// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_CRYPTO_QUIC_SERVER_INFO_H_
#define NET_QUIC_CRYPTO_QUIC_SERVER_INFO_H_

#include <string>
#include <vector>

#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "base/time/time.h"
#include "net/base/completion_callback.h"
#include "net/base/net_export.h"
#include "net/quic/quic_server_id.h"

namespace net {

class X509Certificate;

class NET_EXPORT_PRIVATE QuicServerInfo {
 public:
  QuicServerInfo(const QuicServerId& server_id);
  virtual ~QuicServerInfo();

  
  
  
  virtual void Start() = 0;

  
  
  
  
  
  
  
  
  
  
  virtual int WaitForDataReady(const CompletionCallback& callback) = 0;

  
  
  virtual bool IsDataReady() = 0;

  
  
  virtual bool IsReadyToPersist() = 0;

  
  
  
  
  
  virtual void Persist() = 0;

  struct State {
    State();
    ~State();

    void Clear();

    
    std::string server_config;         
    std::string source_address_token;  
    std::vector<std::string> certs;    
                                       
    std::string server_config_sig;     

   private:
    DISALLOW_COPY_AND_ASSIGN(State);
  };

  
  
  const State& state() const;
  State* mutable_state();

 protected:
  
  
  
  bool Parse(const std::string& data);
  std::string Serialize();
  State state_;

 private:
  
  bool ParseInner(const std::string& data);

  
  std::string SerializeInner() const;

  
  
  const QuicServerId server_id_;

  DISALLOW_COPY_AND_ASSIGN(QuicServerInfo);
};

class QuicServerInfoFactory {
 public:
  virtual ~QuicServerInfoFactory();

  
  
  virtual QuicServerInfo* GetForServer(const QuicServerId& server_id) = 0;
};

}  

#endif  
