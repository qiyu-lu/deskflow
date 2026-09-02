/*
 * Deskflow -- mouse and keyboard sharing utility
 * SPDX-FileCopyrightText: (C) 2026 Deskflow Developers
 * SPDX-License-Identifier: GPL-2.0-only WITH LicenseRef-OpenSSL-Exception
 */

#pragma once

#include <cstdint>

namespace deskflow::input_broadcast {

enum Mode : uint8_t
{
  None = 0,
  Mouse = 1 << 0,
  Keyboard = 1 << 1
};

inline uint8_t modes(bool mouse, bool keyboard)
{
  return static_cast<uint8_t>((mouse ? Mouse : None) | (keyboard ? Keyboard : None));
}

} // namespace deskflow::input_broadcast
