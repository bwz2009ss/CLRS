#include "comm.h"
#include "algorithm.h"

//二分法查找
int *bsearch(int *t, int n, int x)
{
	int *lo = t, *hi = t + n;
	while (lo < hi) {
		int *mid = lo + ((hi - lo) >> 1);
		if (x < *mid)
			hi = mid;
		else if (x > *mid)
			lo = mid + 1;
		else
			return mid;
	}
	return NULL;
}

//最大子数组
MaxSubarray findMaxCrossingSubarray(int *a, int low, int mid, int high)
{
	int leftSum = INT_MIN;
	int rightSum = INT_MIN;
	int sum = 0;
	MaxSubarray maxSubarray;

	for (int i = mid; i >= low; i--)
	{
		sum += a[i];
		if (sum > leftSum)
		{
			maxSubarray.left = i;
			leftSum = sum;
		}
	}

	sum = 0;
	for (int i = mid + 1; i <= high; i++)
	{
		sum += a[i];
		if (sum > rightSum)
		{
			maxSubarray.right = i;
			rightSum = sum;
		}
	}

	maxSubarray.sum = leftSum + rightSum;

	return maxSubarray;
}

MaxSubarray findMaximumSubarray(int *a, int low, int high)
{
	MaxSubarray maxSubarray;

	if (low == high)
	{
		maxSubarray.left = maxSubarray.right = low;
		maxSubarray.sum = a[low];
		return maxSubarray;
	}

	int mid = (low + high) >> 1;

	maxSubarray = findMaxCrossingSubarray(a, low, mid, high);
	MaxSubarray tmp1 = findMaximumSubarray(a, low, mid);
	MaxSubarray tmp2 = findMaximumSubarray(a, mid + 1, high);

	if (tmp1.sum > maxSubarray.sum)
		maxSubarray = tmp1;
	if (tmp2.sum > maxSubarray.sum)
		maxSubarray = tmp2;

	return maxSubarray;
}

//插入排序
void insertionSort(int *a, int len)
{
	for (int j = 1; j < len; j++) {
		int key = a[j];
		int i = j - 1;
		while (i >= 0 && a[i] > key) {
			a[i + 1] = a[i];
			i--;
		}
		a[i + 1] = key;
	}
}

//归并排序
void merge(int *a, int p, int q, int r)
{
	int n1 = q - p + 1;
	int n2 = r - q;
	int *left = (int*)malloc((n1 + 1) * sizeof(int));
	int *right = (int*)malloc((n2 + 1) * sizeof(int));

	int i, j;
	for (i = 0; i < n1; i++)
		left[i] = a[p + i];
	left[n1] = INT_MAX;
	for (j = 0; j < n2; j++)
		right[j] = a[q + j + 1];
	right[n2] = INT_MAX;

	i = 0;
	j = 0;
	for (int k = p; k <= r; k++)
	{
		if (left[i] <= right[j])
			a[k] = left[i++];
		else
			a[k] = right[j++];
	}
}

void mergeSort(int *a, int p, int r)
{
	if (p < r)
	{
		int q = (p + r) / 2;
		mergeSort(a, p, q);
		mergeSort(a, q + 1, r);
		merge(a, p, q, r);
	}
}

//冒泡排序
void bubbleSort(int *a, int len)
{
	for (int i = 0; i < len - 1; i++)
	{
		for (int j = len - 1; j > i; j--)
		{
			if (a[j] < a[j - 1])
			{
				int tmp = a[j];
				a[j] = a[j - 1];
				a[j - 1] = tmp;
			}
		}
	}
}

//堆排序
void max_heapify(vector<int> &a, size_t i)
{
	size_t l = LEFT(i);
	size_t r = RIGHT(i);
	size_t largest = i;

	if (l < a.size() && a[l] > a[largest])
	{
		largest = l;
	}

	if (r < a.size() && a[r] > a[largest])
	{
		largest = r;
	}

	if (largest != i)
	{
		std::swap(a[i], a[largest]);
		max_heapify(a, largest);
	}
}

void min_heapify(vector<int> &a, size_t i)
{
	size_t l = LEFT(i);
	size_t r = RIGHT(i);
	size_t min = i;

	if (l < a.size() && a[l] < a[min])
	{
		min = l;
	}

	if (r < a.size() && a[r] < a[min])
	{
		min = r;
	}

	if (min != i)
	{
		std::swap(a[i], a[min]);
		min_heapify(a, min);
	}
}

void build_max_heap(vector<int> &a)
{
	for (int i = static_cast<int>((a.size() >> 1)) - 1; i >= 0; i--)
	{
		max_heapify(a, i);
	}
}

void build_min_heap(vector<int> &a)
{
	for (int i = static_cast<int>((a.size() >> 1)) - 1; i >= 0; i--)
	{
		min_heapify(a, i);
	}
}

void heap_sort(vector<int>& a)
{
	build_max_heap(a);
	vector<int> a2 = a;

	for (int i = a.size() - 1; i >= 1; i--)
	{
		std::swap(a[0], a[i]);
		a2[i] = a[i];
		a.pop_back();
		max_heapify(a, 0);
	}
	a2[0] = a[0];

	a = a2;
}

//最大优先队列
int heap_maximum(const vector<int> &a)
{
	return a[0];
}

int heap_extract_max(vector<int> &a)
{
	int max = a[0];
	a[0] = a.back();
	a.pop_back();
	if (a.size() > 1)
	{
		max_heapify(a, 0);
	}

	return max;
}

void heap_increase_key(vector<int> &a, int i, int key)
{
	if (a[i] >= key)
	{
		return;
	}

	a[i] = key;
	while (i > 0 && a[PARENT(i)] < a[i])
	{
		std::swap(a[PARENT(i)], a[i]);
		i = PARENT(i);
	}
}

void max_heap_insert(vector<int> &a, int key)
{
	a.push_back(INT_MIN);
	heap_increase_key(a, a.size() - 1, key);
}

//最小优先队列
int heap_minimum(const vector<int> &a)
{
	return a[0];
}

int heap_extract_min(vector<int> &a)
{
	int min = a[0];
	a[0] = a.back();
	a.pop_back();
	if (a.size() > 1)
	{
		min_heapify(a, 0);
	}

	return min;
}

void heap_decrease_key(vector<int> &a, int i, int key)
{
	if (a[i] <= key)
	{
		return;
	}

	a[i] = key;
	while (i > 0 && a[PARENT(i)] > a[i])
	{
		std::swap(a[PARENT(i)], a[i]);
		i = PARENT(i);
	}
}

void min_heap_insert(vector<int> &a, int key)
{
	a.push_back(INT_MAX);
	heap_decrease_key(a, a.size() - 1, key);
}

//快速排序
int partition(int *a, int p, int r)
{
	int i = p - 1;
	int x = a[r];
	
	for (int j = p; j < r; j++)
	{
		if (a[j] <= x)
		{
			std::swap(a[++i], a[j]);
		}
	}

	std::swap(a[++i], a[r]);

	return i;
}

void quick_sort(int *a, int p, int r)
{
	if (p < r)
	{
		int q = partition(a, p, r);
		quick_sort(a, p, q - 1);
		quick_sort(a, q + 1, r);
	}
}

//快速排序的随机化版本
int randomized_partition(int *a, int p, int r)
{
	int i = p - 1;
	int k = rand() % (r - p + 1) + p;
	int x = a[k];
	std::swap(a[k], a[r]);

	for (int j = p; j < r; j++)
	{
		if (a[j] <= x)
		{
			std::swap(a[++i], a[j]);
		}
	}
	
	std::swap(a[++i], a[r]);

	return i;
}

void randomized_quick_sort(int *a, int p, int r)
{
	if (p < r)
	{
		int q = randomized_partition(a, p, r);
		randomized_quick_sort(a, p, q - 1);
		randomized_quick_sort(a, q + 1, r);
	}
}

//计数排序
vector<int> counting_sort(const vector<int> &a, int k)
{
	vector<int> b(a.size());
	vector<int> c(k + 1, 0);

	for (auto e : a)
	{
		c[e] += 1;
	}
	for (int i = 1; i <= k; i++)
	{
		c[i] += c[i - 1];
	}

	for (int i = a.size() - 1; i >= 0 ; i--)
	{
		b[c[a[i]] - 1] = a[i];
		c[a[i]] -= 1;
	}

	return b;
}

//基数排序
vector<vector<int>> counting_sort_(const vector<vector<int>> &a, int d, int k)
{
	vector<vector<int>> b(a);
	vector<int> c(k + 1, 0);

	for (auto e : a[d])
	{
		c[e] += 1;
	}
	for (int i = 1; i <= k; i++)
	{
		c[i] += c[i - 1];
	}

	for (int i = a[d].size() - 1; i >= 0; i--)
	{
		for (size_t j = 0; j < a.size(); j++)
		{
			b[j][c[a[d][i]] - 1] = a[j][i];
		}
		c[a[d][i]] -= 1;
	}

	return b;
}

vector<vector<int>> radix_sort(const vector<vector<int>> &a)
{
	vector<vector<int>> b(a);

	for (int i = a.size() - 1; i >= 0; i--)
	{
		b = counting_sort_(b, i, 9);
	}

	return b;
}

//桶排序
static List<double> *bucket_sort_add_element_in_order(List<double> *head, double e)
{
	List<double> *p = new List<double>(e, nullptr);
	List<double> *pivot = head;
	List<double> *prev = nullptr;

	if (head == nullptr)
	{
		return p;
	}

	while (pivot != nullptr && pivot->value < e)
	{
		prev = pivot;
		pivot = pivot->next;
	}
	if (prev == nullptr)
	{
		p->next = head;
		head = p;
	}
	else
	{
		prev->next = p;
		p->next = pivot;
	}

	return head;
}

static List<double> *bucket_sort_concatenate_list(const vector<List<double>*> &l)
{
	List<double> *head = nullptr;
	List<double> *pivot;

	for (const auto &e: l)
	{
		if (e != nullptr)
		{
			if (head == nullptr)
			{
				head = e;
				pivot = head;
			}
			else
			{
				while (pivot->next != nullptr)
				{
					pivot = pivot->next;
				}
				pivot->next = e;
			}
		}
	}

	return head;
}

List<double> *bucket_sort(const vector<double>& a)
{
	vector<List<double>*> b(a.size(), nullptr);

	for (size_t i = 0; i < a.size(); i++)
	{
		size_t idx = static_cast<size_t>(a.size() * a[i]);
		b[idx] = bucket_sort_add_element_in_order(b[idx], a[i]);
	}

	return bucket_sort_concatenate_list(b);
}

//求数组最小值
int minimun(const vector<int> &a)
{
	int min = a[0];

	for (size_t i = 1; i < a.size(); i++)
	{
		if (a[i] < min)
		{
			min = a[i];
		}
	}

	return min;
}

//求数组最小值和最大值
std::pair<int, int> minmax(const vector<int> &a)
{
	auto n = a.size();
	int min, max;
	size_t beg;

	if (n == 1)
	{
		return { a[0], a[0] };
	}
	else if (n & 1)
	{
		min = max = a[0];
		beg = 1;
	}
	else
	{
		min = a[0];
		max = a[1];
		if (min > max)
		{
			min = a[1];
			max = a[0];
		}
		beg = 2;
	}

	for (size_t i = beg; i < n; i += 2)
	{
		int p = a[i], q = a[i + 1];
		if (a[i] > a[i + 1])
		{
			p = a[i + 1];
			q = a[i];
		}
		min = (min > p) ? p : min;
		max = (max < q) ? q : max;
	}

	return { min, max };
}

//选择数组第i个统计元素的随机化算法
int randomized_select(int *a, size_t p, size_t r, size_t i)
{
	if (p == r)
	{
		return a[p];
	}

	size_t q = randomized_partition(a, p, r);
	size_t k = q - p + 1;

	if (i == k)
	{
		return a[q];
	}
	else if (i < k)
	{
		return randomized_select(a, p, q - 1, i);
	}
	else
	{
		return randomized_select(a, q + 1, r, i - k);
	}
}

//选择数组第i个统计元素的最坏情况下O(n)算法
size_t fixed_partition(int *a, size_t p, size_t r, int x)
{
	size_t i = p;
	for (size_t j = p; j <= r; j++)
	{
		if (a[j] <= x)
		{
			std::swap(a[i++], a[j]);
		}
	}
	if (a[--i] != x)
	{
		size_t j = i;
		while (j != p && a[j] != x)
		{
			j--;
		}
		std::swap(a[i], a[j]);
	}
	return i;
}

int select(int *a, size_t p, size_t r, size_t i)
{
	if (p == r)
	{
		return a[p];
	}

	size_t n = r - p + 1;
	size_t gp_num = (n % 5) ? (n / 5 + 1) : (n / 5);
	size_t last_gp_elem_num = (n % 5) ? (n % 5) : 5;

	for (size_t i = 0; i < gp_num - 1; i++)
	{
		insertionSort(a + p + 5 * i, 5);
	}
	insertionSort(a + p + (5 * gp_num - 5), last_gp_elem_num);

	//方案1
	for (size_t i = 0; i < gp_num - 1; i++)
	{
		std::swap(a[p + i], a[p + 5 * i + 2]);
	}
	std::swap(a[p + gp_num - 1], a[p + 5 * gp_num - 5 + (last_gp_elem_num - 1) / 2]);

	int m = select(a, p, p + gp_num - 1, (gp_num + 1) / 2);

	//方案2
	/*int *medians = new int[gp_num];
	for (size_t i = 0; i < gp_num - 1; i++)
	{
		medians[i] = a[p + 5 * i + 2];
	}
	medians[gp_num - 1] = a[p + 5 * gp_num - 5 + (last_gp_elem_num - 1) / 2];

	int m = select(medians, 0, gp_num - 1, (gp_num + 1) / 2);
	delete[] medians;*/

	size_t q = fixed_partition(a, p, r, m);
	size_t k = q - p + 1;

	if (i == k)
	{
		return a[q];
	}
	else if (i < k)
	{
		return select(a, p, q - 1, i);
	}
	else
	{
		return select(a, q + 1, r, i - k);
	}
}

//栈和队列
unsigned char stack[STACK_SIZE];
unsigned char queue[QUEUE_SIZE];
unsigned char *sp = stack;
unsigned char *qhead = queue;
unsigned char *qtail = queue;