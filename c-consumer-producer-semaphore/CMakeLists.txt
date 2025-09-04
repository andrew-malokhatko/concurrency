project(c-consumer-producer-semaphore)

set(C_STANDARD 99)

# C examples use pthreads so cannot be compiled for Windows OS
if (UNIX)
	add_executable(c-consumer-producer-semaphore main.c data.c)

	find_package(Threads)

	target_link_libraries(c-consumer-producer-semaphore
		PUBLIC Threads::Threads
	)

endif()