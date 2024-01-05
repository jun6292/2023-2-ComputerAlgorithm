#include <iostream>
#include <string>

using namespace std;

int *skip;
int *SP;

int bruteCount = 0;
int kmpCount = 0;
int bmCount = 0;

int initSP(char *p) 
{
    int count = 0;
    int i, j, m = strlen(p);
    SP = new int[m];
    SP[0] = -1;
    for (i = 1, j = -1; i <= m - 1; i++) {
        while ((j >= 0) && ++count && (p[j + 1] != p[i]))
            j = SP[j];
        count++;
        if (p[j + 1] == p[i])
            j++;
        SP[i] = j;
    }
    return count;
}

const int alphabet_count = 26;

int index(char a)
{
    return toupper(a) - 'A';
}

int *lp;

void LastPos(char *p) 
{
    int i;
    lp = new int[alphabet_count];
    for (i = 0; i < alphabet_count; i++) lp[i] = -1;
    for (i = 0; i < strlen(p); i++) lp[index(p[i])] = i;
}

int GoodSuffix(char *p) 
{
    int i, k, m = strlen(p);
    int count = 0;
    skip = new int[m];
    char *r_p = new char[m];
    for (i = 0; i < m; i++) {
        r_p[m - i - 1] = p[i];
    }
    count = initSP(r_p);
    for (i = -1; i <= m - 1; i++) skip[i] = m - 1 - SP[m - 1];
    for (k = 0; k <= m - 1; k++) {
        i = m - 1 - SP[k] - 1;
        if (skip[i] > k - SP[k]) skip[i] = k - SP[k];
    }
    return count;
}

void boyermoore(char *p, char *a) 
{
    int i, j, m = strlen(p), n = strlen(a);
    LastPos(p);
    bmCount = GoodSuffix(p);
    j = 0;
    while (j <= n - m) {
        for (i = m - 1; i >= 0 && p[i] == a[j + i]; i--) bmCount++;
        bmCount++;
        if (i == -1) {
            cout << j << ", ";
            j = j + skip[-1];
        }
        else {
            j = j + max(skip[i], i - lp[index(a[j + i])]);
        }
    }
     cout << bmCount << " (Boyer-Moore)" << '\n';
}

void brutesearch(char *p, char *a) 
{
    int i, j, m = strlen(p), n = strlen(a);
    for (i = 0; i <= n - m; i++) {
        for (j = 0; j < m; j++) {
            bruteCount++;
            if (a[i + j] != p[j]) break;
        }
        if (j == m) cout << i << ", ";
    }
     cout <<  bruteCount << " (Brute-Force)" << '\n';
}

void kmpsearch(char *p, char *a)
{
    int i, j, m = strlen(p), n = strlen(a);
    kmpCount = initSP(p);
    for (i = 0, j = -1; i <= n - 1; i++) {
        while ((j >= 0) && (p[j + 1] != a[i])) {
            j = SP[j];
        }

        if (++kmpCount && p[j + 1] == a[i]) j++;
        if (j == m - 1) {
            //kmpCount++;
            j = SP[j];
            cout << i - m + 1 << ", ";
        }
    }
    cout << kmpCount << " (KMP)" << '\n';
}

// A STRING SEARCHING EXAMPLE CONSISTING OF A GIVEN STRING
int main()
{
    char t[200];
    char p[100];

    cin.getline(t, 200);
    cin.getline(p, 100);

    boyermoore(p, t);
    brutesearch(p, t);
    kmpsearch(p, t);
}