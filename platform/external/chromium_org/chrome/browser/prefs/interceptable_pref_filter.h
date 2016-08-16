// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PREFS_INTERCEPTABLE_PREF_FILTER_H_
#define CHROME_BROWSER_PREFS_INTERCEPTABLE_PREF_FILTER_H_

#include "base/callback.h"
#include "base/memory/weak_ptr.h"
#include "base/prefs/pref_filter.h"
#include "base/values.h"

class InterceptablePrefFilter
    : public PrefFilter,
      public base::SupportsWeakPtr<InterceptablePrefFilter> {
 public:
  
  
  
  
  typedef base::Callback<void(scoped_ptr<base::DictionaryValue> prefs,
                              bool prefs_altered)> FinalizeFilterOnLoadCallback;

  
  
  
  typedef base::Callback<
      void(const FinalizeFilterOnLoadCallback& finalize_filter_on_load,
           scoped_ptr<base::DictionaryValue> prefs)> FilterOnLoadInterceptor;

  InterceptablePrefFilter();
  virtual ~InterceptablePrefFilter();

  
  virtual void FilterOnLoad(
      const PostFilterOnLoadCallback& post_filter_on_load_callback,
      scoped_ptr<base::DictionaryValue> pref_store_contents) OVERRIDE;

  
  
  
  void InterceptNextFilterOnLoad(
      const FilterOnLoadInterceptor& filter_on_load_interceptor);

 private:
  
  
  
  virtual void FinalizeFilterOnLoad(
      const PostFilterOnLoadCallback& post_filter_on_load_callback,
      scoped_ptr<base::DictionaryValue> pref_store_contents,
      bool prefs_altered) = 0;

  
  
  
  FilterOnLoadInterceptor filter_on_load_interceptor_;
};

#endif  
