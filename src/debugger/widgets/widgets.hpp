#pragma once

#include "imgui.h"
#include "system/psx_system.hpp"

namespace Debug{
  void ShowRegistersWidget(bool* popen, Jun::PsxSystem& system);
  void ShowExecutorWidget(bool* popen, Jun::PsxSystem& system);
}
