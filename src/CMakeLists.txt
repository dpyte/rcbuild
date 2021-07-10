
set (toml11_BUILD_TEST ON CACHE BOOL "" FORCE)
add_subdirectory("lib/toml11")

# Target build
set (Executable rcb)
# Sources
set (USOURCES
		main.cxx
		RcGenSources.cxx
		PathSC.cxx
		Path.cxx
		ApplicationVersion.hxx
		Details.hxx RcValues.cxx RcValues.hxx)

add_executable (${Executable} ${USOURCES})

# "We have a mole on our hands"
set_target_properties(rcb PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(rcb PUBLIC toml11)