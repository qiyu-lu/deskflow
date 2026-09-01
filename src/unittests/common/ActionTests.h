/*
 * Deskflow -- mouse and keyboard sharing utility
 * SPDX-FileCopyrightText: (C) 2026 Deskflow Developers
 * SPDX-License-Identifier: GPL-2.0-only WITH LicenseRef-OpenSSL-Exception
 */

#include <QTest>

class ActionTests : public QObject
{
  Q_OBJECT
private Q_SLOTS:
  void mouseBroadcastText_allScreens();
  void mouseBroadcastText_selectedScreens();
  void mouseBroadcastSettings_roundTripsMode();
};
