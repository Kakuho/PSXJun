#include <variant>
#include <type_traits>

#include "./widgets.hpp"
#include "mips_r3000a/instructions.hpp"
#include "mips_r3000a/mips_manager.hpp"

namespace Debug{  

class InstructionTrace{
  public:
    InstructionTrace() = default;
    void AppendInstructionString(std::string& val){ m_buffer.push_back(val);}
  private:
    std::vector<std::string> m_buffer;  // linear history representation
};

void ShowInstructionTraceWidget(bool* p_open, InstructionTrace& history){

}

}
