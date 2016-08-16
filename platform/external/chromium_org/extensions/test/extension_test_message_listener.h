// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_TEST_EXTENSION_TEST_MESSAGE_LISTENER_H_
#define EXTENSIONS_TEST_EXTENSION_TEST_MESSAGE_LISTENER_H_

#include <string>

#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"

namespace extensions {
class TestSendMessageFunction;
}

class ExtensionTestMessageListener : public content::NotificationObserver {
 public:
  
  ExtensionTestMessageListener(const std::string& expected_message,
                               bool will_reply);
  
  explicit ExtensionTestMessageListener(bool will_reply);

  virtual ~ExtensionTestMessageListener();

  
  
  
  
  bool WaitUntilSatisfied();

  
  
  void Reply(const std::string& message);

  
  void Reply(int message);

  void ReplyWithError(const std::string& error);

  
  
  void Reset();

  

  bool was_satisfied() const { return satisfied_; }

  void set_failure_message(const std::string& failure_message) {
    failure_message_ = failure_message;
  }

  const std::string& extension_id() const { return extension_id_; }
  void set_extension_id(const std::string& extension_id) {
    extension_id_ = extension_id;
  }

  const std::string& message() const { return message_; }

 private:
  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  content::NotificationRegistrar registrar_;

  
  std::string expected_message_;

  
  std::string message_;

  
  bool satisfied_;

  
  
  bool waiting_;

  
  bool wait_for_any_message_;

  
  
  bool will_reply_;

  
  bool replied_;

  
  std::string extension_id_;

  
  std::string failure_message_;

  
  bool failed_;

  
  scoped_refptr<extensions::TestSendMessageFunction> function_;
};

#endif  
