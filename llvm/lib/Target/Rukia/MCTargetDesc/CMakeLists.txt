add_llvm_component_library(LLVMRukiaDesc
  RukiaMCAsmInfo.cpp
  RukiaMCTargetDesc.cpp

  LINK_COMPONENTS
  MC
  RukiaInfo
  Support
  TargetParser

  ADD_TO_COMPONENT
  Rukia
  )
