/*
 * Deskflow -- mouse and keyboard sharing utility
 * SPDX-FileCopyrightText: (C) 2025-2026 Synergy App Ltd
 * SPDX-License-Identifier: GPL-2.0-only WITH LicenseRef-OpenSSL-Exception
 */

#pragma once

#include "IpcServer.h"

#include <QObject>
#include <QSet>
#include <QStringList>

#include <cstdint>

class QLocalSocket;

namespace deskflow::core::ipc {

class CoreIpcServer : public IpcServer
{
  Q_OBJECT

public:
  explicit CoreIpcServer(QObject *parent);

  static CoreIpcServer &instance();
  void setInputBroadcastState(uint8_t modes);

Q_SIGNALS:
  void mouseBroadcastRequested(bool enabled, const QStringList &targets);
  void mouseBroadcastStateRequested();
  void keyboardBroadcastRequested(bool enabled, const QStringList &targets);
  void keyboardBroadcastStateRequested();

private:
  void processCommand(QLocalSocket *clientSocket, const QString &command, const QStringList &parts) override;

  uint8_t m_inputBroadcastModes = 0;
};

} // namespace deskflow::core::ipc
