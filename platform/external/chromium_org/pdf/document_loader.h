// Copyright (c) 2010 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PDF_DOCUMENT_LOADER_H_
#define PDF_DOCUMENT_LOADER_H_

#include <list>
#include <string>
#include <vector>

#include "base/basictypes.h"
#include "pdf/chunk_stream.h"
#include "ppapi/cpp/url_loader.h"
#include "ppapi/utility/completion_callback_factory.h"

#define kDefaultRequestSize 32768u

namespace chrome_pdf {

class DocumentLoader {
 public:
  class Client {
  public:
    
    virtual pp::Instance* GetPluginInstance() = 0;
    
    virtual pp::URLLoader CreateURLLoader() = 0;
    
    
    
    virtual void OnPartialDocumentLoaded() = 0;
    
    virtual void OnPendingRequestComplete() = 0;
    
    virtual void OnNewDataAvailable() = 0;
    
    virtual void OnDocumentComplete() = 0;
  };

  explicit DocumentLoader(Client* client);
  virtual ~DocumentLoader();

  bool Init(const pp::URLLoader& loader,
            const std::string& url,
            const std::string& headers);

  
  bool GetBlock(uint32 position, uint32 size, void* buf) const;

  
  bool IsDataAvailable(uint32 position, uint32 size) const;

  
  void RequestData(uint32 position, uint32 size);

  bool IsDocumentComplete() const;
  uint32 document_size() const { return document_size_; }

  
  uint32 GetAvailableData() const;

  
  void ClearPendingRequests();

  bool is_partial_document() { return partial_document_; }

 private:
  
  void DidOpen(int32_t result);
  
  void ReadMore();
  
  void DidRead(int32_t result);

  
  
  
  
  
  static bool GetByteRange(const std::string& headers, uint32* start,
                           uint32* end);

  
  
  static std::string GetMultiPartBoundary(const std::string& headers);

  
  void LoadPartialDocument();
  
  void LoadFullDocument();
  
  void DownloadPendingRequests();
  
  void ReadComplete();
  
  pp::URLRequestInfo GetRequest(uint32 position, uint32 size) const;
  
  uint32 GetRequestSize() const;

  Client* client_;
  std::string url_;
  pp::URLLoader loader_;
  pp::CompletionCallbackFactory<DocumentLoader> loader_factory_;
  ChunkStream chunk_stream_;
  bool partial_document_;
  bool request_pending_;
  typedef std::list<std::pair<size_t, size_t> > PendingRequests;
  PendingRequests pending_requests_;
  char buffer_[kDefaultRequestSize];
  uint32 current_pos_;
  uint32 current_chunk_size_;
  uint32 current_chunk_read_;
  uint32 document_size_;
  bool header_request_;
  bool is_multipart_;
  std::string multipart_boundary_;
  uint32 requests_count_;
  std::list<std::vector<unsigned char> > chunk_buffer_;
};

}  

#endif  
