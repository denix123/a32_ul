// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef JINGLE_NOTIFIER_LISTENER_PUSH_NOTIFICATIONS_SUBSCRIBE_TASK_H_
#define JINGLE_NOTIFIER_LISTENER_PUSH_NOTIFICATIONS_SUBSCRIBE_TASK_H_

#include <string>
#include <vector>

#include "base/compiler_specific.h"
#include "base/gtest_prod_util.h"
#include "jingle/notifier/listener/notification_defines.h"
#include "talk/xmpp/xmpptask.h"
#include "third_party/webrtc/libjingle/xmllite/xmlelement.h"

namespace notifier {
class PushNotificationsSubscribeTask : public buzz::XmppTask {
 public:
  class Delegate {
   public:
     virtual ~Delegate() {}
     virtual void OnSubscribed() = 0;
     virtual void OnSubscriptionError() = 0;
  };

  PushNotificationsSubscribeTask(buzz::XmppTaskParentInterface* parent,
                                 const SubscriptionList& subscriptions,
                                 Delegate* delegate);
  virtual ~PushNotificationsSubscribeTask();

  
  virtual int ProcessStart() OVERRIDE;
  virtual int ProcessResponse() OVERRIDE;
  virtual bool HandleStanza(const buzz::XmlElement* stanza) OVERRIDE;

 private:
  
  static buzz::XmlElement* MakeSubscriptionMessage(
      const SubscriptionList& subscriptions,
      const buzz::Jid& jid, const std::string& task_id);

  SubscriptionList subscriptions_;
  Delegate* delegate_;

  FRIEND_TEST_ALL_PREFIXES(PushNotificationsSubscribeTaskTest,
                           MakeSubscriptionMessage);

  DISALLOW_COPY_AND_ASSIGN(PushNotificationsSubscribeTask);
};

typedef PushNotificationsSubscribeTask::Delegate
    PushNotificationsSubscribeTaskDelegate;


}  

#endif  