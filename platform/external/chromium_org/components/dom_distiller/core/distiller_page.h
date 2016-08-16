// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_DOM_DISTILLER_CORE_DISTILLER_PAGE_H_
#define COMPONENTS_DOM_DISTILLER_CORE_DISTILLER_PAGE_H_

#include <string>

#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/values.h"
#include "third_party/dom_distiller_js/dom_distiller.pb.h"
#include "ui/gfx/size.h"
#include "url/gurl.h"

namespace dom_distiller {

class SourcePageHandle {
 public:
  virtual ~SourcePageHandle() {}
};

class DistillerPage {
 public:
  typedef base::Callback<
      void(scoped_ptr<proto::DomDistillerResult> distilled_page,
           bool distillation_successful)> DistillerPageCallback;

  DistillerPage();
  virtual ~DistillerPage();

  
  
  
  
  void DistillPage(const GURL& url,
                   const proto::DomDistillerOptions options,
                   const DistillerPageCallback& callback);

  
  
  virtual void OnDistillationDone(const GURL& page_url,
                                  const base::Value* value);

 protected:
  
  
  
  virtual void DistillPageImpl(const GURL& url, const std::string& script) = 0;

 private:
  bool ready_;
  DistillerPageCallback distiller_page_callback_;
  DISALLOW_COPY_AND_ASSIGN(DistillerPage);
};

class DistillerPageFactory {
 public:
  virtual ~DistillerPageFactory();

  
  
  
  virtual scoped_ptr<DistillerPage> CreateDistillerPage(
      const gfx::Size& render_view_size) const = 0;
  virtual scoped_ptr<DistillerPage> CreateDistillerPageWithHandle(
      scoped_ptr<SourcePageHandle> handle) const = 0;
};

}  

#endif  
