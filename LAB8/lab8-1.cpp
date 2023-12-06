#include <iostream>
#include <string>
using namespace std;

int D[1001][1001];

int min(int A, int B, int C) {
    int result;
    if (A <= B && A <= C) {
        result = A;
    } else if (B <= A && B <= C) {
        result = B;
    } else {
        result = C;
    }
    return result;
}

int edit_dist(int n, string X, int m, string Y, int ins, int del, int chg) {
    // n: X의 길이, m: Y의 길이, ins: 삽입비용, del: 삭제비용, chg: 변경비용
    D[0][0] = 0;
    int c;

    for (int i = 1; i < n + 1; i++)
        D[i][0] = D[i - 1][0] + del;    // 첫 열 초기화
    for (int j = 1; j < n + 1; j++)
        D[0][j] = D[0][j - 1] + ins;    // 첫 행 초기화
    
    for (int i = 1; i < n + 1; i++) {
        for( int j = 1; j < m + 1; j++) {
            c = (X[i - 1] == Y[j - 1]) ? 0 : chg;
            D[i][j] = min(D[i - 1][j] + del, D[i][j - 1] + ins, D[i - 1][j - 1] + c);
        }
    }
    return D[n][m];
}

int main()
{
    string X, Y;
    cout << "초기 문자열을 입력하시오: ";
    cin >> X;
    cout << "목표 문자열을 입력하시오: ";
    cin >> Y;
    cout << "최소편집비용: " << edit_dist(X.length(), X, Y.length(), Y, 1, 1, 2) << '\n';

    cout << "\n편집거리 테이블\n";
    for (int i = 0; i <= X.length(); i++) {
        for (int j = 0; j <= Y.length(); j++) {
            cout << D[i][j] << "  ";
        }
        cout << '\n';
    }
}