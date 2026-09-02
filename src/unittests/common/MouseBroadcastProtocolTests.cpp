/*
 * Deskflow -- mouse and keyboard sharing utility
 * SPDX-FileCopyrightText: (C) 2026 Deskflow Developers
 * SPDX-License-Identifier: GPL-2.0-only WITH LicenseRef-OpenSSL-Exception
 */

#include "common/MouseBroadcastProtocol.h"

#include <QTest>

class MouseBroadcastProtocolTests : public QObject
{
  Q_OBJECT

private Q_SLOTS:
  void request_roundTripsAllTargets();
  void request_roundTripsSelectedTargets();
  void request_rejectsInvalidPayloads_data();
  void request_rejectsInvalidPayloads();
  void state_roundTripsReason();
};

void MouseBroadcastProtocolTests::request_roundTripsAllTargets()
{
  const auto payload = deskflow::mouse_broadcast::formatRequest(true, {});
  QCOMPARE(payload, QStringLiteral("on|*"));

  const auto request = deskflow::mouse_broadcast::parseRequest(payload);
  QVERIFY(request.has_value());
  QVERIFY(request->enabled);
  QVERIFY(request->targets.isEmpty());
}

void MouseBroadcastProtocolTests::request_roundTripsSelectedTargets()
{
  const auto payload = deskflow::mouse_broadcast::formatRequest(
      false, {QStringLiteral("client2"), QStringLiteral("client1"), QStringLiteral("client1")}
  );
  QCOMPARE(payload, QStringLiteral("off|client1:client2"));

  const auto request = deskflow::mouse_broadcast::parseRequest(payload);
  QVERIFY(request.has_value());
  QVERIFY(!request->enabled);
  QCOMPARE(request->targets, QStringList({QStringLiteral("client1"), QStringLiteral("client2")}));
}

void MouseBroadcastProtocolTests::request_rejectsInvalidPayloads_data()
{
  QTest::addColumn<QString>("payload");

  QTest::newRow("toggle-is-not-a-gui-command") << QStringLiteral("toggle|*");
  QTest::newRow("missing-targets") << QStringLiteral("on|");
  QTest::newRow("missing-mode") << QStringLiteral("client1");
  QTest::newRow("extra-field") << QStringLiteral("on|client1|unexpected");
  QTest::newRow("invalid-target-character") << QStringLiteral("on|client,1");
  QTest::newRow("empty-target") << QStringLiteral("on|client1::client2");
}

void MouseBroadcastProtocolTests::request_rejectsInvalidPayloads()
{
  QFETCH(QString, payload);
  QVERIFY(!deskflow::mouse_broadcast::parseRequest(payload).has_value());
}

void MouseBroadcastProtocolTests::state_roundTripsReason()
{
  const auto payload =
      deskflow::mouse_broadcast::formatState(false, {QStringLiteral("client1")}, QStringLiteral("multipleMonitors"));
  QCOMPARE(payload, QStringLiteral("off|client1|multipleMonitors"));

  const auto state = deskflow::mouse_broadcast::parseState(payload);
  QVERIFY(state.has_value());
  QVERIFY(!state->enabled);
  QCOMPARE(state->targets, QStringList({QStringLiteral("client1")}));
  QCOMPARE(state->reason, QStringLiteral("multipleMonitors"));
}

QTEST_MAIN(MouseBroadcastProtocolTests)

#include "MouseBroadcastProtocolTests.moc"
