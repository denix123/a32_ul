// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_SPDY_SPDY_PRIORITY_TREE_H_
#define NET_SPDY_SPDY_PRIORITY_TREE_H_

#include <cmath>
#include <list>
#include <map>
#include <queue>
#include <set>

#include "base/basictypes.h"
#include "base/containers/hash_tables.h"
#include "base/logging.h"
#include "base/memory/scoped_ptr.h"

namespace net {


namespace test {
template <typename NodeId>
class SpdyPriorityTreePeer;
}

const int kRootNodeId = 0;
const int kDefaultWeight = 16;
const int kMinWeight = 1;
const int kMaxWeight = 256;

template <typename NodeId>
class SpdyPriorityTree {
  typedef std::vector<std::pair<NodeId, float> > PriorityNodeList;

 public:
  SpdyPriorityTree();
  ~SpdyPriorityTree();

  typedef std::list<NodeId> List;
  struct Node {
    Node();
    ~Node();

    NodeId id;
    NodeId parent_id;
    int weight;  
    
    int total_child_weights;
    
    
    
    
    int total_writeable_child_weights;
    List* child_list;  
    bool blocked;  
    bool ready;  
    float priority;  
  };

  
  struct NodePriorityComparator {
    bool operator ()(const std::pair<NodeId, float>& lhs,
                     const std::pair<NodeId, float>& rhs);
  };

  friend class test::SpdyPriorityTreePeer<NodeId>;

  
  int num_nodes() const;

  
  bool NodeExists(NodeId node_id) const;

  
  
  
  
  
  
  bool AddNode(NodeId node_id, NodeId parent_id, int weight, bool exclusive);

  
  
  bool RemoveNode(NodeId node_id);

  
  int GetWeight(NodeId node_id) const;

  
  
  NodeId GetParent(NodeId node_id) const;

  
  
  std::list<NodeId>* GetChildren(NodeId node_id) const;

  
  bool SetWeight(NodeId node_id, int weight);

  
  
  
  
  
  bool SetParent(NodeId node_id, NodeId parent_id, bool exclusive);

  
  bool HasChild(NodeId parent_id, NodeId child_id) const;

  
  
  bool SetBlocked(NodeId node_id, bool blocked);

  
  
  
  bool SetReady(NodeId node_id, bool ready);

  
  
  bool ValidateInvariantsForTests() const;

  
  const Node* FindNode(NodeId node_id) const;

  
  
  
  PriorityNodeList GetPriorityList();

 protected:
  
  
  void PropagateNodeState(NodeId node);

 private:
  typedef base::hash_map<NodeId, Node> NodeMap;

  NodeMap all_nodes_;  

  DISALLOW_COPY_AND_ASSIGN(SpdyPriorityTree);
};

template <typename NodeId>
SpdyPriorityTree<NodeId>::SpdyPriorityTree() {
  Node* root_node = &all_nodes_[kRootNodeId];
  root_node->id = kRootNodeId;
  root_node->weight = kDefaultWeight;
  root_node->parent_id = static_cast<NodeId>(kRootNodeId);
  root_node->child_list = new std::list<NodeId>;
  root_node->priority = 1.0;
  root_node->ready = true;
}

template <typename NodeId>
SpdyPriorityTree<NodeId>::~SpdyPriorityTree() {}

template <typename NodeId>
SpdyPriorityTree<NodeId>::Node::Node() :
  parent_id(kRootNodeId),
  weight(kDefaultWeight),
  total_child_weights(0),
  total_writeable_child_weights(0),
  child_list(),
  blocked(false),
  ready(false),
  priority(0) {
}

template <typename NodeId>
SpdyPriorityTree<NodeId>::Node::~Node() {
  delete child_list;
}

template <typename NodeId>
bool SpdyPriorityTree<NodeId>::NodePriorityComparator::operator ()(
    const std::pair<NodeId, float>& lhs,
    const std::pair<NodeId, float>& rhs) {
  return lhs.second > rhs.second;
}

template <typename NodeId>
int SpdyPriorityTree<NodeId>::num_nodes() const {
  return all_nodes_.size();
}

template <typename NodeId>
bool SpdyPriorityTree<NodeId>::NodeExists(NodeId node_id) const {
  return all_nodes_.count(node_id) != 0;
}

template <typename NodeId>
bool SpdyPriorityTree<NodeId>::AddNode(NodeId node_id,
                                       NodeId parent_id,
                                       int weight,
                                       bool exclusive) {
  if (NodeExists(node_id) || !NodeExists(parent_id)) {
    return false;
  }
  if (weight < kMinWeight || weight > kMaxWeight) {
    return false;
  }
  Node* parent = &all_nodes_[parent_id];
  Node* new_node = &all_nodes_[node_id];
  new_node->id = node_id;
  new_node->weight = weight;
  new_node->parent_id = parent_id;
  if (exclusive) {
    
    new_node->child_list = parent->child_list;
    new_node->total_child_weights = parent->total_child_weights;
    
    for (typename List::iterator it = new_node->child_list->begin();
         it != new_node->child_list->end(); ++it) {
      Node* child = &all_nodes_[*it];
      child->parent_id = node_id;
    }
    
    parent->child_list = new std::list<NodeId>;
    parent->total_child_weights = 0;
  } else {
    new_node->child_list = new std::list<NodeId>;
  }
  
  parent->child_list->push_back(node_id);
  parent->total_child_weights += weight;
  return true;
}

template <typename NodeId>
bool SpdyPriorityTree<NodeId>::RemoveNode(NodeId node_id) {
  if (node_id == static_cast<NodeId>(kRootNodeId) || !NodeExists(node_id)) {
    return false;
  }
  const Node& node = all_nodes_[node_id];

  DCHECK(NodeExists(node.parent_id));
  Node* parent = &all_nodes_[node.parent_id];
  
  parent->child_list->remove(node_id);
  parent->total_child_weights -= node.weight;

  
  if (node.child_list != NULL) {
    
    for (typename List::iterator it = node.child_list->begin();
         it != node.child_list->end(); ++it) {
      Node* child = &all_nodes_[*it];
      child->parent_id = node.parent_id;
      
      
      float float_weight =  node.weight * static_cast<float>(child->weight) /
                            static_cast<float>(node.total_child_weights);
      int new_weight = std::floor(float_weight + 0.5);
      if (new_weight == 0) {
        new_weight = 1;
      }
      child->weight = new_weight;
      parent->total_child_weights += child->weight;
    }
    parent->child_list->splice(parent->child_list->end(), *node.child_list);
  }

  
  all_nodes_.erase(node_id);
  return true;
}

template <typename NodeId>
int SpdyPriorityTree<NodeId>::GetWeight(NodeId node_id) const {
  const Node* node = FindNode(node_id);
  if (node != NULL) {
    return node->weight;
  }
  return 0;
}

template <typename NodeId>
NodeId SpdyPriorityTree<NodeId>::GetParent(NodeId node_id) const {
  const Node* node = FindNode(node_id);
  if (node != NULL && node->id != static_cast<NodeId>(kRootNodeId)) {
    return node->parent_id;
  }
  return static_cast<NodeId>(kRootNodeId);
}

template <typename NodeId>
std::list<NodeId>* SpdyPriorityTree<NodeId>::GetChildren(NodeId node_id) const {
  const Node* node = FindNode(node_id);
  if (node != NULL) {
    return node->child_list;
  }
  return NULL;
}

template <typename NodeId>
bool SpdyPriorityTree<NodeId>::SetWeight(
    NodeId node_id, int weight) {
  if (!NodeExists(node_id)) {
    return false;
  }
  if (weight < kMinWeight || weight > kMaxWeight) {
    return false;
  }

  Node* node = &all_nodes_[node_id];
  Node* parent = &all_nodes_[node->parent_id];

  parent->total_child_weights += (weight - node->weight);
  node->weight = weight;

  return true;
}


template <typename NodeId>
bool SpdyPriorityTree<NodeId>::SetParent(
    NodeId node_id, NodeId parent_id, bool exclusive) {
  if (!NodeExists(node_id) || !NodeExists(parent_id)) {
    return false;
  }
  if (node_id == parent_id) return false;

  Node* node = &all_nodes_[node_id];
  Node* new_parent = &all_nodes_[parent_id];
  
  if (node->parent_id == parent_id) {
    return true;
  }

  
  
  Node* last = new_parent;
  NodeId last_id = parent_id;
  bool cycle_exists = false;
  while (last->parent_id != static_cast<NodeId>(kRootNodeId)) {
    if (last->parent_id == node_id) {
      cycle_exists = true;
      break;
    }
    last_id = last->parent_id;
    DCHECK(NodeExists(last_id));
    last = &all_nodes_[last_id];
  }

  if (cycle_exists) {
    
    SetParent(parent_id, node->parent_id, false);
  }

  
  const NodeId old_parent_id = node->parent_id;
  DCHECK(NodeExists(old_parent_id));
  Node* old_parent = &all_nodes_[old_parent_id];
  old_parent->child_list->remove(node_id);
  old_parent->total_child_weights -= node->weight;

  
  node->parent_id = parent_id;
  new_parent->child_list->push_back(node_id);
  new_parent->total_child_weights += node->weight;
  return true;
}

template <typename NodeId>
bool SpdyPriorityTree<NodeId>::SetBlocked(NodeId node_id, bool blocked) {
  if (!NodeExists(node_id)) {
    return false;
  }

  Node* node = &all_nodes_[node_id];
  node->blocked = blocked;
  return true;
}

template <typename NodeId>
bool SpdyPriorityTree<NodeId>::SetReady(NodeId node_id, bool ready) {
  if (!NodeExists(node_id)) {
    return false;
  }
  Node* node = &all_nodes_[node_id];
  node->ready = ready;
  return true;
}

template <typename NodeId>
void SpdyPriorityTree<NodeId>::PropagateNodeState(NodeId node_id) {
  
  Node* node = &all_nodes_[node_id];
  node->total_writeable_child_weights = node->total_child_weights;
  for (typename List::iterator it = node->child_list->begin();
       it != node->child_list->end(); ++it) {
    PropagateNodeState(*it);
  }
  if (node->total_writeable_child_weights == 0 &&
      (node->blocked || !node->ready)) {
    
    Node* parent = &all_nodes_[node->parent_id];
    parent->total_writeable_child_weights -= node->weight;
  }
}

template <typename NodeId>
const typename SpdyPriorityTree<NodeId>::Node*
SpdyPriorityTree<NodeId>::FindNode(NodeId node_id) const {
  typename NodeMap::const_iterator iter = all_nodes_.find(node_id);
  if (iter == all_nodes_.end()) {
    return NULL;
  }
  return &iter->second;
}

template <typename NodeId>
bool SpdyPriorityTree<NodeId>::HasChild(NodeId parent_id,
                                        NodeId child_id) const {
  const Node* parent = FindNode(parent_id);
  return parent->child_list->end() !=
         std::find(parent->child_list->begin(),
                   parent->child_list->end(),
                   child_id);
}

template <typename NodeId>
std::vector<std::pair<NodeId, float> >
SpdyPriorityTree<NodeId>::GetPriorityList() {
  typedef std::pair<NodeId, float> PriorityNode;
  typedef std::vector<PriorityNode> PriorityList;
  PriorityList priority_list;

  
  
  PropagateNodeState(kRootNodeId);

  List queue;
  const Node* root_node = FindNode(kRootNodeId);
  DCHECK(root_node->priority == 1.0);
  
  for (typename List::iterator it = root_node->child_list->begin();
       it != root_node->child_list->end(); ++it) {
    queue.push_back(*it);
  }
  while (!queue.empty()) {
    NodeId current_node_id = queue.front();
    Node* current_node = &all_nodes_[current_node_id];
    const Node* parent_node = FindNode(current_node->parent_id);
    if (current_node->blocked || !current_node->ready) {
      if (current_node->total_writeable_child_weights > 0) {
        
        
        
        current_node->priority = parent_node->priority *
            (static_cast<float>(current_node->weight) /
             static_cast<float>(parent_node->total_writeable_child_weights));
        
        for (typename List::iterator it = current_node->child_list->begin();
             it != current_node->child_list->end(); ++it) {
          queue.push_back(*it);
        }
      } else {
        
        current_node->priority = 0;
      }
    } else {
      
      current_node->priority = parent_node->priority *
          (static_cast<float>(current_node->weight) /
           static_cast<float>(parent_node->total_writeable_child_weights));
      
      priority_list.push_back(PriorityNode(current_node_id,
                                           current_node->priority));
    }
    
    queue.pop_front();
  }

  
  std::sort(priority_list.begin(), priority_list.end(),
            NodePriorityComparator());

  return priority_list;
}

template <typename NodeId>
bool SpdyPriorityTree<NodeId>::ValidateInvariantsForTests() const {
  int total_nodes = 0;
  int nodes_visited = 0;
  
  for (typename NodeMap::const_iterator iter = all_nodes_.begin();
       iter != all_nodes_.end(); ++iter) {
    ++total_nodes;
    ++nodes_visited;
    const Node& node = iter->second;
    
    
    if (node.id != static_cast<NodeId>(kRootNodeId) &&
        (!NodeExists(node.parent_id) ||
         !HasChild(node.parent_id, node.id))) {
      DLOG(INFO) << "Parent node " << node.parent_id
                 << " does not exist, or does not list node " << node.id
                 << " as its child.";
      return false;
    }

    if (!node.child_list->empty()) {
      int total_child_weights = 0;
      
      for (typename List::iterator it = node.child_list->begin();
           it != node.child_list->end(); ++it) {
        ++nodes_visited;
        
        
        if (!NodeExists(*it) || node.id != GetParent(*it)) {
          DLOG(INFO) << "Child node " << *it << " does not exist, "
                     << "or does not list " << node.id << " as its parent.";
          return false;
        }
        const Node* child = FindNode(*it);
        total_child_weights += child->weight;
      }
      
      if (total_child_weights != node.total_child_weights) {
        DLOG(INFO) << "Child weight totals do not agree. For node " << node.id
                   << " total_child_weights has value "
                   << node.total_child_weights
                   << ", expected " << total_child_weights;
        return false;
      }
    }
  }

  
  if (total_nodes != num_nodes()) {
    DLOG(INFO) << "Map contains incorrect number of nodes.";
    return false;
  }
  
  
  DCHECK(nodes_visited == 2*num_nodes() - 1);
  return true;
}

}  

#endif  
