//===-- RukiaDisassembler.cpp - Disassembler for Rukia --------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "MCTargetDesc/RukiaMCTargetDesc.h"
#include "TargetInfo/RukiaTargetInfo.h"
#include "llvm/MC/MCDecoderOps.h"
#include "llvm/MC/MCDisassembler/MCDisassembler.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/Compiler.h"
#include "llvm/Support/Endian.h"

using namespace llvm;

#define DEBUG_TYPE "rukia-disassembler"

typedef MCDisassembler::DecodeStatus DecodeStatus;

namespace {
class RukiaDisassembler : public MCDisassembler {
public:
  RukiaDisassembler(const MCSubtargetInfo &STI, MCContext &Ctx)
      : MCDisassembler(STI, Ctx) {}

  DecodeStatus getInstruction(MCInst &MI, uint64_t &Size,
                              ArrayRef<uint8_t> Bytes, uint64_t Address,
                              raw_ostream &CStream) const override;
};
} // end anonymous namespace

static MCDisassembler *createRukiaDisassembler(const Target &T,
                                               const MCSubtargetInfo &STI,
                                               MCContext &Ctx) {
  return new RukiaDisassembler(STI, Ctx);
}

extern "C" LLVM_ABI LLVM_EXTERNAL_VISIBILITY void
LLVMInitializeRukiaDisassembler() {
  TargetRegistry::RegisterMCDisassembler(getTheRukia32Target(),
                                         createRukiaDisassembler);
}

// Auto-generated decoder: DecoderTable32 + decodeInstruction().
#include "RukiaGenDisassemblerTables.inc"

DecodeStatus RukiaDisassembler::getInstruction(MCInst &MI, uint64_t &Size,
                                               ArrayRef<uint8_t> Bytes,
                                               uint64_t Address,
                                               raw_ostream &CStream) const {
  // Every Rukia instruction is 32 bits, stored little-endian.
  if (Bytes.size() < 4) {
    Size = 0;
    return MCDisassembler::Fail;
  }
  Size = 4;

  uint32_t Insn = support::endian::read32le(Bytes.data());
  return decodeInstruction(DecoderTable32, MI, Insn, Address, this, STI);
}
