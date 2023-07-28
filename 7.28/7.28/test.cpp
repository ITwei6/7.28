#include <iostream>
#include <time.h>
using namespace std;
#include <vector>
#include<list>
#include <algorithm>
//int main()
//{
//	srand(time(0));
//	const int N = 500000;
//	vector<int> v;
//	v.reserve(N);
//	list<int> lt1;
//	list<int> lt2;
//	for (int i = 0; i < N; i++)
//	{
//		auto e = rand();
//		lt1.push_back(e);
//		lt2.push_back(e);
//  }
//
//	//拷贝到vector数组里
//	int begin1 = clock();
//	for (auto e : lt1)
//	{
//		v.push_back(e);
//	}
//	
//	//拷贝完后在vector数组里排序
//	sort(v.begin(), v.end());
//	//排完序后再拷贝回去
//	size_t i = 0;
//	for (auto& e : v)
//	{
//		e = v[i++];
//	}
//	int end1 = clock();
//
//	int begin2 = clock();
//	lt2.sort();
//	int end2 = clock();
//	printf("vector sort:%d\n", end1 - begin1);
//	printf("list sort:%d\n", end2 - begin2);
//}
#include "list.h"
int main()
{
	tao::test1();
}