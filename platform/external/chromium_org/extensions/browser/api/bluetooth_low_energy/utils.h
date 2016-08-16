// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_API_BLUETOOTH_LOW_ENERGY_UTILS_H_
#define EXTENSIONS_BROWSER_API_BLUETOOTH_LOW_ENERGY_UTILS_H_

#include "base/memory/scoped_ptr.h"
#include "base/values.h"
#include "extensions/common/api/bluetooth_low_energy.h"

namespace extensions {
namespace core_api {
namespace bluetooth_low_energy {


scoped_ptr<base::DictionaryValue> CharacteristicToValue(Characteristic* from);

scoped_ptr<base::DictionaryValue> DescriptorToValue(Descriptor* from);

}  
}  
}  

#endif  
