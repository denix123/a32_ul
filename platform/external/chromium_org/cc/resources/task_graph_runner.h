// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CC_RESOURCES_TASK_GRAPH_RUNNER_H_
#define CC_RESOURCES_TASK_GRAPH_RUNNER_H_

#include <map>
#include <vector>

#include "base/logging.h"
#include "base/memory/ref_counted.h"
#include "base/synchronization/condition_variable.h"
#include "cc/base/cc_export.h"

namespace cc {

class CC_EXPORT Task : public base::RefCountedThreadSafe<Task> {
 public:
  typedef std::vector<scoped_refptr<Task> > Vector;

  virtual void RunOnWorkerThread() = 0;

  void WillRun();
  void DidRun();
  bool HasFinishedRunning() const;

 protected:
  friend class base::RefCountedThreadSafe<Task>;

  Task();
  virtual ~Task();

  bool will_run_;
  bool did_run_;
};

struct CC_EXPORT TaskGraph {
  struct Node {
    class TaskComparator {
     public:
      explicit TaskComparator(const Task* task) : task_(task) {}

      bool operator()(const Node& node) const { return node.task == task_; }

     private:
      const Task* task_;
    };

    typedef std::vector<Node> Vector;

    Node(Task* task, unsigned priority, size_t dependencies)
        : task(task), priority(priority), dependencies(dependencies) {}

    Task* task;
    unsigned priority;
    size_t dependencies;
  };

  struct Edge {
    typedef std::vector<Edge> Vector;

    Edge(const Task* task, Task* dependent)
        : task(task), dependent(dependent) {}

    const Task* task;
    Task* dependent;
  };

  TaskGraph();
  ~TaskGraph();

  void Swap(TaskGraph* other);
  void Reset();

  Node::Vector nodes;
  Edge::Vector edges;
};

class TaskGraphRunner;

class CC_EXPORT NamespaceToken {
 public:
  NamespaceToken() : id_(0) {}
  ~NamespaceToken() {}

  bool IsValid() const { return id_ != 0; }

 private:
  friend class TaskGraphRunner;

  explicit NamespaceToken(int id) : id_(id) {}

  int id_;
};

class CC_EXPORT TaskGraphRunner {
 public:
  TaskGraphRunner();
  virtual ~TaskGraphRunner();

  
  
  NamespaceToken GetNamespaceToken();

  
  
  
  
  
  void ScheduleTasks(NamespaceToken token, TaskGraph* graph);

  
  void WaitForTasksToFinishRunning(NamespaceToken token);

  
  void CollectCompletedTasks(NamespaceToken token,
                             Task::Vector* completed_tasks);

  
  void Run();

  
  
  void RunUntilIdle();

  
  
  
  void Shutdown();

 private:
  struct PrioritizedTask {
    typedef std::vector<PrioritizedTask> Vector;

    PrioritizedTask(Task* task, unsigned priority)
        : task(task), priority(priority) {}

    Task* task;
    unsigned priority;
  };

  typedef std::vector<const Task*> TaskVector;

  struct TaskNamespace {
    typedef std::vector<TaskNamespace*> Vector;

    TaskNamespace();
    ~TaskNamespace();

    
    TaskGraph graph;

    
    PrioritizedTask::Vector ready_to_run_tasks;

    
    Task::Vector completed_tasks;

    
    TaskVector running_tasks;
  };

  typedef std::map<int, TaskNamespace> TaskNamespaceMap;

  static bool CompareTaskPriority(const PrioritizedTask& a,
                                  const PrioritizedTask& b) {
    
    return a.priority > b.priority;
  }

  static bool CompareTaskNamespacePriority(const TaskNamespace* a,
                                           const TaskNamespace* b) {
    DCHECK(!a->ready_to_run_tasks.empty());
    DCHECK(!b->ready_to_run_tasks.empty());

    
    
    
    return CompareTaskPriority(a->ready_to_run_tasks.front(),
                               b->ready_to_run_tasks.front());
  }

  static bool HasFinishedRunningTasksInNamespace(
      const TaskNamespace* task_namespace) {
    return task_namespace->running_tasks.empty() &&
           task_namespace->ready_to_run_tasks.empty();
  }

  
  
  void RunTaskWithLockAcquired();

  
  
  mutable base::Lock lock_;

  
  
  base::ConditionVariable has_ready_to_run_tasks_cv_;

  
  
  base::ConditionVariable has_namespaces_with_finished_running_tasks_cv_;

  
  int next_namespace_id_;

  
  
  TaskNamespaceMap namespaces_;

  
  TaskNamespace::Vector ready_to_run_namespaces_;

  
  bool shutdown_;

  DISALLOW_COPY_AND_ASSIGN(TaskGraphRunner);
};

}  

#endif  
