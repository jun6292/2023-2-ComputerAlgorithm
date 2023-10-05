#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
typedef int itemType;

int data_cmp = 0, data_move = 0;
inline void swap(itemType a[], int i, int j) {
    itemType tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
    data_move += 3;
}

int partition(itemType a[], int left, int right) {
    int i, j;
    itemType v;
    if (right > left) {
        v = a[left];   // 피벗
        i = left + 1;
        j = right;
        while (true) {
            while (i <= right && ++data_cmp && (a[i] < v))
                i++;
            while (j > left && ++data_cmp && (a[j] > v))
                j--;
            if (i >= j)
                break;
            swap(a, i, j);
        }
        swap(a, left, j);
    }
    return j;
}

void quick_sort(itemType a[], int left, int right) {
    int j;
    if (right > left) {
        j = partition(a, left, right);
        quick_sort(a, left, j - 1);
        quick_sort(a, j + 1, right);
    }
}

int main()
{
    int N;
    cin >> N;
    if (N <= 10000)
        exit(0);

    int* A = new int[N];
    int* B = new int[N];
    int** tmp = new int*[N];
    int num = N;

    for (int i = 0; i < N; i++) {   // A 배열 만들기 - 내림차순으로 졍렬된 배열
        A[i] = num--;
    }

    srand((unsigned)time(NULL));
    for (int i = 0; i < N; i++) {
        tmp[i] = new int[2];
        tmp[i][0] = (1 + rand() % N);
        tmp[i][1] = i + 1;
    }

    int temp1, temp2;
    for (int i = 0; i < N; i++) {
		for (int j = 0; j < (N - i) - 1; j++) {
			if (tmp[j][0] > tmp[j + 1][0]) {
				temp1 = tmp[j][0];
				tmp[j][0] = tmp[j + 1][0];
				tmp[j + 1][0] = temp1;

                temp2 = tmp[j][1];
				tmp[j][1] = tmp[j + 1][1];
				tmp[j + 1][1] = temp2;
			}
		}
	}

    for (int i = 0; i < N; i++) {
        B[i] = tmp[i][1];
    }

    for (int i = 0; i < N; i++)
        delete [] tmp[i];
    delete [] tmp;

    int A_info[2], B_info[2];
    quick_sort(A, 0, N - 1);
    A_info[0] = data_cmp, A_info[1] = data_move;

    data_cmp = 0; data_move = 0;
    quick_sort(B, 0, N - 1);
    B_info[0] = data_cmp, B_info[1] = data_move;

    cout << "SortedData_A: ";
    for(int i = 0; i < 20; i++)
        cout << A[i] << ' ';
    cout << "\nSortedData_B: ";
    for(int i = 0; i < 20; i++)
        cout << B[i] << ' ';
    cout << '\n';
    cout << "Compare_Cnt_A " << A_info[0] << ", DataMove_Cnt_A " << A_info[1] << '\n';
    cout << "Compare_Cnt_B " << B_info[0] << ", DataMove_Cnt_B " << B_info[1] << '\n';

    return 0;
}