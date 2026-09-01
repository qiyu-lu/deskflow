/*
 * Deskflow -- mouse and keyboard sharing utility
 * SPDX-FileCopyrightText: (C) 2026 Deskflow Developers
 * SPDX-License-Identifier: GPL-2.0-only WITH LicenseRef-OpenSSL-Exception
 */

#include "ActionTests.h"

#include "common/Action.h"

#include <QSettings>
#include <QTemporaryDir>

void ActionTests::mouseBroadcastText_allScreens()
{
  Action action;
  action.setType(static_cast<int>(Action::Type::mouseBroadcast));
  action.setMouseBroadcastMode(static_cast<int>(Action::MouseBroadcastMode::toggle));

  QCOMPARE(action.text(), QStringLiteral("mouseBroadcast(toggle)"));
}

void ActionTests::mouseBroadcastText_selectedScreens()
{
  Action action;
  action.setType(static_cast<int>(Action::Type::mouseBroadcast));
  action.setMouseBroadcastMode(static_cast<int>(Action::MouseBroadcastMode::on));
  action.setHaveScreens(true);
  action.addScreen(QStringLiteral("client1"));
  action.addScreen(QStringLiteral("client2"));

  QCOMPARE(action.text(), QStringLiteral("mouseBroadcast(on,client1:client2)"));
}

void ActionTests::mouseBroadcastSettings_roundTripsMode()
{
  QTemporaryDir temporaryDir;
  QVERIFY(temporaryDir.isValid());

  QSettings settings(temporaryDir.filePath(QStringLiteral("action.ini")), QSettings::IniFormat);
  Action saved;
  saved.setType(static_cast<int>(Action::Type::mouseBroadcast));
  saved.setMouseBroadcastMode(static_cast<int>(Action::MouseBroadcastMode::off));
  saved.setRestartServer(false);
  saved.saveSettings(settings);
  settings.sync();

  Action loaded;
  loaded.loadSettings(settings);
  QCOMPARE(loaded.type(), static_cast<int>(Action::Type::mouseBroadcast));
  QCOMPARE(loaded.mouseBroadcastMode(), static_cast<int>(Action::MouseBroadcastMode::off));
}

QTEST_MAIN(ActionTests)
