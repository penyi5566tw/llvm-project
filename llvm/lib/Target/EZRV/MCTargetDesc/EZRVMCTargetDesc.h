//===-- EZRVMCTargetDesc.h - EZRV Target Descriptions ---------------------===//
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

#ifndef LLVM_LIB_TARGET_EZRV_MCTARGETDESC_EZRVMCTARGETDESC_H
#define LLVM_LIB_TARGET_EZRV_MCTARGETDESC_EZRVMCTARGETDESC_H

// Defines symbolic names for EZRV registers.
#define GET_REGINFO_ENUM
#include "EZRVGenRegisterInfo.inc"

#endif // LLVM_LIB_TARGET_EZRV_MCTARGETDESC_EZRVMCTARGETDESC_H
