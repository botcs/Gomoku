#include "w_TextControl.h"


void w_TextControl::handle_event(event& e)
{
    if(e.type!=ev_key) return;
    if(e.keycode==key_backspace) m_text=m_text.substr(0, m_text.size()-1);
    if(e.keycode!=key_backspace && e.keycode>31 && e.keycode<256)  m_text+=char(e.keycode);
    if(W<gout.twidth(m_text)+10) m_text=m_text.substr(0, m_text.size()-1);
}

void w_TextControl::draw(genv::canvas & c)
{
    drawBase(c);
    c<<color(black)<<move_to(X+5, Y+gout.cascent())<<text(m_text);
    if(IsActive)
        c<<text('|');
}
