// Registers

std::uint32_t CPU::GetRegisterValue(std::uint8_t index) const{
  if(index == 0){
    // zeroth register is hardwired to 0
    return 0;
  }
  else if (index <= 32){
    return m_registers[index];
  }
  else{
    /* TODO: should throw an out of bounds exception */
    std::cerr << "ERROR :: INDEX IS OUT OF BOUNDS" << '\n';
  }
}

// Memory getters

std::uint8_t CPU::ReadByte(std::index) const{
  /* TODO: wrapping around the address space*/
  return m_ram[index];
}

std::uint16_t CPU::GetHalfWord(std::size_t index1, std::size_t index2, 
                               std::size_t index3, std::size_t index4) const{
  /* TODO : wrapping around the address space */
  // Assumes: fetching bytes in the order M[index1], M[index2], M[index3], M[index4]
  std::uint8_t byte1 = ReadByte(index1);
  // R3000A is little endian, so the half word would be M[index4], M[index3], M[index2], M[index1].
}

std::uint32_t CPU::GetWord(std::size_t index) const{

}


std::uint32_t CPU::GetIntruction() const{
  // The MIPS ISA contains fixed size 32-bit instructions.
  std::uint32_t buffer = GetWord(ram[pc]);
}

// CPU operational functions
//---------------------------------------------------------------//
// Classic Fetch Decode Cycle:
//
// The CPU contains a buffer of ticks (m_ticks) which contains the amount of ticks
// needed / stored for each executed instruction. Tick() checks to see if there are any 
// pending ticks and proceeds only if there are no more ticks left in the buffer.
//
// Perhaps not the most cycle accurate, however later on I will do a survery to see how other 
// emulators handle cycle accuracy
//
//  * Fetch(): fetches the instruction from memory.
//
//    ^
//    |
//
//  * Tick(): checks to see if there is any buffered ticks. 
//            If not then proceeds to Fetch(), decode and executes the instruction.
//            Otherwise a call decrements the buffered ticks.
//
// 
//---------------------------------------------------------------//
//
// However the R3000A is a mips-1 processor and thus implements a 5 stage pipeline.
// Therefore more research is needed to understand how to create an emulator for a 
// 5-stage pipeline, as I expect timing considerations will be different, especially in regards
// to data hazards.
//
//---------------------------------------------------------------//

void CPU::Tick(){
  // first check if there are any buffered ticks
  if( GetTicks() ){
    return;
  }
  else{
    Fetch();
    std::uint8_t opcode = Instruction::GetOpcode(GetInstruction());  // decode step
    switch(opcode){
      case 0: // R-type instruction
        std::uint8_t funct = instruction::GetFunct(GetInstruction());
        switch(funct){
          case OP_ADD:    UnimplementedOp(); break;
          case OP_ADDU:   UnimplementedOp(); break;
          case OP_SUB:    UnimplementedOp(); break;
          case OP_SUBU:   UnimplementedOp(); break;
          case OP_MULT:   UnimplementedOp(); break;
          case OP_MULTU:  UnimplementedOp(); break;
          case OP_DIV:    UnimplementedOp(); break;
          case OP_DIVU:   UnimplementedOp(); break;
          case OP_MFHI:   UnimplementedOp(); break;
          case OP_MTHI:   UnimplementedOp(); break;
          case OP_MFLO:   UnimplementedOp(); break;
          case OP_MTLO:   UnimplementedOp(); break;
          case OP_AND:    UnimplementedOp(); break;
          case OP_NOR:    UnimplementedOp(); break;
          case OP_XOR:    UnimplementedOp(); break;
          case OP_OR:     UnimplementedOp(); break;
          case OP_JALR:   UnimplementedOp(); break;
          case OP_JR:     UnimplementedOp(); break;
          case OP_SLT:    UnimplementedOp(); break;
          case OP_SLTU:   UnimplementedOp(); break;
          case OP_SLL:    UnimplementedOp(); break;
          case OP_SRL:    UnimplementedOp(); break;
          case OP_SRA:    UnimplementedOp(); break;
          case OP_MFC0:   UnimplementedOp(); break;
        }
      // all other functions
      case OP_JP:     UnimplementedOp(); break;
      case OP_JAL:    UnimplementedOp(); break;
      case SP_SLTI:   UnimplementedOp(); break;
      case SP_SLTIU:  UnimplementedOp(); break;
      case SP_ANDI:   UnimplementedOp(); break;
      case SP_ORI:    UnimplementedOp(); break;
      case SP_BEQ:    UnimplementedOp(); break;
      case SP_BNE:    UnimplementedOp(); break;
      case SP_BLEZ:   UnimplementedOp(); break;
      case SP_BGTZL   UnimplementedOp(); break;
      case SP_ADDI:   UnimplementedOp(); break;
      case SP_ADDIU:  UnimplementedOp(); break;
      case SP_LUI:    UnimplementedOp(); break;
      case SP_SW:     UnimplementedOp(); break;
      case SP_LB:     UnimplementedOp(); break;
      case SP_LW:     UnimplementedOp(); break;
      case SP_LBU:    UnimplementedOp(); break;
      case SP_LHU:    UnimplementedOp(); break;
      case SP_SB:     UnimplementedOp(); break;
      case SP_SH:     UnimplementedOp(); break;
    }
  }
}

void CPU::Fetch(){
  SetInstruction( ReadWord( GetPC() ) );
}

// CPU opcodes functions
