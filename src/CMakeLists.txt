

# Target build
set (Executable rcbuild)

add_library (toml99
	STATIC
	lib/tomlc99/toml.c)

# Sources
set (USOURCES
	main.c
	mem.c
	path.c
	path_sc.c
	process.c
	details.h
	ApplicationVersion.h)

add_executable (${Executable} ${USOURCES})

# "We have a mole on our hands"
target_link_libraries (${Executable} PUBLIC toml99)
target_include_directories (${Executable} PUBLIC lib/tomlc99)
set_target_properties(rcbuild PROPERTIES LINKER_LANGUAGE C)
