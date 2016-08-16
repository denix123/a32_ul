// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_BASE_IME_CANDIDATE_WINDOW_H_
#define UI_BASE_IME_CANDIDATE_WINDOW_H_

#include <string>
#include <vector>
#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "ui/base/ime/infolist_entry.h"
#include "ui/base/ui_base_export.h"

namespace ui {

class UI_BASE_EXPORT CandidateWindow {
 public:
  enum Orientation {
    HORIZONTAL = 0,
    VERTICAL = 1,
  };

  struct UI_BASE_EXPORT CandidateWindowProperty {
    CandidateWindowProperty();
    virtual ~CandidateWindowProperty();
    int page_size;
    int cursor_position;
    bool is_cursor_visible;
    bool is_vertical;
    bool show_window_at_composition;

    
    
    std::string auxiliary_text;
    bool is_auxiliary_text_visible;
  };

  
  struct UI_BASE_EXPORT Entry {
    Entry();
    virtual ~Entry();
    base::string16 value;
    base::string16 label;
    base::string16 annotation;
    base::string16 description_title;
    base::string16 description_body;
  };

  CandidateWindow();
  virtual ~CandidateWindow();

  
  bool IsEqual(const CandidateWindow& candidate_window) const;

  
  void CopyFrom(const CandidateWindow& candidate_window);

  const CandidateWindowProperty& GetProperty() const {
    return *property_;
  }
  void SetProperty(const CandidateWindowProperty& property) {
    *property_ = property;
  }

  
  
  void GetInfolistEntries(std::vector<InfolistEntry>* entries,
                          bool* has_highlighted) const;

  
  uint32 page_size() const { return property_->page_size; }
  void set_page_size(uint32 page_size) { property_->page_size = page_size; }

  
  uint32 cursor_position() const { return property_->cursor_position; }
  void set_cursor_position(uint32 cursor_position) {
    property_->cursor_position = cursor_position;
  }

  
  bool is_cursor_visible() const { return property_->is_cursor_visible; }
  void set_is_cursor_visible(bool is_cursor_visible) {
    property_->is_cursor_visible = is_cursor_visible;
  }

  
  Orientation orientation() const {
    return property_->is_vertical ? VERTICAL : HORIZONTAL;
  }
  void set_orientation(Orientation orientation) {
    property_->is_vertical = (orientation == VERTICAL);
  }

  
  bool is_auxiliary_text_visible() const {
    return property_->is_auxiliary_text_visible;
  }
  void set_is_auxiliary_text_visible(bool is_auxiliary_text_visible) const {
    property_->is_auxiliary_text_visible = is_auxiliary_text_visible;
  }

  
  const std::string& auxiliary_text() const {
    return property_->auxiliary_text;
  }
  void set_auxiliary_text(const std::string& auxiliary_text) const {
    property_->auxiliary_text = auxiliary_text;
  }

  const std::vector<Entry>& candidates() const { return candidates_; }
  std::vector<Entry>* mutable_candidates() { return &candidates_; }

  bool show_window_at_composition() const {
    return property_->show_window_at_composition;
  }
  void set_show_window_at_composition(bool show_window_at_composition) {
    property_->show_window_at_composition = show_window_at_composition;
  }

 private:
  scoped_ptr<CandidateWindowProperty> property_;
  std::vector<Entry> candidates_;

  DISALLOW_COPY_AND_ASSIGN(CandidateWindow);
};

}  

#endif  
