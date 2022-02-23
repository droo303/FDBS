# FDBS

Repository for FDBS tasks.

### Úkol 0.
Při testu pro srovnání rychlosti přístupu (čtení, zápis) do paměti se potvrdilo, že sekvenční přístup je rychlejší. V tomto testu bylo vykonáno 10 milionu přístupů pro každou operaci, kde sekvenční přístup proběhl v 5 až 10 krát kratším čase.

### Úkol 1.
Do tabulky s řádkovým uložením bylo vloženo 10 milionu záznamů. Při sekvenčním průchodu byla naměřena propustnost ~150 mil. op/s. pro vkládání a ~160 mil. op/s pro čtení.

Časová složitost operace Find (hledání záznamu dle klíče) je pro nesetřízená data vzhledem k  velikosti tabulky lineární. Pro test nevhodnosti lineárního hledání bylo v tabulce opakovaně hledáno 10 000 náhodných klíčů. V tomto případě propustnost dosahovala pouze okolo 8000 op/s.

### Úkol 2.
