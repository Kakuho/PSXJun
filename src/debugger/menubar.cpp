#include "menubar.hpp"
#include "system/psx_system.hpp"

namespace Debug{

void DrawDebugMenu(bool* openRegisters, bool* openExecutor, bool* openMemory);
void DrawCpuMenu(bool* openRegisters, bool* openExecutor);
void DrawMemoryMenu();

void DrawMenuBar(DebugWindowState& state, Jun::PsxSystem& system){
  if (ImGui::BeginMainMenuBar()){
    DrawDebugMenu(&state.showRegisters, 
                  &state.showExecutor, 
                  &state.showMemory);
    ImGui::Text("Bios File: %s", system.GetMemmap().BiosPath().c_str());
    ImGui::EndMainMenuBar();
  }
}

void DrawDebugMenu(bool* openRegisters = nullptr, bool* openExecutor = nullptr, bool* openMemory = nullptr){
  if (ImGui::BeginMenu("Debug")){
    DrawCpuMenu(openRegisters, openExecutor);
    DrawMemoryMenu();
    ImGui::Separator();
    ImGui::EndMenu();
  }
}

void DrawCpuMenu(bool* openRegisters, bool* openExecutor){
  if (ImGui::BeginMenu("Cpu")){
    if (ImGui::MenuItem("Registers")){
      if(openRegisters){
        *openRegisters = true;
      }
    }
    if (ImGui::MenuItem("Executor")){
      if(openExecutor){
        *openExecutor = true;
      }
    }
    ImGui::EndMenu();
  }
}
    
void DrawMemoryMenu(){

}

} // namespace Debug
