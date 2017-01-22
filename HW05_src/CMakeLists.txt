# CMakeLists.txt s upresnujicim nastavenim pro ulohu HW05.

add_executable(HW05 main.c)

# Zkopirovani testovacich souboru do build/tests_HW05 slozky:
add_custom_command(TARGET HW05 PRE_BUILD
     COMMAND ${CMAKE_COMMAND} -E copy_directory
     ${CMAKE_CURRENT_SOURCE_DIR}/tests $<TARGET_FILE_DIR:HW05>/tests_HW05
)

# Specifikujeme, co a kam se bude kopirovat prikazem "make install".
install(TARGETS HW05
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib/static)
