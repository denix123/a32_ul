// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_MESSAGE_CENTER_VIEWS_POPUP_ALIGNMENT_DELEGATE_H_
#define UI_MESSAGE_CENTER_VIEWS_POPUP_ALIGNMENT_DELEGATE_H_

#include "ui/message_center/message_center_export.h"

namespace gfx {
class Display;
class Point;
class Rect;
}

namespace message_center {

class MessagePopupCollection;

class MESSAGE_CENTER_EXPORT PopupAlignmentDelegate {
 public:
  PopupAlignmentDelegate();

  void set_collection(MessagePopupCollection* collection) {
    collection_ = collection;
  }

  
  virtual int GetToastOriginX(const gfx::Rect& toast_bounds) const = 0;

  
  
  virtual int GetBaseLine() const = 0;

  
  virtual int GetWorkAreaBottom() const  = 0;

  
  virtual bool IsTopDown() const = 0;

  
  
  virtual bool IsFromLeft() const = 0;

  
  
  
  virtual void RecomputeAlignment(const gfx::Display& display) = 0;

 protected:
  virtual ~PopupAlignmentDelegate();

  void DoUpdateIfPossible();

 private:
  MessagePopupCollection* collection_;
};

}  

#endif  
