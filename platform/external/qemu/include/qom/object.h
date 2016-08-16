/*
 * QEMU Object Model
 *
 * Copyright IBM, Corp. 2011
 *
 * Authors:
 *  Anthony Liguori   <aliguori@us.ibm.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2 or later.
 * See the COPYING file in the top-level directory.
 *
 */

#ifndef QEMU_OBJECT_H
#define QEMU_OBJECT_H

#include <glib.h>
#include <stdint.h>
#include <stdbool.h>
#include "qemu/queue.h"
#include "qapi/error.h"

struct Visitor;

struct TypeImpl;
typedef struct TypeImpl *Type;

typedef struct ObjectClass ObjectClass;
typedef struct Object Object;

typedef struct TypeInfo TypeInfo;

typedef struct InterfaceClass InterfaceClass;
typedef struct InterfaceInfo InterfaceInfo;

#define TYPE_OBJECT "object"



typedef void (ObjectPropertyAccessor)(Object *obj,
                                      struct Visitor *v,
                                      void *opaque,
                                      const char *name,
                                      Error **errp);

typedef void (ObjectPropertyRelease)(Object *obj,
                                     const char *name,
                                     void *opaque);

typedef struct ObjectProperty
{
    gchar *name;
    gchar *type;
    ObjectPropertyAccessor *get;
    ObjectPropertyAccessor *set;
    ObjectPropertyRelease *release;
    void *opaque;

    QTAILQ_ENTRY(ObjectProperty) node;
} ObjectProperty;

typedef void (ObjectUnparent)(Object *obj);

typedef void (ObjectFree)(void *obj);

#define OBJECT_CLASS_CAST_CACHE 4

struct ObjectClass
{
    
    Type type;
    GSList *interfaces;

    const char *cast_cache[OBJECT_CLASS_CAST_CACHE];

    ObjectUnparent *unparent;
};

struct Object
{
    
    ObjectClass *class;
    ObjectFree *free;
    QTAILQ_HEAD(, ObjectProperty) properties;
    uint32_t ref;
    Object *parent;
};

struct TypeInfo
{
    const char *name;
    const char *parent;

    size_t instance_size;
    void (*instance_init)(Object *obj);
    void (*instance_post_init)(Object *obj);
    void (*instance_finalize)(Object *obj);

    bool abstract;
    size_t class_size;

    void (*class_init)(ObjectClass *klass, void *data);
    void (*class_base_init)(ObjectClass *klass, void *data);
    void (*class_finalize)(ObjectClass *klass, void *data);
    void *class_data;

    InterfaceInfo *interfaces;
};

#define OBJECT(obj) \
    ((Object *)(obj))

#define OBJECT_CLASS(class) \
    ((ObjectClass *)(class))

#define OBJECT_CHECK(type, obj, name) \
    ((type *)object_dynamic_cast_assert(OBJECT(obj), (name), \
                                        __FILE__, __LINE__, __func__))

#define OBJECT_CLASS_CHECK(class, obj, name) \
    ((class *)object_class_dynamic_cast_assert(OBJECT_CLASS(obj), (name), \
                                               __FILE__, __LINE__, __func__))

#define OBJECT_GET_CLASS(class, obj, name) \
    OBJECT_CLASS_CHECK(class, object_get_class(OBJECT(obj)), name)

struct InterfaceInfo {
    const char *type;
};

struct InterfaceClass
{
    ObjectClass parent_class;
    
    ObjectClass *concrete_class;
};

#define TYPE_INTERFACE "interface"

#define INTERFACE_CLASS(klass) \
    OBJECT_CLASS_CHECK(InterfaceClass, klass, TYPE_INTERFACE)

#define INTERFACE_CHECK(interface, obj, name) \
    ((interface *)object_dynamic_cast_assert(OBJECT((obj)), (name), \
                                             __FILE__, __LINE__, __func__))

Object *object_new(const char *typename);

Object *object_new_with_type(Type type);

void object_initialize_with_type(void *data, size_t size, Type type);

void object_initialize(void *obj, size_t size, const char *typename);

Object *object_dynamic_cast(Object *obj, const char *typename);

Object *object_dynamic_cast_assert(Object *obj, const char *typename,
                                   const char *file, int line, const char *func);

ObjectClass *object_get_class(Object *obj);

const char *object_get_typename(Object *obj);

Type type_register_static(const TypeInfo *info);

Type type_register(const TypeInfo *info);

ObjectClass *object_class_dynamic_cast_assert(ObjectClass *klass,
                                              const char *typename,
                                              const char *file, int line,
                                              const char *func);

ObjectClass *object_class_dynamic_cast(ObjectClass *klass,
                                       const char *typename);

ObjectClass *object_class_get_parent(ObjectClass *klass);

const char *object_class_get_name(ObjectClass *klass);

bool object_class_is_abstract(ObjectClass *klass);

ObjectClass *object_class_by_name(const char *typename);

void object_class_foreach(void (*fn)(ObjectClass *klass, void *opaque),
                          const char *implements_type, bool include_abstract,
                          void *opaque);

GSList *object_class_get_list(const char *implements_type,
                              bool include_abstract);

void object_ref(Object *obj);

void object_unref(Object *obj);

/**
 * object_property_add:
 * @obj: the object to add a property to
 * @name: the name of the property.  This can contain any character except for
 *  a forward slash.  In general, you should use hyphens '-' instead of
 *  underscores '_' when naming properties.
 * @type: the type name of the property.  This namespace is pretty loosely
 *   defined.  Sub namespaces are constructed by using a prefix and then
 *   to angle brackets.  For instance, the type 'virtio-net-pci' in the
 *   'link' namespace would be 'link<virtio-net-pci>'.
 * @get: The getter to be called to read a property.  If this is NULL, then
 *   the property cannot be read.
 * @set: the setter to be called to write a property.  If this is NULL,
 *   then the property cannot be written.
 * @release: called when the property is removed from the object.  This is
 *   meant to allow a property to free its opaque upon object
 *   destruction.  This may be NULL.
 * @opaque: an opaque pointer to pass to the callbacks for the property
 * @errp: returns an error if this function fails
 */
void object_property_add(Object *obj, const char *name, const char *type,
                         ObjectPropertyAccessor *get,
                         ObjectPropertyAccessor *set,
                         ObjectPropertyRelease *release,
                         void *opaque, Error **errp);

void object_property_del(Object *obj, const char *name, Error **errp);

ObjectProperty *object_property_find(Object *obj, const char *name,
                                     Error **errp);

void object_unparent(Object *obj);

/**
 * object_property_get:
 * @obj: the object
 * @v: the visitor that will receive the property value.  This should be an
 *   Output visitor and the data will be written with @name as the name.
 * @name: the name of the property
 * @errp: returns an error if this function fails
 *
 * Reads a property from a object.
 */
void object_property_get(Object *obj, struct Visitor *v, const char *name,
                         Error **errp);

/**
 * object_property_set_str:
 * @value: the value to be written to the property
 * @name: the name of the property
 * @errp: returns an error if this function fails
 *
 * Writes a string value to a property.
 */
void object_property_set_str(Object *obj, const char *value,
                             const char *name, Error **errp);

char *object_property_get_str(Object *obj, const char *name,
                              Error **errp);

/**
 * object_property_set_link:
 * @value: the value to be written to the property
 * @name: the name of the property
 * @errp: returns an error if this function fails
 *
 * Writes an object's canonical path to a property.
 */
void object_property_set_link(Object *obj, Object *value,
                              const char *name, Error **errp);

Object *object_property_get_link(Object *obj, const char *name,
                                 Error **errp);

/**
 * object_property_set_bool:
 * @value: the value to be written to the property
 * @name: the name of the property
 * @errp: returns an error if this function fails
 *
 * Writes a bool value to a property.
 */
void object_property_set_bool(Object *obj, bool value,
                              const char *name, Error **errp);

bool object_property_get_bool(Object *obj, const char *name,
                              Error **errp);

/**
 * object_property_set_int:
 * @value: the value to be written to the property
 * @name: the name of the property
 * @errp: returns an error if this function fails
 *
 * Writes an integer value to a property.
 */
void object_property_set_int(Object *obj, int64_t value,
                             const char *name, Error **errp);

int64_t object_property_get_int(Object *obj, const char *name,
                                Error **errp);

/**
 * object_property_set:
 * @obj: the object
 * @v: the visitor that will be used to write the property value.  This should
 *   be an Input visitor and the data will be first read with @name as the
 *   name and then written as the property value.
 * @name: the name of the property
 * @errp: returns an error if this function fails
 *
 * Writes a property to a object.
 */
void object_property_set(Object *obj, struct Visitor *v, const char *name,
                         Error **errp);

void object_property_parse(Object *obj, const char *string,
                           const char *name, Error **errp);

char *object_property_print(Object *obj, const char *name,
                            Error **errp);

const char *object_property_get_type(Object *obj, const char *name,
                                     Error **errp);

Object *object_get_root(void);

gchar *object_get_canonical_path(Object *obj);

Object *object_resolve_path(const char *path, bool *ambiguous);

Object *object_resolve_path_type(const char *path, const char *typename,
                                 bool *ambiguous);

Object *object_resolve_path_component(Object *parent, const gchar *part);

void object_property_add_child(Object *obj, const char *name,
                               Object *child, Error **errp);

void object_property_add_link(Object *obj, const char *name,
                              const char *type, Object **child,
                              Error **errp);

void object_property_add_str(Object *obj, const char *name,
                             char *(*get)(Object *, Error **),
                             void (*set)(Object *, const char *, Error **),
                             Error **errp);

void object_property_add_bool(Object *obj, const char *name,
                              bool (*get)(Object *, Error **),
                              void (*set)(Object *, bool, Error **),
                              Error **errp);

void object_property_add_uint8_ptr(Object *obj, const char *name,
                                   const uint8_t *v, Error **errp);

void object_property_add_uint16_ptr(Object *obj, const char *name,
                                    const uint16_t *v, Error **errp);

void object_property_add_uint32_ptr(Object *obj, const char *name,
                                    const uint32_t *v, Error **errp);

void object_property_add_uint64_ptr(Object *obj, const char *name,
                                    const uint64_t *v, Error **Errp);

int object_child_foreach(Object *obj, int (*fn)(Object *child, void *opaque),
                         void *opaque);

Object *container_get(Object *root, const char *path);


#endif
