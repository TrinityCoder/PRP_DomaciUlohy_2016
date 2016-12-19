# CMakeLists.txt s upresnujicim nastavenim pro ulohu HW02.

add_executable(HW02 main.c)

# Specifikujeme, co a kam se bude kopirovat prikazem "make install".
install(TARGETS HW02
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib/static
	)
