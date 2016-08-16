// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_BROWSER_DEVTOOLS_HTTP_HANDLER_H_
#define CONTENT_PUBLIC_BROWSER_DEVTOOLS_HTTP_HANDLER_H_

#include <string>

#include "base/files/file_path.h"
#include "base/memory/scoped_ptr.h"
#include "content/common/content_export.h"

class GURL;

namespace net {
class ServerSocket;
class URLRequestContextGetter;
}

namespace content {

class DevToolsHttpHandlerDelegate;

class DevToolsHttpHandler {
 public:

  
  
  class CONTENT_EXPORT ServerSocketFactory {
   public:
    ServerSocketFactory(const std::string& address, int port, int backlog);
    virtual ~ServerSocketFactory();

    
    
    
    virtual scoped_ptr<net::ServerSocket> CreateAndListen() const;

   protected:
    
    
    virtual scoped_ptr<net::ServerSocket> Create() const = 0;

    const std::string address_;
    const int port_;
    const int backlog_;

   private:
    DISALLOW_COPY_AND_ASSIGN(ServerSocketFactory);
  };

  
  CONTENT_EXPORT static bool IsSupportedProtocolVersion(
      const std::string& version);

  
  CONTENT_EXPORT static int GetFrontendResourceId(
      const std::string& name);

  
  
  
  // port selected by the OS will be written to a well-known file in
  
  CONTENT_EXPORT static DevToolsHttpHandler* Start(
      scoped_ptr<ServerSocketFactory> server_socket_factory,
      const std::string& frontend_url,
      DevToolsHttpHandlerDelegate* delegate,
      const base::FilePath& active_port_output_directory);

  
  
  virtual void Stop() = 0;

  
  virtual GURL GetFrontendURL() = 0;

 protected:
  virtual ~DevToolsHttpHandler() {}
};

}  

#endif  
