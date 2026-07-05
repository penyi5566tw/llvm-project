add_llvm_component_library(LLVMEZRVDesc
  EZRVMCTargetDesc.cpp

  LINK_COMPONENTS
  MC
  Support

  ADD_TO_COMPONENT
  EZRV
  )
