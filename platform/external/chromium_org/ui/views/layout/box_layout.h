// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_LAYOUT_BOX_LAYOUT_H_
#define UI_VIEWS_LAYOUT_BOX_LAYOUT_H_

#include <map>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "ui/gfx/insets.h"
#include "ui/views/layout/layout_manager.h"

namespace gfx {
class Rect;
class Size;
}

namespace views {

class View;

class VIEWS_EXPORT BoxLayout : public LayoutManager {
 public:
  enum Orientation {
    kHorizontal,
    kVertical,
  };

  
  
  
  enum MainAxisAlignment {
    MAIN_AXIS_ALIGNMENT_START,
    MAIN_AXIS_ALIGNMENT_CENTER,
    MAIN_AXIS_ALIGNMENT_END,
    
    
  };

  
  
  
  enum CrossAxisAlignment {
    
    CROSS_AXIS_ALIGNMENT_STRETCH,
    CROSS_AXIS_ALIGNMENT_START,
    CROSS_AXIS_ALIGNMENT_CENTER,
    CROSS_AXIS_ALIGNMENT_END,
  };

  
  
  
  
  BoxLayout(Orientation orientation,
            int inside_border_horizontal_spacing,
            int inside_border_vertical_spacing,
            int between_child_spacing);
  virtual ~BoxLayout();

  void set_main_axis_alignment(MainAxisAlignment main_axis_alignment) {
    main_axis_alignment_ = main_axis_alignment;
  }

  void set_cross_axis_alignment(CrossAxisAlignment cross_axis_alignment) {
    cross_axis_alignment_ = cross_axis_alignment;
  }

  void set_inside_border_insets(const gfx::Insets& insets) {
    inside_border_insets_ = insets;
  }

  void set_minimum_cross_axis_size(int size) {
    minimum_cross_axis_size_ = size;
  }

  
  
  
  
  
  
  
  void SetFlexForView(const View* view, int flex);

  
  
  void ClearFlexForView(const View* view);

  
  void SetDefaultFlex(int default_flex);

  
  virtual void Installed(View* host) OVERRIDE;
  virtual void Uninstalled(View* host) OVERRIDE;
  virtual void ViewRemoved(View* host, View* view) OVERRIDE;
  virtual void Layout(View* host) OVERRIDE;
  virtual gfx::Size GetPreferredSize(const View* host) const OVERRIDE;
  virtual int GetPreferredHeightForWidth(const View* host,
                                         int width) const OVERRIDE;

 private:
  
  int GetFlexForView(const View* view) const;

  
  int MainAxisSize(const gfx::Rect& rect) const;
  int MainAxisPosition(const gfx::Rect& rect) const;

  
  void SetMainAxisSize(int size, gfx::Rect* rect) const;
  void SetMainAxisPosition(int position, gfx::Rect* rect) const;

  
  int CrossAxisSize(const gfx::Rect& rect) const;
  int CrossAxisPosition(const gfx::Rect& rect) const;

  
  void SetCrossAxisSize(int size, gfx::Rect* rect) const;
  void SetCrossAxisPosition(int size, gfx::Rect* rect) const;

  
  
  int MainAxisSizeForView(const View* view, int child_area_width) const;

  
  int CrossAxisSizeForView(const View* view) const;

  
  gfx::Size GetPreferredSizeForChildWidth(const View* host,
                                          int child_area_width) const;

  
  
  gfx::Size NonChildSize(const View* host) const;

  const Orientation orientation_;

  
  gfx::Insets inside_border_insets_;

  
  const int between_child_spacing_;

  
  
  MainAxisAlignment main_axis_alignment_;

  
  
  CrossAxisAlignment cross_axis_alignment_;

  
  std::map<const View*, int> flex_map_;

  
  int default_flex_;

  
  int minimum_cross_axis_size_;

  
  views::View* host_;

  DISALLOW_IMPLICIT_CONSTRUCTORS(BoxLayout);
};

} 

#endif  
