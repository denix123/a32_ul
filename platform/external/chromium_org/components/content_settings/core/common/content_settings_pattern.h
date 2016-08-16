// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef COMPONENTS_CONTENT_SETTINGS_CORE_COMMON_CONTENT_SETTINGS_PATTERN_H_
#define COMPONENTS_CONTENT_SETTINGS_CORE_COMMON_CONTENT_SETTINGS_PATTERN_H_

#include <string>

#include "base/gtest_prod_util.h"

class GURL;

namespace content_settings {
class PatternParser;
}

class ContentSettingsPattern {
 public:
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  enum Relation {
    DISJOINT_ORDER_POST = -2,
    SUCCESSOR = -1,
    IDENTITY = 0,
    PREDECESSOR = 1,
    DISJOINT_ORDER_PRE = 2,
  };

  struct PatternParts {
    PatternParts();
    ~PatternParts();

    
    
    std::string scheme;

    
    bool is_scheme_wildcard;

    
    
    
    
    
    std::string host;

    
    bool has_domain_wildcard;

    
    
    std::string port;

    
    bool is_port_wildcard;

    
    
    
    std::string path;

    
    bool is_path_wildcard;
  };

  class BuilderInterface {
   public:
    virtual ~BuilderInterface() {}

    virtual BuilderInterface* WithPort(const std::string& port) = 0;

    virtual BuilderInterface* WithPortWildcard() = 0;

    virtual BuilderInterface* WithHost(const std::string& host) = 0;

    virtual BuilderInterface* WithDomainWildcard() = 0;

    virtual BuilderInterface* WithScheme(const std::string& scheme) = 0;

    virtual BuilderInterface* WithSchemeWildcard() = 0;

    virtual BuilderInterface* WithPath(const std::string& path) = 0;

    virtual BuilderInterface* WithPathWildcard() = 0;

    virtual BuilderInterface* Invalid() = 0;

    
    
    virtual ContentSettingsPattern Build() = 0;
  };

  static BuilderInterface* CreateBuilder(bool use_legacy_validate);

  
  static const int kContentSettingsPatternVersion;

  
  
  static ContentSettingsPattern Wildcard();

  
  
  static ContentSettingsPattern FromURL(const GURL& url);

  
  static ContentSettingsPattern FromURLNoWildcard(const GURL& url);

  
  
  
  
  
  
  
  
  
  static ContentSettingsPattern FromString(const std::string& pattern_spec);

  
  
  
  
  static void SetNonWildcardDomainNonPortScheme(const char* scheme);

  
  static bool IsNonWildcardDomainNonPortScheme(const std::string& scheme);

  
  
  ContentSettingsPattern();

  
  bool IsValid() const { return is_valid_; }

  
  bool Matches(const GURL& url) const;

  
  bool MatchesAllHosts() const;

  
  std::string ToString() const;

  
  
  Relation Compare(const ContentSettingsPattern& other) const;

  
  bool operator==(const ContentSettingsPattern& other) const;

  
  bool operator!=(const ContentSettingsPattern& other) const;

  
  bool operator<(const ContentSettingsPattern& other) const;

  
  bool operator>(const ContentSettingsPattern& other) const;

 private:
  friend class content_settings::PatternParser;
  friend class ContentSettingsPatternSerializer;
  FRIEND_TEST_ALL_PREFIXES(ContentSettingsPatternParserTest, SerializePatterns);

  class Builder;

  static Relation CompareScheme(
      const ContentSettingsPattern::PatternParts& parts,
      const ContentSettingsPattern::PatternParts& other_parts);

  static Relation CompareHost(
      const ContentSettingsPattern::PatternParts& parts,
      const ContentSettingsPattern::PatternParts& other_parts);

  static Relation ComparePort(
      const ContentSettingsPattern::PatternParts& parts,
      const ContentSettingsPattern::PatternParts& other_parts);

  ContentSettingsPattern(const PatternParts& parts, bool valid);

  PatternParts parts_;

  bool is_valid_;
};

#endif  
