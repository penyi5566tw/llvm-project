//===-- RukiaMCAsmInfo.cpp - Rukia Asm Properties -------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "RukiaMCAsmInfo.h"
#include "llvm/TargetParser/Triple.h"

using namespace llvm;

RukiaMCAsmInfo::RukiaMCAsmInfo(const Triple &TT) {
  CommentString = "#";  // same as RISC-V
}
