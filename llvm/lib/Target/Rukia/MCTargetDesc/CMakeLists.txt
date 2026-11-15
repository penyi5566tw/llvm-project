add_llvm_component_library(LLVMRukiaDesc
  RukiaMCTargetDesc.cpp

  LINK_COMPONENTS
  MC
  RukiaInfo
  Support
  TargetParser

  ADD_TO_COMPONENT
  Rukia
  )
