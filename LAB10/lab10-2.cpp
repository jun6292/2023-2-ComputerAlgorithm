#include <iostream>
using namespace std;

const int q = 33554393;
const int d = 26;

int index(char c)
{
    if (c == ' ') return 0;
    return c - 'A' + 1;
}

void brutesearch(char p[10][10], char a[100][100])
{
    int m = 10, n = 100;
    int flag = 1;
    int count = 0;

    for (int i = 0; i < n - m + 1; i++) {
        for (int j = 0; j < n - m + 1; j++) {
            for (int k = 0, flag = 1; k < m && flag==1; k++) {
                for (int s = 0; s < m && flag==1; s++) {
                    count++;
                    if (p[k][s] != a[i + k][j + s])
                        flag = 0;
                }
            }
        }
    }
    cout << count;
    cout << " (Brute-Force)" << endl;
}

void rksearch(char p[10][10], char a[100][100])
{
    int dM = 1, h1 = 0, h2 = 0;
    int m = 10, n = 100;
    int count = 0;

    for (int i = 1; i < m*m; i++)
        dM = (d * dM) % q;

    for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++)
            h1 = (h1*d + index(p[i][j])) % q;

    for (int t1 = 0; t1 < n - m + 1; t1++)
        for (int t2 = 0; t2 < n - m + 1; t2++)
        {
            for (int p1 = t1; p1 < m + t1; p1++)
                for (int p2 = t2; p2 < m + t2; p2++)
                    h2 = (h2*d + index(a[p2][p2])) % q;
            count++;

            if (h1 != h2)
                h2 = 0;
        }
    cout << count;
    cout << " (Rabin-Karp)" << endl;
}

int main()
{
    int i, j;
    char text_string[100][100];
    char pattern_string[10][10];

    for (i = 0; i < 100; i++) {
        for (j = 0; j < 100; j++)
            text_string[i][j] = 'A';
    }

    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++)
            pattern_string[i][j] = 'A';
    }
    pattern_string[9][9] = 'B';

    brutesearch(pattern_string, text_string);
    rksearch(pattern_string, text_string);

    return 0;
}
