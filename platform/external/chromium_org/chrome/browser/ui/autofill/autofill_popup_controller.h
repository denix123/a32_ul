// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_AUTOFILL_AUTOFILL_POPUP_CONTROLLER_H_
#define CHROME_BROWSER_UI_AUTOFILL_AUTOFILL_POPUP_CONTROLLER_H_

#include <vector>

#include "base/compiler_specific.h"
#include "base/strings/string16.h"
#include "chrome/browser/ui/autofill/autofill_popup_view_delegate.h"

namespace gfx {
class FontList;
class Point;
class Rect;
class RectF;
}

namespace autofill {

class AutofillPopupController : public AutofillPopupViewDelegate {
 public:
  
  virtual void UpdateBoundsAndRedrawPopup() = 0;

  
  virtual void AcceptSuggestion(size_t index) = 0;

  
  
  virtual int GetIconResourceID(const base::string16& resource_name) const = 0;

  
  virtual bool CanDelete(size_t index) const = 0;

  
  
  virtual bool IsWarning(size_t index) const = 0;

  
  virtual void SetPopupBounds(const gfx::Rect& bounds) = 0;

  
  
  virtual gfx::Rect GetRowBounds(size_t index) = 0;

  
  virtual const gfx::RectF& element_bounds() const = 0;

  
  virtual bool IsRTL() const = 0;

  
  
  
  
  virtual const std::vector<base::string16>& names() const = 0;

  
  virtual const std::vector<base::string16>& subtexts() const = 0;

  
  virtual const std::vector<base::string16>& icons() const = 0;

  
  virtual const std::vector<int>& identifiers() const = 0;

#if !defined(OS_ANDROID)
  
  
  virtual const gfx::FontList& GetNameFontListForRow(size_t index) const = 0;
  virtual const gfx::FontList& subtext_font_list() const = 0;
#endif

  
  
  virtual int selected_line() const = 0;

 protected:
  virtual ~AutofillPopupController() {}
};

}  

#endif  
