#include "w_BaseWidget.h"

unsigned int w_Widget::wCounter=0;
using namespace genv;
void w_Widget::drawBase(genv::canvas& c)
{
    c<<move_to(X+W,Y+gout.cascent())<<color(black)<<text(m_label)<<color(white)<<move_to(X, Y)<<box(W,H);
}

bool w_Widget::adopt(w_App* parent)
{
    if(parent)
    {
        m_parent=parent;
        return true;
    }
    else return false;
}

void w_Widget::align (w_Widget* _to, int _dist, int _dir)
{
    if(_dir==after)
    {
        X=_to->X+_to->w()+_dist;
        Y=_to->Y;
    }
    if(_dir==before)
    {
        X=_to->X-_dist;
        Y=_to->Y;
    }
    if(_dir==above)
    {
        X=_to->X;
        Y=_to->Y-_dist-H;
    }
    if(_dir==below)
    {
        X=_to->X;
        Y=_to->Y+_to->h()+_dist;
    }
}

void w_Text::draw(canvas& c)
{
    c<<move_to(X,Y)<<color(defColor)<<box(W,H)
     <<move_to(X+margin/2,Y+gout.cascent())<<color(white)<<text(m_label);
}

void w_Control::drawBase(genv::canvas& c)
{
    if(IsActive)
        c<<move_to(X-2, Y-2)<<color(red)<<box(W+4, H+4);


    c<<move_to(X-1, Y-1)<<color(black)<<box(W+2, H+2)<<move_to(X, Y)<<color(white)<<box(W,H);
}
bool w_Control::IsMouseOver(const int MX, const int MY) const
{
    return (MX>X && MX<X+W && MY>Y && MY<Y+H);
}
