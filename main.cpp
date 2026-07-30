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

	std::cout << "All insert tests passed successfully.\n";

	return 0;
}
