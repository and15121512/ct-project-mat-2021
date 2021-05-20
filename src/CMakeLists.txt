include(CTest)
enable_testing()

add_library(skeletonization
  skeletonization.h
  skeletonization.cpp
)
set_property(TARGET skeletonization PROPERTY CXX_STANDARD 17)

add_executable(main
  main.cpp
)
set_property(TARGET main PROPERTY CXX_STANDARD 17)

target_link_libraries(main
  ${OpenCV_LIBS}
  skeletonization
)

# Installation
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/build/bin CACHE PATH ${CMAKE_SOURCE_DIR}/build FORCE)
endif(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

install(TARGETS main CONFIGURATIONS Release RUNTIME DESTINATION ".")
install(DIRECTORY ${PROJECT_SOURCE_DIR}/data DESTINATION ".")
install(DIRECTORY DESTINATION "./out")

# Testing
set(TestBinDir ${CMAKE_SOURCE_DIR}/build/bin)
set(TestInDir ${CMAKE_SOURCE_DIR}/build/bin/data/test_images)
set(TestOutSkelDir ${CMAKE_SOURCE_DIR}/build/bin/data/test_skel)
set(TestOutMergedDir ${CMAKE_SOURCE_DIR}/build/bin/data/test_merged)
set(TestOutDir ${CMAKE_SOURCE_DIR}/build/bin/out)

set(TestInputs "pict1.png" "pict2.png" "pict3.png" "pict4.png")
foreach(TestInput ${TestInputs})
  add_test(
    NAME run_${TestInput}
    COMMAND ${TestBinDir}/main.exe ${TestInDir}/${TestInput} ${TestOutDir}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/build/bin
  )
  add_test(
    NAME cmp_skel_${TestInput}
    COMMAND ${CMAKE_COMMAND} -E compare_files ${TestOutSkelDir}/${TestInput} ${TestOutDir}/skel_${TestInput}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/build/bin
  )
  add_test(
    NAME cmp_merged_${TestInput}
    COMMAND ${CMAKE_COMMAND} -E compare_files ${TestOutMergedDir}/${TestInput} ${TestOutDir}/merged_${TestInput}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/build/bin
  )
endforeach()
