// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_AUTOFILL_AUTOFILL_DIALOG_COMMON_H_
#define CHROME_BROWSER_UI_AUTOFILL_AUTOFILL_DIALOG_COMMON_H_

#include "chrome/browser/ui/autofill/autofill_dialog_types.h"
#include "components/autofill/core/browser/autofill_type.h"
#include "components/autofill/core/browser/field_types.h"

namespace autofill {
class AutofillProfile;
}

namespace wallet {
class Address;
}

namespace autofill {
namespace common {

enum AddressType {
  ADDRESS_TYPE_BILLING,
  ADDRESS_TYPE_SHIPPING,
};

bool ServerTypeEncompassesFieldType(ServerFieldType type,
                                    const AutofillType& field_type);

bool ServerTypeMatchesField(DialogSection section,
                            ServerFieldType type,
                            const AutofillField& field);

bool IsCreditCardType(ServerFieldType type);

void BuildInputs(const DetailInput input_template[],
                 size_t template_size,
                 DetailInputs* inputs);

AutofillMetrics::DialogUiEvent DialogSectionToUiItemAddedEvent(
    DialogSection section);

AutofillMetrics::DialogUiEvent DialogSectionToUiSelectionChangedEvent(
    DialogSection section);

std::vector<ServerFieldType> TypesFromInputs(const DetailInputs& inputs);

}  
}  

#endif  
