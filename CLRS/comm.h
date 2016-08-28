#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <memory.h>
#include <memory>
#include <limits.h>
#include <vector>
#include <algorithm>
#include <thread>
#include <iostream>

using std::vector;
using std::shared_ptr;

#define NIL UINT_MAX

//¶Ñ
#define PARENT(i) (((i + 1) >> 1) - 1)
#define LEFT(i) (((i + 1) << 1) - 1)
#define RIGHT(i) ((i + 1) << 1)

typedef struct MaxSubarray
{
	int left;
	int right;
	int sum;
} MaxSubarray;

//Á´±í
template<typename T> struct List
{
	List() = default;
	List (const T &v, List *p) : value(v), next(p) { }

	T value;
	List *next;
};

//¶þ²æÊ÷
template<typename T> struct BinaryTree
{
	BinaryTree() = default;
	BinaryTree(const T &v, BinaryTree *l, BinaryTree *r) :
		value(v), left(l), right(r) { }

	T value;
	BinaryTree *left;
	BinaryTree *right;
};

struct tree_t
{
	tree_t *left;
	tree_t *right;
	tree_t *parent;
	int key;
};