function(set_cxx_standard CXX_TARGET CXX_VERSION)
  set_target_properties(${CXX_TARGET}
                        PROPERTIES CXX_STANDARD
                                   ${CXX_VERSION}
                                   CXX_STANDARD_REQUIRED
                                   ON
                                   CXX_EXTENSIONS
                                   OFF)
endfunction()
