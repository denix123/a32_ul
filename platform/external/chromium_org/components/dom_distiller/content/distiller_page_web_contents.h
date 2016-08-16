// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_DOM_DISTILLER_CONTENT_DISTILLER_PAGE_WEB_CONTENTS_H_
#define COMPONENTS_DOM_DISTILLER_CONTENT_DISTILLER_PAGE_WEB_CONTENTS_H_

#include <string>

#include "base/memory/scoped_ptr.h"
#include "components/dom_distiller/core/distiller_page.h"
#include "content/public/browser/web_contents.h"
#include "content/public/browser/web_contents_delegate.h"
#include "content/public/browser/web_contents_observer.h"
#include "url/gurl.h"

namespace dom_distiller {

class SourcePageHandleWebContents : public SourcePageHandle {
 public:
  explicit SourcePageHandleWebContents(
      scoped_ptr<content::WebContents> web_contents);
  virtual ~SourcePageHandleWebContents();

  scoped_ptr<content::WebContents> GetWebContents();

 private:
  
  scoped_ptr<content::WebContents> web_contents_;
};

class DistillerPageWebContentsFactory : public DistillerPageFactory {
 public:
  explicit DistillerPageWebContentsFactory(
      content::BrowserContext* browser_context)
      : DistillerPageFactory(), browser_context_(browser_context) {}
  virtual ~DistillerPageWebContentsFactory() {}

  virtual scoped_ptr<DistillerPage> CreateDistillerPage(
      const gfx::Size& render_view_size) const OVERRIDE;
  virtual scoped_ptr<DistillerPage> CreateDistillerPageWithHandle(
      scoped_ptr<SourcePageHandle> handle) const OVERRIDE;

 private:
  content::BrowserContext* browser_context_;
};

class DistillerPageWebContents : public DistillerPage,
                                 public content::WebContentsDelegate,
                                 public content::WebContentsObserver {
 public:
  DistillerPageWebContents(
      content::BrowserContext* browser_context,
      const gfx::Size& render_view_size,
      scoped_ptr<SourcePageHandleWebContents> optional_web_contents_handle);
  virtual ~DistillerPageWebContents();

  
  virtual gfx::Size GetSizeForNewRenderView(
      content::WebContents* web_contents) const OVERRIDE;

  
  virtual void DocumentLoadedInFrame(
      content::RenderFrameHost* render_frame_host) OVERRIDE;

  virtual void DidFailLoad(content::RenderFrameHost* render_frame_host,
                           const GURL& validated_url,
                           int error_code,
                           const base::string16& error_description) OVERRIDE;

 protected:
  virtual void DistillPageImpl(const GURL& url,
                               const std::string& script) OVERRIDE;

 private:
  friend class TestDistillerPageWebContents;

  enum State {
    
    IDLE,
    
    LOADING_PAGE,
    
    PAGELOAD_FAILED,
    
    
    EXECUTING_JAVASCRIPT
  };

  
  
  virtual void CreateNewWebContents(const GURL& url);

  
  
  void ExecuteJavaScript();

  
  void OnWebContentsDistillationDone(const GURL& page_url,
                                     const base::Value* value);

  
  State state_;

  
  std::string script_;

  scoped_ptr<content::WebContents> web_contents_;
  content::BrowserContext* browser_context_;
  gfx::Size render_view_size_;
  DISALLOW_COPY_AND_ASSIGN(DistillerPageWebContents);
};

}  

#endif  
