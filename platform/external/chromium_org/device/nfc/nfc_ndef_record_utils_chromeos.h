// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/values.h"
#include "chromeos/dbus/nfc_record_client.h"

#ifndef DEVICE_NFC_CHROMEOS_NDEF_RECORD_UTILS_CHROMEOS_H_
#define DEVICE_NFC_CHROMEOS_NDEF_RECORD_UTILS_CHROMEOS_H_

namespace device {
class NfcNdefRecord;
}  

namespace chromeos {
namespace nfc_ndef_record_utils {

bool NfcNdefRecordToDBusAttributes(
    const device::NfcNdefRecord* record,
    base::DictionaryValue* out);

bool RecordPropertiesToNfcNdefRecord(
    const NfcRecordClient::Properties* properties,
    device::NfcNdefRecord* out);

}  
}  

#endif  
