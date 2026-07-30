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
bool RBT<T>::empty() const
{
	return this->root == nullptr;
}
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
     n->parent->parent->right->c = color::Black; n->parent->parent->c = color::Red;
     n = n->parent->parent;
     continue; }
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


