#include "w_ListBox.h"

const int slider_w=15;




void _Frame_override::draw(canvas & c)
{
    drawBase(c);

    //if(!IsActive) for (w_Widget* c : m_widgets) c->IsActive=false;
    if(!IsActive && hor_slider) hor_slider->IsActive=false;
    if(!IsActive && ver_slider) ver_slider->IsActive=false;

    c<<move_to(X-1, Y-1)<<color(black)<<box(W+2,H+2)<<move_to(X,Y)<<color(defColor)<<box(W,H);

    c<<move_to(X+W/10,Y)<<color(defColor)<<box(c.twidth(m_label),-c.cascent())
     <<move_to(X+W/10,Y)<<color(white)<<text(m_label);

    m_frame<<move_to(0, 0)<<color(defColor)<<box_to(in_w-1, in_h-1);

    for (w_Widget* w : m_widgets)
    {
        if(w->IsActive) m_frame<<color(red)<<move_to(w->x(), w->y()-5)<<box(W-5, w->h()+10);
        w->draw(m_frame);
    }

    int sx=0, sy=0;
    if(hor_slider) sx = hor_slider->state()*(in_w-W);
    if(ver_slider) sy = ver_slider->state()*(in_h-H);

    c<<stamp(m_frame, sx, sy, W, H, X, Y);

    if(hor_slider) hor_slider->draw(c), c<<move_to(X+W-1, Y+H-1)<<color(black)<<box(-slider_w, -slider_w);
    if(ver_slider) ver_slider->draw(c), c<<move_to(X+W-1, Y+H-1)<<color(black)<<box(-slider_w, -slider_w);
}

void _Frame_override::handle_event(event e)
{
    int calib_x=0, calib_y=0;
    if(hor_slider) calib_x=hor_slider->state()*(in_w-W);
    if(ver_slider) calib_y=ver_slider->state()*(in_h-H);
    event calib_ev=e;
    calib_ev.pos_x+=calib_x;
    calib_ev.pos_y+=calib_y;

    if(e.button==btn_left)
    {
        for (w_Widget* c : m_widgets)
            if(c->IsMouseOver(calib_ev.pos_x, calib_ev.pos_y)) c->IsActive=!c->IsActive;

        if(ver_slider) ver_slider->IsActive=ver_slider->IsMouseOver(e.pos_x, e.pos_y);
        if(hor_slider) hor_slider->IsActive=hor_slider->IsMouseOver(e.pos_x, e.pos_y);
    }

    if(ver_slider && ver_slider->IsActive) ver_slider->handle_event(e);
    if(hor_slider && hor_slider->IsActive) hor_slider->handle_event(e);

    for(w_Widget* c : m_widgets) if(c->IsActive) c->handle_event(calib_ev);

}
