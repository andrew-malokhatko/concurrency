project(c-data-race)

set(C_STANDARD 99)

# C examples use pthreads so cannot be compiled for Windows OS
if (UNIX)
	add_executable(c-data-race main.c)

	find_package(Threads)

	target_link_libraries(c-data-race
		PUBLIC Threads::Threads
	)

endif()