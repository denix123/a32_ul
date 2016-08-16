

#ifndef _ARRAYARRAY_H
#define _ARRAYARRAY_H


typedef struct arraydescr {
    int typecode;
    int itemsize;
    PyObject * (*getitem)(struct arrayobject *, Py_ssize_t);
    int (*setitem)(struct arrayobject *, Py_ssize_t, PyObject *);
#if PY_VERSION_HEX >= 0x03000000
    char *formats;
#endif    
} arraydescr;


struct arrayobject {
    PyObject_HEAD
    Py_ssize_t ob_size;
    union {
        char *ob_item;
        float *as_floats;
        double *as_doubles;
        int *as_ints;
        unsigned int *as_uints;
        unsigned char *as_uchars;
        signed char *as_schars;
        char *as_chars;
        unsigned long *as_ulongs;
        long *as_longs;
        short *as_shorts;
        unsigned short *as_ushorts;
        Py_UNICODE *as_pyunicodes;
        void *as_voidptr;
    } data;
    Py_ssize_t allocated;
    struct arraydescr *ob_descr;
    PyObject *weakreflist; 
#if PY_VERSION_HEX >= 0x03000000
        int ob_exports;  
#endif
};

#ifndef NO_NEWARRAY_INLINE
static CYTHON_INLINE PyObject * newarrayobject(PyTypeObject *type, Py_ssize_t size,
    struct arraydescr *descr) {
    arrayobject *op;
    size_t nbytes;

    if (size < 0) {
        PyErr_BadInternalCall();
        return NULL;
    }

    nbytes = size * descr->itemsize;
    
    if (nbytes / descr->itemsize != (size_t)size) {
        return PyErr_NoMemory();
    }
    op = (arrayobject *) type->tp_alloc(type, 0);
    if (op == NULL) {
        return NULL;
    }
    op->ob_descr = descr;
    op->allocated = size;
    op->weakreflist = NULL;
    op->ob_size = size;
    if (size <= 0) {
        op->data.ob_item = NULL;
    }
    else {
        op->data.ob_item = PyMem_NEW(char, nbytes);
        if (op->data.ob_item == NULL) {
            Py_DECREF(op);
            return PyErr_NoMemory();
        }
    }
    return (PyObject *) op;
}
#else
PyObject* newarrayobject(PyTypeObject *type, Py_ssize_t size,
    struct arraydescr *descr);
#endif 

static CYTHON_INLINE int resize(arrayobject *self, Py_ssize_t n) {
    void *items = (void*) self->data.ob_item;
    PyMem_Resize(items, char, (size_t)(n * self->ob_descr->itemsize));
    if (items == NULL) {
        PyErr_NoMemory();
        return -1;
    }    
    self->data.ob_item = (char*) items;
    self->ob_size = n;
    self->allocated = n;
    return 0;
}

static CYTHON_INLINE int resize_smart(arrayobject *self, Py_ssize_t n) {
    void *items = (void*) self->data.ob_item;
    Py_ssize_t newsize;
    if (n < self->allocated) {
        if (n*4 > self->allocated) {
            self->ob_size = n;
            return 0;
        }
    }
    newsize = n  * 3 / 2 + 1;
    PyMem_Resize(items, char, (size_t)(newsize * self->ob_descr->itemsize));
    if (items == NULL) {
        PyErr_NoMemory();
        return -1;
    }    
    self->data.ob_item = (char*) items;
    self->ob_size = n;
    self->allocated = newsize;
    return 0;
}

#endif
