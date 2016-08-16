// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_TEST_BROWSER_TEST_UTILS_H_
#define CONTENT_PUBLIC_TEST_BROWSER_TEST_UTILS_H_

#include <queue>
#include <string>
#include <vector>

#include "base/callback_forward.h"
#include "base/compiler_specific.h"
#include "base/files/scoped_temp_dir.h"
#include "base/memory/ref_counted.h"
#include "base/process/process.h"
#include "base/strings/string16.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "content/public/browser/render_process_host_observer.h"
#include "content/public/browser/web_contents_observer.h"
#include "third_party/WebKit/public/web/WebInputEvent.h"
#include "ui/events/keycodes/keyboard_codes.h"
#include "url/gurl.h"

#if defined(OS_WIN)
#include "base/win/scoped_handle.h"
#endif

namespace base {
class RunLoop;
}

namespace gfx {
class Point;
}


namespace content {

class BrowserContext;
class MessageLoopRunner;
class RenderViewHost;
class WebContents;

GURL GetFileUrlWithQuery(const base::FilePath& path,
                         const std::string& query_string);

void WaitForLoadStop(WebContents* web_contents);

#if defined(USE_AURA)
void WaitForResizeComplete(WebContents* web_contents);
#endif  

void CrashTab(WebContents* web_contents);

void SimulateMouseClick(WebContents* web_contents,
                        int modifiers,
                        blink::WebMouseEvent::Button button);

void SimulateMouseClickAt(WebContents* web_contents,
                          int modifiers,
                          blink::WebMouseEvent::Button button,
                          const gfx::Point& point);

void SimulateMouseEvent(WebContents* web_contents,
                        blink::WebInputEvent::Type type,
                        const gfx::Point& point);

void SimulateTapAt(WebContents* web_contents, const gfx::Point& point);

void SimulateKeyPress(WebContents* web_contents,
                      ui::KeyboardCode key_code,
                      bool control,
                      bool shift,
                      bool alt,
                      bool command);

void SimulateKeyPressWithCode(WebContents* web_contents,
                              ui::KeyboardCode key_code,
                              const char* code,
                              bool control,
                              bool shift,
                              bool alt,
                              bool command);

namespace internal {
class ToRenderFrameHost {
 public:
  ToRenderFrameHost(WebContents* web_contents);
  ToRenderFrameHost(RenderViewHost* render_view_host);
  ToRenderFrameHost(RenderFrameHost* render_frame_host);

  RenderFrameHost* render_frame_host() const { return render_frame_host_; }

 private:
  RenderFrameHost* render_frame_host_;
};
}  

bool ExecuteScript(const internal::ToRenderFrameHost& adapter,
                   const std::string& script) WARN_UNUSED_RESULT;

bool ExecuteScriptAndExtractInt(const internal::ToRenderFrameHost& adapter,
                                const std::string& script,
                                int* result) WARN_UNUSED_RESULT;
bool ExecuteScriptAndExtractBool(const internal::ToRenderFrameHost& adapter,
                                 const std::string& script,
                                 bool* result) WARN_UNUSED_RESULT;
bool ExecuteScriptAndExtractString(const internal::ToRenderFrameHost& adapter,
                                   const std::string& script,
                                   std::string* result) WARN_UNUSED_RESULT;

RenderFrameHost* FrameMatchingPredicate(
    WebContents* web_contents,
    const base::Callback<bool(RenderFrameHost*)>& predicate);

bool FrameMatchesName(const std::string& name, RenderFrameHost* frame);
bool FrameIsChildOfMainFrame(RenderFrameHost* frame);
bool FrameHasSourceUrl(const GURL& url, RenderFrameHost* frame);

bool ExecuteWebUIResourceTest(WebContents* web_contents,
                              const std::vector<int>& js_resource_ids);

std::string GetCookies(BrowserContext* browser_context, const GURL& url);

bool SetCookie(BrowserContext* browser_context,
               const GURL& url,
               const std::string& value);

void FetchHistogramsFromChildProcesses();

class TitleWatcher : public WebContentsObserver {
 public:
  
  
  
  TitleWatcher(WebContents* web_contents,
               const base::string16& expected_title);
  virtual ~TitleWatcher();

  
  void AlsoWaitForTitle(const base::string16& expected_title);

  
  
  
  const base::string16& WaitAndGetTitle() WARN_UNUSED_RESULT;

 private:
  
  virtual void DidStopLoading(RenderViewHost* render_view_host) OVERRIDE;
  virtual void TitleWasSet(NavigationEntry* entry, bool explicit_set) OVERRIDE;

  void TestTitle();

  std::vector<base::string16> expected_titles_;
  scoped_refptr<MessageLoopRunner> message_loop_runner_;

  
  base::string16 observed_title_;

  DISALLOW_COPY_AND_ASSIGN(TitleWatcher);
};

class WebContentsDestroyedWatcher : public WebContentsObserver {
 public:
  explicit WebContentsDestroyedWatcher(WebContents* web_contents);
  virtual ~WebContentsDestroyedWatcher();

  
  void Wait();

 private:
  
  virtual void WebContentsDestroyed() OVERRIDE;

  scoped_refptr<MessageLoopRunner> message_loop_runner_;

  DISALLOW_COPY_AND_ASSIGN(WebContentsDestroyedWatcher);
};

class RenderProcessHostWatcher : public RenderProcessHostObserver {
 public:
  enum WatchType {
    WATCH_FOR_PROCESS_EXIT,
    WATCH_FOR_HOST_DESTRUCTION
  };

  RenderProcessHostWatcher(RenderProcessHost* render_process_host,
                           WatchType type);
  
  RenderProcessHostWatcher(WebContents* web_contents, WatchType type);
  virtual ~RenderProcessHostWatcher();

  
  void Wait();

 private:
  
  virtual void RenderProcessExited(RenderProcessHost* host,
                                   base::ProcessHandle handle,
                                   base::TerminationStatus status,
                                   int exit_code) OVERRIDE;
  virtual void RenderProcessHostDestroyed(RenderProcessHost* host) OVERRIDE;

  RenderProcessHost* render_process_host_;
  WatchType type_;

  scoped_refptr<MessageLoopRunner> message_loop_runner_;

  DISALLOW_COPY_AND_ASSIGN(RenderProcessHostWatcher);
};

class DOMMessageQueue : public NotificationObserver {
 public:
  
  
  
  DOMMessageQueue();
  virtual ~DOMMessageQueue();

  
  void ClearQueue();

  
  
  bool WaitForMessage(std::string* message) WARN_UNUSED_RESULT;

  
  virtual void Observe(int type,
                       const NotificationSource& source,
                       const NotificationDetails& details) OVERRIDE;

 private:
  NotificationRegistrar registrar_;
  std::queue<std::string> message_queue_;
  scoped_refptr<MessageLoopRunner> message_loop_runner_;

  DISALLOW_COPY_AND_ASSIGN(DOMMessageQueue);
};

}  

#endif  