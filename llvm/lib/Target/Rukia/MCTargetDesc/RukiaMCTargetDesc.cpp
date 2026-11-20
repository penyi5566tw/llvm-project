//===-- RukiaMCTargetDesc.cpp - Rukia Target Descriptions -----------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// Registers the Rukia MC-layer components: MCAsmInfo, MCInstrInfo,
// MCRegisterInfo, MCSubtargetInfo and MCInstPrinter.
//
//===----------------------------------------------------------------------===//

#include "MCTargetDesc/RukiaMCTargetDesc.h"
#include "MCTargetDesc/RukiaInstPrinter.h"
#include "MCTargetDesc/RukiaMCAsmInfo.h"
#include "TargetInfo/RukiaTargetInfo.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/Compiler.h"

#define GET_INSTRINFO_MC_DESC
#include "RukiaGenInstrInfo.inc"

#define GET_REGINFO_MC_DESC
#include "RukiaGenRegisterInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "RukiaGenSubtargetInfo.inc"

using namespace llvm;

static MCAsmInfo *createRukiaMCAsmInfo(const MCRegisterInfo &MRI,
                                       const Triple &TT,
                                       const MCTargetOptions &Options) {
  return new RukiaMCAsmInfo(TT);
}

static MCInstrInfo *createRukiaMCInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();
  InitRukiaMCInstrInfo(X);
  return X;
}

static MCRegisterInfo *createRukiaMCRegisterInfo(const Triple &TT) {
  MCRegisterInfo *X = new MCRegisterInfo();
  InitRukiaMCRegisterInfo(X, Rukia::GPR_X1); // return address
  return X;
}

static MCSubtargetInfo *
createRukiaMCSubtargetInfo(const Triple &TT, StringRef CPU, StringRef FS) {
  return createRukiaMCSubtargetInfoImpl(TT, CPU, /*TuneCPU=*/CPU, FS);
}

static MCInstPrinter *createRukiaMCInstPrinter(const Triple &T,
                                               unsigned SyntaxVariant,
                                               const MCAsmInfo &MAI,
                                               const MCInstrInfo &MII,
                                               const MCRegisterInfo &MRI) {
  return new RukiaInstPrinter(MAI, MII, MRI);
}

extern "C" LLVM_ABI LLVM_EXTERNAL_VISIBILITY void
LLVMInitializeRukiaTargetMC() {
  Target &T = getTheRukia32Target();
  TargetRegistry::RegisterMCAsmInfo(T, createRukiaMCAsmInfo);
  TargetRegistry::RegisterMCInstrInfo(T, createRukiaMCInstrInfo);
  TargetRegistry::RegisterMCRegInfo(T, createRukiaMCRegisterInfo);
  TargetRegistry::RegisterMCSubtargetInfo(T, createRukiaMCSubtargetInfo);
  TargetRegistry::RegisterMCInstPrinter(T, createRukiaMCInstPrinter);
}
