// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_LIBADDRESSINPUT_CHROMIUM_ADDRESSINPUT_UTIL_H_
#define THIRD_PARTY_LIBADDRESSINPUT_CHROMIUM_ADDRESSINPUT_UTIL_H_

#include <map>

#include "third_party/libaddressinput/src/cpp/include/libaddressinput/address_field.h"
#include "third_party/libaddressinput/src/cpp/include/libaddressinput/address_problem.h"

namespace i18n {
namespace addressinput {
struct AddressData;
}
}

namespace autofill {
namespace addressinput {

bool HasAllRequiredFields(
    const ::i18n::addressinput::AddressData& address_to_check);

void ValidateRequiredFields(
    const ::i18n::addressinput::AddressData& address_to_check,
    const std::multimap< ::i18n::addressinput::AddressField,
                         ::i18n::addressinput::AddressProblem>* filter,
    std::multimap< ::i18n::addressinput::AddressField,
                   ::i18n::addressinput::AddressProblem>* problems);

}  
}  

#endif  
