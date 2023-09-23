#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;
typedef int itemType;

int compare_cnt = 0, move_cnt = 0;
void insertion_sort(itemType a[], int n) { 
    int i, j;
    itemType v;
	for (i = 1; i < n; i++) {
		v = a[i];
        move_cnt++;   // 이동
		j = i - 1;
		while (a[j] > v && j >= 0) {   // 정렬할 데이터 비교
            ++compare_cnt;
			a[j + 1] = a[j];    // 데이터 이동
            move_cnt++;
			j--;
		}
		a[j + 1] = v;   // 데이터 이동 
        move_cnt++;
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
        delete [] tmp[i];
    delete [] tmp;

    int compare_cnt_A, compare_cnt_B, move_cnt_A, move_cnt_B;
    // 배열 A, B가 정렬되고 데이터 비교 연산 및 자료 이동 연산 횟수 정보가 저장됨.
    insertion_sort(A, N);
    compare_cnt_A = compare_cnt;
    move_cnt_A = move_cnt;

    compare_cnt = 0, move_cnt = 0;
    insertion_sort(B, N);
    compare_cnt_B = compare_cnt;
    move_cnt_B = move_cnt;

    cout << "SortedData_A: ";
    for(int i = 0; i < 20; i++)
        cout << A[i] << ' ';
    cout << "\nSortedData_B: ";
    for(int i = 0; i < 20; i++)
        cout << B[i] << ' ';
    cout << '\n';
    cout << "Compare_Cnt_A " << compare_cnt_A << ", DataMove_Cnt_A " << move_cnt_A << '\n';
    cout << "Compare_Cnt_B " << compare_cnt_B << ", DataMove_Cnt_B " << move_cnt_B << '\n';

    return 0;
}