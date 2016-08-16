// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_OMNIBOX_AUTOCOMPLETE_PROVIDER_LISTENER_H_
#define COMPONENTS_OMNIBOX_AUTOCOMPLETE_PROVIDER_LISTENER_H_

class AutocompleteProviderListener {
 public:
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  virtual void OnProviderUpdate(bool updated_matches) = 0;

 protected:
  virtual ~AutocompleteProviderListener() {}
};

#endif  
