// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_API_BOOKMARKS_BOOKMARKS_API_H_
#define CHROME_BROWSER_EXTENSIONS_API_BOOKMARKS_BOOKMARKS_API_H_

#include <list>
#include <string>
#include <vector>

#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "chrome/browser/extensions/chrome_extension_function.h"
#include "components/bookmarks/browser/base_bookmark_model_observer.h"
#include "components/bookmarks/browser/bookmark_node.h"
#include "extensions/browser/browser_context_keyed_api_factory.h"
#include "extensions/browser/event_router.h"
#include "ui/shell_dialogs/select_file_dialog.h"

class ChromeBookmarkClient;

namespace base {
class FilePath;
class ListValue;
}

namespace content {
class BrowserContext;
}

namespace extensions {

namespace api {
namespace bookmarks {
struct CreateDetails;
}
}

class BookmarkEventRouter : public BookmarkModelObserver {
 public:
  explicit BookmarkEventRouter(Profile* profile);
  virtual ~BookmarkEventRouter();

  
  virtual void BookmarkModelLoaded(BookmarkModel* model,
                                   bool ids_reassigned) OVERRIDE;
  virtual void BookmarkModelBeingDeleted(BookmarkModel* model) OVERRIDE;
  virtual void BookmarkNodeMoved(BookmarkModel* model,
                                 const BookmarkNode* old_parent,
                                 int old_index,
                                 const BookmarkNode* new_parent,
                                 int new_index) OVERRIDE;
  virtual void BookmarkNodeAdded(BookmarkModel* model,
                                 const BookmarkNode* parent,
                                 int index) OVERRIDE;
  virtual void BookmarkNodeRemoved(BookmarkModel* model,
                                   const BookmarkNode* parent,
                                   int old_index,
                                   const BookmarkNode* node,
                                   const std::set<GURL>& removed_urls) OVERRIDE;
  virtual void BookmarkAllUserNodesRemoved(
      BookmarkModel* model,
      const std::set<GURL>& removed_urls) OVERRIDE;
  virtual void BookmarkNodeChanged(BookmarkModel* model,
                                   const BookmarkNode* node) OVERRIDE;
  virtual void BookmarkNodeFaviconChanged(BookmarkModel* model,
                                          const BookmarkNode* node) OVERRIDE;
  virtual void BookmarkNodeChildrenReordered(BookmarkModel* model,
                                             const BookmarkNode* node) OVERRIDE;
  virtual void ExtensiveBookmarkChangesBeginning(BookmarkModel* model) OVERRIDE;
  virtual void ExtensiveBookmarkChangesEnded(BookmarkModel* model) OVERRIDE;

 private:
  
  void DispatchEvent(const std::string& event_name,
                     scoped_ptr<base::ListValue> event_args);

  content::BrowserContext* browser_context_;
  BookmarkModel* model_;
  ChromeBookmarkClient* client_;

  DISALLOW_COPY_AND_ASSIGN(BookmarkEventRouter);
};

class BookmarksAPI : public BrowserContextKeyedAPI,
                     public EventRouter::Observer {
 public:
  explicit BookmarksAPI(content::BrowserContext* context);
  virtual ~BookmarksAPI();

  
  virtual void Shutdown() OVERRIDE;

  
  static BrowserContextKeyedAPIFactory<BookmarksAPI>* GetFactoryInstance();

  
  virtual void OnListenerAdded(
      const EventListenerInfo& details) OVERRIDE;

 private:
  friend class BrowserContextKeyedAPIFactory<BookmarksAPI>;

  content::BrowserContext* browser_context_;

  
  static const char* service_name() {
    return "BookmarksAPI";
  }
  static const bool kServiceIsNULLWhileTesting = true;

  
  scoped_ptr<BookmarkEventRouter> bookmark_event_router_;
};

class BookmarksFunction : public ChromeAsyncExtensionFunction,
                          public BaseBookmarkModelObserver {
 public:
  
  virtual bool RunAsync() OVERRIDE;

 protected:
  virtual ~BookmarksFunction() {}

  
  virtual bool RunOnReady() = 0;

  
  BookmarkModel* GetBookmarkModel();

  
  ChromeBookmarkClient* GetChromeBookmarkClient();

  
  
  
  bool GetBookmarkIdAsInt64(const std::string& id_string, int64* id);

  
  
  
  const BookmarkNode* GetBookmarkNodeFromId(const std::string& id_string);

  
  
  const BookmarkNode* CreateBookmarkNode(
      BookmarkModel* model,
      const api::bookmarks::CreateDetails& details,
      const BookmarkNode::MetaInfoMap* meta_info);

  
  
  bool EditBookmarksEnabled();

  
  
  
  
  bool CanBeModified(const BookmarkNode* node);

 private:
  
  virtual void BookmarkModelChanged() OVERRIDE;
  virtual void BookmarkModelLoaded(BookmarkModel* model,
                                   bool ids_reassigned) OVERRIDE;
};

class BookmarksGetFunction : public BookmarksFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("bookmarks.get", BOOKMARKS_GET)

 protected:
  virtual ~BookmarksGetFunction() {}

  
  virtual bool RunOnReady() OVERRIDE;
};

class BookmarksGetChildrenFunction : public BookmarksFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("bookmarks.getChildren", BOOKMARKS_GETCHILDREN)

 protected:
  virtual ~BookmarksGetChildrenFunction() {}

  
  virtual bool RunOnReady() OVERRIDE;
};

class BookmarksGetRecentFunction : public BookmarksFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("bookmarks.getRecent", BOOKMARKS_GETRECENT)

 protected:
  virtual ~BookmarksGetRecentFunction() {}

  
  virtual bool RunOnReady() OVERRIDE;
};

class BookmarksGetTreeFunction : public BookmarksFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("bookmarks.getTree", BOOKMARKS_GETTREE)

 protected:
  virtual ~BookmarksGetTreeFunction() {}

  
  virtual bool RunOnReady() OVERRIDE;
};

class BookmarksGetSubTreeFunction : public BookmarksFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("bookmarks.getSubTree", BOOKMARKS_GETSUBTREE)

 protected:
  virtual ~BookmarksGetSubTreeFunction() {}

  
  virtual bool RunOnReady() OVERRIDE;
};

class BookmarksSearchFunction : public BookmarksFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("bookmarks.search", BOOKMARKS_SEARCH)

 protected:
  virtual ~BookmarksSearchFunction() {}

  
  virtual bool RunOnReady() OVERRIDE;
};

class BookmarksRemoveFunction : public BookmarksFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("bookmarks.remove", BOOKMARKS_REMOVE)

  
  
  static bool ExtractIds(const base::ListValue* args,
                         std::list<int64>* ids,
                         bool* invalid_id);

 protected:
  virtual ~BookmarksRemoveFunction() {}

  
  virtual bool RunOnReady() OVERRIDE;
};

class BookmarksRemoveTreeFunction : public BookmarksRemoveFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("bookmarks.removeTree", BOOKMARKS_REMOVETREE)

 protected:
  virtual ~BookmarksRemoveTreeFunction() {}
};

class BookmarksCreateFunction : public BookmarksFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("bookmarks.create", BOOKMARKS_CREATE)

 protected:
  virtual ~BookmarksCreateFunction() {}

  
  virtual bool RunOnReady() OVERRIDE;
};

class BookmarksMoveFunction : public BookmarksFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("bookmarks.move", BOOKMARKS_MOVE)

  static bool ExtractIds(const base::ListValue* args,
                         std::list<int64>* ids,
                         bool* invalid_id);

 protected:
  virtual ~BookmarksMoveFunction() {}

  
  virtual bool RunOnReady() OVERRIDE;
};

class BookmarksUpdateFunction : public BookmarksFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("bookmarks.update", BOOKMARKS_UPDATE)

  static bool ExtractIds(const base::ListValue* args,
                         std::list<int64>* ids,
                         bool* invalid_id);

 protected:
  virtual ~BookmarksUpdateFunction() {}

  
  virtual bool RunOnReady() OVERRIDE;
};

class BookmarksIOFunction : public BookmarksFunction,
                            public ui::SelectFileDialog::Listener {
 public:
  BookmarksIOFunction();

  virtual void FileSelected(const base::FilePath& path, int index, void* params) = 0;

  
  virtual void MultiFilesSelected(const std::vector<base::FilePath>& files,
                                  void* params) OVERRIDE;
  virtual void FileSelectionCanceled(void* params) OVERRIDE;

  void SelectFile(ui::SelectFileDialog::Type type);

 protected:
  virtual ~BookmarksIOFunction();

 private:
  void ShowSelectFileDialog(
      ui::SelectFileDialog::Type type,
      const base::FilePath& default_path);

 protected:
  scoped_refptr<ui::SelectFileDialog> select_file_dialog_;
};

class BookmarksImportFunction : public BookmarksIOFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("bookmarks.import", BOOKMARKS_IMPORT)

  
  virtual void FileSelected(const base::FilePath& path,
                            int index,
                            void* params) OVERRIDE;

 private:
  virtual ~BookmarksImportFunction() {}

  
  virtual bool RunOnReady() OVERRIDE;
};

class BookmarksExportFunction : public BookmarksIOFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("bookmarks.export", BOOKMARKS_EXPORT)

  
  virtual void FileSelected(const base::FilePath& path,
                            int index,
                            void* params) OVERRIDE;

 private:
  virtual ~BookmarksExportFunction() {}

  
  virtual bool RunOnReady() OVERRIDE;
};

}  

#endif  
