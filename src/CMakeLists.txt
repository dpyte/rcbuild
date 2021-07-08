
add_subdirectory("lib/toml11")

# Target build
set (Executable rcbuild)
# Sources
set (USOURCES
		main.cxx
		PathSC.cxx
		Path.cxx
		ApplicationVersion.hxx
		Details.hxx)

add_executable (${Executable} ${USOURCES})

# "We have a mole on our hands"
set_target_properties(rcbuild PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(rcbuild PUBLIC toml11)