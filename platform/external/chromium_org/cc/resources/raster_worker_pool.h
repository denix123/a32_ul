// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CC_RESOURCES_RASTER_WORKER_POOL_H_
#define CC_RESOURCES_RASTER_WORKER_POOL_H_

#include "cc/resources/rasterizer.h"
#include "ui/gfx/geometry/size.h"

namespace base {
class SequencedTaskRunner;
}

namespace cc {

class CC_EXPORT RasterWorkerPool {
 public:
  static unsigned kBenchmarkRasterTaskPriority;
  static unsigned kRasterFinishedTaskPriority;
  static unsigned kRasterTaskPriorityBase;

  RasterWorkerPool();
  virtual ~RasterWorkerPool();

  
  
  
  static void SetNumRasterThreads(int num_threads);

  
  static int GetNumRasterThreads();

  
  static TaskGraphRunner* GetTaskGraphRunner();

  
  
  static scoped_refptr<RasterizerTask> CreateRasterFinishedTask(
      base::SequencedTaskRunner* task_runner,
      const base::Closure& callback);

  
  
  static void ScheduleTasksOnOriginThread(RasterizerTaskClient* client,
                                          TaskGraph* graph);

  
  
  
  static void InsertNodeForTask(TaskGraph* graph,
                                RasterizerTask* task,
                                unsigned priority,
                                size_t dependencies);

  
  
  static void InsertNodesForRasterTask(
      TaskGraph* graph,
      RasterTask* task,
      const ImageDecodeTask::Vector& decode_tasks,
      unsigned priority);

  
  
  static void AcquireBitmapForBuffer(SkBitmap* bitmap,
                                     uint8_t* buffer,
                                     ResourceFormat format,
                                     const gfx::Size& size,
                                     int stride);
  static void ReleaseBitmapForBuffer(SkBitmap* bitmap,
                                     uint8_t* buffer,
                                     ResourceFormat format);

  
  virtual Rasterizer* AsRasterizer() = 0;
};

}  

#endif  
