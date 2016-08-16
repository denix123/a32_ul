// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_BASE_X_SELECTION_OWNER_H_
#define UI_BASE_X_SELECTION_OWNER_H_

#include <vector>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/memory/ref_counted_memory.h"
#include "base/time/time.h"
#include "base/timer/timer.h"
#include "ui/base/ui_base_export.h"
#include "ui/base/x/selection_utils.h"
#include "ui/gfx/x/x11_atom_cache.h"
#include "ui/gfx/x/x11_types.h"

namespace ui {

class UI_BASE_EXPORT SelectionOwner {
 public:
  SelectionOwner(XDisplay* xdisplay,
                 XID xwindow,
                 XAtom selection_name);
  ~SelectionOwner();

  
  const SelectionFormatMap& selection_format_map() { return format_map_; }

  
  void RetrieveTargets(std::vector<XAtom>* targets);

  
  
  void TakeOwnershipOfSelection(const SelectionFormatMap& data);

  
  
  void ClearSelectionOwner();

  
  void OnSelectionRequest(const XEvent& event);
  void OnSelectionClear(const XEvent& event);

  
  
  bool CanDispatchPropertyEvent(const XEvent& event);

  void OnPropertyEvent(const XEvent& event);

 private:
  
  struct IncrementalTransfer {
    IncrementalTransfer(XID window,
                        XAtom target,
                        XAtom property,
                        const scoped_refptr<base::RefCountedMemory>& data,
                        int offset,
                        base::TimeTicks timeout,
                        int foreign_window_manager_id);
    ~IncrementalTransfer();

    
    
    XID window;
    XAtom target;
    XAtom property;

    
    scoped_refptr<base::RefCountedMemory> data;

    
    
    size_t offset;

    
    
    base::TimeTicks timeout;

    
    
    int foreign_window_manager_id;
  };

  
  
  
  bool ProcessTarget(XAtom target, XID requestor, XAtom property);

  
  void ProcessIncrementalTransfer(IncrementalTransfer* transfer);

  
  void AbortStaleIncrementalTransfers();

  
  void CompleteIncrementalTransfer(
      std::vector<IncrementalTransfer>::iterator it);

  
  
  std::vector<IncrementalTransfer>::iterator FindIncrementalTransferForEvent(
      const XEvent& event);

  
  XDisplay* x_display_;
  XID x_window_;

  
  XAtom selection_name_;

  
  size_t max_request_size_;

  
  SelectionFormatMap format_map_;

  std::vector<IncrementalTransfer> incremental_transfers_;

  
  base::RepeatingTimer<SelectionOwner> incremental_transfer_abort_timer_;

  X11AtomCache atom_cache_;

  DISALLOW_COPY_AND_ASSIGN(SelectionOwner);
};

}  

#endif  
