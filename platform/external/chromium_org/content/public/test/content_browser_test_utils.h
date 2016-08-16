// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_TEST_CONTENT_BROWSER_TEST_UTILS_H_
#define CONTENT_PUBLIC_TEST_CONTENT_BROWSER_TEST_UTILS_H_

#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "ui/gfx/native_widget_types.h"
#include "url/gurl.h"

namespace base {
class FilePath;
}

namespace gfx {
class Rect;
}


namespace content {

class MessageLoopRunner;
class RenderViewCreatedObserver;
class Shell;
class WebContents;

base::FilePath GetTestFilePath(const char* dir, const char* file);

GURL GetTestUrl(const char* dir, const char* file);

void NavigateToURL(Shell* window, const GURL& url);
void LoadDataWithBaseURL(Shell* window,
                         const GURL& url,
                         const std::string data,
                         const GURL& base_url);

void NavigateToURLBlockUntilNavigationsComplete(Shell* window,
                                                const GURL& url,
                                                int number_of_navigations);
void ReloadBlockUntilNavigationsComplete(Shell* window,
                                         int number_of_navigations);

void WaitForAppModalDialog(Shell* window);

class ShellAddedObserver {
 public:
  ShellAddedObserver();
  ~ShellAddedObserver();

  
  
  Shell* GetShell();

 private:
  void ShellCreated(Shell* shell);

  Shell* shell_;
  scoped_refptr<MessageLoopRunner> runner_;

  DISALLOW_COPY_AND_ASSIGN(ShellAddedObserver);
};

class WebContentsAddedObserver {
 public:
  WebContentsAddedObserver();
  ~WebContentsAddedObserver();

  
  
  WebContents* GetWebContents();

  
  bool RenderViewCreatedCalled();

  base::Callback<void(WebContents*)> web_contents_created_callback_;

 private:
  void WebContentsCreated(WebContents* web_contents);

  
  WebContents* web_contents_;
  scoped_ptr<RenderViewCreatedObserver> child_observer_;
  scoped_refptr<MessageLoopRunner> runner_;

  DISALLOW_COPY_AND_ASSIGN(WebContentsAddedObserver);
};

#if defined OS_MACOSX
void SetWindowBounds(gfx::NativeWindow window, const gfx::Rect& bounds);
#endif

}  

#endif  
