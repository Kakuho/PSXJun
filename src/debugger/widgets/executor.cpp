#include <variant>
#include <type_traits>

#include "./widgets.hpp"
#include "mips_r3000a/instructions.hpp"
#include "mips_r3000a/mips_manager.hpp"

namespace Debug{
  void ShowExecutorWidget(bool* p_open, Jun::PsxSystem& system){
    ImGuiWindowFlags window_flags = 0;
    std::uint8_t opcode = system.GetCpu().NextOpcode();

    ImGui::Begin("Executor", p_open, window_flags);
    ImGui::Text("%-7s: 0x%08x", "pc", system.GetCpu().State().PC());
    ImGui::Text("%-7s: %10u", "cycles", system.GetCpu().State().Cycles());
    ImGui::Text("Next Opcode: 0x%x", opcode);
    ImGui::Text("Instruction Hex: 0x%x", system.GetCpu().NextInstructionHex());
    ImGui::Separator();
    auto instructionVariant = system.GetCpu().CurrentInstruction();
    if(std::holds_alternative<Jun::RegisterInstruction>(instructionVariant)){
      Jun::RegisterInstruction& instruction = std::get<Jun::RegisterInstruction>(instructionVariant);
      ImGui::Text("%-6s", Jun::MipsManager::RegisterOpcodeMnemonic(instruction.funct).c_str());
      ImGui::SameLine();
      ImGui::Text("$%2d,", instruction.rd);
      ImGui::SameLine();
      ImGui::Text("$%2d,", instruction.rs);
      ImGui::SameLine();
      ImGui::Text("$%2d", instruction.rt);
    }
    else if(std::holds_alternative<Jun::JumpInstruction>(instructionVariant)){
      Jun::JumpInstruction& instruction = std::get<Jun::JumpInstruction>(instructionVariant);
      ImGui::Text("%-3s", Jun::MipsManager::JumpOpcodeMnemonic(opcode).c_str());
      ImGui::SameLine();
      ImGui::Text("0x%x", instruction.target);
    }
    else{
      Jun::ImmediateInstruction& instruction = std::get<Jun::ImmediateInstruction>(instructionVariant);
      ImGui::Text("%-3s", Jun::MipsManager::ImmediateOpcodeMnemonic(opcode).c_str());
      ImGui::SameLine();
      ImGui::Text("$%d,", instruction.rt);
      ImGui::SameLine();
      ImGui::Text("%x($%d)", instruction.immediate, instruction.rs);
    }
    if(ImGui::Button("Step")){
      system.Tick();
    }
    ImGui::End();
  }

} // namespace Debug
