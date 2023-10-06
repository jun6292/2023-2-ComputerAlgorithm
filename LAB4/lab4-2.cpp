#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;
typedef int itemType;

itemType* sorted;
int data_cmp = 0, data_move = 0;

void merge(itemType a[], int left, int mid, int right) {
    int i, j, k, n;
    i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        if (++data_cmp && (a[i] <= a[j])) {
            sorted[k++] = a[i++];
            data_move++;
        }
        else {
            sorted[k++] = a[j++];
            data_move++;
        }
    }

    if (i > mid) {
        for (n = j; n <= right; n++) {
            sorted[k++] = a[n];
            data_move++;
        }
    }
    else {
        for (n = i; n <= mid; n++) {
            sorted[k++] = a[n];
            data_move++;
        }
    }
    // 정렬된 배열을 다시 원래의 배열에 복사
    for (n = left; n <= right; n++) {
        a[n] = sorted[n];
        data_move++;
    }
}

void merge_sort(itemType a[], int left, int right) {
    int mid;
    if (left < right) {
        mid = (left + right) / 2;
        merge_sort(a, left, mid);
        merge_sort(a, mid + 1, right);
        merge(a, left, mid, right);
    }
}

int main()
{
    int N;
    cin >> N;
    if (N <= 10000)
        exit(0);

    sorted = new itemType[N];
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
    merge_sort(A, 0, N - 1);
    A_info[0] = data_cmp, A_info[1] = data_move;

    data_cmp = 0; data_move = 0;
    merge_sort(B, 0, N - 1);
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