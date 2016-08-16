// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_RENDERER_HOST_PEPPER_PEPPER_TRUETYPE_FONT_H_
#define CONTENT_BROWSER_RENDERER_HOST_PEPPER_PEPPER_TRUETYPE_FONT_H_

#include <string>
#include <vector>

#include "base/memory/ref_counted.h"
#include "ppapi/proxy/serialized_structs.h"

namespace content {

class PepperTrueTypeFont
    : public base::RefCountedThreadSafe<PepperTrueTypeFont> {
 public:
  
  static PepperTrueTypeFont* Create();

  
  
  
  
  
  virtual int32_t Initialize(
      ppapi::proxy::SerializedTrueTypeFontDesc* desc) = 0;

  
  
  // written only on success.
  
  
  virtual int32_t GetTableTags(std::vector<uint32_t>* tags) = 0;

  
  
  
  // 'data' is written only on success.
  
  
  virtual int32_t GetTable(uint32_t table_tag,
                           int32_t offset,
                           int32_t max_data_length,
                           std::string* data) = 0;

 protected:
  friend class base::RefCountedThreadSafe<PepperTrueTypeFont>;
  virtual ~PepperTrueTypeFont() {};
};

}  

#endif  
