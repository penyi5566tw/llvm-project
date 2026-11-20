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
// System instructions
//===----------------------------------------------------------------------===//

// ecall: environment call (syscall). Encoding 0x00000073.
let hasSideEffects = 1, mayLoad = 0, mayStore = 0 in
def ECALL : RukiaInst<(outs), (ins), "ecall", ""> {
  let Inst{31-20} = 0;         // imm12
  let Inst{19-15} = 0;         // rs1
  let Inst{14-12} = 0;         // funct3
  let Inst{11-7}  = 0;         // rd
  let Inst{6-0}   = 0b1110011; // opcode: SYSTEM
}
