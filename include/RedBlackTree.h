#ifndef RBT_H
#define RBT_H

#include <cstddef>
#include <memory>
#include <ostream>

enum class color
{
	Red,
	Black
};

template <typename T>
struct node
{
	T key;
	color c;

	std::unique_ptr<node<T>> left;
	std::unique_ptr<node<T>> right;

	node<T>* parent;

	explicit node(const T& key);
};

template <typename T>
class RBT
{
public:
	RBT();
	~RBT() = default;

	RBT(const RBT&) = delete;
	RBT& operator=(const RBT&) = delete;

	RBT(RBT&&) noexcept = default;
	RBT& operator=(RBT&&) noexcept = default;

	bool insert(const T& key);
	bool find(const T& key) const;
	bool erase(const T& key);

	bool empty() const;
	std::size_t size() const;
	void clear();

	void print(std::ostream& output) const;
	bool validate() const;

private:
	std::unique_ptr<node<T>> root;
	std::size_t tree_size;

	node<T>* find_key(node<T>* n, const T& key) const;
	node<T>* minimum(node<T>* n) const;

	void insert_fixup(node<T>* n);
	void delete_fixup(node<T>* n, node<T>* parent);

	void rotate_left(node<T>* n);
	void rotate_right(node<T>* n);

	void transplant(
		node<T>* old_subtree,
		std::unique_ptr<node<T>> new_subtree
	);

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
};

#include "RedBlackTree.tpp"

#endif
