#include <iostream>
#include <time.h>
#include <stdlib.h>
#define infoNIL 0
#define itemMIN -1
typedef int itemType;
typedef double infoType;
using namespace std;
double data_cmp = 0;

class BST {
private:
   struct node {
      itemType key;
      infoType info;
      struct node *l, *r;
      node(itemType k, infoType i, struct node *ll, struct node *rr) {
         key = k;
         info = i;
         l = ll;
         r = rr;
      } // node 생성 시 초기값 부여 가능 
   };
   struct node *head, *z;  // z: List의 끝을 대표하는 node pointer - NULL에 해당
public:
   BST(int max) {
      z = new node(0, infoNIL, 0, 0);
      head = new node(itemMIN, infoNIL, z, z);
   }
   ~BST() {
      delete head;
      delete z;
   }
   infoType BSTsearch(itemType v);
   void BSTinsert(itemType v, infoType info);
};

infoType BST::BSTsearch(itemType v) {
   struct node *x = head -> r;
   z -> key = v;
   while (++data_cmp && v != x -> key) {
      x = (v < x -> key) ? x -> l : x -> r;
   }
   return x -> info;
}

void BST::BSTinsert(itemType v, infoType info) {
   struct node *p, *x;
   p = head;
   x = head -> r;
   while (x != z) {
      p = x;
      x = (v < x -> key) ? x -> l : x -> r;
   }
   x = new node(v, info, z, z);
   if (v < p -> key)
      p -> l = x;
   else
      p -> r = x;
}

int main()
{
   int N;
   cin >> N;
   int* A = new int[N];
   int** tmp = new int*[N];
   BST T1(N);

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
      A[i] = tmp[i][1];
   }

   for (int i = 0; i < N; i++)
      delete [] tmp[i];
   delete [] tmp;

   for (int i = 0; i < N; i++) {
      T1.BSTinsert(A[i], A[i]);
   }

   for (int i = 0; i < N; i++) {
      T1.BSTsearch(A[i]);
   }
   cout << "데이터 평균 비교 횟수: " << data_cmp / N << " (T1의 평균 비교 횟수)\n";

   return 0;
}