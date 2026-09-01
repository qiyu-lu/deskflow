/*
 * Deskflow -- mouse and keyboard sharing utility
 * SPDX-FileCopyrightText: (C) 2025 Chris Rizzitello <sithlord48@gmail.com>
 * SPDX-FileCopyrightText: (C) 2025 Deskflow Developers
 * SPDX-FileCopyrightText: (C) 2012 - 2016 Synergy App Ltd
 * SPDX-FileCopyrightText: (C) 2008 Volker Lanz <vl@fidra.de>
 * SPDX-License-Identifier: GPL-2.0-only WITH LicenseRef-OpenSSL-Exception
 */

#pragma once

#include "common/Action.h"

#include <QDialog>

class Hotkey;
class ServerConfig;
class KeySequenceWidget;

namespace Ui {
class ActionDialog;
}

class ActionDialog : public QDialog
{
  Q_OBJECT

public:
  ActionDialog(QWidget *parent, const ServerConfig &config, Hotkey &hotkey, Action &action);
  ~ActionDialog() override;

protected Q_SLOTS:
  void accept() override;

private:
  void updateSize();
  void keySequenceChanged();
  void itemToggled() const;
  void actionTypeChanged(int index);
  Action::Type currentActionType() const;
  bool isKeyAction(Action::Type type) const;
  bool canSave() const;

  std::unique_ptr<Ui::ActionDialog> ui;
  Hotkey &m_hotkey;
  Action &m_action;
};
