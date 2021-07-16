
add_subdirectory("lib/toml11")
add_subdirectory("lib/libgit2")

# Target build
set (Executable rcb)
# Sources
set (USOURCES
	main.cxx
	Path.cxx
	PathSC.cxx
	RcAsyncInstall.cxx
	RcError.cxx
	RcFetchSrc.cxx
	RcGenSources.cxx
	RcValues.cxx
	ApplicationVersion.hxx
	Details.hxx )

add_executable (${Executable} ${USOURCES})

# "We have a mole on our hands"
set_target_properties (rcb PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries (rcb PUBLIC toml11)
target_link_libraries (rcb PUBLIC git2)
target_link_libraries (rcb PUBLIC pthread)
