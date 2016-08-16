// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_CULL_SET_H_
#define UI_VIEWS_CULL_SET_H_

#include "base/containers/hash_tables.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "ui/views/views_export.h"

namespace views {

class View;

class VIEWS_EXPORT CullSet {
 public:
  
  
  CullSet();
  ~CullSet();

  
  
  
  CullSet(scoped_ptr<base::hash_set<intptr_t> > cull_set);

  
  bool ShouldPaint(const View* view) const;

 private:
  friend class BoundsTreeTestView;

  
  
  scoped_ptr<base::hash_set<intptr_t> > cull_set_;

  DISALLOW_COPY_AND_ASSIGN(CullSet);
};

}  

#endif  
