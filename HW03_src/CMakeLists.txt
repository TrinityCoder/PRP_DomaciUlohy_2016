# CMakeLists.txt s upresnujicim nastavenim pro ulohu HW03.

add_executable(HW03 main.c)

# Zkopirovani testovacich souboru do build/tests_HW03 slozky:
add_custom_command(TARGET HW03 PRE_BUILD
     COMMAND ${CMAKE_COMMAND} -E copy_directory
     ${CMAKE_CURRENT_SOURCE_DIR}/tests $<TARGET_FILE_DIR:HW03>/tests_HW03
)

# Specifikujeme, co a kam se bude kopirovat prikazem "make install".
install(TARGETS HW03
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib/static)
