// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef UI_BASE_RESOURCE_DATA_PACK_H_
#define UI_BASE_RESOURCE_DATA_PACK_H_

#include <map>

#include "base/basictypes.h"
#include "base/files/file.h"
#include "base/files/memory_mapped_file.h"
#include "base/memory/scoped_ptr.h"
#include "base/strings/string_piece.h"
#include "ui/base/layout.h"
#include "ui/base/resource/resource_handle.h"
#include "ui/base/ui_base_export.h"

namespace base {
class FilePath;
class RefCountedStaticMemory;
}

namespace ui {

class UI_BASE_EXPORT DataPack : public ResourceHandle {
 public:
  DataPack(ui::ScaleFactor scale_factor);
  virtual ~DataPack();

  
  bool LoadFromPath(const base::FilePath& path);

  
  bool LoadFromFile(base::File file);

  
  bool LoadFromFileRegion(base::File file,
                          const base::MemoryMappedFile::Region& region);

  
  // text resources to be written, their encoding must already agree to the
  
  
  static bool WritePack(const base::FilePath& path,
                        const std::map<uint16, base::StringPiece>& resources,
                        TextEncodingType textEncodingType);

  
  virtual bool HasResource(uint16 resource_id) const OVERRIDE;
  virtual bool GetStringPiece(uint16 resource_id,
                              base::StringPiece* data) const OVERRIDE;
  virtual base::RefCountedStaticMemory* GetStaticMemory(
      uint16 resource_id) const OVERRIDE;
  virtual TextEncodingType GetTextEncodingType() const OVERRIDE;
  virtual ui::ScaleFactor GetScaleFactor() const OVERRIDE;

 private:
  
  bool LoadImpl();

  
  scoped_ptr<base::MemoryMappedFile> mmap_;

  
  size_t resource_count_;

  
  TextEncodingType text_encoding_type_;

  
  
  ui::ScaleFactor scale_factor_;

  DISALLOW_COPY_AND_ASSIGN(DataPack);
};

}  

#endif  
