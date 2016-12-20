# CMakeLists.txt s upresnujicim nastavenim pro ulohu HW00.

add_executable(HW00 main.c)

# Specifikujeme, co a kam se bude kopirovat prikazem "make install".
install(TARGETS HW00
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib/static)
