#pragma once

#include <iostream>
#include "imgui.h"

#include "debug_state.hpp"
#include "system/psx_system.hpp"

namespace Debug{
  void DrawMenuBar(DebugWindowState& state, Jun::PsxSystem& system);
}
