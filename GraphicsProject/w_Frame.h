#ifndef W_FRAME_H
#define W_FRAME_H
#include "graphics.hpp"
#include <list>

#include "w_Slider.h"
#include "w_BaseWidget.h"



class w_Frame : public w_Control
{
protected:
    int in_h, in_w;
    genv::canvas m_frame;
    w_Slider* hor_slider;
    w_Slider* ver_slider;
    std::list<w_Widget*>  m_widgets;
    //std::list<w_Control*> m_control;

    void resize_frame();

public:
    event calib_ev;
    int inner_h() const {return in_h;}
    int inner_w() const {return in_w;}

    virtual void draw(genv::canvas&);
    virtual void push(w_Widget*);
    virtual void remove_w(const w_Widget*);
    virtual void handle_event(genv::event&);

    w_Frame(const w_Widget base);
    ~w_Frame();

};

#endif // W_FRAME_H
