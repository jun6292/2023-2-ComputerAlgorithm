#include <iostream>

using namespace std;
typedef int itemType;

int weight_bubble = 0, weight_insertion = 0, weight_shell = 0;
// 수정된 bubble sort
bool bubble(bool sorted, itemType *a, int n) {
    int temp;
    if (*(a - 1) > *a) {    // 비교
        temp = *a;    // 가벼운 것을 먼저 이동
        weight_bubble += temp;
        *a = *(a - 1);
        weight_bubble += *(a - 1);
        *(a - 1) = temp;
        weight_bubble += temp;
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

void insertion_sort(itemType a[], int n) { 
    int i, j;
    itemType v;
	for (i = 1; i < n; i++) {
		v = a[i];
        weight_insertion += v;
		j = i - 1;
		while (a[j] > v && j >= 0) {   // 정렬할 데이터 비교
			a[j + 1] = a[j];    // 데이터 이동
            weight_insertion += a[j];
			j--;
		}
		a[j + 1] = v;   // 데이터 이동 
        weight_insertion += v;
	}
}

void shell_sort(itemType a[], int n) { 
    int i, j, h;
    itemType v;
    h = 1;
    do {
        h = 3 * h + 1;
    } while (h < n);
    do {
        h = h / 3;
        for (i = h; i < n; i++) {
            v = a[i];   // 데이터 이동
            weight_shell += a[i];
            j = i;
            while (a[j - h] > v) {   // 비교
                a[j] = a[j - h];    // 데이터 이동
                weight_shell += a[j - h];
                j -= h;
                if (j <= h - 1)
                    break;
            }
            a[j] = v;   // 데이터 이동
            weight_shell += v;
        }
    } while (h > 1);
}

int main()
{
    int N;
    cin >> N;
    if (N <= 500)
        exit(0);

    int* bubble = new int[N];
    int* insertion = new int[N];
    int* shell = new int[N];

    int num = N;
    for (int i = 0; i < N; i++) {
        bubble[i] = num;
        insertion[i] = num;
        shell[i] = num;
        num--;
    }

    bubble_sort(bubble, N);
    insertion_sort(insertion, N);
    shell_sort(shell, N);

    cout << "Insertion Sort : " << weight_insertion << '\n';
    cout << "Bubble Sort : " << weight_bubble << '\n';
    cout << "Shell Sort : " << weight_shell << '\n';

    return 0;
}