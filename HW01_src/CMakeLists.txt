# CMakeLists.txt s upresnujicim nastavenim pro ulohu HW01.

add_executable(HW01 main.c)

# Zkopirovani testovacich souboru do build/tests_HW01 slozky:
add_custom_command(TARGET HW01 PRE_BUILD
     COMMAND ${CMAKE_COMMAND} -E copy_directory
     ${CMAKE_CURRENT_SOURCE_DIR}/tests $<TARGET_FILE_DIR:HW01>/tests_HW01
)

# Specifikujeme, co a kam se bude kopirovat prikazem "make install".
install(TARGETS HW01
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib/static
	)
