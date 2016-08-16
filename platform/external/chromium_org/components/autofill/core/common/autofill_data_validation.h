// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_AUTOFILL_CORE_COMMON_AUTOFILL_DATA_VALIDATION_H_
#define COMPONENTS_AUTOFILL_CORE_COMMON_AUTOFILL_DATA_VALIDATION_H_

#include <string>
#include <vector>

#include "base/strings/string16.h"

class GURL;

namespace autofill {

struct FormData;
struct FormFieldData;
struct PasswordFormFillData;


extern const size_t kMaxDataLength;

extern const size_t kMaxListSize;

bool IsValidString(const std::string& str);
bool IsValidString16(const base::string16& str);
bool IsValidGURL(const GURL& url);
bool IsValidFormFieldData(const FormFieldData& field);
bool IsValidFormData(const FormData& form);
bool IsValidPasswordFormFillData(const PasswordFormFillData& form);
bool IsValidString16Vector(const std::vector<base::string16>& v);
bool IsValidFormDataVector(const std::vector<FormData>& v);

}  

#endif  
