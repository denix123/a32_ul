// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_API_BOOKMARK_MANAGER_PRIVATE_BOOKMARK_MANAGER_PRIVATE_API_H_
#define CHROME_BROWSER_EXTENSIONS_API_BOOKMARK_MANAGER_PRIVATE_BOOKMARK_MANAGER_PRIVATE_API_H_

#include "base/memory/scoped_ptr.h"
#include "base/values.h"
#include "chrome/browser/extensions/api/bookmarks/bookmarks_api.h"
#include "chrome/browser/extensions/chrome_extension_function.h"
#include "chrome/browser/ui/bookmarks/bookmark_tab_helper.h"
#include "chrome/browser/undo/bookmark_undo_service.h"
#include "chrome/browser/undo/bookmark_undo_service_factory.h"
#include "components/bookmarks/browser/base_bookmark_model_observer.h"
#include "components/bookmarks/browser/bookmark_node_data.h"
#include "extensions/browser/browser_context_keyed_api_factory.h"
#include "extensions/browser/event_router.h"

class Profile;

namespace bookmarks {
struct BookmarkNodeData;
}

namespace content {
class BrowserContext;
class WebContents;
}

namespace extensions {

class BookmarkManagerPrivateEventRouter : public BaseBookmarkModelObserver {
 public:
  BookmarkManagerPrivateEventRouter(content::BrowserContext* browser_context,
                                    BookmarkModel* bookmark_model);
  virtual ~BookmarkManagerPrivateEventRouter();

  
  virtual void BookmarkModelChanged() OVERRIDE;
  virtual void BookmarkModelBeingDeleted(BookmarkModel* model) OVERRIDE;
  virtual void OnWillChangeBookmarkMetaInfo(BookmarkModel* model,
                                            const BookmarkNode* node) OVERRIDE;
  virtual void BookmarkMetaInfoChanged(BookmarkModel* model,
                                       const BookmarkNode* node) OVERRIDE;

 private:
  
  void DispatchEvent(const std::string& event_name,
                     scoped_ptr<base::ListValue> event_args);

  
  BookmarkNode::MetaInfoMap prev_meta_info_;

  content::BrowserContext* browser_context_;
  BookmarkModel* bookmark_model_;
};

class BookmarkManagerPrivateAPI : public BrowserContextKeyedAPI,
                                  public EventRouter::Observer {
 public:
  explicit BookmarkManagerPrivateAPI(content::BrowserContext* browser_context);
  virtual ~BookmarkManagerPrivateAPI();

  
  virtual void Shutdown() OVERRIDE;

  
  static BrowserContextKeyedAPIFactory<BookmarkManagerPrivateAPI>*
      GetFactoryInstance();

  
  virtual void OnListenerAdded(const EventListenerInfo& details) OVERRIDE;

 private:
  friend class BrowserContextKeyedAPIFactory<BookmarkManagerPrivateAPI>;

  
  static const char* service_name() { return "BookmarkManagerPrivateAPI"; }
  static const bool kServiceIsNULLWhileTesting = true;

  content::BrowserContext* browser_context_;

  
  scoped_ptr<BookmarkManagerPrivateEventRouter> event_router_;
};

class BookmarkManagerPrivateDragEventRouter
    : public BookmarkTabHelper::BookmarkDrag {
 public:
  BookmarkManagerPrivateDragEventRouter(Profile* profile,
                                        content::WebContents* web_contents);
  virtual ~BookmarkManagerPrivateDragEventRouter();

  
  virtual void OnDragEnter(const bookmarks::BookmarkNodeData& data) OVERRIDE;
  virtual void OnDragOver(const bookmarks::BookmarkNodeData& data) OVERRIDE;
  virtual void OnDragLeave(const bookmarks::BookmarkNodeData& data) OVERRIDE;
  virtual void OnDrop(const bookmarks::BookmarkNodeData& data) OVERRIDE;

  
  
  const bookmarks::BookmarkNodeData* GetBookmarkNodeData();

  
  void ClearBookmarkNodeData();

 private:
  
  void DispatchEvent(const std::string& event_name,
                     scoped_ptr<base::ListValue> args);

  Profile* profile_;
  content::WebContents* web_contents_;
  bookmarks::BookmarkNodeData bookmark_drag_data_;

  DISALLOW_COPY_AND_ASSIGN(BookmarkManagerPrivateDragEventRouter);
};

class ClipboardBookmarkManagerFunction : public extensions::BookmarksFunction {
 protected:
  virtual ~ClipboardBookmarkManagerFunction() {}

  bool CopyOrCut(bool cut, const std::vector<std::string>& id_list);
};

class BookmarkManagerPrivateCopyFunction
    : public ClipboardBookmarkManagerFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("bookmarkManagerPrivate.copy",
                             BOOKMARKMANAGERPRIVATE_COPY)

 protected:
  virtual ~BookmarkManagerPrivateCopyFunction() {}

  
  virtual bool RunOnReady() OVERRIDE;
};

class BookmarkManagerPrivateCutFunction
    : public ClipboardBookmarkManagerFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("bookmarkManagerPrivate.cut",
                             BOOKMARKMANAGERPRIVATE_CUT)

 protected:
  virtual ~BookmarkManagerPrivateCutFunction() {}

  
  virtual bool RunOnReady() OVERRIDE;
};

class BookmarkManagerPrivatePasteFunction
    : public extensions::BookmarksFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("bookmarkManagerPrivate.paste",
                             BOOKMARKMANAGERPRIVATE_PASTE)

 protected:
  virtual ~BookmarkManagerPrivatePasteFunction() {}

  
  virtual bool RunOnReady() OVERRIDE;
};

class BookmarkManagerPrivateCanPasteFunction
    : public extensions::BookmarksFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("bookmarkManagerPrivate.canPaste",
                             BOOKMARKMANAGERPRIVATE_CANPASTE)

 protected:
  virtual ~BookmarkManagerPrivateCanPasteFunction() {}

  
  virtual bool RunOnReady() OVERRIDE;
};

class BookmarkManagerPrivateSortChildrenFunction
    : public extensions::BookmarksFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("bookmarkManagerPrivate.sortChildren",
                             BOOKMARKMANAGERPRIVATE_SORTCHILDREN)

 protected:
  virtual ~BookmarkManagerPrivateSortChildrenFunction() {}

  
  virtual bool RunOnReady() OVERRIDE;
};

class BookmarkManagerPrivateGetStringsFunction : public AsyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("bookmarkManagerPrivate.getStrings",
                             BOOKMARKMANAGERPRIVATE_GETSTRINGS)

 protected:
  virtual ~BookmarkManagerPrivateGetStringsFunction() {}

  
  virtual bool RunAsync() OVERRIDE;
};

class BookmarkManagerPrivateStartDragFunction
    : public extensions::BookmarksFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("bookmarkManagerPrivate.startDrag",
                             BOOKMARKMANAGERPRIVATE_STARTDRAG)

 protected:
  virtual ~BookmarkManagerPrivateStartDragFunction() {}

  
  virtual bool RunOnReady() OVERRIDE;
};

class BookmarkManagerPrivateDropFunction
    : public extensions::BookmarksFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("bookmarkManagerPrivate.drop",
                             BOOKMARKMANAGERPRIVATE_DROP)

 protected:
  virtual ~BookmarkManagerPrivateDropFunction() {}

  
  virtual bool RunOnReady() OVERRIDE;
};

class BookmarkManagerPrivateGetSubtreeFunction
    : public extensions::BookmarksFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("bookmarkManagerPrivate.getSubtree",
                             BOOKMARKMANAGERPRIVATE_GETSUBTREE)

 protected:
  virtual ~BookmarkManagerPrivateGetSubtreeFunction() {}

  
  virtual bool RunOnReady() OVERRIDE;
};

class BookmarkManagerPrivateCanEditFunction
    : public extensions::BookmarksFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("bookmarkManagerPrivate.canEdit",
                             BOOKMARKMANAGERPRIVATE_CANEDIT)

 protected:
  virtual ~BookmarkManagerPrivateCanEditFunction() {}

  
  virtual bool RunOnReady() OVERRIDE;
};

class BookmarkManagerPrivateRecordLaunchFunction
    : public extensions::BookmarksFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("bookmarkManagerPrivate.recordLaunch",
                             BOOKMARKMANAGERPRIVATE_RECORDLAUNCH)

 protected:
  virtual ~BookmarkManagerPrivateRecordLaunchFunction() {}

  
  virtual bool RunOnReady() OVERRIDE;
};

class BookmarkManagerPrivateCreateWithMetaInfoFunction
    : public extensions::BookmarksFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("bookmarkManagerPrivate.createWithMetaInfo",
                             BOOKMARKMANAGERPRIVATE_CREATEWITHMETAINFO)

 protected:
  virtual ~BookmarkManagerPrivateCreateWithMetaInfoFunction() {}

  
  virtual bool RunOnReady() OVERRIDE;
};

class BookmarkManagerPrivateGetMetaInfoFunction
    : public extensions::BookmarksFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("bookmarkManagerPrivate.getMetaInfo",
                             BOOKMARKMANAGERPRIVATE_GETMETAINFO)

 protected:
  virtual ~BookmarkManagerPrivateGetMetaInfoFunction() {}

  
  virtual bool RunOnReady() OVERRIDE;
};

class BookmarkManagerPrivateSetMetaInfoFunction
    : public extensions::BookmarksFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("bookmarkManagerPrivate.setMetaInfo",
                             BOOKMARKMANAGERPRIVATE_SETMETAINFO)

 protected:
  virtual ~BookmarkManagerPrivateSetMetaInfoFunction() {}

  
  virtual bool RunOnReady() OVERRIDE;
};

class BookmarkManagerPrivateUpdateMetaInfoFunction
    : public extensions::BookmarksFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("bookmarkManagerPrivate.updateMetaInfo",
                             BOOKMARKMANAGERPRIVATE_UPDATEMETAINFO)

 protected:
  virtual ~BookmarkManagerPrivateUpdateMetaInfoFunction() {}

  
  virtual bool RunOnReady() OVERRIDE;
};

class BookmarkManagerPrivateCanOpenNewWindowsFunction
    : public extensions::BookmarksFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("bookmarkManagerPrivate.canOpenNewWindows",
                             BOOKMARKMANAGERPRIVATE_CANOPENNEWWINDOWS)

 protected:
  virtual ~BookmarkManagerPrivateCanOpenNewWindowsFunction() {}

  
  virtual bool RunOnReady() OVERRIDE;
};

class BookmarkManagerPrivateRemoveTreesFunction
    : public extensions::BookmarksFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("bookmarkManagerPrivate.removeTrees",
                             BOOKMARKMANAGERPRIVATE_REMOVETREES)

 protected:
  virtual ~BookmarkManagerPrivateRemoveTreesFunction() {}

  
  virtual bool RunOnReady() OVERRIDE;
};

class BookmarkManagerPrivateUndoFunction
    : public extensions::BookmarksFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("bookmarkManagerPrivate.undo",
                             BOOKMARKMANAGERPRIVATE_UNDO)

 protected:
  virtual ~BookmarkManagerPrivateUndoFunction() {}

  
  virtual bool RunOnReady() OVERRIDE;
};

class BookmarkManagerPrivateRedoFunction
    : public extensions::BookmarksFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("bookmarkManagerPrivate.redo",
                             BOOKMARKMANAGERPRIVATE_REDO)

 protected:
  virtual ~BookmarkManagerPrivateRedoFunction() {}

  
  virtual bool RunOnReady() OVERRIDE;
};

class BookmarkManagerPrivateGetUndoInfoFunction
    : public extensions::BookmarksFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("bookmarkManagerPrivate.getUndoInfo",
                             BOOKMARKMANAGERPRIVATE_UNDOINFO)

 protected:
  virtual ~BookmarkManagerPrivateGetUndoInfoFunction() {}

  
  virtual bool RunOnReady() OVERRIDE;
};

class BookmarkManagerPrivateGetRedoInfoFunction
    : public extensions::BookmarksFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("bookmarkManagerPrivate.getRedoInfo",
                             BOOKMARKMANAGERPRIVATE_REDOINFO)

 protected:
  virtual ~BookmarkManagerPrivateGetRedoInfoFunction() {}

  
  virtual bool RunOnReady() OVERRIDE;
};

}  

#endif  
