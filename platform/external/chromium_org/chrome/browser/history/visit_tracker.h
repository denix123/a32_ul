// Copyright (c) 2010 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_HISTORY_VISIT_TRACKER_H__
#define CHROME_BROWSER_HISTORY_VISIT_TRACKER_H__

#include <map>
#include <vector>

#include "base/basictypes.h"
#include "components/history/core/browser/history_types.h"

namespace history {

class VisitTracker {
 public:
  VisitTracker();
  ~VisitTracker();

  

  void AddVisit(ContextID context_id,
                int32 page_id,
                const GURL& url,
                VisitID visit_id);

  
  
  void ClearCachedDataForContextID(ContextID context_id);

  

  
  
  
  VisitID GetLastVisit(ContextID context_id, int32 page_id, const GURL& url);

 private:
  struct Transition {
    GURL url;          
    int32 page_id;     
    VisitID visit_id;  
  };
  typedef std::vector<Transition> TransitionList;
  typedef std::map<ContextID, TransitionList*> ContextList;

  
  
  
  void CleanupTransitionList(TransitionList* transitions);

  
  ContextList contexts_;

  DISALLOW_COPY_AND_ASSIGN(VisitTracker);
};

}  

#endif  
