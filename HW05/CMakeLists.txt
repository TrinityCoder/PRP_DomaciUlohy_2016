# CMakeLists.txt s upresnujicim nastavenim pro ulohu HW05.

add_executable(HW05 main.c)

# Specifikujeme, co a kam se bude kopirovat prikazem "make install".
install(TARGETS HW05
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib/static)
