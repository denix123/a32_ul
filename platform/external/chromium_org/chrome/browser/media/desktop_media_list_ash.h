// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_MEDIA_DESKTOP_MEDIA_LIST_ASH_H_
#define CHROME_BROWSER_MEDIA_DESKTOP_MEDIA_LIST_ASH_H_

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/sequenced_task_runner.h"
#include "chrome/browser/media/desktop_media_list.h"
#include "content/public/browser/desktop_media_id.h"

class SkBitmap;

namespace aura {
class Window;
}

namespace cc {
class CopyOutputResult;
class SingleReleaseCallback;
}

namespace gfx {
class Image;
}

class DesktopMediaListAsh : public DesktopMediaList {
 public:
  enum SourceTypes {
    SCREENS = 1,
    WINDOWS = 2,
  };

  explicit DesktopMediaListAsh(int source_types);
  virtual ~DesktopMediaListAsh();

  
  virtual void SetUpdatePeriod(base::TimeDelta period) OVERRIDE;
  virtual void SetThumbnailSize(const gfx::Size& thumbnail_size) OVERRIDE;
  virtual void StartUpdating(DesktopMediaListObserver* observer) OVERRIDE;
  virtual int GetSourceCount() const OVERRIDE;
  virtual const Source& GetSource(int index) const OVERRIDE;
  virtual void SetViewDialogWindowId(
      content::DesktopMediaID::Id dialog_id) OVERRIDE;

 private:
  
  struct SourceDescription {
    SourceDescription(content::DesktopMediaID id, const base::string16& name);

    content::DesktopMediaID id;
    base::string16 name;
  };

  
  static bool CompareSources(const SourceDescription& a,
                             const SourceDescription& b);

  void Refresh();
  void EnumerateWindowsForRoot(
      std::vector<DesktopMediaListAsh::SourceDescription>* windows,
      aura::Window* root_window,
      int container_id);
  void EnumerateSources(
      std::vector<DesktopMediaListAsh::SourceDescription>* windows);
  void CaptureThumbnail(content::DesktopMediaID id, aura::Window* window);
  void OnThumbnailCaptured(content::DesktopMediaID id,
                           const gfx::Image& image);

  int source_types_;

  
  base::TimeDelta update_period_;

  
  gfx::Size thumbnail_size_;

  
  content::DesktopMediaID::Id view_dialog_id_;

  
  DesktopMediaListObserver* observer_;

  
  std::vector<Source> sources_;

  int pending_window_capture_requests_;

  base::WeakPtrFactory<DesktopMediaListAsh> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(DesktopMediaListAsh);
};

#endif  
