// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SEARCH_ENGINES_TEMPLATE_URL_SERVICE_OBSERVER_H_
#define COMPONENTS_SEARCH_ENGINES_TEMPLATE_URL_SERVICE_OBSERVER_H_

class TemplateURLServiceObserver {
 public:
  
  virtual void OnTemplateURLServiceChanged() = 0;

 protected:
  virtual ~TemplateURLServiceObserver() {}
};

#endif  
