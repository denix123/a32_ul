// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_LIBGTK2UI_GTK2_UI_H_
#define CHROME_BROWSER_UI_LIBGTK2UI_GTK2_UI_H_

#include <map>
#include <vector>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "base/observer_list.h"
#include "chrome/browser/ui/libgtk2ui/gtk2_signal.h"
#include "chrome/browser/ui/libgtk2ui/gtk2_signal_registrar.h"
#include "chrome/browser/ui/libgtk2ui/libgtk2ui_export.h"
#include "chrome/browser/ui/libgtk2ui/owned_widget_gtk2.h"
#include "ui/events/linux/text_edit_key_bindings_delegate_auralinux.h"
#include "ui/gfx/color_utils.h"
#include "ui/views/linux_ui/linux_ui.h"
#include "ui/views/window/frame_buttons.h"

typedef struct _GdkColor GdkColor;
typedef struct _GtkBorder GtkBorder;
typedef struct _GtkStyle GtkStyle;
typedef struct _GtkWidget GtkWidget;

class SkBitmap;

namespace gfx {
class Image;
class ScopedPangoFontDescription;
}

namespace libgtk2ui {
class Gtk2Border;
class Gtk2KeyBindingsHandler;
class Gtk2SignalRegistrar;
class GConfListener;

class Gtk2UI : public views::LinuxUI {
 public:
  Gtk2UI();
  virtual ~Gtk2UI();

  typedef base::Callback<ui::NativeTheme*(aura::Window* window)>
      NativeThemeGetter;

  
  void SetWindowButtonOrdering(
      const std::vector<views::FrameButton>& leading_buttons,
      const std::vector<views::FrameButton>& trailing_buttons);
  void SetNonClientMiddleClickAction(NonClientMiddleClickAction action);

  
  SkBitmap DrawGtkButtonBorder(int gtk_state,
                               bool focused,
                               bool call_to_action,
                               int width,
                               int height) const;

  
  virtual scoped_ptr<ui::LinuxInputMethodContext> CreateInputMethodContext(
      ui::LinuxInputMethodContextDelegate* delegate) const OVERRIDE;

  
  virtual gfx::FontRenderParams GetDefaultFontRenderParams() const OVERRIDE;
  virtual scoped_ptr<gfx::ScopedPangoFontDescription>
      GetDefaultPangoFontDescription() const OVERRIDE;
  virtual double GetFontDPI() const OVERRIDE;

  
  virtual ui::SelectFileDialog* CreateSelectFileDialog(
      ui::SelectFileDialog::Listener* listener,
      ui::SelectFilePolicy* policy) const OVERRIDE;

  
  virtual void Initialize() OVERRIDE;
  virtual gfx::Image GetThemeImageNamed(int id) const OVERRIDE;
  virtual bool GetColor(int id, SkColor* color) const OVERRIDE;
  virtual bool HasCustomImage(int id) const OVERRIDE;
  virtual SkColor GetFocusRingColor() const OVERRIDE;
  virtual SkColor GetThumbActiveColor() const OVERRIDE;
  virtual SkColor GetThumbInactiveColor() const OVERRIDE;
  virtual SkColor GetTrackColor() const OVERRIDE;
  virtual SkColor GetActiveSelectionBgColor() const OVERRIDE;
  virtual SkColor GetActiveSelectionFgColor() const OVERRIDE;
  virtual SkColor GetInactiveSelectionBgColor() const OVERRIDE;
  virtual SkColor GetInactiveSelectionFgColor() const OVERRIDE;
  virtual double GetCursorBlinkInterval() const OVERRIDE;
  virtual ui::NativeTheme* GetNativeTheme(aura::Window* window) const OVERRIDE;
  virtual void SetNativeThemeOverride(const NativeThemeGetter& callback)
      OVERRIDE;
  virtual bool GetDefaultUsesSystemTheme() const OVERRIDE;
  virtual void SetDownloadCount(int count) const OVERRIDE;
  virtual void SetProgressFraction(float percentage) const OVERRIDE;
  virtual bool IsStatusIconSupported() const OVERRIDE;
  virtual scoped_ptr<views::StatusIconLinux> CreateLinuxStatusIcon(
      const gfx::ImageSkia& image,
      const base::string16& tool_tip) const OVERRIDE;
  virtual gfx::Image GetIconForContentType(
      const std::string& content_type, int size) const OVERRIDE;
  virtual scoped_ptr<views::Border> CreateNativeBorder(
      views::LabelButton* owning_button,
      scoped_ptr<views::LabelButtonBorder> border) OVERRIDE;
  virtual void AddWindowButtonOrderObserver(
      views::WindowButtonOrderObserver* observer) OVERRIDE;
  virtual void RemoveWindowButtonOrderObserver(
      views::WindowButtonOrderObserver* observer) OVERRIDE;
  virtual bool UnityIsRunning() OVERRIDE;
  virtual NonClientMiddleClickAction GetNonClientMiddleClickAction() OVERRIDE;
  virtual void NotifyWindowManagerStartupComplete() OVERRIDE;

  
  virtual bool MatchEvent(
      const ui::Event& event,
      std::vector<ui::TextEditCommandAuraLinux>* commands) OVERRIDE;

 private:
  typedef std::map<int, SkColor> ColorMap;
  typedef std::map<int, color_utils::HSL> TintMap;
  typedef std::map<int, gfx::Image> ImageCache;

  
  
  
  void GetScrollbarColors(GdkColor* thumb_active_color,
                          GdkColor* thumb_inactive_color,
                          GdkColor* track_color);

  
  
  void LoadGtkValues();

  
  
  GdkColor BuildFrameColors(GtkStyle* frame_style);

  
  void SetThemeColorFromGtk(int id, const GdkColor* color);
  void SetThemeTintFromGtk(int id, const GdkColor* color);

  
  
  
  GdkColor BuildAndSetFrameColor(const GdkColor* base,
                                 const GdkColor* gtk_base,
                                 const color_utils::HSL& tint,
                                 int color_id,
                                 int tint_id);

  
  SkBitmap GenerateGtkThemeBitmap(int id) const;

  
  
  
  
  SkBitmap GenerateFrameImage(int color_id,
                              const char* gradient_name) const;

  
  SkBitmap GenerateTabImage(int base_id) const;

  
  SkBitmap GenerateTintedIcon(int base_id,
                              const color_utils::HSL& tint) const;

  
  
  SkBitmap GenerateGTKIcon(int base_id) const;

  
  
  SkBitmap GenerateToolbarBezel(int gtk_state, int sizing_idr) const;

  
  
  void GetNormalButtonTintHSL(color_utils::HSL* tint) const;

  
  void GetNormalEntryForegroundHSL(color_utils::HSL* tint) const;

  
  
  void GetSelectedEntryForegroundHSL(color_utils::HSL* tint) const;

  
  SkColor CallToActionBgColor(int gtk_state) const;

  
  void ClearAllThemeData();

  
  CHROMEGTK_CALLBACK_1(Gtk2UI, void, OnStyleSet, GtkStyle*);

  GtkWidget* fake_window_;
  GtkWidget* fake_frame_;
  OwnedWidgetGtk fake_label_;
  OwnedWidgetGtk fake_entry_;

  
  scoped_ptr<Gtk2SignalRegistrar> signals_;

  
  
  ColorMap colors_;
  TintMap tints_;

  
  color_utils::HSL button_tint_;
  color_utils::HSL entry_tint_;
  color_utils::HSL selected_entry_tint_;

  
  
  SkColor focus_ring_color_;
  SkColor thumb_active_color_;
  SkColor thumb_inactive_color_;
  SkColor track_color_;
  SkColor active_selection_bg_color_;
  SkColor active_selection_fg_color_;
  SkColor inactive_selection_bg_color_;
  SkColor inactive_selection_fg_color_;

  
  scoped_ptr<gfx::ScopedPangoFontDescription> default_font_description_;

#if defined(USE_GCONF)
  
  
  scoped_ptr<GConfListener> gconf_listener_;
#endif  

  
  
  std::vector<views::FrameButton> leading_buttons_;
  std::vector<views::FrameButton> trailing_buttons_;

  scoped_ptr<Gtk2KeyBindingsHandler> key_bindings_handler_;

  
  ObserverList<views::WindowButtonOrderObserver> observer_list_;

  
  
  NonClientMiddleClickAction middle_click_action_;

  
  mutable ImageCache gtk_images_;

  
  
  
  NativeThemeGetter native_theme_overrider_;

  DISALLOW_COPY_AND_ASSIGN(Gtk2UI);
};

}  

LIBGTK2UI_EXPORT views::LinuxUI* BuildGtk2UI();

#endif  
