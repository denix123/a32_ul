// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_AUTOFILL_AUTOFILL_DIALOG_VIEWS_H_
#define CHROME_BROWSER_UI_VIEWS_AUTOFILL_AUTOFILL_DIALOG_VIEWS_H_

#include <map>
#include <set>

#include "base/memory/scoped_vector.h"
#include "base/memory/weak_ptr.h"
#include "base/scoped_observer.h"
#include "chrome/browser/ui/autofill/autofill_dialog_types.h"
#include "chrome/browser/ui/autofill/autofill_dialog_view.h"
#include "chrome/browser/ui/autofill/autofill_dialog_view_delegate.h"
#include "ui/views/controls/button/button.h"
#include "ui/views/controls/button/menu_button.h"
#include "ui/views/controls/button/menu_button_listener.h"
#include "ui/views/controls/combobox/combobox_listener.h"
#include "ui/views/controls/link_listener.h"
#include "ui/views/controls/progress_bar.h"
#include "ui/views/controls/scroll_view.h"
#include "ui/views/controls/styled_label_listener.h"
#include "ui/views/controls/textfield/textfield_controller.h"
#include "ui/views/focus/focus_manager.h"
#include "ui/views/view_targeter_delegate.h"
#include "ui/views/widget/widget_observer.h"
#include "ui/views/window/dialog_delegate.h"

namespace gfx {
class Image;
}

namespace views {
class BubbleBorder;
class Checkbox;
class Combobox;
class FocusManager;
class ImageView;
class Label;
class LabelButton;
class Link;
class MenuRunner;
class StyledLabel;
class WebView;
class Widget;
}  

namespace ui {
class ComboboxModel;
class EventHandler;
class KeyEvent;
}

namespace autofill {

class AutofillDialogSignInDelegate;
class ExpandingTextfield;
class InfoBubble;

class AutofillDialogViews : public AutofillDialogView,
                            public views::DialogDelegateView,
                            public views::WidgetObserver,
                            public views::TextfieldController,
                            public views::FocusChangeListener,
                            public views::ComboboxListener,
                            public views::StyledLabelListener,
                            public views::MenuButtonListener {
 public:
  explicit AutofillDialogViews(AutofillDialogViewDelegate* delegate);
  virtual ~AutofillDialogViews();

  
  virtual void Show() OVERRIDE;
  virtual void Hide() OVERRIDE;
  virtual void UpdatesStarted() OVERRIDE;
  virtual void UpdatesFinished() OVERRIDE;
  virtual void UpdateAccountChooser() OVERRIDE;
  virtual void UpdateButtonStrip() OVERRIDE;
  virtual void UpdateOverlay() OVERRIDE;
  virtual void UpdateDetailArea() OVERRIDE;
  virtual void UpdateForErrors() OVERRIDE;
  virtual void UpdateNotificationArea() OVERRIDE;
  virtual void UpdateSection(DialogSection section) OVERRIDE;
  virtual void UpdateErrorBubble() OVERRIDE;
  virtual void FillSection(DialogSection section,
                           ServerFieldType originating_type) OVERRIDE;
  virtual void GetUserInput(DialogSection section,
                            FieldValueMap* output) OVERRIDE;
  virtual base::string16 GetCvc() OVERRIDE;
  virtual bool SaveDetailsLocally() OVERRIDE;
  virtual const content::NavigationController* ShowSignIn() OVERRIDE;
  virtual void HideSignIn() OVERRIDE;
  virtual void ModelChanged() OVERRIDE;
  virtual void OnSignInResize(const gfx::Size& pref_size) OVERRIDE;
  virtual void ValidateSection(DialogSection section) OVERRIDE;

  
  virtual gfx::Size GetPreferredSize() const OVERRIDE;
  virtual gfx::Size GetMinimumSize() const OVERRIDE;
  virtual void Layout() OVERRIDE;
  virtual void OnNativeThemeChanged(const ui::NativeTheme* theme) OVERRIDE;

  
  virtual ui::ModalType GetModalType() const OVERRIDE;
  virtual base::string16 GetWindowTitle() const OVERRIDE;
  virtual void WindowClosing() OVERRIDE;
  virtual void DeleteDelegate() OVERRIDE;
  virtual views::View* CreateOverlayView() OVERRIDE;
  virtual int GetDialogButtons() const OVERRIDE;
  virtual int GetDefaultDialogButton() const OVERRIDE;
  virtual base::string16 GetDialogButtonLabel(ui::DialogButton button) const
      OVERRIDE;
  virtual bool ShouldDefaultButtonBeBlue() const OVERRIDE;
  virtual bool IsDialogButtonEnabled(ui::DialogButton button) const OVERRIDE;
  virtual views::View* GetInitiallyFocusedView() OVERRIDE;
  virtual views::View* CreateExtraView() OVERRIDE;
  virtual views::View* CreateTitlebarExtraView() OVERRIDE;
  virtual views::View* CreateFootnoteView() OVERRIDE;
  virtual bool Cancel() OVERRIDE;
  virtual bool Accept() OVERRIDE;

  
  virtual void OnWidgetClosing(views::Widget* widget) OVERRIDE;
  virtual void OnWidgetDestroying(views::Widget* widget) OVERRIDE;
  virtual void OnWidgetBoundsChanged(views::Widget* widget,
                                     const gfx::Rect& new_bounds) OVERRIDE;

  
  virtual void ContentsChanged(views::Textfield* sender,
                               const base::string16& new_contents) OVERRIDE;
  virtual bool HandleKeyEvent(views::Textfield* sender,
                              const ui::KeyEvent& key_event) OVERRIDE;
  virtual bool HandleMouseEvent(views::Textfield* sender,
                                const ui::MouseEvent& key_event) OVERRIDE;

  
  virtual void OnWillChangeFocus(views::View* focused_before,
                                 views::View* focused_now) OVERRIDE;
  virtual void OnDidChangeFocus(views::View* focused_before,
                                views::View* focused_now) OVERRIDE;

  
  virtual void OnPerformAction(views::Combobox* combobox) OVERRIDE;

  
  virtual void StyledLabelLinkClicked(const gfx::Range& range, int event_flags)
      OVERRIDE;

  
  virtual void OnMenuButtonClicked(views::View* source,
                                   const gfx::Point& point) OVERRIDE;

 protected:
  
  views::View* GetLoadingShieldForTesting();
  views::WebView* GetSignInWebViewForTesting();
  views::View* GetNotificationAreaForTesting();
  views::View* GetScrollableAreaForTesting();

 private:
  friend class AutofillDialogViewTesterViews;

  
  
  enum DialogMode {
    DETAIL_INPUT,
    LOADING,
    SIGN_IN,
  };

  
  
  class AccountChooser : public views::View,
                         public views::LinkListener,
                         public views::MenuButtonListener,
                         public base::SupportsWeakPtr<AccountChooser> {
   public:
    explicit AccountChooser(AutofillDialogViewDelegate* delegate);
    virtual ~AccountChooser();

    
    void Update();

    
    virtual void LinkClicked(views::Link* source, int event_flags) OVERRIDE;

    
    virtual void OnMenuButtonClicked(views::View* source,
                                     const gfx::Point& point) OVERRIDE;

   private:
    
    views::ImageView* image_;

    
    views::MenuButton* menu_button_;

    
    views::Link* link_;

    
    AutofillDialogViewDelegate* delegate_;

    
    scoped_ptr<views::MenuRunner> menu_runner_;

    DISALLOW_COPY_AND_ASSIGN(AccountChooser);
  };

  
  
  class OverlayView : public views::View {
   public:
    explicit OverlayView(AutofillDialogViewDelegate* delegate);
    virtual ~OverlayView();

    
    
    
    int GetHeightForContentsForWidth(int width);

    
    void UpdateState();

    
    virtual gfx::Insets GetInsets() const OVERRIDE;
    virtual void Layout() OVERRIDE;
    virtual const char* GetClassName() const OVERRIDE;
    virtual void OnPaint(gfx::Canvas* canvas) OVERRIDE;
    virtual void OnNativeThemeChanged(const ui::NativeTheme* theme) OVERRIDE;

   private:
    
    views::BubbleBorder* GetBubbleBorder();

    
    gfx::Rect ContentBoundsSansBubbleBorder();

    
    AutofillDialogViewDelegate* delegate_;

    
    views::ImageView* image_view_;
    
    views::Label* message_view_;

    DISALLOW_COPY_AND_ASSIGN(OverlayView);
  };

  
  class NotificationArea : public views::View {
   public:
    explicit NotificationArea(AutofillDialogViewDelegate* delegate);
    virtual ~NotificationArea();

    
    void SetNotifications(const std::vector<DialogNotification>& notifications);

    
    virtual gfx::Size GetPreferredSize() const OVERRIDE;
    virtual const char* GetClassName() const OVERRIDE;
    virtual void PaintChildren(gfx::Canvas* canvas,
                               const views::CullSet& cull_set) OVERRIDE;
    virtual void OnPaint(gfx::Canvas* canvas) OVERRIDE;

    void set_arrow_centering_anchor(
        const base::WeakPtr<views::View>& arrow_centering_anchor) {
      arrow_centering_anchor_ = arrow_centering_anchor;
    }

   private:
    
    
    bool HasArrow();

    
    
    AutofillDialogViewDelegate* delegate_;  

    
    base::WeakPtr<views::View> arrow_centering_anchor_;

    std::vector<DialogNotification> notifications_;

    DISALLOW_COPY_AND_ASSIGN(NotificationArea);
  };

  typedef std::map<ServerFieldType, ExpandingTextfield*> TextfieldMap;
  typedef std::map<ServerFieldType, views::Combobox*> ComboboxMap;

  
  
  class SectionContainer : public views::View,
                           public views::ViewTargeterDelegate {
   public:
    SectionContainer(const base::string16& label,
                     views::View* controls,
                     views::Button* proxy_button);
    virtual ~SectionContainer();

    
    
    void SetActive(bool active);

    
    void SetForwardMouseEvents(bool forward);

    
    virtual const char* GetClassName() const OVERRIDE;
    virtual void OnMouseMoved(const ui::MouseEvent& event) OVERRIDE;
    virtual void OnMouseEntered(const ui::MouseEvent& event) OVERRIDE;
    virtual void OnMouseExited(const ui::MouseEvent& event) OVERRIDE;
    virtual bool OnMousePressed(const ui::MouseEvent& event) OVERRIDE;
    virtual void OnMouseReleased(const ui::MouseEvent& event) OVERRIDE;
    virtual void OnGestureEvent(ui::GestureEvent* event) OVERRIDE;

   private:
    
    virtual views::View* TargetForRect(views::View* root,
                                       const gfx::Rect& rect) OVERRIDE;

    
    static ui::MouseEvent ProxyEvent(const ui::MouseEvent& event);

    
    bool ShouldForwardEvent(const ui::LocatedEvent& event);

    
    views::Button* proxy_button_;  

    
    bool forward_mouse_events_;

    DISALLOW_COPY_AND_ASSIGN(SectionContainer);
  };

  
  class SuggestedButton : public views::MenuButton {
   public:
    explicit SuggestedButton(views::MenuButtonListener* listener);
    virtual ~SuggestedButton();

    
    virtual gfx::Size GetPreferredSize() const OVERRIDE;
    virtual const char* GetClassName() const OVERRIDE;
    virtual void PaintChildren(gfx::Canvas* canvas,
                               const views::CullSet& cull_set) OVERRIDE;
    virtual void OnPaint(gfx::Canvas* canvas) OVERRIDE;

   private:
    
    int ResourceIDForState() const;

    DISALLOW_COPY_AND_ASSIGN(SuggestedButton);
  };

  
  
  class DetailsContainerView : public views::View {
   public:
    explicit DetailsContainerView(const base::Closure& callback);
    virtual ~DetailsContainerView();

    void set_ignore_layouts(bool ignore_layouts) {
      ignore_layouts_ = ignore_layouts;
    }

    
    virtual void OnBoundsChanged(const gfx::Rect& previous_bounds) OVERRIDE;
    virtual void Layout() OVERRIDE;

   private:
    base::Closure bounds_changed_callback_;

    
    bool ignore_layouts_;

    DISALLOW_COPY_AND_ASSIGN(DetailsContainerView);
  };

  
  class SuggestionView : public views::View {
   public:
    explicit SuggestionView(AutofillDialogViews* autofill_dialog);
    virtual ~SuggestionView();

    void SetState(const SuggestionState& state);

    
    virtual gfx::Size GetPreferredSize() const OVERRIDE;
    virtual int GetHeightForWidth(int width) const OVERRIDE;
    virtual void OnBoundsChanged(const gfx::Rect& previous_bounds) OVERRIDE;

    ExpandingTextfield* textfield() { return textfield_; }

   private:
    
    
    
    
    
    bool CanUseVerticallyCompactText(int available_width,
                                     int* resulting_height) const;

    
    void SetLabelText(const base::string16& text);

    
    void SetIcon(const gfx::Image& image);

    
    
    void SetTextfield(const base::string16& placeholder_text,
                      const gfx::Image& icon);

    
    void UpdateLabelText();

    
    SuggestionState state_;

    
    
    mutable std::map<int, std::pair<bool, int> > calculated_heights_;

    
    views::Label* label_;
    
    views::Label* label_line_2_;
    
    views::ImageView* icon_;
    
    ExpandingTextfield* textfield_;

    DISALLOW_COPY_AND_ASSIGN(SuggestionView);
  };

  
  
  struct DetailsGroup {
    explicit DetailsGroup(DialogSection section);
    ~DetailsGroup();

    
    const DialogSection section;
    
    SectionContainer* container;
    
    views::View* manual_input;
    
    TextfieldMap textfields;
    
    ComboboxMap comboboxes;
    
    
    SuggestionView* suggested_info;
    
    SuggestedButton* suggested_button;
  };

  typedef std::map<DialogSection, DetailsGroup> DetailGroupMap;

  
  gfx::Size CalculatePreferredSize(bool get_minimum_size) const;

  
  gfx::Size GetMinimumSignInViewSize() const;

  
  gfx::Size GetMaximumSignInViewSize() const;

  
  DialogSection GetCreditCardSection() const;

  void InitChildViews();

  
  views::View* CreateDetailsContainer();

  
  views::View* CreateNotificationArea();

  
  views::View* CreateMainContainer();

  
  
  void CreateDetailsSection(DialogSection section);

  
  
  views::View* CreateInputsContainer(DialogSection section);

  
  void InitInputsView(DialogSection section);

  
  
  
  void ShowDialogInMode(DialogMode dialog_mode);

  
  
  
  void UpdateSectionImpl(DialogSection section, bool clobber_inputs);

  
  void UpdateDetailsGroupState(const DetailsGroup& group);

  
  
  DetailsGroup* GroupForSection(DialogSection section);

  
  
  DetailsGroup* GroupForView(views::View* view);

  
  void EraseInvalidViewsInGroup(const DetailsGroup* group);

  
  void FocusInitialView();

  
  
  
  template<class T>
  void SetValidityForInput(T* input, const base::string16& message);

  
  
  void ShowErrorBubbleForViewIfNecessary(views::View* view);

  
  void HideErrorBubble();

  
  
  void MarkInputsInvalid(DialogSection section,
                         const ValidityMessages& validity_messages,
                         bool overwrite_invalid);

  
  
  bool ValidateGroup(const DetailsGroup& group, ValidationType type);

  
  
  bool ValidateForm();

  
  
  
  
  void InputEditedOrActivated(ServerFieldType type,
                              const gfx::Rect& bounds,
                              bool was_edit);

  
  void UpdateButtonStripExtraView();

  
  void ContentsPreferredSizeChanged();
  void DoContentsPreferredSizeChanged();

  
  ExpandingTextfield* TextfieldForType(ServerFieldType type);

  
  ServerFieldType TypeForTextfield(const views::View* textfield);

  
  views::Combobox* ComboboxForType(ServerFieldType type);

  
  ServerFieldType TypeForCombobox(const views::Combobox* combobox) const;

  
  void DetailsContainerBoundsChanged();

  
  
  void SetIconsForSection(DialogSection section);

  
  
  void SetEditabilityForSection(DialogSection section);

  
  void NonClientMousePressed();

  
  AutofillDialogViewDelegate* const delegate_;

  
  mutable gfx::Size preferred_size_;

  
  int updates_scope_;

  
  
  bool needs_update_;

  
  
  views::Widget* window_;

  
  DetailGroupMap detail_groups_;

  
  NotificationArea* notification_area_;

  
  scoped_ptr<views::MenuRunner> menu_runner_;

  
  AccountChooser* account_chooser_;

  
  
  views::WebView* sign_in_web_view_;

  
  views::ScrollView* scrollable_area_;

  
  DetailsContainerView* details_container_;

  
  views::View* loading_shield_;

  
  
  int loading_shield_height_;

  
  OverlayView* overlay_view_;

  
  views::View* button_strip_extra_view_;

  
  
  views::Checkbox* save_in_chrome_checkbox_;

  
  views::View* save_in_chrome_checkbox_container_;

  
  views::ImageView* button_strip_image_;

  
  
  ScopedVector<views::View> other_owned_views_;

  
  
  views::View* footnote_view_;

  
  views::StyledLabel* legal_document_view_;

  
  views::FocusManager* focus_manager_;

  
  InfoBubble* error_bubble_;  

  
  std::map<views::View*, base::string16> validity_map_;

  ScopedObserver<views::Widget, AutofillDialogViews> observer_;

  
  scoped_ptr<AutofillDialogSignInDelegate> sign_in_delegate_;

  
  scoped_ptr<ui::EventHandler> event_handler_;

  DISALLOW_COPY_AND_ASSIGN(AutofillDialogViews);
};

}  

#endif  
