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
        if(_table[row][i]==Empty) return;
        i++;
    }

    if(interrupt==column_filled) interrupt=tie;
}

int GM::drop_chip()
{
    if(interrupt) return 0;

    size_t row=0;
    if(_table[row][_cursor]!=Empty)
    {interrupt=column_filled; return 0;}

    while (row<_table.size()-1 && _table[row+1][_cursor]==Empty) row++;
    _table[row][_cursor]=chip;

    //chip=!chip;
    if(chip==Red) chip=Blue;
    else chip=Red;

    check_win();

    return row;
}

void GM::check_win()
{
    if(interrupt) return;


    for (auto row: _table)
    {
        for(size_t i=0; i<row.size()-consec+1; i++)
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


    /**global -prettier- solution for checking diags of a matrix available on paper*/
    /**BEWARE WILD MAGIC NUMBERS*/


    for(size_t r=0; r<_table.size()-consec+1; r++)
    {
        for(size_t i=0; i<_table[r].size(); i++)
        {
            int b_cnt=0, r_cnt=0;
            for(size_t j=0; j<consec; j++)
            {
                if(_table[j+r][i]==Blue) b_cnt++;
                if(_table[j+r][i]==Red) r_cnt++;
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


            b_cnt=0, r_cnt=0;
            for(size_t j=0; j<consec; j++)
            {
                if(_table[j+r][j+i]==Blue) b_cnt++;
                if(_table[j+r][j+i]==Red) r_cnt++;
                //cout<<"j+r= "<<j+r<<" j+i= "<<j+i<<" r= "<<r<<'\n';
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

            b_cnt=0, r_cnt=0;
            for(size_t j=0; j<consec; j++)
            {
                if(_table[j+r][_table[r].size()-1-i-j]==Blue) b_cnt++;
                if(_table[j+r][_table[r].size()-1-i-j]==Red)  r_cnt++;
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

}

void GM::print()
{
    for(auto row: _table)
    {
        for(auto col: row) cout<<col<<' ';
        cout<<'\n';
    }

}
