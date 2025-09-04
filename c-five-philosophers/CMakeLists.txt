project(c-five-philosophers)

set(C_STANDARD 99)

# C examples use pthreads so cannot be compiled for Windows OS
if (UNIX)
	add_executable(c-five-philosophers main.c)

	find_package(Threads)

	target_link_libraries(c-five-philosophers
		PUBLIC Threads::Threads
	)

endif()
