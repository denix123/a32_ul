// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_HOST_SIGNALING_CONNECTOR_H_
#define REMOTING_HOST_SIGNALING_CONNECTOR_H_

#include "base/basictypes.h"
#include "base/memory/weak_ptr.h"
#include "base/threading/non_thread_safe.h"
#include "base/timer/timer.h"
#include "net/base/network_change_notifier.h"
#include "remoting/host/oauth_token_getter.h"
#include "remoting/signaling/xmpp_signal_strategy.h"

namespace remoting {

class DnsBlackholeChecker;

class SignalingConnector
    : public base::SupportsWeakPtr<SignalingConnector>,
      public base::NonThreadSafe,
      public SignalStrategy::Listener,
      public net::NetworkChangeNotifier::ConnectionTypeObserver,
      public net::NetworkChangeNotifier::IPAddressObserver {
 public:
  
  SignalingConnector(
      XmppSignalStrategy* signal_strategy,
      scoped_ptr<DnsBlackholeChecker> dns_blackhole_checker,
      const base::Closure& auth_failed_callback);
  virtual ~SignalingConnector();

  
  
  
  void EnableOAuth(OAuthTokenGetter* oauth_token_getter);

  
  void OnAccessToken(OAuthTokenGetter::Status status,
                     const std::string& user_email,
                     const std::string& access_token);

  
  virtual void OnSignalStrategyStateChange(
      SignalStrategy::State state) OVERRIDE;
  virtual bool OnSignalStrategyIncomingStanza(
      const buzz::XmlElement* stanza) OVERRIDE;

  
  virtual void OnConnectionTypeChanged(
      net::NetworkChangeNotifier::ConnectionType type) OVERRIDE;

  
  virtual void OnIPAddressChanged() OVERRIDE;

 private:
  void OnNetworkError();
  void ScheduleTryReconnect();
  void ResetAndTryReconnect();
  void TryReconnect();
  void OnDnsBlackholeCheckerDone(bool allow);

  XmppSignalStrategy* signal_strategy_;
  base::Closure auth_failed_callback_;
  scoped_ptr<DnsBlackholeChecker> dns_blackhole_checker_;

  OAuthTokenGetter* oauth_token_getter_;

  
  int reconnect_attempts_;

  base::OneShotTimer<SignalingConnector> timer_;

  DISALLOW_COPY_AND_ASSIGN(SignalingConnector);
};

}  

#endif  
