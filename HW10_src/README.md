## HW10 - vysvětlení

Cílem tohoto úkolu bylo:

1. Najít a opravit kód ve funkci `pq_update` (je umístěna v souboru `pq_heap-no_update.c`),
který způsobuje, že je mnohem pomalejší, než by správně měla být.
2. Implementovat funkce `dijkstra_set_graph` a `dijkstra_get_solution` v souboru
`dijkstra.c` na základě jejich signatur definovaných v `dijkstra.h`.

Úkol měl tedy dvě části - jednak optimalizovat funkci `pq_update` a jednak
implementovat funkce, které umožní snadno spouštět Dijkstrův algoritmus v případě,
že zadanou množinu hran jako pole uspořádaných trojic (tj. `int hrany[][3]`).
Funkce 2) jsou totiž jakési paralely k funkcím `dijkstra_load_graph` a `dijkstra_save_path`,
ale zatímco tyto dvě funkce pracují s načítáním grafu ze souboru,
funkce 2) mají pracovat s polem hran grafu, které nemáme uložené v žádném
souboru, ale přímo načtené v nějaké proměnné.

### Tedy co je jinak oproti oficiálním zdrojákům z CourseWare?

Hlavičkové i zdrojové soubory v této složce a soubory z lekce 11 (viz
http://cw.fel.cvut.cz/wiki/courses/b0b36prp/hw/hw10) jsou ve skutečnosti stejné,
až na implementace tří funkcí:

* `pq_update` v suboru `pq_heap-no_update.c`,
* `dijkstra_set_graph` v souboru `dijkstra.c`
* `dijkstra_get_solution` v souboru `dijkstra.c`

Funkce `pq_update` je jen trochu pozměněná na konci, zatímco
další dvě funkce jsou inspirovány jejich "souborovými protiklady".

Všimněte si, že funkce
* `dijkstra_set_graph` a `dijkstra_load_graph`
* `dijkstra_save_path` a `dijkstra_get_solution`

Jsou téměř úplně stejné. Řešení úlohy tak spočívalo jen v nutnosti uvědomit si,
že ony dvě nové funkce budou téměř stejné (neboť počítají stejnou věc), jako nějaké
dvě již implementované, a drobné rozdíly správně pozměnit.
