#include "str_bm.h"
#include "text.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <map>
#include <stdlib.h>
#include <climits>
#include <ctime>
#define RESET   "\033[0m"
#define RED     "\033[31m"

using namespace std;

typedef pair<str_bm, str_bm> option;

ostream &operator<<(ostream &out, const vector <int> &v)
{
    for (auto i : v) {
        out << i << " ";
    }
    return out;
}

ostream &operator<<(ostream &out, const vector <vector <int>> &v)
{
    for (int i = 0; i < v.size(); i++) {
        out << "Line " << v[i][0] + 1 << " at index";
        if (v[i].size() > 2) {
            out << "es";
        }
        out << ": [";
        for (int j = 1; j < v[i].size() - 1; j++) {
            out << v[i][j] << ", ";
        }
        out << v[i][v[i].size() - 1] << "]";
        out << endl;
    }
    return out;
}

ostream &operator<<(ostream &out, const vector <option> &v)
{
    for (auto i : v) {
        cout << "arg_name: " << i.first;
        if (i.second.length() > 0) {
            cout << ", arg_value: " << i.second;
        }
        cout << endl;
    }
    return out;
}

void print_help(int argc, char **argv)
{
    cout << "Usage: " << argv[0] << " [options] <-p{pattern}> <-f{filename}>" << endl;
    cout << "Options:" << endl;
    cout << "-h: print this help" << endl;
    cout << "-i: ignore case" << endl;
    cout << "-n: print line numbers" << endl;
    cout << "-c: print number of occurences" << endl;
    cout << "-w: match whole words" << endl;
    cout << "-g: make the pattern glow" << endl;
    cout << "-m{num}: stop after num occurences" << endl;
    cout << "-p{pattern}: pattern to search for" << endl;
    cout << "-f{filename}: file to search in" << endl;
}

vector <option> args_in(int argc, char **argv, map<char, bool>& used)
{
    if (argc < 3) {
        if (argc == 2 && strcmp(argv[1], "-h") == 0) {
            print_help(argc, argv);
            exit(0);
        }
        cout << "Too few arguments!" << endl;
        cout << "Use the \"-h\" option for help." << endl;
        exit(1);
    }
    vector <option> ret;
    str_bm arg_string;
    for (int i = 1; i < argc; i++) {
        arg_string += str_bm(argv[i]);
        arg_string += str_bm(" ");
    }

    vector<int> sep = arg_string.find_from(str_bm("-"));
    for (int i = 0; i < sep.size() - 1; i++) {
        ret.push_back(make_pair(arg_string.substr(sep[i] + 1, sep[i + 1] - 1), str_bm()));
    }
    str_bm last_arg = arg_string.substr(sep[sep.size() - 1] + 1, arg_string.length() - 1);
    ret.push_back(make_pair(last_arg, str_bm()));

    map<char, bool> takes_value = {
        {'h', false},
        {'i', false},
        {'n', false},
        {'c', false},
        {'w', false},
        {'g', false},
        {'m', true},
        {'p', true},
        {'f', true}
    };

    vector<str_bm> valid_args = { "h", "i", "n", "c", "w", "g", "m", "p", "f" };
    
    //separate values from options
    for (int i = 0; i < ret.size(); i++) {
        str_bm curr_arg = ret[i].first;

        //check if value is given
        vector<int> val_sep_open = curr_arg.find_from(str_bm("{"));
        vector<int> val_sep_close = curr_arg.find_from(str_bm("}"));

        //check if option takes a value
        if (takes_value[curr_arg[0]] && val_sep_open.size() == 0 && val_sep_close.size() == 0) {
            cout << "Option \"" << curr_arg[0] << "\" takes a value!" << endl;
            cout << "Use the \"-h\" option for help." << endl;
            exit(1);
        }

        //check if option doesn't take a value
        if (!takes_value[curr_arg[0]] && (val_sep_open.size() > 0 || val_sep_close.size() > 0)) {
            cout << "Option \"" << curr_arg[0] << "\" doesn't take a value!" << endl;
            cout << "Use the \"-h\" option for help." << endl;
            exit(1);
        }

        //check if value is given correctly
        if ((val_sep_open.size() == 0 && val_sep_close.size() > 0) || (val_sep_open.size() > 0 && val_sep_close.size() == 0)) {
            cout << "Syntax error at \"" << curr_arg[0] << "\"!" << endl;
            cout << "Use the \"-h\" option for help." << endl;
            exit(1);
        }

        //put value in option
        if (val_sep_open.size() > 0 || val_sep_close.size() > 0) {
            //check if value is empty
            if (val_sep_open[0] + 1 == val_sep_close.back()) {
                cout << "Value for option \"" << curr_arg[0] << "\" is empty!" << endl;
                cout << "Use the \"-h\" option for help." << endl;
                exit(1);
            }
            str_bm arg_value = curr_arg.substr(val_sep_open[0] + 1, val_sep_close.back() - 1);
            ret[i].first = curr_arg.substr(0, val_sep_open[0] - 1);
            ret[i].second = arg_value;
        }
        else {
            ret[i].first = curr_arg.substr(0, curr_arg.length() - 2);
        }

        //check if option is valid
        for (int j = 0; j < valid_args.size(); j++) {
            if (strcmp(ret[i].first.get_data(), valid_args[j].get_data()) == 0) {
                break;
            }
            if (j == valid_args.size() - 1) {
                cout << "Invalid option \"" << ret[i].first << "\"!" << endl;
                cout << "Use the \"-h\" option for help." << endl;
                exit(1);
            }
        }

        //check if option is given more than once
        if (used[ret[i].first[0]]) {
            cout << "Option \"" << ret[i].first << "\" is given more than once!" << endl;
            cout << "Use the \"-h\" option for help." << endl;
            exit(1);
        }

        used[ret[i].first[0]] = true;
    }

    //check if pattern is given
    if (!used['p']) {
        cout << "Pattern required!" << endl;
        cout << "Use the \"-h\" option for help." << endl;
        exit(1);
    }

    //check if file is given
    if (!used['f']) {
        cout << "File required!" << endl;
        cout << "Use the \"-h\" option for help." << endl;
        exit(1);
    }
    
    //check if file exists
    for (int i = 0; i < ret.size(); i++) {
        if (strcmp(ret[i].first.get_data(), "f") == 0) {
            ifstream fin(ret[i].second.get_data());
            if (!fin) {
                cout << "File \"" << ret[i].second << "\" not found!" << endl;
                cout << "Use the \"-h\" option for help." << endl;
                exit(1);
            }
            fin.close();
            break;
        }
    }

    return ret;
}

void check_whole_words(vector <vector <int>>& occurences, text& t, str_bm& pattern)
{
    str_bm white_chars(" \t\n\r\v\f.,;:?!\"\'()[]{}<>+-*/\\=|&^%$#@~`");
    vector <vector <int>> new_occurences;
    for (int i = 0; i < occurences.size(); i++) {
        bool ok = true;
        for (int j = 1; j < occurences[i].size(); j++) {
            if (occurences[i][j] > 0 && white_chars.find_from_naive(t[occurences[i][0]].substr(occurences[i][j] - 1, occurences[i][j] - 1)).size() == 0) {
                ok = false;
                break;
            }
            if (occurences[i][j] + pattern.length() < t[occurences[i][0]].length() && white_chars.find_from_naive(t[occurences[i][0]].substr(occurences[i][j] + pattern.length(), occurences[i][j] + pattern.length())).size() == 0) {
                ok = false;
                break;
            }
        }
        if (ok) {
            new_occurences.push_back(occurences[i]);
        }
    }
    occurences = new_occurences;
}

void print_occurences(vector <option>& args, vector <vector <int>>& occurences, map<char, bool>& used, text& t, str_bm& pattern)
{
    int limit = INT_MAX;
    if (used['m']) {
        for (int i = 0; i < args.size(); i++) {
            if (strcmp(args[i].first.get_data(), "-m") == 0) {
                limit = atoi(args[i].second.get_data());
                break;
            }
        }
    }
    if (used['c']) {
        cout << occurences.size() << endl;
        exit(0);
    }
    if (!occurences.empty()) {
        for (int i = 0; i < occurences.size() && i < limit; i++) {
            int line = occurences[i][0];
            vector <bool> color(t[line].length(), false);
            if (used['g']) {
                for (int j = 1; j < occurences[i].size(); j++) {
                    for (int k = 0; k < pattern.length(); k++) {
                        color[occurences[i][j] + k] = true;
                    }
                }
            }
            if (used['n']) cout << line + 1 << ": ";
            for (int j = 0; j < t[line].length(); j++) {
                if (color[j]) {
                    cout << RED << t[line][j] << RESET;
                }
                else {
                    cout << t[line][j];
                }
            }

            cout << endl;
        }
        cout << endl;
    }
}

int main(int argc, char **argv)
{
    map<char, bool> used = {
        {'h', false},
        {'i', false},
        {'n', false},
        {'c', false},
        {'w', false},
        {'g', false},
        {'m', false},
        {'p', false},
        {'f', false}
    };

    vector <option> args = args_in(argc, argv, used);

    text t;
    ifstream fin(args[args.size() - 1].second.get_data());
    t.read_from(fin);

    str_bm pattern = args[args.size() - 2].second;

    if (used['i']) {
        t = t.to_lower();
        pattern = pattern.to_lower();
    }
    
    vector <vector <int>> occurences = t.occurences_of(pattern);

    if (used['w']) {
        check_whole_words(occurences, t, pattern);
    }

    print_occurences(args, occurences, used, t, pattern);

    return 0;
}