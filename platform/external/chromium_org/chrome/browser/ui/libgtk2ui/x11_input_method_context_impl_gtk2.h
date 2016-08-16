// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_LIBGTK2UI_X11_INPUT_METHOD_CONTEXT_IMPL_GTK2_H_
#define CHROME_BROWSER_UI_LIBGTK2UI_X11_INPUT_METHOD_CONTEXT_IMPL_GTK2_H_

#include <vector>

#include "base/containers/hash_tables.h"
#include "base/event_types.h"
#include "base/gtest_prod_util.h"
#include "base/strings/string16.h"
#include "ui/base/glib/glib_integers.h"
#include "ui/base/glib/glib_signal.h"
#include "ui/base/ime/linux/linux_input_method_context.h"
#include "ui/gfx/rect.h"

typedef union _GdkEvent GdkEvent;
typedef struct _GdkDrawable GdkWindow;
typedef struct _GtkIMContext GtkIMContext;

namespace libgtk2ui {

class X11InputMethodContextImplGtk2 : public ui::LinuxInputMethodContext {
 public:
  explicit X11InputMethodContextImplGtk2(
      ui::LinuxInputMethodContextDelegate* delegate);
  virtual ~X11InputMethodContextImplGtk2();

  
  virtual bool DispatchKeyEvent(const ui::KeyEvent& key_event) OVERRIDE;
  virtual void Reset() OVERRIDE;
  virtual void OnTextInputTypeChanged(ui::TextInputType text_input_type)
      OVERRIDE;
  virtual void OnCaretBoundsChanged(const gfx::Rect& caret_bounds) OVERRIDE;

 private:
  
  
  
  void ResetXModifierKeycodesCache();

  
  
  GdkEvent* GdkEventFromNativeEvent(const base::NativeEvent& native_event);

  
  bool IsKeycodeModifierKey(unsigned int keycode) const;

  
  
  
  bool IsAnyOfKeycodesPressed(const std::vector<int>& keycodes,
                              const char* keybits,
                              int num_keys) const;

  
  
  CHROMEG_CALLBACK_1(X11InputMethodContextImplGtk2, void, OnCommit,
                     GtkIMContext*, gchar*);
  CHROMEG_CALLBACK_0(X11InputMethodContextImplGtk2, void, OnPreeditChanged,
                     GtkIMContext*);
  CHROMEG_CALLBACK_0(X11InputMethodContextImplGtk2, void, OnPreeditEnd,
                     GtkIMContext*);
  CHROMEG_CALLBACK_0(X11InputMethodContextImplGtk2, void, OnPreeditStart,
                     GtkIMContext*);

  
  ui::LinuxInputMethodContextDelegate* delegate_;

  
  
  GtkIMContext* gtk_context_simple_;
  
  GtkIMContext* gtk_multicontext_;

  
  
  GtkIMContext* gtk_context_;

  
  GdkWindow* gdk_last_set_client_window_;

  
  gfx::Rect last_caret_bounds_;

  
  base::hash_set<unsigned int> modifier_keycodes_;

  
  std::vector<int> meta_keycodes_;
  std::vector<int> super_keycodes_;
  std::vector<int> hyper_keycodes_;

  
  
  
  
  
  
  
  
  class GtkCommitSignalTrap {
   public:
    GtkCommitSignalTrap();

    
    void StartTrap(guint keyval);

    
    void StopTrap();

    
    
    
    
    bool Trap(const base::string16& text);

    
    bool IsSignalCaught() const { return is_signal_caught_; }

   private:
    bool is_trap_enabled_;
    guint gdk_event_key_keyval_;
    bool is_signal_caught_;

    DISALLOW_COPY_AND_ASSIGN(GtkCommitSignalTrap);
  };

  GtkCommitSignalTrap commit_signal_trap_;

  FRIEND_TEST_ALL_PREFIXES(X11InputMethodContextImplGtk2FriendTest,
                           GtkCommitSignalTrap);

  DISALLOW_COPY_AND_ASSIGN(X11InputMethodContextImplGtk2);
};

}  

#endif  
