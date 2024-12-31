if(EXISTS "${CMAKE_BINARY_DIR}/BuildManagement/Build_Recursion_Guard.txt")
    file(REMOVE "${CMAKE_BINARY_DIR}/BuildManagement/Build_Recursion_Guard.txt")
else()
	if(EXISTS "${CMAKE_BINARY_DIR}/BuildManagement/Force_Build_Finished.txt")
		file(REMOVE "${CMAKE_BINARY_DIR}/BuildManagement/Force_Build_Finished.txt")
	endif()

    file(TOUCH "${CMAKE_BINARY_DIR}/BuildManagement/Build_Recursion_Guard.txt")

	execute_process(
        COMMAND ${CMAKE_COMMAND} --build "${CMAKE_BINARY_DIR}" --target PLACE_HOLDER --config Release
        RESULT_VARIABLE BuildResult
        OUTPUT_VARIABLE BuildOutput
    )
	
	if(BuildResult)
        message("Release Build failed with error ${BuildResult}: ${BuildOutput}")
    else()
        message("Release Build succeeded: ${BuildOutput}")
		file(TOUCH "${CMAKE_BINARY_DIR}/BuildManagement/Force_Build_Finished.txt")
    endif()
endif()