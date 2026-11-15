//===-- RukiaTargetInfo.cpp - Rukia Target Implementation -----------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "TargetInfo/RukiaTargetInfo.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/Compiler.h"

using namespace llvm;

Target &llvm::getTheRukia32Target() {
  static Target TheRukia32Target;
  return TheRukia32Target;
}

extern "C" LLVM_ABI LLVM_EXTERNAL_VISIBILITY void
LLVMInitializeRukiaTargetInfo() {
  RegisterTarget<Triple::rukia32> X(getTheRukia32Target(), "rukia32",
                                    "32-bit Rukia (toy RISC-V)", "Rukia");
}
