// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_DEVTOOLS_DEVTOOLS_WINDOW_H_
#define CHROME_BROWSER_DEVTOOLS_DEVTOOLS_WINDOW_H_

#include "chrome/browser/devtools/devtools_contents_resizing_strategy.h"
#include "chrome/browser/devtools/devtools_toggle_action.h"
#include "chrome/browser/devtools/devtools_ui_bindings.h"
#include "content/public/browser/web_contents_delegate.h"
#include "content/public/browser/web_contents_observer.h"

class Browser;
class BrowserWindow;
class DevToolsWindowTesting;
class DevToolsEventForwarder;

namespace content {
class DevToolsAgentHost;
struct NativeWebKeyboardEvent;
class RenderViewHost;
}

namespace user_prefs {
class PrefRegistrySyncable;
}

class DevToolsWindow : public DevToolsUIBindings::Delegate,
                       public content::WebContentsDelegate {
 public:
  class ObserverWithAccessor : public content::WebContentsObserver {
   public:
    explicit ObserverWithAccessor(content::WebContents* web_contents);
    virtual ~ObserverWithAccessor();

   private:
    DISALLOW_COPY_AND_ASSIGN(ObserverWithAccessor);
  };

  static const char kDevToolsApp[];

  virtual ~DevToolsWindow();

  static void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* registry);

  
  
  static DevToolsWindow* GetInstanceForInspectedWebContents(
      content::WebContents* inspected_web_contents);

  
  
  
  
  
  
  
  static content::WebContents* GetInTabWebContents(
      content::WebContents* inspected_tab,
      DevToolsContentsResizingStrategy* out_strategy);

  static bool IsDevToolsWindow(content::WebContents* web_contents);

  
  static DevToolsWindow* OpenDevToolsWindow(
      content::WebContents* inspected_web_contents,
      const DevToolsToggleAction& action);

  
  static DevToolsWindow* OpenDevToolsWindow(
      content::WebContents* inspected_web_contents);

  
  
  static DevToolsWindow* ToggleDevToolsWindow(
      Browser* browser,
      const DevToolsToggleAction& action);

  
  static void OpenExternalFrontend(
      Profile* profile,
      const std::string& frontend_uri,
      const scoped_refptr<content::DevToolsAgentHost>& agent_host,
      bool isWorker);

  
  static DevToolsWindow* OpenDevToolsWindowForWorker(
      Profile* profile,
      const scoped_refptr<content::DevToolsAgentHost>& worker_agent);

  static void InspectElement(content::WebContents* inspected_web_contents,
                             int x,
                             int y);

  
  
  void SetLoadCompletedCallback(const base::Closure& closure);

  
  bool ForwardKeyboardEvent(const content::NativeWebKeyboardEvent& event);

  

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  

  
  
  
  
  
  
  
  
  
  
  
  
  
  static bool HandleBeforeUnload(content::WebContents* contents,
                                 bool proceed,
                                 bool* proceed_to_fire_unload);

  
  
  
  
  
  static bool InterceptPageBeforeUnload(content::WebContents* contents);

  
  
  static bool HasFiredBeforeUnloadEventForDevToolsBrowser(Browser* browser);

  
  
  static bool NeedsToInterceptBeforeUnload(content::WebContents* contents);

  
  
  static void OnPageCloseCanceled(content::WebContents* contents);

 private:
  friend class DevToolsWindowTesting;

  
  
  
  
  
  
  
  
  
  
  
  
  
  enum LifeStage {
    kNotLoaded,
    kOnLoadFired, 
    kIsDockedSet, 
    kLoadCompleted,
    kClosing
  };

  DevToolsWindow(Profile* profile,
                 const GURL& frontend_url,
                 content::WebContents* inspected_web_contents,
                 bool can_dock);

  static DevToolsWindow* Create(Profile* profile,
                                const GURL& frontend_url,
                                content::WebContents* inspected_web_contents,
                                bool shared_worker_frontend,
                                bool external_frontend,
                                bool can_dock,
                                const std::string& settings);
  static GURL GetDevToolsURL(Profile* profile,
                             const GURL& base_url,
                             bool shared_worker_frontend,
                             bool external_frontend,
                             bool can_dock,
                             const std::string& settings);
  static DevToolsWindow* FindDevToolsWindow(content::DevToolsAgentHost*);
  static DevToolsWindow* AsDevToolsWindow(content::WebContents*);
  static DevToolsWindow* CreateDevToolsWindowForWorker(Profile* profile);
  static DevToolsWindow* ToggleDevToolsWindow(
      content::WebContents* web_contents,
      bool force_open,
      const DevToolsToggleAction& action,
      const std::string& settings);

  
  virtual content::WebContents* OpenURLFromTab(
      content::WebContents* source,
      const content::OpenURLParams& params) OVERRIDE;
  virtual void ActivateContents(content::WebContents* contents) OVERRIDE;
  virtual void AddNewContents(content::WebContents* source,
                              content::WebContents* new_contents,
                              WindowOpenDisposition disposition,
                              const gfx::Rect& initial_pos,
                              bool user_gesture,
                              bool* was_blocked) OVERRIDE;
  virtual void WebContentsCreated(content::WebContents* source_contents,
                                  int opener_render_frame_id,
                                  const base::string16& frame_name,
                                  const GURL& target_url,
                                  content::WebContents* new_contents) OVERRIDE;
  virtual void CloseContents(content::WebContents* source) OVERRIDE;
  virtual void ContentsZoomChange(bool zoom_in) OVERRIDE;
  virtual void BeforeUnloadFired(content::WebContents* tab,
                                 bool proceed,
                                 bool* proceed_to_fire_unload) OVERRIDE;
  virtual bool PreHandleKeyboardEvent(
      content::WebContents* source,
      const content::NativeWebKeyboardEvent& event,
      bool* is_keyboard_shortcut) OVERRIDE;
  virtual void HandleKeyboardEvent(
      content::WebContents* source,
      const content::NativeWebKeyboardEvent& event) OVERRIDE;
  virtual content::JavaScriptDialogManager*
      GetJavaScriptDialogManager() OVERRIDE;
  virtual content::ColorChooser* OpenColorChooser(
      content::WebContents* web_contents,
      SkColor color,
      const std::vector<content::ColorSuggestion>& suggestions) OVERRIDE;
  virtual void RunFileChooser(
      content::WebContents* web_contents,
      const content::FileChooserParams& params) OVERRIDE;
  virtual void WebContentsFocused(content::WebContents* contents) OVERRIDE;
  virtual bool PreHandleGestureEvent(
      content::WebContents* source,
      const blink::WebGestureEvent& event) OVERRIDE;

  
  virtual void ActivateWindow() OVERRIDE;
  virtual void CloseWindow() OVERRIDE;
  virtual void SetInspectedPageBounds(const gfx::Rect& rect) OVERRIDE;
  virtual void InspectElementCompleted() OVERRIDE;
  virtual void MoveWindow(int x, int y) OVERRIDE;
  virtual void SetIsDocked(bool is_docked) OVERRIDE;
  virtual void OpenInNewTab(const std::string& url) OVERRIDE;
  virtual void SetWhitelistedShortcuts(const std::string& message) OVERRIDE;
  virtual void InspectedContentsClosing() OVERRIDE;
  virtual void OnLoadCompleted() OVERRIDE;
  virtual InfoBarService* GetInfoBarService() OVERRIDE;
  virtual void RenderProcessGone() OVERRIDE;

  void CreateDevToolsBrowser();
  BrowserWindow* GetInspectedBrowserWindow();
  void ScheduleShow(const DevToolsToggleAction& action);
  void Show(const DevToolsToggleAction& action);
  void DoAction(const DevToolsToggleAction& action);
  void LoadCompleted();
  void UpdateBrowserToolbar();
  void UpdateBrowserWindow();
  content::WebContents* GetInspectedWebContents();

  scoped_ptr<ObserverWithAccessor> inspected_contents_observer_;

  Profile* profile_;
  content::WebContents* main_web_contents_;
  content::WebContents* toolbox_web_contents_;
  DevToolsUIBindings* bindings_;
  Browser* browser_;
  bool is_docked_;
  const bool can_dock_;
  LifeStage life_stage_;
  DevToolsToggleAction action_on_load_;
  DevToolsContentsResizingStrategy contents_resizing_strategy_;
  
  
  bool intercepted_page_beforeunload_;
  base::Closure load_completed_callback_;
  base::Closure close_callback_;

  base::TimeTicks inspect_element_start_time_;
  scoped_ptr<DevToolsEventForwarder> event_forwarder_;

  friend class DevToolsEventForwarder;
  DISALLOW_COPY_AND_ASSIGN(DevToolsWindow);
};

#endif  
