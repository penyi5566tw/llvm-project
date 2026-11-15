#!/usr/bin/env bash
set -euo pipefail

LLVM_LIT=/root/llvm/build/bin/llvm-lit
RUKIA_TEST=/root/llvm/llvm-project/llvm/test/Rukia

"${LLVM_LIT}" -v "${RUKIA_TEST}"
