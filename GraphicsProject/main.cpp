#include <iostream>


#include <functional>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <map>

#define clrscr move_to(0,0)<<color(defColor)<<box(XX-1,YY-1)

#include "GameMaster.h"
#include "w_App.h"
#include "w_BaseWidget.h"
#include "w_Button.h"

using namespace genv;
const unsigned int X=800, Y=600;
using namespace std;
using namespace genv;

struct chip : w_Widget
{
    chip_types type;
    void draw(canvas& c)
    {
        if(type==Empty) return;
        if(type==Blue) c<<move_to(X, Y)<<color(0,0,255)<<box(W,H);
        else           c<<move_to(X, Y)<<color(255,0,0)<<box(W,H);
    }
    chip(w_Widget base, chip_types x): w_Widget(base), type(x){}
};

struct arrow: w_Widget
{
    bool RED;
    void draw(canvas& c)
    {
        if(RED)  c<<color(red);
        else     c<<color(0,0,255);
        c<<move_to(X+W/2, Y)<<box(2, H)
         <<genv::move(-1,0)<<line(-W/2, -H/2)<<line(W, 0)<<line(-W/2-1, H/2);
    }
    arrow():w_Widget(0,0,50,60), RED(false){}
};

struct GUI : private w_App
{
    GM * game;
    vector<w_Frame *> bars;
    vector<vector<chip *> > table;
    arrow* arr;
    int R, C;

    w_Text* res=0;

    void new_game()
    {
        delete game;
        game=new GM(R,C);
        for(int i=0; i<table.size(); i++)
            for(int j=0; j<table[i].size(); j++)
                table[i][j]->type=game->_table[i][j];
    }

    void init()
    {
        catch_after=[&]()
        {
            if(game->interrupt==GM::red_win)
            {
                game->interrupt=GM::pause;
                if(!res)
                {
                    res=new w_Text("RED PLAYER WINS",10,20);
                }
                else
                {
                    auto n= new w_Text("RED PLAYER WINS",10,20);
                    n->align(res, 10, below);
                    res=n;
                }

                this->push(res);
                return;
            }
            if(game->interrupt==GM::blue_win)
            {
                game->interrupt=GM::pause;
                if(!res)
                {
                    res=new w_Text("BLUE PLAYER WINS",10,20);
                }
                else
                {
                    auto n= new w_Text("BLUE PLAYER WINS",10,20);
                    n->align(res, 10, below);
                    res=n;
                }
                this->push(res);
            }


            for(w_Frame * col: bars)
            {
                arr->RED=game->chip;

                if(col->IsMouseOver(ev.pos_x, ev.pos_y)) arr->align(col, 10, above);
            }

            if (ev.button==btn_left || ev.button==btn_right || ev.keycode==key_enter || ev.keycode==key_space)
            {
                if(game->interrupt && game->interrupt!=GM::column_filled) return;
                int col;
                for(col=0; col<C; col++) if(bars[col]->IsActive) break;

                if(col>=C) return;
                game->set_cursor(col);

                if(game->interrupt==GM::column_filled)return;

                int row=game->drop_chip();
                table[row][col]->type=game->_table[row][col];
            }
        };
        this->run();
    }

    GUI(int rows, int cols) : w_App(X, Y), R(rows), C(cols)
    {
        game = new GM(R, C);
        arr= new arrow;
        for(int i=0; i<C; i++)
        {
            auto col = new w_Frame(w_Widget(150,150,50,R*50));
            *this<<col;

            bars.push_back(col);
        }
        *this<<arr;


        this->push(new w_Button("NEW GAME", 400, 20, [&](){new_game();}));

        for(int i=0; i<rows; i++)
        {
            vector<chip*> row;
            for(int j=0; j<C; j++)
            {
                chip* c=new chip(w_Widget(bars[j]->x()+5, bars[j]->y()+5+i*50, 40, 40), Empty);
                row.push_back(c);
                this->push(c);
            }
            table.push_back(row);
        }

    }
    ~GUI(){delete game;}
};

int main()
{
    GUI app(7,6);
    app.init();
    return 0;
}
