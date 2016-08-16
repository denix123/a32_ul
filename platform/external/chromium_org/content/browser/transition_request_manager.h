// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_TRANSITION_REQUEST_MANAGER_H_
#define CONTENT_BROWSER_TRANSITION_REQUEST_MANAGER_H_

#include <map>
#include <string>
#include <utility>
#include <vector>

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "content/common/content_export.h"
#include "url/gurl.h"

template <typename T>
struct DefaultSingletonTraits;

namespace net {
class HttpResponseHeaders;
}
class GURL;

namespace content {

struct TransitionLayerData {
  TransitionLayerData();
  ~TransitionLayerData();

  std::string markup;
  std::string css_selector;
  scoped_refptr<net::HttpResponseHeaders> response_headers;
  GURL request_url;
};

class TransitionRequestManager {
 public:
  
  CONTENT_EXPORT static TransitionRequestManager* GetInstance();

  
  
  CONTENT_EXPORT static void ParseTransitionStylesheetsFromHeaders(
      const scoped_refptr<net::HttpResponseHeaders>& headers,
      std::vector<GURL>& entering_stylesheets,
      const GURL& resolve_address);

  
  
  
  bool HasPendingTransitionRequest(int render_process_id,
                                   int render_frame_id,
                                   const GURL& request_url,
                                   TransitionLayerData* transition_data);

  
  
  CONTENT_EXPORT void AddPendingTransitionRequestData(
      int render_process_id,
      int render_frame_id,
      const std::string& allowed_destination_host_pattern,
      const std::string& css_selector,
      const std::string& markup);

  void ClearPendingTransitionRequestData(int render_process_id,
                                         int render_frame_id);

 private:
  class TransitionRequestData {
   public:
    TransitionRequestData();
    ~TransitionRequestData();
    void AddEntry(const std::string& allowed_destination_host_pattern,
                  const std::string& selector,
                  const std::string& markup);
    bool FindEntry(const GURL& request_url,
                    TransitionLayerData* transition_data);

   private:
    struct AllowedEntry {
      
      
      
      std::string allowed_destination_host_pattern;
      std::string css_selector;
      std::string markup;

      AllowedEntry(const std::string& allowed_destination_host_pattern,
                   const std::string& css_selector,
                   const std::string& markup) :
        allowed_destination_host_pattern(allowed_destination_host_pattern),
        css_selector(css_selector),
        markup(markup) {}
    };
    std::vector<AllowedEntry> allowed_entries_;
  };

  friend struct DefaultSingletonTraits<TransitionRequestManager>;
  typedef std::map<std::pair<int, int>, TransitionRequestData>
      RenderFrameRequestDataMap;

  TransitionRequestManager();
  ~TransitionRequestManager();

  
  
  
  
  RenderFrameRequestDataMap pending_transition_frames_;

  DISALLOW_COPY_AND_ASSIGN(TransitionRequestManager);
};

}  

#endif  
