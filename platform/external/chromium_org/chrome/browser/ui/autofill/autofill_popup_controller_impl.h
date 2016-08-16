// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_AUTOFILL_AUTOFILL_POPUP_CONTROLLER_IMPL_H_
#define CHROME_BROWSER_UI_AUTOFILL_AUTOFILL_POPUP_CONTROLLER_IMPL_H_

#include "base/gtest_prod_util.h"
#include "base/i18n/rtl.h"
#include "base/memory/weak_ptr.h"
#include "base/strings/string16.h"
#include "chrome/browser/ui/autofill/autofill_popup_controller.h"
#include "chrome/browser/ui/autofill/popup_controller_common.h"
#include "ui/gfx/font_list.h"
#include "ui/gfx/rect.h"
#include "ui/gfx/rect_f.h"

namespace autofill {

class AutofillPopupDelegate;
class AutofillPopupView;

class AutofillPopupControllerImpl : public AutofillPopupController {
 public:
  
  
  
  
  static base::WeakPtr<AutofillPopupControllerImpl> GetOrCreate(
      base::WeakPtr<AutofillPopupControllerImpl> previous,
      base::WeakPtr<AutofillPopupDelegate> delegate,
      content::WebContents* web_contents,
      gfx::NativeView container_view,
      const gfx::RectF& element_bounds,
      base::i18n::TextDirection text_direction);

  
  void Show(const std::vector<base::string16>& names,
            const std::vector<base::string16>& subtexts,
            const std::vector<base::string16>& icons,
            const std::vector<int>& identifiers);

  
  void UpdateDataListValues(const std::vector<base::string16>& values,
                            const std::vector<base::string16>& labels);

  
  
  virtual void Hide() OVERRIDE;

  
  virtual void ViewDestroyed() OVERRIDE;

  bool HandleKeyPressEvent(const content::NativeWebKeyboardEvent& event);

  
  void set_hide_on_outside_click(bool hide_on_outside_click);

 protected:
  FRIEND_TEST_ALL_PREFIXES(AutofillExternalDelegateBrowserTest,
                           CloseWidgetAndNoLeaking);
  FRIEND_TEST_ALL_PREFIXES(AutofillPopupControllerUnitTest,
                           ProperlyResetController);

  AutofillPopupControllerImpl(base::WeakPtr<AutofillPopupDelegate> delegate,
                              content::WebContents* web_contents,
                              gfx::NativeView container_view,
                              const gfx::RectF& element_bounds,
                              base::i18n::TextDirection text_direction);
  virtual ~AutofillPopupControllerImpl();

  
  virtual void UpdateBoundsAndRedrawPopup() OVERRIDE;
  virtual void SetSelectionAtPoint(const gfx::Point& point) OVERRIDE;
  virtual bool AcceptSelectedLine() OVERRIDE;
  virtual void SelectionCleared() OVERRIDE;
  virtual void AcceptSuggestion(size_t index) OVERRIDE;
  virtual int GetIconResourceID(
      const base::string16& resource_name) const OVERRIDE;
  virtual bool CanDelete(size_t index) const OVERRIDE;
  virtual bool IsWarning(size_t index) const OVERRIDE;
  virtual gfx::Rect GetRowBounds(size_t index) OVERRIDE;
  virtual void SetPopupBounds(const gfx::Rect& bounds) OVERRIDE;
  virtual const gfx::Rect& popup_bounds() const OVERRIDE;
  virtual gfx::NativeView container_view() OVERRIDE;
  virtual const gfx::RectF& element_bounds() const OVERRIDE;
  virtual bool IsRTL() const OVERRIDE;

  virtual const std::vector<base::string16>& names() const OVERRIDE;
  virtual const std::vector<base::string16>& subtexts() const OVERRIDE;
  virtual const std::vector<base::string16>& icons() const OVERRIDE;
  virtual const std::vector<int>& identifiers() const OVERRIDE;
#if !defined(OS_ANDROID)
  virtual const gfx::FontList& GetNameFontListForRow(
      size_t index) const OVERRIDE;
  virtual const gfx::FontList& subtext_font_list() const OVERRIDE;
#endif
  virtual int selected_line() const OVERRIDE;

  content::WebContents* web_contents();

  
  void SetSelectedLine(int selected_line);

  
  void SelectNextLine();

  
  void SelectPreviousLine();

  
  bool RemoveSelectedLine();

  
  int LineFromY(int y);

  
  int GetRowHeightFromId(int identifier) const;

  
  bool CanAccept(int id);

  
  bool HasSuggestions();

  
  
  void SetValues(const std::vector<base::string16>& names,
                 const std::vector<base::string16>& subtexts,
                 const std::vector<base::string16>& icons,
                 const std::vector<int>& identifier);

  AutofillPopupView* view() { return view_; }

  
  virtual void ShowView();
  virtual void InvalidateRow(size_t row);

  
#if !defined(OS_ANDROID)
  
  int GetDesiredPopupWidth() const;

  
  int GetDesiredPopupHeight() const;

  
  
  
  int RowWidthWithoutText(int row) const;
#endif

  base::WeakPtr<AutofillPopupControllerImpl> GetWeakPtr();

  
  
  scoped_ptr<PopupControllerCommon> controller_common_;

 private:
  
  
  void ClearState();

#if !defined(OS_ANDROID)
  
  
  void UpdatePopupBounds();
#endif

  AutofillPopupView* view_;  
  base::WeakPtr<AutofillPopupDelegate> delegate_;

  
  gfx::Rect popup_bounds_;

  
  base::i18n::TextDirection text_direction_;

  
  std::vector<base::string16> names_;
  std::vector<base::string16> subtexts_;
  std::vector<base::string16> icons_;
  std::vector<int> identifiers_;

  
  
  std::vector<base::string16> full_names_;

#if !defined(OS_ANDROID)
  
  gfx::FontList name_font_list_;
  gfx::FontList subtext_font_list_;
  gfx::FontList warning_font_list_;
#endif

  
  
  int selected_line_;

  base::WeakPtrFactory<AutofillPopupControllerImpl> weak_ptr_factory_;
};

}  

#endif  
