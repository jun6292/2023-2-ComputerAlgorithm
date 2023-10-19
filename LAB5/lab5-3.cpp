#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;
typedef int itemType;

typedef struct node *node_pointer;
struct node {
   itemType value;
   node_pointer next;
};

node_pointer TABLE[10], x, z, temp;
int data_cmp = 0, data_move = 0;

void radix_sort(itemType *a, int n) {
   int i, j, cnt, radix, radix_mod = 10, cipher = 0;
   i = n;
   while (i > 0) {
      i = i / 10;
      cipher++;   // 입력 데이터의 자리수
   }
   for (i = 0; i < cipher; i++) {
      for (j = 0; j < n; j++) {
         cnt = 0;
         radix = (a[j] % radix_mod) / (radix_mod / 10);
         /* radix_mod = 10 이면 radix는 a[j]의 일의 자리수 
         radix_mod = 100 이면 radix는 a[j]의 십의 자리수 */
         temp = new node;
         temp -> value = a[j];
         data_move++;
         temp -> next = z;
         if (TABLE[radix] == z) {
            TABLE[radix] = temp;
         }
         else {
            x = TABLE[radix];
            while (x -> next != z) {
               x = x -> next;
            }
            x -> next = temp;
         }
      }

      for (j = 0; j < 10; j++) {
         if (TABLE[j] != z) {
            x = TABLE[j];
            while(x != z) {
               a[cnt++] = x -> value;
               data_move++;
               temp = x;
               x = x -> next;
               delete temp;
            }
         }
         TABLE[j] = z;
      }
      radix_mod *= 10;
   }
}

int main()
{
   int N;
   cin >> N;
   int* A = new int[N];
   int* B = new int[N];
   int* C = new int[N];
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

   for (int i = 0; i < N; i++) {
      C[i] = (1 + rand() % N);
   }

   int A_info[2], B_info[2], C_info[2];
   radix_sort(A, N);
   A_info[0] = data_cmp, A_info[1] = data_move;

   data_cmp = 0; data_move = 0;
   radix_sort(B, N);
   B_info[0] = data_cmp, B_info[1] = data_move;

   data_cmp = 0; data_move = 0;
   radix_sort(C, N);
   C_info[0] = data_cmp, C_info[1] = data_move;

   cout << "SortedData_A: ";
   for(int i = 0; i < 20; i++)
      cout << A[i] << ' ';

   cout << "\nSortedData_B: ";
   for(int i = 0; i < 20; i++)
      cout << B[i] << ' ';

   cout << "\nSortedData_C: ";
   for(int i = 0; i < 20; i++)
      cout << C[i] << ' ';

   cout << '\n';
   cout << "Compare_Cnt_A " << A_info[0] << ", DataMove_Cnt_A " << A_info[1] << '\n';
   cout << "Compare_Cnt_B " << B_info[0] << ", DataMove_Cnt_B " << B_info[1] << '\n';
   cout << "Compare_Cnt_C " << C_info[0] << ", DataMove_Cnt_C " << C_info[1] << '\n';

   return 0;
}