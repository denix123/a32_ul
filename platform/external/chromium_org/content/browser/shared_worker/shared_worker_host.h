// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_SHARED_WORKER_SHARED_WORKER_HOST_H_
#define CONTENT_BROWSER_SHARED_WORKER_SHARED_WORKER_HOST_H_

#include <list>
#include <vector>

#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/strings/string16.h"
#include "base/time/time.h"
#include "content/browser/shared_worker/shared_worker_message_filter.h"
#include "content/browser/shared_worker/worker_document_set.h"

class GURL;

namespace IPC {
class Message;
}

namespace content {
class SharedWorkerMessageFilter;
class SharedWorkerInstance;

class SharedWorkerHost {
 public:
  SharedWorkerHost(SharedWorkerInstance* instance,
                   SharedWorkerMessageFilter* filter,
                   int worker_route_id);
  ~SharedWorkerHost();

  
  bool Send(IPC::Message* message);

  
  
  void Start(bool pause_on_start);

  
  
  bool FilterMessage(const IPC::Message& message,
                     SharedWorkerMessageFilter* filter);

  
  
  void FilterShutdown(SharedWorkerMessageFilter* filter);

  
  
  void DocumentDetached(SharedWorkerMessageFilter* filter,
                        unsigned long long document_id);

  void WorkerContextClosed();
  void WorkerReadyForInspection();
  void WorkerScriptLoaded();
  void WorkerScriptLoadFailed();
  void WorkerConnected(int message_port_id);
  void WorkerContextDestroyed();
  void AllowDatabase(const GURL& url,
                     const base::string16& name,
                     const base::string16& display_name,
                     unsigned long estimated_size,
                     bool* result);
  void AllowFileSystem(const GURL& url, scoped_ptr<IPC::Message> reply_msg);
  void AllowIndexedDB(const GURL& url,
                      const base::string16& name,
                      bool* result);

  
  void TerminateWorker();

  void AddFilter(SharedWorkerMessageFilter* filter, int route_id);

  SharedWorkerInstance* instance() { return instance_.get(); }
  WorkerDocumentSet* worker_document_set() const {
    return worker_document_set_.get();
  }
  SharedWorkerMessageFilter* container_render_filter() const {
    return container_render_filter_;
  }
  int process_id() const { return worker_process_id_; }
  int worker_route_id() const { return worker_route_id_; }
  bool load_failed() const { return load_failed_; }
  bool closed() const { return closed_; }

 private:
  
  class FilterInfo {
   public:
    FilterInfo(SharedWorkerMessageFilter* filter, int route_id)
        : filter_(filter), route_id_(route_id), message_port_id_(0) {}
    SharedWorkerMessageFilter* filter() const { return filter_; }
    int route_id() const { return route_id_; }
    int message_port_id() const { return message_port_id_; }
    void set_message_port_id(int id) { message_port_id_ = id; }

   private:
    SharedWorkerMessageFilter* filter_;
    int route_id_;
    int message_port_id_;
  };

  typedef std::list<FilterInfo> FilterList;

  
  
  void RelayMessage(const IPC::Message& message,
                    SharedWorkerMessageFilter* incoming_filter);

  
  std::vector<std::pair<int, int> > GetRenderFrameIDsForWorker();

  void RemoveFilters(SharedWorkerMessageFilter* filter);
  bool HasFilter(SharedWorkerMessageFilter* filter, int route_id) const;
  void SetMessagePortID(SharedWorkerMessageFilter* filter,
                        int route_id,
                        int message_port_id);
  void AllowFileSystemResponse(scoped_ptr<IPC::Message> reply_msg,
                               bool allowed);
  scoped_ptr<SharedWorkerInstance> instance_;
  scoped_refptr<WorkerDocumentSet> worker_document_set_;
  FilterList filters_;
  SharedWorkerMessageFilter* container_render_filter_;
  int worker_process_id_;
  int worker_route_id_;
  bool load_failed_;
  bool closed_;
  const base::TimeTicks creation_time_;

  base::WeakPtrFactory<SharedWorkerHost> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(SharedWorkerHost);
};
}  

#endif  
