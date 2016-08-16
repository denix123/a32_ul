// Copyright (c) 2010 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_PROXY_PROXY_CONFIG_SERVICE_COMMON_UNITTEST_H_
#define NET_PROXY_PROXY_CONFIG_SERVICE_COMMON_UNITTEST_H_

#include "net/proxy/proxy_config.h"
#include "testing/gtest/include/gtest/gtest.h"


namespace net {

struct ProxyRulesExpectation {
  ProxyRulesExpectation(ProxyConfig::ProxyRules::Type type,
                        const char* single_proxy,
                        const char* proxy_for_http,
                        const char* proxy_for_https,
                        const char* proxy_for_ftp,
                        const char* fallback_proxy,
                        const char* flattened_bypass_rules,
                        bool reverse_bypass);

  
  
  ::testing::AssertionResult Matches(
      const ProxyConfig::ProxyRules& rules) const;

  
  static ProxyRulesExpectation Empty();

  
  
  static ProxyRulesExpectation EmptyWithBypass(
      const char* flattened_bypass_rules);

  
  
  static ProxyRulesExpectation Single(const char* single_proxy,
                                      const char* flattened_bypass_rules);

  
  
  static ProxyRulesExpectation PerScheme(const char* proxy_http,
                                         const char* proxy_https,
                                         const char* proxy_ftp,
                                         const char* flattened_bypass_rules);

  
  static ProxyRulesExpectation PerSchemeWithSocks(
      const char* proxy_http,
      const char* proxy_https,
      const char* proxy_ftp,
      const char* fallback_proxy,
      const char* flattened_bypass_rules);

  
  static ProxyRulesExpectation PerSchemeWithBypassReversed(
      const char* proxy_http,
      const char* proxy_https,
      const char* proxy_ftp,
      const char* flattened_bypass_rules);

  ProxyConfig::ProxyRules::Type type;
  const char* single_proxy;
  const char* proxy_for_http;
  const char* proxy_for_https;
  const char* proxy_for_ftp;
  const char* fallback_proxy;
  const char* flattened_bypass_rules;
  bool reverse_bypass;
};

}  

#endif  