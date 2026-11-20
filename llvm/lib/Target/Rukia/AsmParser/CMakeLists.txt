add_llvm_component_library(LLVMRukiaAsmParser
  RukiaAsmParser.cpp

  LINK_COMPONENTS
  MC
  MCParser
  RukiaDesc
  RukiaInfo
  Support

  ADD_TO_COMPONENT
  Rukia
  )
