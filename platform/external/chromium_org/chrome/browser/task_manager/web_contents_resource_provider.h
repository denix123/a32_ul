// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_TASK_MANAGER_WEB_CONTENTS_RESOURCE_PROVIDER_H_
#define CHROME_BROWSER_TASK_MANAGER_WEB_CONTENTS_RESOURCE_PROVIDER_H_

#include <map>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "chrome/browser/task_manager/renderer_resource.h"
#include "chrome/browser/task_manager/resource_provider.h"

class TaskManager;

namespace content {
class RenderFrameHost;
class SiteInstance;
class WebContents;
}

namespace task_manager {

class RendererResource;
class TaskManagerWebContentsEntry;
class WebContentsInformation;

class WebContentsResourceProvider : public ResourceProvider {
 public:
  WebContentsResourceProvider(TaskManager* task_manager,
                              scoped_ptr<WebContentsInformation> info);

  
  virtual RendererResource* GetResource(int origin_pid,
                                        int child_id,
                                        int route_id) OVERRIDE;
  virtual void StartUpdating() OVERRIDE;
  virtual void StopUpdating() OVERRIDE;

  
  
  void OnWebContentsCreated(content::WebContents* web_contents);

  
  void DeleteEntry(content::WebContents* web_contents,
                   TaskManagerWebContentsEntry* entry);

  TaskManager* task_manager() { return task_manager_; }
  WebContentsInformation* info() { return info_.get(); }

 protected:
  virtual ~WebContentsResourceProvider();

 private:
  typedef std::map<content::WebContents*, TaskManagerWebContentsEntry*>
      EntryMap;

  TaskManager* task_manager_;

  
  
  
  EntryMap entries_;

  
  
  scoped_ptr<WebContentsInformation> info_;

  DISALLOW_COPY_AND_ASSIGN(WebContentsResourceProvider);
};

}  

#endif  
