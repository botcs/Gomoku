#include "w_CheckBox.h"
using namespace genv;
void w_CheckBox::handle_event(event& e)
{
    if(e.button==btn_left && IsMouseOver(e.pos_x, e.pos_y)) m_Check= !m_Check;
    if((e.keycode==key_enter || e.keycode==key_space) && IsActive) m_Check= !m_Check;
}

void w_CheckBox::draw(genv::canvas & c)
{
    drawBase(c);
    c<<move_to(X+W+5, Y+H/2+gout.cdescent())<<color(white)<<text(m_label);
    if(m_Check) c<<move_to(X+W,Y+H)<<color(black)<<line(-W,-H)<<move_to(X+W,Y)<<line(-W, H);
}
