// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SSL_SSL_ERROR_CLASSIFICATION_H_
#define CHROME_BROWSER_SSL_SSL_ERROR_CLASSIFICATION_H_

#include <string>
#include <vector>

#include "base/time/time.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "net/cert/x509_certificate.h"
#include "url/gurl.h"

namespace content {
class WebContents;
}

class SSLErrorClassification : public content::NotificationObserver {
 public:
  SSLErrorClassification(content::WebContents* web_contents,
                         const base::Time& current_time,
                         const GURL& url,
                         int cert_error,
                         const net::X509Certificate& cert);
  virtual ~SSLErrorClassification();

  
  static bool IsUserClockInThePast(const base::Time& time_now);

  
  
  static bool IsUserClockInTheFuture(const base::Time& time_now);

  
  
  static bool MaybeWindowsLacksSHA256Support();

  
  
  
  
  void InvalidDateSeverityScore();

  
  
  
  
  void InvalidCommonNameSeverityScore();

  void RecordUMAStatistics(bool overridable) const;
  void RecordCaptivePortalUMAStatistics(bool overridable) const;
  base::TimeDelta TimePassedSinceExpiry() const;

 private:
  FRIEND_TEST_ALL_PREFIXES(SSLErrorClassificationTest, TestDateInvalidScore);
  FRIEND_TEST_ALL_PREFIXES(SSLErrorClassificationTest, TestNameMismatch);
  FRIEND_TEST_ALL_PREFIXES(SSLErrorClassificationTest,
                           TestHostNameHasKnownTLD);

  typedef std::vector<std::string> Tokens;

  
  static bool IsHostNameKnownTLD(const std::string& host_name);

  
  
  
  
  
  
  
  
  bool IsWWWSubDomainMatch() const;

  
  bool NameUnderAnyNames(const Tokens& child,
                        const std::vector<Tokens>& potential_parents) const;

  
  
  
  
  bool AnyNamesUnderName(const std::vector<Tokens>& potential_children,
                        const Tokens& parent) const;

  
  
  
  
  
  bool IsSubDomainOutsideWildcard(const Tokens& hostname) const;

  
  
  
  
  bool IsCertLikelyFromMultiTenantHosting() const;

  static std::vector<Tokens> GetTokenizedDNSNames(
      const std::vector<std::string>& dns_names);

  
  
  
  
  
  
  
  
  
  size_t FindSubDomainDifference(const Tokens& potential_subdomain,
                                 const Tokens& parent) const;

  static Tokens Tokenize(const std::string& name);

  float CalculateScoreTimePassedSinceExpiry() const;
  float CalculateScoreEnvironments() const;

  
  virtual void Observe(
      int type,
      const content::NotificationSource& source,
      const content::NotificationDetails& details) OVERRIDE;

  content::WebContents* web_contents_;
  
  base::Time current_time_;
  const GURL& request_url_;
  int cert_error_;
  
  const net::X509Certificate& cert_;
  
  bool captive_portal_detection_enabled_;
  
  bool captive_portal_probe_completed_;
  
  bool captive_portal_no_response_;
  
  bool captive_portal_detected_;

  content::NotificationRegistrar registrar_;
};

#endif  
