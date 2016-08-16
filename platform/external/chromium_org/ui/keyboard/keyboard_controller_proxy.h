// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_KEYBOARD_KEYBOARD_CONTROLLER_PROXY_H_
#define UI_KEYBOARD_KEYBOARD_CONTROLLER_PROXY_H_

#include "base/memory/scoped_ptr.h"
#include "content/public/common/media_stream_request.h"
#include "ui/aura/window_observer.h"
#include "ui/base/ime/text_input_type.h"
#include "ui/keyboard/keyboard_export.h"

namespace aura {
class Window;
}
namespace content {
class BrowserContext;
class SiteInstance;
class WebContents;
}
namespace gfx {
class Rect;
}
namespace ui {
class InputMethod;
}
namespace wm {
class Shadow;
}

namespace keyboard {

class KEYBOARD_EXPORT KeyboardControllerProxy : public aura::WindowObserver {
 public:
  class TestApi {
   public:
    explicit TestApi(KeyboardControllerProxy* proxy) : proxy_(proxy) {}

    const content::WebContents* keyboard_contents() {
      return proxy_->keyboard_contents_.get();
    }

   private:
    KeyboardControllerProxy* proxy_;

    DISALLOW_COPY_AND_ASSIGN(TestApi);
  };

  KeyboardControllerProxy();
  virtual ~KeyboardControllerProxy();

  
  
  virtual aura::Window* GetKeyboardWindow();

  
  
  virtual bool HasKeyboardWindow() const;

  
  
  virtual ui::InputMethod* GetInputMethod() = 0;

  
  virtual void RequestAudioInput(content::WebContents* web_contents,
      const content::MediaStreamRequest& request,
      const content::MediaResponseCallback& callback) = 0;

  
  
  
  virtual void ShowKeyboardContainer(aura::Window* container);

  
  
  
  virtual void HideKeyboardContainer(aura::Window* container);

  
  virtual void SetUpdateInputType(ui::TextInputType type);

  
  
  virtual void EnsureCaretInWorkArea();

  
  
  virtual void LoadSystemKeyboard();

  
  
  
  
  
  
  
  
  
  virtual void ReloadKeyboardIfNeeded();

 protected:
  
  
  virtual content::BrowserContext* GetBrowserContext() = 0;

  
  
  
  
  virtual void SetupWebContents(content::WebContents* contents);

  
  virtual void OnWindowBoundsChanged(aura::Window* window,
                                     const gfx::Rect& old_bounds,
                                     const gfx::Rect& new_bounds) OVERRIDE;
  virtual void OnWindowDestroyed(aura::Window* window) OVERRIDE;

 private:
  friend class TestApi;

  
  void LoadContents(const GURL& url);

  
  const GURL& GetVirtualKeyboardUrl();

  const GURL default_url_;

  scoped_ptr<content::WebContents> keyboard_contents_;
  scoped_ptr<wm::Shadow> shadow_;

  DISALLOW_COPY_AND_ASSIGN(KeyboardControllerProxy);
};

}  

#endif  
