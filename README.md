\# Red-Black Tree



Implementace červeno-černého binárního vyhledávacího

stromu v jazyce C++.



\## Vlastnosti



\- šablonová třída `RBT<T>`

\- vlastnictví uzlů pomocí `std::unique\_ptr`

\- vložení, hledání a mazání v čase `O(log n)`

\- validace vlastností červeno-černého stromu

\- výpis stromu pomocí `operator<<`



\## Použití



```cpp

RBT<int> tree;



tree.insert(10);

tree.insert(5);

tree.insert(15);



std::cout << tree << '\\n';



tree.erase(10);



if (tree.validate()) {

std::cout << "Strom je platný.\\n";

}
```


## Testovací sada

Testovací sada je implementována v souboru `main.cpp` pomocí makra `assert`.
### Testy operace `insert`

Testovací sada ověřuje zejména:

- vložení do prázdného stromu,
- vložení jednoho klíče,
- odmítnutí duplicitního klíče,
- levá–levá rotace,
- pravá–pravá rotace,
- levá–pravá dvojitá rotace,
- pravá–levá dvojitá rotace,
- přebarvování uzlů,
- vkládání seřazených hodnot,
- vkládání hodnot v opačném pořadí,
- vkládání velkého množství náhodně uspořádaných hodnot.
Testovací sada ověřuje zejména:
### Testy operace `erase`

- mazání z prázdného stromu,
- mazání neexistujícího klíče,
- odstranění jediného uzlu,
- odstranění červeného listu,
- odstranění černého listu,
- odstranění uzlu pouze s levým potomkem,
- odstranění uzlu pouze s pravým potomkem,
- odstranění kořene s jedním potomkem,
- odstranění uzlu se dvěma potomky, jehož následník je přímý pravý syn,
- odstranění uzlu se dvěma potomky, jehož následník leží hlouběji
  v pravém podstromu,
- mazání klíčů ve vzestupném pořadí,
- mazání klíčů v sestupném pořadí,
- mazání velkého množství klíčů v náhodném pořadí.
## Dokumentace

Dokumentace zdrojového kódu je vytvářena pomocí nástroje
[Doxygen](https://www.doxygen.nl/).

Hlavní stránka dokumentace je:

```text
docs/html/index.html
```