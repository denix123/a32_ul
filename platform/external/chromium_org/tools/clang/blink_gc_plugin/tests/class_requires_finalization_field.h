// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CLASS_REQUIRES_FINALIZATION_H_
#define CLASS_REQUIRES_FINALIZATION_H_

#include "heap/stubs.h"

namespace blink {

class A : public GarbageCollected<A> {
public:
    virtual void trace(Visitor*) { }
};

class B {
public:
    ~B() { }
    void trace(Visitor*) { };
};

class C {
public:
    void trace(Visitor*) { };
};

} 

namespace WTF {

template<>
struct VectorTraits<blink::C> {
    static const bool needsDestruction = false;
};

} 

namespace blink {

class NeedsFinalizer : public A, public ScriptWrappable {
public:
    void trace(Visitor*);
private:
    Vector<Member<A> > m_as;
};

class AlsoNeedsFinalizer : public A {
public:
    void trace(Visitor*);
private:
    HeapVector<B, 10> m_bs;
};

class DoesNotNeedFinalizer : public A, public ScriptWrappable {
public:
    void trace(Visitor*);
private:
    HeapVector<B> m_bs;
};

class AlsoDoesNotNeedFinalizer : public A, public ScriptWrappable {
public:
    void trace(Visitor*);
private:
    HeapVector<Member<A>, 10> m_as;
    HeapVector<C, 10> m_cs;
};

}

#endif
