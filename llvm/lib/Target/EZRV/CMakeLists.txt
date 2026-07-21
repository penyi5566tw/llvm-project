add_llvm_component_group(EZRV)

set(LLVM_TARGET_DEFINITIONS EZRV.td)

tablegen(LLVM EZRVGenRegisterInfo.inc -gen-register-info)

add_public_tablegen_target(EZRVCommonTableGen)

add_llvm_target(EZRVCodeGen
  EZRVTargetMachine.cpp

  LINK_COMPONENTS
  MC
  Support

  ADD_TO_COMPONENT
  EZRV
  )

add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)
