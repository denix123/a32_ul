// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_TEST_RESULT_CATCHER_H_
#define EXTENSIONS_TEST_RESULT_CATCHER_H_

#include <deque>
#include <string>

#include "base/compiler_specific.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"

namespace content {
class BrowserContext;
}  

namespace extensions {

class ResultCatcher : public content::NotificationObserver {
 public:
  ResultCatcher();
  virtual ~ResultCatcher();

  
  
  bool GetNextResult();

  void RestrictToBrowserContext(content::BrowserContext* context) {
    browser_context_restriction_ = context;
  }

  const std::string& message() { return message_; }

 private:
  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  content::NotificationRegistrar registrar_;

  
  std::deque<bool> results_;

  
  std::deque<std::string> messages_;
  std::string message_;

  
  content::BrowserContext* browser_context_restriction_;

  
  
  bool waiting_;
};

}  

#endif  
