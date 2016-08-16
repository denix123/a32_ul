// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_CPP_BINDINGS_TESTS_VALIDATION_TEST_INPUT_PARSER_H_
#define MOJO_PUBLIC_CPP_BINDINGS_TESTS_VALIDATION_TEST_INPUT_PARSER_H_

#include <stdint.h>

#include <string>
#include <vector>

namespace mojo {
namespace test {


bool ParseValidationTestInput(const std::string& input,
                              std::vector<uint8_t>* data,
                              size_t* num_handles,
                              std::string* error_message);

}  
}  

#endif  
