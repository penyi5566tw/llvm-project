//===-- EZRVMCTargetDesc.cpp - EZRV Target Descriptions -------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file provides EZRV specific target descriptions.
//
//===----------------------------------------------------------------------===//

#include "EZRVMCTargetDesc.h"
#include "TargetInfo/EZRVTargetInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/Compiler.h"

#define GET_REGINFO_MC_DESC
#include "EZRVGenRegisterInfo.inc"

using namespace llvm;

static MCRegisterInfo *createEZRVMCRegisterInfo(const Triple &TT) {
  MCRegisterInfo *X = new MCRegisterInfo();
  // X1 ("ra" in RISC-V's ABI) is the return address register.
  InitEZRVMCRegisterInfo(X, EZRV::X1);
  return X;
}

extern "C" LLVM_ABI LLVM_EXTERNAL_VISIBILITY void LLVMInitializeEZRVTargetMC() {
  TargetRegistry::RegisterMCRegInfo(getTheEZRVTarget(),
                                    createEZRVMCRegisterInfo);
}
