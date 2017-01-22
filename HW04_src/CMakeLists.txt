# CMakeLists.txt s upresnujicim nastavenim pro ulohu HW04.

add_executable(HW04 main.c)

# Prilinkujeme matematickou knihovnu...
target_link_libraries(HW04 m)

# Zkopirovani testovacich souboru do build/tests_HW04 slozky:
add_custom_command(TARGET HW04 PRE_BUILD
     COMMAND ${CMAKE_COMMAND} -E copy_directory
     ${CMAKE_CURRENT_SOURCE_DIR}/tests $<TARGET_FILE_DIR:HW04>/tests_HW04
)

# Specifikujeme, co a kam se bude kopirovat prikazem "make install".
install(TARGETS HW04
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib/static)
