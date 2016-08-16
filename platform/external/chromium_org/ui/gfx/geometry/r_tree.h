// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef UI_GFX_GEOMETRY_R_TREE_H_
#define UI_GFX_GEOMETRY_R_TREE_H_

#include "r_tree_base.h"

namespace gfx {

template <typename Key>
class RTree : public RTreeBase {
 public:
  typedef base::hash_set<Key> Matches;

  
  
  
  
  
  
  
  
  
  
  
  
  RTree(size_t min_children, size_t max_children);
  ~RTree();

  
  
  
  void Insert(const Rect& rect, Key key);

  
  void Remove(Key key);

  
  
  void AppendIntersectingRecords(const Rect& query_rect,
                                 Matches* matches_out) const;

  void Clear();

 private:
  friend class RTreeTest;
  friend class RTreeNodeTest;

  class Record : public RecordBase {
   public:
    Record(const Rect& rect, const Key& key);
    virtual ~Record();
    const Key& key() const { return key_; }

   private:
    Key key_;

    DISALLOW_COPY_AND_ASSIGN(Record);
  };

  
  
  typedef base::hash_map<Key, Record*> RecordMap;
  RecordMap record_map_;

  DISALLOW_COPY_AND_ASSIGN(RTree);
};

template <typename Key>
RTree<Key>::RTree(size_t min_children, size_t max_children)
    : RTreeBase(min_children, max_children) {
}

template <typename Key>
RTree<Key>::~RTree() {
}

template <typename Key>
void RTree<Key>::Insert(const Rect& rect, Key key) {
  scoped_ptr<NodeBase> record;
  
  typename RecordMap::iterator it(record_map_.find(key));

  if (it != record_map_.end()) {
    
    Record* existing_record = it->second;
    
    
    if (existing_record->rect() == rect)
      return;

    
    record = RemoveNode(existing_record);

    PruneRootIfNecessary();

    
    
    
    if (rect.IsEmpty()) {
      record_map_.erase(it);
      return;
    }

    
    record->set_rect(rect);
  } else {
    if (rect.IsEmpty())
      return;

    record.reset(new Record(rect, key));
    record_map_.insert(std::make_pair(key, static_cast<Record*>(record.get())));
  }

  int highest_reinsert_level = -1;
  InsertNode(record.Pass(), &highest_reinsert_level);
}

template <typename Key>
void RTree<Key>::Clear() {
  record_map_.clear();
  ResetRoot();
}

template <typename Key>
void RTree<Key>::Remove(Key key) {
  
  typename RecordMap::iterator it = record_map_.find(key);
  if (it == record_map_.end())
    return;

  Record* record = it->second;
  record_map_.erase(it);
  RemoveNode(record);

  
  
  PruneRootIfNecessary();
}

template <typename Key>
void RTree<Key>::AppendIntersectingRecords(
      const Rect& query_rect, Matches* matches_out) const {
  RTreeBase::Records matching_records;
  root()->AppendIntersectingRecords(query_rect, &matching_records);
  for (RTreeBase::Records::const_iterator it = matching_records.begin();
       it != matching_records.end();
       ++it) {
    const Record* record = static_cast<const Record*>(*it);
    matches_out->insert(record->key());
  }
}



template <typename Key>
RTree<Key>::Record::Record(const Rect& rect, const Key& key)
    : RecordBase(rect),
      key_(key) {
}

template <typename Key>
RTree<Key>::Record::~Record() {
}

}  

#endif  
