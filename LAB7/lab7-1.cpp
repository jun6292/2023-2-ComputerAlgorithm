#include <iostream>
#include <time.h>
#include <stdlib.h>
#define infoNIL 0
#define itemMIN -1
#define black 0
#define red 1
typedef int itemType;
typedef double infoType;
using namespace std;
double insert_data_cmp = 0, search_data_cmp = 0;

class RBtree {
private:
   struct node {
      itemType key, tag;
      infoType Info;
      struct node *l, *r;
      node(itemType k, infoType i, itemType t, struct node *ll, struct node *rr) {
         key = k;
         Info = i;
         tag = t;
         l = ll;
         r = rr;
      }
   };
   struct node *head, *tail, *x, *p, *g, *gg, *z;
public:
   RBtree(int max) {
      z = new node(0, infoNIL, black, 0, 0);
      z -> l = z;
      z -> r = z;
      head = new node(itemMIN, infoNIL, black, z, z);
   }
   void insert(itemType k, infoType info) {
      x = head; p = head; g = head;
      while (x != z) {
         gg = g; g = p; p = x;
         insert_data_cmp++;
         x = (k < x -> key) ? x -> l : x -> r;
         if (x -> l -> tag && x -> r -> tag)
            split(k);
      }
      x = new node(k, info, red, z, z);
      if (k < p -> key)
         p -> l = x;
      else
         p -> r = x;
      insert_data_cmp++;
      split(k);
      head -> r -> tag = black;
   }
   struct node* rotate(itemType k, struct node *y) {
      struct node *high, *low;
      insert_data_cmp++;
      high = (k < y -> key) ? y -> l : y -> r; 
      insert_data_cmp++;
      if (k < high -> key) { 
         low = high -> l; 
         high -> l = low -> r; 
         low -> r = high; 
      } 
      else { 
         low = high -> r; 
         high -> r = low -> l;
         low -> l = high; 
      }
      insert_data_cmp++;
      if (k < y -> key) 
         y -> l = low; 
      else 
         y -> r = low; 
      return low; 
   }
   void split(itemType k) {
      x -> tag = red; 
      x -> l -> tag = black; 
      x -> r -> tag = black; 
      if (p -> tag) { 
         g -> tag = red; 
         if (++insert_data_cmp && k < g -> key != k < p -> key) 
            p = rotate(k, g); 
         x = rotate(k, gg); 
         x -> tag = black; 
      } 
   }
   infoType search(itemType k) { // Red-Black Tree의 탐색 기능
      struct node *x = head -> r; 
      z -> key = k;
      while (++search_data_cmp && k != x->key){
         x = (k < x->key) ? x->l : x->r; 
         ++search_data_cmp;
      }
      return x -> Info; 
   }
};

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
   infoType BSTsearch(itemType v) {
      struct node *x = head -> r;
      z -> key = v;
      while (++search_data_cmp && v != x -> key) {
         x = (v < x -> key) ? x -> l : x -> r;
         ++search_data_cmp;
      }
      return x -> info;
   }
   void BSTinsert(itemType v, infoType info) {
      struct node *p, *x;
      p = head;
      x = head -> r;
      while (x != z) {
         p = x;
         insert_data_cmp++;
         x = (v < x -> key) ? x -> l : x -> r;
      }
      x = new node(v, info, z, z);
      if (v < p -> key)
         p -> l = x;
      else
         p -> r = x;
      insert_data_cmp++;
   }
   void traverse(BST *T1) {
      traverse(head -> r, T1);
   }
   void traverse(struct node *t, BST *T1) {
      if (t != z) {
         traverse(t -> l, T1);
         T1 -> BSTinsert(t -> key, t -> key);
         traverse(t -> r, T1);
      }
   }
   void traverse(RBtree *T3) {
      traverse(head -> r, T3);
   }
   void traverse(struct node *t, RBtree *T3) {
      if (t != z) {
         traverse(t -> l, T3);
         T3 -> insert(t -> key, t -> key);
         traverse(t -> r, T3);
      }
   }
};

int main()
{
   int N;
   cin >> N;
   int* A = new int[N];
   int** tmp = new int*[N];
   BST T1(N);
   BST T2(N);
   RBtree T3(N);
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
   double T1_insert_data_cmp = insert_data_cmp;
   insert_data_cmp = 0;
   
   for (int i = 0; i < N; i++) {
      T1.BSTsearch(A[i]);
   }
   double T1_search_data_cmp = search_data_cmp;
   search_data_cmp = 0;
   
   T1.traverse(&T2); // 중위순회로 T2 구축
   double T2_insert_data_cmp = insert_data_cmp;
   insert_data_cmp = 0;
   for (int i = 0; i < N; i++) {
      T2.BSTsearch(A[i]);
   }
   double T2_search_data_cmp = search_data_cmp;
   search_data_cmp = 0;

   T1.traverse(&T3); // 중위 순회로 T3 구축
   double T3_insert_data_cmp = insert_data_cmp;
   for (int i = 0; i < N; i++) {
      T3.search(A[i]);
   }
   double T3_search_data_cmp = search_data_cmp;

   cout << T1_insert_data_cmp / N << " (T1의 구축 시 평균 비교 회수)\n";
   cout << T2_insert_data_cmp / N << " (T2의 구축 시 평균 비교 회수)\n";
   cout << T3_insert_data_cmp / N << " (T3의 구축 시 평균 비교 회수)\n";

   cout << T1_search_data_cmp / N << " (T1의 평균 탐색 비교 회수)\n";
   cout << T2_search_data_cmp / N << " (T2의 평균 탐색 비교 회수)\n";
   cout << T3_search_data_cmp / N << " (T3의 평균 탐색 비교 회수)\n";
   
   return 0;
}