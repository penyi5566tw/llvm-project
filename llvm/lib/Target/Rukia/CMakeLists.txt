add_llvm_component_group(Rukia)

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

add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)
