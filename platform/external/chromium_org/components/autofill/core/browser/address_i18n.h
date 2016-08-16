// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_AUTOFILL_CORE_BROWSER_ADDRESS_I18N_H_
#define COMPONENTS_AUTOFILL_CORE_BROWSER_ADDRESS_I18N_H_

#include "base/callback_forward.h"
#include "base/memory/scoped_ptr.h"
#include "base/strings/string16.h"
#include "components/autofill/core/browser/field_types.h"
#include "third_party/libaddressinput/src/cpp/include/libaddressinput/address_field.h"

namespace i18n {
namespace addressinput {
struct AddressData;
}
}

namespace autofill {

class AutofillProfile;
class AutofillType;

namespace i18n {

scoped_ptr< ::i18n::addressinput::AddressData> CreateAddressData(
    const base::Callback<base::string16(const AutofillType&)>& get_info);

scoped_ptr< ::i18n::addressinput::AddressData>
    CreateAddressDataFromAutofillProfile(const AutofillProfile& profile,
                                         const std::string& app_locale);

ServerFieldType TypeForField(::i18n::addressinput::AddressField field,
                             bool billing);

bool FieldForType(ServerFieldType server_type,
                  ::i18n::addressinput::AddressField* field);

}  
}  

#endif  
