add_llvm_component_library(LLVMRukiaInfo
  RukiaTargetInfo.cpp

  LINK_COMPONENTS
  MC
  Support

  ADD_TO_COMPONENT
  Rukia
  )
