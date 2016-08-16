// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_SHELF_SHELF_MODEL_H_
#define ASH_SHELF_SHELF_MODEL_H_

#include "ash/ash_export.h"
#include "ash/shelf/shelf_item_types.h"
#include "base/basictypes.h"
#include "base/observer_list.h"

namespace ash {

class ShelfModelObserver;

class ASH_EXPORT ShelfModel {
 public:
  enum Status {
    STATUS_NORMAL,
    
    STATUS_LOADING,
  };

  ShelfModel();
  ~ShelfModel();

  
  int Add(const ShelfItem& item);

  
  
  int AddAt(int index, const ShelfItem& item);

  
  void RemoveItemAt(int index);

  
  
  void Move(int index, int target_index);

  
  
  void Set(int index, const ShelfItem& item);

  
  int ItemIndexByID(ShelfID id) const;

  
  
  
  int GetItemIndexForType(ShelfItemType type);

  
  
  
  int FirstRunningAppIndex() const;

  
  
  int FirstPanelIndex() const;

  
  ShelfID next_id() const { return next_id_; }

  
  ShelfID reserve_external_id() { return next_id_++; }

  
  
  ShelfItems::const_iterator ItemByID(ShelfID id) const;

  const ShelfItems& items() const { return items_; }
  int item_count() const { return static_cast<int>(items_.size()); }

  void SetStatus(Status status);
  Status status() const { return status_; }

  void AddObserver(ShelfModelObserver* observer);
  void RemoveObserver(ShelfModelObserver* observer);

 private:
  
  
  
  int ValidateInsertionIndex(ShelfItemType type, int index) const;

  
  ShelfID next_id_;

  ShelfItems items_;
  Status status_;
  ObserverList<ShelfModelObserver> observers_;

  DISALLOW_COPY_AND_ASSIGN(ShelfModel);
};

}  

#endif  
