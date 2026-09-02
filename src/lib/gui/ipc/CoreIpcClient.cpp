/*
 * Deskflow -- mouse and keyboard sharing utility
 * SPDX-FileCopyrightText: (C) 2025-2026 Synergy App Ltd
 * SPDX-License-Identifier: GPL-2.0-only WITH LicenseRef-OpenSSL-Exception
 */

#include "CoreIpcClient.h"

#include "common/Constants.h"
#include "common/KeyboardBroadcastProtocol.h"
#include "common/MouseBroadcastProtocol.h"

#include <QString>

namespace deskflow::gui::ipc {

CoreIpcClient::CoreIpcClient(QObject *parent) : IpcClient(parent, kCoreIpcName, QStringLiteral("core"))
{
  // do nothing
}

void CoreIpcClient::requestMouseBroadcastState()
{
  sendMessage(QStringLiteral("getMouseBroadcastState"));
}

void CoreIpcClient::sendMouseBroadcast(bool enabled, const QStringList &targets)
{
  sendMessage(QStringLiteral("mouseBroadcast=%1").arg(deskflow::mouse_broadcast::formatRequest(enabled, targets)));
}

void CoreIpcClient::requestKeyboardBroadcastState()
{
  sendMessage(QStringLiteral("getKeyboardBroadcastState"));
}

void CoreIpcClient::sendKeyboardBroadcast(bool enabled, const QStringList &targets)
{
  sendMessage(QStringLiteral("keyboardBroadcast=%1").arg(deskflow::keyboard_broadcast::formatRequest(enabled, targets))
  );
}

void CoreIpcClient::requestInputBroadcastState()
{
  sendMessage(QStringLiteral("getInputBroadcastState"));
}

void CoreIpcClient::sendStop()
{
  sendMessage(QStringLiteral("stop"));
}

void CoreIpcClient::processCommand(const QString &command, const QStringList &parts)
{
  const auto args = parts.size() >= 2 ? parts.at(1) : QString();
  Q_EMIT commandReceived(command, args);
}

} // namespace deskflow::gui::ipc
