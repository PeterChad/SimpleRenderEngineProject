file(GLOB_RECURSE Sources "*.h" "*.cpp") # will get all the .cpp and all the .h files in directory and subdirectories
add_executable(ExamGame ${Sources} "main.cpp")

target_link_libraries(ExamGame ${SGE_LIBRARIES})

# Copy project data to output path
file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


IF (WIN32)
	## Copy dll's to output path
	file(COPY ${SGE_LIBRARIES_SHARED} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
ENDIF(WIN32)
