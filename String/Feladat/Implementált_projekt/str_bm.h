#ifndef STR_BM_H
#define STR_BM_H
#include <iostream>
#include <vector>

class str_bm
{
    private:
        char *data;
        int len;
        
        int strlen(const char *) const;

        std::vector<int> bad_char(str_bm);
    public:
        const char *get_data() const;
        str_bm();
        str_bm(const char *);
        str_bm(const str_bm &);
        ~str_bm();

        char &operator[](int);

        str_bm &operator=(const str_bm &);
        str_bm operator+(const str_bm &) const;
        str_bm &operator+=(const str_bm &);

        str_bm to_lower() const;
        str_bm to_upper() const;

        friend std::ostream &operator<<(std::ostream &, const str_bm &);
        friend std::istream &operator>>(std::istream &, str_bm &);
        
        str_bm substr(int, int) const;
        str_bm insert(int, const str_bm &);
        str_bm replace(int, int, const str_bm &);
        
        str_bm reverse() const;
        
        int length() const;
        
        std::vector<int> find_from(str_bm);
        std::vector<int> find_from_see_steps(str_bm);
        std::vector<int> find_from_naive(str_bm);

        void read_from(const char *);

        bool getline(std::istream &);
};
#endif