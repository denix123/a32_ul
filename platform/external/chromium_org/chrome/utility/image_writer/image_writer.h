// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_UTILITY_IMAGE_WRITER_IMAGE_WRITER_H_
#define CHROME_UTILITY_IMAGE_WRITER_IMAGE_WRITER_H_

#include <vector>

#include "base/bind.h"
#include "base/callback.h"
#include "base/files/file.h"
#include "base/files/file_path.h"
#include "base/memory/weak_ptr.h"

#if defined(OS_WIN)
#include <windows.h>
#endif

namespace image_writer {

class ImageWriterHandler;
#if defined(OS_MACOSX)
class DiskUnmounterMac;
#endif

class ImageWriter : public base::SupportsWeakPtr<ImageWriter> {
 public:
  explicit ImageWriter(ImageWriterHandler* handler,
                       const base::FilePath& image_path,
                       const base::FilePath& device_path);
  virtual ~ImageWriter();

  
  void Write();
  
  
  void Verify();
  
  void Cancel();

  
  bool IsRunning() const;
  
  
  bool IsValidDevice();
  
  
  void UnmountVolumes(const base::Closure& continuation);

  
  const base::FilePath& GetImagePath();
  
  const base::FilePath& GetDevicePath();

 private:
  
  void PostTask(const base::Closure& task);
  void PostProgress(int64 progress);
  void Error(const std::string& message);

  
  bool InitializeFiles();
  bool OpenDevice();

  
  void WriteChunk();
  void VerifyChunk();

  base::FilePath image_path_;
  base::FilePath device_path_;

  base::File image_file_;
  base::File device_file_;
  int64 bytes_processed_;
  bool running_;

#if defined(OS_WIN)
  std::vector<HANDLE> volume_handles_;
#endif

#if defined(OS_MACOSX)
  friend class DiskUnmounterMac;
  scoped_ptr<DiskUnmounterMac> unmounter_;
#endif

  ImageWriterHandler* handler_;
};

}  

#endif  
