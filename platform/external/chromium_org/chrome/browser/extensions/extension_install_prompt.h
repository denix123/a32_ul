// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_EXTENSION_INSTALL_PROMPT_H_
#define CHROME_BROWSER_EXTENSIONS_EXTENSION_INSTALL_PROMPT_H_

#include <string>
#include <vector>

#include "base/callback.h"
#include "base/compiler_specific.h"
#include "base/files/file_path.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/strings/string16.h"
#include "chrome/browser/extensions/crx_installer_error.h"
#include "chrome/browser/extensions/extension_install_prompt_experiment.h"
#include "extensions/common/url_pattern.h"
#include "third_party/skia/include/core/SkBitmap.h"
#include "ui/gfx/image/image.h"
#include "ui/gfx/image/image_skia.h"
#include "ui/gfx/native_widget_types.h"

class Browser;
class ExtensionInstallUI;
class Profile;

namespace base {
class DictionaryValue;
class MessageLoop;
}  

namespace content {
class PageNavigator;
class WebContents;
}

namespace extensions {
class BundleInstaller;
class Extension;
class ExtensionWebstorePrivateApiTest;
class MockGetAuthTokenFunction;
class PermissionSet;
}  

namespace infobars {
class InfoBarDelegate;
}

class ExtensionInstallPrompt
    : public base::SupportsWeakPtr<ExtensionInstallPrompt> {
 public:
  
  
  enum AutoConfirmForTests {
    NONE,    
    ACCEPT,  
    CANCEL,  
  };
  static AutoConfirmForTests g_auto_confirm_for_tests;

  
  
  enum PromptType {
    UNSET_PROMPT_TYPE = -1,
    INSTALL_PROMPT = 0,
    INLINE_INSTALL_PROMPT,
    BUNDLE_INSTALL_PROMPT,
    RE_ENABLE_PROMPT,
    PERMISSIONS_PROMPT,
    EXTERNAL_INSTALL_PROMPT,
    POST_INSTALL_PERMISSIONS_PROMPT,
    LAUNCH_PROMPT,
    REMOTE_INSTALL_PROMPT,
    REPAIR_PROMPT,
    NUM_PROMPT_TYPES
  };

  
  enum DetailsType {
    PERMISSIONS_DETAILS = 0,
    WITHHELD_PERMISSIONS_DETAILS,
    RETAINED_FILES_DETAILS,
  };

  
  
  enum PermissionsType {
    REGULAR_PERMISSIONS = 0,
    WITHHELD_PERMISSIONS,
    ALL_PERMISSIONS,
  };

  static std::string PromptTypeToString(PromptType type);

  
  
  
  
  
  
  class Prompt : public base::RefCountedThreadSafe<Prompt> {
   public:
    explicit Prompt(PromptType type);

    
    void SetPermissions(const std::vector<base::string16>& permissions,
                        PermissionsType permissions_type);
    
    void SetPermissionsDetails(const std::vector<base::string16>& details,
                               PermissionsType permissions_type);
    void SetIsShowingDetails(DetailsType type,
                             size_t index,
                             bool is_showing_details);
    void SetWebstoreData(const std::string& localized_user_count,
                         bool show_user_count,
                         double average_rating,
                         int rating_count);
    void SetUserNameFromProfile(Profile* profile);

    PromptType type() const { return type_; }
    void set_type(PromptType type) { type_ = type; }

    
    base::string16 GetDialogTitle() const;
    base::string16 GetHeading() const;
    int GetDialogButtons() const;
    bool HasAcceptButtonLabel() const;
    base::string16 GetAcceptButtonLabel() const;
    bool HasAbortButtonLabel() const;
    base::string16 GetAbortButtonLabel() const;
    base::string16 GetPermissionsHeading(
        PermissionsType permissions_type) const;
    base::string16 GetRetainedFilesHeading() const;

    bool ShouldShowPermissions() const;
    bool ShouldShowExplanationText() const;

    
    

    
    
    
    
    typedef void(*StarAppender)(const gfx::ImageSkia*, void*);
    void AppendRatingStars(StarAppender appender, void* data) const;
    base::string16 GetRatingCount() const;
    base::string16 GetUserCount() const;
    size_t GetPermissionCount(PermissionsType permissions_type) const;
    size_t GetPermissionsDetailsCount(PermissionsType permissions_type) const;
    base::string16 GetPermission(size_t index,
                                 PermissionsType permissions_type) const;
    base::string16 GetPermissionsDetails(
        size_t index,
        PermissionsType permissions_type) const;
    bool GetIsShowingDetails(DetailsType type, size_t index) const;
    size_t GetRetainedFileCount() const;
    base::string16 GetRetainedFile(size_t index) const;

    
    const extensions::BundleInstaller* bundle() const { return bundle_; }
    void set_bundle(const extensions::BundleInstaller* bundle) {
      bundle_ = bundle;
    }

    
    const extensions::Extension* extension() const { return extension_; }
    void set_extension(const extensions::Extension* extension) {
      extension_ = extension;
    }

    
    void set_retained_files(const std::vector<base::FilePath>& retained_files) {
      retained_files_ = retained_files;
    }

    const gfx::Image& icon() const { return icon_; }
    void set_icon(const gfx::Image& icon) { icon_ = icon; }

    bool has_webstore_data() const { return has_webstore_data_; }

    const ExtensionInstallPromptExperiment* experiment() const {
      return experiment_.get();
    }
    void set_experiment(ExtensionInstallPromptExperiment* experiment) {
      experiment_ = experiment;
    }

   private:
    friend class base::RefCountedThreadSafe<Prompt>;

    struct InstallPromptPermissions {
      InstallPromptPermissions();
      ~InstallPromptPermissions();

      std::vector<base::string16> permissions;
      std::vector<base::string16> details;
      std::vector<bool> is_showing_details;
    };

    virtual ~Prompt();

    
    
    InstallPromptPermissions& GetPermissionsForType(
        PermissionsType permissions_type);
    const InstallPromptPermissions& GetPermissionsForType(
        PermissionsType permissions_type) const;

    bool ShouldDisplayRevokeFilesButton() const;

    PromptType type_;

    
    
    InstallPromptPermissions prompt_permissions_;
    
    InstallPromptPermissions withheld_prompt_permissions_;

    bool is_showing_details_for_retained_files_;

    
    const extensions::Extension* extension_;
    const extensions::BundleInstaller* bundle_;

    
    gfx::Image icon_;

    
    
    
    std::string localized_user_count_;
    
    double average_rating_;
    int rating_count_;

    
    
    bool show_user_count_;

    
    
    bool has_webstore_data_;

    std::vector<base::FilePath> retained_files_;

    scoped_refptr<ExtensionInstallPromptExperiment> experiment_;

    DISALLOW_COPY_AND_ASSIGN(Prompt);
  };

  static const int kMinExtensionRating = 0;
  static const int kMaxExtensionRating = 5;

  class Delegate {
   public:
    
    virtual void InstallUIProceed() = 0;

    
    
    virtual void InstallUIAbort(bool user_initiated) = 0;

   protected:
    virtual ~Delegate() {}
  };

  
  
  
  struct ShowParams {
    explicit ShowParams(content::WebContents* contents);
    ShowParams(gfx::NativeWindow window, content::PageNavigator* navigator);

    
    content::WebContents* parent_web_contents;

    
    
    gfx::NativeWindow parent_window;
    content::PageNavigator* navigator;
  };

  typedef base::Callback<void(const ExtensionInstallPrompt::ShowParams&,
                              ExtensionInstallPrompt::Delegate*,
                              scoped_refptr<ExtensionInstallPrompt::Prompt>)>
      ShowDialogCallback;

  
  
  static ShowDialogCallback GetDefaultShowDialogCallback();

  
  
  static scoped_refptr<extensions::Extension> GetLocalizedExtensionForDisplay(
      const base::DictionaryValue* manifest,
      int flags,  
      const std::string& id,
      const std::string& localized_name,
      const std::string& localized_description,
      std::string* error);

  
  explicit ExtensionInstallPrompt(content::WebContents* contents);

  
  ExtensionInstallPrompt(Profile* profile,
                         gfx::NativeWindow native_window,
                         content::PageNavigator* navigator);

  virtual ~ExtensionInstallPrompt();

  ExtensionInstallUI* install_ui() const { return install_ui_.get(); }

  content::WebContents* parent_web_contents() const {
    return show_params_.parent_web_contents;
  }

  
  
  
  
  virtual void ConfirmBundleInstall(
      extensions::BundleInstaller* bundle,
      const extensions::PermissionSet* permissions);

  
  
  
  
  virtual void ConfirmStandaloneInstall(Delegate* delegate,
                                        const extensions::Extension* extension,
                                        SkBitmap* icon,
                                        scoped_refptr<Prompt> prompt);

  
  
  
  
  
  virtual void ConfirmWebstoreInstall(
      Delegate* delegate,
      const extensions::Extension* extension,
      const SkBitmap* icon,
      const ShowDialogCallback& show_dialog_callback);

  
  
  
  
  
  virtual void ConfirmInstall(Delegate* delegate,
                              const extensions::Extension* extension,
                              const ShowDialogCallback& show_dialog_callback);

  
  
  
  
  virtual void ConfirmReEnable(Delegate* delegate,
                               const extensions::Extension* extension);

  
  
  
  
  virtual void ConfirmExternalInstall(
      Delegate* delegate,
      const extensions::Extension* extension,
      const ShowDialogCallback& show_dialog_callback,
      scoped_refptr<Prompt> prompt);

  
  
  
  
  virtual void ConfirmPermissions(Delegate* delegate,
                                  const extensions::Extension* extension,
                                  const extensions::PermissionSet* permissions);

  
  
  
  
  virtual void ReviewPermissions(
      Delegate* delegate,
      const extensions::Extension* extension,
      const std::vector<base::FilePath>& retained_file_paths);

  
  virtual void OnInstallSuccess(const extensions::Extension* extension,
                                SkBitmap* icon);

  
  virtual void OnInstallFailure(const extensions::CrxInstallerError& error);

  void set_callback_for_test(const ShowDialogCallback& show_dialog_callback) {
    show_dialog_callback_ = show_dialog_callback;
  }

 protected:
  friend class extensions::ExtensionWebstorePrivateApiTest;
  friend class WebstoreStartupInstallUnpackFailureTest;

  
  bool record_oauth2_grant_;

 private:
  friend class GalleryInstallApiTestObserver;

  
  
  void SetIcon(const SkBitmap* icon);

  
  void OnImageLoaded(const gfx::Image& image);

  
  
  
  void LoadImageIfNeeded();

  
  void ShowConfirmation();

  base::MessageLoop* ui_loop_;

  
  SkBitmap icon_;

  
  
  const extensions::Extension* extension_;

  
  const extensions::BundleInstaller* bundle_;

  
  
  scoped_refptr<const extensions::PermissionSet> custom_permissions_;

  
  scoped_ptr<ExtensionInstallUI> install_ui_;

  
  ShowParams show_params_;

  
  Delegate* delegate_;

  
  scoped_refptr<Prompt> prompt_;

  
  ShowDialogCallback show_dialog_callback_;
};

#endif  
