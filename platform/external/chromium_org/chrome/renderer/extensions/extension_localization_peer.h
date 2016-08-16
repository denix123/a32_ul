// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_RENDERER_EXTENSIONS_EXTENSION_LOCALIZATION_PEER_H_
#define CHROME_RENDERER_EXTENSIONS_EXTENSION_LOCALIZATION_PEER_H_

#include <string>

#include "content/public/child/request_peer.h"
#include "content/public/common/resource_response_info.h"

namespace IPC {
class Sender;
}

class ExtensionLocalizationPeer : public content::RequestPeer {
 public:
  virtual ~ExtensionLocalizationPeer();

  static ExtensionLocalizationPeer* CreateExtensionLocalizationPeer(
      content::RequestPeer* peer,
      IPC::Sender* message_sender,
      const std::string& mime_type,
      const GURL& request_url);

  
  virtual void OnUploadProgress(uint64 position, uint64 size) OVERRIDE;
  virtual bool OnReceivedRedirect(
      const net::RedirectInfo& redirect_info,
      const content::ResourceResponseInfo& info) OVERRIDE;
  virtual void OnReceivedResponse(
      const content::ResourceResponseInfo& info) OVERRIDE;
  virtual void OnDownloadedData(int len, int encoded_data_length) OVERRIDE {}
  virtual void OnReceivedData(const char* data,
                              int data_length,
                              int encoded_data_length) OVERRIDE;
  virtual void OnCompletedRequest(int error_code,
                                  bool was_ignored_by_handler,
                                  bool stale_copy_in_cache,
                                  const std::string& security_info,
                                  const base::TimeTicks& completion_time,
                                  int64 total_transfer_size) OVERRIDE;

 private:
  friend class ExtensionLocalizationPeerTest;

  
  ExtensionLocalizationPeer(content::RequestPeer* peer,
                            IPC::Sender* message_sender,
                            const GURL& request_url);

  
  
  void ReplaceMessages();

  
  content::RequestPeer* original_peer_;

  
  content::ResourceResponseInfo response_info_;

  
  
  IPC::Sender* message_sender_;

  
  std::string data_;

  
  GURL request_url_;

 private:
  DISALLOW_COPY_AND_ASSIGN(ExtensionLocalizationPeer);
};

#endif  
