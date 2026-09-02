/*
 * Deskflow -- mouse and keyboard sharing utility
 * SPDX-FileCopyrightText: (C) 2025-2026 Synergy App Ltd
 * SPDX-License-Identifier: GPL-2.0-only WITH LicenseRef-OpenSSL-Exception
 */

#include "CoreIpcServer.h"

#include "base/Log.h"
#include "common/Constants.h"
#include "common/KeyboardBroadcastProtocol.h"
#include "common/MouseBroadcastProtocol.h"

#include <QLocalSocket>

namespace deskflow::core::ipc {

static CoreIpcServer *s_instance = nullptr;

CoreIpcServer::CoreIpcServer(QObject *parent) : IpcServer(parent, kCoreIpcName, QStringLiteral("core"))
{
  assert(s_instance == nullptr);
  s_instance = this;
}

CoreIpcServer &CoreIpcServer::instance()
{
  assert(s_instance != nullptr);
  return *s_instance;
}

void CoreIpcServer::setInputBroadcastState(uint8_t modes)
{
  m_inputBroadcastModes = modes;
  broadcastCommand(QStringLiteral("inputBroadcastState"), QString::number(modes), false);
}

void CoreIpcServer::processCommand(QLocalSocket *clientSocket, const QString &command, const QStringList &parts)
{
  if (command == QStringLiteral("stop")) {
    LOG_DEBUG("core ipc server got stop message");
    writeToClientSocket(clientSocket, QStringLiteral("ok"));
    broadcastCommand(QStringLiteral("bye"));
    Q_EMIT stopProcessRequested();
    return;
  }

  if (command == QStringLiteral("mouseBroadcast")) {
    if (parts.size() != 2) {
      LOG_WARN("core ipc server got invalid mouse broadcast request");
      writeToClientSocket(clientSocket, QStringLiteral("error=invalid mouse broadcast request"));
      return;
    }

    const auto request = deskflow::mouse_broadcast::parseRequest(parts.at(1));
    if (!request.has_value()) {
      LOG_WARN("core ipc server got invalid mouse broadcast payload");
      writeToClientSocket(clientSocket, QStringLiteral("error=invalid mouse broadcast payload"));
      return;
    }

    Q_EMIT mouseBroadcastRequested(request->enabled, request->targets);
    return;
  }

  if (command == QStringLiteral("getMouseBroadcastState")) {
    if (parts.size() != 1) {
      LOG_WARN("core ipc server got invalid mouse broadcast state request");
      writeToClientSocket(clientSocket, QStringLiteral("error=invalid mouse broadcast state request"));
      return;
    }

    Q_EMIT mouseBroadcastStateRequested();
    return;
  }

  if (command == QStringLiteral("keyboardBroadcast")) {
    if (parts.size() != 2) {
      LOG_WARN("core ipc server got invalid keyboard broadcast request");
      writeToClientSocket(clientSocket, QStringLiteral("error=invalid keyboard broadcast request"));
      return;
    }

    const auto request = deskflow::keyboard_broadcast::parseRequest(parts.at(1));
    if (!request.has_value()) {
      LOG_WARN("core ipc server got invalid keyboard broadcast payload");
      writeToClientSocket(clientSocket, QStringLiteral("error=invalid keyboard broadcast payload"));
      return;
    }

    Q_EMIT keyboardBroadcastRequested(request->enabled, request->targets);
    return;
  }

  if (command == QStringLiteral("getKeyboardBroadcastState")) {
    if (parts.size() != 1) {
      LOG_WARN("core ipc server got invalid keyboard broadcast state request");
      writeToClientSocket(clientSocket, QStringLiteral("error=invalid keyboard broadcast state request"));
      return;
    }

    Q_EMIT keyboardBroadcastStateRequested();
    return;
  }

  if (command == QStringLiteral("getInputBroadcastState")) {
    if (parts.size() != 1) {
      LOG_WARN("core ipc server got invalid input broadcast state request");
      writeToClientSocket(clientSocket, QStringLiteral("error=invalid input broadcast state request"));
      return;
    }

    writeToClientSocket(
        clientSocket, QStringLiteral("inputBroadcastState=%1").arg(QString::number(m_inputBroadcastModes))
    );
    return;
  }

  LOG_WARN("core ipc server got unknown command: %s", command.toUtf8().constData());
}

} // namespace deskflow::core::ipc
