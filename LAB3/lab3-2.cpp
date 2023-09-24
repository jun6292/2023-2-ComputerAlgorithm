#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;
typedef int itemType;

int* shell_sort(itemType a[], int n) { 
    int i, j, h;
    itemType v;
    int* info = new int[2];
    info[0] = 0;    // data move count
    info[1] = 0;    // data compare count

    h = 1;
    do {
        h = 3 * h + 1;
    } while (h < n);
    do {
        h = h / 3;
        for (i = h; i < n; i++) {
            v = a[i];   // 이동
            info[0]++;
            j = i;
            while (++info[1] && (a[j - h] > v)) {   // 비교
                a[j] = a[j - h];    // 이동
                info[0]++;
                j -= h;
                if (j <= h - 1)
                    break;
            }
            a[j] = v;   // 이동
            info[0]++;
        }
    } while (h > 1);

    return info;
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
    int* A_info = shell_sort(A, N);
    int* B_info = shell_sort(B, N);

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