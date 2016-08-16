// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef COMPONENTS_CONTENT_SETTINGS_CORE_BROWSER_CONTENT_SETTINGS_RULE_H_
#define COMPONENTS_CONTENT_SETTINGS_CORE_BROWSER_CONTENT_SETTINGS_RULE_H_

#include "base/compiler_specific.h"
#include "base/memory/linked_ptr.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "base/synchronization/lock.h"
#include "base/values.h"
#include "components/content_settings/core/common/content_settings_pattern.h"

namespace content_settings {

struct Rule {
  Rule();
  
  Rule(const ContentSettingsPattern& primary_pattern,
       const ContentSettingsPattern& secondary_pattern,
       base::Value* value);
  ~Rule();

  ContentSettingsPattern primary_pattern;
  ContentSettingsPattern secondary_pattern;
  linked_ptr<base::Value> value;
};

class RuleIterator {
 public:
  virtual ~RuleIterator();
  virtual bool HasNext() const = 0;
  virtual Rule Next() = 0;
};

class EmptyRuleIterator : public RuleIterator {
 public:
  virtual ~EmptyRuleIterator();
  virtual bool HasNext() const OVERRIDE;
  virtual Rule Next() OVERRIDE;
};

class ConcatenationIterator : public RuleIterator {
 public:
  
  
  ConcatenationIterator(ScopedVector<RuleIterator>* iterators,
                        base::AutoLock* auto_lock);
  virtual ~ConcatenationIterator();
  virtual bool HasNext() const OVERRIDE;
  virtual Rule Next() OVERRIDE;
 private:
  ScopedVector<RuleIterator> iterators_;
  scoped_ptr<base::AutoLock> auto_lock_;
};

}  

#endif  