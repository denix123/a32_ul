// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef COMPONENTS_DATA_REDUCTION_PROXY_BROWSER_DATA_REDUCTION_PROXY_TAMPER_DETECTION_H_
#define COMPONENTS_DATA_REDUCTION_PROXY_BROWSER_DATA_REDUCTION_PROXY_TAMPER_DETECTION_H_

#include <map>
#include <string>
#include <vector>

#include "net/proxy/proxy_service.h"

namespace net {
class HttpResponseHeaders;
}

namespace data_reduction_proxy {

class DataReductionProxyTamperDetection {
 public:
  
  
  
  
  
  static bool DetectAndReport(const net::HttpResponseHeaders* headers,
                              bool scheme_is_https);

  
  
  
  DataReductionProxyTamperDetection(
      const net::HttpResponseHeaders* response_headers,
      bool scheme_is_https,
      unsigned carrier_id);

  virtual ~DataReductionProxyTamperDetection();

 private:
  FRIEND_TEST_ALL_PREFIXES(DataReductionProxyTamperDetectionTest,
                           TestFingerprintCommon);
  FRIEND_TEST_ALL_PREFIXES(DataReductionProxyTamperDetectionTest,
                           ChromeProxy);
  FRIEND_TEST_ALL_PREFIXES(DataReductionProxyTamperDetectionTest,
                           Via);
  FRIEND_TEST_ALL_PREFIXES(DataReductionProxyTamperDetectionTest,
                           OtherHeaders);
  FRIEND_TEST_ALL_PREFIXES(DataReductionProxyTamperDetectionTest,
                           ContentLength);
  FRIEND_TEST_ALL_PREFIXES(DataReductionProxyTamperDetectionTest,
                           HeaderRemoving);
  FRIEND_TEST_ALL_PREFIXES(DataReductionProxyTamperDetectionTest,
                           ValuesToSortedString);
  FRIEND_TEST_ALL_PREFIXES(DataReductionProxyTamperDetectionTest,
                           GetHeaderValues);
  FRIEND_TEST_ALL_PREFIXES(DataReductionProxyTamperDetectionTest,
                           DetectAndReport);

  
  bool ValidateChromeProxyHeader(const std::string& fingerprint) const;

  
  void ReportUMAforChromeProxyHeaderValidation() const;

  
  
  bool ValidateViaHeader(const std::string& fingerprint,
                         bool* has_chrome_proxy_via_header) const;

  
  void ReportUMAforViaHeaderValidation(bool has_chrome_proxy_via_header) const;

  
  bool ValidateOtherHeaders(const std::string& fingerprint) const;

  
  void ReportUMAforOtherHeadersValidation() const;

  
  bool ValidateContentLengthHeader(const std::string& fingerprint) const;

  
  void ReportUMAforContentLengthHeaderValidation() const;

  
  static std::string ValuesToSortedString(std::vector<std::string>* values);

  
  
  static void GetMD5(const std::string& input, std::string* output);

  
  
  static std::vector<std::string> GetHeaderValues(
      const net::HttpResponseHeaders* headers,
      const std::string& header_name);

  
  const net::HttpResponseHeaders* response_headers_;

  
  const bool scheme_is_https_;

  
  const unsigned carrier_id_;

  DISALLOW_COPY_AND_ASSIGN(DataReductionProxyTamperDetection);
};

}  
#endif  
