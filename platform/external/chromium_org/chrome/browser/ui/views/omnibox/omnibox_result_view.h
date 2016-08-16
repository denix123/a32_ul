// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_OMNIBOX_OMNIBOX_RESULT_VIEW_H_
#define CHROME_BROWSER_UI_VIEWS_OMNIBOX_OMNIBOX_RESULT_VIEW_H_

#include <vector>

#include "base/gtest_prod_util.h"
#include "components/omnibox/autocomplete_match.h"
#include "third_party/skia/include/core/SkColor.h"
#include "ui/gfx/animation/animation_delegate.h"
#include "ui/gfx/animation/slide_animation.h"
#include "ui/gfx/font_list.h"
#include "ui/gfx/rect.h"
#include "ui/views/controls/image_view.h"
#include "ui/views/view.h"

class LocationBarView;
class OmniboxPopupContentsView;

namespace gfx {
class Canvas;
class RenderText;
}

class OmniboxResultView : public views::View,
                          private gfx::AnimationDelegate {
 public:
  
  
  enum ResultViewState {
    NORMAL = 0,
    HOVERED,
    SELECTED,
    NUM_STATES
  };

  enum ColorKind {
    BACKGROUND = 0,
    TEXT,
    DIMMED_TEXT,
    URL,
    DIVIDER,
    NUM_KINDS
  };

  OmniboxResultView(OmniboxPopupContentsView* model,
                    int model_index,
                    LocationBarView* location_bar_view,
                    const gfx::FontList& font_list);
  virtual ~OmniboxResultView();

  SkColor GetColor(ResultViewState state, ColorKind kind) const;

  
  
  
  void SetMatch(const AutocompleteMatch& match);

  void ShowKeyword(bool show_keyword);

  void Invalidate();

  
  virtual gfx::Size GetPreferredSize() const OVERRIDE;

  ResultViewState GetState() const;

  
  
  virtual int GetTextHeight() const;

  
  int GetMatchContentsWidth() const;

 protected:
  
  
  virtual void PaintMatch(const AutocompleteMatch& match,
                          gfx::RenderText* contents,
                          gfx::RenderText* description,
                          gfx::Canvas* canvas,
                          int x) const;

  
  
  
  
  
  
  int DrawRenderText(const AutocompleteMatch& match,
                     gfx::RenderText* render_text,
                     bool contents,
                     gfx::Canvas* canvas,
                     int x,
                     int y,
                     int max_width) const;

  
  scoped_ptr<gfx::RenderText> CreateRenderText(
      const base::string16& text) const;

  
  
  scoped_ptr<gfx::RenderText> CreateClassifiedRenderText(
      const base::string16& text,
      const ACMatchClassifications& classifications,
      bool force_dim) const;

  const gfx::Rect& text_bounds() const { return text_bounds_; }

  void set_edge_item_padding(int value) { edge_item_padding_ = value; }
  void set_item_padding(int value) { item_padding_ = value; }
  void set_minimum_text_vertical_padding(int value) {
    minimum_text_vertical_padding_ = value;
  }

 private:
  gfx::ImageSkia GetIcon() const;
  const gfx::ImageSkia* GetKeywordIcon() const;

  
  
  
  bool ShowOnlyKeywordMatch() const;

  
  
  void ResetRenderTexts() const;

  
  void InitContentsRenderTextIfNecessary() const;

  
  virtual void Layout() OVERRIDE;
  virtual void OnBoundsChanged(const gfx::Rect& previous_bounds) OVERRIDE;
  virtual void OnPaint(gfx::Canvas* canvas) OVERRIDE;

  
  virtual void AnimationProgressed(const gfx::Animation* animation) OVERRIDE;

  
  
  
  int GetDisplayOffset(const AutocompleteMatch& match,
                       bool is_ui_rtl,
                       bool is_match_contents_rtl) const;

  static int default_icon_size_;

  
  int edge_item_padding_;
  int item_padding_;
  int minimum_text_vertical_padding_;

  
  OmniboxPopupContentsView* model_;
  size_t model_index_;

  LocationBarView* location_bar_view_;

  const gfx::FontList font_list_;
  int font_height_;

  
  class MirroringContext;
  scoped_ptr<MirroringContext> mirroring_context_;

  AutocompleteMatch match_;

  gfx::Rect text_bounds_;
  gfx::Rect icon_bounds_;

  gfx::Rect keyword_text_bounds_;
  scoped_ptr<views::ImageView> keyword_icon_;

  scoped_ptr<gfx::SlideAnimation> animation_;

  
  
  mutable scoped_ptr<gfx::RenderText> contents_rendertext_;
  mutable scoped_ptr<gfx::RenderText> description_rendertext_;
  mutable scoped_ptr<gfx::RenderText> separator_rendertext_;
  mutable scoped_ptr<gfx::RenderText> keyword_contents_rendertext_;
  mutable scoped_ptr<gfx::RenderText> keyword_description_rendertext_;

  mutable int separator_width_;

  DISALLOW_COPY_AND_ASSIGN(OmniboxResultView);
};

#endif  
