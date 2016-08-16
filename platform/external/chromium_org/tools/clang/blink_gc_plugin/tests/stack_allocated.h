// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STACK_ALLOCATED_H_
#define STACK_ALLOCATED_H_

#include "heap/stubs.h"

namespace blink {

class HeapObject;

class PartObject {
    DISALLOW_ALLOCATION();
private:
    Member<HeapObject> m_obj; 
};

class StackObject {
    STACK_ALLOCATED();
private:
    Member<HeapObject> m_obj; 
};

class AnotherStackObject : public PartObject { 
    STACK_ALLOCATED();
private:
    StackObject m_part; 
};

class HeapObject : public GarbageCollected<HeapObject> {
public:
    void trace(Visitor*);
private:
    StackObject m_part; 
};

class DerivedStackObject : public StackObject {
private:
    AnotherStackObject m_anotherPart; 
};

}

#endif
