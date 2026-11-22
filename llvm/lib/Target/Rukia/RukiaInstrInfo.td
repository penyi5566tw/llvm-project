//===-- RukiaInstrInfo.td - Target Description for Rukia ---*- tablegen -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Instruction base class
//===----------------------------------------------------------------------===//

// Base class for every 32-bit Rukia instruction. Each instruction fills in
// all 32 bits of Inst itself.
class RukiaInst<dag outs, dag ins, string opcodestr, string argstr>
    : Instruction {
  field bits<32> Inst;
  // Bits that may differ without changing the decoding. Required by the
  // disassembler emitter; Rukia has none.
  field bits<32> SoftFail = 0;
  let Size = 4;

  let Namespace = "Rukia";
  let OutOperandList = outs;
  let InOperandList = ins;
  let AsmString = opcodestr # !if(!empty(argstr), "", "\t" # argstr);
}

//===----------------------------------------------------------------------===//
// Operands
//===----------------------------------------------------------------------===//

// Signed 12-bit immediate. The asm parser calls isSImm12() / addImmOperands().
def SImm12AsmOperand : AsmOperandClass {
  let Name = "SImm12";
  let RenderMethod = "addImmOperands";
}

def simm12 : Operand<i32> {
  let ParserMatchClass = SImm12AsmOperand;
  let DecoderMethod = "decodeSImmOperand<12>";
  let OperandType = "OPERAND_IMMEDIATE";
}

//===----------------------------------------------------------------------===//
// System instructions
//===----------------------------------------------------------------------===//

// ecall: environment call (syscall). Encoding 0x00000073.
def ECALL : RukiaInst<(outs), (ins), "ecall", ""> {
  let Inst{31-20} = 0;         // imm12
  let Inst{19-15} = 0;         // rs1
  let Inst{14-12} = 0;         // funct3
  let Inst{11-7}  = 0;         // rd
  let Inst{6-0}   = 0b1110011; // opcode: SYSTEM

  let hasSideEffects = 1;
  let mayLoad = 0;
  let mayStore = 0;
}

//===----------------------------------------------------------------------===//
// Integer arithmetic
//===----------------------------------------------------------------------===//

// add rd, rs1, rs2: rd = rs1 + rs2. R-type.
def ADD : RukiaInst<(outs GPR:$rd),
                    (ins GPR:$rs1, GPR:$rs2),
                    "add", "$rd, $rs1, $rs2"> {
  bits<5> rs2;
  bits<5> rs1;
  bits<5> rd;

  let Inst{31-25} = 0b0000000; // funct7
  let Inst{24-20} = rs2;
  let Inst{19-15} = rs1;
  let Inst{14-12} = 0b000;     // funct3
  let Inst{11-7}  = rd;
  let Inst{6-0}   = 0b0110011; // opcode: OP

  let isCommutable = 1;
  let hasSideEffects = 0;
  let mayLoad = 0;
  let mayStore = 0;
}

// addi rd, rs1, imm12: rd = rs1 + sext(imm12). I-type.
def ADDI : RukiaInst<(outs GPR:$rd),
                     (ins GPR:$rs1, simm12:$imm12),
                     "addi", "$rd, $rs1, $imm12"> {
  bits<12> imm12;
  bits<5> rs1;
  bits<5> rd;

  let Inst{31-20} = imm12;
  let Inst{19-15} = rs1;
  let Inst{14-12} = 0b000;     // funct3
  let Inst{11-7}  = rd;
  let Inst{6-0}   = 0b0010011; // opcode: OP-IMM

  let hasSideEffects = 0;
  let mayLoad = 0;
  let mayStore = 0;
}
