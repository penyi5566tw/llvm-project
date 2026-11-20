//===-- Rukia.td - Describe the Rukia Target Machine -------*- tablegen -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Target-independent interfaces
//===----------------------------------------------------------------------===//

include "llvm/Target/Target.td"

//===----------------------------------------------------------------------===//
// Registers and instructions
//===----------------------------------------------------------------------===//

include "RukiaRegisterInfo.td"
include "RukiaInstrInfo.td"

//===----------------------------------------------------------------------===//
// Target
//===----------------------------------------------------------------------===//

def RukiaInstrInfo : InstrInfo;

def Rukia : Target {
  let InstructionSet = RukiaInstrInfo;
}
