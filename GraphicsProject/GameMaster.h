#ifndef GAMEMASTER_H_INCLUDED
#define GAMEMASTER_H_INCLUDED
#include <vector>
#include <iostream>

using namespace std;

class GM
{    vector<vector<int> > _table;
    enum
    {
        Empty=-1,
        Blue,
        Red,
    } chip;


    int _cursor;

public:
    enum
    {
        none,
        tie,
        blue_win,
        red_win,
        column_filled
    } interrupt;

    GM(int rows, int cols):_table(vector<vector<int> > (rows, vector<int>(cols, Empty))), chip(Blue), _cursor(0){};
    void set_cursor(size_t c);
    void drop_chip();
    void check_win();
    void print();
};

#endif // GAMEMASTER_H_INCLUDED
