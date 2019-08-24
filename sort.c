#include <stdio.h>
#include <stdlib.h>
#include "sort.h"



void InsertSort(int *src, int n)//ֱ�Ӳ�������(�����㹻Сʱ����,����Խ�������Խ��)���ȶ���
{
	int i, j;
	int tmp;
	for (i = 1; i < n; i++)
	{
		tmp = src[i];
		for (j = i; j>0 && src[j - 1]>tmp; j--)
		{
			src[j] = src[j - 1];
		}
		src[j] = tmp;
	}
}
void ShelSort(int *src, int n)//ϣ�����򣺲���������Ż����Ȳ���������΢��һ�㣨���ȶ���
{
	int i, j, k;
	int gap, tmp;

	for (gap = n / 2; gap; gap /= 2)
	{
		for (k = 0; k < gap; k++)
		{
			for (i = gap + k; i < n; i += gap)
			{
				tmp = src[i];

				for (j = i; j >= gap && src[j - gap] > tmp; j -= gap)
				{
					src[j] = src[j - gap];
				}

				src[j] = tmp;
			}
		}
	}
}
//�鲢����Ҫ����һ����ʱ�Ŀռ�(�൱�ڶ������ĺ���)
void dealMergeSort(int *src, int *tmp, int start, int end)//�����Լ��ĺ���ʵ��
{
	if (start >= end)
	{
		return;
	}

	int mid = (start + end) / 2;
	dealMergeSort(src, tmp, start, mid);
	dealMergeSort(src, tmp, mid + 1, end);

	int a = start;
	int b = mid + 1;
	int c = start;
	while (a <= mid && b <= end)
	{
		if (src[a] < src[b])
		{
			tmp[c] = src[a];
			a++;
		}
		else
		{
			tmp[c] = src[b];
			b++;
		}
		c++;
	}

	for (; a <= mid; a++, c++)
	{
		tmp[c] = src[a];
	}

	for (; b <= end; b++, c++)
	{
		tmp[c] = src[b];
	}

	int i;
	for (i = start; i <= end; i++)
	{
		src[i] = tmp[i];
	}
}

void MergeSort(int *src, int n)//�鲢��������ӿ�
{
	int *tmp = (int *)malloc(n*sizeof(int));
	dealMergeSort(src, tmp, 0, n - 1);
	free(tmp);
}
//�����൱�ڶ�������ǰ�����
void swapArgs(int *pa, int *pb)
{
	int tmp;
	tmp = *pa;
	*pa = *pb;
	*pb = tmp;
}
int HoareWay(int *src, int start, int end)//���ŵ�hoare��
{
	int a = start + 1, b = end - 2;
	int mid = (start + end) / 2;
	if (src[start] > src[mid])
	{
		swapArgs(src + start, src + mid);
	}
	if (src[mid] > src[end])
	{
		swapArgs(src + mid, src + end);
	}
	if (src[start] > src[mid])
	{
		swapArgs(src + start, src + mid);
	}
	if (end - start <= 2)
	{
		return mid;
	}
	swapArgs(src + mid, src + end - 1);
	while (a <= b)
	{
		while (src[a] <= src[end-1] && a<end-1)
		{
			a++;
		}

		while (src[b] >= src[end-1] && b>1)
		{
			b--;
		}
		if (a == b && (a == end-1 || a == 1))
		{
			break;
		}
		if (a < b)
		{
			swapArgs(src + a, src + b);

		}
	}
	swapArgs(src + a, src + end - 1);
	return a;
}
int doublePointerWay2(int *src, int start, int end)
//1.��������м��㵱�����ӵ�
//2.�����ӵ������һ��end��Ӧ�����ֽ�����ʵ�ֱ�������
//3.��ָ��a��ָ��b�ֱ�ʼ��ǰ���󣬴Ӻ�ǰ������ָ��aѰ�ұ����ӵ������֣�ָ��bѰ�ұ����ӵ�С�����֣��ҵ���֮��ͽ���
{
	int a = start, b = end - 1;
	int mid = (start + end) / 2;
	swapArgs(src + mid, src + end);
	while (a<=b)
	{
		while (src[a] <= src[end] && a<end)
		{
			a++;
		}
		
		while (src[b]>=src[end] && b>0)
		{
			b--;
		}
		if (a == b && (a == end || a == 0))
		{
			break;
		}
		if (a < b)
		{
			swapArgs(src + a, src + b);

		}
	}
	swapArgs(src + a, src + end);
	return a;
}
int digWay(int *src, int start, int end)//ʹ���ڿӷ�ʵ�ֿ���
{
	int a = start;
	int b = end;
	int tmp = src[start];
	while (1)
	{
		while (src[b] >= tmp && b>start)
		{
			b--;
		}
		if (a < b)
		{
			src[a] = src[b];
		}
		else
		{
			src[a] = tmp;
			return a;
		}
		while (src[a] <= tmp && a<end)
		{
			a++;
		}
		if (a < b)
		{
			src[b] = src[a];
		}
		else
		{
			src[b] = tmp;
			return b;
		}	
	}
}
int doublePointerWay1(int *src, int start, int end)//˫ָ�뷨
{
	int a = start;
	int b = end;
	int flag = 1;
	while (src[b] > src[a])
	{
		b--;
	}
	while (a<b)
	{
		swapArgs(src + b, src + a);
		flag = !flag;
		while (src[b] >= src[a])
		{
			flag ? a++ : b--;
		}
		
	}
	return flag ? b : a;
}
void dealQuickSort(int *src, int start, int end)
{
	int mid;
	if (start + 8 <end)
	{
		mid = HoareWay(src, start, end);
		dealQuickSort(src, start, mid - 1);
		dealQuickSort(src, mid + 1, end);
	}
	else
	{
		InsertSort(src + start, end - start + 1);
	}
}
void QuickSort(int *src, int n)
{
	dealQuickSort(src, 0, n - 1);
}
//void QuickSortNonR(int *src, int n)��������ķǵݹ��㷨
//{
//	int start = 0, end = n - 1;
//	Queue qu;
//	QueuePush(&qu, start);
//	QueuePush(&qu, end);
//
//	QueueInit(&qu);
//	while (!QueueIsEmpty(&qu))
//	{
//		start = QueueTop(&qu);
//		QueuePop(&qu);
//		end = QueueTop(&qu);
//		QueuePop(&qu);
//		mid = HoareWay(src, start, end);
//
//		if (start < mid)
//		{
//			QueuePush(&qu, start);
//			QueuePush(&qu, mid);
//		}
//		if (mid + 1 < end)
//		{
//			QueuePush(&qu, mid+1);
//			QueuePush(&qu, end);
//		}
//
//	}
//	QueueDestory(&qu);
//}
