// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_COMMON_EXTENSION_SET_H_
#define EXTENSIONS_COMMON_EXTENSION_SET_H_

#include <iterator>
#include <map>
#include <string>

#include "base/callback.h"
#include "base/gtest_prod_util.h"
#include "base/memory/ref_counted.h"
#include "extensions/common/extension.h"
#include "url/gurl.h"

namespace extensions {

class ExtensionSet {
 public:
  typedef std::pair<base::FilePath, std::string> ExtensionPathAndDefaultLocale;
  typedef std::map<std::string, scoped_refptr<const Extension> > ExtensionMap;
  typedef base::Callback<void(const ExtensionIdSet&)>
      ModificationCallback;

  
  
  class const_iterator : public std::iterator<std::input_iterator_tag,
                                              scoped_refptr<const Extension> > {
   public:
    const_iterator();
    const_iterator(const const_iterator& other);
    explicit const_iterator(ExtensionMap::const_iterator it);
    ~const_iterator();
    const_iterator& operator++() {
      ++it_;
      return *this;
    }
    const_iterator operator++(int) {
      const const_iterator old(*this);
      ++it_;
      return old;
    }
    const scoped_refptr<const Extension>& operator*() const {
      return it_->second;
    }
    const scoped_refptr<const Extension>* operator->() const {
      return &it_->second;
    }
    bool operator!=(const const_iterator& other) const {
      return it_ != other.it_;
    }
    bool operator==(const const_iterator& other) const {
      return it_ == other.it_;
    }

   private:
    ExtensionMap::const_iterator it_;
  };

  ExtensionSet();
  ~ExtensionSet();

  size_t size() const;
  bool is_empty() const;

  
  const_iterator begin() const { return const_iterator(extensions_.begin()); }
  const_iterator end() const { return const_iterator(extensions_.end()); }

  
  bool Contains(const std::string& id) const;

  
  
  
  bool Insert(const scoped_refptr<const Extension>& extension);

  
  
  bool InsertAll(const ExtensionSet& extensions);

  
  
  bool Remove(const std::string& id);

  
  void Clear();

  
  
  std::string GetExtensionOrAppIDByURL(const GURL& url) const;

  
  
  
  
  
  const Extension* GetExtensionOrAppByURL(const GURL& url) const;

  
  
  
  const Extension* GetAppByURL(const GURL& url) const;

  
  const Extension* GetHostedAppByURL(const GURL& url) const;

  
  
  const Extension* GetHostedAppByOverlappingWebExtent(
      const URLPatternSet& extent) const;

  
  
  bool InSameExtent(const GURL& old_url, const GURL& new_url) const;

  
  const Extension* GetByID(const std::string& id) const;

  
  ExtensionIdSet GetIDs() const;

  
  
  
  bool ExtensionBindingsAllowed(const GURL& url) const;

  void set_modification_callback(
      const ModificationCallback& modification_callback) {
    modification_callback_ = modification_callback;
  }

 private:
  FRIEND_TEST_ALL_PREFIXES(ExtensionSetTest, ExtensionSet);

  ExtensionMap extensions_;

  
  
  
  
  ModificationCallback modification_callback_;

  DISALLOW_COPY_AND_ASSIGN(ExtensionSet);
};

}  

#endif  
