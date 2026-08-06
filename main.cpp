#include <iostream>
#include "RedBlackTree.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

void test_empty_tree()
{
	RBT<int> tree;

	assert(tree.empty());
	assert(tree.size() == 0);
	assert(!tree.find(10));
	assert(tree.validate());
}

void test_single_insert()
{
	RBT<int> tree;

	assert(tree.insert(10));
	assert(tree.find(10));
	assert(tree.size() == 1);
	assert(!tree.empty());
	assert(tree.validate());
}

void test_duplicate_insert()
{
	RBT<int> tree;

	assert(tree.insert(10));
	assert(!tree.insert(10));

	assert(tree.size() == 1);
	assert(tree.find(10));
	assert(tree.validate());
}

void test_left_left_case()
{
	RBT<int> tree;

	assert(tree.insert(30));
	assert(tree.validate());

	assert(tree.insert(20));
	assert(tree.validate());

	assert(tree.insert(10));
	assert(tree.validate());

	assert(tree.find(30));
	assert(tree.find(20));
	assert(tree.find(10));
	assert(tree.size() == 3);
}

void test_right_right_case()
{
	RBT<int> tree;

	assert(tree.insert(10));
	assert(tree.validate());

	assert(tree.insert(20));
	assert(tree.validate());

	assert(tree.insert(30));
	assert(tree.validate());

	assert(tree.find(10));
	assert(tree.find(20));
	assert(tree.find(30));
	assert(tree.size() == 3);
}

void test_left_right_case()
{
	RBT<int> tree;

	assert(tree.insert(30));
	assert(tree.validate());

	assert(tree.insert(10));
	assert(tree.validate());

	assert(tree.insert(20));
	assert(tree.validate());

	assert(tree.find(30));
	assert(tree.find(10));
	assert(tree.find(20));
	assert(tree.size() == 3);
}

void test_right_left_case()
{
	RBT<int> tree;

	assert(tree.insert(10));
	assert(tree.validate());

	assert(tree.insert(30));
	assert(tree.validate());

	assert(tree.insert(20));
	assert(tree.validate());

	assert(tree.find(10));
	assert(tree.find(30));
	assert(tree.find(20));
	assert(tree.size() == 3);
}

void test_recoloring()
{
	RBT<int> tree;

	const std::vector<int> values {
		10, 5, 15, 1, 7, 12, 20, 0
	};

	for (int value : values) {
		assert(tree.insert(value));
		assert(tree.find(value));
		assert(tree.validate());
	}

	assert(tree.size() == values.size());
}

void test_sorted_insertion()
{
	RBT<int> tree;

	for (int value = 1; value <= 1000; ++value) {
		assert(tree.insert(value));
		assert(tree.validate());
	}

	assert(tree.size() == 1000);

	for (int value = 1; value <= 1000; ++value) {
		assert(tree.find(value));
	}

	assert(!tree.find(0));
	assert(!tree.find(1001));
}

void test_reverse_sorted_insertion()
{
	RBT<int> tree;

	for (int value = 1000; value >= 1; --value) {
		assert(tree.insert(value));
		assert(tree.validate());
	}

	assert(tree.size() == 1000);

	for (int value = 1; value <= 1000; ++value) {
		assert(tree.find(value));
	}
}

void test_random_insertion()
{
	RBT<int> tree;

	std::vector<int> values(1000);
	std::iota(values.begin(), values.end(), 1);

	std::mt19937 generator(12345);
	std::shuffle(values.begin(), values.end(), generator);

	for (int value : values) {
		assert(tree.insert(value));
		assert(tree.validate());
	}

	assert(tree.size() == values.size());

	for (int value : values) {
		assert(tree.find(value));
	}

	for (int value : values) {
		assert(!tree.insert(value));
	}

	assert(tree.size() == values.size());
	assert(tree.validate());
}
void test_erase_empty_tree()
{
	RBT<int> tree;

	assert(!tree.erase(10));
	assert(tree.empty());
	assert(tree.size() == 0);
	assert(tree.validate());
}

void test_erase_missing_key()
{
	RBT<int> tree;

	assert(tree.insert(10));
	assert(tree.insert(5));
	assert(tree.insert(15));

	assert(!tree.erase(100));

	assert(tree.find(10));
	assert(tree.find(5));
	assert(tree.find(15));
	assert(tree.size() == 3);
	assert(tree.validate());
}

void test_erase_single_node()
{
	RBT<int> tree;

	assert(tree.insert(10));
	assert(tree.erase(10));

	assert(!tree.find(10));
	assert(tree.empty());
	assert(tree.size() == 0);
	assert(tree.validate());

	assert(!tree.erase(10));
}

void test_erase_red_leaf()
{
	RBT<int> tree;

	assert(tree.insert(10));
	assert(tree.insert(5));
	assert(tree.insert(15));

	assert(tree.erase(5));

	assert(!tree.find(5));
	assert(tree.find(10));
	assert(tree.find(15));
	assert(tree.size() == 2);
	assert(tree.validate());
}

void test_erase_black_leaf()
{
	RBT<int> tree;

	const std::vector<int> values {
		10, 5, 15, 1
	};

	for (int value : values) {
		assert(tree.insert(value));
		assert(tree.validate());
	}

	assert(tree.erase(15));

	assert(!tree.find(15));
	assert(tree.find(10));
	assert(tree.find(5));
	assert(tree.find(1));
	assert(tree.size() == 3);
	assert(tree.validate());
}

void test_erase_node_with_right_child()
{
	RBT<int> tree;

	const std::vector<int> values {
		10, 5, 15, 20
	};

	for (int value : values) {
		assert(tree.insert(value));
		assert(tree.validate());
	}

	assert(tree.erase(15));

	assert(!tree.find(15));
	assert(tree.find(10));
	assert(tree.find(5));
	assert(tree.find(20));
	assert(tree.size() == 3);
	assert(tree.validate());
}

void test_erase_node_with_left_child()
{
	RBT<int> tree;

	const std::vector<int> values {
		10, 5, 15, 1
	};

	for (int value : values) {
		assert(tree.insert(value));
		assert(tree.validate());
	}
	assert(tree.erase(5));

	assert(!tree.find(5));
	assert(tree.find(10));
	assert(tree.find(15));
	assert(tree.find(1));
	assert(tree.size() == 3);
	assert(tree.validate());
}

void test_erase_root_with_one_child()
{
	{
		RBT<int> tree;

		assert(tree.insert(10));
		assert(tree.insert(5));
		assert(tree.validate());

		assert(tree.erase(10));

		assert(!tree.find(10));
		assert(tree.find(5));
		assert(tree.size() == 1);
		assert(!tree.empty());
		assert(tree.validate());
	}

	{
		RBT<int> tree;

		assert(tree.insert(10));
		assert(tree.insert(15));
		assert(tree.validate());

		assert(tree.erase(10));

		assert(!tree.find(10));
		assert(tree.find(15));
		assert(tree.size() == 1);
		assert(!tree.empty());
		assert(tree.validate());
	}
}

void test_erase_two_children_direct_successor()
{
	RBT<int> tree;

	const std::vector<int> values {
		10, 5, 15, 20
	};

	for (int value : values) {
		assert(tree.insert(value));
		assert(tree.validate());
	}
	assert(tree.erase(10));

	assert(!tree.find(10));
	assert(tree.find(5));
	assert(tree.find(15));
	assert(tree.find(20));
	assert(tree.size() == 3);
	assert(tree.validate());
}

void test_erase_two_children_deep_successor()
{
	RBT<int> tree;

	const std::vector<int> values {
		20, 10, 30, 25, 40, 22, 27
	};

	for (int value : values) {
		assert(tree.insert(value));
		assert(tree.validate());
	}

	assert(tree.erase(20));

	assert(!tree.find(20));
	assert(tree.find(10));
	assert(tree.find(22));
	assert(tree.find(25));
	assert(tree.find(27));
	assert(tree.find(30));
	assert(tree.find(40));
	assert(tree.size() == 6);
	assert(tree.validate());
}

void test_sorted_erase()
{
	RBT<int> tree;

	for (int value = 1; value <= 200; ++value) {
		assert(tree.insert(value));
		assert(tree.validate());
	}

	for (int value = 1; value <= 200; ++value) {
		assert(tree.erase(value));
		assert(!tree.find(value));

		assert(
			tree.size() ==
			static_cast<std::size_t>(200 - value)
		);

		assert(tree.validate());
	}

	assert(tree.empty());
	assert(tree.size() == 0);
}

void test_reverse_sorted_erase()
{
	RBT<int> tree;

	for (int value = 1; value <= 200; ++value) {
		assert(tree.insert(value));
		assert(tree.validate());
	}

	std::size_t remaining = 200;

	for (int value = 200; value >= 1; --value) {
		assert(tree.erase(value));
		assert(!tree.find(value));

		--remaining;

		assert(tree.size() == remaining);
		assert(tree.validate());
	}

	assert(tree.empty());
	assert(tree.size() == 0);
}

void test_random_erase()
{
	RBT<int> tree;

	std::vector<int> values(1000);
	std::iota(values.begin(), values.end(), 1);

	std::mt19937 generator(12345);

	std::shuffle(
		values.begin(),
		values.end(),
		generator
	);

	for (int value : values) {
		assert(tree.insert(value));
		assert(tree.validate());
	}

	assert(tree.size() == values.size());
	std::shuffle(
		values.begin(),
		values.end(),
		generator
	);

	std::size_t remaining = values.size();

	for (int value : values) {
		assert(tree.find(value));
		assert(tree.erase(value));
		assert(!tree.find(value));

		--remaining;

		assert(tree.size() == remaining);
		assert(tree.validate());
	}

	assert(tree.empty());
	assert(tree.size() == 0);
	assert(tree.validate());
}
void assert_logarithmic_height(const RBT<int>& tree)
{
    if (tree.empty()) {
        assert(tree.height() == 0);
        return;
    }

    double maximum_height =
        2.0 * std::log2(
            static_cast<double>(tree.size()) + 1.0
        ) + 1.0;

    assert(
        static_cast<double>(tree.height())
        <= maximum_height
    );
}
using namespace std;

int main()
{
	test_empty_tree();
	test_single_insert();
	test_duplicate_insert();

	test_left_left_case();
	test_right_right_case();
	test_left_right_case();
	test_right_left_case();

	test_recoloring();
	test_sorted_insertion();
	test_reverse_sorted_insertion();
	test_random_insertion();

	test_erase_empty_tree();
	test_erase_missing_key();
	test_erase_single_node();

	test_erase_red_leaf();
	test_erase_black_leaf();

	test_erase_node_with_right_child();
	test_erase_node_with_left_child();
	test_erase_root_with_one_child();

	test_erase_two_children_direct_successor();
	test_erase_two_children_deep_successor();

	test_sorted_erase();
	test_reverse_sorted_erase();
	test_random_erase();

	cout<< "Všechny insert a erase testy úspěšně prošly"<<endl;


    RBT<int> rbt;
    vector<int> values(100);
	iota(values.begin(), values.end(), 1);

	mt19937 generator(12345);
	shuffle(values.begin(), values.end(), generator);

	for (int value : values) {
		assert(rbt.insert(value));
		assert(rbt.validate());
       if(value%10==0){
        assert_logarithmic_height(rbt);
       }
	}

    cout << rbt << endl;
	return 0;
}
