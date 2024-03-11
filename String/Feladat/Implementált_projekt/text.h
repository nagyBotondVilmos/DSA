#ifndef TEXT_H
#define TEXT_H
#include "str_bm.h"
#include <iostream>
#include <vector>

class text
{
    private:
        std::vector <str_bm> data;
    public:
        text();
        ~text();
        bool read_from(std::istream &);
        friend std::ostream &operator<<(std::ostream &, text &);
        str_bm operator[](int) const;
        int get_nr_of_lines() const;
        int get_length() const;
        void add_line(const str_bm &);
        text &operator=(const text &);
        text to_lower() const;
        text to_upper() const;
        std::vector<std::vector<int>> occurences_of(str_bm);
        std::vector<std::vector<int>> occurences_of_naive(str_bm);
};
#endif