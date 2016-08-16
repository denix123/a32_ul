// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_CONTROLS_LABEL_H_
#define UI_VIEWS_CONTROLS_LABEL_H_

#include <string>
#include <vector>

#include "base/compiler_specific.h"
#include "base/gtest_prod_util.h"
#include "base/strings/string16.h"
#include "third_party/skia/include/core/SkColor.h"
#include "ui/gfx/font_list.h"
#include "ui/gfx/shadow_value.h"
#include "ui/gfx/text_constants.h"
#include "ui/views/view.h"

namespace views {

class VIEWS_EXPORT Label : public View {
 public:
  
  static const char kViewClassName[];

  
  static const int kFocusBorderPadding;

  Label();
  explicit Label(const base::string16& text);
  Label(const base::string16& text, const gfx::FontList& font_list);
  virtual ~Label();

  
  const gfx::FontList& font_list() const { return font_list_; }
  virtual void SetFontList(const gfx::FontList& font_list);

  
  const base::string16& text() const { return text_; }
  virtual void SetText(const base::string16& text);

  
  
  
  
  void SetAutoColorReadabilityEnabled(bool enabled);

  
  
  virtual void SetEnabledColor(SkColor color);
  void SetDisabledColor(SkColor color);

  SkColor enabled_color() const { return actual_enabled_color_; }

  
  
  void SetBackgroundColor(SkColor color);
  SkColor background_color() const { return background_color_; }

  
  void SetShadows(const gfx::ShadowValues& shadows);
  const gfx::ShadowValues& shadows() const { return shadows_; }

  
  
  void SetSubpixelRenderingEnabled(bool subpixel_rendering_enabled);

  
  void SetHorizontalAlignment(gfx::HorizontalAlignment alignment);
  gfx::HorizontalAlignment GetHorizontalAlignment() const;

  
  
  
  int line_height() const { return line_height_; }
  void SetLineHeight(int height);

  
  bool multi_line() const { return multi_line_; }
  void SetMultiLine(bool multi_line);

  
  
  bool obscured() const { return obscured_; }
  void SetObscured(bool obscured);

  
  void SetAllowCharacterBreak(bool allow_character_break);

  
  
  void SetElideBehavior(gfx::ElideBehavior elide_behavior);

  
  
  
  
  void SetTooltipText(const base::string16& tooltip_text);

  
  
  
  
  
  
  void SizeToFit(int max_width);

  
  void set_collapse_when_hidden(bool value) { collapse_when_hidden_ = value; }

  
  const base::string16& GetLayoutTextForTesting() const;

  
  virtual gfx::Insets GetInsets() const OVERRIDE;
  virtual int GetBaseline() const OVERRIDE;
  virtual gfx::Size GetPreferredSize() const OVERRIDE;
  virtual gfx::Size GetMinimumSize() const OVERRIDE;
  virtual int GetHeightForWidth(int w) const OVERRIDE;
  virtual const char* GetClassName() const OVERRIDE;
  virtual View* GetTooltipHandlerForPoint(const gfx::Point& point) OVERRIDE;
  virtual bool CanProcessEventsWithinSubtree() const OVERRIDE;
  virtual void GetAccessibleState(ui::AXViewState* state) OVERRIDE;
  virtual bool GetTooltipText(const gfx::Point& p,
                              base::string16* tooltip) const OVERRIDE;

 protected:
  
  void PaintText(gfx::Canvas* canvas,
                 const base::string16& text,
                 const gfx::Rect& text_bounds,
                 int flags);

  virtual gfx::Size GetTextSize() const;

  SkColor disabled_color() const { return actual_disabled_color_; }

  
  virtual void OnBoundsChanged(const gfx::Rect& previous_bounds) OVERRIDE;
  virtual void OnPaint(gfx::Canvas* canvas) OVERRIDE;
  virtual void OnNativeThemeChanged(const ui::NativeTheme* theme) OVERRIDE;

 private:
  
  
  FRIEND_TEST_ALL_PREFIXES(LabelTest, DrawSingleLineString);
  FRIEND_TEST_ALL_PREFIXES(LabelTest, DrawMultiLineString);
  FRIEND_TEST_ALL_PREFIXES(LabelTest, DrawSingleLineStringInRTL);
  FRIEND_TEST_ALL_PREFIXES(LabelTest, DrawMultiLineStringInRTL);
  FRIEND_TEST_ALL_PREFIXES(LabelTest, DirectionalityFromText);
  FRIEND_TEST_ALL_PREFIXES(LabelTest, DisableSubpixelRendering);

  
  
  void SetTextInternal(const base::string16& text);

  void Init(const base::string16& text, const gfx::FontList& font_list);

  void RecalculateColors();

  
  gfx::Rect GetTextBounds() const;

  int ComputeDrawStringFlags() const;

  gfx::Rect GetAvailableRect() const;

  
  void CalculateDrawStringParams(base::string16* paint_text,
                                 gfx::Rect* text_bounds,
                                 int* flags) const;

  
  void UpdateColorsFromTheme(const ui::NativeTheme* theme);

  
  
  void ResetCachedSize();

  bool ShouldShowDefaultTooltip() const;

  base::string16 text_;
  base::string16 layout_text_;
  gfx::FontList font_list_;
  SkColor requested_enabled_color_;
  SkColor actual_enabled_color_;
  SkColor requested_disabled_color_;
  SkColor actual_disabled_color_;
  SkColor background_color_;

  
  bool enabled_color_set_;
  bool disabled_color_set_;
  bool background_color_set_;

  bool subpixel_rendering_enabled_;
  bool auto_color_readability_;
  mutable gfx::Size text_size_;
  mutable bool text_size_valid_;
  int line_height_;
  bool multi_line_;
  bool obscured_;
  bool allow_character_break_;
  gfx::ElideBehavior elide_behavior_;
  gfx::HorizontalAlignment horizontal_alignment_;
  base::string16 tooltip_text_;
  
  bool collapse_when_hidden_;
  gfx::ShadowValues shadows_;

  
  mutable std::vector<gfx::Size> cached_heights_;
  mutable int cached_heights_cursor_;

  DISALLOW_COPY_AND_ASSIGN(Label);
};

}  

#endif  
