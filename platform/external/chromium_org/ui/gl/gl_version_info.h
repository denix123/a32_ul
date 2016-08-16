// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_GL_GL_VERSION_INFO_H_
#define UI_GL_GL_VERSION_INFO_H_

#include <string>
#include "base/basictypes.h"

namespace gfx {

struct GLVersionInfo {
  GLVersionInfo(const char* version_str, const char* renderer_str);

  
  
  bool is_es;
  bool is_es1;
  bool is_es2;
  bool is_es3;

  bool is_gl1;
  bool is_gl2;
  bool is_gl3;
  bool is_gl4;

  bool is_angle;

private:
  DISALLOW_COPY_AND_ASSIGN(GLVersionInfo);
};

}  

#endif 
