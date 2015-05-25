#include <iostream>

#include "graphics.hpp"
#include "w_BaseWidget.h"
#include "w_Frame.h"
#include "w_RadioButton.h"
#include "w_Button.h"
#include "w_CheckBox.h"
#include "w_LongText.h"
#include "w_TextControl.h"
#include "w_NumTxtCtrl.h"
#include "w_ListBox.h"
#include <vector>
#include <functional>
#include <queue>
#define clrscr move_to(0,0)<<color(defColor)<<box(XX-1,YY-1)

using namespace genv;
const unsigned int XX=500, YY=500;


int main()
{
    gout.open(XX, YY, false);
    event ev;
    gin.timer(20);

    unsigned posX=0, posY=0;
    std::vector<w_Control*> WX;

    w_Frame * F = new w_Frame(w_Widget(0, 0, XX, YY));
/*
    w_TextControl * T = new w_TextControl ("uj opcio", 1000, 1000);
    F->push_control(T);

    w_LongText * L = new w_LongText (w_Widget("SZÖVEG", 20,50,400,400), "Log.txt", w_LongText::wrapped);
    F->push_control(L);


    w_NumTxtCtrl * NC = new w_NumTxtCtrl (10, 10, 100, -100, 100, 40);
    //NC->align(L,300);
    F->push_control(NC);

    //w_Button * B = new w_Button ("hozzáad", 0, 0, [&](){L->push_line("ANYÁD");});
    //F->push_control(B);

    //w_ListBox<w_CheckBox> * LB = new w_ListBox<w_CheckBox>(w_Widget(500,500,500,500));
*/

    enum op
    {
        none,
        plus,
        minus,
        divide,
        times
    };

    std::queue<op> operations;
    std::queue<double> values;

    w_NumTxtCtrl * N = new w_NumTxtCtrl(10,10,150,-999999, 999999, 20000);
    F->push_control(N);
    /**NUM PALETTE*/

        w_Button * B_n = new w_Button("0", 10,10, [&](){N->push_digit(0);});
        B_n->align(N, 20,w_Widget::below);
        F->push_control(B_n);

        w_Button * B_l = B_n;
        B_n = new w_Button("1", 0,0, [&](){N->push_digit(1);});
        F->push_control(B_n);
        B_n->align(B_l, 10, w_Widget::after);

        B_l = B_n;
        B_n = new w_Button("2", 0,0, [&](){N->push_digit(2);});
        F->push_control(B_n);
        B_n->align(B_l, 10, w_Widget::after);

        B_l = B_n;
        B_n = new w_Button("3", 0,0, [&](){N->push_digit(3);});
        F->push_control(B_n);
        B_n->align(B_l, 10, w_Widget::after);


        w_Button * p = new w_Button("+", 0, 0, [&](){operations.push(plus), N->setval(0);});
        F->push_control(p);
        p->align(N, 50, w_Widget::below);

        w_Button * m = new w_Button("-", 0, 0, [&](){operations.push(minus), N->setval(0);});
        F->push_control(m);
        m->align(p, 30, w_Widget::after);

        w_Button * t = new w_Button("x", 0, 0, [&](){operations.push(times), N->setval(0);});
        F->push_control(t);
        t->align(m, 30, w_Widget::after);

        w_Button * d = new w_Button("/", 0, 0, [&](){operations.push(divide), N->setval(0);});
        F->push_control(d);
        d->align(t, 30, w_Widget::after);

        std::function<void()> equals= [&]()
        {
            double lval=0, rval=0;
                lval=values.front();
                values.pop();
            while (!operations.empty())
            {
                //std::cout<<values.size()<<' '<<operations.size()<<'\n';
                rval=values.front();
                values.pop();
                op last_op=operations.front();
                operations.pop();
                switch (last_op)
                {
                    case plus : lval+=rval;
                    break;
                    case minus : lval-=rval;
                    break;
                    case divide : lval/=rval;
                    break;
                    case times : lval*=rval;
                    break;
                    default : ;
                }
            }
            std::cout<<lval<<'\n';
            values.push(lval);
            N->setval(0);
        };

        w_Button * e = new w_Button("=", 300, 300, equals);
        F->push_control(e);
        e->align(d, 30, w_Widget::after);

    /***/



    WX.push_back(F);

    while(gin >> ev)
    {
        gout<<clrscr;
        if (ev.type==ev_mouse)
        {
            posX=ev.pos_x;
            posY=ev.pos_y;
            if(ev.button==btn_right)
            {

            }

            if (ev.button==btn_middle)
            {

            }

            if(ev.button==btn_left)
            {
                for(w_Control* w: WX)
                {
                    if(w->IsMouseOver(posX, posY)) w->IsActive=true;
                        else w->IsActive=false;
                }
            }
        }


        if (ev.type!=ev_timer && ev.keycode!=key_tab)
        {
            for(w_Control* w : WX)
            {
                if(w->IsActive) w->handle_event(ev);

            }
        }

        if(ev.keycode==key_tab)
        {
            for (size_t i=0; i<WX.size(); i++)
            {
                if(WX[i]->IsActive)
                {

                    WX[i]->IsActive=false;
                    i++;
                    WX[i%WX.size()]->IsActive=true;
                }
            }
        }


        if(ev.type==ev_timer)
        {
            for(w_Widget* w : WX) w->draw(gout);
            gout<<refresh;
        }

    }
    return 0;
}
