// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_CHROMEOS_NETWORK_NETWORK_LIST_H_
#define UI_CHROMEOS_NETWORK_NETWORK_LIST_H_

#include <map>
#include <set>
#include <string>

#include "chromeos/network/network_state_handler.h"
#include "ui/chromeos/network/network_icon_animation_observer.h"
#include "ui/chromeos/ui_chromeos_export.h"
#include "ui/gfx/image/image_skia.h"

namespace views {
class Label;
class View;
}

namespace ui {

struct NetworkInfo;
class NetworkListDelegate;

class UI_CHROMEOS_EXPORT NetworkListView
    : public network_icon::AnimationObserver {
 public:
  explicit NetworkListView(NetworkListDelegate* delegate);
  virtual ~NetworkListView();

  void UpdateNetworkList();

  
  
  
  bool IsViewInList(views::View* view, std::string* service_path) const;

  void set_content_view(views::View* content) { content_ = content; }

 private:
  void UpdateNetworks(
      const chromeos::NetworkStateHandler::NetworkStateList& networks);
  void UpdateNetworkListInternal();
  bool UpdateNetworkListEntries(std::set<std::string>* new_service_paths);
  bool UpdateNetworkChild(int index, const NetworkInfo* info);
  bool PlaceViewAtIndex(views::View* view, int index);
  bool UpdateInfoLabel(int message_id, int index, views::Label** label);

  
  virtual void NetworkIconChanged() OVERRIDE;

  NetworkListDelegate* delegate_;
  views::View* content_;

  views::Label* scanning_view_;
  views::Label* no_wifi_networks_view_;
  views::Label* no_cellular_networks_view_;

  
  ScopedVector<NetworkInfo> network_list_;

  typedef std::map<views::View*, std::string> NetworkMap;
  NetworkMap network_map_;

  
  typedef std::map<std::string, views::View*> ServicePathMap;
  ServicePathMap service_path_map_;

  DISALLOW_COPY_AND_ASSIGN(NetworkListView);
};

}  

#endif  
