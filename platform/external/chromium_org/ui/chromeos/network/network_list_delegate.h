// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_CHROMEOS_NETWORK_NETWORK_LIST_DELEGATE_H_
#define UI_CHROMEOS_NETWORK_NETWORK_LIST_DELEGATE_H_

#include "ui/chromeos/ui_chromeos_export.h"

namespace chromeos {
class NetworkState;
class NetworkTypePattern;
}

namespace views {
class Label;
class View;
}

namespace ui {

struct NetworkInfo;

class UI_CHROMEOS_EXPORT NetworkListDelegate {
 public:
  virtual ~NetworkListDelegate() {}

  
  virtual views::View* CreateViewForNetwork(const NetworkInfo& info) = 0;

  
  
  virtual bool IsViewHovered(views::View* view) = 0;

  
  virtual chromeos::NetworkTypePattern GetNetworkTypePattern() const = 0;

  
  
  virtual void UpdateViewForNetwork(views::View* view,
                                    const NetworkInfo& info) = 0;

  
  
  virtual views::Label* CreateInfoLabel() = 0;

  virtual void RelayoutScrollList() = 0;
};

}  

#endif  
