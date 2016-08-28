#pragma once

void insertionSort(int * array, int len);
void mergeSort(int *a, int p, int r);
void bubbleSort(int *a, int len);

int *bsearch(int *t, int n, int x);

MaxSubarray findMaximumSubarray(int *a, int low, int high);

void max_heapify(vector<int> &a, size_t i);
void min_heapify(vector<int> &a, size_t i);
void build_max_heap(vector<int> &a);
void build_min_heap(vector<int> &a);
void heap_sort(vector<int> &a);
int heap_maximum(const vector<int> &a);
int heap_extract_max(vector<int> &a);
void heap_increase_key(vector<int> &a, int i, int key);
void max_heap_insert(vector<int> &a, int key);
int heap_minimum(const vector<int> &a);
int heap_extract_min(vector<int> &a);
void heap_decrease_key(vector<int> &a, int i, int key);
void min_heap_insert(vector<int> &a, int key);

int partition(int *a, int p, int r);
void quick_sort(int *a, int p, int r);
int randomized_partition(int *a, int p, int r);
void randomized_quick_sort(int *a, int p, int r);

vector<int> counting_sort(const vector<int> &a, int k); //a�е�Ԫ������[0, k]
vector<vector<int>> counting_sort_(const vector<vector<int>> &a, int d, int k); //���ڻ�������ļ�������
vector<vector<int>> radix_sort(const vector<vector<int>> &a); //a�е�ÿ��vector������ͬ��size
List<double> *bucket_sort(const vector<double> &a);

int minimun(const vector<int> &a);
std::pair<int, int> minmax(const vector<int> &a);
int randomized_select(int *a, size_t p, size_t r, size_t i);
size_t fixed_partition(int *a, size_t p, size_t r, int x);
int select(int *a, size_t p, size_t r, size_t i);

