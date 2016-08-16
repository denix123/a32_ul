// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_TASK_MANAGER_EXTENSION_INFORMATION_H_
#define CHROME_BROWSER_TASK_MANAGER_EXTENSION_INFORMATION_H_

#include "base/basictypes.h"
#include "chrome/browser/task_manager/web_contents_information.h"

namespace task_manager {

class ExtensionProcessResource;

class ExtensionInformation
    : public NotificationObservingWebContentsInformation {
 public:
  ExtensionInformation();
  virtual ~ExtensionInformation();

  
  virtual bool CheckOwnership(content::WebContents* web_contents) OVERRIDE;
  virtual void GetAll(const NewWebContentsCallback& callback) OVERRIDE;
  virtual scoped_ptr<RendererResource> MakeResource(
      content::WebContents* web_contents) OVERRIDE;

 private:
  DISALLOW_COPY_AND_ASSIGN(ExtensionInformation);
};

}  

#endif  
