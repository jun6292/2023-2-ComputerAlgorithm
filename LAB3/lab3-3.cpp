#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;
typedef int itemType;

int data_cmp = 0, data_move = 0;
bool bubble(bool sorted, itemType *a, int n) {
    int temp;
    if (++data_cmp && *(a - 1) > *a) {    // 비교  
        temp = *(a - 1);    // 이동
        data_move++;
        *(a - 1) = *a;  // 이동
        data_move++;
        *a = temp;  // 이동
        data_move++;
        sorted = false;
    }
    return sorted;
}

void bubble_sort(itemType a[], int n) {
    int i;
    bool Sorted;
    Sorted = false;
    while (!Sorted) {
        Sorted = true;
        for (i = 1; i < n; i++) {
            Sorted = bubble(Sorted, &a[i], n);
        }
        n--;
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
    for (int i = 0; i < N; i++) {   // B 배열 만들기 - Hint
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
        delete[] tmp[i];
    delete[] tmp;

    // 배열 A, B가 정렬되고 데이터 비교 연산 및 자료 이동 연산 횟수 정보가 저장됨.
    int A_info[2] = {0, 0};
    bubble_sort(A, N);
    A_info[0] = data_move;
    A_info[1] = data_cmp;

    data_move = 0;
    data_cmp = 0;

    int B_info[2] = {0, 0};
    bubble_sort(B, N);
    B_info[0] = data_move;
    B_info[1] = data_cmp;

    cout << "SortedData_A: ";
    for(int i = 0; i < 20; i++)
        cout << A[i] << ' ';
    cout << "\nSortedData_B: ";
    for(int i = 0; i < 20; i++)
        cout << B[i] << ' ';
    cout << '\n';
    cout << "Compare_Cnt_A " << A_info[1] << ", DataMove_Cnt_A " << A_info[0] << '\n';
    cout << "Compare_Cnt_B " << B_info[1] << ", DataMove_Cnt_B " << B_info[0] << '\n';

    return 0;
}