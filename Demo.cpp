#include "Sort.h"


void main()
{
	Stu *arr[10];
	arr[0] = new Stu(33, "������");
	arr[1] = new Stu(13, "ȫ�浿");
	arr[2] = new Stu(33, "��������");
	arr[3] = new Stu(37, "����");
	arr[4] = new Stu(11, "����ȣ");
	arr[5] = new Stu(92, "õ�ȼ�");
	arr[6] = new Stu(81, "�ھƻ�");
	arr[7] = new Stu(33, "������");
	arr[8] = new Stu(66, "����");
	arr[9] = new Stu(57, "������");
	
	int a[10] = { 442, 335 , 214 ,591, 972, 422, 209, 948, 650, 136 };


	quick_sort(arr, 10, CompareStuByNum);

	/*for (int i = 0; i < 10; i++)
	{
		cout << a[i] << endl;
	}*/
	
	for (int i = 0; i < 10; i++)
	{
		cout << arr[i]->GetNum() << ":" << arr[i]->GetName().c_str()  << endl;
	}
	
	for (int i = 0; i < 10; i++)
	{
		delete arr[i];
	}
}