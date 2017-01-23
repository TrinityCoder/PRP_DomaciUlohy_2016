# CMakeLists.txt s upresnujicim nastavenim pro ulohu HW09.

# Z nasi implementace grafu udelame statickou knihovnu a tu pak
# prilinkujeme k obema testovacim programum (bin2txt a txt2bin).

add_library(HW09_libgraph STATIC graph.c)

add_executable(HW09_bin2txt bin2txt.c)
add_executable(HW09_txt2bin txt2bin.c)

target_link_libraries(HW09_bin2txt PUBLIC HW09_libgraph)
target_link_libraries(HW09_txt2bin PUBLIC HW09_libgraph)

# Zkopirovani testovacich souboru do build/tests_HW09 slozky:
add_custom_command(TARGET HW09_libgraph PRE_BUILD
     COMMAND ${CMAKE_COMMAND} -E copy_directory
     ${CMAKE_CURRENT_SOURCE_DIR}/tests $<TARGET_FILE_DIR:HW09_libgraph>/tests_HW09
)

# "make zip" zabali graph.h a graph.c do souboru HW09_upload.zip,
# tj. pripravi ZIP soubor k uploadu do hodnoticiho systemu.
add_custom_target(zip_HW09
     COMMAND ${CMAKE_COMMAND} -E tar "cfv" "HW09_upload.zip" --format=zip
     WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
     SOURCES   "${CMAKE_CURRENT_SOURCE_DIR}/graph.c"
               "${CMAKE_CURRENT_SOURCE_DIR}/graph.h"
)

# Specifikujeme, co a kam se bude kopirovat prikazem "make install".
install(TARGETS HW09_libgraph HW09_bin2txt HW09_txt2bin
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib/static
	)
