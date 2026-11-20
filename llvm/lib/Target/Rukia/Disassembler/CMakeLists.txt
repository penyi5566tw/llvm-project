add_llvm_component_library(LLVMRukiaDisassembler
  RukiaDisassembler.cpp

  LINK_COMPONENTS
  MC
  MCDisassembler
  RukiaDesc
  RukiaInfo
  Support

  ADD_TO_COMPONENT
  Rukia
  )
