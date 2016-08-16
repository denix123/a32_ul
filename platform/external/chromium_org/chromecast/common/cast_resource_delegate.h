// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMECAST_COMMON_CAST_RESOURCE_DELEGATE_H_
#define CHROMECAST_COMMON_CAST_RESOURCE_DELEGATE_H_

#include <string>

#include "base/macros.h"
#include "base/memory/ref_counted_memory.h"
#include "base/memory/scoped_ptr.h"
#include "ui/base/resource/resource_bundle.h"

namespace base {
class FilePath;
}

namespace gfx {
class Image;
}

namespace chromecast {

class CastResourceDelegate : public ui::ResourceBundle::Delegate {
 public:
  
  static CastResourceDelegate* GetInstance();

  CastResourceDelegate();
  virtual ~CastResourceDelegate();

  
  virtual base::FilePath GetPathForResourcePack(
      const base::FilePath& pack_path,
      ui::ScaleFactor scale_factor) OVERRIDE;
  virtual base::FilePath GetPathForLocalePack(
      const base::FilePath& pack_path,
      const std::string& locale) OVERRIDE;
  virtual gfx::Image GetImageNamed(int resource_id) OVERRIDE;
  virtual gfx::Image GetNativeImageNamed(
      int resource_id,
      ui::ResourceBundle::ImageRTL rtl) OVERRIDE;
  virtual base::RefCountedStaticMemory* LoadDataResourceBytes(
      int resource_id,
      ui::ScaleFactor scale_factor) OVERRIDE;
  virtual bool GetRawDataResource(int resource_id,
                                  ui::ScaleFactor scale_factor,
                                  base::StringPiece* value) OVERRIDE;
  virtual bool GetLocalizedString(int message_id,
                                  base::string16* value) OVERRIDE;
  virtual scoped_ptr<gfx::Font> GetFont(
      ui::ResourceBundle::FontStyle style) OVERRIDE;

  
  void AddExtraLocalizedString(int resource_id,
                               const base::string16& localized);
  void RemoveExtraLocalizedString(int resource_id);
  void ClearAllExtraLocalizedStrings();

 private:
  typedef base::hash_map<int, base::string16> ExtraLocaledStringMap;

  ExtraLocaledStringMap extra_localized_strings_;

  DISALLOW_COPY_AND_ASSIGN(CastResourceDelegate);
};

}  

#endif  
