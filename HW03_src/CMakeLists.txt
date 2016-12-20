# CMakeLists.txt s upresnujicim nastavenim pro ulohu HW03.

add_executable(HW03 main.c)

# Specifikujeme, co a kam se bude kopirovat prikazem "make install".
install(TARGETS HW03
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib/static)
