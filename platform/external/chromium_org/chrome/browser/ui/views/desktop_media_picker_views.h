// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_DESKTOP_MEDIA_PICKER_VIEWS_H_
#define CHROME_BROWSER_UI_VIEWS_DESKTOP_MEDIA_PICKER_VIEWS_H_

#include "chrome/browser/media/desktop_media_list_observer.h"
#include "chrome/browser/media/desktop_media_picker.h"
#include "ui/views/window/dialog_delegate.h"

namespace views {
class ImageView;
class Label;
}  

class DesktopMediaPickerDialogView;
class DesktopMediaPickerViews;
class DesktopMediaSourceView;

class DesktopMediaListView : public views::View,
                             public DesktopMediaListObserver {
 public:
  DesktopMediaListView(DesktopMediaPickerDialogView* parent,
                       scoped_ptr<DesktopMediaList> media_list);
  virtual ~DesktopMediaListView();

  void StartUpdating(content::DesktopMediaID::Id dialog_window_id);

  
  void OnSelectionChanged();

  
  void OnDoubleClick();

  
  DesktopMediaSourceView* GetSelection();

  
  virtual gfx::Size GetPreferredSize() const OVERRIDE;
  virtual void Layout() OVERRIDE;
  virtual bool OnKeyPressed(const ui::KeyEvent& event) OVERRIDE;

 private:
  
  virtual void OnSourceAdded(int index) OVERRIDE;
  virtual void OnSourceRemoved(int index) OVERRIDE;
  virtual void OnSourceMoved(int old_index, int new_index) OVERRIDE;
  virtual void OnSourceNameChanged(int index) OVERRIDE;
  virtual void OnSourceThumbnailChanged(int index) OVERRIDE;

  
  void AcceptSelection();

  DesktopMediaPickerDialogView* parent_;
  scoped_ptr<DesktopMediaList> media_list_;
  base::WeakPtrFactory<DesktopMediaListView> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(DesktopMediaListView);
};

class DesktopMediaSourceView : public views::View {
 public:
  DesktopMediaSourceView(DesktopMediaListView* parent,
                         content::DesktopMediaID source_id);
  virtual ~DesktopMediaSourceView();

  
  void SetName(const base::string16& name);
  void SetThumbnail(const gfx::ImageSkia& thumbnail);

  
  const content::DesktopMediaID& source_id() const { return source_id_; }

  
  bool is_selected() const { return selected_; }

  
  virtual const char* GetClassName() const OVERRIDE;
  virtual void Layout() OVERRIDE;
  virtual views::View* GetSelectedViewForGroup(int group) OVERRIDE;
  virtual bool IsGroupFocusTraversable() const OVERRIDE;
  virtual void OnPaint(gfx::Canvas* canvas) OVERRIDE;
  virtual void OnFocus() OVERRIDE;
  virtual void OnBlur() OVERRIDE;
  virtual bool OnMousePressed(const ui::MouseEvent& event) OVERRIDE;
  virtual void OnGestureEvent(ui::GestureEvent* event) OVERRIDE;

 private:
  
  
  
  void SetSelected(bool selected);

  DesktopMediaListView* parent_;
  content::DesktopMediaID source_id_;

  views::ImageView* image_view_;
  views::Label* label_;

  bool selected_;

  DISALLOW_COPY_AND_ASSIGN(DesktopMediaSourceView);
};

class DesktopMediaPickerDialogView : public views::DialogDelegateView {
 public:
  DesktopMediaPickerDialogView(content::WebContents* parent_web_contents,
                               gfx::NativeWindow context,
                               DesktopMediaPickerViews* parent,
                               const base::string16& app_name,
                               const base::string16& target_name,
                               scoped_ptr<DesktopMediaList> media_list);
  virtual ~DesktopMediaPickerDialogView();

  
  void DetachParent();

  
  void OnSelectionChanged();
  void OnDoubleClick();

  
  virtual gfx::Size GetPreferredSize() const OVERRIDE;
  virtual void Layout() OVERRIDE;

  
  virtual ui::ModalType GetModalType() const OVERRIDE;
  virtual base::string16 GetWindowTitle() const OVERRIDE;
  virtual bool IsDialogButtonEnabled(ui::DialogButton button) const OVERRIDE;
  virtual base::string16 GetDialogButtonLabel(
      ui::DialogButton button) const OVERRIDE;
  virtual bool Accept() OVERRIDE;
  virtual void DeleteDelegate() OVERRIDE;

  void OnMediaListRowsChanged();

  DesktopMediaSourceView* GetMediaSourceViewForTesting(int index) const;

 private:
  DesktopMediaPickerViews* parent_;
  base::string16 app_name_;

  views::Label* label_;
  views::ScrollView* scroll_view_;
  DesktopMediaListView* list_view_;

  DISALLOW_COPY_AND_ASSIGN(DesktopMediaPickerDialogView);
};

class DesktopMediaPickerViews : public DesktopMediaPicker {
 public:
  DesktopMediaPickerViews();
  virtual ~DesktopMediaPickerViews();

  void NotifyDialogResult(content::DesktopMediaID source);

  
  virtual void Show(content::WebContents* web_contents,
                    gfx::NativeWindow context,
                    gfx::NativeWindow parent,
                    const base::string16& app_name,
                    const base::string16& target_name,
                    scoped_ptr<DesktopMediaList> media_list,
                    const DoneCallback& done_callback) OVERRIDE;

  DesktopMediaPickerDialogView* GetDialogViewForTesting() const {
    return dialog_;
  }

 private:
  DoneCallback callback_;

  
  
  
  DesktopMediaPickerDialogView* dialog_;

  DISALLOW_COPY_AND_ASSIGN(DesktopMediaPickerViews);
};

#endif  
