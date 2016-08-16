// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <map>

#include "remoting/protocol/input_filter.h"

namespace remoting {

class NormalizingInputFilterMac : public protocol::InputFilter {
 public:
  explicit NormalizingInputFilterMac(protocol::InputStub* input_stub);
  virtual ~NormalizingInputFilterMac();

  
  virtual void InjectKeyEvent(const protocol::KeyEvent& event) OVERRIDE;

 private:
  typedef std::map<int, protocol::KeyEvent> KeyPressedMap;

  
  void GenerateKeyupEvents();

  
  KeyPressedMap key_pressed_map_;

  DISALLOW_COPY_AND_ASSIGN(NormalizingInputFilterMac);
};

}  
