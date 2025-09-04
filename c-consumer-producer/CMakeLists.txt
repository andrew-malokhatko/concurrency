project(c-consumer-producer)

set(C_STANDARD 99)

# C examples use pthreads so cannot be compiled for Windows OS
if (UNIX)
	add_executable(main.c)

	find_package(Threads)

	target_link_libraries(c-consumer-producer
		PRIVATE Threads::Threads
	)

endif()