### Sekvenční vs Náhodný přístup
Při testu s 10^7 přístupy byl sekvenční přístup 5-10 krát rychlejší než náhodný.
Tato vlastnost je způsobena cachováním procesoru.
### HeapTable
Tabulka s řádkovým uložením:
Pro 10^7 záznamů naměřena propustnost:
* Vkládání : ~9 mil. op/s
* Čtení:     ~10 mil. op/s
* Hledání:   ~200 op/s 

### HashTable
Tabulka s uložením dat v hashovací tabulce
Pro 10^7 záznamů naměřena propustnost:

* Vkládání: ~2 mil. op/s.
* Hledání: ~6 mil. op/s.

Za cenu pomalejšího vkládání dosahuje použití hashovací tabulky výrazně rychlejšího hledání.

Dalšího zrychlení lze dosáhnout odstraněním dynamické alokace paměti nebo odstranění rekurzivního použití metod.