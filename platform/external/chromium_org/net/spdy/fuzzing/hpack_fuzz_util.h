// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_SPDY_FUZZING_HPACK_FUZZ_UTIL_H_
#define NET_SPDY_FUZZING_HPACK_FUZZ_UTIL_H_

#include <string>
#include <vector>

#include "base/memory/scoped_ptr.h"
#include "base/strings/string_piece.h"
#include "net/base/net_export.h"
#include "net/spdy/hpack_decoder.h"
#include "net/spdy/hpack_encoder.h"

namespace net {

class NET_EXPORT_PRIVATE HpackFuzzUtil {
 public:
  
  
  struct NET_EXPORT_PRIVATE GeneratorContext {
    GeneratorContext();
    ~GeneratorContext();
    std::vector<std::string> names;
    std::vector<std::string> values;
  };

  
  static void InitializeGeneratorContext(GeneratorContext* context);

  
  static std::map<std::string, std::string> NextGeneratedHeaderSet(
      GeneratorContext* context);

  
  
  static size_t SampleExponential(size_t mean, size_t sanity_bound);

  
  struct NET_EXPORT_PRIVATE Input {
    Input();  
    ~Input();

    size_t remaining() {
      return input.size() - offset;
    }
    const char* ptr() {
      return input.data() + offset;
    }

    std::string input;
    size_t offset;
  };

  
  
  static bool NextHeaderBlock(Input* input, base::StringPiece* out);

  
  
  static std::string HeaderBlockPrefix(size_t block_size);

  
  
  struct NET_EXPORT_PRIVATE FuzzerContext {
    FuzzerContext();
    ~FuzzerContext();
    scoped_ptr<HpackDecoder> first_stage;
    scoped_ptr<HpackEncoder> second_stage;
    scoped_ptr<HpackDecoder> third_stage;
  };

  static void InitializeFuzzerContext(FuzzerContext* context);

  
  
  
  static bool RunHeaderBlockThroughFuzzerStages(FuzzerContext* context,
                                                base::StringPiece input_block);

  
  
  
  static void FlipBits(uint8* buffer,
                       size_t buffer_length,
                       size_t flip_per_thousand);
};

}  

#endif  
