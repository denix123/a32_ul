// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_HOST_TRANSFORMER_HELPER_H_
#define ASH_HOST_TRANSFORMER_HELPER_H_

#include "base/memory/scoped_ptr.h"

namespace gfx {
class Insets;
class Size;
class Transform;
}

namespace ash {
class AshWindowTreeHost;
class RootWindowTransformer;

class TransformerHelper {
 public:
  explicit TransformerHelper(AshWindowTreeHost* ash_host);
  ~TransformerHelper();

  
  
  gfx::Insets GetHostInsets() const;

  
  void SetTransform(const gfx::Transform& transform);

  
  void SetRootWindowTransformer(scoped_ptr<RootWindowTransformer> transformer);

  
  gfx::Transform GetTransform() const;
  gfx::Transform GetInverseTransform() const;

  
  
  void UpdateWindowSize(const gfx::Size& host_size);

 private:
  AshWindowTreeHost* ash_host_;
  scoped_ptr<RootWindowTransformer> transformer_;

  DISALLOW_COPY_AND_ASSIGN(TransformerHelper);
};

}  

#endif  
