# CMakeLists.txt s upresnujicim nastavenim pro ulohu HW02.

add_executable(HW02 main.c)

# Zkopirovani testovacich souboru do build/tests_HW02 slozky:
add_custom_command(TARGET HW02 PRE_BUILD
     COMMAND ${CMAKE_COMMAND} -E copy_directory
     ${CMAKE_CURRENT_SOURCE_DIR}/tests $<TARGET_FILE_DIR:HW02>/tests_HW02
)

# Specifikujeme, co a kam se bude kopirovat prikazem "make install".
install(TARGETS HW02
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib/static
	)
