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

//fun525: ��XiΪ����1,2,...,i�к���i��������������ת��Ϊ��E[X1+X2+...+Xn]

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
	while (--i >= p && a[i] == x); //ѭ����Ϊ��
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

//8-2 a��������b��0��ΪԪ�ؽ���partition��c��������
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
//a. 1-sort��Ϊͨ�����������
//b. 2,1,3,4,5,6,7,8,9,10
//c. ��k-sort�Ĺ�ʽ��߼�ȥ�ұ߼���֤
//d. k-sort <=> (a1,a1+k,a1+2k...)��(a2,a2+k,a2+2k...)��(ak,a2k,a3k...)��k��������������
//ÿ��������n/k��Ԫ�أ����Կ���ʹ�ÿ�����������������k�������飬���Ӷ�ΪO(k*(n/k)*lg(n/k))=O(nlg(n/k))
//e. ��6.5-9�ķ���merge k�������飬���Ӷ�ΪO(nlgk)
//f. k-sort�ȼ�������k���ӳ���Ϊn/k�����飬ÿ������������ĸ��Ӷ�Ϊ��((n/k)lg(n/k))�������ܸ��Ӷ�Ϊ��(nlg(n/k))��
//����kΪ��������(nlg(n/k)) = ��(nlgn)

//8-6
//a. �൱�ڴ�2n������ѡ��n�������ΪC(2n, n)
//b. ������Ҷ�ĸ����൱�ڴ�2n����λѡ��n���������һ�����飬�ٷ���ڶ������飬�����������鶼������ģ���˷����˳��
//ֻ��һ�֣���˹���C(2n, n)��Ҷ������lgC(2n, n)�ɵ�2n - o(n)
//c. �����źõ�����������Ԫ��a,b�ֱ���������1������2�������ǱȽ��������a��b��λ��ֻ���ɱȽϻ�ã�����aδ��b�Ƚϣ���
//a��һ��С�ڵ���b��Ԫ��x1�Ƚϵõ�a <= x1��b��һ�����ڵ���a��Ԫ��x2�Ƚϵó�b >= x2����������Ľ���ֱ�Ϊa,x1,b��a,x2,b��
//��ǰ������ì�ܣ����ǵ�֤
//d. ��������1��Ԫ��ai������2��Ԫ��bi�������������������������Ԫ��˳��Ϊa1,b1,a2,b2...������c�ɵã�b1��a1��a2�Ƚϵȣ�
//������ٱȽ�2n - 1�Σ������µıȽϴ�����Ӧ�ñ���������٣����ǵ�֤

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

void columnsort(int *a, size_t r, size_t s) //����Ԫ�ذ��д��
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