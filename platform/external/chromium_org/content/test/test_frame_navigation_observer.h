// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_TEST_TEST_FRAME_NAVIGATION_OBSERVER_H_
#define CONTENT_TEST_TEST_FRAME_NAVIGATION_OBSERVER_H_

#include <set>

#include "base/callback.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "content/public/browser/web_contents_observer.h"
#include "content/public/test/test_utils.h"

class GURL;

namespace content {
class FrameTreeNode;
class RenderFrameHostImpl;
class WebContents;
struct LoadCommittedDetails;

class TestFrameNavigationObserver : public WebContentsObserver {
 public:
  
  
  TestFrameNavigationObserver(FrameTreeNode* node, int number_of_navigations);
  
  explicit TestFrameNavigationObserver(FrameTreeNode* node);

  virtual ~TestFrameNavigationObserver();

  
  
  void Wait();

 private:
  
  virtual void DidStartProvisionalLoadForFrame(
      RenderFrameHost* render_frame_host,
      const GURL& validated_url,
      bool is_error_page,
      bool is_iframe_srcdoc) OVERRIDE;
  virtual void DidNavigateAnyFrame(
      const LoadCommittedDetails& details,
      const FrameNavigateParams& params) OVERRIDE;

  
  int frame_tree_node_id_;

  
  bool navigation_started_;

  
  int navigations_completed_;

  
  int number_of_navigations_;

  
  scoped_refptr<MessageLoopRunner> message_loop_runner_;

  DISALLOW_COPY_AND_ASSIGN(TestFrameNavigationObserver);
};

}  

#endif  
