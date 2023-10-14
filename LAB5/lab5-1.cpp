#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;
typedef int itemType;

int data_cmp = 0, data_move = 0;

class MakeHeap {
private:
   itemType *a;
   int N;
public:
   MakeHeap(int max) {
      a = new itemType[max];
      N = 0;
   }
   ~MakeHeap() {
      delete a;
   }
   void swap(itemType a[], int i, int j) {
      int temp;
      temp = a[j];
      a[j] = a[i];
      a[i] = temp;
      data_move += 3;
   }
   void make_heap(itemType a[], int root, int last_node) {
      int parent, leftson, rightson, son;
      itemType root_value;
      parent = root;
      root_value = a[root];
      data_move++;
      leftson = 2 * parent + 1;
      rightson = leftson + 1;
      while (leftson <= last_node) {
         if (rightson <= last_node && ++data_cmp && a[leftson] < a[rightson]) {
            son = rightson;
         }
         else
            son = leftson;
         if (++data_cmp && root_value < a[son]) {
            a[parent] = a[son];
            data_move++;
            parent = son;
            leftson = parent * 2 + 1;
            rightson = leftson + 1;
         }
         else
            break;
      }
      a[parent] = root_value;
      data_move++;
   }

   void heapsort(itemType a[], int N) {
      int i;
      for (i = N / 2; i >= 1; i--)
         make_heap(a, i - 1, N - 1);
      for (i = N - 1; i >= 1; i--) {
         swap(a, 0, i);
         make_heap(a, 0, i - 1);
      }
   }
};

int main()
{
   int N;
   cin >> N;
   int* A = new int[N];
   int* B = new int[N];
   int* C = new int[N];
   int** tmp = new int*[N];
   int num = N;
   MakeHeap heap(N);

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
   heap.heapsort(A, N);
   A_info[0] = data_cmp, A_info[1] = data_move;

   data_cmp = 0; data_move = 0;
   heap.heapsort(B, N);
   B_info[0] = data_cmp, B_info[1] = data_move;

   data_cmp = 0; data_move = 0;
   heap.heapsort(C, N);
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