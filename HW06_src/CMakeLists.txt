# CMakeLists.txt s upresnujicim nastavenim pro ulohu HW06.

add_executable(HW06 main.c)

# Zkopirovani testovacich souboru do build/tests_HW06 slozky:
add_custom_command(TARGET HW06 PRE_BUILD
     COMMAND ${CMAKE_COMMAND} -E copy_directory
     ${CMAKE_CURRENT_SOURCE_DIR}/tests $<TARGET_FILE_DIR:HW06>/tests_HW06
)

# Specifikujeme, co a kam se bude kopirovat prikazem "make install".
install(TARGETS HW06
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib/static
	)
