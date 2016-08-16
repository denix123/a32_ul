// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_ENHANCED_BOOKMARKS_METADATA_ACCESSOR_H_
#define COMPONENTS_ENHANCED_BOOKMARKS_METADATA_ACCESSOR_H_

#include <set>
#include <string>
#include <vector>

class BookmarkModel;
class BookmarkNode;
class GURL;


namespace enhanced_bookmarks {

typedef std::vector<const BookmarkNode*> NodeVector;
typedef std::set<const BookmarkNode*> NodeSet;

extern const char* kPageDataKey;
extern const char* kImageDataKey;
extern const char* kIdDataKey;
extern const char* kNoteKey;

std::string RemoteIdFromBookmark(BookmarkModel* bookmark_model,
                                 const BookmarkNode* node);

void SetDescriptionForBookmark(BookmarkModel* bookmark_model,
                               const BookmarkNode* node,
                               const std::string& description);

std::string DescriptionFromBookmark(const BookmarkNode* node);

bool SetOriginalImageForBookmark(BookmarkModel* bookmark_model,
                                 const BookmarkNode* node,
                                 const GURL& url,
                                 int width,
                                 int height);

bool OriginalImageFromBookmark(const BookmarkNode* node,
                               GURL* url,
                               int* width,
                               int* height);

bool ThumbnailImageFromBookmark(const BookmarkNode* node,
                                GURL* url,
                                int* width,
                                int* height);

std::string SnippetFromBookmark(const BookmarkNode* node);

bool SetAllImagesForBookmark(BookmarkModel* bookmark_model,
                             const BookmarkNode* node,
                             const GURL& image_url,
                             int image_width,
                             int image_height,
                             const GURL& thumbnail_url,
                             int thumbnail_width,
                             int thumbnail_height);

}  

#endif  
