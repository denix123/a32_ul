/*
 * QEMU Object Model.
 *
 * Based on ideas by Avi Kivity <avi@redhat.com>
 *
 * Copyright (C) 2009 Red Hat Inc.
 *
 * Authors:
 *  Luiz Capitulino <lcapitulino@redhat.com>
 *
 * This work is licensed under the terms of the GNU LGPL, version 2.1 or later.
 * See the COPYING.LIB file in the top-level directory.
 *
 * QObject Reference Counts Terminology
 * ------------------------------------
 *
 *  - Returning references: A function that returns an object may
 *  return it as either a weak or a strong reference.  If the reference
 *  is strong, you are responsible for calling QDECREF() on the reference
 *  when you are done.
 *
 *  If the reference is weak, the owner of the reference may free it at
 *  any time in the future.  Before storing the reference anywhere, you
 *  should call QINCREF() to make the reference strong.
 *
 *  - Transferring ownership: when you transfer ownership of a reference
 *  by calling a function, you are no longer responsible for calling
 *  QDECREF() when the reference is no longer needed.  In other words,
 *  when the function returns you must behave as if the reference to the
 *  passed object was weak.
 */
#ifndef QOBJECT_H
#define QOBJECT_H

#include <stddef.h>
#include <assert.h>

typedef enum {
    QTYPE_NONE,
    QTYPE_QINT,
    QTYPE_QSTRING,
    QTYPE_QDICT,
    QTYPE_QLIST,
    QTYPE_QFLOAT,
    QTYPE_QBOOL,
    QTYPE_QERROR,
    QTYPE_MAX,
} qtype_code;

struct QObject;

typedef struct QType {
    qtype_code code;
    void (*destroy)(struct QObject *);
} QType;

typedef struct QObject {
    const QType *type;
    size_t refcnt;
} QObject;

#define QObject_HEAD  \
    QObject base

#define QOBJECT(obj) (&(obj)->base)

#define QINCREF(obj)      \
    qobject_incref(QOBJECT(obj))

#define QDECREF(obj)              \
    qobject_decref(obj ? QOBJECT(obj) : NULL)

#define QOBJECT_INIT(obj, qtype_type)   \
    obj->base.refcnt = 1;               \
    obj->base.type   = qtype_type

static inline void qobject_incref(QObject *obj)
{
    if (obj)
        obj->refcnt++;
}

static inline void qobject_decref(QObject *obj)
{
    if (obj && --obj->refcnt == 0) {
        assert(obj->type != NULL);
        assert(obj->type->destroy != NULL);
        obj->type->destroy(obj);
    }
}

static inline qtype_code qobject_type(const QObject *obj)
{
    assert(obj->type != NULL);
    return obj->type->code;
}

#endif 