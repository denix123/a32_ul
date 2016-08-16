// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SAFE_BROWSING_INCIDENT_REPORTING_MODULE_INTEGRITY_VERIFIER_WIN_H_
#define CHROME_BROWSER_SAFE_BROWSING_INCIDENT_REPORTING_MODULE_INTEGRITY_VERIFIER_WIN_H_

#include <stdint.h>

#include <set>
#include <string>

namespace base {
namespace win {
class PEImage;
class PEImageAsData;
}  
}  

namespace safe_browsing {

enum ModuleState {
  MODULE_STATE_UNKNOWN,
  MODULE_STATE_UNMODIFIED,
  MODULE_STATE_MODIFIED,
};

bool GetCodeAddrsAndSize(const base::win::PEImage& mem_peimage,
                         const base::win::PEImageAsData& disk_peimage,
                         uint8_t** mem_code_addr,
                         uint8_t** disk_code_addr,
                         uint32_t* code_size);

ModuleState VerifyModule(const wchar_t* module_name,
                         std::set<std::string>* modified_exports);

}  

#endif  
