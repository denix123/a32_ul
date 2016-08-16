// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_BOOKMARKS_BROWSER_BOOKMARK_PASTEBOARD_HELPER_MAC_H_
#define COMPONENTS_BOOKMARKS_BROWSER_BOOKMARK_PASTEBOARD_HELPER_MAC_H_

#include "components/bookmarks/browser/bookmark_node_data.h"

#if defined(__OBJC__)
@class NSString;
#endif  

namespace base {
class FilePath;
}


void WriteBookmarksToPasteboard(
    ui::ClipboardType type,
    const std::vector<bookmarks::BookmarkNodeData::Element>& elements,
    const base::FilePath& profile_path);

bool ReadBookmarksFromPasteboard(
    ui::ClipboardType type,
    std::vector<bookmarks::BookmarkNodeData::Element>& elements,
    base::FilePath* profile_path);

bool PasteboardContainsBookmarks(ui::ClipboardType type);

#if defined(__OBJC__)
extern "C" NSString* const kBookmarkDictionaryListPboardType;
#endif  

#endif  
