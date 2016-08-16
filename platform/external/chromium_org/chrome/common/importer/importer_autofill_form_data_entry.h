// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_COMMON_IMPORTER_IMPORTER_AUTOFILL_FORM_DATA_ENTRY_H_
#define CHROME_COMMON_IMPORTER_IMPORTER_AUTOFILL_FORM_DATA_ENTRY_H_

#include "base/strings/string16.h"
#include "base/time/time.h"

struct ImporterAutofillFormDataEntry {
  ImporterAutofillFormDataEntry();
  ~ImporterAutofillFormDataEntry();

  
  base::string16 name;

  
  base::string16 value;

  
  int times_used;

  
  base::Time first_used;

  
  base::Time last_used;
};

#endif  
