add_llvm_component_library(LLVMRukiaDesc
  RukiaInstPrinter.cpp
  RukiaMCAsmInfo.cpp
  RukiaMCCodeEmitter.cpp
  RukiaMCTargetDesc.cpp

  LINK_COMPONENTS
  MC
  RukiaInfo
  Support
  TargetParser

  ADD_TO_COMPONENT
  Rukia
  )
