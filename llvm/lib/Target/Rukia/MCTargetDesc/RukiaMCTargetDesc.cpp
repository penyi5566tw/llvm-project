//===-- RukiaMCTargetDesc.cpp - Rukia Target Descriptions -----------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// Registers the Rukia MC-layer components (MCAsmInfo, MCInstrInfo,
// MCRegisterInfo, MCSubtargetInfo, ...). Nothing is registered yet.
//
//===----------------------------------------------------------------------===//

#include "TargetInfo/RukiaTargetInfo.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/Compiler.h"

using namespace llvm;

extern "C" LLVM_ABI LLVM_EXTERNAL_VISIBILITY void
LLVMInitializeRukiaTargetMC() {
  // TODO: TargetRegistry::RegisterMCAsmInfo(getTheRukia32Target(), ...);
}
