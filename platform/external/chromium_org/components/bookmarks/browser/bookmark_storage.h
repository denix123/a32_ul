// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_BOOKMARKS_BROWSER_BOOKMARK_STORAGE_H_
#define COMPONENTS_BOOKMARKS_BROWSER_BOOKMARK_STORAGE_H_

#include "base/callback_forward.h"
#include "base/files/file_path.h"
#include "base/files/important_file_writer.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "base/memory/weak_ptr.h"
#include "components/bookmarks/browser/bookmark_node.h"

class BookmarkModel;

namespace base {
class SequencedTaskRunner;
}

namespace bookmarks {

class BookmarkIndex;

typedef ScopedVector<BookmarkPermanentNode> BookmarkPermanentNodeList;

typedef base::Callback<BookmarkPermanentNodeList(int64*)> LoadExtraCallback;

class BookmarkLoadDetails {
 public:
  BookmarkLoadDetails(BookmarkPermanentNode* bb_node,
                      BookmarkPermanentNode* other_folder_node,
                      BookmarkPermanentNode* mobile_folder_node,
                      const LoadExtraCallback& load_extra_callback,
                      BookmarkIndex* index,
                      int64 max_id);
  ~BookmarkLoadDetails();

  void LoadExtraNodes();

  BookmarkPermanentNode* bb_node() { return bb_node_.get(); }
  BookmarkPermanentNode* release_bb_node() { return bb_node_.release(); }
  BookmarkPermanentNode* mobile_folder_node() {
    return mobile_folder_node_.get();
  }
  BookmarkPermanentNode* release_mobile_folder_node() {
    return mobile_folder_node_.release();
  }
  BookmarkPermanentNode* other_folder_node() {
    return other_folder_node_.get();
  }
  BookmarkPermanentNode* release_other_folder_node() {
    return other_folder_node_.release();
  }
  const BookmarkPermanentNodeList& extra_nodes() {
    return extra_nodes_;
  }
  void release_extra_nodes(std::vector<BookmarkPermanentNode*>* extra_nodes) {
    extra_nodes_.release(extra_nodes);
  }
  BookmarkIndex* index() { return index_.get(); }
  BookmarkIndex* release_index() { return index_.release(); }

  const BookmarkNode::MetaInfoMap& model_meta_info_map() const {
    return model_meta_info_map_;
  }
  void set_model_meta_info_map(const BookmarkNode::MetaInfoMap& meta_info_map) {
    model_meta_info_map_ = meta_info_map;
  }

  int64 model_sync_transaction_version() const {
    return model_sync_transaction_version_;
  }
  void set_model_sync_transaction_version(int64 sync_transaction_version) {
    model_sync_transaction_version_ = sync_transaction_version;
  }

  
  void set_max_id(int64 max_id) { max_id_ = max_id; }
  int64 max_id() const { return max_id_; }

  
  void set_computed_checksum(const std::string& value) {
    computed_checksum_ = value;
  }
  const std::string& computed_checksum() const { return computed_checksum_; }

  
  void set_stored_checksum(const std::string& value) {
    stored_checksum_ = value;
  }
  const std::string& stored_checksum() const { return stored_checksum_; }

  
  
  
  
  void set_ids_reassigned(bool value) { ids_reassigned_ = value; }
  bool ids_reassigned() const { return ids_reassigned_; }

 private:
  scoped_ptr<BookmarkPermanentNode> bb_node_;
  scoped_ptr<BookmarkPermanentNode> other_folder_node_;
  scoped_ptr<BookmarkPermanentNode> mobile_folder_node_;
  LoadExtraCallback load_extra_callback_;
  BookmarkPermanentNodeList extra_nodes_;
  scoped_ptr<BookmarkIndex> index_;
  BookmarkNode::MetaInfoMap model_meta_info_map_;
  int64 model_sync_transaction_version_;
  int64 max_id_;
  std::string computed_checksum_;
  std::string stored_checksum_;
  bool ids_reassigned_;

  DISALLOW_COPY_AND_ASSIGN(BookmarkLoadDetails);
};

class BookmarkStorage : public base::ImportantFileWriter::DataSerializer {
 public:
  
  
  
  BookmarkStorage(BookmarkModel* model,
                  const base::FilePath& profile_path,
                  base::SequencedTaskRunner* sequenced_task_runner);
  virtual ~BookmarkStorage();

  
  
  
  void LoadBookmarks(
      scoped_ptr<BookmarkLoadDetails> details,
      const scoped_refptr<base::SequencedTaskRunner>& task_runner);

  
  void ScheduleSave();

  
  
  void BookmarkModelDeleted();

  
  void OnLoadFinished(scoped_ptr<BookmarkLoadDetails> details);

  
  virtual bool SerializeData(std::string* output) OVERRIDE;

 private:
  
  
  bool SaveNow();

  
  BookmarkModel* model_;

  
  base::ImportantFileWriter writer_;

  
  scoped_refptr<base::SequencedTaskRunner> sequenced_task_runner_;

  base::WeakPtrFactory<BookmarkStorage> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(BookmarkStorage);
};

}  

#endif  
