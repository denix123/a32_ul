// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_EXAMPLES_KEYBOARD_KEYS_H_
#define MOJO_EXAMPLES_KEYBOARD_KEYS_H_

#include <vector>

#include "base/basictypes.h"

namespace mojo {
namespace examples {

enum SpecialKey {
  SPECIAL_KEY_SHIFT = -1,
  SPECIAL_KEY_NUMERIC = -2,
  SPECIAL_KEY_ALPHA = -3,
};

struct Key {
  int keyboard_code() const {
    
#if defined(OS_WIN)
    return generated_code ? generated_code : display_code;
#else
    return display_code;
#endif
  }

  
  
  int display_code;

  
  float size;

  
  int event_flags;

  
  int generated_code;
};

struct Row {
  float padding;
  const Key* keys;
  size_t num_keys;
};

std::vector<const Row*> GetQWERTYRows();

std::vector<const Row*> GetNumericRows();

}  
}  

#endif  
