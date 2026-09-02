/*
 * Deskflow -- mouse and keyboard sharing utility
 * SPDX-FileCopyrightText: (C) 2026 Deskflow Developers
 * SPDX-License-Identifier: GPL-2.0-only WITH LicenseRef-OpenSSL-Exception
 */

#pragma once

#include <QString>
#include <QStringList>

#include <optional>

namespace deskflow::mouse_broadcast {

struct Request
{
  bool enabled = false;
  QStringList targets;
};

struct State
{
  bool enabled = false;
  QStringList targets;
  QString reason;
};

QString formatRequest(bool enabled, const QStringList &targets);
std::optional<Request> parseRequest(const QString &payload);

QString formatState(bool enabled, const QStringList &targets, const QString &reason = QString());
std::optional<State> parseState(const QString &payload);

} // namespace deskflow::mouse_broadcast
