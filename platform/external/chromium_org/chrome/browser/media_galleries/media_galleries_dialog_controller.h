// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_MEDIA_GALLERIES_MEDIA_GALLERIES_DIALOG_CONTROLLER_H_
#define CHROME_BROWSER_MEDIA_GALLERIES_MEDIA_GALLERIES_DIALOG_CONTROLLER_H_

#include <vector>

#include "base/strings/string16.h"
#include "chrome/browser/media_galleries/media_galleries_preferences.h"

namespace content {
class WebContents;
}

namespace ui {
class MenuModel;
}

class MediaGalleriesDialogController;

class MediaGalleriesDialog {
 public:
  virtual ~MediaGalleriesDialog();

  
  virtual void UpdateGalleries() = 0;

  
  static MediaGalleriesDialog* Create(
      MediaGalleriesDialogController* controller);
 private:
  friend class TestMediaGalleriesAddScanResultsFunction;

  virtual void AcceptDialogForTesting() = 0;
};

class MediaGalleriesDialogController {
 public:
  struct Entry {
    Entry(const MediaGalleryPrefInfo& pref_info, bool selected)
        : pref_info(pref_info),
          selected(selected) {
    }
    Entry() {}

    MediaGalleryPrefInfo pref_info;
    bool selected;
  };

  typedef std::vector<Entry> Entries;

  
  virtual base::string16 GetHeader() const = 0;

  
  virtual base::string16 GetSubtext() const = 0;

  
  virtual bool IsAcceptAllowed() const = 0;

  
  virtual bool ShouldShowFolderViewer(const Entry& entry) const = 0;

  
  virtual std::vector<base::string16> GetSectionHeaders() const = 0;

  
  
  virtual Entries GetSectionEntries(size_t index) const = 0;

  
  virtual base::string16 GetAuxiliaryButtonText() const = 0;

  
  virtual void DidClickAuxiliaryButton() = 0;

  
  virtual void DidToggleEntry(MediaGalleryPrefId id, bool selected) = 0;

  
  virtual void DidClickOpenFolderViewer(MediaGalleryPrefId id) = 0;

  
  virtual void DidForgetEntry(MediaGalleryPrefId id) = 0;

  
  virtual base::string16 GetAcceptButtonText() const = 0;

  
  virtual void DialogFinished(bool accepted) = 0;

  virtual ui::MenuModel* GetContextMenu(MediaGalleryPrefId id) = 0;

  virtual content::WebContents* WebContents() = 0;

 protected:
  MediaGalleriesDialogController();
  virtual ~MediaGalleriesDialogController();

  DISALLOW_COPY_AND_ASSIGN(MediaGalleriesDialogController);
};

#endif  
