// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_ANDROID_META_TAG_OBSERVER_H_
#define CHROME_BROWSER_ANDROID_META_TAG_OBSERVER_H_

#include "content/public/browser/web_contents_observer.h"

class GURL;

class MetaTagObserver : public content::WebContentsObserver {
 public:
  explicit MetaTagObserver(const std::string& meta_tag);
  virtual ~MetaTagObserver();

  
  virtual void DidFinishLoad(content::RenderFrameHost* render_frame_host,
                             const GURL& validated_url) OVERRIDE;

  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;

 protected:
  
  virtual void HandleMetaTagContent(const std::string& tag_content,
                                    const GURL& expected_url) = 0;

 private:
  
  void OnDidRetrieveMetaTagContent(bool success,
                                   const std::string& tag_name,
                                   const std::string& tag_content,
                                   const GURL& expected_url);

  const std::string meta_tag_;
  GURL validated_url_;

  DISALLOW_COPY_AND_ASSIGN(MetaTagObserver);
};

#endif  
