//===-- EZRVRegisterInfo.td - EZRV Register defs -------------*- tablegen -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//  Declarations that describe the EZRV register file
//===----------------------------------------------------------------------===//

let Namespace = "EZRV" in {
class EZRVReg<bits<5> Enc, string n> : Register<n> {
  let HWEncoding{4-0} = Enc;
}

foreach i = 0-31 in {
  def X#i : EZRVReg<i, "x"#i>;
}
} // Namespace = "EZRV"

def GPR : RegisterClass<"EZRV", [i32], 32, (sequence "X%u", 0, 31)>;
