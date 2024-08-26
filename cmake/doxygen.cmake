# check if Doxygen is installed
find_package(Doxygen)
if(DOXYGEN_FOUND)
	set(DOXYGEN_PROJECT_NAME ${FS_EDITOR})
	set(DOXYGEN_PROJECT_LOGO ${CMAKE_CURRENT_SOURCE_DIR}/editor/resources/icons/logo.png)
	set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/docs)
	set(DOXYGEN_USE_MDFILE_AS_MAINPAGE ${CMAKE_CURRENT_SOURCE_DIR}/README.md)
	set(DOXYGEN_WARN_IF_UNDOCUMENTED NO)
	doxygen_add_docs(
		docs
		${CMAKE_CURRENT_SOURCE_DIR}/README.md
		${CMAKE_CURRENT_SOURCE_DIR}/data/include/
	)
else()
  message("Doxygen need to be installed to generate the doxygen documentation")
endif()