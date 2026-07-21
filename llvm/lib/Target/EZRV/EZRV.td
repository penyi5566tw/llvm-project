//===-- EZRV.td - Describe the EZRV Target Machine ---------*- tablegen -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

include "llvm/Target/Target.td"

//===----------------------------------------------------------------------===//
// Registers
//===----------------------------------------------------------------------===//

include "EZRVRegisterInfo.td"

//===----------------------------------------------------------------------===//
// Define the EZRV target.
//===----------------------------------------------------------------------===//

def EZRV : Target;
