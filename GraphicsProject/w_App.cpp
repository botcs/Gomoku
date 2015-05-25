#include "w_BaseWidget.h"
#include "w_App.h"
#define clrscr move_to(0,0)<<color(defColor)<<box(XX-1,YY-1)

w_App::w_App(const int width, const int height) : XX(width), YY(height), _cursor(0)
{
    state=running;
    renderer=new w_Frame(w_Widget(0,0,width,height));
    renderer->IsActive=true;
}

int w_App::run()
{
    gout.open(XX, YY, false);
    genv::event ev;
    genv::gin.timer(40);
    while(gin >> ev)
    {
        gout<<clrscr;
        //gout<<color(white)<<box_to(10,10);
        if(ev.type!=ev_timer) renderer->handle_event(ev);
        else{
            renderer->draw(gout);
            gout<<refresh;
        }

    }
    return 0;
}

bool w_App::push (w_Widget* W)
{
    renderer->push(W);
    _cursor=W;
    if(W->x() <= XX && W->y() <= YY) return true;
    else return false;
}


w_App&  operator << (w_App& lay_out, w_App::lo_ops layout_oper)
{
    lay_out.lay_op=layout_oper;
    return lay_out;
}

w_App&  operator << (w_App& lay_out, w_Widget* W)
{
    w_Widget blank(100,100,0,0);
    W->adopt(&lay_out);
    if(!lay_out._cursor)
    {
        lay_out._cursor=W;
        lay_out._begin=W;
        lay_out.push(W);
        return lay_out;
    }

    if(lay_out.lay_op==w_App::left)W->align(lay_out._cursor, lay_out.hor_space());
    if(lay_out.lay_op==w_App::endl) W->align(lay_out._begin, lay_out.ver_space(), w_Widget::below),  lay_out._begin=W, lay_out.lay_op=w_App::left;
    if(lay_out.lay_op==w_App::downstream)W->align(lay_out._cursor, lay_out.ver_space(), w_Widget::below);

    lay_out.push(W);

    return lay_out;
}

