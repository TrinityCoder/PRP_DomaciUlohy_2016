## CVUT_FEL_PRP_DomaciUlohy_2016

Tento repozitář obsahuje implementace domácích úloh zadaných v předmětu
Procedurální programování v zimním semestru ak. roku 2016/2017 na FELu ČVUT.

Cílem je odprezentovat svá řešení úloh, použité algoritmy a nápady. Také věřím,
že vidět řešení může některým studentům pomoci s jeho pochopením.

### Jak úlohy zkompilovat a spustit?

Standardní způsob kompilace vypadá asi takto:

```bash
git clone https://github.com/TrinityCoder/PRP_DomaciUlohy_2016.git
cd PRP_DomaciUlohy_2016 && mkdir build && cd build
cmake ..
make
```

Nyní se binárky všech úloh nacházejí v podadresáři `bin`, tj. chcete-li např. spustit
úlohu HW00, můžete tak učinit příkazem

```bash
me@linux:~/PRP_DomaciUlohy_2016/build$ ./bin/HW00
Hello, PRP!
```

Testy se nachází v adresáři `bin/tests/<uloha>`, tj. např. pro HW06 lze testovací vstupy
najít v adresáři `bin/tests/HW06`. Zde jsou již dobrovolné a povinné testy dohromady
(rozlišit se dají pomocí písmena 'o' nebo 'm' v názvu jako 'optional' a 'mandatory'),
původní adresářová struktura testů je zachována v podsložce `tests` složek obsahujících
zdrojové kódy jednotlivých úloh.

### Licence

Zdrojové kódy uvolňuji do public domain; jejich použití za jakýmkoli účelem
je čistě na zodpovědnosti toho, kdo je použít chce.

### Co bude dál?

V současnosti pracuji na dodělání dalších úloh; dávat je sem budu trochu se zpožděním
oproti termínům v odevzdávacím systému. Máte-li jakýkoli nápad na vylepšení/pull request,
budu se těšit!

-- *Miroslav Mareš* (a. k. a. *TrinityCoder*)
