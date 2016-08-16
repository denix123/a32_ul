// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CC_DEBUG_INVALIDATION_BENCHMARK_H_
#define CC_DEBUG_INVALIDATION_BENCHMARK_H_

#include <string>

#include "cc/debug/micro_benchmark_controller.h"

namespace cc {

class LayerTreeHost;
class Layer;
class CC_EXPORT InvalidationBenchmark : public MicroBenchmark {
 public:
  explicit InvalidationBenchmark(scoped_ptr<base::Value> value,
                                 const MicroBenchmark::DoneCallback& callback);
  virtual ~InvalidationBenchmark();

  
  virtual void DidUpdateLayers(LayerTreeHost* host) OVERRIDE;
  virtual void RunOnLayer(PictureLayer* layer) OVERRIDE;
  virtual bool ProcessMessage(scoped_ptr<base::Value> value) OVERRIDE;

 private:
  enum Mode { FIXED_SIZE, LAYER, VIEWPORT, RANDOM };

  void Run(Layer* layer);
  float LCGRandom();

  Mode mode_;
  int width_;
  int height_;
  uint32 seed_;
};

}  

#endif  
