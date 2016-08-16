// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_DISPLAY_TYPES_DISPLAY_SNAPSHOT_H_
#define UI_DISPLAY_TYPES_DISPLAY_SNAPSHOT_H_

#include <vector>

#include "ui/display/types/display_constants.h"
#include "ui/display/types/display_mode.h"
#include "ui/gfx/geometry/point.h"
#include "ui/gfx/geometry/size.h"

namespace ui {

class DISPLAY_TYPES_EXPORT DisplaySnapshot {
 public:
  DisplaySnapshot(int64_t display_id,
                  bool has_proper_display_id,
                  const gfx::Point& origin,
                  const gfx::Size& physical_size,
                  DisplayConnectionType type,
                  bool is_aspect_preserving_scaling,
                  bool has_overscan,
                  std::string display_name,
                  const std::vector<const DisplayMode*>& modes,
                  const DisplayMode* current_mode,
                  const DisplayMode* native_mode);
  virtual ~DisplaySnapshot();

  const gfx::Point& origin() const { return origin_; }
  const gfx::Size& physical_size() const { return physical_size_; }
  ui::DisplayConnectionType type() const { return type_; }
  bool is_aspect_preserving_scaling() const {
    return is_aspect_preserving_scaling_;
  }
  bool has_overscan() const { return has_overscan_; }
  std::string display_name() const { return display_name_; }

  int64_t display_id() const { return display_id_; }
  bool has_proper_display_id() const { return has_proper_display_id_; }

  const DisplayMode* current_mode() const { return current_mode_; }
  const DisplayMode* native_mode() const { return native_mode_; }

  const std::vector<const DisplayMode*>& modes() const { return modes_; }

  void set_current_mode(const DisplayMode* mode) { current_mode_ = mode; }
  void set_origin(const gfx::Point& origin) { origin_ = origin; }
  void add_mode(const DisplayMode* mode) { modes_.push_back(mode); }

  
  virtual std::string ToString() const = 0;

 protected:
  
  int64_t display_id_;
  bool has_proper_display_id_;

  
  gfx::Point origin_;

  gfx::Size physical_size_;

  DisplayConnectionType type_;

  bool is_aspect_preserving_scaling_;

  bool has_overscan_;

  std::string display_name_;

  std::vector<const DisplayMode*> modes_;  

  
  const DisplayMode* current_mode_;

  
  const DisplayMode* native_mode_;

  DISALLOW_COPY_AND_ASSIGN(DisplaySnapshot);
};

}  

#endif  
