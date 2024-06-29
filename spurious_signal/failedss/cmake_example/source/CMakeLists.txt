cmake_minimum_required( VERSION 3.6 FATAL_ERROR )

set(CMAKE_CXX_STANDARD 17)

project (SPURIOUS_SIGNAL)

# setup ROOT
find_package( ROOT REQUIRED COMPONENTS Core RooFitCore RooFit RooStats HistFactory TMVA RIO)

# include path
include_directories("${PROJECT_BINARY_DIR}")
include_directories ("${ROOT_INCLUDE_DIRS}")

# sub-directory
add_subdirectory (Spurious_Signal)
