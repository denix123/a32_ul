// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_LIBGTK2UI_GTK2_KEY_BINDINGS_HANDLER_H_
#define CHROME_BROWSER_UI_LIBGTK2UI_GTK2_KEY_BINDINGS_HANDLER_H_

#include <gtk/gtk.h>

#include <string>
#include <vector>

#include "base/event_types.h"
#include "chrome/browser/ui/libgtk2ui/owned_widget_gtk2.h"
#include "ui/events/linux/text_edit_command_auralinux.h"

namespace content {
struct NativeWebKeyboardEvent;
}

namespace ui {
class Event;
}

namespace libgtk2ui {

class Gtk2KeyBindingsHandler {
 public:
  Gtk2KeyBindingsHandler();
  virtual ~Gtk2KeyBindingsHandler();

  
  
  
  
  bool MatchEvent(const ui::Event& event,
                  std::vector<ui::TextEditCommandAuraLinux>* commands);

 private:
  
  struct Handler {
    GtkTextView parent_object;
    Gtk2KeyBindingsHandler *owner;
  };

  
  struct HandlerClass {
    GtkTextViewClass parent_class;
  };

  
  GtkWidget* CreateNewHandler();

  
  void EditCommandMatched(ui::TextEditCommandAuraLinux::CommandId id,
                          const std::string& value,
                          bool extend_selection);

  
  void BuildGdkEventKeyFromXEvent(const base::NativeEvent& xevent,
                                  GdkEventKey* gdk_event);

  
  static void HandlerInit(Handler *self);

  
  static void HandlerClassInit(HandlerClass *klass);

  
  static GType HandlerGetType();

  
  static Gtk2KeyBindingsHandler* GetHandlerOwner(GtkTextView* text_view);

  
  static void BackSpace(GtkTextView* text_view);

  
  static void CopyClipboard(GtkTextView* text_view);

  
  static void CutClipboard(GtkTextView* text_view);

  
  static void DeleteFromCursor(GtkTextView* text_view, GtkDeleteType type,
                               gint count);

  
  static void InsertAtCursor(GtkTextView* text_view, const gchar* str);

  
  static void MoveCursor(GtkTextView* text_view, GtkMovementStep step,
                         gint count, gboolean extend_selection);

  
  static void MoveViewport(GtkTextView* text_view, GtkScrollStep step,
                           gint count);

  
  static void PasteClipboard(GtkTextView* text_view);

  
  static void SelectAll(GtkTextView* text_view, gboolean select);

  
  static void SetAnchor(GtkTextView* text_view);

  
  static void ToggleCursorVisible(GtkTextView* text_view);

  
  static void ToggleOverwrite(GtkTextView* text_view);

  
  static gboolean ShowHelp(GtkWidget* widget, GtkWidgetHelpType arg1);

  
  static void MoveFocus(GtkWidget* widget, GtkDirectionType arg1);

  GtkWidget* fake_window_;

  libgtk2ui::OwnedWidgetGtk handler_;

  
  std::vector<ui::TextEditCommandAuraLinux> edit_commands_;

  
  bool has_xkb_;
};

}  

#endif  
