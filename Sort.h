#pragma once
#include <iostream>
using std::cout;
using std::endl;
#include <string.h>
using std::string;
using std::ostream;
#include <stack>
using std::stack;

template <typename Element>
void swap(Element &e1, Element &e2)
{
	Element temp = e1;
	e1 = e2;
	e2 = temp;
}


template <typename Element, typename Compare>
void bubble_sort(Element *base, size_t asize, Compare compare)
{

	for (; asize > 1; asize--)
	{
		for (size_t i = 1; i < asize; i++)
		{
			if (compare(base[i - 1], base[i])>0)
			{
				swap(base[i - 1], base[i]);
			}
		}
	}

}

template <typename Element, typename Compare>
void selection_sort(Element *base, size_t asize, Compare compare)
{
	int min = 0;

	for (int i = 0; i < asize; i++)
	{
		min = i;
		for (int j = min + 1; j < asize; j++)
		{
			if (compare(base[min], base[j])>0)
			{
				min = j;
				//swap(base[i], base[j]);
			}
		}
		swap(base[min], base[i]);
	}
}

template <typename Element, typename Compare>
void insertion_sort(Element *base, size_t asize, Compare compare)
{
	for (int i = 1; i < asize; i++)
	{
		for (int j = i; j > 0; j--)
		{
			if (compare(base[j], base[j - 1]) < 0)
			{
				swap(base[j], base[j - 1]);
			}
			else
			{
				break;
			}
		}
	}
}

template <typename Element, typename Compare>
Element *find_middle(Element &e1, Element &e2, Element &e3, Compare compare)
{
	if (compare(e1, e2) > 0)
	{
		if (compare(e2, e3) > 0)
		{
			return &e2;
		}
		else
		{
			if (compare(e1, e3) > 0)
			{
				return &e3;
			}
			return &e1;
		}
	}

	if (compare(e2, e3) < 0)
	{
		return &e2;
	}
	else
	{
		if (compare(e1, e3) > 0)
		{
			return &e1;
		}
		return &e3;
	}
}

template <typename Element, typename Compare>
void quick_sort(Element *base, size_t asize, Compare compare)
{
	if (asize <= 1)
	{
		return;
	}
	int last = asize - 1;

	Element *pivot = find_middle(base[0], base[asize / 2], base[last], compare);
	swap(*pivot, base[last]);

	int more = -1;
	int less = last;

	while (more < less)
	{
		for (more++; more < last; more++)
		{
			if (compare(base[more], base[last])>0)
			{
				break;
			}
		}

		for (less--; less >= 0; less--)
		{
			if (compare(base[less], base[last]) < 0)
			{
				break;
			}
		}

		if (more < less)
		{
			swap(base[more], base[less]);
		}
	}

	swap(base[more], base[last]);
	quick_sort(base, more, compare);
	quick_sort(base + more + 1, asize - 1 - more, compare);
}

template <typename Element, typename Compare>
void QuickSort_nr(Element* base, size_t asize, Compare compare)
{
	Element t;
	Element *v;
	size_t i, j;
	size_t l, r; // 스택에 저장할 공간의 정보 (non-recursive 필수);;
	stack<size_t> stack;
	l = 0;
	r = asize - 1;
	stack.push(r);
	stack.push(l);
	

	while (!stack.empty())
	{
		l = stack.top();
		stack.pop();
		r = stack.top();
		stack.pop();

		v = find_middle(base[l], base[r / 2], base[r], compare);
		swap(*v, base[r]);

		if (r > l) // 종료조건 r-l+1은 구간의 길이,, 중요
		{
			t = base[r];
			i = l;
			j = r-1;
			while (i<=j)
			{
				for (; i < r; i++)
				{
					if (compare(base[i], t) > 0)
						break;
				}
				for (; j >= l; j--)
				{
					if (compare(base[j], t) < 0)
						break;
				}
				if(i<j)
				{
					swap(base[i], base[j]);
				}
			}
			if (i>j) {
				swap(base[i], base[r]);
				stack.push(r);
				stack.push(i + 1);
				stack.push(i - 1);
				stack.push(l);
			}
		}
	}
}

template <typename Element, typename Compare>
void Radix_sort(Element* base, size_t asize, Compare compare)
{
	Element arr1[10] = { 0, }, arr2[10], temp;
	size_t ain[10] = { 0, }, bin[10] = { 0, };

	temp = base[0];
	while (temp > 1)
	{
		for (int i = 0; i < asize; i++)
		{
			if (temp / 100 >= 1)
				arr2[i] = base[i] % 10;
			else if (temp / 10 >= 1 && temp / 10 < 10)
				arr2[i] = (base[i] / 10)%10;
			else if ( 0 <= temp / 10 && temp / 10 < 1)
				arr2[i] = base[i] / 100;

		}
		for (int i = 0; i < asize; i++)
		{
			ain[arr2[i]]++;
		}

		bin[0] = ain[0];
		for (int i = 1; i < asize; i++)
		{
			bin[i] = bin[i - 1] + ain[i];
		}

		for (int j = asize - 1; j >= 0; j--)
		{
			arr1[bin[arr2[j]] - 1] = base[j];
			bin[arr2[j]]--;
		}

		for (int i = 0; i < asize; i++)
		{
			base[i] = arr1[i];
		}

		for (int i = 0; i < 10; i++)
		{
			ain[i] = bin[i] = 0;
		}
		temp = temp/10;
	}
}

template <typename Element, typename Compare>
void merge_sort(Element *base, int asize, Compare compare)
{
	if (asize <= 1)
	{
		return;
	}
	int half_one = asize / 2;
	int half_two = asize - asize / 2;
	Element *rbase = base + half_one;
	merge_sort(base, half_one, compare);
	merge_sort(rbase, half_two, compare);

	int index1 = 0; // 앞쪽 배열의 원소를 차례대로 접근할 변수
	int index2 = 0; // 뒷쪽 배열의 원소를 차례대로 접근할 변수
	Element *tbase = new Element[asize];

	while ((index1 < half_one) && (index2 < half_two))
	{
		if (compare(base[index1], rbase[index2]) <= 0)
		{
			tbase[index1 + index2] = base[index1];
			index1++;
		}
		else
		{
			tbase[index1 + index2] = rbase[index2];
			index2++;
		}
	}
		if (index1 == half_one)
		{
			while (index2 < half_two)
			{
				tbase[index1 + index2] = rbase[index2];
				index2++;
			}
		}
		else
		{
			while (index1 < half_one)
			{
				tbase[index1 + index2] = base[index1];
				index1++;
			}
		}

		for (int i = 0; i < asize; i++)
		{
			base[i] = tbase[i];
		}
		delete[] tbase;
}

#define LEFT_CHILD(x) (2*x+1)
#define RIGHT_CHILD(x) (2*x+2)
#define PARENT(x) ((x-1)/2)

template <typename Element, typename Compare>
void heap_sort(Element *base, int asize, Compare compare)
{
	init_heap(base, asize, compare);
	while (asize > 1)
	{
		swap(base[0], base[asize - 1]);
		asize--;
		make_heap(base, asize, compare);
	}
}

template <typename Element, typename Compare>
void init_heap(Element *base, int asize, Compare compare)
{
	int pa = 0;

	for (int now = 1; now < asize; now++)
	{
		
		while (now > 0)
		{
			pa = PARENT(now);

			if (compare(base[now], base[pa]) > 0)
			{
				swap(base[now], base[pa]);
				now = pa;
			}
			else
			{
				break;
			}
		}
	}
}

template <typename Element, typename Compare>
void make_heap(Element *base, int asize, Compare compare)
{
	int now = 0;
	int mp = 0;

	while (LEFT_CHILD(now) < asize)
	{
		mp = findmaxindex(base, asize, compare, now);
		if (now == mp)
		{
			break;
		}
		swap(base[now], base[mp]);
		now = mp;
	}
}

template <typename Element, typename Compare>
int findmaxindex(Element *base, int asize, Compare compare, int now)
{
	int lc = LEFT_CHILD(now);
	int rc = RIGHT_CHILD(now);

	if (lc >= asize)
	{
		return now;
	}

	if (rc >= asize)
	{
		if (compare(base[now], base[lc]) < 0)
		{
			return lc;
		}
		return now;
	}

	if (compare(base[now], base[lc]) < 0)
	{
		if (compare(base[lc], base[rc]) > 0)
		{
			return lc;
		}
		return rc;
	}

	if (compare(base[now], base[rc]) > 0)
	{
		return now;
	}
	return rc;
}

int CompareInt(int a, int b)
{
	return a - b;
}


class Stu
{
	int num;
	string name;
public:
	Stu(int num, string name) :num(num), name(name)
	{

	}
	int GetNum() const
	{
		return num;
	}
	string GetName() const
	{
		return name;
	}
	int Compp(Stu *stu2)
	{
		return strcmp(this->name.c_str(), stu2->GetName().c_str());
	}
};

int CompareStuByNum(Stu *stu1, Stu *stu2)
{
	return stu1->GetNum() - stu2->GetNum();
}

int CompareStuByName(Stu *stu1, Stu *stu2)
{
	return stu1->Compp(stu2);
}

extern ostream &operator<<(ostream &os, const Stu stu)
{
	printf("%s", stu.GetName().c_str());
	return os;
}

extern ostream &operator<<(ostream &os, const Stu *stu)
{
	printf("%s", stu->GetName().c_str());
	return os;
	//return os << *stu;
}