// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_COCOA_ACCELERATORS_COCOA_H_
#define CHROME_BROWSER_UI_COCOA_ACCELERATORS_COCOA_H_

#import <Cocoa/Cocoa.h>

#include <map>
#include <vector>

#include "base/gtest_prod_util.h"
#include "ui/base/accelerators/accelerator.h"

template <typename T> struct DefaultSingletonTraits;

class AcceleratorsCocoa {
 public:
  typedef std::map<int, ui::Accelerator> AcceleratorMap;
  typedef std::vector<ui::Accelerator> AcceleratorVector;
  typedef AcceleratorMap::const_iterator const_iterator;

  const_iterator const begin() { return accelerators_.begin(); }
  const_iterator const end() { return accelerators_.end(); }

  
  const ui::Accelerator* GetAcceleratorForCommand(int command_id);
  
  
  const ui::Accelerator* GetAcceleratorForHotKey(NSString* key_equivalent,
                                                 NSUInteger modifiers) const;

  
  static AcceleratorsCocoa* GetInstance();

 private:
  friend struct DefaultSingletonTraits<AcceleratorsCocoa>;
  FRIEND_TEST_ALL_PREFIXES(AcceleratorsCocoaBrowserTest,
                           MappingAcceleratorsInMainMenu);

  AcceleratorsCocoa();
  ~AcceleratorsCocoa();

  
  
  
  AcceleratorMap accelerators_;
  
  
  
  AcceleratorVector accelerator_vector_;

  DISALLOW_COPY_AND_ASSIGN(AcceleratorsCocoa);
};

#endif  
