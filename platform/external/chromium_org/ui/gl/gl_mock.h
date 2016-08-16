// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef UI_GL_GL_MOCK_H_
#define UI_GL_GL_MOCK_H_

#include "testing/gmock/include/gmock/gmock.h"
#include "ui/gl/gl_bindings.h"

namespace gfx {

class MockGLInterface {
 public:
  MockGLInterface();
  virtual ~MockGLInterface();

  
  
  static void SetGLInterface(MockGLInterface* gl_interface);

  
  static void* GL_BINDING_CALL GetGLProcAddress(const char* name);

  
  
  

  
  #include "gl_mock_autogen_gl.h"

 private:
  static MockGLInterface* interface_;

  
  #include "gl_bindings_autogen_mock.h"
};

}  

#endif  
