// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_API_SYSTEM_DISPLAY_DISPLAY_INFO_PROVIDER_H_
#define EXTENSIONS_BROWSER_API_SYSTEM_DISPLAY_DISPLAY_INFO_PROVIDER_H_

#include <string>
#include <vector>

#include "base/macros.h"
#include "base/memory/linked_ptr.h"

namespace gfx {
class Display;
class Screen;
}

namespace extensions {

namespace core_api {
namespace system_display {
struct DisplayProperties;
struct DisplayUnitInfo;
}
}

typedef std::vector<linked_ptr<core_api::system_display::DisplayUnitInfo> >
    DisplayInfo;

class DisplayInfoProvider {
 public:
  virtual ~DisplayInfoProvider();

  
  
  static DisplayInfoProvider* Get();

  
  
  static void InitializeForTesting(DisplayInfoProvider* display_info_provider);

  
  
  
  virtual bool SetInfo(const std::string& display_id,
                       const core_api::system_display::DisplayProperties& info,
                       std::string* error) = 0;

  
  
  virtual gfx::Screen* GetActiveScreen() = 0;

  DisplayInfo GetAllDisplaysInfo();

 protected:
  DisplayInfoProvider();

 private:
  static DisplayInfoProvider* Create();

  
  
  virtual void UpdateDisplayUnitInfoForPlatform(
      const gfx::Display& display,
      core_api::system_display::DisplayUnitInfo* unit) = 0;

  DISALLOW_COPY_AND_ASSIGN(DisplayInfoProvider);
};

}  

#endif  
