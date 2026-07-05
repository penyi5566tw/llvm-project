add_llvm_component_group(EZRV)

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
