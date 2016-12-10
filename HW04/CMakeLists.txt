# CMakeLists.txt s upresnujicim nastavenim pro ulohu HW04.

add_executable(HW04 main.c)

# Prilinkujeme matematickou knihovnu...
target_link_libraries(HW04 m)

# Specifikujeme, co a kam se bude kopirovat prikazem "make install".
install(TARGETS HW04
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib/static)
