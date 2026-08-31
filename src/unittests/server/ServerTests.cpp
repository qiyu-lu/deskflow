/*
 * Deskflow -- mouse and keyboard sharing utility
 * SPDX-FileCopyrightText: (C) 2025 Chris Rizzitello <sithlord48@gmail.com>
 * SPDX-FileCopyrightText: (C) 2014 - 2016 Synergy App Ltd
 * SPDX-License-Identifier: GPL-2.0-only WITH LicenseRef-OpenSSL-Exception
 */

#include "ServerTests.h"

#include "server/InputFilter.h"
#include "server/Server.h"

#include <set>

void ServerTests::SwitchToScreenInfo_alloc_screen()
{
  auto actual = new Server::SwitchToScreenInfo("test");
  QCOMPARE(actual->m_screen, "test");
  delete actual;
}

void ServerTests::KeyboardBroadcastInfo_alloc_stateAndSceens()
{
  auto info = new Server::KeyboardBroadcastInfo(Server::KeyboardBroadcastInfo::State::kOn, "test");
  QCOMPARE(info->m_state, Server::KeyboardBroadcastInfo::State::kOn);
  QCOMPARE(info->m_screens, "test");
  delete info;
}

void ServerTests::MouseBroadcastInfo_alloc_stateAndScreens()
{
  auto info = new Server::MouseBroadcastInfo(Server::MouseBroadcastInfo::State::kOn, "client1");
  QCOMPARE(info->m_state, Server::MouseBroadcastInfo::State::kOn);
  QCOMPARE(info->m_screens, "client1");
  delete info;
}

void ServerTests::MouseBroadcastAction_formatsSelectedScreens()
{
  const std::set<std::string> screens = {"client1", "client2"};
  const InputFilter::MouseBroadcastAction action(nullptr, InputFilter::MouseBroadcastAction::kOn, screens);

  QCOMPARE(action.getMode(), InputFilter::MouseBroadcastAction::kOn);
  QVERIFY(action.getScreens() == screens);
  QCOMPARE(action.format(), "mouseBroadcast(on,client1:client2)");
}

void ServerTests::mapMouseBroadcastCoordinate_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("sourceOrigin");
  QTest::addColumn<int>("sourceSize");
  QTest::addColumn<int>("targetOrigin");
  QTest::addColumn<int>("targetSize");
  QTest::addColumn<int>("expected");

  QTest::newRow("top-left") << 0 << 0 << 1920 << 0 << 2560 << 0;
  QTest::newRow("bottom-right") << 1919 << 0 << 1920 << 0 << 2560 << 2559;
  QTest::newRow("center") << 50 << 0 << 101 << 0 << 201 << 100;
  QTest::newRow("negative-source-origin") << -50 << -100 << 201 << 200 << 401 << 300;
  QTest::newRow("clamp-below-source") << -10 << 0 << 100 << 100 << 200 << 100;
  QTest::newRow("clamp-above-source") << 200 << 0 << 100 << 100 << 200 << 299;
  QTest::newRow("single-source-coordinate") << 42 << 42 << 1 << 100 << 200 << 100;
  QTest::newRow("single-target-coordinate") << 50 << 0 << 101 << -20 << 1 << -20;
}

void ServerTests::mapMouseBroadcastCoordinate()
{
  QFETCH(int, value);
  QFETCH(int, sourceOrigin);
  QFETCH(int, sourceSize);
  QFETCH(int, targetOrigin);
  QFETCH(int, targetSize);
  QFETCH(int, expected);

  QCOMPARE(
      deskflow::server::mapMouseBroadcastCoordinate(value, sourceOrigin, sourceSize, targetOrigin, targetSize), expected
  );
}

QTEST_MAIN(ServerTests)
