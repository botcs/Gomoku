#include "w_Button.h"
#include <iostream>
using namespace genv;

w_Button::w_Button(const std::string l, const int x, const int y, std::function<void()> f) :
    w_Control(l,x,y, gout.twidth(l)+10, gout.cdescent()+gout.cascent()), callback(f){}


w_Button::w_Button():
    w_Control(0,0,0,0), callback([](){std::cout<<"empty constructor";}) {}


void w_Button::draw(genv::canvas & c)
{
    drawBase(c);
    c<<move_to(X+2, Y+2)<<color(black)<<box(W-4, H-4);
    c<<move_to(X+5, Y+gout.cascent())<<color(white)<<text(m_label);
}

void w_Button::handle_event(event& e)
{
    if (e.button==btn_left || e.keycode==key_enter || e.keycode==key_space) callback();
}
