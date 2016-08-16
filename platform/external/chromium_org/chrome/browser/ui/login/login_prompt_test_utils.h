// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_LOGIN_LOGIN_PROMPT_TEST_UTILS_H_
#define CHROME_BROWSER_UI_LOGIN_LOGIN_PROMPT_TEST_UTILS_H_

#include <list>

#include "chrome/browser/chrome_notification_types.h"
#include "content/public/browser/navigation_controller.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/test/test_utils.h"

class LoginHandler;

class LoginPromptBrowserTestObserver : public content::NotificationObserver {
 public:
  LoginPromptBrowserTestObserver();
  virtual ~LoginPromptBrowserTestObserver();

  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  void AddHandler(LoginHandler* handler);

  void RemoveHandler(LoginHandler* handler);

  void Register(const content::NotificationSource& source);

  const std::list<LoginHandler*>& handlers() const { return handlers_; }

  int auth_needed_count() const { return auth_needed_count_; }
  int auth_supplied_count() const { return auth_supplied_count_; }
  int auth_cancelled_count() const { return auth_cancelled_count_; }

 private:
  std::list<LoginHandler*> handlers_;

  
  
  
  
  int auth_needed_count_;
  int auth_supplied_count_;
  int auth_cancelled_count_;

 private:
  content::NotificationRegistrar registrar_;

  DISALLOW_COPY_AND_ASSIGN(LoginPromptBrowserTestObserver);
};

template <int T>
class WindowedNavigationObserver
    : public content::WindowedNotificationObserver {
 public:
  explicit WindowedNavigationObserver(
      content::NavigationController* controller);

 private:
  DISALLOW_COPY_AND_ASSIGN(WindowedNavigationObserver);
};

template <int T>
WindowedNavigationObserver<T>::WindowedNavigationObserver(
    content::NavigationController* controller)
    : content::WindowedNotificationObserver(
        T, content::Source<content::NavigationController>(controller)) {
}

typedef WindowedNavigationObserver<chrome::NOTIFICATION_AUTH_NEEDED>
    WindowedAuthNeededObserver;

typedef WindowedNavigationObserver<chrome::NOTIFICATION_AUTH_CANCELLED>
    WindowedAuthCancelledObserver;

typedef WindowedNavigationObserver<chrome::NOTIFICATION_AUTH_SUPPLIED>
    WindowedAuthSuppliedObserver;

class WindowedLoadStopObserver
    : public WindowedNavigationObserver<content::NOTIFICATION_LOAD_STOP> {
 public:
  WindowedLoadStopObserver(content::NavigationController* controller,
                           int notification_count);

 protected:
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

 private:
  int remaining_notification_count_;  

  DISALLOW_COPY_AND_ASSIGN(WindowedLoadStopObserver);
};

#endif  
