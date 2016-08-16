// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_CHROMEOS_NETWORK_NETWORK_ICON_H_
#define UI_CHROMEOS_NETWORK_NETWORK_ICON_H_

#include <string>

#include "base/strings/string16.h"
#include "ui/chromeos/ui_chromeos_export.h"
#include "ui/gfx/image/image_skia.h"

namespace chromeos {
class NetworkState;
}

namespace ui {
namespace network_icon {

class AnimationObserver;

enum IconType {
  ICON_TYPE_TRAY,  
  ICON_TYPE_DEFAULT_VIEW,  
  ICON_TYPE_LIST,  
};

UI_CHROMEOS_EXPORT gfx::ImageSkia GetImageForNetwork(
    const chromeos::NetworkState* network,
    IconType icon_type);

UI_CHROMEOS_EXPORT std::string GetImageUrlForNetwork(
    const chromeos::NetworkState* network,
    IconType icon_type,
    float scale_factor);

UI_CHROMEOS_EXPORT gfx::ImageSkia GetImageForConnectedNetwork(
    IconType icon_type,
    const std::string& network_type);

UI_CHROMEOS_EXPORT gfx::ImageSkia GetImageForConnectingNetwork(
    IconType icon_type,
    const std::string& network_type);

UI_CHROMEOS_EXPORT gfx::ImageSkia GetImageForDisconnectedNetwork(
    IconType icon_type,
    const std::string& network_type);

UI_CHROMEOS_EXPORT base::string16 GetLabelForNetwork(
    const chromeos::NetworkState* network,
    IconType icon_type);

UI_CHROMEOS_EXPORT int GetCellularUninitializedMsg();

UI_CHROMEOS_EXPORT void GetDefaultNetworkImageAndLabel(IconType icon_type,
                                                       gfx::ImageSkia* image,
                                                       base::string16* label,
                                                       bool* animating);

UI_CHROMEOS_EXPORT void PurgeNetworkIconCache();

}  
}  

#endif  
