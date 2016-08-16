// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_TEST_BASE_EXTENSION_LOAD_WAITER_ONE_SHOT_H_
#define CHROME_TEST_BASE_EXTENSION_LOAD_WAITER_ONE_SHOT_H_

#include "base/callback_forward.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "content/public/test/test_utils.h"

namespace content {
class BrowserContext;
}  

class ExtensionLoadWaiterOneShot : public content::NotificationObserver {
 public:
  ExtensionLoadWaiterOneShot();
  virtual ~ExtensionLoadWaiterOneShot();

  
  
  void WaitForExtension(const char* extension_id, const base::Closure& load_cb);

  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  
  
  content::BrowserContext* browser_context() { return browser_context_; }

  
  const char* extension_id() { return extension_id_; }

 private:
  content::NotificationRegistrar registrar_;
  scoped_refptr<content::MessageLoopRunner> load_looper_;
  const char* extension_id_;
  content::BrowserContext* browser_context_;

  DISALLOW_COPY_AND_ASSIGN(ExtensionLoadWaiterOneShot);
};

#endif  
