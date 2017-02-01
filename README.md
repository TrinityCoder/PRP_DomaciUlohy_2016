## CVUT_FEL_PRP_DomaciUlohy_2016

Tento repozitář obsahuje implementace domácích úloh zadaných v předmětu
Procedurální programování v zimním semestru ak. roku 2016/2017 na FELu ČVUT.

Cílem je odprezentovat svá řešení úloh, použité algoritmy a nápady. Také věřím,
že vidět řešení může některým studentům pomoci s jeho pochopením.

### Jak úlohy zkompilovat a spustit?

Standardní způsob kompilace vypadá asi takto:

```bash
me@linux:~$ git clone https://github.com/TrinityCoder/PRP_DomaciUlohy_2016.git
me@linux:~$ cd PRP_DomaciUlohy_2016 && mkdir build && cd build
me@linux:~/PRP_DomaciUlohy_2016/build$ cmake .. && make
```

Binárky všech úloh se nacházejí v aktuálním adresáři, tj. chcete-li např. spustit
úlohu HW00, můžete tak učinit příkazem

```bash
me@linux:~/PRP_DomaciUlohy_2016/build$ ./HW00
Hello, PRP!
me@linux:~/PRP_DomaciUlohy_2016/build$
```

Testy se nachází v adresáři `tests_<uloha>/`, tj. např. pro HW06 lze testovací vstupy
najít v adresáři `tests_HW06`.

### Licence

Zdrojové kódy uvolňuji do public domain; jejich použití za jakýmkoli účelem
je čistě na zodpovědnosti toho, kdo je použít chce.

### Co bude dál?

V současnosti jsem již veškeré práci na tomto repozitáři ukončil. Pokud zde ještě
přibude nějaký commit, tak spíš už jen detailního rázu. Všechny úlohy
(kromě bonusové úlohy HW05b) byly implementovány.

-- *Miroslav Mareš* (a. k. a. *TrinityCoder*)
