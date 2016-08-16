// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_GUEST_VIEW_WEB_VIEW_WEB_VIEW_FIND_HELPER_H_
#define EXTENSIONS_BROWSER_GUEST_VIEW_WEB_VIEW_WEB_VIEW_FIND_HELPER_H_

#include <map>
#include <vector>

#include "base/memory/weak_ptr.h"
#include "base/values.h"
#include "content/public/browser/web_contents.h"
#include "third_party/WebKit/public/web/WebFindOptions.h"
#include "ui/gfx/geometry/rect.h"

namespace extensions {
class WebViewInternalFindFunction;
class WebViewGuest;

class WebViewFindHelper {
 public:
  explicit WebViewFindHelper(WebViewGuest* webview_guest);
  ~WebViewFindHelper();

  
  void CancelAllFindSessions();

  
  void DispatchFindUpdateEvent(bool canceled, bool final_update);

  
  
  void EndFindSession(int session_request_id, bool canceled);

  
  void Find(content::WebContents* guest_web_contents,
            const base::string16& search_text,
            const blink::WebFindOptions& options,
            scoped_refptr<WebViewInternalFindFunction> find_function);

  
  void FindReply(int request_id,
                 int number_of_matches,
                 const gfx::Rect& selection_rect,
                 int active_match_ordinal,
                 bool final_update);

 private:
  
  class FindResults {
   public:
    FindResults();
    ~FindResults();

    
    void AggregateResults(int number_of_matches,
                          const gfx::Rect& selection_rect,
                          int active_match_ordinal,
                          bool final_update);

    
    void PrepareResults(base::DictionaryValue* results);

   private:
    int number_of_matches_;
    int active_match_ordinal_;
    gfx::Rect selection_rect_;

    friend void WebViewFindHelper::EndFindSession(int session_request_id,
                                                  bool canceled);

    DISALLOW_COPY_AND_ASSIGN(FindResults);
  };

  
  class FindUpdateEvent {
   public:
    explicit FindUpdateEvent(const base::string16& search_text);
    ~FindUpdateEvent();

    
    void AggregateResults(int number_of_matches,
                          const gfx::Rect& selection_rect,
                          int active_match_ordinal,
                          bool final_update);

    
    void PrepareResults(base::DictionaryValue* results);

   private:
    const base::string16 search_text_;
    FindResults find_results_;

    DISALLOW_COPY_AND_ASSIGN(FindUpdateEvent);
  };

  
  class FindInfo {
   public:
    FindInfo(int request_id,
             const base::string16& search_text,
             const blink::WebFindOptions& options,
             scoped_refptr<WebViewInternalFindFunction> find_function);
    ~FindInfo();

    
    void AddFindNextRequest(const base::WeakPtr<FindInfo>& request) {
      find_next_requests_.push_back(request);
    }

    
    void AggregateResults(int number_of_matches,
                          const gfx::Rect& selection_rect,
                          int active_match_ordinal,
                          bool final_update);

    base::WeakPtr<FindInfo> AsWeakPtr();

    blink::WebFindOptions* options() {
      return &options_;
    }

    bool replied() {
      return replied_;
    }

    int request_id() {
      return request_id_;
    }

    const base::string16& search_text() {
      return search_text_;
    }

    
    
    void SendResponse(bool canceled);

   private:
    const int request_id_;
    const base::string16 search_text_;
    blink::WebFindOptions options_;
    scoped_refptr<WebViewInternalFindFunction> find_function_;
    FindResults find_results_;

    
    bool replied_;

    
    
    std::vector<base::WeakPtr<FindInfo> > find_next_requests_;

    friend void WebViewFindHelper::EndFindSession(int session_request_id,
                                                  bool canceled);

    base::WeakPtrFactory<FindInfo> weak_ptr_factory_;

    DISALLOW_COPY_AND_ASSIGN(FindInfo);
  };

  
  WebViewGuest* const webview_guest_;

  
  
  int current_find_request_id_;

  
  scoped_ptr<FindUpdateEvent> find_update_event_;

  
  linked_ptr<FindInfo> current_find_session_;

  
  
  typedef std::map<int, linked_ptr<FindInfo> > FindInfoMap;
  FindInfoMap find_info_map_;

  DISALLOW_COPY_AND_ASSIGN(WebViewFindHelper);
};

} 

#endif  
