// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_LIBADDRESSINPUT_CHROMIUM_INPUT_SUGGESTER_H_
#define THIRD_PARTY_LIBADDRESSINPUT_CHROMIUM_INPUT_SUGGESTER_H_

#include <stdint.h>
#include <map>
#include <vector>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "third_party/icu/source/i18n/unicode/coll.h"
#include "third_party/libaddressinput/src/cpp/include/libaddressinput/address_field.h"
#include "third_party/libaddressinput/src/cpp/include/libaddressinput/address_input_helper.h"
#include "third_party/libaddressinput/src/cpp/include/libaddressinput/address_validator.h"
#include "third_party/libaddressinput/src/cpp/include/libaddressinput/region_data_builder.h"

namespace i18n {
namespace addressinput {
class PreloadSupplier;
class RegionData;
struct AddressData;
}
}

namespace autofill {

class InputSuggester {
 public:
  
  explicit InputSuggester(::i18n::addressinput::PreloadSupplier* supplier);
  ~InputSuggester();

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  void GetSuggestions(
      const ::i18n::addressinput::AddressData& user_input,
      ::i18n::addressinput::AddressField focused_field,
      size_t suggestion_limit,
      std::vector< ::i18n::addressinput::AddressData>* suggestions);

 private:
  class SubRegionData;

  
  class StringCanonicalizer {
   public:
    
    
    StringCanonicalizer();
    ~StringCanonicalizer();

    
    
    
    
    
    
    
    
    
    
    const std::vector<uint8_t>& Canonicalize(const std::string& original) const;

   private:
    int32_t buffer_size() const;

    mutable std::vector<uint8_t> buffer_;
    scoped_ptr<icu::Collator> collator_;

    DISALLOW_COPY_AND_ASSIGN(StringCanonicalizer);
  };

  
  void Validated(bool success,
                 const ::i18n::addressinput::AddressData&,
                 const ::i18n::addressinput::FieldProblemMap&);

  
  ::i18n::addressinput::RegionDataBuilder region_data_builder_;

  
  const ::i18n::addressinput::AddressInputHelper input_helper_;

  
  ::i18n::addressinput::AddressValidator validator_;

  
  const scoped_ptr<const ::i18n::addressinput::AddressValidator::Callback>
      validated_;

  
  
  std::map<const ::i18n::addressinput::RegionData*, SubRegionData> sub_regions_;

  
  
  StringCanonicalizer canonicalizer_;

  DISALLOW_COPY_AND_ASSIGN(InputSuggester);
};

}  

#endif  
