// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_ACCESSIBILITY_AX_AURA_OBJ_CACHE_H_
#define UI_VIEWS_ACCESSIBILITY_AX_AURA_OBJ_CACHE_H_

#include <map>

#include "base/basictypes.h"
#include "ui/views/views_export.h"

template <typename T> struct DefaultSingletonTraits;

namespace aura {
class Window;
}  

namespace views {
class AXAuraObjWrapper;
class View;
class Widget;

class VIEWS_EXPORT AXAuraObjCache {
 public:
  
  static AXAuraObjCache* GetInstance();

  
  AXAuraObjWrapper* GetOrCreate(View* view);
  AXAuraObjWrapper* GetOrCreate(Widget* widget);
  AXAuraObjWrapper* GetOrCreate(aura::Window* window);

  
  int32 GetID(View* view);
  int32 GetID(Widget* widget);
  int32 GetID(aura::Window* window);

  
  
  int32 GetNextID() { return current_id_++; }

  
  void Remove(View* view);
  void Remove(Widget* widget);
  void Remove(aura::Window* window);

  
  AXAuraObjWrapper* Get(int32 id);

  
  void Remove(int32 id);

 private:
  friend struct DefaultSingletonTraits<AXAuraObjCache>;

  AXAuraObjCache();
  virtual ~AXAuraObjCache();

  template <typename AuraViewWrapper, typename AuraView>
      AXAuraObjWrapper* CreateInternal(
          AuraView* aura_view, std::map<AuraView*, int32>& aura_view_to_id_map);

  template<typename AuraView> int32 GetIDInternal(
      AuraView* aura_view, std::map<AuraView*, int32>& aura_view_to_id_map);

  template<typename AuraView> void RemoveInternal(
      AuraView* aura_view, std::map<AuraView*, int32>& aura_view_to_id_map);

  std::map<views::View*, int32> view_to_id_map_;
  std::map<views::Widget*, int32> widget_to_id_map_;
  std::map<aura::Window*, int32> window_to_id_map_;

  std::map<int32, AXAuraObjWrapper*> cache_;
  int32 current_id_;

  DISALLOW_COPY_AND_ASSIGN(AXAuraObjCache);
};

}  

#endif  
