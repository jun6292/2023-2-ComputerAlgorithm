#include <iostream>
#include <string>
using namespace std;

int *SP; // SP에 대한 메모리는 p의 크기만큼 동적 할당 해야한다.
const int q = 33554393;
const int d = 26;

int index(char c)
{
    if (c == ' ')
        return 0;
    return c - 'A' + 1;
}

int initSP(string p)
{
    int i, j, m = p.length();
    int count = 0;
    SP = new int[m];
    SP[0] = -1;
    for (i = 1, j = -1; i <= m - 1; i++)
    {
        while ((j >= 0) && ++count && (p[j + 1] != p[i]))
        {
            j = SP[j];
        }
        count++;
        if (p[j + 1] == p[i])
            j++;
        SP[i] = j;
    }
    return count;
}

void brutesearch(string p, string a)
{ // p : Pattern String, a : Text String
    int count = 0;
    int i, j, m = p.length(), n = a.length();
    for (i = 0; i <= n - m; i++)
    {
        for (j = 0; j < m; j++)
        {
            count++;
            if (a[i + j] != p[j])
                break;
        }
        if (j == m)
        {
            cout << i << ", ";
        }
    }
    cout << count;
    cout << " (Brute-Force)" << endl;
}

void kmpsearch(string p, string a)
{
    int count = 0;
    count = initSP(p);
    int i, j, m = p.length(), n = a.length();
    for (i = 0, j = -1; i <= n - 1; i++)
    {
        while ((j >= 0) && (p[j + 1] != a[i]))
        {
            j = SP[j];
        }
        if (++count && p[j + 1] == a[i])
            j++;
        if (j == m - 1)
        {
            cout << i - j << ", ";
            j = SP[j];
        }
    }
    cout << count;
    cout << " (KMP)" << endl;

}

void rksearch(string p, string t) {
    int count = 0;
    int i, j, dM = 1, h1 = 0, h2 = 0, flag;
    int m = p.length(), n = t.length();
    for (i = 1; i < m; i++) 
        dM = (d * dM) % q;

    for (i = 0; i < m; i++) {
        h1 = (h1 * d + p[i]) % q; 
        h2 = (h2 * d + t[i]) % q; 
    } 


    for (i = 0; i < n - m + 1; i++) {
        if (h1 == h2) {
            flag = 1;
            for (j = i; j < m + i; j++) {
                count++;
                if (t[j] != p[j - i]) {
                    flag = 0;
                    break;
                }
            }
            if (flag) {
                cout << i << ", ";
            }
        }  

        if (i < n - m) {
            h2 = (h2 - t[i] * dM) % q;

            if (h2 < 0) 
                h2 = h2 % q + q;

            h2 = (h2 * d + t[i + m]) % q;
        }  
    } 
    cout << count << " (Rabin-Karp)" << endl;
}

int main()
{
    string text, pattern;
    getline(cin, text);
    getline(cin, pattern);

    brutesearch(pattern, text);
    kmpsearch(pattern, text);
    rksearch(pattern, text);
}

// A STRING SEARCHING EXAMPLE CONSISTING OF A GIVEN STING
// STING