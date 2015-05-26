#ifndef GAMEMASTER_H_INCLUDED
#define GAMEMASTER_H_INCLUDED
#include <vector>
#include <iostream>

using namespace std;


enum chip_types
{
    Empty=-1,
    Blue,
    Red
};

struct GM
{

    vector<vector<chip_types> > _table;
    size_t _cursor;
    chip_types chip;


    enum
    {
        none,
        tie,
        blue_win,
        red_win,
        pause,
        column_filled
    } interrupt;

    GM(int rows, int cols):_table(vector<vector<chip_types> > (rows, vector<chip_types>(cols, Empty))),_cursor(0), chip(Blue), interrupt(none){};
    void set_cursor(size_t c);
    int  get_cursor(){return _cursor;}
    int  drop_chip();
    void check_win();
    void print();
};

#endif // GAMEMASTER_H_INCLUDED
