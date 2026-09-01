/*
 * Deskflow -- mouse and keyboard sharing utility
 * SPDX-FileCopyrightText: (C) 2025-2026 Synergy App Ltd
 * SPDX-License-Identifier: GPL-2.0-only WITH LicenseRef-OpenSSL-Exception
 */

#pragma once

#include "IpcClient.h"

#include <QObject>
#include <QStringList>

namespace deskflow::gui::ipc {

class CoreIpcClient : public IpcClient
{
  Q_OBJECT

public:
  explicit CoreIpcClient(QObject *parent = nullptr);

  void requestMouseBroadcastState();
  void sendMouseBroadcast(bool enabled, const QStringList &targets);
  void sendStop();

Q_SIGNALS:
  void commandReceived(const QString &command, const QString &args);

protected:
  void processCommand(const QString &command, const QStringList &parts) override;
};

} // namespace deskflow::gui::ipc
