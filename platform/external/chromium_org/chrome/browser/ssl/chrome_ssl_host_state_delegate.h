// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SSL_CHROME_SSL_HOST_STATE_DELEGATE_H_
#define CHROME_BROWSER_SSL_CHROME_SSL_HOST_STATE_DELEGATE_H_

#include "base/gtest_prod_util.h"
#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"
#include "content/public/browser/ssl_host_state_delegate.h"

class Profile;

namespace base {
class Clock;
class DictionaryValue;
}  

class ChromeSSLHostStateDelegate : public content::SSLHostStateDelegate {
 public:
  explicit ChromeSSLHostStateDelegate(Profile* profile);
  virtual ~ChromeSSLHostStateDelegate();

  
  virtual void AllowCert(const std::string& host,
                         const net::X509Certificate& cert,
                         net::CertStatus error) OVERRIDE;
  virtual void Clear() OVERRIDE;
  virtual CertJudgment QueryPolicy(const std::string& host,
                                   const net::X509Certificate& cert,
                                   net::CertStatus error,
                                   bool* expired_previous_decision) OVERRIDE;
  virtual void HostRanInsecureContent(const std::string& host,
                                      int pid) OVERRIDE;
  virtual bool DidHostRunInsecureContent(const std::string& host,
                                         int pid) const OVERRIDE;

  
  
  virtual void RevokeUserAllowExceptions(const std::string& host);

  
  
  
  
  virtual void RevokeUserAllowExceptionsHard(const std::string& host);

  
  
  
  
  virtual bool HasAllowException(const std::string& host) const;

 protected:
  
  void SetClock(scoped_ptr<base::Clock> clock);

 private:
  FRIEND_TEST_ALL_PREFIXES(ForgetInstantlySSLHostStateDelegateTest,
                           MakeAndForgetException);
  FRIEND_TEST_ALL_PREFIXES(RememberSSLHostStateDelegateTest, AfterRestart);
  FRIEND_TEST_ALL_PREFIXES(RememberSSLHostStateDelegateTest,
                           QueryPolicyExpired);

  
  
  enum CreateDictionaryEntriesDisposition {
    CREATE_DICTIONARY_ENTRIES,
    DO_NOT_CREATE_DICTIONARY_ENTRIES
  };

  
  
  
  
  
  enum RememberSSLExceptionDecisionsDisposition {
    FORGET_SSL_EXCEPTION_DECISIONS_AT_SESSION_END,
    REMEMBER_SSL_EXCEPTION_DECISIONS_FOR_DELTA
  };

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  base::DictionaryValue* GetValidCertDecisionsDict(
      base::DictionaryValue* dict,
      CreateDictionaryEntriesDisposition create_entries,
      bool* expired_previous_decision);

  scoped_ptr<base::Clock> clock_;
  RememberSSLExceptionDecisionsDisposition should_remember_ssl_decisions_;
  base::TimeDelta default_ssl_cert_decision_expiration_delta_;
  Profile* profile_;

  
  
  typedef std::pair<std::string, int> BrokenHostEntry;

  
  
  
  std::set<BrokenHostEntry> ran_insecure_content_hosts_;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  const std::string current_expiration_guid_;

  DISALLOW_COPY_AND_ASSIGN(ChromeSSLHostStateDelegate);
};

#endif  
