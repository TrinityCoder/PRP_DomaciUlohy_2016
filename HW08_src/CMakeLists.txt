# CMakeLists.txt s upresnujicim nastavenim pro ulohu HW08.

add_executable(HW08 main.c queue.c)

# Zkopirovani testovacich souboru do build/tests_HW08 slozky:
add_custom_command(TARGET HW08 PRE_BUILD
     COMMAND ${CMAKE_COMMAND} -E copy_directory
     ${CMAKE_CURRENT_SOURCE_DIR}/tests $<TARGET_FILE_DIR:HW08>/tests_HW08
)

# "make zip" zabali queue.h a queue.c do souboru HW08_upload.zip,
# tj. pripravi ZIP soubor k uploadu do hodnoticiho systemu.
add_custom_target(zip_HW08
     COMMAND ${CMAKE_COMMAND} -E tar "cfv" "HW08_upload.zip" --format=zip
               "${CMAKE_CURRENT_SOURCE_DIR}/queue.c"
               "${CMAKE_CURRENT_SOURCE_DIR}/queue.h"
     WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
     DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/queue.c"
             "${CMAKE_CURRENT_SOURCE_DIR}/queue.h"
)

# Specifikujeme, co a kam se bude kopirovat prikazem "make install".
install(TARGETS HW08
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib/static
	)
