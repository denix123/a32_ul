// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_API_CAST_CHANNEL_CAST_CHANNEL_API_H_
#define EXTENSIONS_BROWSER_API_CAST_CHANNEL_CAST_CHANNEL_API_H_

#include <string>

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/threading/thread_checker.h"
#include "extensions/browser/api/api_resource_manager.h"
#include "extensions/browser/api/async_api_function.h"
#include "extensions/browser/api/cast_channel/cast_socket.h"
#include "extensions/browser/browser_context_keyed_api_factory.h"
#include "extensions/common/api/cast_channel.h"

class GURL;
class CastChannelAPITest;

namespace content {
class BrowserContext;
}

namespace net {
class IPEndPoint;
}

namespace extensions {

namespace core_api {
namespace cast_channel {
class Logger;
}  
}  

namespace cast_channel = core_api::cast_channel;

class CastChannelAPI : public BrowserContextKeyedAPI,
                       public cast_channel::CastSocket::Delegate {
 public:
  explicit CastChannelAPI(content::BrowserContext* context);

  static CastChannelAPI* Get(content::BrowserContext* context);

  
  static BrowserContextKeyedAPIFactory<CastChannelAPI>* GetFactoryInstance();

  
  
  
  
  
  
  scoped_refptr<cast_channel::Logger> GetLogger();

  
  
  void SetSocketForTest(scoped_ptr<cast_channel::CastSocket> socket_for_test);

  
  
  scoped_ptr<cast_channel::CastSocket> GetSocketForTest();

 private:
  friend class BrowserContextKeyedAPIFactory<CastChannelAPI>;
  friend class ::CastChannelAPITest;

  virtual ~CastChannelAPI();

  
  virtual void OnError(const cast_channel::CastSocket* socket,
                       cast_channel::ChannelError error_state,
                       const cast_channel::LastErrors& last_errors) OVERRIDE;
  virtual void OnMessage(const cast_channel::CastSocket* socket,
                         const cast_channel::MessageInfo& message) OVERRIDE;

  
  static const char* service_name() { return "CastChannelAPI"; }

  content::BrowserContext* const browser_context_;
  scoped_refptr<cast_channel::Logger> logger_;
  scoped_ptr<cast_channel::CastSocket> socket_for_test_;

  DISALLOW_COPY_AND_ASSIGN(CastChannelAPI);
};

class CastChannelAsyncApiFunction : public AsyncApiFunction {
 public:
  CastChannelAsyncApiFunction();

 protected:
  virtual ~CastChannelAsyncApiFunction();

  
  virtual bool PrePrepare() OVERRIDE;
  virtual bool Respond() OVERRIDE;

  
  
  
  cast_channel::CastSocket* GetSocketOrCompleteWithError(int channel_id);

  
  
  int AddSocket(cast_channel::CastSocket* socket);

  
  
  void RemoveSocket(int channel_id);

  
  
  void SetResultFromSocket(const cast_channel::CastSocket& socket);

  
  
  void SetResultFromError(int channel_id, cast_channel::ChannelError error);

  
  
  cast_channel::CastSocket* GetSocket(int channel_id);

 private:
  
  void SetResultFromChannelInfo(const cast_channel::ChannelInfo& channel_info);

  
  ApiResourceManager<cast_channel::CastSocket>* manager_;

  
  cast_channel::ChannelError error_;
};

class CastChannelOpenFunction : public CastChannelAsyncApiFunction {
 public:
  CastChannelOpenFunction();

 protected:
  virtual ~CastChannelOpenFunction();

  
  virtual bool PrePrepare() OVERRIDE;
  virtual bool Prepare() OVERRIDE;
  virtual void AsyncWorkStart() OVERRIDE;

 private:
  DECLARE_EXTENSION_FUNCTION("cast.channel.open", CAST_CHANNEL_OPEN)

  
  
  
  static bool ParseChannelUrl(const GURL& url,
                              cast_channel::ConnectInfo* connect_info);

  
  
  static net::IPEndPoint* ParseConnectInfo(
      const cast_channel::ConnectInfo& connect_info);

  void OnOpen(int result);

  scoped_ptr<cast_channel::Open::Params> params_;
  
  int new_channel_id_;
  CastChannelAPI* api_;
  scoped_ptr<cast_channel::ConnectInfo> connect_info_;
  scoped_ptr<net::IPEndPoint> ip_endpoint_;
  cast_channel::ChannelAuthType channel_auth_;

  FRIEND_TEST_ALL_PREFIXES(CastChannelOpenFunctionTest, TestParseChannelUrl);
  FRIEND_TEST_ALL_PREFIXES(CastChannelOpenFunctionTest, TestParseConnectInfo);
  DISALLOW_COPY_AND_ASSIGN(CastChannelOpenFunction);
};

class CastChannelSendFunction : public CastChannelAsyncApiFunction {
 public:
  CastChannelSendFunction();

 protected:
  virtual ~CastChannelSendFunction();

  
  virtual bool Prepare() OVERRIDE;
  virtual void AsyncWorkStart() OVERRIDE;

 private:
  DECLARE_EXTENSION_FUNCTION("cast.channel.send", CAST_CHANNEL_SEND)

  void OnSend(int result);

  scoped_ptr<cast_channel::Send::Params> params_;

  DISALLOW_COPY_AND_ASSIGN(CastChannelSendFunction);
};

class CastChannelCloseFunction : public CastChannelAsyncApiFunction {
 public:
  CastChannelCloseFunction();

 protected:
  virtual ~CastChannelCloseFunction();

  
  virtual bool Prepare() OVERRIDE;
  virtual void AsyncWorkStart() OVERRIDE;

 private:
  DECLARE_EXTENSION_FUNCTION("cast.channel.close", CAST_CHANNEL_CLOSE)

  void OnClose(int result);

  scoped_ptr<cast_channel::Close::Params> params_;

  DISALLOW_COPY_AND_ASSIGN(CastChannelCloseFunction);
};

class CastChannelGetLogsFunction : public CastChannelAsyncApiFunction {
 public:
  CastChannelGetLogsFunction();

 protected:
  virtual ~CastChannelGetLogsFunction();

  
  virtual bool PrePrepare() OVERRIDE;
  virtual bool Prepare() OVERRIDE;
  virtual void AsyncWorkStart() OVERRIDE;

 private:
  DECLARE_EXTENSION_FUNCTION("cast.channel.getLogs", CAST_CHANNEL_GETLOGS)

  void OnClose(int result);

  CastChannelAPI* api_;

  DISALLOW_COPY_AND_ASSIGN(CastChannelGetLogsFunction);
};

}  

#endif  