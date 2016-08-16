// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef CONTENT_CHILD_RESOURCE_DISPATCHER_H_
#define CONTENT_CHILD_RESOURCE_DISPATCHER_H_

#include <deque>
#include <string>

#include "base/containers/hash_tables.h"
#include "base/memory/linked_ptr.h"
#include "base/memory/shared_memory.h"
#include "base/memory/weak_ptr.h"
#include "base/time/time.h"
#include "content/common/content_export.h"
#include "content/public/common/resource_type.h"
#include "ipc/ipc_listener.h"
#include "ipc/ipc_sender.h"
#include "net/base/request_priority.h"
#include "url/gurl.h"

struct ResourceMsg_RequestCompleteData;

namespace blink {
class WebThreadedDataReceiver;
}

namespace net {
struct RedirectInfo;
}

namespace content {
class RequestPeer;
class ResourceDispatcherDelegate;
class ResourceLoaderBridge;
class ThreadedDataProvider;
struct ResourceResponseInfo;
struct RequestInfo;
struct ResourceResponseHead;
struct SiteIsolationResponseMetaData;

class CONTENT_EXPORT ResourceDispatcher : public IPC::Listener {
 public:
  explicit ResourceDispatcher(IPC::Sender* sender);
  virtual ~ResourceDispatcher();

  
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;

  
  
  
  virtual ResourceLoaderBridge* CreateBridge(const RequestInfo& request_info);

  
  
  int AddPendingRequest(RequestPeer* callback,
                        ResourceType resource_type,
                        int origin_pid,
                        const GURL& frame_origin,
                        const GURL& request_url,
                        bool download_to_file);

  
  
  bool RemovePendingRequest(int request_id);

  
  
  void CancelPendingRequest(int request_id);

  
  void SetDefersLoading(int request_id, bool value);

  
  void DidChangePriority(int request_id,
                         net::RequestPriority new_priority,
                         int intra_priority_value);

  
  
  bool AttachThreadedDataReceiver(
      int request_id, blink::WebThreadedDataReceiver* threaded_data_receiver);

  IPC::Sender* message_sender() const { return message_sender_; }

  
  
  void set_delegate(ResourceDispatcherDelegate* delegate) {
    delegate_ = delegate;
  }

  
  void set_io_timestamp(base::TimeTicks io_timestamp) {
    io_timestamp_ = io_timestamp;
  }

 private:
  friend class ResourceDispatcherTest;

  typedef std::deque<IPC::Message*> MessageQueue;
  struct PendingRequestInfo {
    PendingRequestInfo();

    PendingRequestInfo(RequestPeer* peer,
                       ResourceType resource_type,
                       int origin_pid,
                       const GURL& frame_origin,
                       const GURL& request_url,
                       bool download_to_file);

    ~PendingRequestInfo();

    RequestPeer* peer;
    ThreadedDataProvider* threaded_data_provider;
    ResourceType resource_type;
    
    
    
    int origin_pid;
    MessageQueue deferred_message_queue;
    bool is_deferred;
    
    GURL url;
    
    GURL frame_origin;
    
    GURL response_url;
    bool download_to_file;
    linked_ptr<IPC::Message> pending_redirect_message;
    base::TimeTicks request_start;
    base::TimeTicks response_start;
    base::TimeTicks completion_time;
    linked_ptr<base::SharedMemory> buffer;
    linked_ptr<SiteIsolationResponseMetaData> site_isolation_metadata;
    bool blocked_response;
    int buffer_size;
  };
  typedef base::hash_map<int, PendingRequestInfo> PendingRequestList;

  
  
  PendingRequestInfo* GetPendingRequestInfo(int request_id);

  
  void FollowPendingRedirect(int request_id, PendingRequestInfo& request_info);

  
  void OnUploadProgress(int request_id, int64 position, int64 size);
  void OnReceivedResponse(int request_id, const ResourceResponseHead&);
  void OnReceivedCachedMetadata(int request_id, const std::vector<char>& data);
  void OnReceivedRedirect(int request_id,
                          const net::RedirectInfo& redirect_info,
                          const ResourceResponseHead& response_head);
  void OnSetDataBuffer(int request_id,
                       base::SharedMemoryHandle shm_handle,
                       int shm_size,
                       base::ProcessId renderer_pid);
  void OnReceivedData(int request_id,
                      int data_offset,
                      int data_length,
                      int encoded_data_length);
  void OnDownloadedData(int request_id, int data_len, int encoded_data_length);
  void OnRequestComplete(
      int request_id,
      const ResourceMsg_RequestCompleteData& request_complete_data);

  
  void DispatchMessage(const IPC::Message& message);

  
  
  void FlushDeferredMessages(int request_id);

  void ToResourceResponseInfo(const PendingRequestInfo& request_info,
                              const ResourceResponseHead& browser_info,
                              ResourceResponseInfo* renderer_info) const;

  base::TimeTicks ToRendererCompletionTime(
      const PendingRequestInfo& request_info,
      const base::TimeTicks& browser_completion_time) const;

  
  
  
  base::TimeTicks ConsumeIOTimestamp();

  
  static bool IsResourceDispatcherMessage(const IPC::Message& message);

  
  
  
  
  static void ReleaseResourcesInDataMessage(const IPC::Message& message);

  
  
  
  static void ReleaseResourcesInMessageQueue(MessageQueue* queue);

  IPC::Sender* message_sender_;

  
  PendingRequestList pending_requests_;

  ResourceDispatcherDelegate* delegate_;

  
  base::TimeTicks io_timestamp_;

  base::WeakPtrFactory<ResourceDispatcher> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(ResourceDispatcher);
};

}  

#endif  
