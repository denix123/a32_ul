// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef UI_GFX_GEOMETRY_R_TREE_BASE_H_
#define UI_GFX_GEOMETRY_R_TREE_BASE_H_

#include <list>
#include <vector>

#include "base/containers/hash_tables.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "ui/gfx/geometry/rect.h"
#include "ui/gfx/gfx_export.h"

namespace gfx {

class GFX_EXPORT RTreeBase {
 protected:
  class NodeBase;
  class RecordBase;

  typedef std::vector<const RecordBase*> Records;
  typedef ScopedVector<NodeBase> Nodes;

  RTreeBase(size_t min_children, size_t max_children);
  ~RTreeBase();

  
  
  class GFX_EXPORT NodeBase {
   public:
    virtual ~NodeBase();

    
    
    
    virtual void AppendIntersectingRecords(const Rect& query_rect,
                                           Records* records_out) const = 0;

    
    
    virtual void AppendAllRecords(Records* records_out) const = 0;

    
    virtual scoped_ptr<NodeBase> RemoveAndReturnLastChild() = 0;

    
    
    
    
    virtual int Level() const = 0;

    
    
    
    void RecomputeBoundsUpToRoot();

    NodeBase* parent() { return parent_; }
    const NodeBase* parent() const { return parent_; }
    void set_parent(NodeBase* parent) { parent_ = parent; }
    const Rect& rect() const { return rect_; }
    void set_rect(const Rect& rect) { rect_ = rect; }

   protected:
    NodeBase(const Rect& rect, NodeBase* parent);

    
    virtual void RecomputeLocalBounds();

   private:
    friend class RTreeTest;
    friend class RTreeNodeTest;

    
    Rect rect_;

    
    
    NodeBase* parent_;

    DISALLOW_COPY_AND_ASSIGN(NodeBase);
  };

  class GFX_EXPORT RecordBase : public NodeBase {
   public:
    explicit RecordBase(const Rect& rect);
    virtual ~RecordBase();

    virtual void AppendIntersectingRecords(const Rect& query_rect,
                                           Records* records_out) const OVERRIDE;
    virtual void AppendAllRecords(Records* records_out) const OVERRIDE;
    virtual scoped_ptr<NodeBase> RemoveAndReturnLastChild() OVERRIDE;
    virtual int Level() const OVERRIDE;

   private:
    friend class RTreeTest;
    friend class RTreeNodeTest;

    DISALLOW_COPY_AND_ASSIGN(RecordBase);
  };

  class GFX_EXPORT Node : public NodeBase {
   public:
    
    Node();
    virtual ~Node();

    virtual void AppendIntersectingRecords(const Rect& query_rect,
                                           Records* records_out) const OVERRIDE;
    virtual scoped_ptr<NodeBase> RemoveAndReturnLastChild() OVERRIDE;
    virtual int Level() const OVERRIDE;
    virtual void AppendAllRecords(Records* matches_out) const OVERRIDE;

    
    
    
    
    scoped_ptr<Node> ConstructParent();

    
    
    
    
    
    
    
    
    void RemoveNodesForReinsert(size_t number_to_remove, Nodes* nodes);

    
    
    
    
    
    scoped_ptr<NodeBase> RemoveChild(NodeBase* child_node, Nodes* orphans);

    
    Node* ChooseSubtree(NodeBase* node);

    
    
    
    size_t AddChild(scoped_ptr<NodeBase> node);

    
    
    
    scoped_ptr<NodeBase> Split(size_t min_children, size_t max_children);

    size_t count() const { return children_.size(); }
    const NodeBase* child(size_t i) const { return children_[i]; }
    NodeBase* child(size_t i) { return children_[i]; }

   private:
    typedef std::vector<Rect> Rects;

    explicit Node(int level);

    
    
    
    
    static size_t ChooseSplitIndex(size_t start_index,
                                   size_t end_index,
                                   const Rects& low_bounds,
                                   const Rects& high_bounds);

    
    
    
    
    
    
    
    
    
    
    static int SmallestMarginSum(size_t start_index,
                                 size_t end_index,
                                 const Rects& low_bounds,
                                 const Rects& high_bounds);

    
    
    static bool CompareVertical(const NodeBase* a, const NodeBase* b);

    
    
    static bool CompareHorizontal(const NodeBase* a, const NodeBase* b);

    
    
    static bool CompareCenterDistanceFromParent(
        const NodeBase* a, const NodeBase* b);

    
    
    
    static void BuildLowBounds(const std::vector<NodeBase*>& vertical_sort,
                               const std::vector<NodeBase*>& horizontal_sort,
                               Rects* vertical_bounds,
                               Rects* horizontal_bounds);

    
    
    
    
    static void BuildHighBounds(const std::vector<NodeBase*>& vertical_sort,
                                const std::vector<NodeBase*>& horizontal_sort,
                                Rects* vertical_bounds,
                                Rects* horizontal_bounds);

    virtual void RecomputeLocalBounds() OVERRIDE;

    
    
    
    
    
    int OverlapIncreaseToAdd(const Rect& rect,
                             const NodeBase* candidate_node,
                             const Rect& expanded_rect) const;

    
    
    scoped_ptr<NodeBase> DivideChildren(
        const Rects& low_bounds,
        const Rects& high_bounds,
        const std::vector<NodeBase*>& sorted_children,
        size_t split_index);

    
    
    
    
    
    
    
    
    
    
    Node* LeastOverlapIncrease(const Rect& node_rect,
                               const Rects& expanded_rects);

    
    
    
    
    
    Node* LeastAreaEnlargement(const Rect& node_rect,
                               const Rects& expanded_rects);

    const int level_;

    Nodes children_;

    friend class RTreeTest;
    friend class RTreeNodeTest;

    DISALLOW_COPY_AND_ASSIGN(Node);
  };

  
  
  
  
  
  
  
  void InsertNode(scoped_ptr<NodeBase> node, int* highest_reinsert_level);

  
  scoped_ptr<NodeBase> RemoveNode(NodeBase* node);

  
  
  void PruneRootIfNecessary();

  
  void ResetRoot();

  const Node* root() const { return root_.get(); }

 private:
  friend class RTreeTest;
  friend class RTreeNodeTest;

  
  scoped_ptr<Node> root_;

  
  const size_t min_children_;
  const size_t max_children_;

  DISALLOW_COPY_AND_ASSIGN(RTreeBase);
};

}  

#endif  
