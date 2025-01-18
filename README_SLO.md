# Namizna aplikacija za sledenje opravilom ("TODO App")
Cilj projekta je bil razviti intuitivno in enostavno namizno aplikacijo za sledenje opravilom, ki omogoča učinkovito organizacijo in upravljanje osebnih ali profesionalnih nalog. Aplikacija je zasnovana za Linux okolje in omogoča osnovne funkcionalnosti, kot so dodajanje, urejanje, označevanje opravljenih opravil ter odstranjevanje nalog.

<p align="center">
  <img src="images/main_window.png">
</p>

##  Funkcionalnosti:
- Dodajanje opravil: Uporabnik lahko vnese nova opravila s kratkim opisom naloge.
- Urejanje opravil: Možnost naknadne spremembe opisa naloge.
- Označevanje opravljenih opravil: Uporabnik lahko označi opravila kot dokončana.
- Odstranjevanje opravil: Opravila, ki niso več potrebna, se lahko izbrišejo.

## Tehnologije:
- C++
- Linux
- CMake
- GTK4

## Možne nadgradnje
- Vpeljava prioritete opravil:
    - Dodajanje možnosti nastavitve prioritet (nizka, srednja, visoka) za vsako nalogo.
    - Barvno označevanje in sortiranje opravil glede na njihovo prioriteto.
- Časovne omejitve opravil:
    - Omogočanje nastavitve roka za dokončanje posameznih opravil.
    - Vizualna opozorila ali opomniki za naloge, katerih rok se bliža ali je že potekel.
- Zgodovina opravil:
    - Evidenca vseh opravljenih ali odstranjenih opravil za kasnejši pregled.
    - Možnost ponovnega aktiviranja izbrisanih nalog.
- Statistika opravil:
    - Pregled uspešnosti uporabnika (opravljena, neopravljena in zamujena opravila).
    - Grafični prikaz napredka skozi čas.

## Ključne prednosti aplikacije
- Preprostost aplikacije: preprost GUI, logičen še za tako laike uporabnike
- Lahka aplikacija: zaradi implementacije le najbolj osnovnih funkcji je aplikacija zelo lahka in deluje tudi na najšibkejših sistemih
- Razvita za Linux

## Images
<p align="center">
  <img src="images/main_window.png">
  <br>
  <br>
  <br>
  <img src="images/add_task_window.png">
</p>

## Usage
### Linux
```sh
./configure.sh # updates the CMAKE configuration
./build.sh # builds all the files
./run.sh # runs the program
```

## Sources
[GTK Getting started](https://www.gtk.org/docs/getting-started/hello-world/) <br>
[GTK4 Tutorial - github](https://github.com/ToshioCP/Gtk4-tutorial) <br>
GTK Documentation <br>
