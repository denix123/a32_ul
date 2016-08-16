// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "remoting/protocol/input_filter.h"

#include "remoting/proto/event.pb.h"

namespace remoting {

class NormalizingInputFilterCros : public protocol::InputFilter {
 public:
  explicit NormalizingInputFilterCros(protocol::InputStub* input_stub);
  virtual ~NormalizingInputFilterCros();

  
  virtual void InjectKeyEvent(const protocol::KeyEvent& event) OVERRIDE;
  virtual void InjectMouseEvent(const protocol::MouseEvent& event) OVERRIDE;

 private:
  void ProcessKeyDown(const protocol::KeyEvent& event);
  void ProcessKeyUp(const protocol::KeyEvent& event);

  void SwitchRewritingKeyToModifying();

  
  
  
  
  protocol::KeyEvent deferred_keydown_event_;

  
  // by one or more Rewritten key events, and not by any Modified events.
  bool deferred_key_is_rewriting_;

  
  uint32 modifying_key_;

  
  bool left_alt_is_pressed_;

  DISALLOW_COPY_AND_ASSIGN(NormalizingInputFilterCros);
};

}  
