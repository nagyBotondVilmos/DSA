#define _CRT_SECURE_NO_WARNINGS

#include "str_bm.h"
#include <cstring>

using namespace std;

int str_bm::strlen(const char *str) const
{
    int i = 0;
    while (str[i] != '\0') {
        i++;
    }
    return i;
}

vector<int> str_bm::bad_char(str_bm pattern)
{
    vector<int> bc(256, -1);
    for (int i = 0; i < pattern.len; i++) {
        bc[(int)pattern.data[i]] = i;
    }
    return bc;
}

const char *str_bm::get_data() const
{
    return data;
}

str_bm::str_bm() : data(new char[1]), len(0)
{
    data[0] = '\0';
}

str_bm::str_bm(const char *str) : data(new char[strlen(str) + 1]), len(strlen(str))
{
    strcpy(data, str);
}

str_bm::str_bm(const str_bm &str) : data(new char[str.len + 1]), len(str.len)
{
    strcpy(data, str.data);
}

str_bm::~str_bm()
{
    delete[] data;
}

char &str_bm::operator[](int idx)
{
    if (idx < 0 || idx >= len) {
        throw out_of_range("Index out of range");
    }
    return data[idx];
}

str_bm &str_bm::operator=(const str_bm &str)
{
    delete[] data;
    data = new char[str.len + 1];
    len = str.len;
    strcpy(data, str.data);
    return *this;
}

str_bm str_bm::operator+(const str_bm &str) const
{
    str_bm tmp;
    tmp.len = len + str.len;
    delete[] tmp.data;
    tmp.data = new char[tmp.len + 1];
    strcpy(tmp.data, data);
    strcat(tmp.data, str.data);
    return tmp;
}

str_bm &str_bm::operator+=(const str_bm &str)
{
    len += str.len;
    char *tmp = new char[len + 1];
    strcpy(tmp, data);
    strcat(tmp, str.data);
    delete[] data;
    data = tmp;
    return *this;
}

str_bm str_bm::to_lower() const
{
    str_bm tmp;
    tmp.len = len;
    delete[] tmp.data;
    tmp.data = new char[len + 1];
    for (int i = 0; i < len; i++) {
        if (data[i] >= 'A' && data[i] <= 'Z') {
            tmp.data[i] = data[i] - 'A' + 'a';
        } else {
            tmp.data[i] = data[i];
        }
    }
    tmp.data[len] = '\0';
    return tmp;
}

str_bm str_bm::to_upper() const
{
    str_bm tmp;
    tmp.len = len;
    delete[] tmp.data;
    tmp.data = new char[len + 1];
    for (int i = 0; i < len; i++) {
        if (data[i] >= 'a' && data[i] <= 'z') {
            tmp.data[i] = data[i] - 'a' + 'A';
        } else {
            tmp.data[i] = data[i];
        }
    }
    tmp.data[len] = '\0';
    return tmp;
}

ostream &operator<<(ostream &os, const str_bm &str)
{
    os << str.data;
    return os;
}

istream &operator>>(istream &is, str_bm &str)
{
    string tmp;
    is >> tmp;
    delete[] str.data;
    str.data = new char[tmp.length() + 1];
    str.len = tmp.length();
    strcpy(str.data, tmp.c_str());
    return is;
}

str_bm str_bm::substr(int start, int end) const
{
    if (start < 0 || start >= len || end < 0 || end >= len || start > end) {
        throw out_of_range("Index out of range");
    }
    str_bm tmp;
    tmp.len = end - start + 1;
    delete[] tmp.data;
    tmp.data = new char[tmp.len + 1];
    for (int i = start; i <= end; i++) {
        tmp.data[i - start] = data[i];
    }
    tmp.data[tmp.len] = '\0';
    return tmp;
}

str_bm str_bm::insert(int pos, const str_bm& str)
{
    if (pos < 0 || pos > len) {
        throw out_of_range("Index out of range");
    }
    str_bm tmp;
    tmp.len = len + str.len;
    delete[] tmp.data;
    tmp.data = new char[tmp.len + 1];
    for (int i = 0; i < pos; i++) {
        tmp.data[i] = data[i];
    }
    for (int i = pos; i < pos + str.len; i++) {
        tmp.data[i] = str.data[i - pos];
    }
    for (int i = pos + str.len; i < tmp.len; i++) {
        tmp.data[i] = data[i - str.len];
    }
    tmp.data[tmp.len] = '\0';
    return tmp;
}

str_bm str_bm::replace(int start, int end, const str_bm &str)
{
    if (start < 0 || start >= len || end < 0 || end >= len || start > end) {
        throw out_of_range("Index out of range");
    }
    str_bm tmp;
    tmp.len = len - (end - start + 1) + str.len;
    str_bm before;
    if (start > 0) {
        before = substr(0, start - 1);
    }
    str_bm after;
    if (end < len - 1) {
        after = substr(end + 1, len - 1);
    }
    delete[] tmp.data;
    tmp.data = new char[tmp.len + 1];
    strcpy(tmp.data, before.data);
    strcat(tmp.data, str.data);
    strcat(tmp.data, after.data);
    tmp.data[tmp.len] = '\0';
    return tmp;
}

str_bm str_bm::reverse() const
{
    str_bm tmp;
    tmp.len = len;
    delete[] tmp.data;
    tmp.data = new char[len + 1];
    for (int i = 0; i < len; i++) {
        tmp.data[i] = data[len - i - 1];
    }
    tmp.data[len] = '\0';
    return tmp;
}

int str_bm::length() const
{
    return len;
}

vector<int> str_bm::find_from(str_bm pattern)
{
    if (pattern.len == 0) return vector<int>();
    vector<int> res;
    vector<int> bc = bad_char(pattern);
    int i = 0;
    int shift = 0;
    while (i <= len - pattern.len) {
        int j = pattern.len - 1;
        while (j >= 0 && pattern.data[j] == data[i + j]) {
            j--;
        }
        if (j < 0) {
            res.push_back(i);
            if (i + pattern.len < len) {
                shift = pattern.len - bc[(int)data[i + pattern.len]];
                i += shift;
            } else {
                shift = 1;
                i += shift;
            }
        } else {
            shift = j - bc[(int)data[i + j]];
            if (shift < 1) {
                shift = 1;
            }
            i += shift;
        }
    }
    return res;
}

vector<int> str_bm::find_from_see_steps(str_bm pattern)
{
    if (pattern.len == 0) return vector<int>();
    vector<int> res;
    vector<int> bc = bad_char(pattern);
    int i = 0;
    int old_i = 0;
    int j = 0;
    int shift = 0;
    cout << "i = " << i << endl;
    cout << "j = " << j << endl;
    cout << "shift = " << shift << endl;
    cout << "bc = " << endl;
    vector <bool> used(256, false);
    for (int k = 0; k < pattern.len; k++) {
        if (used[(int)pattern.data[k]]) continue;
        cout << "( " << pattern.data[k] << ": " << bc[(int)pattern.data[k]] << " )" << endl;
        used[(int)pattern.data[k]] = true;
    }
    cout << endl;
    if (res.size() > 0) {
        cout << "res = ";
        for (int k = 0; k < res.size(); k++) {
            cout << res[k] << " ";
        }
        cout << endl;
    }
    cout << "----------------------------------------" << endl;
    while (i <= len - pattern.len) {
        while (j >= 0 && pattern.data[j] == data[i + j]) {
            j--;
        }
        if (j < 0) {
            res.push_back(i);
            if (i + pattern.len < len) {
                shift = pattern.len - bc[(int)data[i + pattern.len]];
                i += shift;
            } else {
                shift = 1;
                i += shift;
            }
        } else {
            int shift = j - bc[(int)data[i + j]];
            if (shift < 1) {
                shift = 1;
            }
            i += shift;
        }
        cout << "i = " << old_i << endl;
        cout << "j = " << j << endl;
        cout << "shift = " << shift << endl;
        cout << "bc = " << endl;
        vector <bool> used(256, false);
        for (int k = 0; k < pattern.len; k++) {
            if (used[(int)pattern.data[k]]) continue;
            cout << "( " << pattern.data[k] << ": " << bc[(int)pattern.data[k]] << " )" << endl;
            used[(int)pattern.data[k]] = true;
        }
        if (res.size() > 0) {
            cout << endl;
            cout << "res = ";
            for (int k = 0; k < res.size(); k++) {
                cout << res[k] << " ";
            }
            cout << endl;
        }
        cout << "----------------------------------------" << endl;
        old_i = i;
    }
    return res;
}

vector<int> str_bm::find_from_naive(str_bm pattern)
{
    if (pattern.len == 0) return vector<int>();
    vector<int> res;
    for (int i = 0; i < len; i++) {
        if (i + pattern.len <= len && strcmp(substr(i, i + pattern.len - 1).get_data(), pattern.get_data()) == 0) {
            res.push_back(i);
        }
    }
    return res;
}

void str_bm::read_from(const char *filename)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        throw invalid_argument("File not found");
    }
    fseek(f, 0, SEEK_END);
    len = ftell(f);
    fseek(f, 0, SEEK_SET);
    delete[] data;
    data = new char[len + 1];
    fread(data, 1, len, f);
    data[len] = '\0';
    fclose(f);
}

bool str_bm::getline(istream &is)
{
    bool ret = false;
    char buf[1000];
    is.getline(buf, 1000);
    if (is) {
        ret = true;
    }
    len = strlen(buf);
    delete[] data;
    data = new char[len + 1];
    strcpy(data, buf);
    return ret;
}