#include "w_Frame.h"
#include <iostream>

const int slider_w=15;
using namespace genv;


w_Frame::w_Frame(const w_Widget base) : w_Control(base), hor_slider(0), ver_slider(0)
{
    if(m_label.size()*gout.twidth(" ")+2*slider_w>W)
        W=m_label.size()*gout.twidth(" ")+2*slider_w;

    in_w=W;
    in_h=H;


    m_frame.open(in_w, in_h);
}

w_Frame::~w_Frame()
{
    for(w_Widget * w : m_widgets) delete w;
    delete hor_slider;
    delete ver_slider;
}

void w_Frame::resize_frame()
{
    int max_x=0, max_y=0;
    for(w_Widget * w : m_widgets)
    {
        if(w->x()+w->w()>max_x) max_x=w->x()+w->w();
        if(w->y()+w->h()>max_y) max_y=w->y()+w->h();
    }

    if(max_x>=W)
    {
        hor_slider=new w_Slider(w_Control(X, Y+H-slider_w, W-slider_w, slider_w), w_Slider::Horizontal);
    } else
    {
        delete hor_slider;
        hor_slider=0;
    }

    if(max_y>=H)
    {
        ver_slider=new w_Slider(w_Control(X+W-slider_w, Y, slider_w, H-slider_w), w_Slider::Vertical);
    } else
    {
        delete ver_slider;
        ver_slider=0;
    }


    in_w=max_x+2*slider_w;
    in_h=max_y+2*slider_w;
    m_frame.open(in_w, in_h);
}

void w_Frame::push(w_Widget* w)
{
    m_widgets.push_back(w);
    resize_frame();
}

void w_Frame::remove_w(const w_Widget* del_w)
{
    std::list<w_Widget *>::iterator i=m_widgets.begin();
    for (w_Widget * w : m_widgets)
    {
        if(w==del_w)
        {
            delete w;
            m_widgets.erase(i);
        }
        i++;
    }
}

void w_Frame::handle_event(event & e)
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
        {
            if(c->focusable())
                c->IsActive=(c->IsMouseOver(calib_ev.pos_x, calib_ev.pos_y));
        }


        if(ver_slider) ver_slider->IsActive=ver_slider->IsMouseOver(e.pos_x, e.pos_y);
        if(hor_slider) hor_slider->IsActive=hor_slider->IsMouseOver(e.pos_x, e.pos_y);
    }

    if(ver_slider && ver_slider->IsActive) ver_slider->handle_event(e);
    if(hor_slider && hor_slider->IsActive) hor_slider->handle_event(e);

    if (e.type!=ev_timer && e.keycode!=key_tab)
        for(w_Widget* w : m_widgets) if(w->IsActive) w->handle_event(e);

    if(e.keycode==key_tab)
    {
        for (std::list<w_Widget*>::iterator i=m_widgets.begin(); i!=m_widgets.end(); i++)
        {
            if((*i)->IsActive)
            {
                (*i)->IsActive=false;
                i++;
                if (!(*i)->focusable())
                {
                    while(!(*i)->focusable())
                    {
                        i++;
                        if(i==m_widgets.end()) i=m_widgets.begin();
                    }
                }
                if(i==m_widgets.end()) i=m_widgets.begin();
                (*i)->IsActive=true;
                break;
            }
        }
    }
}

void w_Frame::draw(canvas & c)
{
    drawBase(c);

    if(!IsActive) for (w_Widget* c : m_widgets) c->IsActive=false;
    if(!IsActive && hor_slider) hor_slider->IsActive=false;
    if(!IsActive && ver_slider) ver_slider->IsActive=false;

    c<<move_to(X-1, Y-1)<<color(black)<<box(W+2,H+2)<<move_to(X,Y)<<color(defColor)<<box(W,H);

    c<<move_to(X+W/10,Y)<<color(defColor)<<box(c.twidth(m_label),-c.cascent())
     <<move_to(X+W/10,Y)<<color(white)<<text(m_label);

    m_frame<<move_to(0, 0)<<color(defColor)<<box_to(in_w-1, in_h-1);

    for (w_Widget* w : m_widgets) w->draw(m_frame);

    int sx=0, sy=0;
    if(hor_slider) sx = hor_slider->state()*(in_w-W);
    if(ver_slider) sy = ver_slider->state()*(in_h-H);

    c<<stamp(m_frame, sx, sy, W, H, X, Y);

    if(hor_slider) hor_slider->draw(c), c<<move_to(X+W-1, Y+H-1)<<color(black)<<box(-slider_w, -slider_w);
    if(ver_slider) ver_slider->draw(c), c<<move_to(X+W-1, Y+H-1)<<color(black)<<box(-slider_w, -slider_w);
}

