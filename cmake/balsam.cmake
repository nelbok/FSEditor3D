get_target_property(BALSAM_LOCATION Qt6::balsam IMPORTED_LOCATION)
if(WIN32)
	get_filename_component(FS_BALSAM ${BALSAM_LOCATION} NAME)
else()
	set(FS_BALSAM ${BALSAM_LOCATION})
endif()