#include "text.h"
#include <cstring>
#include <string>
#include <fstream>
#include "str_bm.h"

using namespace std;

text::text() {}

text::~text()
{
    data.clear();
}

bool text::read_from(istream &is)
{
    bool ret = true;
    str_bm tmp;
    while (tmp.getline(is)) {
        data.push_back(tmp);
    }
    if (data.size() == 0) {
        ret = false;
    }
    return ret;
}

ostream &operator<<(ostream &out, text &t)
{
    for (auto i : t.data) {
        out << i << endl;
    }
    return out;
}

str_bm text::operator[](int idx) const
{
    if (idx < 0 || idx >= data.size()) {
        throw "Index out of bounds";
    }
    return data[idx];
}

int text::get_nr_of_lines() const
{
    return data.size();
}

int text::get_length() const
{
    int res = 0;
    for (auto i : data) {
        res += i.length();
    }
    return res;
}

void text::add_line(const str_bm &s)
{
    data.push_back(s);
}

text &text::operator=(const text &t)
{
    data = t.data;
    return *this;
}

text text::to_lower() const
{
    text res;
    for (auto i : data) {
        res.add_line(i.to_lower());
    }
    return res;
}

text text::to_upper() const
{
    text res;
    for (auto i : data) {
        res.add_line(i.to_upper());
    }
    return res;
}

vector<vector<int>> text::occurences_of(str_bm s)
{
    vector<vector<int>> res;
    for (int i = 0; i < data.size(); ++i) {
        vector <int> tmp = data[i].find_from(s);
        if (tmp.size() > 0) {
            tmp.insert(tmp.begin(), i);
            res.push_back(tmp);
        }
    }
    return res;
}

vector<vector<int>> text::occurences_of_naive(str_bm s)
{
    vector<vector<int>> res;
    for (int i = 0; i < data.size(); ++i) {
        vector <int> tmp = data[i].find_from_naive(s);
        if (tmp.size() > 0) {
            tmp.insert(tmp.begin(), i);
            res.push_back(tmp);
        }
    }
    return res;
}