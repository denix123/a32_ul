// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_CDM_JSON_WEB_KEY_H_
#define MEDIA_CDM_JSON_WEB_KEY_H_

#include <string>
#include <utility>
#include <vector>

#include "base/basictypes.h"
#include "media/base/media_export.h"
#include "media/base/media_keys.h"

namespace media {

// The ClearKey license request format (ref:

// The ClearKey license format is a JSON Web Key (JWK) Set containing


typedef std::pair<std::string, std::string> KeyIdAndKeyPair;
typedef std::vector<KeyIdAndKeyPair> KeyIdAndKeyPairs;

MEDIA_EXPORT std::string GenerateJWKSet(const uint8* key, int key_length,
                                        const uint8* key_id, int key_id_length);

MEDIA_EXPORT bool ExtractKeysFromJWKSet(const std::string& jwk_set,
                                        KeyIdAndKeyPairs* keys,
                                        MediaKeys::SessionType* session_type);

// Create a license request message for the |key_id| and |session_type|
// so no need to take a list of |key_id|'s. |license| is updated to contain the
MEDIA_EXPORT void CreateLicenseRequest(const uint8* key_id,
                                       int key_id_length,
                                       MediaKeys::SessionType session_type,
                                       std::vector<uint8>* license);

// Extract the first key from the license request message. Returns true if
// |license| is a valid license request and contains at least one key,
MEDIA_EXPORT bool ExtractFirstKeyIdFromLicenseRequest(
    const std::vector<uint8>& license,
    std::vector<uint8>* first_key);

}  

#endif  
