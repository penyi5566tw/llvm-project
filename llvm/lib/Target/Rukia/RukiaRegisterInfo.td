//===-- RukiaRegisterInfo.td - Rukia Register defs ---------*- tablegen -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

let Namespace = "Rukia" in {

class RukiaReg<bits<5> Enc, string n, list<string> alt = []> : Register<n> {
  let HWEncoding{4-0} = Enc;
  let AltNames = alt;
}

def ABIRegAltName : RegAltNameIndex;

// x0 is hardwired to zero; x8 has two ABI names (s0 / fp).
let RegAltNameIndices = [ABIRegAltName] in {
  def GPR_X0  : RukiaReg< 0, "x0",  ["zero"]>;
  def GPR_X1  : RukiaReg< 1, "x1",  ["ra"]>;
  def GPR_X2  : RukiaReg< 2, "x2",  ["sp"]>;
  def GPR_X3  : RukiaReg< 3, "x3",  ["gp"]>;
  def GPR_X4  : RukiaReg< 4, "x4",  ["tp"]>;
  def GPR_X5  : RukiaReg< 5, "x5",  ["t0"]>;
  def GPR_X6  : RukiaReg< 6, "x6",  ["t1"]>;
  def GPR_X7  : RukiaReg< 7, "x7",  ["t2"]>;
  def GPR_X8  : RukiaReg< 8, "x8",  ["s0", "fp"]>;
  def GPR_X9  : RukiaReg< 9, "x9",  ["s1"]>;
  def GPR_X10 : RukiaReg<10, "x10", ["a0"]>;
  def GPR_X11 : RukiaReg<11, "x11", ["a1"]>;
  def GPR_X12 : RukiaReg<12, "x12", ["a2"]>;
  def GPR_X13 : RukiaReg<13, "x13", ["a3"]>;
  def GPR_X14 : RukiaReg<14, "x14", ["a4"]>;
  def GPR_X15 : RukiaReg<15, "x15", ["a5"]>;
  def GPR_X16 : RukiaReg<16, "x16", ["a6"]>;
  def GPR_X17 : RukiaReg<17, "x17", ["a7"]>;
  def GPR_X18 : RukiaReg<18, "x18", ["s2"]>;
  def GPR_X19 : RukiaReg<19, "x19", ["s3"]>;
  def GPR_X20 : RukiaReg<20, "x20", ["s4"]>;
  def GPR_X21 : RukiaReg<21, "x21", ["s5"]>;
  def GPR_X22 : RukiaReg<22, "x22", ["s6"]>;
  def GPR_X23 : RukiaReg<23, "x23", ["s7"]>;
  def GPR_X24 : RukiaReg<24, "x24", ["s8"]>;
  def GPR_X25 : RukiaReg<25, "x25", ["s9"]>;
  def GPR_X26 : RukiaReg<26, "x26", ["s10"]>;
  def GPR_X27 : RukiaReg<27, "x27", ["s11"]>;
  def GPR_X28 : RukiaReg<28, "x28", ["t3"]>;
  def GPR_X29 : RukiaReg<29, "x29", ["t4"]>;
  def GPR_X30 : RukiaReg<30, "x30", ["t5"]>;
  def GPR_X31 : RukiaReg<31, "x31", ["t6"]>;
} // RegAltNameIndices

} // Namespace = "Rukia"

def GPR : RegisterClass<"Rukia", [i32], 32, (sequence "GPR_X%u", 0, 31)>;
