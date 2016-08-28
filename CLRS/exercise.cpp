#include "comm.h"
#include "algorithm.h"
#include "exercise.h"

void fun214(int *a, int *b, int *c, int n)
{
	int flag = 0;
	for (int j = 0; j < n; j++)
	{
		c[j] = a[j] + b[j] + flag;
		if (c[j] > 1)
		{
			c[j] %= 2;
			flag = 1;
		}
		else
			flag = 0;
	}
	c[n] = flag;
}

void fun232(int *a, int p, int q, int r)
{
	int n1 = q - p + 1;
	int n2 = r - q;
	int *left = (int*)malloc(n1 * sizeof(int));
	int *right = (int*)malloc(n2 * sizeof(int));

	int i, j;
	for (i = 0; i < n1; i++)
		left[i] = a[p + i];
	for (j = 0; j < n2; j++)
		right[j] = a[q + j + 1];

	i = 0;
	j = 0;
	int k = p;
	for (k = p; k <= r && i < n1 && j < n2; k++)
	{
		if (left[i] <= right[j])
			a[k] = left[i++];
		else
			a[k] = right[j++];
	}

	memcpy(&a[k], &left[i], n1 - i);
	memcpy(&a[k], &right[j], n2 - j);
}

void fun234(int *a, int len)
{
	if (len > 1)
	{
		fun234(a, len - 1);

		int k = a[len - 1];
		int i = len - 2;
		while (a[i] > k)
		{
			a[i + 1] = a[i];
			i--;
		}
		a[++i] = k;
	}
}

int fun235(int *a, int p, int r, int val)
{
	if (r - p > 1)
	{
		int q = (r + p) >> 1;
		if (val > a[q])
			fun235(a, q + 1, r, val);
		else if (val < a[q])
			fun235(a, p, q + 1, val);
		else
			return q;
	}
	else if (r - p == 1 && a[p] == val)
		return p;
	return r;
}

void fun236(int *a, int len)
{
	for (int j = 1; j < len; j++)
	{
		int k = a[j];
		int begin = 0, end = j, mid;
		while (begin != end)
		{
			mid = (begin + end) >> 1;
			if (k < a[mid])
				end = mid;
			else if (k > a[mid])
				begin = mid + 1;
			else
				break;
		}
		if (begin == end)
			mid = end;
		for (int i = j - 1; i >= mid; i--)
			a[i + 1] = a[i];
		a[mid] = k;
	}
}

bool fun237(int *a, int len, int x)
{
	mergeSort(a, 0, len - 1);
	for (int i = 0; i < len; i++)
	{
		if (bsearch(a, len, x - a[i]) != NULL)
			return true;
	}
	return false;
}

int fun24a(int *a, int p, int q, int r)
{
	int n1 = q - p + 1;
	int n2 = r - q;
	int *left = (int*)malloc(n1 * sizeof(int));
	int *right = (int*)malloc(n2 * sizeof(int));
	int inversions = 0;

	int i, j;
	for (i = 0; i < n1; i++)
		left[i] = a[p + i];
	for (j = 0; j < n2; j++)
		right[j] = a[q + j + 1];

	i = 0;
	j = 0;
	int k = p;
	while (i < n1 && j < n2)
	{
		if (left[i] <= right[j])
			a[k++] = left[i++];
		else
		{
			a[k++] = right[j++];
			inversions += n1 - i;
		}
	}

	memcpy(&a[k], &left[i], n1 - i);
	memcpy(&a[k], &right[j], n2 - j);

	return inversions;
}

int fun24(int *a, int p, int r)
{
	int inversions = 0;
	if (p < r)
	{
		int q = (p + r) >> 1;
		inversions += fun24(a, p, q);
		inversions += fun24(a, q + 1, r);
		inversions += fun24a(a, p, q, r);
	}
	return inversions;
}

int fun413(int *a, int low, int high)
{
	int maxSum = INT_MIN;
	int sum;

	for (int i = low; i <= high; i++)
	{
		sum = 0;
		for (int j = i; j <= high; j++)
		{
			sum += a[j];
			if (maxSum < sum)
				maxSum = sum;
		}
	}

	return maxSum;
}

//http://www.cnblogs.com/waytofall/archive/2012/04/10/2439820.html
int fun415(int *a, int low, int high)
{
	int maxSum = a[low];
	int sum = a[low];

	for (int i = low + 1; i <= high; i++)
	{
		if (sum < 0)
			sum = a[i];
		else
			sum += a[i];

		if (maxSum < sum)
			maxSum = sum;
	}

	return maxSum;
}

void fun427(int a, int b, int c, int d, int *real, int *img)
{
	int x1, x2, x3;
	x1 = a*(c - d);
	x2 = (a + b)*c;
	x3 = (a - b)*d;

	*real = x1 + x3;
	*img = x2 - x1;
}

//fun525: 设Xi为序列1,2,...,i中含有i的逆序数，问题转化为求E[X1+X2+...+Xn]

void fun625(vector<int> &a, size_t i)
{
	size_t l = LEFT(i);
	size_t r = RIGHT(i);
	size_t largest;

	while ((l < a.size() && a[l] > a[i]) || (r < a.size() && a[r] > a[i]))
	{
		largest = (r < a.size() && a[r] > a[l]) ? r : l;
		std::swap(a[i], a[largest]);
		i = largest;
		l = LEFT(i);
		r = RIGHT(i);
	}
}

//6.5-6
void heap_increase_key_no_swap(vector<int> &a, int i, int key)
{
	if (a[i] >= key)
	{
		return;
	}

	while (i > 0 && a[PARENT(i)] < key)
	{
		a[i] = a[PARENT(i)];
		i = PARENT(i);
	}
	a[i] = key;
}

//6.5-8
void heap_delete(vector<int> &a, size_t i)
{
	if (i >= a.size())
	{
		return;
	}

	std::swap(a[i], a[a.size() - 1]);
	a.pop_back();
	max_heapify(a, i);
}

//6.5-9
List<int> *merge_list(vector<List<int>*> a)
{
	vector<int> min_heap;
	List<int> *head = nullptr;
	List<int> *currList = head;
	size_t k;
	int min;

	for (auto &e : a)
	{
		if (e != nullptr)
		{
			min_heap_insert(min_heap, e->value);
			e = e->next;
		}
	}

	while (min_heap.size() > 0)
	{
		if (head == nullptr)
		{
			head = new List<int>;
			currList = head;
		}
		else
		{
			currList->next = new List<int>;
			currList = currList->next;
		}

		currList->value = heap_extract_min(min_heap);

		min = INT_MAX;
		k = a.size();
		for (size_t i = 0; i < a.size(); i++)
		{
			if (a[i] != nullptr && min >= a[i]->value)
			{
				min = a[i]->value;
				k = i;
			}
		}
		if (k != a.size())
		{
			min_heap_insert(min_heap, a[k]->value);
			a[k] = a[k]->next;
		}
	}

	currList->next = nullptr;

	return head;
}

//7-1
int hoare_partition(int *a, int p, int r)
{
	int i = p - 1;
	int j = r + 1;
	int x = a[p];

	while (true)
	{
		do 
		{
			--j;
		} while (a[j] > x);
		do 
		{
			++i;
		} while (a[i] < x);
		if (i < j)
		{
			std::swap(a[i], a[j]);
		}
		else
		{
			return j;
		}
	}
}

//7-2
void partition_(int *a, int p, int r, int *q, int *t)
{
	int idx = rand() % (r - p + 1) + p;
	int x = a[idx];
	int i = p - 1;
	std::swap(a[idx], a[r]);

	for (int j = p; j < r; j++)
	{
		if (a[j] < x)
		{
			std::swap(a[++i], a[j]);
		}
	}
	for (int j = i + 1; j < r; j++)
	{
		if (a[j] == x)
		{
			std::swap(a[++i], a[j]);
		}
	}

	std::swap(a[++i], a[r]);

	*t = i;
	while (--i >= p && a[i] == x); //循环体为空
	*q = i + 1;
}

void quick_sort_(int *a, int p, int r)
{
	if (p < r)
	{
		int q, t;
		partition_(a, p, r, &q, &t);
		quick_sort_(a, p, q - 1);
		quick_sort_(a, t + 1, r);
	}
}

//7-4
void tail_recursive_quick_sort(int *a, int p, int r)
{
	while (p < r)
	{
		int q = partition(a, p, r);
		tail_recursive_quick_sort(a, p, q - 1);
		p = q + 1;
	}
}

void tail_recursive_quick_sort_(int *a, int p, int r)
{
	while (p < r)
	{
		int q = partition(a, p, r);
		if (q - p < r - q)
		{
			tail_recursive_quick_sort_(a, p, q - 1);
			p = q + 1;
		}
		else
		{
			tail_recursive_quick_sort_(a, q + 1, r);
			r = q - 1;
		}
	}
}

//8-2 a计数排序；b用0作为元素进行partition；c插入排序
//e
void counting_sort_in_place(vector<int> &a, int k)
{
	vector<int> c(k + 1, 0);
	int pos = 0;

	for (auto e : a)
	{
		c[e] += 1;
	}

	for (int i = 0; i <= k; i++)
	{
		if (c[i] > 0)
		{
			memset(&a[pos], i, c[i]);
			pos += c[i];
		}
	}
}

//8-5
//a. 1-sort即为通常意义的排序
//b. 2,1,3,4,5,6,7,8,9,10
//c. 把k-sort的公式左边减去右边即得证
//d. k-sort <=> (a1,a1+k,a1+2k...)、(a2,a2+k,a2+2k...)、(ak,a2k,a3k...)等k个子数组已排序，
//每个数组有n/k个元素，所以可以使用快速排序依次排序这k个子数组，复杂度为O(k*(n/k)*lg(n/k))=O(nlg(n/k))
//e. 用6.5-9的方法merge k个子数组，复杂度为O(nlgk)
//f. k-sort等价于排序k个子长度为n/k的数组，每个子数组排序的复杂度为Ω((n/k)lg(n/k))，所以总复杂度为Ω(nlg(n/k))，
//由于k为常数，Ω(nlg(n/k)) = Ω(nlgn)

//8-6
//a. 相当于从2n个数中选择n个，因此为C(2n, n)
//b. 决策树叶的个数相当于从2n个空位选择n个，放入第一个数组，再放入第二个数组，由于两个数组都是排序的，因此放入的顺序
//只有一种，因此公有C(2n, n)个叶，计算lgC(2n, n)可得2n - o(n)
//c. 假设排好的序列有相邻元素a,b分别属于数组1和数组2，由于是比较排序，因此a和b的位置只能由比较获得，假如a未与b比较，则
//a与一个小于等于b的元素x1比较得到a <= x1或b与一个大于等于a的元素x2比较得出b >= x2，两种情况的结果分别为a,x1,b和a,x2,b，
//与前提条件矛盾，于是得证
//d. 考虑数组1中元素ai与数组2中元素bi交叉的情况，即最终排序的数组元素顺序为a1,b1,a2,b2...，则由c可得，b1与a1、a2比较等，
//因此至少比较2n - 1次，最坏情况下的比较次数不应该比这种情况少，于是得证

//8-7
static void sort_column(int *a, size_t r, size_t s)
{
	std::vector<std::thread *> vpt(s, nullptr);

	for (size_t i = 0; i < s; i++)
	{
		auto beg = i * r, end = beg + r - 1;
		vpt[i] = new std::thread(quick_sort, a, beg, end);
	}

	for (auto e : vpt)
	{
		e->join();
	}
}

void columnsort(int *a, size_t r, size_t s) //数组元素按列存放
{
	size_t n = r * s;
	int *cpy = (int*)calloc(n, sizeof(int));

	sort_column(a, r, s);

	for (size_t i = 0; i < n; i++)
	{
		cpy[i%s*r + i/s] = a[i];
	}

	sort_column(cpy, r, s);

	for (size_t i = 0; i < n; i++)
	{
		a[i] = cpy[i%s*r + i / s];
	}

	sort_column(a, r, s);

	sort_column(a + r / 2, r, s - 1);

	free(cpy);
}

//9.2-3
int iterative_randomized_select(int *a, size_t p, size_t r, size_t i)
{
	while (p < r)
	{
		size_t q = randomized_partition(a, p, r);
		size_t k = q - p + 1;
		if (i == k)
		{
			return a[q];
		}
		else if (i < k)
		{
			r = q - 1;
		}
		else
		{
			p = q + 1;
			i -= k;
		}
	}

	return a[p];
}

//9-3
int fun93(int *a, size_t p, size_t r, size_t i)
{
	size_t n = r - p + 1;
	size_t mid_size = n / 2;

	if (i >= n / 2)
	{
		return select(a, p, r, i);
	}

	for (size_t j = p; j < p + mid_size; j++)
	{
		if (a[j] < a[j + mid_size])
		{
			std::swap(a[j], a[j + mid_size]);
		}
	}

	std::vector<std::pair<int, int>> vp;
	for (size_t j = p; j < p + mid_size; j++)
	{
		vp.push_back({ a[j], a[j + mid_size] });
	}
	fun93(a, p + mid_size, r, i);

	int *b = new int[2 * i];
	size_t l = 0;
	for (size_t j = p + mid_size; j < p + mid_size + i; j++)
	{
		bool flag = false;
		for (size_t k = 0; k < mid_size; k++)
		{
			if (vp[k].second == a[j])
			{
				b[l++] = vp[k].first;
				b[l++] = vp[k].second;
				flag = true;
				break;
			}
		}
		if (!flag)
		{
			b[l++] = a[j];
		}
	}
	int m = select(b, 0, l - 1, i);
	fixed_partition(a, p, r, m);

	delete[] b;
	return m;
}

//10.2-7
List<int> *revert(List<int> *head)
{
	List<int> *curr, *prev, *next;
	prev = head;

	if (head == nullptr) return nullptr;

	curr = prev->next;
	while (curr != nullptr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	head->next = nullptr;

	return prev;
}

//10.4-5
size_t print_tree(tree_t *tree, int *out)
{
	size_t i = 0;
	tree_t *prev = tree->parent;

	while (tree)
	{
		if (prev == tree->parent)
		{
			out[i++] = tree->key;
			prev = tree;
			tree = tree->left ? tree->left : tree->right ?
				tree->right : tree->parent;
		}
		else if (prev == tree->left && tree->right)
		{
			prev = tree;
			tree = tree->right;
		}
		else
		{
			prev = tree;
			tree = tree->parent;
		}
	}

	return i;
}