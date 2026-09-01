/*
 * Deskflow -- mouse and keyboard sharing utility
 * SPDX-FileCopyrightText: (C) 2026 Deskflow Developers
 * SPDX-License-Identifier: GPL-2.0-only WITH LicenseRef-OpenSSL-Exception
 */

#include "MouseBroadcastProtocol.h"

#include <QRegularExpression>

#include <utility>

namespace deskflow::mouse_broadcast {

namespace {

const auto kAllTargets = QStringLiteral("*");
const auto kEnabled = QStringLiteral("on");
const auto kDisabled = QStringLiteral("off");
const auto kFieldSeparator = QChar('|');
const auto kTargetSeparator = QChar(':');

QStringList normalizeTargets(QStringList targets)
{
  targets.removeAll(QString());
  targets.removeDuplicates();
  targets.sort();
  return targets;
}

QString formatTargets(const QStringList &targets)
{
  const auto normalized = normalizeTargets(targets);
  return normalized.isEmpty() ? kAllTargets : normalized.join(kTargetSeparator);
}

std::optional<QStringList> parseTargets(const QString &value)
{
  if (value == kAllTargets) {
    return QStringList();
  }

  static const auto validTarget = QRegularExpression(QStringLiteral("^[\\w.\\-]{1,255}$"));
  const auto rawTargets = value.split(kTargetSeparator, Qt::KeepEmptyParts);
  if (rawTargets.contains(QString())) {
    return std::nullopt;
  }

  auto targets = normalizeTargets(rawTargets);

  for (const auto &target : std::as_const(targets)) {
    if (!validTarget.match(target).hasMatch()) {
      return std::nullopt;
    }
  }
  return targets;
}

std::optional<bool> parseEnabled(const QString &value)
{
  if (value == kEnabled) {
    return true;
  }
  if (value == kDisabled) {
    return false;
  }
  return std::nullopt;
}

} // namespace

QString formatRequest(bool enabled, const QStringList &targets)
{
  return QStringLiteral("%1|%2").arg(enabled ? kEnabled : kDisabled, formatTargets(targets));
}

std::optional<Request> parseRequest(const QString &payload)
{
  const auto fields = payload.split(kFieldSeparator, Qt::KeepEmptyParts);
  if (fields.size() != 2) {
    return std::nullopt;
  }

  const auto enabled = parseEnabled(fields.at(0));
  const auto targets = parseTargets(fields.at(1));
  if (!enabled.has_value() || !targets.has_value()) {
    return std::nullopt;
  }
  return Request{enabled.value(), targets.value()};
}

QString formatState(bool enabled, const QStringList &targets, const QString &reason)
{
  return QStringLiteral("%1|%2|%3").arg(enabled ? kEnabled : kDisabled, formatTargets(targets), reason);
}

std::optional<State> parseState(const QString &payload)
{
  const auto fields = payload.split(kFieldSeparator, Qt::KeepEmptyParts);
  if (fields.size() != 3) {
    return std::nullopt;
  }

  const auto enabled = parseEnabled(fields.at(0));
  const auto targets = parseTargets(fields.at(1));
  if (!enabled.has_value() || !targets.has_value() || fields.at(2).contains(kFieldSeparator)) {
    return std::nullopt;
  }
  return State{enabled.value(), targets.value(), fields.at(2)};
}

} // namespace deskflow::mouse_broadcast
