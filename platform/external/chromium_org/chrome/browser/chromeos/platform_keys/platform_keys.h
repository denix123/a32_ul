// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_PLATFORM_KEYS_PLATFORM_KEYS_H_
#define CHROME_BROWSER_CHROMEOS_PLATFORM_KEYS_PLATFORM_KEYS_H_

#include <string>
#include <vector>

#include "base/callback_forward.h"
#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"

namespace content {
class BrowserContext;
}

namespace net {
class X509Certificate;
typedef std::vector<scoped_refptr<X509Certificate> > CertificateList;
}

namespace chromeos {

namespace platform_keys {

extern const char kTokenIdUser[];
extern const char kTokenIdSystem[];

enum HashAlgorithm {
  HASH_ALGORITHM_SHA1,
  HASH_ALGORITHM_SHA256,
  HASH_ALGORITHM_SHA384,
  HASH_ALGORITHM_SHA512
};

namespace subtle {

typedef base::Callback<void(const std::string& public_key_spki_der,
                            const std::string& error_message)>
    GenerateKeyCallback;

void GenerateRSAKey(const std::string& token_id,
                    unsigned int modulus_length_bits,
                    const GenerateKeyCallback& callback,
                    content::BrowserContext* browser_context);

typedef base::Callback<void(const std::string& signature,
                            const std::string& error_message)> SignCallback;

void Sign(const std::string& token_id,
          const std::string& public_key,
          HashAlgorithm hash_algorithm,
          const std::string& data,
          const SignCallback& callback,
          content::BrowserContext* browser_context);

}  

typedef base::Callback<void(scoped_ptr<net::CertificateList> certs,
                            const std::string& error_message)>
    GetCertificatesCallback;

void GetCertificates(const std::string& token_id,
                     const GetCertificatesCallback& callback,
                     content::BrowserContext* browser_context);

typedef base::Callback<void(const std::string& error_message)>
    ImportCertificateCallback;

void ImportCertificate(const std::string& token_id,
                       scoped_refptr<net::X509Certificate> certificate,
                       const ImportCertificateCallback& callback,
                       content::BrowserContext* browser_context);

typedef base::Callback<void(const std::string& error_message)>
    RemoveCertificateCallback;

void RemoveCertificate(const std::string& token_id,
                       scoped_refptr<net::X509Certificate> certificate,
                       const RemoveCertificateCallback& callback,
                       content::BrowserContext* browser_context);

typedef base::Callback<void(scoped_ptr<std::vector<std::string> > token_ids,
                            const std::string& error_message)>
    GetTokensCallback;

void GetTokens(const GetTokensCallback& callback,
               content::BrowserContext* browser_context);

}  

}  

#endif  
