// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ATHENA_ACTIVITY_PUBLIC_ACTIVITY_VIEW_MODEL_H_
#define ATHENA_ACTIVITY_PUBLIC_ACTIVITY_VIEW_MODEL_H_

#include "athena/athena_export.h"
#include "base/strings/string16.h"

typedef unsigned int SkColor;

namespace gfx {
class ImageSkia;
}

namespace views {
class View;
class Widget;
}

namespace athena {

class ATHENA_EXPORT ActivityViewModel {
 public:
  virtual ~ActivityViewModel() {}

  
  
  
  
  virtual void Init() = 0;

  
  virtual SkColor GetRepresentativeColor() const = 0;

  
  virtual base::string16 GetTitle() const = 0;

  
  virtual gfx::ImageSkia GetIcon() const = 0;

  
  
  virtual bool UsesFrame() const = 0;

  
  
  
  virtual views::View* GetContentsView() = 0;

  
  
  virtual views::Widget* CreateWidget() = 0;

  
  
  
  
  
  
  
  
  virtual gfx::ImageSkia GetOverviewModeImage() = 0;

  
  virtual void PrepareContentsForOverview() = 0;

  
  virtual void ResetContentsView() = 0;
};

}  

#endif  
