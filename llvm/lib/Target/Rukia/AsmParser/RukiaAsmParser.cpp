//===-- RukiaAsmParser.cpp - Parse Rukia assembly to MCInst ---------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "MCTargetDesc/RukiaMCTargetDesc.h"
#include "TargetInfo/RukiaTargetInfo.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCParser/AsmLexer.h"
#include "llvm/MC/MCParser/MCParsedAsmOperand.h"
#include "llvm/MC/MCParser/MCTargetAsmParser.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/Compiler.h"

using namespace llvm;

#define DEBUG_TYPE "rukia-asm-parser"

namespace {

class RukiaAsmParser : public MCTargetAsmParser {
  // Declares MatchInstructionImpl(), ComputeAvailableFeatures(), ...
#define GET_ASSEMBLER_HEADER
#include "RukiaGenAsmMatcher.inc"

  bool parseRegister(MCRegister &Reg, SMLoc &StartLoc, SMLoc &EndLoc) override;
  ParseStatus tryParseRegister(MCRegister &Reg, SMLoc &StartLoc,
                               SMLoc &EndLoc) override;
  bool parseInstruction(ParseInstructionInfo &Info, StringRef Name,
                        SMLoc NameLoc, OperandVector &Operands) override;
  bool matchAndEmitInstruction(SMLoc IDLoc, unsigned &Opcode,
                               OperandVector &Operands, MCStreamer &Out,
                               uint64_t &ErrorInfo,
                               bool MatchingInlineAsm) override;

public:
  RukiaAsmParser(const MCSubtargetInfo &STI, MCAsmParser &Parser,
                 const MCInstrInfo &MII, const MCTargetOptions &Options)
      : MCTargetAsmParser(Options, STI, MII) {
    setAvailableFeatures(ComputeAvailableFeatures(STI.getFeatureBits()));
  }
};

// One parsed operand. The mnemonic itself is a Token operand.
struct RukiaOperand : public MCParsedAsmOperand {
  enum KindTy { Token, Register } Kind;
  SMLoc StartLoc, EndLoc;
  StringRef Tok;  // Kind == Token
  MCRegister Reg; // Kind == Register

  explicit RukiaOperand(KindTy K) : Kind(K) {}

  bool isToken() const override { return Kind == Token; }
  bool isReg() const override { return Kind == Register; }
  bool isImm() const override { return false; }
  bool isMem() const override { return false; }

  StringRef getToken() const {
    assert(isToken() && "Invalid access!");
    return Tok;
  }
  MCRegister getReg() const override {
    assert(isReg() && "Invalid access!");
    return Reg;
  }
  SMLoc getStartLoc() const override { return StartLoc; }
  SMLoc getEndLoc() const override { return EndLoc; }

  // Used by the generated convertToMCInst() for register operands.
  void addRegOperands(MCInst &Inst, unsigned N) const {
    assert(N == 1 && "Invalid number of operands!");
    Inst.addOperand(MCOperand::createReg(getReg()));
  }

  void print(raw_ostream &OS, const MCAsmInfo &MAI) const override {
    if (isToken())
      OS << "'" << Tok << "'";
    else
      OS << "<register " << Reg.id() << ">";
  }

  static std::unique_ptr<RukiaOperand> createToken(StringRef Str, SMLoc S) {
    auto Op = std::make_unique<RukiaOperand>(Token);
    Op->Tok = Str;
    Op->StartLoc = Op->EndLoc = S;
    return Op;
  }

  static std::unique_ptr<RukiaOperand> createReg(MCRegister R, SMLoc S,
                                                 SMLoc E) {
    auto Op = std::make_unique<RukiaOperand>(Register);
    Op->Reg = R;
    Op->StartLoc = S;
    Op->EndLoc = E;
    return Op;
  }
};

} // end anonymous namespace

// MatchRegisterName() and MatchInstructionImpl().
#define GET_REGISTER_MATCHER
#define GET_MATCHER_IMPLEMENTATION
#include "RukiaGenAsmMatcher.inc"

bool RukiaAsmParser::parseRegister(MCRegister &Reg, SMLoc &StartLoc,
                                   SMLoc &EndLoc) {
  if (!tryParseRegister(Reg, StartLoc, EndLoc).isSuccess())
    return Error(StartLoc, "invalid register name");
  return false;
}

ParseStatus RukiaAsmParser::tryParseRegister(MCRegister &Reg,
                                             SMLoc &StartLoc,
                                             SMLoc &EndLoc) {
  const AsmToken &Tok = getParser().getTok();
  StartLoc = Tok.getLoc();
  EndLoc = Tok.getEndLoc();
  if (Tok.isNot(AsmToken::Identifier))
    return ParseStatus::NoMatch;

  Reg = MatchRegisterName(Tok.getIdentifier()); // x0 ... x31
  if (!Reg)
    return ParseStatus::NoMatch;

  getParser().Lex(); // Eat the register name.
  return ParseStatus::Success;
}

bool RukiaAsmParser::parseInstruction(ParseInstructionInfo &Info,
                                      StringRef Name, SMLoc NameLoc,
                                      OperandVector &Operands) {
  // The mnemonic is always the first operand.
  Operands.push_back(RukiaOperand::createToken(Name, NameLoc));

  // Comma-separated register operands, e.g. "x10, x11, x12".
  // TODO: immediate operands.
  if (getLexer().isNot(AsmToken::EndOfStatement)) {
    do {
      MCRegister Reg;
      SMLoc S, E;
      if (!tryParseRegister(Reg, S, E).isSuccess())
        return Error(getLexer().getLoc(), "expected register");
      Operands.push_back(RukiaOperand::createReg(Reg, S, E));
    } while (parseOptionalToken(AsmToken::Comma));
  }

  if (getLexer().isNot(AsmToken::EndOfStatement))
    return Error(getLexer().getLoc(), "unexpected token");

  getParser().Lex(); // Consume the EndOfStatement.
  return false;
}

bool RukiaAsmParser::matchAndEmitInstruction(SMLoc IDLoc, unsigned &Opcode,
                                             OperandVector &Operands,
                                             MCStreamer &Out,
                                             uint64_t &ErrorInfo,
                                             bool MatchingInlineAsm) {
  MCInst Inst;
  switch (MatchInstructionImpl(Operands, Inst, ErrorInfo, MatchingInlineAsm)) {
  case Match_Success:
    Inst.setLoc(IDLoc);
    Out.emitInstruction(Inst, getSTI());
    return false;
  case Match_MnemonicFail:
    return Error(IDLoc, "unrecognized instruction mnemonic");
  case Match_InvalidOperand:
    return Error(IDLoc, "invalid operand for instruction");
  default:
    return Error(IDLoc, "invalid instruction");
  }
}

extern "C" LLVM_ABI LLVM_EXTERNAL_VISIBILITY void
LLVMInitializeRukiaAsmParser() {
  RegisterMCAsmParser<RukiaAsmParser> X(getTheRukia32Target());
}
