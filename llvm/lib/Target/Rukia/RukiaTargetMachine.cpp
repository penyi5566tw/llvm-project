//===-- RukiaTargetMachine.cpp - Define TargetMachine for Rukia -----------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "RukiaTargetMachine.h"
#include "TargetInfo/RukiaTargetInfo.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/Compiler.h"

using namespace llvm;

extern "C" LLVM_ABI LLVM_EXTERNAL_VISIBILITY void LLVMInitializeRukiaTarget() {
  RegisterTargetMachine<RukiaTargetMachine> X(getTheRukia32Target());
}

static std::string computeDataLayout() {
  return "e"        // Little endian
         "-m:e"     // ELF name mangling
         "-p:32:32" // 32-bit pointers, 32-bit aligned
         "-i64:64"  // 64-bit integers, 64-bit aligned
         "-n32"     // 32-bit native integer width
         "-S128";   // 128-bit natural stack alignment (RISC-V ilp32)
}

static Reloc::Model getEffectiveRelocModel(std::optional<Reloc::Model> RM) {
  return RM.value_or(Reloc::Static);
}

RukiaTargetMachine::RukiaTargetMachine(const Target &T, const Triple &TT,
                                       StringRef CPU, StringRef FS,
                                       const TargetOptions &Options,
                                       std::optional<Reloc::Model> RM,
                                       std::optional<CodeModel::Model> CM,
                                       CodeGenOptLevel OL, bool JIT)
    : CodeGenTargetMachineImpl(T, computeDataLayout(), TT, CPU, FS, Options,
                               getEffectiveRelocModel(RM),
                               getEffectiveCodeModel(CM, CodeModel::Small),
                               OL) {
  // TODO: call initAsmInfo() once MCAsmInfo/MCRegisterInfo are registered
  // in RukiaMCTargetDesc.cpp; calling it now would assert.
}
