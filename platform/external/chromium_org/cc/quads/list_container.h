// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CC_QUADS_LIST_CONTAINER_H_
#define CC_QUADS_LIST_CONTAINER_H_

#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "cc/base/cc_export.h"

namespace cc {
class SharedQuadState;
class DrawQuad;

template <class BaseElementType>
class CC_EXPORT ListContainer {
 public:
  
  
  
  
  explicit ListContainer(size_t max_size_for_derived_class);
  
  
  
  ListContainer();
  
  
  ListContainer(size_t max_size_for_derived_class,
                size_t num_of_elements_to_reserve_for);

  ~ListContainer();

  
  
  class CC_EXPORT ListContainerCharAllocator;

  
  
  struct CC_EXPORT PositionInListContainerCharAllocator {
    ListContainerCharAllocator* ptr_to_container;
    size_t vector_index;
    char* item_iterator;

    PositionInListContainerCharAllocator(
        const PositionInListContainerCharAllocator& other);

    PositionInListContainerCharAllocator(ListContainerCharAllocator* container,
                                         size_t vector_ind,
                                         char* item_iter);

    bool operator==(const PositionInListContainerCharAllocator& other) const;
    bool operator!=(const PositionInListContainerCharAllocator& other) const;

    PositionInListContainerCharAllocator Increment();
    PositionInListContainerCharAllocator ReverseIncrement();
  };

  
  
  class CC_EXPORT Iterator : public PositionInListContainerCharAllocator {
    
    
   public:
    Iterator(ListContainerCharAllocator* container,
             size_t vector_ind,
             char* item_iter);
    ~Iterator();
    BaseElementType* operator->() const;
    BaseElementType& operator*() const;
    Iterator operator++(int unused_post_increment);
    Iterator operator++();
  };

  class CC_EXPORT ConstIterator : public PositionInListContainerCharAllocator {
    
    
   public:
    ConstIterator(ListContainerCharAllocator* container,
                  size_t vector_ind,
                  char* item_iter);
    ConstIterator(const Iterator& other);  
    ~ConstIterator();
    const BaseElementType* operator->() const;
    const BaseElementType& operator*() const;
    ConstIterator operator++(int unused_post_increment);
    ConstIterator operator++();
  };

  class CC_EXPORT ReverseIterator
      : public PositionInListContainerCharAllocator {
    
    
   public:
    ReverseIterator(ListContainerCharAllocator* container,
                    size_t vector_ind,
                    char* item_iter);
    ~ReverseIterator();
    BaseElementType* operator->() const;
    BaseElementType& operator*() const;
    ReverseIterator operator++(int unused_post_increment);
    ReverseIterator operator++();
  };

  class CC_EXPORT ConstReverseIterator
      : public PositionInListContainerCharAllocator {
    
    
   public:
    ConstReverseIterator(ListContainerCharAllocator* container,
                         size_t vector_ind,
                         char* item_iter);
    ConstReverseIterator(const ReverseIterator& other);  
    ~ConstReverseIterator();
    const BaseElementType* operator->() const;
    const BaseElementType& operator*() const;
    ConstReverseIterator operator++(int unused_post_increment);
    ConstReverseIterator operator++();
  };

  
  
  
  void EraseAndInvalidateAllPointers(Iterator position);

  ConstReverseIterator rbegin() const;
  ConstReverseIterator rend() const;
  ReverseIterator rbegin();
  ReverseIterator rend();
  ConstIterator begin() const;
  ConstIterator end() const;
  Iterator begin();
  Iterator end();

  BaseElementType* front();
  BaseElementType* back();
  const BaseElementType* front() const;
  const BaseElementType* back() const;

  BaseElementType* ElementAt(size_t index);
  const BaseElementType* ElementAt(size_t index) const;

  
  
  template <typename DerivedElementType>
  DerivedElementType* AllocateAndConstruct() {
    return new (Allocate(sizeof(DerivedElementType))) DerivedElementType;
  }
  
  
  template <typename DerivedElementType>
  DerivedElementType* AllocateAndCopyFrom(const DerivedElementType* source) {
    return new (Allocate(sizeof(DerivedElementType)))
        DerivedElementType(*source);
  }

  size_t size() const;
  bool empty() const;
  void clear();

  size_t AvailableSizeWithoutAnotherAllocationForTesting() const;

 private:
  
  BaseElementType* Allocate(size_t size_of_actual_element_in_bytes);

  scoped_ptr<ListContainerCharAllocator> data_;

  DISALLOW_COPY_AND_ASSIGN(ListContainer);
};

#if !defined(COMPILER_MSVC)
extern template class ListContainer<SharedQuadState>;
extern template class ListContainer<DrawQuad>;
#endif
}  

#endif  
