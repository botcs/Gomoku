#ifndef W_SLIDER_H_INCLUDED
#define W_SLIDER_H_INCLUDED
#include "w_BaseWidget.h"
#include "graphics.hpp"

class w_Slider : public w_Control
{
    double m_state;
    bool m_direction, m_pressed;
public:
    enum
    {
        Horizontal,
        Vertical
    };
    double state() const {return m_state;}
    w_Slider(w_Control base, bool direction) : w_Control(base), m_state(0), m_direction(direction) {}
    void handle_event(genv::event&);
    void draw(genv::canvas&);
};

#endif // W_SLIDER_H_INCLUDED
