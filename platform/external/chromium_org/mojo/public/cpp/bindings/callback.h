


// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_CPP_BINDINGS_CALLBACK_H_
#define MOJO_PUBLIC_CPP_BINDINGS_CALLBACK_H_

#include "mojo/public/cpp/bindings/lib/callback_internal.h"
#include "mojo/public/cpp/bindings/lib/shared_ptr.h"
#include "mojo/public/cpp/bindings/lib/template_util.h"

namespace mojo {

template <typename Sig>
class Callback;

template <>
class Callback<void()> {
 public:
  struct Runnable {
    virtual ~Runnable() {}
    virtual void Run() const = 0;
  };

  Callback() {}

  
  explicit Callback(Runnable* runnable) : sink_(runnable) {}

  
  
  template <typename Sink>
  Callback(const Sink& sink) : sink_(new Adapter<Sink>(sink)) {}

  void Run() const {
    if (sink_.get())
      sink_->Run();
  }

  bool is_null() const {
    return !sink_.get();
  }

 private:
  template <typename Sink>
  struct Adapter : public Runnable {
    explicit Adapter(const Sink& sink) : sink(sink) {}
    virtual void Run() const MOJO_OVERRIDE {
      sink.Run();
    }
    Sink sink;
  };

  internal::SharedPtr<Runnable> sink_;
};

template <typename A1>
class Callback<void(A1)> {
 public:
  struct Runnable {
    virtual ~Runnable() {}
    virtual void Run(
        typename internal::Callback_ParamTraits<A1>::ForwardType a1) const = 0;
  };

  Callback() {}

  
  explicit Callback(Runnable* runnable) : sink_(runnable) {}

  
  
  template <typename Sink>
  Callback(const Sink& sink) : sink_(new Adapter<Sink>(sink)) {}

  void Run(typename internal::Callback_ParamTraits<A1>::ForwardType a1) const {
    if (sink_.get())
      sink_->Run(internal::Forward(a1));
  }

  bool is_null() const {
    return !sink_.get();
  }

 private:
  template <typename Sink>
  struct Adapter : public Runnable {
    explicit Adapter(const Sink& sink) : sink(sink) {}
    virtual void Run(
        typename internal::Callback_ParamTraits<A1>::ForwardType a1) const
            MOJO_OVERRIDE {
      sink.Run(internal::Forward(a1));
    }
    Sink sink;
  };

  internal::SharedPtr<Runnable> sink_;
};

template <typename A1, typename A2>
class Callback<void(A1, A2)> {
 public:
  struct Runnable {
    virtual ~Runnable() {}
    virtual void Run(
        typename internal::Callback_ParamTraits<A1>::ForwardType a1,
        typename internal::Callback_ParamTraits<A2>::ForwardType a2) const = 0;
  };

  Callback() {}

  
  explicit Callback(Runnable* runnable) : sink_(runnable) {}

  
  
  template <typename Sink>
  Callback(const Sink& sink) : sink_(new Adapter<Sink>(sink)) {}

  void Run(
      typename internal::Callback_ParamTraits<A1>::ForwardType a1,
      typename internal::Callback_ParamTraits<A2>::ForwardType a2) const {
    if (sink_.get())
      sink_->Run(
          internal::Forward(a1),
          internal::Forward(a2));
  }

  bool is_null() const {
    return !sink_.get();
  }

 private:
  template <typename Sink>
  struct Adapter : public Runnable {
    explicit Adapter(const Sink& sink) : sink(sink) {}
    virtual void Run(
        typename internal::Callback_ParamTraits<A1>::ForwardType a1,
        typename internal::Callback_ParamTraits<A2>::ForwardType a2) const
            MOJO_OVERRIDE {
      sink.Run(
          internal::Forward(a1),
          internal::Forward(a2));
    }
    Sink sink;
  };

  internal::SharedPtr<Runnable> sink_;
};

template <typename A1, typename A2, typename A3>
class Callback<void(A1, A2, A3)> {
 public:
  struct Runnable {
    virtual ~Runnable() {}
    virtual void Run(
        typename internal::Callback_ParamTraits<A1>::ForwardType a1,
        typename internal::Callback_ParamTraits<A2>::ForwardType a2,
        typename internal::Callback_ParamTraits<A3>::ForwardType a3) const = 0;
  };

  Callback() {}

  
  explicit Callback(Runnable* runnable) : sink_(runnable) {}

  
  
  template <typename Sink>
  Callback(const Sink& sink) : sink_(new Adapter<Sink>(sink)) {}

  void Run(
      typename internal::Callback_ParamTraits<A1>::ForwardType a1,
      typename internal::Callback_ParamTraits<A2>::ForwardType a2,
      typename internal::Callback_ParamTraits<A3>::ForwardType a3) const {
    if (sink_.get())
      sink_->Run(
          internal::Forward(a1),
          internal::Forward(a2),
          internal::Forward(a3));
  }

  bool is_null() const {
    return !sink_.get();
  }

 private:
  template <typename Sink>
  struct Adapter : public Runnable {
    explicit Adapter(const Sink& sink) : sink(sink) {}
    virtual void Run(
        typename internal::Callback_ParamTraits<A1>::ForwardType a1,
        typename internal::Callback_ParamTraits<A2>::ForwardType a2,
        typename internal::Callback_ParamTraits<A3>::ForwardType a3) const
            MOJO_OVERRIDE {
      sink.Run(
          internal::Forward(a1),
          internal::Forward(a2),
          internal::Forward(a3));
    }
    Sink sink;
  };

  internal::SharedPtr<Runnable> sink_;
};

template <typename A1, typename A2, typename A3, typename A4>
class Callback<void(A1, A2, A3, A4)> {
 public:
  struct Runnable {
    virtual ~Runnable() {}
    virtual void Run(
        typename internal::Callback_ParamTraits<A1>::ForwardType a1,
        typename internal::Callback_ParamTraits<A2>::ForwardType a2,
        typename internal::Callback_ParamTraits<A3>::ForwardType a3,
        typename internal::Callback_ParamTraits<A4>::ForwardType a4) const = 0;
  };

  Callback() {}

  
  explicit Callback(Runnable* runnable) : sink_(runnable) {}

  
  
  template <typename Sink>
  Callback(const Sink& sink) : sink_(new Adapter<Sink>(sink)) {}

  void Run(
      typename internal::Callback_ParamTraits<A1>::ForwardType a1,
      typename internal::Callback_ParamTraits<A2>::ForwardType a2,
      typename internal::Callback_ParamTraits<A3>::ForwardType a3,
      typename internal::Callback_ParamTraits<A4>::ForwardType a4) const {
    if (sink_.get())
      sink_->Run(
          internal::Forward(a1),
          internal::Forward(a2),
          internal::Forward(a3),
          internal::Forward(a4));
  }

  bool is_null() const {
    return !sink_.get();
  }

 private:
  template <typename Sink>
  struct Adapter : public Runnable {
    explicit Adapter(const Sink& sink) : sink(sink) {}
    virtual void Run(
        typename internal::Callback_ParamTraits<A1>::ForwardType a1,
        typename internal::Callback_ParamTraits<A2>::ForwardType a2,
        typename internal::Callback_ParamTraits<A3>::ForwardType a3,
        typename internal::Callback_ParamTraits<A4>::ForwardType a4) const
            MOJO_OVERRIDE {
      sink.Run(
          internal::Forward(a1),
          internal::Forward(a2),
          internal::Forward(a3),
          internal::Forward(a4));
    }
    Sink sink;
  };

  internal::SharedPtr<Runnable> sink_;
};

template <typename A1, typename A2, typename A3, typename A4, typename A5>
class Callback<void(A1, A2, A3, A4, A5)> {
 public:
  struct Runnable {
    virtual ~Runnable() {}
    virtual void Run(
        typename internal::Callback_ParamTraits<A1>::ForwardType a1,
        typename internal::Callback_ParamTraits<A2>::ForwardType a2,
        typename internal::Callback_ParamTraits<A3>::ForwardType a3,
        typename internal::Callback_ParamTraits<A4>::ForwardType a4,
        typename internal::Callback_ParamTraits<A5>::ForwardType a5) const = 0;
  };

  Callback() {}

  
  explicit Callback(Runnable* runnable) : sink_(runnable) {}

  
  
  template <typename Sink>
  Callback(const Sink& sink) : sink_(new Adapter<Sink>(sink)) {}

  void Run(
      typename internal::Callback_ParamTraits<A1>::ForwardType a1,
      typename internal::Callback_ParamTraits<A2>::ForwardType a2,
      typename internal::Callback_ParamTraits<A3>::ForwardType a3,
      typename internal::Callback_ParamTraits<A4>::ForwardType a4,
      typename internal::Callback_ParamTraits<A5>::ForwardType a5) const {
    if (sink_.get())
      sink_->Run(
          internal::Forward(a1),
          internal::Forward(a2),
          internal::Forward(a3),
          internal::Forward(a4),
          internal::Forward(a5));
  }

  bool is_null() const {
    return !sink_.get();
  }

 private:
  template <typename Sink>
  struct Adapter : public Runnable {
    explicit Adapter(const Sink& sink) : sink(sink) {}
    virtual void Run(
        typename internal::Callback_ParamTraits<A1>::ForwardType a1,
        typename internal::Callback_ParamTraits<A2>::ForwardType a2,
        typename internal::Callback_ParamTraits<A3>::ForwardType a3,
        typename internal::Callback_ParamTraits<A4>::ForwardType a4,
        typename internal::Callback_ParamTraits<A5>::ForwardType a5) const
            MOJO_OVERRIDE {
      sink.Run(
          internal::Forward(a1),
          internal::Forward(a2),
          internal::Forward(a3),
          internal::Forward(a4),
          internal::Forward(a5));
    }
    Sink sink;
  };

  internal::SharedPtr<Runnable> sink_;
};

template <typename A1, typename A2, typename A3, typename A4, typename A5,
    typename A6>
class Callback<void(A1, A2, A3, A4, A5, A6)> {
 public:
  struct Runnable {
    virtual ~Runnable() {}
    virtual void Run(
        typename internal::Callback_ParamTraits<A1>::ForwardType a1,
        typename internal::Callback_ParamTraits<A2>::ForwardType a2,
        typename internal::Callback_ParamTraits<A3>::ForwardType a3,
        typename internal::Callback_ParamTraits<A4>::ForwardType a4,
        typename internal::Callback_ParamTraits<A5>::ForwardType a5,
        typename internal::Callback_ParamTraits<A6>::ForwardType a6) const = 0;
  };

  Callback() {}

  
  explicit Callback(Runnable* runnable) : sink_(runnable) {}

  
  
  template <typename Sink>
  Callback(const Sink& sink) : sink_(new Adapter<Sink>(sink)) {}

  void Run(
      typename internal::Callback_ParamTraits<A1>::ForwardType a1,
      typename internal::Callback_ParamTraits<A2>::ForwardType a2,
      typename internal::Callback_ParamTraits<A3>::ForwardType a3,
      typename internal::Callback_ParamTraits<A4>::ForwardType a4,
      typename internal::Callback_ParamTraits<A5>::ForwardType a5,
      typename internal::Callback_ParamTraits<A6>::ForwardType a6) const {
    if (sink_.get())
      sink_->Run(
          internal::Forward(a1),
          internal::Forward(a2),
          internal::Forward(a3),
          internal::Forward(a4),
          internal::Forward(a5),
          internal::Forward(a6));
  }

  bool is_null() const {
    return !sink_.get();
  }

 private:
  template <typename Sink>
  struct Adapter : public Runnable {
    explicit Adapter(const Sink& sink) : sink(sink) {}
    virtual void Run(
        typename internal::Callback_ParamTraits<A1>::ForwardType a1,
        typename internal::Callback_ParamTraits<A2>::ForwardType a2,
        typename internal::Callback_ParamTraits<A3>::ForwardType a3,
        typename internal::Callback_ParamTraits<A4>::ForwardType a4,
        typename internal::Callback_ParamTraits<A5>::ForwardType a5,
        typename internal::Callback_ParamTraits<A6>::ForwardType a6) const
            MOJO_OVERRIDE {
      sink.Run(
          internal::Forward(a1),
          internal::Forward(a2),
          internal::Forward(a3),
          internal::Forward(a4),
          internal::Forward(a5),
          internal::Forward(a6));
    }
    Sink sink;
  };

  internal::SharedPtr<Runnable> sink_;
};

template <typename A1, typename A2, typename A3, typename A4, typename A5,
    typename A6, typename A7>
class Callback<void(A1, A2, A3, A4, A5, A6, A7)> {
 public:
  struct Runnable {
    virtual ~Runnable() {}
    virtual void Run(
        typename internal::Callback_ParamTraits<A1>::ForwardType a1,
        typename internal::Callback_ParamTraits<A2>::ForwardType a2,
        typename internal::Callback_ParamTraits<A3>::ForwardType a3,
        typename internal::Callback_ParamTraits<A4>::ForwardType a4,
        typename internal::Callback_ParamTraits<A5>::ForwardType a5,
        typename internal::Callback_ParamTraits<A6>::ForwardType a6,
        typename internal::Callback_ParamTraits<A7>::ForwardType a7) const = 0;
  };

  Callback() {}

  
  explicit Callback(Runnable* runnable) : sink_(runnable) {}

  
  
  template <typename Sink>
  Callback(const Sink& sink) : sink_(new Adapter<Sink>(sink)) {}

  void Run(
      typename internal::Callback_ParamTraits<A1>::ForwardType a1,
      typename internal::Callback_ParamTraits<A2>::ForwardType a2,
      typename internal::Callback_ParamTraits<A3>::ForwardType a3,
      typename internal::Callback_ParamTraits<A4>::ForwardType a4,
      typename internal::Callback_ParamTraits<A5>::ForwardType a5,
      typename internal::Callback_ParamTraits<A6>::ForwardType a6,
      typename internal::Callback_ParamTraits<A7>::ForwardType a7) const {
    if (sink_.get())
      sink_->Run(
          internal::Forward(a1),
          internal::Forward(a2),
          internal::Forward(a3),
          internal::Forward(a4),
          internal::Forward(a5),
          internal::Forward(a6),
          internal::Forward(a7));
  }

  bool is_null() const {
    return !sink_.get();
  }

 private:
  template <typename Sink>
  struct Adapter : public Runnable {
    explicit Adapter(const Sink& sink) : sink(sink) {}
    virtual void Run(
        typename internal::Callback_ParamTraits<A1>::ForwardType a1,
        typename internal::Callback_ParamTraits<A2>::ForwardType a2,
        typename internal::Callback_ParamTraits<A3>::ForwardType a3,
        typename internal::Callback_ParamTraits<A4>::ForwardType a4,
        typename internal::Callback_ParamTraits<A5>::ForwardType a5,
        typename internal::Callback_ParamTraits<A6>::ForwardType a6,
        typename internal::Callback_ParamTraits<A7>::ForwardType a7) const
            MOJO_OVERRIDE {
      sink.Run(
          internal::Forward(a1),
          internal::Forward(a2),
          internal::Forward(a3),
          internal::Forward(a4),
          internal::Forward(a5),
          internal::Forward(a6),
          internal::Forward(a7));
    }
    Sink sink;
  };

  internal::SharedPtr<Runnable> sink_;
};

typedef Callback<void()> Closure;

}  

#endif  