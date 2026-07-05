//===-- EZRVTargetInfo.cpp - EZRV Target Implementation ------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "EZRVTargetInfo.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/Compiler.h"

using namespace llvm;

Target &llvm::getTheEZRVTarget() {
  static Target TheEZRVTarget;
  return TheEZRVTarget;
}

extern "C" LLVM_ABI LLVM_EXTERNAL_VISIBILITY void
LLVMInitializeEZRVTargetInfo() {
  RegisterTarget<Triple::ezrv32> X(getTheEZRVTarget(), "ezrv32",
                                   "32-bit easy RISCV", "EZRV");
}
