#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;
typedef int itemType;

itemType *a, *b, *N;
int data_cmp = 0, data_move = 0;

void count_sort(itemType *a, itemType *b, itemType *N, int n, int k) {
   int i, j;
   for (i = 1; i <= k; i++)   
      N[i] = 0;
   for (i = 1; i <= n; i++)
      N[a[i]] = N[a[i]] + 1;
   for (i = 2; i <= k; i++)
      N[i] = N[i] + N[i - 1];
   for (j = n; j >= 1; j--) {
      b[N[a[j]]] = a[j];
      data_move++;
      N[a[j]] = N[a[j]] - 1;
   }
}

int main()
{
   int input;
   cin >> input;
   int k = input;
   b = new itemType[input];
   N = new itemType[input];

   int* A = new int[input];
   int* B = new int[input];
   int* C = new int[input];
   int** tmp = new int*[input];
   int num = input;

   for (int i = 0; i < input; i++) {   // A 배열 만들기 - 내림차순으로 졍렬된 배열
      A[i] = num--;
   }

   srand((unsigned)time(NULL));
   for (int i = 0; i < input; i++) {
      tmp[i] = new int[2];
      tmp[i][0] = (1 + rand() % input);
      tmp[i][1] = i + 1;
   }

   int temp1, temp2;
   for (int i = 0; i < input; i++) {
      for (int j = 0; j < (input - i) - 1; j++) {
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

   for (int i = 0; i < input; i++) {
      B[i] = tmp[i][1];
   }

   for (int i = 0; i < input; i++)
      delete [] tmp[i];
   delete [] tmp;

   for (int i = 0; i < input; i++) {
      C[i] = (1 + rand() % input);
   }

   int A_info[2], B_info[2], C_info[2];
   count_sort(A, b, N, input, k);
   A_info[0] = data_cmp, A_info[1] = data_move;

   cout << "SortedData_A: ";
   for(int i = 1; i <= 20; i++)
      cout << b[i] << ' ';

   data_cmp = 0; data_move = 0;
   count_sort(B, b, N, input, k);
   B_info[0] = data_cmp, B_info[1] = data_move;

   cout << "\nSortedData_B: ";
   for(int i = 1; i <= 20; i++)
      cout << b[i] << ' ';

   data_cmp = 0; data_move = 0;
   count_sort(C, b, N, input, k);
   C_info[0] = data_cmp, C_info[1] = data_move;
   
   cout << "\nSortedData_C: ";
   for(int i = 1; i <= 20; i++)
      cout << b[i] << ' ';

   cout << '\n';
   cout << "Compare_Cnt_A " << A_info[0] << ", DataMove_Cnt_A " << A_info[1] << '\n';
   cout << "Compare_Cnt_B " << B_info[0] << ", DataMove_Cnt_B " << B_info[1] << '\n';
   cout << "Compare_Cnt_C " << C_info[0] << ", DataMove_Cnt_C " << C_info[1] << '\n';

   return 0;
}