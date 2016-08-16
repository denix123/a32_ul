// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_LOGIN_SCREENSHOT_TESTER_H_
#define CHROME_BROWSER_CHROMEOS_LOGIN_SCREENSHOT_TESTER_H_

#include <string>

#include "base/base_export.h"
#include "base/bind_internal.h"
#include "base/files/file_path.h"
#include "base/macros.h"
#include "base/memory/ref_counted_memory.h"
#include "base/memory/weak_ptr.h"
#include "base/run_loop.h"

namespace chromeos {

class ScreenshotTester {
 public:
  ScreenshotTester();
  virtual ~ScreenshotTester();

  
  
  
  bool TryInitialize();

  
  
  
  
  void Run(const std::string& test_name);

 private:
  typedef scoped_refptr<base::RefCountedBytes> PNGFile;

  
  PNGFile TakeScreenshot();

  
  void UpdateGoldenScreenshot(PNGFile png_data);

  
  
  bool SaveImage(const std::string& file_name,
                 const base::FilePath& screenshot_dir,
                 PNGFile png_data);

  
  void ReturnScreenshot(const PNGFile& screenshot, PNGFile png_data);

  
  
  PNGFile LoadGoldenScreenshot();

  
  
  void CompareScreenshots(PNGFile model, PNGFile sample);

  
  
  std::string test_name_;

  
  base::FilePath golden_screenshots_dir_;

  
  
  base::FilePath artifacts_dir_;

  
  
  base::RunLoop run_loop_;
  base::Closure run_loop_quitter_;

  
  
  bool test_mode_;

  base::WeakPtrFactory<ScreenshotTester> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(ScreenshotTester);
};

}  

#endif  
