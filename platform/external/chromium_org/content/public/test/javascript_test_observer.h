// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_TEST_JAVASCRIPT_TEST_OBSERVER_H_
#define CONTENT_PUBLIC_TEST_JAVASCRIPT_TEST_OBSERVER_H_

#include <string>

#include "base/compiler_specific.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"

namespace base {
class DictionaryValue;
}

namespace content {
class WebContents;

class TestMessageHandler {
 public:
  enum MessageResponse {
    
    CONTINUE,
    
    DONE
  };

  TestMessageHandler();
  virtual ~TestMessageHandler();

  
  virtual MessageResponse HandleMessage(const std::string& json) = 0;

  void SetError(const std::string& message);

  bool ok() const {
    return ok_;
  }

  const std::string& error_message() const {
    return error_message_;
  }

  
  virtual void Reset();

 private:
  bool ok_;
  std::string error_message_;
};

class JavascriptTestObserver : public NotificationObserver {
 public:
  
  
  JavascriptTestObserver(WebContents* web_contents,
                         TestMessageHandler* handler);

  virtual ~JavascriptTestObserver();

  
  
  
  bool Run();

  
  
  void Reset();

  virtual void Observe(
      int type,
      const NotificationSource& source,
      const NotificationDetails& details) OVERRIDE;

 private:
  
  void Continue();

  
  void EndTest();

  TestMessageHandler* handler_;
  bool running_;
  bool finished_;
  NotificationRegistrar registrar_;

  DISALLOW_COPY_AND_ASSIGN(JavascriptTestObserver);
};

}  

#endif  
