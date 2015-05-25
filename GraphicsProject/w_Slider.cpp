#include "w_Slider.h"
#include <iostream>

using namespace genv;

void w_Slider::handle_event(genv::event& e)
{
    if(m_direction==Horizontal)
    {
        if (e.keycode==key_right)   m_state+=0.1;
        if (e.keycode==key_left)    m_state-=0.1;
    } else
    {
        if (e.keycode==key_down)    m_state+=0.1;
        if (e.keycode==key_up)      m_state-=0.1;
    }

    if (e.button==btn_wheelup)  m_state-=0.1;
    if (e.button==btn_wheeldown)m_state+=0.1;

    if (e.button==btn_left) m_pressed=true;
    if (e.button==-btn_left)m_pressed=false;

    if (m_pressed)
    {
        if(m_direction==Horizontal) m_state=(e.pos_x-X)/double(W);
        else m_state=(e.pos_y-Y)/double(H);

    }

    if (m_state > 1) m_state=1;
    if (m_state < 0) m_state=0;
}
void w_Slider::draw(genv::canvas& c)
{
    drawBase(c);
    (IsActive) ? c<<color(red) : c<<color(200,0,0);
    if(m_direction==Horizontal) c<<move_to(X+m_state*(W-W/10), Y)<<box(W/10, H);
        else                    c<<move_to(X, Y+m_state*(H-H/10))<<box(W, H/10);
}
