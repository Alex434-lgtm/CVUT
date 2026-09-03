#include <stack>

template <typename T>
node<T>::node(const T& key)
	: key(key),
	  c(color::Red),
	  left(nullptr),
	  right(nullptr),
	  parent(nullptr)
{
}

template <typename T>
RBT<T>::RBT()
	: root(nullptr),
	  tree_size(0)
{
}
template <typename T>
node<T>* RBT<T>::find_key(node<T>* n, const T& key) const{
    node<T>* current = n;

    while (current != nullptr) {
        if (key == current->key) {
            return current;
        }

        if (key < current->key) {
            current = current->left.get();
        } else {
            current = current->right.get();
        }
    }

    return nullptr;
}
 /**
 * @brief Odstraní zadaný klíč z červeno-černého stromu.
 *
 * @details
 * proměné které figurují v implementaci:
 *-     current – uzel odpovídající mazanému klíči,
 *-     x – uzel, který nahradil fyzicky odstraněný uzel,
 *-     parent – rodič uzlu x, hlavně když je x == nullptr,
 *-     c – původní barva fyzicky odstraněného uzlu,
 *-     temp – dočasný unique_ptr, který uchovává podstrom nebo následníka,
 *-     y – inorder následník při mazání uzlu se dvěma potomky.
 * Popis průběhu funkce:
 * Funkce nejprve najde uzel odpovídající zadanému klíči.
 * Potom provede jednu ze tří variant běžného BST mazání:
 *
 * - uzel nemá levého potomka,
 * - uzel nemá pravého potomka,
 * - uzel má oba potomky.
 *
 * Při dvou potomcích je použit inorder následník, tedy nejmenší
 * uzel v pravém podstromu. Pokud byl fyzicky odstraněný uzel
 * černý, je následně zavolána funkce delete_fixup().
 *
 * @par Průběh funkce
 * 1. Najde uzel s požadovaným klíčem.
 * 2. Určí jeho potomky a původní barvu.
 * 3. Přesune vlastnictví podstromů pomocí std::move.
 * 4. Opraví nevlastnící ukazatele parent.
 * 5. Sníží tree_size.
 * 6. V případě odstranění černého uzlu zavolá delete_fixup().
 *
 * @param key Klíč, který má být ze stromu odstraněn.
 *
 * @retval true Klíč byl nalezen a odstraněn.
 * @retval false Klíč se ve stromu nenacházel.
 *
 * @par Časová složitost
 * O(log n) pro platný červeno-černý strom.
 */
template <typename T>
bool RBT<T>::erase(const T& key){
node<T>* current=this->find_key(this->root.get(),key);
node<T>* x=nullptr;
node<T>* parent=nullptr;
if(current==nullptr){
    return false;
}else{
    color c=current->c;
if (current->left == nullptr) {

    if (current == this->root.get()) {
        this->root = std::move(current->right);
        x = this->root.get();
        parent = nullptr;

        if (x != nullptr) {
            x->parent = nullptr;
        }
    }
    else {
        parent = current->parent;
        x = current->right.get();

        if (x == nullptr) {
            if (current == parent->left.get()) {
                parent->left.reset();
            }
            else {
                parent->right.reset();
            }
        }
        else {
            x->parent = parent;

            if (current == parent->left.get()) {
                parent->left = std::move(current->right);
            }
            else {
                parent->right = std::move(current->right);
            }
        }
    }
}
else if (current->right == nullptr) {

    if (current == this->root.get()) {
        this->root = std::move(current->left);
        x = this->root.get();
        parent = nullptr;

        if (x != nullptr) {
            x->parent = nullptr;
        }
    }
    else {
        parent = current->parent;
        x = current->left.get();

        if (x == nullptr) {
            if (current == parent->left.get()) {
                parent->left.reset();
            }
            else {
                parent->right.reset();
            }
        }
        else {
            x->parent = parent;

            if (current == parent->left.get()) {
                parent->left = std::move(current->left);
            }
            else {
                parent->right = std::move(current->left);
            }
        }
    }
}
else{
    if (current->right->left == nullptr) {
    c = current->right->c;
    current->right->c = current->c;
    x = current->right->right.get();
    std::unique_ptr<node<T>> temp = std::move(current->left);
    if (current == this->root.get()) {
        this->root = std::move(current->right);
        this->root->parent = nullptr;
        this->root->left = std::move(temp);
        if (this->root->left != nullptr) {
            this->root->left->parent = this->root.get();
        }
        parent = this->root.get();
    }
    else {
        parent = current->parent;
        if (current == parent->left.get()) {
            parent->left = std::move(current->right);
            parent->left->parent = parent;
            parent->left->left = std::move(temp);
            if (parent->left->left != nullptr) {
                parent->left->left->parent =
                    parent->left.get();
            }
            parent = parent->left.get();
        }
        else {
            parent->right = std::move(current->right);
            parent->right->parent = parent;
            parent->right->left = std::move(temp);
            if (parent->right->left != nullptr) {
                parent->right->left->parent =
                    parent->right.get();
            }
            parent = parent->right.get();
        }
    }
}
    else {
    node<T>* y = current->right.get();

    while (y->left != nullptr) {
        y = y->left.get();
    }
    c = y->c;
    parent = y->parent;
    node<T>* current_parent = current->parent;
    std::unique_ptr<node<T>> temp =std::move(parent->left);
    parent->left = std::move(temp->right);
    x = parent->left.get();
    if (x != nullptr) {
        x->parent = parent;
    }

    temp->left = std::move(current->left);
    if (temp->left != nullptr) {
        temp->left->parent = temp.get();
    }
    temp->right = std::move(current->right);
    if (temp->right != nullptr) {
        temp->right->parent = temp.get();
    }
    temp->c = current->c;
    temp->parent = current_parent;
    if (current == this->root.get()) {
        this->root = std::move(temp);
    }
    else if (current == current_parent->left.get()) {
        current_parent->left = std::move(temp);
    }
    else {
        current_parent->right = std::move(temp);
    }
}
}
    --this->tree_size;

	if (c == color::Black) {
		delete_fixup(x, parent);
	}

	return true;
}
}
template <typename T>
bool RBT<T>::empty() const
{
	return this->root == nullptr;
}
/**
 * @brief Vyhledá zadaný klíč v červeno-černém stromu.
 *
 * @details
 * Funkce začíná v kořeni stromu a postupně prochází pouze jednu
 * větev binárního vyhledávacího stromu.
 *
 * @par Průběh funkce
 * 1. Nastaví ukazatel current na kořen stromu.
 * 2. Porovná hledaný klíč s klíčem aktuálního uzlu.
 * 3. Pokud jsou klíče stejné, vrátí true.
 * 4. Pokud je hledaný klíč menší, pokračuje do levého podstromu.
 * 5. Pokud je hledaný klíč větší, pokračuje do pravého podstromu.
 * 6. Jestliže narazí na nullptr, klíč ve stromu neexistuje.
 *
 * @param key Klíč, který má být ve stromu vyhledán.
 *
 * @retval true Klíč se ve stromu nachází.
 * @retval false Klíč se ve stromu nenachází.
 *
 * @par Časová složitost
 * O(h), kde h je výška stromu. Pro platný červeno-černý strom
 * je výška O(log n).
 */
template<typename T>
bool RBT<T>::find(const T& key) const
{
    node<T>* current = this->root.get();

    while (current != nullptr) {
        if (key == current->key) {
            return true;
        }

        if (key < current->key) {
            current = current->left.get();
        } else {
            current = current->right.get();
        }
    }

    return false;
}
/**
 * @brief Ověří všechny důležité invarianty stromu.
 *
 * @details
 * Funkce postupně provede několik nezávislých validačních kontrol.
 * Jakmile jedna z nich selže, okamžitě vrátí false.
 *
 * @par Kontrolované vlastnosti
 * - prázdný strom musí mít tree_size rovné nule,
 * - kořen nesmí mít rodiče,
 * - kořen musí být černý,
 * - klíče musí splňovat pravidla binárního vyhledávacího stromu,
 * - červený uzel nesmí mít červeného potomka,
 * - ukazatele parent musí odpovídat skutečné struktuře stromu,
 * - všechny cesty k nullptr musí mít stejnou černou výšku,
 * - skutečný počet uzlů musí odpovídat tree_size.
 *
 * @retval true Strom splňuje všechny kontrolované invarianty.
 * @retval false Alespoň jeden invariant stromu je porušen.
 *
 * @par Časová složitost
 * O(n), protože validační funkce musí navštívit všechny uzly stromu.
 */
template <typename T>
bool RBT<T>::validate() const
{
	if (this->root == nullptr) {
		return this->tree_size == 0;
	}

	if (this->root->parent != nullptr) {
		return false;
	}

	if (this->root->c != color::Black) {
		return false;
	}

	if (!validate_bst(this->root.get())) {
		return false;
	}

	if (!validate_red_nodes(this->root.get())) {
		return false;
	}

	if (!validate_parent_pointers(this->root.get())) {
		return false;
	}

	if (black_height(this->root.get()) < 0) {
		return false;
	}

	auto count_nodes = [](const auto& self, const node<T>* n) -> std::size_t {
		if (n == nullptr) {
			return 0;
		}

		return 1
			+ self(self, n->left.get())
			+ self(self, n->right.get());
	};

	if (count_nodes(count_nodes, this->root.get()) != this->tree_size) {
		return false;
	}

	return true;
}
template <typename T>
int RBT<T>::black_height(const node<T>* n) const
{
	if (n == nullptr) {
		return 0;
	}

	int left_height = black_height(n->left.get());
	if (left_height == -1) {
		return -1;
	}

	int right_height = black_height(n->right.get());
	if (right_height == -1) {
		return -1;
	}

	if (left_height != right_height) {
		return -1;
	}

	if (n->c == color::Black) {
		return left_height + 1;
	}

	return left_height;
}
template <typename T>
bool RBT<T>::validate_red_nodes(const node<T>* n) const
{
	std::stack<const node<T>*> st;

	if (n != nullptr) {
		st.push(n);
	}

	while (!st.empty()) {
		const node<T>* current = st.top();
		st.pop();

		if (current->c == color::Red) {
			if (current->left != nullptr &&
				current->left->c == color::Red) {
				return false;
			}

			if (current->right != nullptr &&
				current->right->c == color::Red) {
				return false;
			}
		}

		if (current->left != nullptr) {
			st.push(current->left.get());
		}

		if (current->right != nullptr) {
			st.push(current->right.get());
		}
	}

	return true;
}
template <typename T>
bool RBT<T>::validate_bst(const node<T>* n)const
{
	std::stack<const node<T>*> st;

	const node<T>* current = n;
	const node<T>* previous = nullptr;

	while (current != nullptr || !st.empty()) {

		while (current != nullptr) {
			st.push(current);
			current = current->left.get();
		}

		current = st.top();
		st.pop();

		if (previous != nullptr &&
			!(previous->key < current->key)) {
			return false;
		}

		previous = current;
		current = current->right.get();
	}

	return true;
}
/**
 * @brief Vloží nový klíč do červeno-černého stromu.
 *
 * @details
 * Funkce nejprve provede běžné vložení do binárního vyhledávacího
 * stromu. Nový uzel je vytvořen jako červený. Následně je zavolána
 * funkce insert_fixup(), která pomocí přebarvování a rotací obnoví
 * vlastnosti červeno-černého stromu.
 *
 * @par Průběh funkce
 * 1. Vyhledá pozici, na kterou má být nový klíč vložen.
 * 2. Pokud již klíč existuje, vložení se neprovede.
 * 3. Vytvoří nový červený uzel pomocí std::make_unique.
 * 4. Nastaví jeho ukazatel parent.
 * 5. Připojí uzel ke kořeni nebo k levému či pravému potomku.
 * 6. Zvýší tree_size.
 * 7. Zavolá insert_fixup() pro opravu RB vlastností.
 * 8. Nastaví kořen na černou barvu.
 *
 * @param key Klíč, který má být do stromu vložen.
 *
 * @retval true Klíč byl úspěšně vložen.
 * @retval false Klíč již ve stromu existoval.
 *
 * @par Časová složitost
 * O(log n) pro platný červeno-černý strom.
 */
template <typename T>
bool RBT<T>::insert(const T& key)
{
	node<T>* parent = nullptr;
	node<T>* current = this->root.get();

	while (current != nullptr) {
		parent = current;

		if (key == current->key) {
			return false;
		}
		else if (key < current->key) {
			current = current->left.get();
		}
		else {
			current = current->right.get();
		}
	}

	auto new_node = std::make_unique<node<T>>(key);

	new_node->c = color::Red;
	new_node->parent = parent;

	node<T>* inserted_node = new_node.get();

	if (parent == nullptr) {
		this->root = std::move(new_node);
	}
	else if (key < parent->key) {
		parent->left = std::move(new_node);
	}
	else {
		parent->right = std::move(new_node);
	}

	++this->tree_size;

	insert_fixup(inserted_node);

	this->root->c = color::Black;

	return true;
}
template <typename T>
void RBT<T>::insert_fixup(node<T>* n) {
     while ((n != this->root.get() && n->parent != nullptr && n->parent->c == color::Red))
        { if (n->parent->c == color::Black) { return; }
     else if ( n->parent->parent != nullptr && n->parent->parent->right != nullptr && n->parent->parent->left != nullptr && n->parent->parent->right->c == color::Red && n->parent->parent->left->c == color::Red )
     {
     n->parent->parent->left->c = color::Black;
     n->parent->parent->right->c = color::Black;
     n->parent->parent->c = color::Red;
     n = n->parent->parent;
     continue;
     }
     else if (n->parent->c == color::Red) {
            if (n->parent == n->parent->parent->left.get()) {
                if (n->parent->right.get() == n) { n = n->parent; rotate_left(n); }
                else { } }
    else {
          if (n->parent->left.get() == n)
          { n = n->parent; rotate_right(n); }
          else { } } }
    if ( n->parent != nullptr && n->parent->parent != nullptr && n->parent->c == color::Red && n->parent->parent->c == color::Black )
        {
             if (n->parent == n->parent->parent->left.get())
             { n->parent->c = color::Black;
             n->parent->parent->c = color::Red;
              rotate_right(n->parent->parent); }
    else { n->parent->c = color::Black; n->parent->parent->c = color::Red; rotate_left(n->parent->parent); } } }
    this->root->c = color::Black;
}
template <typename T>
void RBT<T>::delete_fixup(node<T>* n, node<T>* parent)
{
    while (n != this->root.get() &&
           get_color(n) == color::Black) {

        if (parent == nullptr) {
            break;
        }
        if (n == parent->left.get()) {

            node<T>* sibling = parent->right.get();
            if (get_color(sibling) == color::Red) {
                sibling->c = color::Black;
                parent->c = color::Red;

                rotate_left(parent);

                sibling = parent->right.get();
            }
            if (
                get_color(
                    sibling == nullptr
                        ? nullptr
                        : sibling->left.get()
                ) == color::Black
                &&
                get_color(
                    sibling == nullptr
                        ? nullptr
                        : sibling->right.get()
                ) == color::Black
            ) {
                if (sibling != nullptr) {
                    sibling->c = color::Red;
                }

                n = parent;
                parent = n->parent;
            }
            else {
                if (
                    get_color(
                        sibling == nullptr
                            ? nullptr
                            : sibling->right.get()
                    ) == color::Black
                ) {
                    if (sibling != nullptr &&
                        sibling->left != nullptr) {
                        sibling->left->c = color::Black;
                    }

                    if (sibling != nullptr) {
                        sibling->c = color::Red;
                        rotate_right(sibling);
                    }

                    sibling = parent->right.get();
                }
                if (sibling != nullptr) {
                    sibling->c = parent->c;
                }

                parent->c = color::Black;

                if (sibling != nullptr &&
                    sibling->right != nullptr) {
                    sibling->right->c = color::Black;
                }

                rotate_left(parent);

                n = this->root.get();
                parent = nullptr;
            }
        }
        else {

            node<T>* sibling = parent->left.get();
            if (get_color(sibling) == color::Red) {
                sibling->c = color::Black;
                parent->c = color::Red;

                rotate_right(parent);

                sibling = parent->left.get();
            }
            if (
                get_color(
                    sibling == nullptr
                        ? nullptr
                        : sibling->right.get()
                ) == color::Black
                &&
                get_color(
                    sibling == nullptr
                        ? nullptr
                        : sibling->left.get()
                ) == color::Black
            ) {
                if (sibling != nullptr) {
                    sibling->c = color::Red;
                }

                n = parent;
                parent = n->parent;
            }
            else {
                if (
                    get_color(
                        sibling == nullptr
                            ? nullptr
                            : sibling->left.get()
                    ) == color::Black
                ) {
                    if (sibling != nullptr &&
                        sibling->right != nullptr) {
                        sibling->right->c = color::Black;
                    }

                    if (sibling != nullptr) {
                        sibling->c = color::Red;
                        rotate_left(sibling);
                    }

                    sibling = parent->left.get();
                }
                if (sibling != nullptr) {
                    sibling->c = parent->c;
                }

                parent->c = color::Black;

                if (sibling != nullptr &&
                    sibling->left != nullptr) {
                    sibling->left->c = color::Black;
                }

                rotate_right(parent);

                n = this->root.get();
                parent = nullptr;
            }
        }
    }

    if (n != nullptr) {
        n->c = color::Black;
    }

    if (this->root != nullptr) {
        this->root->c = color::Black;
        this->root->parent = nullptr;
    }
}
template <typename T>
std::size_t RBT<T>::size() const
{
	return this->tree_size;
}
template <typename T>
bool RBT<T>::validate_parent_pointers(const node<T>* n) const
{
	if (n == nullptr) {
		return true;
	}

	std::stack<const node<T>*> st;
	st.push(n);

	while (!st.empty()) {
		const node<T>* current = st.top();
		st.pop();

		if (current->left != nullptr) {
			if (current->left->parent != current) {
				return false;
			}

			st.push(current->left.get());
		}

		if (current->right != nullptr) {
			if (current->right->parent != current) {
				return false;
			}

			st.push(current->right.get());
		}
	}

	return true;
}
template <typename T>
void RBT<T>::rotate_left(node<T>* n)
{
	if (n == nullptr || n->right == nullptr) {
		return;
	}

	std::unique_ptr<node<T>>* x = nullptr;
	node<T>* old_parent = n->parent;

	if (n == this->root.get()) {
		x = &this->root;
	}
	else if (n->parent->left.get() == n) {
		x = &n->parent->left;
	}
	else if (n->parent->right.get() == n) {
		x = &n->parent->right;
	}
	else {
		return;
	}

	std::unique_ptr<node<T>> y = std::move((*x)->right);

	(*x)->right = std::move(y->left);

	if ((*x)->right != nullptr) {
		(*x)->right->parent = (*x).get();
	}

	y->left = std::move(*x);
	y->left->parent = y.get();

	y->parent = old_parent;

	*x = std::move(y);
}
template <typename T>
void RBT<T>::rotate_right(node<T>* n)
{
	if (n == nullptr || n->left == nullptr) {
		return;
	}

	std::unique_ptr<node<T>>* x = nullptr;
	node<T>* old_parent = n->parent;

	if (n == this->root.get()) {
		x = &this->root;
	}
	else if (n->parent->left.get() == n) {
		x = &n->parent->left;
	}
	else if (n->parent->right.get() == n) {
		x = &n->parent->right;
	}
	else {
		return;
	}

	std::unique_ptr<node<T>> y = std::move((*x)->left);

	(*x)->left = std::move(y->right);

	if ((*x)->left != nullptr) {
		(*x)->left->parent = (*x).get();
	}

	y->right = std::move(*x);
	y->right->parent = y.get();

	y->parent = old_parent;

	*x = std::move(y);
}
template <typename T>
color RBT<T>::get_color(const node<T>* n) const
{
    if (n == nullptr) {
        return color::Black;
    }

    return n->c;
}
template <typename T>
void RBT<T>::print_subtree(
	const node<T>* n,
	std::ostream& output,
	std::size_t depth
) const
{
	if (n == nullptr) {
		return;
	}

	print_subtree(
		n->right.get(),
		output,
		depth + 1
	);

	for (std::size_t i = 0; i < depth; ++i) {
		output << "    ";
	}

	output << n->key;

	if (n->c == color::Red) {
		output << " (R)";
	}
	else {
		output << " (B)";
	}

	output << '\n';

	print_subtree(
		n->left.get(),
		output,
		depth + 1
	);
}
template <typename T>
std::ostream& operator<<(
	std::ostream& output,
	const RBT<T>& tree
)
{
	if (tree.root == nullptr) {
		output << "[empty tree]";
		return output;
	}

	tree.print_subtree(
		tree.root.get(),
		output,
		0
	);

	return output;
}
template <typename T>
std::size_t RBT<T>::height() const
{
    return height_subtree(this->root.get());
}

template <typename T>
std::size_t RBT<T>::height_subtree(
    const node<T>* n
) const
{
    if (n == nullptr) {
        return 0;
    }

    std::size_t left_height =
        height_subtree(n->left.get());

    std::size_t right_height =
        height_subtree(n->right.get());

    return 1 + std::max(left_height, right_height);
}
