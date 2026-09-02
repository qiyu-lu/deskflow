/*
 * Deskflow -- mouse and keyboard sharing utility
 * SPDX-FileCopyrightText: (C) 2026 Deskflow Developers
 * SPDX-License-Identifier: GPL-2.0-only WITH LicenseRef-OpenSSL-Exception
 */

#include "server/ClientProxy1_9.h"

#include "deskflow/ProtocolTypes.h"
#include "deskflow/ProtocolUtil.h"

ClientProxy1_9::ClientProxy1_9(
    const std::string &name, deskflow::IStream *adoptedStream, Server *server, IEventQueue *events
)
    : ClientProxy1_8(name, adoptedStream, server, events)
{
  // do nothing
}

bool ClientProxy1_9::supportsInputBroadcastState() const
{
  return true;
}

void ClientProxy1_9::inputBroadcastState(uint8_t modes)
{
  ProtocolUtil::writef(getStream(), kMsgDInputBroadcastState, modes);
}
