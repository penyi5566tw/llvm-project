add_llvm_component_group(Rukia)

set(LLVM_TARGET_DEFINITIONS Rukia.td)

tablegen(LLVM RukiaGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM RukiaGenDisassemblerTables.inc -gen-disassembler)
tablegen(LLVM RukiaGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM RukiaGenMCCodeEmitter.inc -gen-emitter)
tablegen(LLVM RukiaGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM RukiaGenSubtargetInfo.inc -gen-subtarget)

add_public_tablegen_target(RukiaCommonTableGen)

add_llvm_target(RukiaCodeGen
  RukiaTargetMachine.cpp

  LINK_COMPONENTS
  CodeGen
  Core
  MC
  RukiaDesc
  RukiaInfo
  Support
  Target
  TargetParser

  ADD_TO_COMPONENT
  Rukia
  )

add_subdirectory(Disassembler)
add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)
