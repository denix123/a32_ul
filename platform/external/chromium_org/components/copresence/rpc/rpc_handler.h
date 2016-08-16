// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_COPRESENCE_RPC_RPC_HANDLER_H_
#define COMPONENTS_COPRESENCE_RPC_RPC_HANDLER_H_

#include <set>
#include <string>
#include <vector>

#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "components/copresence/proto/enums.pb.h"
#include "components/copresence/public/copresence_delegate.h"
#include "components/copresence/public/whispernet_client.h"
#include "components/copresence/rpc/http_post.h"
#include "components/copresence/timed_map.h"

namespace copresence {

class DirectiveHandler;
class ReportRequest;
class RequestHeader;
class SubscribedMessage;

class RpcHandler {
 public:
  
  typedef base::Callback<void(bool)> SuccessCallback;

  
  static const char kReportRequestRpcName[];

  
  
  explicit RpcHandler(CopresenceDelegate* delegate);

  virtual ~RpcHandler();

  
  
  void Initialize(const SuccessCallback& init_done_callback);

  
  void SendReportRequest(scoped_ptr<ReportRequest> request);
  void SendReportRequest(scoped_ptr<ReportRequest> request,
                         const std::string& app_id,
                         const StatusCallback& callback);

  
  void ReportTokens(const std::vector<AudioToken>& tokens);

  
  
  void ConnectToWhispernet();

 private:
  
  
  typedef base::Callback<void(HttpPost*, int, const std::string&)>
      PostCleanupCallback;

  
  
  
  
  
  
  
  typedef base::Callback<void(net::URLRequestContextGetter*,
                              const std::string&,
                              scoped_ptr<google::protobuf::MessageLite>,
                              const PostCleanupCallback&)> PostCallback;

  friend class RpcHandlerTest;

  void RegisterResponseHandler(const SuccessCallback& init_done_callback,
                               HttpPost* completed_post,
                               int http_status_code,
                               const std::string& response_data);
  void ReportResponseHandler(const StatusCallback& status_callback,
                             HttpPost* completed_post,
                             int http_status_code,
                             const std::string& response_data);

  
  
  void ProcessRemovedOperations(const ReportRequest& request);

  
  
  
  void AddPlayingTokens(ReportRequest* request);

  void DispatchMessages(
      const google::protobuf::RepeatedPtrField<SubscribedMessage>&
      subscribed_messages);

  RequestHeader* CreateRequestHeader(const std::string& client_name) const;

  template <class T>
  void SendServerRequest(const std::string& rpc_name,
                         const std::string& app_id,
                         scoped_ptr<T> request,
                         const PostCleanupCallback& response_handler);

  
  
  void SendHttpPost(net::URLRequestContextGetter* url_context_getter,
                    const std::string& rpc_name,
                    scoped_ptr<google::protobuf::MessageLite> request_proto,
                    const PostCleanupCallback& callback);

  
  
  void AudioDirectiveListToWhispernetConnector(
      const std::string& token,
      bool audible,
      const WhispernetClient::SamplesCallback& samples_callback);

  CopresenceDelegate* delegate_;  
  TimedMap<std::string, bool> invalid_audio_token_cache_;
  PostCallback server_post_callback_;

  std::string device_id_;
  scoped_ptr<DirectiveHandler> directive_handler_;
  std::set<HttpPost*> pending_posts_;

  DISALLOW_COPY_AND_ASSIGN(RpcHandler);
};

}  

#endif  
