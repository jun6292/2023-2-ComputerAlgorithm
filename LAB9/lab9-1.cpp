#include <iostream>
#define Nmax 100
using namespace std;
typedef struct point itemType;

struct point {
    char c;
    int x, y;
    float tangent;
};
struct line {
    struct point p1, p2;
};
struct point polygon[Nmax];
int cal_cnt = 0, cmp_cnt = 0;   // 계산 횟수, 비교 횟수

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
        itemType temp;
        temp = a[j];
        a[j] = a[i];
        a[i] = temp;
    }
    void make_heap(itemType a[], int root, int last_node) {
        int parent, leftson, rightson, son;
        itemType root_value;
        parent = root;
        root_value = a[root];
        leftson = 2 * parent + 1;
        rightson = leftson + 1;
        while (leftson <= last_node) {
            if (rightson <= last_node && ++cmp_cnt && a[leftson].tangent < a[rightson].tangent) {
                son = rightson;
            }
            else
                son = leftson;
            if (++cmp_cnt && root_value.tangent < a[son].tangent) {
                a[parent] = a[son];
                parent = son;
                leftson = parent * 2 + 1;
                rightson = leftson + 1;
            }
            else
                break;
        }
        a[parent] = root_value;
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

float ComputeAngle(struct point p1, struct point p2) {
    int dx, dy, ax, ay;
    float t;
    dx = p2.x - p1.x;
    ax = abs(dx);
    dy = p2.y - p1.y;
    ay = abs(dy);
    t = (ax + ay == 0) ? 0 : (float) dy / (ax + ay);
    if (dx < 0)
        t = 2 - t;
    else if (dy < 0)
        t = 4 + t;
    cal_cnt++;
    return t * 90.0;
}

int main()
{
    int N;
    cin >> N;
    MakeHeap h(N);

    for(int i = 0; i < N; i++) {
        cin >> polygon[i].c >> polygon[i].x >> polygon[i].y;
    }

    int x, y, minIdx, minX = 100, minY = 100;
    for (int i = 0; i < N; i++) {
        x = polygon[i].x;
        y = polygon[i].y;
        if ((minY > y) || (minY == y && minX > x)) {
            minIdx = i;
            minX = x;
            minY = y;
        }
    }

    for(int i = 0; i < N; i++) {
        polygon[i].tangent = ComputeAngle(polygon[minIdx], polygon[i]);
    }

    h.heapsort(polygon, N);
    polygon[N] = polygon[0];

    cout << "다형각이 만들어지는 순서 : ";
    for (int i = 0; i < N; i++) {   
        if(i == N - 1) {
            cout << polygon[i].c;
            break;
        }
        cout << polygon[i].c << " - ";
    }
    cout << '\n';
    cout << cal_cnt << " (수평각 계산 횟수)\n" << cmp_cnt << " (각의 비교 횟수)" << endl;
}