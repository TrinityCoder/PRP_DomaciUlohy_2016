# CMakeLists.txt s upresnujicim nastavenim pro ulohu HW04b.

add_executable(HW04b main.c)

# Prilinkujeme matematickou knihovnu...
target_link_libraries(HW04b m)

# Specifikujeme, co a kam se bude kopirovat prikazem "make install".
install(TARGETS HW04b
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib/static)
