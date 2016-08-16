// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_COMPONENT_UPDATER_COMPONENT_UPDATER_RESOURCE_THROTTLE_H_
#define CHROME_BROWSER_COMPONENT_UPDATER_COMPONENT_UPDATER_RESOURCE_THROTTLE_H_

#include <string>

namespace content {
class ResourceThrottle;
}

namespace component_updater {

class ComponentUpdateService;

content::ResourceThrottle* GetOnDemandResourceThrottle(
    ComponentUpdateService* cus,
    const std::string& crx_id);

}  

#endif  
