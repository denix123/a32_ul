// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef FINALIZE_AFTER_DISPATCH_H_
#define FINALIZE_AFTER_DISPATCH_H_

#include "heap/stubs.h"

namespace blink {

class NeedsFinalize : public GarbageCollectedFinalized<NeedsFinalize> {
public:
    void trace(Visitor*);
    void traceAfterDispatch(Visitor*);
    
};

class NeedsDispatch : public GarbageCollectedFinalized<NeedsDispatch> {
public:
    void trace(Visitor*);
    
    void finalizeGarbageCollectedObject() { };
};

class NeedsFinalizedBase : public GarbageCollected<NeedsFinalizedBase> {
public:
    void trace(Visitor*) { };
    void traceAfterDispatch(Visitor*) { };
    void finalizeGarbageCollectedObject() { };
};

class A : GarbageCollectedFinalized<A> {
public:
    void trace(Visitor*);
    void traceAfterDispatch(Visitor*);
    void finalizeGarbageCollectedObject();
protected:
    enum Type { TB, TC, TD };
    A(Type type) : m_type(type) { }
private:
    Type m_type;
};

class B : public A {
public:
    B() : A(TB) { }
    ~B() { }
    void traceAfterDispatch(Visitor*);
private:
    Member<A> m_a;
};

class C : public A {
public:
    C() : A(TC) { }
    void traceAfterDispatch(Visitor*);
private:
    Member<A> m_a;
};

class Abstract : public A {
protected:
    Abstract(Type type) : A(type) { }
};

class D : public Abstract {
public:
    D() : Abstract(TD) { }
    void traceAfterDispatch(Visitor*);
private:
    Member<A> m_a;
};

}

#endif
