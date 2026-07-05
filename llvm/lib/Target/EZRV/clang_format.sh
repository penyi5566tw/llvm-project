#!/usr/bin/env bash
set -euo pipefail
shopt -s globstar nullglob

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

clang-format -i "${SCRIPT_DIR}"/**/*.cpp "${SCRIPT_DIR}"/**/*.h
