
# 2021y-02m-12d. WorkSpace project.
################################################################################
################################################################################

set(gDEBUG "$ENV{eDEBUG}")
cmake_minimum_required(VERSION 3.1)

include("${CMAKE_CURRENT_LIST_DIR}/setup.cmake")
cmake_scenario("minimalist")

project(${gNAME_PROJECT})

################################################################################
################################################################################

#--- tools-match
make_target()

make_target(
    PATH_TO_SOURCES "test"
#    INCLUDES "${gDIR_SOURCE}/include"
#    DEPENDENCIES "tools-match" 

    #--- automatically link with 'mygtest', 'gmock', or 'gtest' 
    #--- depending on which libraries are available
)

################################################################################
################################################################################

