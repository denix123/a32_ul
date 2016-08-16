

static PyObject* __Pyx_Globals(void); 



static PyObject* __Pyx_Globals(void) {
    Py_ssize_t i;
    
    PyObject *names = NULL;
    PyObject *globals = PyObject_GetAttr($module_cname, PYIDENT("__dict__"));
    if (!globals) {
        PyErr_SetString(PyExc_TypeError,
            "current module must have __dict__ attribute");
        goto bad;
    }
    names = PyObject_Dir($module_cname);
    if (!names)
        goto bad;
    for (i = PyList_GET_SIZE(names)-1; i >= 0; i--) {
#if CYTHON_COMPILING_IN_PYPY
        PyObject* name = PySequence_GetItem(names, i);
        if (!name)
            goto bad;
#else
        PyObject* name = PyList_GET_ITEM(names, i);
#endif
        if (!PyDict_Contains(globals, name)) {
            PyObject* value = __Pyx_GetAttr($module_cname, name);
            if (!value) {
#if CYTHON_COMPILING_IN_PYPY
                Py_DECREF(name);
#endif
                goto bad;
            }
            if (PyDict_SetItem(globals, name, value) < 0) {
#if CYTHON_COMPILING_IN_PYPY
                Py_DECREF(name);
#endif
                Py_DECREF(value);
                goto bad;
            }
        }
#if CYTHON_COMPILING_IN_PYPY
        Py_DECREF(name);
#endif
    }
    Py_DECREF(names);
    return globals;
    
    
    
bad:
    Py_XDECREF(names);
    Py_XDECREF(globals);
    return NULL;
}


static PyObject* __Pyx_PyExecGlobals(PyObject*);


static PyObject* __Pyx_PyExecGlobals(PyObject* code) {
    PyObject* result;
    PyObject* globals = __Pyx_Globals();
    if (unlikely(!globals))
        return NULL;
    result = __Pyx_PyExec2(code, globals);
    Py_DECREF(globals);
    return result;
}


static PyObject* __Pyx_PyExec3(PyObject*, PyObject*, PyObject*);
static CYTHON_INLINE PyObject* __Pyx_PyExec2(PyObject*, PyObject*);


static CYTHON_INLINE PyObject* __Pyx_PyExec2(PyObject* o, PyObject* globals) {
    return __Pyx_PyExec3(o, globals, NULL);
}

static PyObject* __Pyx_PyExec3(PyObject* o, PyObject* globals, PyObject* locals) {
    PyObject* result;
    PyObject* s = 0;
    char *code = 0;

    if (!globals || globals == Py_None) {
        globals = PyModule_GetDict($module_cname);
        if (!globals)
            goto bad;
    } else if (!PyDict_Check(globals)) {
        PyErr_Format(PyExc_TypeError, "exec() arg 2 must be a dict, not %.200s",
                     Py_TYPE(globals)->tp_name);
        goto bad;
    }
    if (!locals || locals == Py_None) {
        locals = globals;
    }

    if (PyDict_GetItem(globals, PYIDENT("__builtins__")) == NULL) {
        if (PyDict_SetItem(globals, PYIDENT("__builtins__"), PyEval_GetBuiltins()) < 0)
            goto bad;
    }

    if (PyCode_Check(o)) {
        if (PyCode_GetNumFree((PyCodeObject *)o) > 0) {
            PyErr_SetString(PyExc_TypeError,
                "code object passed to exec() may not contain free variables");
            goto bad;
        }
        #if PY_VERSION_HEX < 0x030200B1
        result = PyEval_EvalCode((PyCodeObject *)o, globals, locals);
        #else
        result = PyEval_EvalCode(o, globals, locals);
        #endif
    } else {
        PyCompilerFlags cf;
        cf.cf_flags = 0;
        if (PyUnicode_Check(o)) {
            cf.cf_flags = PyCF_SOURCE_IS_UTF8;
            s = PyUnicode_AsUTF8String(o);
            if (!s) goto bad;
            o = s;
        #if PY_MAJOR_VERSION >= 3
        } else if (!PyBytes_Check(o)) {
        #else
        } else if (!PyString_Check(o)) {
        #endif
            PyErr_Format(PyExc_TypeError,
                "exec: arg 1 must be string, bytes or code object, got %.200s",
                Py_TYPE(o)->tp_name);
            goto bad;
        }
        #if PY_MAJOR_VERSION >= 3
        code = PyBytes_AS_STRING(o);
        #else
        code = PyString_AS_STRING(o);
        #endif
        if (PyEval_MergeCompilerFlags(&cf)) {
            result = PyRun_StringFlags(code, Py_file_input, globals, locals, &cf);
        } else {
            result = PyRun_String(code, Py_file_input, globals, locals);
        }
        Py_XDECREF(s);
    }

    return result;
bad:
    Py_XDECREF(s);
    return 0;
}


static CYTHON_INLINE PyObject *__Pyx_GetAttr3(PyObject *, PyObject *, PyObject *); 


static CYTHON_INLINE PyObject *__Pyx_GetAttr3(PyObject *o, PyObject *n, PyObject *d) {
    PyObject *r = __Pyx_GetAttr(o, n);
    if (unlikely(!r)) {
        if (!PyErr_ExceptionMatches(PyExc_AttributeError))
            goto bad;
        PyErr_Clear();
        r = d;
        Py_INCREF(d);
    }
    return r;
bad:
    return NULL;
}


static PyObject* __Pyx_Intern(PyObject* s); 


static PyObject* __Pyx_Intern(PyObject* s) {
    if (!(likely(PyString_CheckExact(s)))) {
        PyErr_Format(PyExc_TypeError, "Expected %.16s, got %.200s", "str", Py_TYPE(s)->tp_name);
        return 0;
    }
    Py_INCREF(s);
    #if PY_MAJOR_VERSION >= 3
    PyUnicode_InternInPlace(&s);
    #else
    PyString_InternInPlace(&s);
    #endif
    return s;
}


static CYTHON_INLINE unsigned int __Pyx_abs_int(int x) {
    if (unlikely(x == -INT_MAX-1))
        return ((unsigned int)INT_MAX) + 1U;
    return (unsigned int) abs(x);
}


static CYTHON_INLINE unsigned long __Pyx_abs_long(long x) {
    if (unlikely(x == -LONG_MAX-1))
        return ((unsigned long)LONG_MAX) + 1U;
    return (unsigned long) labs(x);
}


static CYTHON_INLINE unsigned PY_LONG_LONG __Pyx_abs_longlong(PY_LONG_LONG x) {
#ifndef PY_LLONG_MAX
#ifdef LLONG_MAX
    const PY_LONG_LONG PY_LLONG_MAX = LLONG_MAX;
#else
    
    const PY_LONG_LONG PY_LLONG_MAX = (1 + 2 * ((1LL << (CHAR_BIT * sizeof(PY_LONG_LONG) - 2)) - 1));
#endif
#endif
    if (unlikely(x == -PY_LLONG_MAX-1))
        return ((unsigned PY_LONG_LONG)PY_LLONG_MAX) + 1U;
#if defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
    return (unsigned PY_LONG_LONG) llabs(x);
#else
    return (x<0) ? (unsigned PY_LONG_LONG)-x : (unsigned PY_LONG_LONG)x;
#endif
}


#define __Pyx_PyNumber_Power2(a, b) PyNumber_Power(a, b, Py_None)


static CYTHON_INLINE PyObject* __Pyx_PyDict_Keys(PyObject* d); 


static CYTHON_INLINE PyObject* __Pyx_PyDict_Keys(PyObject* d) {
    if (PY_MAJOR_VERSION >= 3)
        return __Pyx_PyObject_CallMethod1((PyObject*)&PyDict_Type, PYIDENT("keys"), d);
    else
        return PyDict_Keys(d);
}


static CYTHON_INLINE PyObject* __Pyx_PyDict_Values(PyObject* d); 


static CYTHON_INLINE PyObject* __Pyx_PyDict_Values(PyObject* d) {
    if (PY_MAJOR_VERSION >= 3)
        return __Pyx_PyObject_CallMethod1((PyObject*)&PyDict_Type, PYIDENT("values"), d);
    else
        return PyDict_Values(d);
}


static CYTHON_INLINE PyObject* __Pyx_PyDict_Items(PyObject* d); 


static CYTHON_INLINE PyObject* __Pyx_PyDict_Items(PyObject* d) {
    if (PY_MAJOR_VERSION >= 3)
        return __Pyx_PyObject_CallMethod1((PyObject*)&PyDict_Type, PYIDENT("items"), d);
    else
        return PyDict_Items(d);
}


static CYTHON_INLINE PyObject* __Pyx_PyDict_IterKeys(PyObject* d); 


static CYTHON_INLINE PyObject* __Pyx_PyDict_IterKeys(PyObject* d) {
    return __Pyx_PyObject_CallMethod0(d, (PY_MAJOR_VERSION >= 3) ? PYIDENT("keys") : PYIDENT("iterkeys"));
}


static CYTHON_INLINE PyObject* __Pyx_PyDict_IterValues(PyObject* d); 


static CYTHON_INLINE PyObject* __Pyx_PyDict_IterValues(PyObject* d) {
    return __Pyx_PyObject_CallMethod0(d, (PY_MAJOR_VERSION >= 3) ? PYIDENT("values") : PYIDENT("itervalues"));
}


static CYTHON_INLINE PyObject* __Pyx_PyDict_IterItems(PyObject* d); 


static CYTHON_INLINE PyObject* __Pyx_PyDict_IterItems(PyObject* d) {
    return __Pyx_PyObject_CallMethod0(d, (PY_MAJOR_VERSION >= 3) ? PYIDENT("items") : PYIDENT("iteritems"));
}


#if PY_VERSION_HEX < 0x02070000
#error This module uses dict views, which require Python 2.7 or later
#endif
static CYTHON_INLINE PyObject* __Pyx_PyDict_ViewKeys(PyObject* d); 


static CYTHON_INLINE PyObject* __Pyx_PyDict_ViewKeys(PyObject* d) {
    return __Pyx_PyObject_CallMethod0(d, (PY_MAJOR_VERSION >= 3) ? PYIDENT("keys") : PYIDENT("viewkeys"));
}


#if PY_VERSION_HEX < 0x02070000
#error This module uses dict views, which require Python 2.7 or later
#endif
static CYTHON_INLINE PyObject* __Pyx_PyDict_ViewValues(PyObject* d); 


static CYTHON_INLINE PyObject* __Pyx_PyDict_ViewValues(PyObject* d) {
    return __Pyx_PyObject_CallMethod0(d, (PY_MAJOR_VERSION >= 3) ? PYIDENT("values") : PYIDENT("viewvalues"));
}


#if PY_VERSION_HEX < 0x02070000
#error This module uses dict views, which require Python 2.7 or later
#endif
static CYTHON_INLINE PyObject* __Pyx_PyDict_ViewItems(PyObject* d); 


static CYTHON_INLINE PyObject* __Pyx_PyDict_ViewItems(PyObject* d) {
    return __Pyx_PyObject_CallMethod0(d, (PY_MAJOR_VERSION >= 3) ? PYIDENT("items") : PYIDENT("viewitems"));
}


#if PY_VERSION_HEX < 0x02050000
#ifndef PyAnySet_CheckExact

#define PyAnySet_CheckExact(ob) \
    ((ob)->ob_type == &PySet_Type || \
     (ob)->ob_type == &PyFrozenSet_Type)

#define PySet_New(iterable) \
    PyObject_CallFunctionObjArgs((PyObject *)&PySet_Type, (iterable), NULL)

#define PyFrozenSet_New(iterable) \
    PyObject_CallFunctionObjArgs((PyObject *)&PyFrozenSet_Type, (iterable), NULL)

#define PySet_Size(anyset) \
    PyObject_Size((anyset))

#define PySet_GET_SIZE(anyset) \
    PyObject_Size((anyset))

#define PySet_Contains(anyset, key) \
    PySequence_Contains((anyset), (key))

#define PySet_Pop(set) \
    PyObject_CallMethod((set), (char*)"pop", NULL)

static CYTHON_INLINE int PySet_Clear(PyObject *set) {
    PyObject *ret = PyObject_CallMethod(set, (char*)"clear", NULL);
    if (!ret) return -1;
    Py_DECREF(ret); return 0;
}

static CYTHON_INLINE int PySet_Discard(PyObject *set, PyObject *key) {
    PyObject *ret = PyObject_CallMethod(set, (char*)"discard", (char*)"(O)", key);
    if (!ret) return -1;
    Py_DECREF(ret); return 0;
}

static CYTHON_INLINE int PySet_Add(PyObject *set, PyObject *key) {
    PyObject *ret = PyObject_CallMethod(set, (char*)"add", (char*)"(O)", key);
    if (!ret) return -1;
    Py_DECREF(ret); return 0;
}

#endif 
#endif 


static CYTHON_INLINE PyObject* __Pyx_PyFrozenSet_New(PyObject* it) {
    if (it) {
        PyObject* result;
        if (PyFrozenSet_CheckExact(it)) {
            Py_INCREF(it);
            return it;
        }
        result = PyFrozenSet_New(it);
        if (unlikely(!result))
            return NULL;
        if (likely(PySet_GET_SIZE(result)))
            return result;
        
        
        Py_DECREF(result);
    }
    #if CYTHON_COMPILING_IN_CPYTHON
    return PyFrozenSet_Type.tp_new(&PyFrozenSet_Type, $empty_tuple, NULL);
    #else
    return PyObject_Call((PyObject*)&PyFrozenSet_Type, $empty_tuple, NULL);
    #endif
}
