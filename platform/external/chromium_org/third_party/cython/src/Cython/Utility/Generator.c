
static CYTHON_INLINE PyObject* __Pyx_Generator_Yield_From(__pyx_GeneratorObject *gen, PyObject *source);


static CYTHON_INLINE PyObject* __Pyx_Generator_Yield_From(__pyx_GeneratorObject *gen, PyObject *source) {
    PyObject *source_gen, *retval;
    source_gen = PyObject_GetIter(source);
    if (unlikely(!source_gen))
        return NULL;
    
    retval = Py_TYPE(source_gen)->tp_iternext(source_gen);
    if (likely(retval)) {
        gen->yieldfrom = source_gen;
        return retval;
    }
    Py_DECREF(source_gen);
    return NULL;
}

#define __Pyx_Generator_USED
#include <structmember.h>
#include <frameobject.h>

typedef PyObject *(*__pyx_generator_body_t)(PyObject *, PyObject *);

typedef struct {
    PyObject_HEAD
    __pyx_generator_body_t body;
    PyObject *closure;
    PyObject *exc_type;
    PyObject *exc_value;
    PyObject *exc_traceback;
    PyObject *gi_weakreflist;
    PyObject *classobj;
    PyObject *yieldfrom;
    int resume_label;
    
    char is_running;
} __pyx_GeneratorObject;

static __pyx_GeneratorObject *__Pyx_Generator_New(__pyx_generator_body_t body,
                                                  PyObject *closure);
static int __pyx_Generator_init(void);
static int __Pyx_Generator_clear(PyObject* self);

#if 1 || PY_VERSION_HEX < 0x030300B0
static int __Pyx_PyGen_FetchStopIterationValue(PyObject **pvalue);
#else
#define __Pyx_PyGen_FetchStopIterationValue(pvalue) PyGen_FetchStopIterationValue(pvalue)
#endif


static PyObject *__Pyx_Generator_Next(PyObject *self);
static PyObject *__Pyx_Generator_Send(PyObject *self, PyObject *value);
static PyObject *__Pyx_Generator_Close(PyObject *self);
static PyObject *__Pyx_Generator_Throw(PyObject *gen, PyObject *args);

static PyTypeObject *__pyx_GeneratorType = 0;

#define __Pyx_Generator_CheckExact(obj) (Py_TYPE(obj) == __pyx_GeneratorType)
#define __Pyx_Generator_Undelegate(gen) Py_CLEAR((gen)->yieldfrom)

#if 1 || PY_VERSION_HEX < 0x030300B0
static int __Pyx_PyGen_FetchStopIterationValue(PyObject **pvalue) {
    PyObject *et, *ev, *tb;
    PyObject *value = NULL;

    __Pyx_ErrFetch(&et, &ev, &tb);

    if (!et) {
        Py_XDECREF(tb);
        Py_XDECREF(ev);
        Py_INCREF(Py_None);
        *pvalue = Py_None;
        return 0;
    }

    if (unlikely(et != PyExc_StopIteration) &&
            unlikely(!PyErr_GivenExceptionMatches(et, PyExc_StopIteration))) {
        __Pyx_ErrRestore(et, ev, tb);
        return -1;
    }

    
    if (likely(et == PyExc_StopIteration)) {
        if (likely(!ev) || !PyObject_IsInstance(ev, PyExc_StopIteration)) {
            
            if (!ev) {
                Py_INCREF(Py_None);
                ev = Py_None;
            }
            Py_XDECREF(tb);
            Py_DECREF(et);
            *pvalue = ev;
            return 0;
        }
    }
    
    PyErr_NormalizeException(&et, &ev, &tb);
    if (unlikely(!PyObject_IsInstance(ev, PyExc_StopIteration))) {
        
        __Pyx_ErrRestore(et, ev, tb);
        return -1;
    }
    Py_XDECREF(tb);
    Py_DECREF(et);
#if PY_VERSION_HEX >= 0x030300A0
    value = ((PyStopIterationObject *)ev)->value;
    Py_INCREF(value);
    Py_DECREF(ev);
#else
    {
        PyObject* args = PyObject_GetAttr(ev, PYIDENT("args"));
        Py_DECREF(ev);
        if (likely(args)) {
            value = PyObject_GetItem(args, 0);
            Py_DECREF(args);
        }
        if (unlikely(!value)) {
            __Pyx_ErrRestore(NULL, NULL, NULL);
            Py_INCREF(Py_None);
            value = Py_None;
        }
    }
#endif
    *pvalue = value;
    return 0;
}
#endif

static CYTHON_INLINE
void __Pyx_Generator_ExceptionClear(__pyx_GeneratorObject *self) {
    PyObject *exc_type = self->exc_type;
    PyObject *exc_value = self->exc_value;
    PyObject *exc_traceback = self->exc_traceback;

    self->exc_type = NULL;
    self->exc_value = NULL;
    self->exc_traceback = NULL;

    Py_XDECREF(exc_type);
    Py_XDECREF(exc_value);
    Py_XDECREF(exc_traceback);
}

static CYTHON_INLINE
int __Pyx_Generator_CheckRunning(__pyx_GeneratorObject *gen) {
    if (unlikely(gen->is_running)) {
        PyErr_SetString(PyExc_ValueError,
                        "generator already executing");
        return 1;
    }
    return 0;
}

static CYTHON_INLINE
PyObject *__Pyx_Generator_SendEx(__pyx_GeneratorObject *self, PyObject *value) {
    PyObject *retval;

    assert(!self->is_running);

    if (unlikely(self->resume_label == 0)) {
        if (unlikely(value && value != Py_None)) {
            PyErr_SetString(PyExc_TypeError,
                            "can't send non-None value to a "
                            "just-started generator");
            return NULL;
        }
    }

    if (unlikely(self->resume_label == -1)) {
        PyErr_SetNone(PyExc_StopIteration);
        return NULL;
    }


    if (value) {
#if CYTHON_COMPILING_IN_PYPY
        
#else
        if (self->exc_traceback) {
            PyThreadState *tstate = PyThreadState_GET();
            PyTracebackObject *tb = (PyTracebackObject *) self->exc_traceback;
            PyFrameObject *f = tb->tb_frame;

            Py_XINCREF(tstate->frame);
            assert(f->f_back == NULL);
            f->f_back = tstate->frame;
        }
#endif
        __Pyx_ExceptionSwap(&self->exc_type, &self->exc_value,
                            &self->exc_traceback);
    } else {
        __Pyx_Generator_ExceptionClear(self);
    }

    self->is_running = 1;
    retval = self->body((PyObject *) self, value);
    self->is_running = 0;

    if (retval) {
        __Pyx_ExceptionSwap(&self->exc_type, &self->exc_value,
                            &self->exc_traceback);
#if CYTHON_COMPILING_IN_PYPY
        
#else
        if (self->exc_traceback) {
            PyTracebackObject *tb = (PyTracebackObject *) self->exc_traceback;
            PyFrameObject *f = tb->tb_frame;
            Py_CLEAR(f->f_back);
        }
#endif
    } else {
        __Pyx_Generator_ExceptionClear(self);
    }

    return retval;
}

static CYTHON_INLINE
PyObject *__Pyx_Generator_FinishDelegation(__pyx_GeneratorObject *gen) {
    PyObject *ret;
    PyObject *val = NULL;
    __Pyx_Generator_Undelegate(gen);
    __Pyx_PyGen_FetchStopIterationValue(&val);
    
    ret = __Pyx_Generator_SendEx(gen, val);
    Py_XDECREF(val);
    return ret;
}

static PyObject *__Pyx_Generator_Next(PyObject *self) {
    __pyx_GeneratorObject *gen = (__pyx_GeneratorObject*) self;
    PyObject *yf = gen->yieldfrom;
    if (unlikely(__Pyx_Generator_CheckRunning(gen)))
        return NULL;
    if (yf) {
        PyObject *ret;
        
        
        
        gen->is_running = 1;
        ret = Py_TYPE(yf)->tp_iternext(yf);
        gen->is_running = 0;
        
        if (likely(ret)) {
            return ret;
        }
        return __Pyx_Generator_FinishDelegation(gen);
    }
    return __Pyx_Generator_SendEx(gen, Py_None);
}

static PyObject *__Pyx_Generator_Send(PyObject *self, PyObject *value) {
    __pyx_GeneratorObject *gen = (__pyx_GeneratorObject*) self;
    PyObject *yf = gen->yieldfrom;
    if (unlikely(__Pyx_Generator_CheckRunning(gen)))
        return NULL;
    if (yf) {
        PyObject *ret;
        
        
        gen->is_running = 1;
        if (__Pyx_Generator_CheckExact(yf)) {
            ret = __Pyx_Generator_Send(yf, value);
        } else {
            if (value == Py_None)
                ret = PyIter_Next(yf);
            else
                ret = __Pyx_PyObject_CallMethod1(yf, PYIDENT("send"), value);
        }
        gen->is_running = 0;
        
        if (likely(ret)) {
            return ret;
        }
        return __Pyx_Generator_FinishDelegation(gen);
    }
    return __Pyx_Generator_SendEx(gen, value);
}

static int __Pyx_Generator_CloseIter(__pyx_GeneratorObject *gen, PyObject *yf) {
    PyObject *retval = NULL;
    int err = 0;

    if (__Pyx_Generator_CheckExact(yf)) {
        retval = __Pyx_Generator_Close(yf);
        if (!retval)
            return -1;
    } else {
        PyObject *meth;
        gen->is_running = 1;
        meth = PyObject_GetAttr(yf, PYIDENT("close"));
        if (unlikely(!meth)) {
            if (!PyErr_ExceptionMatches(PyExc_AttributeError)) {
                PyErr_WriteUnraisable(yf);
            }
            PyErr_Clear();
        } else {
            retval = PyObject_CallFunction(meth, NULL);
            Py_DECREF(meth);
            if (!retval)
                err = -1;
        }
        gen->is_running = 0;
    }
    Py_XDECREF(retval);
    return err;
}

static PyObject *__Pyx_Generator_Close(PyObject *self) {
    __pyx_GeneratorObject *gen = (__pyx_GeneratorObject *) self;
    PyObject *retval, *raised_exception;
    PyObject *yf = gen->yieldfrom;
    int err = 0;

    if (unlikely(__Pyx_Generator_CheckRunning(gen)))
        return NULL;

    if (yf) {
        Py_INCREF(yf);
        err = __Pyx_Generator_CloseIter(gen, yf);
        __Pyx_Generator_Undelegate(gen);
        Py_DECREF(yf);
    }
    if (err == 0)
#if PY_VERSION_HEX < 0x02050000
        PyErr_SetNone(PyExc_StopIteration);
#else
        PyErr_SetNone(PyExc_GeneratorExit);
#endif
    retval = __Pyx_Generator_SendEx(gen, NULL);
    if (retval) {
        Py_DECREF(retval);
        PyErr_SetString(PyExc_RuntimeError,
                        "generator ignored GeneratorExit");
        return NULL;
    }
    raised_exception = PyErr_Occurred();
    if (!raised_exception
        || raised_exception == PyExc_StopIteration
#if PY_VERSION_HEX >= 0x02050000
        || raised_exception == PyExc_GeneratorExit
        || PyErr_GivenExceptionMatches(raised_exception, PyExc_GeneratorExit)
#endif
        || PyErr_GivenExceptionMatches(raised_exception, PyExc_StopIteration))
    {
        if (raised_exception) PyErr_Clear();      
        Py_INCREF(Py_None);
        return Py_None;
    }
    return NULL;
}

static PyObject *__Pyx_Generator_Throw(PyObject *self, PyObject *args) {
    __pyx_GeneratorObject *gen = (__pyx_GeneratorObject *) self;
    PyObject *typ;
    PyObject *tb = NULL;
    PyObject *val = NULL;
    PyObject *yf = gen->yieldfrom;

    if (!PyArg_UnpackTuple(args, (char *)"throw", 1, 3, &typ, &val, &tb))
        return NULL;

    if (unlikely(__Pyx_Generator_CheckRunning(gen)))
        return NULL;

    if (yf) {
        PyObject *ret;
        Py_INCREF(yf);
#if PY_VERSION_HEX >= 0x02050000
        if (PyErr_GivenExceptionMatches(typ, PyExc_GeneratorExit)) {
            int err = __Pyx_Generator_CloseIter(gen, yf);
            Py_DECREF(yf);
            __Pyx_Generator_Undelegate(gen);
            if (err < 0)
                return __Pyx_Generator_SendEx(gen, NULL);
            goto throw_here;
        }
#endif
        gen->is_running = 1;
        if (__Pyx_Generator_CheckExact(yf)) {
            ret = __Pyx_Generator_Throw(yf, args);
        } else {
            PyObject *meth = PyObject_GetAttr(yf, PYIDENT("throw"));
            if (unlikely(!meth)) {
                Py_DECREF(yf);
                if (!PyErr_ExceptionMatches(PyExc_AttributeError)) {
                    gen->is_running = 0;
                    return NULL;
                }
                PyErr_Clear();
                __Pyx_Generator_Undelegate(gen);
                gen->is_running = 0;
                goto throw_here;
            }
            ret = PyObject_CallObject(meth, args);
            Py_DECREF(meth);
        }
        gen->is_running = 0;
        Py_DECREF(yf);
        if (!ret) {
            ret = __Pyx_Generator_FinishDelegation(gen);
        }
        return ret;
    }
throw_here:
    __Pyx_Raise(typ, val, tb, NULL);
    return __Pyx_Generator_SendEx(gen, NULL);
}

static int __Pyx_Generator_traverse(PyObject *self, visitproc visit, void *arg) {
    __pyx_GeneratorObject *gen = (__pyx_GeneratorObject *) self;

    Py_VISIT(gen->closure);
    Py_VISIT(gen->classobj);
    Py_VISIT(gen->yieldfrom);
    Py_VISIT(gen->exc_type);
    Py_VISIT(gen->exc_value);
    Py_VISIT(gen->exc_traceback);
    return 0;
}

static int __Pyx_Generator_clear(PyObject *self) {
    __pyx_GeneratorObject *gen = (__pyx_GeneratorObject *) self;

    Py_CLEAR(gen->closure);
    Py_CLEAR(gen->classobj);
    Py_CLEAR(gen->yieldfrom);
    Py_CLEAR(gen->exc_type);
    Py_CLEAR(gen->exc_value);
    Py_CLEAR(gen->exc_traceback);
    return 0;
}

static void __Pyx_Generator_dealloc(PyObject *self) {
    __pyx_GeneratorObject *gen = (__pyx_GeneratorObject *) self;

    PyObject_GC_UnTrack(gen);
    if (gen->gi_weakreflist != NULL)
        PyObject_ClearWeakRefs(self);

    if (gen->resume_label > 0) {
        
        PyObject_GC_Track(self);
#if PY_VERSION_HEX >= 0x030400a1
        if (PyObject_CallFinalizerFromDealloc(self))
#else
        Py_TYPE(gen)->tp_del(self);
        if (self->ob_refcnt > 0)
#endif
            return;                     
        PyObject_GC_UnTrack(self);
    }

    __Pyx_Generator_clear(self);
    PyObject_GC_Del(gen);
}

static void __Pyx_Generator_del(PyObject *self) {
    PyObject *res;
    PyObject *error_type, *error_value, *error_traceback;
    __pyx_GeneratorObject *gen = (__pyx_GeneratorObject *) self;

    if (gen->resume_label <= 0)
        return ;

#if PY_VERSION_HEX < 0x030400a1
    
    assert(self->ob_refcnt == 0);
    self->ob_refcnt = 1;
#endif

    
    __Pyx_ErrFetch(&error_type, &error_value, &error_traceback);

    res = __Pyx_Generator_Close(self);

    if (res == NULL)
        PyErr_WriteUnraisable(self);
    else
        Py_DECREF(res);

    
    __Pyx_ErrRestore(error_type, error_value, error_traceback);

#if PY_VERSION_HEX < 0x030400a1
    assert(self->ob_refcnt > 0);
    if (--self->ob_refcnt == 0)
        return; 

    {
        Py_ssize_t refcnt = self->ob_refcnt;
        _Py_NewReference(self);
        self->ob_refcnt = refcnt;
    }
#if CYTHON_COMPILING_IN_CPYTHON
    assert(PyType_IS_GC(self->ob_type) &&
           _Py_AS_GC(self)->gc.gc_refs != _PyGC_REFS_UNTRACKED);

    _Py_DEC_REFTOTAL;
#endif
#ifdef COUNT_ALLOCS
    --Py_TYPE(self)->tp_frees;
    --Py_TYPE(self)->tp_allocs;
#endif
#endif
}

static PyMemberDef __pyx_Generator_memberlist[] = {
    {(char *) "gi_running",
#if PY_VERSION_HEX >= 0x02060000
     T_BOOL,
#else
     T_BYTE,
#endif
     offsetof(__pyx_GeneratorObject, is_running),
     READONLY,
     NULL},
    {0, 0, 0, 0, 0}
};

static PyMethodDef __pyx_Generator_methods[] = {
    {__Pyx_NAMESTR("send"), (PyCFunction) __Pyx_Generator_Send, METH_O, 0},
    {__Pyx_NAMESTR("throw"), (PyCFunction) __Pyx_Generator_Throw, METH_VARARGS, 0},
    {__Pyx_NAMESTR("close"), (PyCFunction) __Pyx_Generator_Close, METH_NOARGS, 0},
    {0, 0, 0, 0}
};

static PyTypeObject __pyx_GeneratorType_type = {
    PyVarObject_HEAD_INIT(0, 0)
    __Pyx_NAMESTR("generator"),         
    sizeof(__pyx_GeneratorObject),      
    0,                                  
    (destructor) __Pyx_Generator_dealloc,
    0,                                  
    0,                                  
    0,                                  
#if PY_MAJOR_VERSION < 3
    0,                                  
#else
    0,                                  
#endif
    0,                                   
    0,                                  
    0,                                  
    0,                                  
    0,                                  
    0,                                  
    0,                                  
    0,                                  
    0,                                  
    0,                                  
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_GC | Py_TPFLAGS_HAVE_FINALIZE, 
    0,                                  
    (traverseproc) __Pyx_Generator_traverse,   
    0,                                  
    0,                                  
    offsetof(__pyx_GeneratorObject, gi_weakreflist), 
    0,                                  
    (iternextfunc) __Pyx_Generator_Next, 
    __pyx_Generator_methods,            
    __pyx_Generator_memberlist,         
    0,                                  
    0,                                  
    0,                                  
    0,                                  
    0,                                  
    0,                                  
    0,                                  
    0,                                  
    0,                                  
    0,                                  
    0,                                  
    0,                                  
    0,                                  
    0,                                  
    0,                                  
    0,                                  
#if PY_VERSION_HEX >= 0x030400a1
    0,                                  
#else
    __Pyx_Generator_del,                
#endif
#if PY_VERSION_HEX >= 0x02060000
    0,                                  
#endif
#if PY_VERSION_HEX >= 0x030400a1
    __Pyx_Generator_del,                
#endif
};

static __pyx_GeneratorObject *__Pyx_Generator_New(__pyx_generator_body_t body,
                                                  PyObject *closure) {
    __pyx_GeneratorObject *gen =
        PyObject_GC_New(__pyx_GeneratorObject, &__pyx_GeneratorType_type);

    if (gen == NULL)
        return NULL;

    gen->body = body;
    gen->closure = closure;
    Py_XINCREF(closure);
    gen->is_running = 0;
    gen->resume_label = 0;
    gen->classobj = NULL;
    gen->yieldfrom = NULL;
    gen->exc_type = NULL;
    gen->exc_value = NULL;
    gen->exc_traceback = NULL;
    gen->gi_weakreflist = NULL;

    PyObject_GC_Track(gen);
    return gen;
}

static int __pyx_Generator_init(void) {
    
    __pyx_GeneratorType_type.tp_getattro = PyObject_GenericGetAttr;
    __pyx_GeneratorType_type.tp_iter = PyObject_SelfIter;

    __pyx_GeneratorType = __Pyx_FetchCommonType(&__pyx_GeneratorType_type);
    if (__pyx_GeneratorType == NULL) {
        return -1;
    }
    return 0;
}
