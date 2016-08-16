// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_FEEDBACK_FEEDBACK_PROFILE_OBSERVER_H_
#define CHROME_BROWSER_FEEDBACK_FEEDBACK_PROFILE_OBSERVER_H_

#include "base/basictypes.h"
#include "base/lazy_instance.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"

namespace content {
class BrowserContext;
}

namespace feedback {

class FeedbackUploader;

class FeedbackProfileObserver : public content::NotificationObserver {
 public:
  static void Initialize();

 private:
  friend struct base::DefaultLazyInstanceTraits<FeedbackProfileObserver>;

  FeedbackProfileObserver();
  virtual ~FeedbackProfileObserver();

  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  
  
  void QueueUnsentReports(content::BrowserContext* context);

  static void QueueSingleReport(feedback::FeedbackUploader* uploader,
                                const std::string& data);

  
  
  content::NotificationRegistrar prefs_registrar_;

  DISALLOW_COPY_AND_ASSIGN(FeedbackProfileObserver);
};

}  

#endif  
