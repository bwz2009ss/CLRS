#pragma once

void fun214(int *a, int *b, int *c, int n);
void fun232(int *a, int p, int q, int r);
void fun234(int *a, int len);
int fun235(int *a, int p, int r, int val);
void fun236(int *a, int len);
bool fun237(int *a, int len, int x);
int fun24a(int *a, int p, int q, int r);
int fun24(int *a, int p, int r);
int fun413(int *a, int low, int high);
int fun415(int *a, int low, int high);
void fun427(int a, int b, int c, int d, int *real, int *img);
void fun625(vector<int> &a, size_t i);
void heap_increase_key_no_swap(vector<int> &a, int i, int key);
void heap_delete(vector<int> &a, size_t i);
List<int> *merge_list(vector<List<int>*> a);
int hoare_partition(int *a, int p, int r);
void partition_(int *a, int p, int r, int *q, int *t);
void quick_sort_(int *a, int p, int r);
void tail_recursive_quick_sort(int *a, int p, int r);
void tail_recursive_quick_sort_(int *a, int p, int r);
void counting_sort_in_place(vector<int> &a, int k);
void columnsort(int *a, size_t r, size_t s);
int iterative_randomized_select(int *a, size_t p, size_t r, size_t i);
int fun93(int *a, size_t p, size_t r, size_t i);

List<int> *revert(List<int> *head);
size_t print_tree(tree_t *tree, int *out);