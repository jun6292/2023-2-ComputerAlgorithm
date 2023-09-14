#include <iostream>
#include <set>
#include <map>
#include <random>
using namespace std;

int main()
{
    random_device rd;   // 난수 생성 엔진 초기화
    mt19937 gen(rd());  // 메르센 트위스터를 사용한 난수 생성
    uniform_int_distribution<int> dis(1, 50);   // 1에서 50까지의 균등한 난수열 생성
    set<int> A, B, union_set, intersection_set;
    map<int, int> mapped;
    
    int N, M;
    cin >> N >> M;

    while (A.size() != N) {
        A.insert(dis(gen));
    }
    
    while (B.size() != M) {
        B.insert(dis(gen));
    }

    cout << "집합 A - ";
    for (auto it = A.begin(); it != A.end(); it++) {
        if (it != A.begin())
            cout << ", ";
        cout << *it;
        mapped[*it]++;
        union_set.insert(*it);
    }
    cout << '\n';

    cout << "집합 B - ";
    for (auto it = B.begin(); it != B.end(); it++) {
        if (it != B.begin())
            cout << ", ";
        cout << *it;
        mapped[*it]++;
        union_set.insert(*it);
    }
    cout << '\n';

    cout << "합집합 - ";
    for (auto it = union_set.begin(); it != union_set.end(); it++) {
        if (it != union_set.begin())
                cout << ", ";
            cout << *it;
    }
    cout << '\n';

    for (auto it = mapped.begin(); it != mapped.end(); it++) {
            if (it->second > 1)    // 겹치는 원소가 있었다.
                intersection_set.insert(it->first);
        }
    cout << "교집합 - ";
    
    if (intersection_set.empty())
        cout << "교집합이 존재하지 않습니다.";
    else {
        for (auto it = intersection_set.begin(); it != intersection_set.end(); it++) {
            if (it != intersection_set.begin())
                cout << ", ";
            cout << *it;
        }
    }
    cout << '\n';
}