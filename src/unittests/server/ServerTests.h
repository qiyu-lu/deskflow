/*
 * Deskflow -- mouse and keyboard sharing utility
 * SPDX-FileCopyrightText: (C) 2025 Chris Rizzitello <sithlord48@gmail.com>
 * SPDX-License-Identifier: GPL-2.0-only WITH LicenseRef-OpenSSL-Exception
 */

#include <QTest>

class ServerTests : public QObject
{
  Q_OBJECT
private Q_SLOTS:
  void SwitchToScreenInfo_alloc_screen();
  void KeyboardBroadcastInfo_alloc_stateAndSceens();
  void MouseBroadcastInfo_alloc_stateAndScreens();
  void MouseBroadcastAction_formatsSelectedScreens();
  void mapMouseBroadcastCoordinate_data();
  void mapMouseBroadcastCoordinate();
  void mouseBroadcastStartAllowed_data();
  void mouseBroadcastStartAllowed();
  void mouseBroadcastScreenSwitchBlocked_data();
  void mouseBroadcastScreenSwitchBlocked();
};
