message(STATUS "Opting out assimp tests and shared libs...")

set(BUILD_SHARED_LIBS OFF)
set(ASSIMP_BUILD_TESTS OFF)
set(ASSIMP_INSTALL OFF)
set(ASSIMP_INSTALL_PDB OFF)

add_subdirectory(assimp/)
