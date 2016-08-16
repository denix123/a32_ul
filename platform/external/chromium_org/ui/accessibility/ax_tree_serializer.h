// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_ACCESSIBILITY_AX_TREE_SERIALIZER_H_
#define UI_ACCESSIBILITY_AX_TREE_SERIALIZER_H_

#include <set>

#include "base/containers/hash_tables.h"
#include "base/logging.h"
#include "base/stl_util.h"
#include "ui/accessibility/ax_tree_source.h"
#include "ui/accessibility/ax_tree_update.h"

namespace ui {

struct ClientTreeNode;

template<typename AXSourceNode>
class AXTreeSerializer {
 public:
  explicit AXTreeSerializer(AXTreeSource<AXSourceNode>* tree);
  ~AXTreeSerializer();

  
  
  
  void Reset();

  
  void SerializeChanges(AXSourceNode node,
                        AXTreeUpdate* out_update);

  
  
  void DeleteClientSubtree(AXSourceNode node);

  
  
  
  
  
  
  void ChangeTreeSourceForTesting(AXTreeSource<AXSourceNode>* new_tree);

 private:
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  AXSourceNode LeastCommonAncestor(AXSourceNode node,
                                   ClientTreeNode* client_node);

  
  
  
  
  AXSourceNode LeastCommonAncestor(AXSourceNode node);

  
  
  
  
  bool AnyDescendantWasReparented(AXSourceNode node,
                                  AXSourceNode* out_lca);

  ClientTreeNode* ClientTreeNodeById(int32 id);

  
  
  void DeleteClientSubtree(ClientTreeNode* client_node);

  
  void SerializeChangedNodes(AXSourceNode node,
                             AXTreeUpdate* out_update);

  
  AXTreeSource<AXSourceNode>* tree_;

  
  ClientTreeNode* client_root_;

  
  base::hash_map<int32, ClientTreeNode*> client_id_map_;
};

struct AX_EXPORT ClientTreeNode {
  ClientTreeNode();
  virtual ~ClientTreeNode();
  int32 id;
  ClientTreeNode* parent;
  std::vector<ClientTreeNode*> children;
};

template<typename AXSourceNode>
AXTreeSerializer<AXSourceNode>::AXTreeSerializer(
    AXTreeSource<AXSourceNode>* tree)
    : tree_(tree),
      client_root_(NULL) {
}

template<typename AXSourceNode>
AXTreeSerializer<AXSourceNode>::~AXTreeSerializer() {
  Reset();
}

template<typename AXSourceNode>
void AXTreeSerializer<AXSourceNode>::Reset() {
  if (!client_root_)
    return;

  DeleteClientSubtree(client_root_);
  client_id_map_.erase(client_root_->id);
  delete client_root_;
  client_root_ = NULL;
}

template<typename AXSourceNode>
void AXTreeSerializer<AXSourceNode>::ChangeTreeSourceForTesting(
    AXTreeSource<AXSourceNode>* new_tree) {
  tree_ = new_tree;
}

template<typename AXSourceNode>
AXSourceNode AXTreeSerializer<AXSourceNode>::LeastCommonAncestor(
    AXSourceNode node, ClientTreeNode* client_node) {
  if (!tree_->IsValid(node) || client_node == NULL)
    return tree_->GetNull();

  std::vector<AXSourceNode> ancestors;
  while (tree_->IsValid(node)) {
    ancestors.push_back(node);
    node = tree_->GetParent(node);
  }

  std::vector<ClientTreeNode*> client_ancestors;
  while (client_node) {
    client_ancestors.push_back(client_node);
    client_node = client_node->parent;
  }

  
  
  
  AXSourceNode lca = tree_->GetNull();
  int source_index = static_cast<int>(ancestors.size() - 1);
  int client_index = static_cast<int>(client_ancestors.size() - 1);
  while (source_index >= 0 && client_index >= 0) {
    if (tree_->GetId(ancestors[source_index]) !=
            client_ancestors[client_index]->id) {
      return lca;
    }
    lca = ancestors[source_index];
    source_index--;
    client_index--;
  }
  return lca;
}

template<typename AXSourceNode>
AXSourceNode AXTreeSerializer<AXSourceNode>::LeastCommonAncestor(
    AXSourceNode node) {
  
  
  ClientTreeNode* client_node = ClientTreeNodeById(tree_->GetId(node));
  while (tree_->IsValid(node) && !client_node) {
    node = tree_->GetParent(node);
    if (tree_->IsValid(node))
      client_node = ClientTreeNodeById(tree_->GetId(node));
  }
  return LeastCommonAncestor(node, client_node);
}

template<typename AXSourceNode>
bool AXTreeSerializer<AXSourceNode>::AnyDescendantWasReparented(
    AXSourceNode node, AXSourceNode* out_lca) {
  bool result = false;
  int id = tree_->GetId(node);
  std::vector<AXSourceNode> children;
  tree_->GetChildren(node, &children);
  for (size_t i = 0; i < children.size(); ++i) {
    AXSourceNode& child = children[i];
    int child_id = tree_->GetId(child);
    ClientTreeNode* client_child = ClientTreeNodeById(child_id);
    if (client_child) {
      if (!client_child->parent) {
        
        
        *out_lca = tree_->GetNull();
        return true;
      } else if (client_child->parent->id != id) {
        
        
        *out_lca = LeastCommonAncestor(*out_lca, client_child);
        result = true;
      } else {
        
        
        
        continue;
      }
    }

    
    if (AnyDescendantWasReparented(child, out_lca))
      result = true;
  }
  return result;
}

template<typename AXSourceNode>
ClientTreeNode* AXTreeSerializer<AXSourceNode>::ClientTreeNodeById(int32 id) {
  base::hash_map<int32, ClientTreeNode*>::iterator iter =
      client_id_map_.find(id);
  if (iter != client_id_map_.end())
    return iter->second;
  else
    return NULL;
}

template<typename AXSourceNode>
void AXTreeSerializer<AXSourceNode>::SerializeChanges(
    AXSourceNode node,
    AXTreeUpdate* out_update) {
  
  
  AXSourceNode lca = LeastCommonAncestor(node);

  if (client_root_) {
    bool need_delete = false;
    if (tree_->IsValid(lca)) {
      
      
      
      if (AnyDescendantWasReparented(lca, &lca))
        need_delete = true;
    }

    if (!tree_->IsValid(lca)) {
      
      
      out_update->node_id_to_clear = client_root_->id;
      Reset();
    } else if (need_delete) {
      
      
      
      out_update->node_id_to_clear = tree_->GetId(lca);
      ClientTreeNode* client_lca = ClientTreeNodeById(tree_->GetId(lca));
      CHECK(client_lca);
      for (size_t i = 0; i < client_lca->children.size(); ++i) {
        client_id_map_.erase(client_lca->children[i]->id);
        DeleteClientSubtree(client_lca->children[i]);
        delete client_lca->children[i];
      }
      client_lca->children.clear();
    }
  }

  
  if (!tree_->IsValid(lca))
    lca = tree_->GetRoot();
  SerializeChangedNodes(lca, out_update);
}

template<typename AXSourceNode>
void AXTreeSerializer<AXSourceNode>::DeleteClientSubtree(AXSourceNode node) {
  ClientTreeNode* client_node = ClientTreeNodeById(tree_->GetId(node));
  if (client_node)
    DeleteClientSubtree(client_node);
}

template<typename AXSourceNode>
void AXTreeSerializer<AXSourceNode>::DeleteClientSubtree(
    ClientTreeNode* client_node) {
  for (size_t i = 0; i < client_node->children.size(); ++i) {
    client_id_map_.erase(client_node->children[i]->id);
    DeleteClientSubtree(client_node->children[i]);
    delete client_node->children[i];
  }
  client_node->children.clear();
}

template<typename AXSourceNode>
void AXTreeSerializer<AXSourceNode>::SerializeChangedNodes(
    AXSourceNode node,
    AXTreeUpdate* out_update) {
  
  
  
  
  
  
  

  
  
  
  
  int id = tree_->GetId(node);
  ClientTreeNode* client_node = ClientTreeNodeById(id);
  if (!client_node) {
    Reset();
    client_root_ = new ClientTreeNode();
    client_node = client_root_;
    client_node->id = id;
    client_node->parent = NULL;
    client_id_map_[client_node->id] = client_node;
  }

  
  
  
  base::hash_set<int32> new_child_ids;
  std::vector<AXSourceNode> children;
  tree_->GetChildren(node, &children);
  for (size_t i = 0; i < children.size(); ++i) {
    AXSourceNode& child = children[i];
    int new_child_id = tree_->GetId(child);
    new_child_ids.insert(new_child_id);

    
    
    ClientTreeNode* client_child = client_id_map_[new_child_id];
    CHECK(!client_child || client_child->parent == client_node);
  }

  
  
  
  
  
  
  base::hash_map<int32, ClientTreeNode*> client_child_id_map;
  std::vector<ClientTreeNode*> old_children;
  old_children.swap(client_node->children);
  for (size_t i = 0; i < old_children.size(); ++i) {
    ClientTreeNode* old_child = old_children[i];
    int old_child_id = old_child->id;
    if (new_child_ids.find(old_child_id) == new_child_ids.end()) {
      client_id_map_.erase(old_child_id);
      DeleteClientSubtree(old_child);
      delete old_child;
    } else {
      client_child_id_map[old_child_id] = old_child;
    }
  }

  
  
  out_update->nodes.push_back(AXNodeData());
  AXNodeData* serialized_node = &out_update->nodes.back();
  tree_->SerializeNode(node, serialized_node);
  
  
  if (serialized_node->id == client_root_->id &&
      (serialized_node->role != AX_ROLE_ROOT_WEB_AREA &&
       serialized_node->role != AX_ROLE_DESKTOP)) {
    serialized_node->role = AX_ROLE_ROOT_WEB_AREA;
  }
  serialized_node->child_ids.clear();

  
  
  
  std::vector<AXSourceNode> children_to_serialize;
  client_node->children.reserve(children.size());
  for (size_t i = 0; i < children.size(); ++i) {
    AXSourceNode& child = children[i];
    int child_id = tree_->GetId(child);

    
    
    if (new_child_ids.find(child_id) == new_child_ids.end())
      continue;

    new_child_ids.erase(child_id);
    serialized_node->child_ids.push_back(child_id);
    if (client_child_id_map.find(child_id) != client_child_id_map.end()) {
      ClientTreeNode* reused_child = client_child_id_map[child_id];
      client_node->children.push_back(reused_child);
    } else {
      ClientTreeNode* new_child = new ClientTreeNode();
      new_child->id = child_id;
      new_child->parent = client_node;
      client_node->children.push_back(new_child);
      client_id_map_[child_id] = new_child;
      children_to_serialize.push_back(child);
    }
  }

  
  for (size_t i = 0; i < children_to_serialize.size(); ++i)
    SerializeChangedNodes(children_to_serialize[i], out_update);
}

}  

#endif  
