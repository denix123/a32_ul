// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_OZONE_PLATFORM_TEST_FILE_SURFACE_FACTORY_H_
#define UI_OZONE_PLATFORM_TEST_FILE_SURFACE_FACTORY_H_

#include "base/files/file_path.h"
#include "base/id_map.h"
#include "base/memory/scoped_ptr.h"
#include "ui/gfx/native_widget_types.h"
#include "ui/ozone/platform/test/test_window.h"
#include "ui/ozone/public/surface_factory_ozone.h"

namespace ui {

class TestWindowManager : public SurfaceFactoryOzone {
 public:
  explicit TestWindowManager(const base::FilePath& dump_location);
  virtual ~TestWindowManager();

  
  void Initialize();

  
  int32_t AddWindow(TestWindow* window);

  
  void RemoveWindow(int32_t window_id, TestWindow* window);

  
  base::FilePath base_path() const;

  
  virtual scoped_ptr<SurfaceOzoneCanvas> CreateCanvasForWidget(
      gfx::AcceleratedWidget w) OVERRIDE;
  virtual bool LoadEGLGLES2Bindings(
      AddGLLibraryCallback add_gl_library,
      SetGLGetProcAddressProcCallback set_gl_get_proc_address) OVERRIDE;

 private:
  base::FilePath location_;

  IDMap<TestWindow> windows_;

  DISALLOW_COPY_AND_ASSIGN(TestWindowManager);
};

}  

#endif  
