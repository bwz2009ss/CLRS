#include "comm.h"
#include "algorithm.h"
#include "exercise.h"

using namespace std;

int main()
{
	int a[8] = { 2,5,8,1,2,0,88,11 };
	int b[8] = { 1,4,2,3,6,9,0,7 };
	int c[8] = { 1,2,3,4,5,6,7,8 };
	int d[16] = { 13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7 };
	int e[5] = { -2,-5,-1,-3,-4 };
	int f[5] = { 4, 2,2,1,2 };
	vector<int> va = { 16,4,10,14,7,9,3,2,8,1 };
	vector<int> vb = { 10,2,4,6,8,9 };
	vector<int> vc = { 4,1,3,2,16,9,10,14,8,7 };
	vector<int> vd = { 1, 4,3,9,11,29,60 };  //最小堆
	vector<int> ve = { 12, 8, 6, 2, 5, 3 };  //最大堆

	List<int> *head1, *head2, *head3, *pList1, *pList2, *pList3;
	head1 = new List<int>;
	head2 = new List<int>;
	head3 = new List<int>;
	pList1 = head1;
	pList2 = head2;
	pList3 = head3;
	int i;
	for (i = 0; i < 3; i++)
	{
		pList1->value = 2 * i + 3;
		pList1->next = new List<int>;
		pList1 = pList1->next;

		pList2->value = i + 5;
		pList2->next = new List<int>;
		pList2 = pList2->next;

		pList3->value = 3 * i - 1;
		pList3->next = new List<int>;
		pList3 = pList3->next;
	}
	pList1->value = 2 * i + 3;
	pList1->next = nullptr;
	pList2->value = i + 5;
	pList2->next = nullptr;
	pList3->value = 3 * i - 1;
	pList3->next = nullptr;
	vector<List<int>*> vList = { head1, head2, head3 };

	vector<vector<int>> vva = { { 3,4,6,8,4,7,3 },{ 2,5,5,3,3,2,5 },{ 9,7,7,9,6,0,5 } };
	vector<double> vda = { .78,.17,.39,.26,.72,.94,.21,.12,.23,.68 };
	
	int a1[18] = { 10,8,12,16,4,18,14,7,1,9,15,3,5,17,6,11,2,13 };
	int a2[19] = { 10,8,12,16,4,18,14,7,19,9,15,3,5,17,6,11,2,13,1 };

	for (auto i = 1; i <= 19; i++)
	{
		cout << fun93(a2, 0, 18, i) << endl;
	}
}