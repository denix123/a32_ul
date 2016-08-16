// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEMBER_IN_OFFHEAP_CLASS_H_
#define MEMBER_IN_OFFHEAP_CLASS_H_

#include "heap/stubs.h"

namespace blink {

class HeapObject : public GarbageCollected<HeapObject> { };

class OffHeapObject {
public:
    void trace(Visitor*);
private:
    Member<HeapObject> m_obj; 
    Persistent<HeapVector<Member<HeapObject> > > m_objs; 
};

class StackObject {
    STACK_ALLOCATED();
private:
    Member<HeapObject> m_obj; 
};

class PartObject {
    DISALLOW_ALLOCATION();
public:
    void trace(Visitor*);
private:
    Member<HeapObject> m_obj; 
};

class InlineObject {
    ALLOW_ONLY_INLINE_ALLOCATION();
public:
    void trace(Visitor*);
private:
    Member<HeapObject> m_obj; 
};

}

#endif