// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_HOST_SERVER_LOG_ENTRY_HOST_H_
#define REMOTING_HOST_SERVER_LOG_ENTRY_HOST_H_

#include "remoting/host/host_exit_codes.h"
#include "remoting/host/host_status_sender.h"
#include "remoting/protocol/transport.h"

namespace remoting {

class ServerLogEntry;

scoped_ptr<ServerLogEntry> MakeLogEntryForSessionStateChange(
    bool connected);

scoped_ptr<ServerLogEntry> MakeLogEntryForHeartbeat();

scoped_ptr<ServerLogEntry> MakeLogEntryForHostStatus(
    HostStatusSender::HostStatus host_status, HostExitCodes exit_code);

void AddHostFieldsToLogEntry(ServerLogEntry* entry);

void AddConnectionTypeToLogEntry(ServerLogEntry* entry,
                                 protocol::TransportRoute::RouteType type);

}  

#endif  
