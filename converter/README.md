# Převodník dokumentů

## Specifikace

Program slouží ke konverzi HTML -> MarkDown nebo MarkDown -> HTML. Konvertovat lze jak samotný dokument, tak i celou složku (i rekurzivně).

## Funkce

Program podporuje tato formátování:
* Odstavce textu (text, tucne, kurziva)
* Nadpisy
* Číslované a odrážkové seznamy
* Tabulky
* Odkazy
* Obrázky

V případě, že konvertovný dokument obsahuje nějaké formátování, které není podporováno je vypsáno varování, na kterém řádku nastal problém a toto formátování se ponechá beze změny.



Překonvertované soubory budou uloženy do stejné složky a se stejným názvem jako původní soubory akorát s příponou "-converted".

## Ovládání

Program se spouští a ovláda přes terminál. K dispozici je jednoduchý našeptávač příkazu s vysvětlivkami.
Program podporuje tyto příkazy:
* HTML - konverze HTML dokumentu na MarkDown dokument
* MD - konverze MarkDown dokumentu na HTML dokument
* FILE - konverze jednoho nebo více souborů
* DIR - konverze složky
* RDIR - konverze složky rekurzivně
