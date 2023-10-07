#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct word {
    char str[100];
    int cnt;
};

word words[100], *sorted;
int word_cnt; // 단어 총 개수


void merge(word *list, int left, int mid, int right) {
    int i, j, k;
    i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        if (list[i].cnt > list[j].cnt) // 빈도수로 내림차순 정렬
            sorted[k++] = list[i++];
        else
            sorted[k++] = list[j++];
    }

    if (i > mid) {
        for (int n = j; n <= right; n++)
            sorted[k++] = list[n];
    }
    else {
        for (int n = i; n <= mid; n++)
            sorted[k++] = list[n];
    }

    // 정렬된 배열을 다시 원래의 배열에 복사
    for (int n = left; n <= right; n++)
        list[n] = sorted[n];
}

void merge_sort(word *list, int left, int right) {
    int mid;
    if (left < right) {
        mid = (left + right) / 2;
        merge_sort(list, left, mid);
        merge_sort(list, mid + 1, right);
        merge(list, left, mid, right);
    }
}

void merge2(word *list, int left, int mid, int right) {
    int i, j, k;
    i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        if (strcmp(list[i].str, list[j].str) < 0) // ASCII코드 기준으로 정렬
            sorted[k++] = list[i++];
        else
            sorted[k++] = list[j++];
    }
    if (i > mid) {
        for (int n = j; n <= right; n++)
            sorted[k++] = list[n];
    }
    else {
        for (int n = i; n <= mid; n++)
            sorted[k++] = list[n];
    }

    for (int n = left; n <= right; n++)
        list[n] = sorted[n];
}

void merge_sort2(word *list, int left, int right) {
    int mid;
    if (left < right) {
        mid = (left + right) / 2;
        merge_sort2(list, left, mid);
        merge_sort2(list, mid + 1, right);
        merge2(list, left, mid, right);
    }
    }

    int find_words(const char *s) {
    for (int i = 0; i < word_cnt; i++) {
        if (!strcmp(s, words[i].str)) {   // 같은 문자열인경우
            return i;
        }
    }
    return -1;
}

void count_words(const char *s) {
    int idx = find_words(s);

    if (idx == -1) {
        strcpy(words[word_cnt].str, s);
        words[word_cnt].cnt = 1;
        word_cnt++;
    }
    else {
        words[idx].cnt++;
    }
}

void show_words() {
    for (int i = 0; i < word_cnt; i++) {
        cout << words[i].str << " : " << words[i].cnt << '\n';
    }
}

void make_words(string s) {
    int j = 0;

    for (int i = 0; i < s.size(); i++) {
        if ((0 <= s[i] && s[i] <= 47) || (58 <= s[i] && s[i] <= 64) || (91 <= s[i] && s[i] <= 96) || (123 <= s[i] && s[i] <= 127)) {
            count_words(s.substr(j, i).c_str());
            j = i + 1;
        }
    }

    if (!j) {
        count_words(s.c_str());
    }
    else if (s.size() - j) {
        count_words(s.substr(j, s.size()).c_str());
    }
}

int main()
{
    ifstream file;
    sorted = new word[100];

    file.open("datafile.txt");
    if (file.is_open()) {
        while (!file.eof()) {
            string s;
            file >> s;
            make_words(s);
        }
        file.close(); // 파일 닫기
    }

    merge_sort(words, 0, word_cnt - 1); // 빈도수로 정렬
    int cnt = 0;
    for (int i = 0; i < word_cnt - 1; i++) {
        if (words[i].cnt == words[i + 1].cnt)
            cnt++;
        else if (cnt) {
            merge_sort2(words, i - cnt, i); // ASCII값으로 정렬
            cnt = 0;
        }

        if (words[i].cnt == words[word_cnt - 1].cnt) {
            merge_sort2(words, i, word_cnt - 1);
            break;
        }
    }
    show_words();

    return 0;
}