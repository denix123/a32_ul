// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_WEBSITE_SETTINGS_PERMISSION_BUBBLE_MANAGER_H_
#define CHROME_BROWSER_UI_WEBSITE_SETTINGS_PERMISSION_BUBBLE_MANAGER_H_

#include <vector>

#include "base/memory/weak_ptr.h"
#include "chrome/browser/ui/website_settings/permission_bubble_view.h"
#include "content/public/browser/web_contents_observer.h"
#include "content/public/browser/web_contents_user_data.h"

class PermissionBubbleRequest;

class PermissionBubbleManager
    : public content::WebContentsObserver,
      public content::WebContentsUserData<PermissionBubbleManager>,
      public PermissionBubbleView::Delegate {
 public:
  
  static bool Enabled();

  virtual ~PermissionBubbleManager();

  
  
  
  
  
  
  virtual void AddRequest(PermissionBubbleRequest* request);

  
  
  
  
  
  
  
  virtual void CancelRequest(PermissionBubbleRequest* request);

  
  
  
  virtual void SetView(PermissionBubbleView* view) OVERRIDE;

 private:
  friend class PermissionBubbleManagerTest;
  friend class DownloadRequestLimiterTest;
  friend class content::WebContentsUserData<PermissionBubbleManager>;

  explicit PermissionBubbleManager(content::WebContents* web_contents);

  
  virtual void DocumentOnLoadCompletedInMainFrame() OVERRIDE;
  virtual void DocumentLoadedInFrame(
      content::RenderFrameHost* render_frame_host) OVERRIDE;

  
  
  virtual void NavigationEntryCommitted(
      const content::LoadCommittedDetails& details) OVERRIDE;
  virtual void WebContentsDestroyed() OVERRIDE;

  
  virtual void ToggleAccept(int request_index, bool new_value) OVERRIDE;
  virtual void SetCustomizationMode() OVERRIDE;
  virtual void Accept() OVERRIDE;
  virtual void Deny() OVERRIDE;
  virtual void Closing() OVERRIDE;

  
  void ScheduleShowBubble();

  
  
  void TriggerShowBubble();

  
  void FinalizeBubble();

  
  
  
  void CancelPendingQueues();

  
  
  
  bool ExistingRequest(PermissionBubbleRequest* request,
                       const std::vector<PermissionBubbleRequest*>& queue,
                       bool* same_object);

  
  
  bool HasUserGestureRequest(
      const std::vector<PermissionBubbleRequest*>& queue);

  
  bool bubble_showing_;

  
  PermissionBubbleView* view_;

  std::vector<PermissionBubbleRequest*> requests_;
  std::vector<PermissionBubbleRequest*> queued_requests_;
  std::vector<PermissionBubbleRequest*> queued_frame_requests_;

  
  
  GURL request_url_;
  bool request_url_has_loaded_;

  std::vector<bool> accept_states_;
  bool customization_mode_;

  base::WeakPtrFactory<PermissionBubbleManager> weak_factory_;
};

#endif  
