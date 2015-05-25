#include "GameMaster.h"

const unsigned int consec=4;

using namespace std;

void GM::set_cursor(size_t c)
{
    if(interrupt==tie || interrupt==red_win || interrupt==blue_win) return;
    if (c>=0 && c<_table[0].size()) _cursor=c;

    int row=0;
    if(_table[row][_cursor]!=Empty) interrupt=column_filled;
    else {interrupt=none; return;}

    size_t i=0;
    while(i<_table[0].size() && interrupt==column_filled)
    {
        if(_table[row][_cursor]==Empty)
        {
            _cursor=i;
            interrupt=none;
        }
    }

    if(interrupt==column_filled) interrupt=tie;
}

void GM::drop_chip()
{
    if(interrupt) return;

    size_t row=0;
    if(_table[row][_cursor]!=Empty)
    {interrupt=column_filled; return;}

    while (row<_table.size()-1 && _table[row+1][_cursor]==Empty) row++;
    _table[row][_cursor]=chip;

    //chip=!chip;
    if(chip==Red) chip=Blue;
    else chip=Red;

    check_win();
}

void GM::check_win()
{
    if(interrupt) return;


    for (auto row: _table)
    {
        for(size_t i=0; i<row.size()-4; i++)
        {
            int b_cnt=0, r_cnt=0;
            while (i<row.size() && row[i]==Blue)b_cnt++, i++;
            if(b_cnt>=consec)
            {
                interrupt=blue_win;
                return;
            }

            while (i<row.size() && row[i]==Red)r_cnt++, i++;
            if(r_cnt>=consec)
            {
                interrupt=red_win;
                return;
            }
        }
    }

    /**implemented for fix table size:*/
    /**especially for 4x7 table*/

    for(size_t i=0; i<4; i++)
    {
        int b_cnt=0, r_cnt=0;
        for(int j=0; j<4; j++)
        {
            if(_table[j][j+i]==Blue) b_cnt++;
            if(_table[j][j+i]==Red) r_cnt++;
        }

        if(b_cnt>=consec)
        {
            interrupt=blue_win;
            return;
        }
        if(r_cnt>=consec)
        {
            interrupt=red_win;
            return;
        }
    }
    for(size_t i=0; i<4; i++)
    {
        int b_cnt=0, r_cnt=0;
        for(int j=0; j<4; j++)
        {
            if(_table[j][j+6-i]==Blue) b_cnt++;
            if(_table[j][j+6-i]==Red)  r_cnt++;
        }

        if(b_cnt>=consec)
        {
            interrupt=blue_win;
            return;
        }
        if(r_cnt>=consec)
        {
            interrupt=red_win;
            return;
        }
    }
}

void GM::print()
{
    for(auto row: _table)
    {
        for(auto col: row) cout<<col<<' ';
        cout<<'\n';
    }

}
