#include "widgets.hpp"

#include "mips_r3000a/mips_state.hpp"
#include "mips_r3000a/cop0/cop0_state.hpp"
#include "system/psx_system.hpp"

namespace Debug{

  void DrawGprTab(Jun::PsxSystem& system);
  void DrawCop0Tab(Jun::PsxSystem& system);

  void ShowRegistersWidget(bool* p_open, Jun::PsxSystem& system){
    ImGuiWindowFlags window_flags = 0;
    ImGui::Begin("Registers", p_open, window_flags);

    ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
    if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags)){
      DrawGprTab(system);
      DrawCop0Tab(system);
      ImGui::EndTabBar();
    }
    ImGui::End();
  }

  void DrawGprTab(Jun::PsxSystem& system){
    if (ImGui::BeginTabItem("GPR")){
      for(std::uint8_t i = 0; i < 32; i++){
        ImGui::Text(
            "%s - $%02d: 0x%08x", 
            Jun::Gprs::Name(i).c_str(), 
            i,
            system.GetCpu().State().Reg(i)
        );
      }
      ImGui::EndTabItem();
    }
  }

  void DrawCop0Tab(Jun::PsxSystem& system){
    if (ImGui::BeginTabItem("COP0")){
      for(std::uint8_t i = 0; i < 16; i++){
        if(auto name = Jun::Cop0RegisterName(i); name){
          ImGui::Text(
              "%-5s: 0x%08x", 
              name.value().c_str(), 
              system.GetCpu().State().Cop0().RegVal(i).value_or(0xDEADBEEF)
          );
        }
      }
      ImGui::EndTabItem();
    }
  }

} // namespace kaka
