// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_HOST_SETUP_ME2ME_NATIVE_MESSAGING_HOST_H_
#define REMOTING_HOST_SETUP_ME2ME_NATIVE_MESSAGING_HOST_H_

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/threading/thread_checker.h"
#include "base/timer/timer.h"
#include "extensions/browser/api/messaging/native_messaging_channel.h"
#include "remoting/host/setup/daemon_controller.h"
#include "remoting/host/setup/oauth_client.h"

namespace base {
class DictionaryValue;
class ListValue;
}  

namespace gaia {
class GaiaOAuthClient;
}  

namespace remoting {

const char kElevatingSwitchName[] = "elevate";
const char kInputSwitchName[] = "input";
const char kOutputSwitchName[] = "output";

namespace protocol {
class PairingRegistry;
}  

class Me2MeNativeMessagingHost
    : public extensions::NativeMessagingChannel::EventHandler {
 public:
  Me2MeNativeMessagingHost(
      bool needs_elevation,
      intptr_t parent_window_handle,
      scoped_ptr<extensions::NativeMessagingChannel> channel,
      scoped_refptr<DaemonController> daemon_controller,
      scoped_refptr<protocol::PairingRegistry> pairing_registry,
      scoped_ptr<OAuthClient> oauth_client);
  virtual ~Me2MeNativeMessagingHost();

  void Start(const base::Closure& quit_closure);

  
  virtual void OnMessage(scoped_ptr<base::Value> message) OVERRIDE;
  virtual void OnDisconnect() OVERRIDE;

 private:
  
  
  
  void ProcessHello(
      scoped_ptr<base::DictionaryValue> message,
      scoped_ptr<base::DictionaryValue> response);
  void ProcessClearPairedClients(
      scoped_ptr<base::DictionaryValue> message,
      scoped_ptr<base::DictionaryValue> response);
  void ProcessDeletePairedClient(
      scoped_ptr<base::DictionaryValue> message,
      scoped_ptr<base::DictionaryValue> response);
  void ProcessGetHostName(
      scoped_ptr<base::DictionaryValue> message,
      scoped_ptr<base::DictionaryValue> response);
  void ProcessGetPinHash(
      scoped_ptr<base::DictionaryValue> message,
      scoped_ptr<base::DictionaryValue> response);
  void ProcessGenerateKeyPair(
      scoped_ptr<base::DictionaryValue> message,
      scoped_ptr<base::DictionaryValue> response);
  void ProcessUpdateDaemonConfig(
      scoped_ptr<base::DictionaryValue> message,
      scoped_ptr<base::DictionaryValue> response);
  void ProcessGetDaemonConfig(
      scoped_ptr<base::DictionaryValue> message,
      scoped_ptr<base::DictionaryValue> response);
  void ProcessGetPairedClients(
      scoped_ptr<base::DictionaryValue> message,
      scoped_ptr<base::DictionaryValue> response);
  void ProcessGetUsageStatsConsent(
      scoped_ptr<base::DictionaryValue> message,
      scoped_ptr<base::DictionaryValue> response);
  void ProcessStartDaemon(
      scoped_ptr<base::DictionaryValue> message,
      scoped_ptr<base::DictionaryValue> response);
  void ProcessStopDaemon(
      scoped_ptr<base::DictionaryValue> message,
      scoped_ptr<base::DictionaryValue> response);
  void ProcessGetDaemonState(
      scoped_ptr<base::DictionaryValue> message,
      scoped_ptr<base::DictionaryValue> response);
  void ProcessGetHostClientId(
      scoped_ptr<base::DictionaryValue> message,
      scoped_ptr<base::DictionaryValue> response);
  void ProcessGetCredentialsFromAuthCode(
      scoped_ptr<base::DictionaryValue> message,
      scoped_ptr<base::DictionaryValue> response);

  
  
  
  
  void SendConfigResponse(scoped_ptr<base::DictionaryValue> response,
                          scoped_ptr<base::DictionaryValue> config);
  void SendPairedClientsResponse(scoped_ptr<base::DictionaryValue> response,
                                 scoped_ptr<base::ListValue> pairings);
  void SendUsageStatsConsentResponse(
      scoped_ptr<base::DictionaryValue> response,
      const DaemonController::UsageStatsConsent& consent);
  void SendAsyncResult(scoped_ptr<base::DictionaryValue> response,
                       DaemonController::AsyncResult result);
  void SendBooleanResult(scoped_ptr<base::DictionaryValue> response,
                         bool result);
  void SendCredentialsResponse(scoped_ptr<base::DictionaryValue> response,
                               const std::string& user_email,
                               const std::string& refresh_token);

  void OnError();

  void Stop();

  
  
  bool DelegateToElevatedHost(scoped_ptr<base::DictionaryValue> message);

#if defined(OS_WIN)
  class ElevatedChannelEventHandler
      : public extensions::NativeMessagingChannel::EventHandler {
   public:
    ElevatedChannelEventHandler(Me2MeNativeMessagingHost* host);

    virtual void OnMessage(scoped_ptr<base::Value> message) OVERRIDE;
    virtual void OnDisconnect() OVERRIDE;
   private:
    Me2MeNativeMessagingHost* parent_;
  };

  
  
  
  void Me2MeNativeMessagingHost::EnsureElevatedHostCreated();

  
  void DisconnectElevatedHost();

  
  scoped_ptr<extensions::NativeMessagingChannel> elevated_channel_;

  
  
  scoped_ptr<ElevatedChannelEventHandler> elevated_channel_event_handler_;

  
  base::OneShotTimer<Me2MeNativeMessagingHost> elevated_host_timer_;
#endif  

  bool needs_elevation_;

  
  intptr_t parent_window_handle_;

  base::Closure quit_closure_;

  
  
  scoped_ptr<extensions::NativeMessagingChannel> channel_;
  scoped_refptr<DaemonController> daemon_controller_;

  
  scoped_refptr<protocol::PairingRegistry> pairing_registry_;

  
  scoped_ptr<OAuthClient> oauth_client_;

  base::ThreadChecker thread_checker_;

  base::WeakPtr<Me2MeNativeMessagingHost> weak_ptr_;
  base::WeakPtrFactory<Me2MeNativeMessagingHost> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(Me2MeNativeMessagingHost);
};

}  

#endif  
