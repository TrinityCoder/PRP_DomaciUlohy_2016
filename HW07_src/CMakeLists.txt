# CMakeLists.txt s upresnujicim nastavenim pro ulohu HW07.

add_executable(HW07 main.c lock.c)

# Zkopirovani testovacich souboru do build/tests_HW07 slozky:
add_custom_command(TARGET HW07 PRE_BUILD
     COMMAND ${CMAKE_COMMAND} -E copy_directory
     ${CMAKE_CURRENT_SOURCE_DIR}/tests $<TARGET_FILE_DIR:HW07>/tests_HW07
)

# Specifikujeme, co a kam se bude kopirovat prikazem "make install".
install(TARGETS HW07
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib/static
	RESOURCE DESTINATION bin/tests_HW07
	)
