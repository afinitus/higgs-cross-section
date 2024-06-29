include_directories ("${PROJECT_SOURCE_DIR}/Spurious_Signal/inc")
include_directories ("${PROJECT_SOURCE_DIR}/Spurious_Signal/Root")

add_library(RooTwoSidedCBShape SHARED Root/RooTwoSidedCBShape.cxx inc/RooTwoSidedCBShape.h G__RooTwoSidedCBShape.cxx)
root_generate_dictionary(G__RooTwoSidedCBShape RooTwoSidedCBShape.h LINKDEF Root/LinkDef.h)
target_link_libraries(RooTwoSidedCBShape PUBLIC ${ROOT_LIBRARIES})

# add the executable
add_executable (Hyy_spurious util/Hyy_spurious.cxx)
add_executable (signal_modeling util/signal_modeling.cxx)
add_executable (Smoothing util/Smoothing.cxx)
add_executable (testSmooth util/testSmooth.cxx)
# target link
target_link_libraries (Hyy_spurious RooTwoSidedCBShape)
target_link_libraries (Hyy_spurious ${ROOT_LIBRARIES})
target_link_libraries (signal_modeling RooTwoSidedCBShape)
target_link_libraries (signal_modeling ${ROOT_LIBRARIES})
target_link_libraries (Smoothing RooTwoSidedCBShape)
target_link_libraries (Smoothing ${ROOT_LIBRARIES})
target_link_libraries (testSmooth RooTwoSidedCBShape)
target_link_libraries (testSmooth ${ROOT_LIBRARIES})
