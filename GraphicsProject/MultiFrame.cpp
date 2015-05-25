#include <iostream>

#include "graphics.hpp"
#include "w_Frame.h"
#include <functional>

using namespace genv;
const unsigned int XX=500, YY=600;


int main()
{
    gout.open(XX, YY, false);
    event ev;
    gin.timer(10);


    w_Frame* F = new w_Frame(XX,YY);
    w_Frame* MainFrame = new w_Frame(XX,YY);
    w_Frame* ActiveFrame = MainFrame;
/**SETTINGS FRAME*/
    F->addNumControl(30,30,100,50,150,20);
    F->addNumControl(150,30,100,50,100,50);
    std::vector<std::string> Rset1;
    Rset1.push_back("Crimson red");
    Rset1.push_back("Blu");
    F->addRButtonSet("Fill color", Rset1, 10,200);


    std::vector<std::string> Rset2;
    Rset2.push_back("White");
    Rset2.push_back("Blak");
    F->addRButtonSet("Edge color", Rset2, 200,200);

/** WARNING!! **/
//Frame pointers (at the moment) are not  smart pointers, so be careful
/**     delete F->GetNumC(0);       */
//DON'T Mess it up


    int rectX, rectY, fillC, edgeC=-1;
    std::function<void()> SetDrawing = [&]()
    {
        rectX=F->GetNumC(0)->Getval();
        rectY=F->GetNumC(1)->Getval();

        fillC=F->GetRadB(0)->choiceind();
        edgeC=F->GetRadB(1)->choiceind();
    };


    F->addButton("Go back", 300, 150, [&](){ActiveFrame=MainFrame;});
    F->addButton("Redraw", 100,150, SetDrawing);
    F->addButton("Print Widget State", 100,100, [F](){F->printValues("Log.xls");});

    F->addTextControl("Write here any option", 100,400);
    std::function<void()> addOption = [&](){F->GetRadB(0)->add_opt(F->GetTC(0)->Gettext());};
    F->addButton("add option", 100,500, addOption);

    MainFrame->addTextControl("fajl neve", 10, 10);
    MainFrame->addButton("Settings", 40, 50, [&](){ActiveFrame=F;});

    MainFrame->addButton("Print Settings with given name", 100,100, [&](){F->printValues(ActiveFrame->GetTC(0)->Gettext()+".xls");});

    while(gin >> ev && ev.keycode!=key_escape)
    {
        gout<<clrscr;
        ActiveFrame->refreshFrame(ev);
        gout<<stamp(ActiveFrame->c,1,1);

        if(ActiveFrame==MainFrame)
        {
            if(edgeC==0) gout<<move_to(200-2,400-2)<<color(255,255,255)<<box(rectX+4, rectY+4);
            if(edgeC==1) gout<<move_to(200-2,400-2)<<color(0,0,0)<<box(rectX+4, rectY+4);

            gout<<move_to(200,400)<<color(defColor)<<box(rectX, rectY);

            if(fillC==0) gout<<move_to(200,400)<<color(153,0,0)<<box(rectX, rectY);
            if(fillC==1) gout<<move_to(200,400)<<color(0,0,255)<<box(rectX, rectY);
        }

        if(ev.type==ev_timer) gout<<refresh;
        if(ev.keycode=='p') F->printValues(ActiveFrame->GetTC(0)->Gettext()+".xls");
    }

/**NO NEED OF LONG DECLARATION OF SIMPLE WIDGETS WITH w_Frame
    unsigned posX=0, posY=0;
    w_CheckBox * cb1=new w_CheckBox("1", 40, 40, 50, 50);
    w_CheckBox * cb2=new w_CheckBox("2", 90, 400, 50, 50);
    w_TextControl * tc=new w_TextControl("szoveg", 10,400);
    w_NumControl * nc = new w_NumControl(10,10,100,-5,5,10);
    w_Button * B = new w_Button("kiir", 400, 10, [nc](){std::cout<<"the Numeric Controls current value is: "<<nc->Getval()<<'\n';});

    std::vector<w_Control*> WX;
    WX.push_back(cb1);
    WX.push_back(cb2);
    WX.push_back(tc);
    WX.push_back(B);
    WX.push_back(nc);
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
                if(w->IsActive) w->HandleEvt(ev);

            }
        }

        if(ev.keycode==key_tab)
        {
            for (int i=0; i<WX.size(); i++)
            {
                if(WX[i]->IsActive)std::string s, const int x, const int y
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
    */
    return 0;
}
