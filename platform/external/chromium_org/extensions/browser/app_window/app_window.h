// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_APP_WINDOW_APP_WINDOW_H_
#define EXTENSIONS_BROWSER_APP_WINDOW_APP_WINDOW_H_

#include <string>
#include <vector>

#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "components/sessions/session_id.h"
#include "components/web_modal/popup_manager.h"
#include "components/web_modal/web_contents_modal_dialog_manager_delegate.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "content/public/browser/web_contents_delegate.h"
#include "content/public/browser/web_contents_observer.h"
#include "extensions/browser/extension_icon_image.h"
#include "ui/base/ui_base_types.h"  
#include "ui/gfx/image/image.h"
#include "ui/gfx/rect.h"

class GURL;
class SkRegion;

namespace base {
class DictionaryValue;
}

namespace content {
class BrowserContext;
class WebContents;
}

namespace ui {
class BaseWindow;
}

namespace extensions {

class AppDelegate;
class AppWebContentsHelper;
class Extension;
class NativeAppWindow;
class PlatformAppBrowserTest;
class WindowController;

struct DraggableRegion;

class AppWindowContents {
 public:
  AppWindowContents() {}
  virtual ~AppWindowContents() {}

  
  virtual void Initialize(content::BrowserContext* context,
                          const GURL& url) = 0;

  
  virtual void LoadContents(int32 creator_process_id) = 0;

  
  virtual void NativeWindowChanged(NativeAppWindow* native_app_window) = 0;

  
  virtual void NativeWindowClosed() = 0;

  
  virtual void DispatchWindowShownForTests() const = 0;

  virtual content::WebContents* GetWebContents() const = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(AppWindowContents);
};

class AppWindow : public content::NotificationObserver,
                  public content::WebContentsDelegate,
                  public content::WebContentsObserver,
                  public web_modal::WebContentsModalDialogManagerDelegate,
                  public IconImage::Observer {
 public:
  enum WindowType {
    WINDOW_TYPE_DEFAULT = 1 << 0,   
    WINDOW_TYPE_PANEL = 1 << 1,     
    WINDOW_TYPE_V1_PANEL = 1 << 2,  
                                    
  };

  enum Frame {
    FRAME_CHROME,  
    FRAME_NONE,    
  };

  enum FullscreenType {
    
    FULLSCREEN_TYPE_NONE = 0,

    
    FULLSCREEN_TYPE_WINDOW_API = 1 << 0,

    
    FULLSCREEN_TYPE_HTML_API = 1 << 1,

    
    
    FULLSCREEN_TYPE_OS = 1 << 2,

    
    
    FULLSCREEN_TYPE_FORCED = 1 << 3,
  };

  struct BoundsSpecification {
    
    static const int kUnspecifiedPosition;

    BoundsSpecification();
    ~BoundsSpecification();

    
    
    
    gfx::Rect bounds;

    gfx::Size minimum_size;
    gfx::Size maximum_size;

    
    
    void ResetBounds();
  };

  struct CreateParams {
    CreateParams();
    ~CreateParams();

    WindowType window_type;
    Frame frame;

    bool has_frame_color;
    SkColor active_frame_color;
    SkColor inactive_frame_color;
    bool alpha_enabled;

    
    
    BoundsSpecification content_spec;

    
    
    BoundsSpecification window_spec;

    std::string window_key;

    
    int32 creator_process_id;

    
    ui::WindowShowState state;

    
    bool hidden;

    
    bool resizable;

    
    bool focused;

    
    
    bool always_on_top;

    
    bool visible_on_all_workspaces;

    
    
    gfx::Rect GetInitialWindowBounds(const gfx::Insets& frame_insets) const;

    
    
    
    gfx::Size GetContentMinimumSize(const gfx::Insets& frame_insets) const;
    gfx::Size GetContentMaximumSize(const gfx::Insets& frame_insets) const;
    gfx::Size GetWindowMinimumSize(const gfx::Insets& frame_insets) const;
    gfx::Size GetWindowMaximumSize(const gfx::Insets& frame_insets) const;
  };

  
  
  static SkRegion* RawDraggableRegionsToSkRegion(
      const std::vector<DraggableRegion>& regions);

  
  
  
  
  AppWindow(content::BrowserContext* context,
            AppDelegate* app_delegate,
            const Extension* extension);

  
  
  void Init(const GURL& url,
            AppWindowContents* app_window_contents,
            const CreateParams& params);

  const std::string& window_key() const { return window_key_; }
  const SessionID& session_id() const { return session_id_; }
  const std::string& extension_id() const { return extension_id_; }
  content::WebContents* web_contents() const;
  WindowType window_type() const { return window_type_; }
  bool window_type_is_panel() const {
    return (window_type_ == WINDOW_TYPE_PANEL ||
            window_type_ == WINDOW_TYPE_V1_PANEL);
  }
  content::BrowserContext* browser_context() const { return browser_context_; }
  const gfx::Image& app_icon() const { return app_icon_; }
  const GURL& app_icon_url() const { return app_icon_url_; }
  const gfx::Image& badge_icon() const { return badge_icon_; }
  const GURL& badge_icon_url() const { return badge_icon_url_; }
  bool is_hidden() const { return is_hidden_; }

  const Extension* GetExtension() const;
  NativeAppWindow* GetBaseWindow();
  gfx::NativeWindow GetNativeWindow();

  
  gfx::Rect GetClientBounds() const;

  
  
  base::string16 GetTitle() const;

  
  
  void OnNativeClose();

  
  
  void OnNativeWindowChanged();

  
  void OnNativeWindowActivated();

  
  void SetAppIconUrl(const GURL& icon_url);

  
  void SetBadgeIconUrl(const GURL& icon_url);

  
  void ClearBadge();

  
  void UpdateShape(scoped_ptr<SkRegion> region);

  
  void UpdateDraggableRegions(const std::vector<DraggableRegion>& regions);

  
  
  void UpdateAppIcon(const gfx::Image& image);

  
  
  
  
  
  void SetFullscreen(FullscreenType type, bool enable);

  
  bool IsFullscreen() const;

  
  
  bool IsForcedFullscreen() const;

  
  
  bool IsHtmlApiFullscreen() const;

  
  
  void Fullscreen();
  void Maximize();
  void Minimize();
  void Restore();

  
  void OSFullscreen();

  
  
  void ForcedFullscreen();

  
  void SetContentSizeConstraints(const gfx::Size& min_size,
                                 const gfx::Size& max_size);

  enum ShowType { SHOW_ACTIVE, SHOW_INACTIVE };

  
  
  void Show(ShowType show_type);

  
  
  void Hide();

  AppWindowContents* app_window_contents_for_test() {
    return app_window_contents_.get();
  }

  int fullscreen_types_for_test() {
    return fullscreen_types_;
  }

  
  
  void SetAlwaysOnTop(bool always_on_top);

  
  
  
  bool IsAlwaysOnTop() const;

  
  
  void GetSerializedState(base::DictionaryValue* properties) const;

  
  
  void WindowEventsReady();

  
  bool requested_alpha_enabled() const { return requested_alpha_enabled_; }

  void SetAppWindowContentsForTesting(scoped_ptr<AppWindowContents> contents) {
    app_window_contents_ = contents.Pass();
  }

 protected:
  virtual ~AppWindow();

 private:
  
  friend class PlatformAppBrowserTest;

  
  virtual void CloseContents(content::WebContents* contents) OVERRIDE;
  virtual bool ShouldSuppressDialogs() OVERRIDE;
  virtual content::ColorChooser* OpenColorChooser(
      content::WebContents* web_contents,
      SkColor color,
      const std::vector<content::ColorSuggestion>& suggestions) OVERRIDE;
  virtual void RunFileChooser(content::WebContents* tab,
                              const content::FileChooserParams& params)
      OVERRIDE;
  virtual bool IsPopupOrPanel(const content::WebContents* source)
      const OVERRIDE;
  virtual void MoveContents(content::WebContents* source,
                            const gfx::Rect& pos) OVERRIDE;
  virtual void NavigationStateChanged(
      const content::WebContents* source,
      content::InvalidateTypes changed_flags) OVERRIDE;
  virtual void ToggleFullscreenModeForTab(content::WebContents* source,
                                          bool enter_fullscreen) OVERRIDE;
  virtual bool IsFullscreenForTabOrPending(const content::WebContents* source)
      const OVERRIDE;
  virtual void RequestMediaAccessPermission(
      content::WebContents* web_contents,
      const content::MediaStreamRequest& request,
      const content::MediaResponseCallback& callback) OVERRIDE;
  virtual bool CheckMediaAccessPermission(
      content::WebContents* web_contents,
      const GURL& security_origin,
      content::MediaStreamType type) OVERRIDE;
  virtual content::WebContents* OpenURLFromTab(
      content::WebContents* source,
      const content::OpenURLParams& params) OVERRIDE;
  virtual void AddNewContents(content::WebContents* source,
                              content::WebContents* new_contents,
                              WindowOpenDisposition disposition,
                              const gfx::Rect& initial_pos,
                              bool user_gesture,
                              bool* was_blocked) OVERRIDE;
  virtual bool PreHandleKeyboardEvent(
      content::WebContents* source,
      const content::NativeWebKeyboardEvent& event,
      bool* is_keyboard_shortcut) OVERRIDE;
  virtual void HandleKeyboardEvent(content::WebContents* source,
                                   const content::NativeWebKeyboardEvent& event)
      OVERRIDE;
  virtual void RequestToLockMouse(content::WebContents* web_contents,
                                  bool user_gesture,
                                  bool last_unlocked_by_target) OVERRIDE;
  virtual bool PreHandleGestureEvent(content::WebContents* source,
                                     const blink::WebGestureEvent& event)
      OVERRIDE;

  
  virtual void DidFirstVisuallyNonEmptyPaint() OVERRIDE;

  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  
  virtual void SetWebContentsBlocked(content::WebContents* web_contents,
                                     bool blocked) OVERRIDE;
  virtual bool IsWebContentsVisible(content::WebContents* web_contents)
      OVERRIDE;

  
  void SaveWindowPosition();

  
  
  void AdjustBoundsToBeVisibleOnScreen(const gfx::Rect& cached_bounds,
                                       const gfx::Rect& cached_screen_bounds,
                                       const gfx::Rect& current_screen_bounds,
                                       const gfx::Size& minimum_size,
                                       gfx::Rect* bounds) const;

  
  
  CreateParams LoadDefaults(CreateParams params) const;

  
  void UpdateExtensionAppIcon();

  
  void SetNativeWindowFullscreen();

  
  
  bool IntersectsWithTaskbar() const;

  
  void UpdateNativeAlwaysOnTop();

  
  
  void SendOnWindowShownIfShown();

  
  virtual web_modal::WebContentsModalDialogHost* GetWebContentsModalDialogHost()
      OVERRIDE;

  
  
  void UpdateBadgeIcon(const gfx::Image& image);

  
  void DidDownloadFavicon(int id,
                          int http_status_code,
                          const GURL& image_url,
                          const std::vector<SkBitmap>& bitmaps,
                          const std::vector<gfx::Size>& original_bitmap_sizes);

  
  virtual void OnExtensionIconImageChanged(IconImage* image) OVERRIDE;

  
  
  content::BrowserContext* browser_context_;

  const std::string extension_id_;

  
  
  std::string window_key_;

  const SessionID session_id_;
  WindowType window_type_;
  content::NotificationRegistrar registrar_;

  
  gfx::Image app_icon_;

  
  
  GURL app_icon_url_;

  
  scoped_ptr<IconImage> app_icon_image_;

  
  gfx::Image badge_icon_;

  
  GURL badge_icon_url_;

  
  scoped_ptr<IconImage> badge_icon_image_;

  scoped_ptr<NativeAppWindow> native_app_window_;
  scoped_ptr<AppWindowContents> app_window_contents_;
  scoped_ptr<AppDelegate> app_delegate_;
  scoped_ptr<AppWebContentsHelper> helper_;

  
  
  scoped_ptr<web_modal::PopupManager> popup_manager_;

  base::WeakPtrFactory<AppWindow> image_loader_ptr_factory_;

  
  int fullscreen_types_;

  
  
  bool show_on_first_paint_;

  
  bool first_paint_complete_;

  
  bool has_been_shown_;

  
  bool can_send_events_;

  
  
  
  
  
  
  bool is_hidden_;

  
  ShowType delayed_show_type_;

  
  
  
  
  
  bool cached_always_on_top_;

  
  bool requested_alpha_enabled_;

  DISALLOW_COPY_AND_ASSIGN(AppWindow);
};

}  

#endif  
