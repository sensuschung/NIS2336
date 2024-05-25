add_llvm_library( libFuncArgCnt MODULE BUILDTREE_ONLY
  legacyArgCnt.cpp
  newArgCnt.cpp

  DEPENDS
  intrinsics_gen
  PLUGIN_TOOL
  opt
  )
