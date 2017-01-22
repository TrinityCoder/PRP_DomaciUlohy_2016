# CMakeLists.txt s upresnujicim nastavenim pro ulohu HW04b.

add_executable(HW04b main.c)

# Prilinkujeme matematickou knihovnu...
target_link_libraries(HW04b m)

# Zkopirovani testovacich souboru do build/tests_HW04b slozky:
add_custom_command(TARGET HW04b PRE_BUILD
     COMMAND ${CMAKE_COMMAND} -E copy_directory
     ${CMAKE_CURRENT_SOURCE_DIR}/tests $<TARGET_FILE_DIR:HW04b>/tests_HW04b
)

# Specifikujeme, co a kam se bude kopirovat prikazem "make install".
install(TARGETS HW04b
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib/static)
