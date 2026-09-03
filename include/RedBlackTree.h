#ifndef RBT_H
#define RBT_H

#include <cstddef>
#include <memory>
#include <ostream>

/**
* @brief barva uzlu
*/
enum class color
{
	Red,
	Black
};
/**
* @brief datový objekt uzlu pro červený černý strom
*
* obsahuje samotný klíč, barvu daněho uzlu (color c) a dva unique pointery na pravého a levého potomka(	std::unique_ptr<node<T>> left, std::unique_ptr<node<T>> right)
* a klasický pointer ukazující na rodiče
*/
template <typename T>
struct node
{
	T key;
	color c;

	std::unique_ptr<node<T>> left;
	std::unique_ptr<node<T>> right;

	node<T>* parent;

    /**
     * @brief Vytvoří nový červený uzel.
     *
     * @param key Hodnota uložená v uzlu.
     */

	explicit node(const T& key);
};

/**
 * @brief Červeno-černý binární vyhledávací strom.
 *
 * Strom podporuje hledání, vložení a odstranění v nejhorším
 * případě v čase O(log n).
 *
 * Obsahuje 2 Data membery 	std::unique_ptr<node<T>> root; což je kořen daného BST
 *	 a std::size_t tree_size; který udavá počet uzlů v stromě
 *
 * @tparam T Typ ukládaných klíčů.
 *
 * @note Typ T musí podporovat porovnání pomocí operátoru <.
 */

template <typename T>
class RBT;

/**
 * @brief Vypíše strom do výstupního proudu.
 *
 * Strom je vypsán naležato. Praví potomci jsou zobrazeni
 * nad rodičem a leví potomci pod rodičem.
 *
 * @tparam T Typ klíčů stromu.
 * @param output Výstupní proud.
 * @param tree Strom, který má být vypsán.
 * @return Reference na výstupní proud.
 */
template <typename T>
std::ostream& operator<<(
	std::ostream& output,
	const RBT<T>& tree
);

template <typename T>
class RBT
{
public:
    /**
     * @brief No args konstruktor-> vytvoří prázdný strom.
     */
	RBT();
	~RBT() = default;
    /**
    * @brief copy Konstruktor není povolen deep copy není naimplementováno
    */
	RBT(const RBT&) = delete;
    /**
    * @brief copy assigment operator není povolen deep copy není naimplementováno
    */
	RBT& operator=(const RBT&) = delete;
	/**
    * @brief Move konstruktor pro přesunutí stromu
    */
	RBT(RBT&&) noexcept = default;
	/**
    * @brief Move assigment operator pro přesunutí stromu
    */
	RBT& operator=(RBT&&) noexcept = default;

    /**
     * @brief Vloží nový klíč do stromu.
     *
     * Po vložení obnoví vlastnosti červeno-černého stromu pomocí helper funkce insert fixup
     *
     * @param key Klíč, který má být vložen.
     * @return true Pokud byl klíč vložen.
     * @return false Pokud už klíč ve stromu existuje.
     *
     * @complexity O(log n).
     */
	bool insert(const T& key);
	/**
     * @brief Zjistí, zda strom obsahuje daný klíč.
     *
     * @param key Hledaný klíč.
     * @return true Pokud klíč existuje.
     * @return false Pokud klíč neexistuje.
     *
     * @complexity O(log n).
     */
	bool find(const T& key) const;
	bool erase(const T& key);
   /**
     * @brief Zjistí, zda je strom prázdný.
     *
     * @return true Pokud strom neobsahuje žádný uzel.
     */
	bool empty() const;
    /**
    * @brief Vrátí počet klíčů uložených ve stromu.
    * @return Počet uzlů stromu.
    * @complexity O(1).
    */
	std::size_t size() const;
	/**
     * @brief Odstraní všechny uzly ze stromu.
     */
	void clear();
	/**
     * @brief Ověří všechny invarianty stromu.
     *
     * Kontroluje:
     * - uspořádání binárního vyhledávacího stromu,
     * - černou barvu kořene,
     * - zákaz dvou sousedních červených uzlů,
     * - shodnou černou výšku všech cest,
     * - správnost ukazatelů na rodiče,
     * - shodu skutečného počtu uzlů s tree_size.
     *
     * @return true Pokud je struktura stromu platná.
     */
	bool validate() const;
    friend std::ostream& operator<< <>(std::ostream& output,const RBT<T>& tree);
    /**
    * @brief Vrátí výšku stromu.
    * @return Počet uzlů na nejdelší cestě od kořene k listu.
    * @complexity O(n).
    */
    std::size_t height() const;

private:
	std::unique_ptr<node<T>> root;
	std::size_t tree_size;
	node<T>* find_key(node<T>* n, const T& key) const;
	node<T>* minimum(node<T>* n) const;
   /**
   * @brief Obnoví RB vlastnosti po vložení uzlu.
   * @param n Nově vložený uzel.
   */
	void insert_fixup(node<T>* n);
	/**
    * @brief Obnoví RB vlastnosti po odstranění černého uzlu.
    *
    * @param n Uzel nahrazující odstraněný uzel; může být nullptr.
    * @param parent Rodič uzlu n nebo prázdné pozice.
    */
	void delete_fixup(node<T>* n, node<T>* parent);
    /**
    * @brief Provede levou rotaci kolem uzlu.
    * @param n Kořen rotovaného podstromu.
    */
	void rotate_left(node<T>* n);
	void rotate_right(node<T>* n);
	std::unique_ptr<node<T>>* owning_pointer(node<T>* n);
    color get_color(const node<T>* n) const;
	bool is_red(const node<T>* n) const;
	bool is_black(const node<T>* n) const;
	void print_subtree(
		const node<T>* n,
		std::ostream& output,
		std::size_t depth
	) const;
	bool validate_bst(const node<T>* n) const;
	bool validate_red_nodes(const node<T>* n) const;
	bool validate_parent_pointers(const node<T>* n) const;
	int black_height(const node<T>* n) const;
	std::size_t height_subtree(const node<T>* n) const;
};

#include "RedBlackTree.tpp"

#endif
