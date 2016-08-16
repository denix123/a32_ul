// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_UTILITY_MEDIA_GALLERIES_IAPPS_XML_UTILS_H_
#define CHROME_UTILITY_MEDIA_GALLERIES_IAPPS_XML_UTILS_H_

#include <set>
#include <string>

#include "base/files/file.h"
#include "base/stl_util.h"

class XmlReader;

namespace iapps {

bool SkipToNextElement(XmlReader* reader);

bool SeekToNodeAtCurrentDepth(XmlReader* reader, const std::string& name);

bool SeekInDict(XmlReader* reader, const std::string& key);

bool ReadString(XmlReader* reader, std::string* result);

bool ReadInteger(XmlReader* reader, uint64* result);

std::string ReadFileAsString(base::File file);

class XmlDictReader {
 public:
  explicit XmlDictReader(XmlReader* reader);
  virtual ~XmlDictReader();

  
  
  bool Read();

  
  
  virtual bool ShouldLoop();

  
  bool HandleKey(const std::string& key);

  virtual bool HandleKeyImpl(const std::string& key) = 0;

  
  
  virtual bool AllowRepeats();

  
  
  virtual bool FinishedOk();

  
  
  bool SkipToNext();

  
  
  bool Found(const std::string& key) const;

 protected:
  XmlReader* reader_;

 private:
  
  std::set<std::string> found_;

  DISALLOW_COPY_AND_ASSIGN(XmlDictReader);
};

}  

#endif  
