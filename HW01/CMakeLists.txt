# CMakeLists.txt s upresnujicim nastavenim pro ulohu HW01.

add_executable(HW01 main.c)

# Specifikujeme, co a kam se bude kopirovat prikazem "make install".
install(TARGETS HW01
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib/static
	)
