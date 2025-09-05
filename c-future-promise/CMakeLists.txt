project(c-future-promise)

set(C_STANDARD 99)

# C examples use pthreads so cannot be compiled for Windows OS
if (UNIX)
	add_executable(c-future-promise main.c future-promise.c)

	find_package(Threads)

	target_link_libraries(c-future-promise
		PUBLIC Threads::Threads
	)

endif()
