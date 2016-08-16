// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_TASK_MANAGER_WEB_CONTENTS_INFORMATION_H_
#define CHROME_BROWSER_TASK_MANAGER_WEB_CONTENTS_INFORMATION_H_

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"

namespace content {
class WebContents;
}

namespace task_manager {

class RendererResource;

class WebContentsInformation {
 public:
  typedef base::Callback<void(content::WebContents*)> NewWebContentsCallback;

  WebContentsInformation();
  virtual ~WebContentsInformation();

  
  
  virtual void GetAll(const NewWebContentsCallback& callback) = 0;

  
  virtual bool CheckOwnership(content::WebContents* web_contents) = 0;

  
  
  virtual void StartObservingCreation(
      const NewWebContentsCallback& callback) = 0;

  
  virtual void StopObservingCreation() = 0;

  
  virtual scoped_ptr<RendererResource> MakeResource(
      content::WebContents* web_contents) = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(WebContentsInformation);
};

class NotificationObservingWebContentsInformation
    : public WebContentsInformation,
      public content::NotificationObserver {
 public:
  NotificationObservingWebContentsInformation();
  virtual ~NotificationObservingWebContentsInformation();

  
  virtual void StartObservingCreation(const NewWebContentsCallback& callback)
      OVERRIDE;
  virtual void StopObservingCreation() OVERRIDE;

  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

 private:
  content::NotificationRegistrar registrar_;
  NewWebContentsCallback observer_callback_;
  DISALLOW_COPY_AND_ASSIGN(NotificationObservingWebContentsInformation);
};

}  

#endif  
