// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_GL_GL_IMAGE_H_
#define UI_GL_GL_IMAGE_H_

#include "base/memory/ref_counted.h"
#include "ui/gfx/native_widget_types.h"
#include "ui/gfx/overlay_transform.h"
#include "ui/gfx/rect.h"
#include "ui/gfx/rect_f.h"
#include "ui/gfx/size.h"
#include "ui/gl/gl_export.h"

namespace gfx {

class GL_EXPORT GLImage : public base::RefCounted<GLImage> {
 public:
  GLImage();

  
  virtual void Destroy(bool have_context) = 0;

  
  virtual gfx::Size GetSize() = 0;

  
  virtual bool BindTexImage(unsigned target) = 0;

  
  virtual void ReleaseTexImage(unsigned target) = 0;

  
  virtual bool CopyTexImage(unsigned target) = 0;

  
  virtual void WillUseTexImage() = 0;

  
  virtual void DidUseTexImage() = 0;

  
  virtual void WillModifyTexImage() = 0;

  
  virtual void DidModifyTexImage() = 0;

  
  virtual bool ScheduleOverlayPlane(gfx::AcceleratedWidget widget,
                                    int z_order,
                                    OverlayTransform transform,
                                    const Rect& bounds_rect,
                                    const RectF& crop_rect) = 0;

  
  
  virtual void SetReleaseAfterUse();

 protected:
  virtual ~GLImage();

 private:
  friend class base::RefCounted<GLImage>;

  DISALLOW_COPY_AND_ASSIGN(GLImage);
};

}  

#endif  
