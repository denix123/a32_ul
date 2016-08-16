// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_LOCATION_BAR_LOCATION_BAR_VIEW_H_
#define CHROME_BROWSER_UI_VIEWS_LOCATION_BAR_LOCATION_BAR_VIEW_H_

#include <string>
#include <vector>

#include "base/compiler_specific.h"
#include "base/prefs/pref_member.h"
#include "chrome/browser/extensions/extension_context_menu_model.h"
#include "chrome/browser/ui/location_bar/location_bar.h"
#include "chrome/browser/ui/omnibox/omnibox_edit_controller.h"
#include "chrome/browser/ui/search/search_model_observer.h"
#include "chrome/browser/ui/toolbar/toolbar_model.h"
#include "chrome/browser/ui/views/dropdown_bar_host.h"
#include "chrome/browser/ui/views/dropdown_bar_host_delegate.h"
#include "chrome/browser/ui/views/extensions/extension_popup.h"
#include "chrome/browser/ui/views/omnibox/omnibox_view_views.h"
#include "components/search_engines/template_url_service_observer.h"
#include "ui/gfx/animation/animation_delegate.h"
#include "ui/gfx/font.h"
#include "ui/gfx/rect.h"
#include "ui/views/controls/button/button.h"
#include "ui/views/drag_controller.h"

class ActionBoxButtonView;
class CommandUpdater;
class ContentSettingBubbleModelDelegate;
class ContentSettingImageView;
class EVBubbleView;
class ExtensionAction;
class GURL;
class GeneratedCreditCardView;
class InstantController;
class KeywordHintView;
class LocationIconView;
class OpenPDFInReaderView;
class ManagePasswordsIconView;
class OriginChipView;
class PageActionWithBadgeView;
class PageActionImageView;
class Profile;
class SearchButton;
class SelectedKeywordView;
class StarView;
class TemplateURLService;
class TranslateIconView;
class ZoomView;

namespace content {
struct SSLStatus;
}

namespace gfx {
class SlideAnimation;
}

namespace views {
class BubbleDelegateView;
class ImageButton;
class ImageView;
class Label;
class Widget;
}

class LocationBarView : public LocationBar,
                        public LocationBarTesting,
                        public views::View,
                        public views::ButtonListener,
                        public views::DragController,
                        public OmniboxEditController,
                        public DropdownBarHostDelegate,
                        public gfx::AnimationDelegate,
                        public TemplateURLServiceObserver,
                        public SearchModelObserver {
 public:
  
  static const char kViewClassName[];

  
  int dropdown_animation_offset() const { return dropdown_animation_offset_; }

  class Delegate {
   public:
    
    virtual content::WebContents* GetWebContents() = 0;

    
    virtual InstantController* GetInstant() = 0;

    virtual ToolbarModel* GetToolbarModel() = 0;
    virtual const ToolbarModel* GetToolbarModel() const = 0;

    
    virtual views::Widget* CreateViewsBubble(
        views::BubbleDelegateView* bubble_delegate) = 0;

    
    virtual PageActionImageView* CreatePageActionImageView(
        LocationBarView* owner,
        ExtensionAction* action) = 0;

    
    virtual ContentSettingBubbleModelDelegate*
        GetContentSettingBubbleModelDelegate() = 0;

    
    virtual void ShowWebsiteSettings(content::WebContents* web_contents,
                                     const GURL& url,
                                     const content::SSLStatus& ssl) = 0;

   protected:
    virtual ~Delegate() {}
  };

  enum ColorKind {
    BACKGROUND = 0,
    TEXT,
    SELECTED_TEXT,
    DEEMPHASIZED_TEXT,
    SECURITY_TEXT,
  };

  LocationBarView(Browser* browser,
                  Profile* profile,
                  CommandUpdater* command_updater,
                  Delegate* delegate,
                  bool is_popup_mode);

  virtual ~LocationBarView();

  
  void Init();

  
  
  bool IsInitialized() const;

  
  
  SkColor GetColor(ToolbarModel::SecurityLevel security_level,
                   ColorKind kind) const;

  
  Delegate* delegate() const { return delegate_; }

  
  void ZoomChangedForActiveTab(bool can_show_bubble);

  
  ZoomView* zoom_view() { return zoom_view_; }

  
  ManagePasswordsIconView* manage_passwords_icon_view() {
    return manage_passwords_icon_view_;
  }

  
  
  
  
  
  void SetPreviewEnabledPageAction(ExtensionAction* page_action,
                                   bool preview_enabled);

  
  PageActionWithBadgeView* GetPageActionView(ExtensionAction* page_action);

  
  void SetStarToggled(bool on);

  
  StarView* star_view() { return star_view_; }

  
  void SetTranslateIconToggled(bool on);

  
  TranslateIconView* translate_icon_view() { return translate_icon_view_; }

  
  
  gfx::Point GetOmniboxViewOrigin() const;

  
  
  
  void SetImeInlineAutocompletion(const base::string16& text);

  
  void SetGrayTextAutocompletion(const base::string16& text);

  
  base::string16 GetGrayTextAutocompletion() const;

  
  
  
  virtual void SetShowFocusRect(bool show);

  
  
  virtual void SelectAll();

  LocationIconView* location_icon_view() { return location_icon_view_; }

  
  
  gfx::Point GetLocationBarAnchorPoint() const;

  OmniboxViewViews* omnibox_view() { return omnibox_view_; }
  const OmniboxViewViews* omnibox_view() const { return omnibox_view_; }

  views::View* generated_credit_card_view();

  
  
  
  
  int GetInternalHeight(bool use_preferred_size);

  
  
  
  void GetOmniboxPopupPositioningInfo(gfx::Point* top_left_screen_coord,
                                      int* popup_width,
                                      int* left_margin,
                                      int* right_margin);

  
  virtual void FocusLocation(bool select_all) OVERRIDE;
  virtual void Revert() OVERRIDE;
  virtual OmniboxView* GetOmniboxView() OVERRIDE;

  
  virtual bool HasFocus() const OVERRIDE;
  virtual void GetAccessibleState(ui::AXViewState* state) OVERRIDE;
  virtual gfx::Size GetPreferredSize() const OVERRIDE;
  virtual void Layout() OVERRIDE;

  
  virtual void Update(const content::WebContents* contents) OVERRIDE;
  virtual void ShowURL() OVERRIDE;
  virtual void EndOriginChipAnimations(bool cancel_fade) OVERRIDE;
  virtual ToolbarModel* GetToolbarModel() OVERRIDE;
  virtual content::WebContents* GetWebContents() OVERRIDE;

  
  static const int kNormalEdgeThickness;
  
  static const int kPopupEdgeThickness;
  
  
  static const int kItemPadding;
  
  static const int kIconInternalPadding;
  
  
  static const int kOriginChipEdgeItemPadding;
  
  static const int kOriginChipBuiltinPadding;
  
  static const int kBubblePadding;

 private:
  typedef std::vector<ContentSettingImageView*> ContentSettingViews;

  friend class PageActionImageView;
  friend class PageActionWithBadgeView;
  typedef std::vector<ExtensionAction*> PageActions;
  typedef std::vector<PageActionWithBadgeView*> PageActionViews;

  
  
  static int IncrementalMinimumWidth(views::View* view);

  
  int GetHorizontalEdgeThickness() const;

  
  int vertical_edge_thickness() const {
    return is_popup_mode_ ? kPopupEdgeThickness : kNormalEdgeThickness;
  }

  
  
  
  bool RefreshContentSettingViews();

  
  void DeletePageActionViews();

  
  
  
  bool RefreshPageActionViews();

  
  
  bool RefreshZoomView();

  
  void RefreshTranslateIcon();

  
  bool RefreshManagePasswordsIconView();

  
  void ShowFirstRunBubbleInternal();

  
  bool HasValidSuggestText() const;

  bool ShouldShowKeywordBubble() const;
  bool ShouldShowEVBubble() const;

  
  
  
  
  
  
  
  
  double GetValueForAnimation(bool hide) const;

  
  void ResetShowAnimationAndColors();

  
  virtual void ShowFirstRunBubble() OVERRIDE;
  virtual GURL GetDestinationURL() const OVERRIDE;
  virtual WindowOpenDisposition GetWindowOpenDisposition() const OVERRIDE;
  virtual ui::PageTransition GetPageTransition() const OVERRIDE;
  virtual void AcceptInput() OVERRIDE;
  virtual void FocusSearch() OVERRIDE;
  virtual void UpdateContentSettingsIcons() OVERRIDE;
  virtual void UpdateManagePasswordsIconAndBubble() OVERRIDE;
  virtual void UpdatePageActions() OVERRIDE;
  virtual void InvalidatePageActions() OVERRIDE;
  virtual void UpdateBookmarkStarVisibility() OVERRIDE;
  virtual bool ShowPageActionPopup(const extensions::Extension* extension,
                                   bool grant_active_tab) OVERRIDE;
  virtual void UpdateOpenPDFInReaderPrompt() OVERRIDE;
  virtual void UpdateGeneratedCreditCardView() OVERRIDE;
  virtual void SaveStateToContents(content::WebContents* contents) OVERRIDE;
  virtual const OmniboxView* GetOmniboxView() const OVERRIDE;
  virtual LocationBarTesting* GetLocationBarForTesting() OVERRIDE;

  
  virtual int PageActionCount() OVERRIDE;
  virtual int PageActionVisibleCount() OVERRIDE;
  virtual ExtensionAction* GetPageAction(size_t index) OVERRIDE;
  virtual ExtensionAction* GetVisiblePageAction(size_t index) OVERRIDE;
  virtual void TestPageActionPressed(size_t index) OVERRIDE;
  virtual bool GetBookmarkStarVisibility() OVERRIDE;

  
  virtual const char* GetClassName() const OVERRIDE;
  virtual void OnBoundsChanged(const gfx::Rect& previous_bounds) OVERRIDE;
  virtual void OnFocus() OVERRIDE;
  virtual void OnPaint(gfx::Canvas* canvas) OVERRIDE;
  virtual void PaintChildren(gfx::Canvas* canvas,
                             const views::CullSet& cull_set) OVERRIDE;

  
  virtual void ButtonPressed(views::Button* sender,
                             const ui::Event& event) OVERRIDE;

  
  virtual void WriteDragDataForView(View* sender,
                                    const gfx::Point& press_pt,
                                    OSExchangeData* data) OVERRIDE;
  virtual int GetDragOperationsForView(View* sender,
                                       const gfx::Point& p) OVERRIDE;
  virtual bool CanStartDragForView(View* sender,
                                   const gfx::Point& press_pt,
                                   const gfx::Point& p) OVERRIDE;

  
  virtual void OnChanged() OVERRIDE;
  virtual void OnSetFocus() OVERRIDE;
  virtual InstantController* GetInstant() OVERRIDE;
  virtual const ToolbarModel* GetToolbarModel() const OVERRIDE;
  virtual void HideURL() OVERRIDE;

  
  virtual void SetFocusAndSelection(bool select_all) OVERRIDE;
  virtual void SetAnimationOffset(int offset) OVERRIDE;

  
  virtual void AnimationProgressed(const gfx::Animation* animation) OVERRIDE;
  virtual void AnimationEnded(const gfx::Animation* animation) OVERRIDE;

  
  virtual void OnTemplateURLServiceChanged() OVERRIDE;

  
  virtual void ModelChanged(const SearchModel::State& old_state,
                            const SearchModel::State& new_state) OVERRIDE;

  
  
  
  Browser* browser_;

  OmniboxViewViews* omnibox_view_;

  
  Delegate* delegate_;

  
  scoped_ptr<views::Painter> border_painter_;

  
  OriginChipView* origin_chip_view_;

  
  LocationIconView* location_icon_view_;

  
  EVBubbleView* ev_bubble_view_;

  
  
  
  
  views::Label* ime_inline_autocomplete_view_;

  
  
  
  
  

  
  SelectedKeywordView* selected_keyword_view_;

  
  
  views::Label* suggested_text_view_;

  
  KeywordHintView* keyword_hint_view_;

  
  views::ImageButton* mic_search_view_;

  
  ContentSettingViews content_setting_views_;

  
  ZoomView* zoom_view_;

  
  GeneratedCreditCardView* generated_credit_card_view_;

  
  OpenPDFInReaderView* open_pdf_in_reader_view_;

  
  ManagePasswordsIconView* manage_passwords_icon_view_;

  
  PageActions page_actions_;

  
  PageActionViews page_action_views_;

  
  TranslateIconView* translate_icon_view_;

  
  StarView* star_view_;

  
  SearchButton* search_button_;

  
  
  const bool is_popup_mode_;

  
  
  bool show_focus_rect_;

  
  
  TemplateURLService* template_url_service_;

  
  BooleanPrefMember edit_bookmarks_enabled_;

  
  
  
  
  int dropdown_animation_offset_;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  scoped_ptr<gfx::SlideAnimation> show_url_animation_;
  scoped_ptr<gfx::SlideAnimation> hide_url_animation_;
  
  
  
  
  int starting_omnibox_offset_;
  int current_omnibox_offset_;
  
  
  
  
  
  
  int starting_omnibox_leading_inset_;
  int current_omnibox_leading_inset_;
  
  
  
  int current_omnibox_width_;
  int ending_omnibox_width_;

  DISALLOW_COPY_AND_ASSIGN(LocationBarView);
};

#endif  
