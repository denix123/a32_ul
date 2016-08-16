// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CC_RESOURCES_RASTERIZER_H_
#define CC_RESOURCES_RASTERIZER_H_

#include <bitset>
#include <vector>

#include "base/callback.h"
#include "cc/resources/resource_format.h"
#include "cc/resources/task_graph_runner.h"

namespace cc {
class ImageDecodeTask;
class RasterTask;
class Resource;
class RasterBuffer;

class CC_EXPORT RasterizerTaskClient {
 public:
  virtual scoped_ptr<RasterBuffer> AcquireBufferForRaster(
      const Resource* resource) = 0;
  virtual void ReleaseBufferForRaster(scoped_ptr<RasterBuffer> buffer) = 0;

 protected:
  virtual ~RasterizerTaskClient() {}
};

class CC_EXPORT RasterizerTask : public Task {
 public:
  typedef std::vector<scoped_refptr<RasterizerTask> > Vector;

  virtual void ScheduleOnOriginThread(RasterizerTaskClient* client) = 0;
  virtual void CompleteOnOriginThread(RasterizerTaskClient* client) = 0;
  virtual void RunReplyOnOriginThread() = 0;

  
  virtual ImageDecodeTask* AsImageDecodeTask();
  virtual RasterTask* AsRasterTask();

  void WillSchedule();
  void DidSchedule();
  bool HasBeenScheduled() const;

  void WillComplete();
  void DidComplete();
  bool HasCompleted() const;

 protected:
  RasterizerTask();
  virtual ~RasterizerTask();

  bool did_schedule_;
  bool did_complete_;
};

class CC_EXPORT ImageDecodeTask : public RasterizerTask {
 public:
  typedef std::vector<scoped_refptr<ImageDecodeTask> > Vector;

  
  virtual ImageDecodeTask* AsImageDecodeTask() OVERRIDE;

 protected:
  ImageDecodeTask();
  virtual ~ImageDecodeTask();
};

class CC_EXPORT RasterTask : public RasterizerTask {
 public:
  typedef std::vector<scoped_refptr<RasterTask> > Vector;

  
  virtual RasterTask* AsRasterTask() OVERRIDE;

  const Resource* resource() const { return resource_; }
  const ImageDecodeTask::Vector& dependencies() const { return dependencies_; }

 protected:
  RasterTask(const Resource* resource, ImageDecodeTask::Vector* dependencies);
  virtual ~RasterTask();

 private:
  const Resource* resource_;
  ImageDecodeTask::Vector dependencies_;
};

static const size_t kNumberOfTaskSets = 2;
typedef size_t TaskSet;
typedef std::bitset<kNumberOfTaskSets> TaskSetCollection;

class CC_EXPORT RasterizerClient {
 public:
  virtual void DidFinishRunningTasks(TaskSet task_set) = 0;
  virtual TaskSetCollection TasksThatShouldBeForcedToComplete() const = 0;

 protected:
  virtual ~RasterizerClient() {}
};

struct CC_EXPORT RasterTaskQueue {
  struct CC_EXPORT Item {
    class TaskComparator {
     public:
      explicit TaskComparator(const RasterTask* task) : task_(task) {}

      bool operator()(const Item& item) const { return item.task == task_; }

     private:
      const RasterTask* task_;
    };

    typedef std::vector<Item> Vector;

    Item(RasterTask* task, const TaskSetCollection& task_sets);
    ~Item();

    RasterTask* task;
    TaskSetCollection task_sets;
  };

  RasterTaskQueue();
  ~RasterTaskQueue();

  void Swap(RasterTaskQueue* other);
  void Reset();

  Item::Vector items;
};

class CC_EXPORT Rasterizer {
 public:
  
  virtual void SetClient(RasterizerClient* client) = 0;

  
  
  
  virtual void Shutdown() = 0;

  
  
  
  
  
  virtual void ScheduleTasks(RasterTaskQueue* queue) = 0;

  
  virtual void CheckForCompletedTasks() = 0;

 protected:
  virtual ~Rasterizer() {}
};

}  

#endif  
