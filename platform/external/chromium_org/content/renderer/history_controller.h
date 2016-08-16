// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

/*
 * Copyright (C) 2006, 2007, 2008, 2009 Apple Inc. All rights reserved.
 * Copyright (C) 2008, 2009 Torch Mobile Inc. All rights reserved.
 *     (http://www.torchmobile.com/)
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 * 3.  Neither the name of Apple Computer, Inc. ("Apple") nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE AND ITS CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE OR ITS CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef CONTENT_RENDERER_HISTORY_CONTROLLER_H_
#define CONTENT_RENDERER_HISTORY_CONTROLLER_H_

#include "base/containers/hash_tables.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "content/common/content_export.h"
#include "content/renderer/history_entry.h"
#include "third_party/WebKit/public/platform/WebURLRequest.h"
#include "third_party/WebKit/public/web/WebHistoryCommitType.h"
#include "third_party/WebKit/public/web/WebHistoryItem.h"

namespace blink {
class WebFrame;
}

namespace content {
class RenderFrameImpl;
class RenderViewImpl;

class CONTENT_EXPORT HistoryController {
 public:
  explicit HistoryController(RenderViewImpl* render_view);
  ~HistoryController();

  void GoToEntry(scoped_ptr<HistoryEntry> entry,
                 blink::WebURLRequest::CachePolicy cache_policy);

  void UpdateForCommit(RenderFrameImpl* frame,
                       const blink::WebHistoryItem& item,
                       blink::WebHistoryCommitType commit_type,
                       bool navigation_within_page);

  HistoryEntry* GetCurrentEntry();
  blink::WebHistoryItem GetItemForNewChildFrame(RenderFrameImpl* frame) const;
  void RemoveChildrenForRedirect(RenderFrameImpl* frame);

 private:
  typedef std::vector<std::pair<blink::WebFrame*, blink::WebHistoryItem> >
      HistoryFrameLoadVector;
  void RecursiveGoToEntry(blink::WebFrame* frame,
                          HistoryFrameLoadVector& sameDocumentLoads,
                          HistoryFrameLoadVector& differentDocumentLoads);

  void UpdateForInitialLoadInChildFrame(RenderFrameImpl* frame,
                                        const blink::WebHistoryItem& item);
  void CreateNewBackForwardItem(RenderFrameImpl* frame,
                                const blink::WebHistoryItem& item,
                                bool clone_children_of_target);

  RenderViewImpl* render_view_;

  scoped_ptr<HistoryEntry> current_entry_;
  scoped_ptr<HistoryEntry> provisional_entry_;

  DISALLOW_COPY_AND_ASSIGN(HistoryController);
};

}  

#endif  
