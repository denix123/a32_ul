// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_BASE_X_SELECTION_REQUESTOR_H_
#define UI_BASE_X_SELECTION_REQUESTOR_H_

#include <vector>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/event_types.h"
#include "base/memory/ref_counted_memory.h"
#include "base/time/time.h"
#include "base/timer/timer.h"
#include "ui/base/ui_base_export.h"
#include "ui/gfx/x/x11_atom_cache.h"
#include "ui/gfx/x/x11_types.h"

namespace ui {
class PlatformEventDispatcher;
class SelectionData;

class UI_BASE_EXPORT SelectionRequestor {
 public:
  SelectionRequestor(XDisplay* xdisplay,
                     XID xwindow,
                     PlatformEventDispatcher* dispatcher);
  ~SelectionRequestor();

  
  
  
  
  bool PerformBlockingConvertSelection(
      XAtom selection,
      XAtom target,
      scoped_refptr<base::RefCountedMemory>* out_data,
      size_t* out_data_items,
      XAtom* out_type);

  
  
  void PerformBlockingConvertSelectionWithParameter(
      XAtom selection,
      XAtom target,
      const std::vector<XAtom>& parameter);

  
  
  SelectionData RequestAndWaitForTypes(XAtom selection,
                                       const std::vector<XAtom>& types);

  
  
  void OnSelectionNotify(const XEvent& event);

  
  
  bool CanDispatchPropertyEvent(const XEvent& event);

  void OnPropertyEvent(const XEvent& event);

 private:
  friend class SelectionRequestorTest;

  
  struct Request {
    Request(XAtom selection, XAtom target, base::TimeTicks timeout);
    ~Request();

    
    
    XAtom selection;
    XAtom target;

    
    
    bool data_sent_incrementally;

    
    std::vector<scoped_refptr<base::RefCountedMemory> > out_data;
    size_t out_data_items;
    XAtom out_type;

    
    bool success;

    
    base::TimeTicks timeout;

    
    base::Closure quit_closure;

    
    bool completed;
  };

  
  void AbortStaleRequests();

  
  
  void CompleteRequest(size_t index, bool success);

  
  void ConvertSelectionForCurrentRequest();

  
  
  void BlockTillSelectionNotifyForRequest(Request* request);

  
  Request* GetCurrentRequest();

  
  XDisplay* x_display_;
  XID x_window_;

  
  
  XAtom x_property_;

  
  
  
  
  
  PlatformEventDispatcher* dispatcher_;

  
  
  
  std::vector<Request*> requests_;

  
  
  
  size_t current_request_index_;

  
  base::RepeatingTimer<SelectionRequestor> abort_timer_;

  X11AtomCache atom_cache_;

  DISALLOW_COPY_AND_ASSIGN(SelectionRequestor);
};

}  

#endif  
