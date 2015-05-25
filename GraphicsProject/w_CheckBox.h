#ifndef W_CHECKBOX_H_INCLUDED
#define W_CHECKBOX_H_INCLUDED
#include "w_BaseWidget.h"
#include <iostream>
static int def_box_size=20;
class w_CheckBox : public w_Control
{
    bool m_Check;
public:
    bool Getcheck() const{return m_Check;}
    void handle_event(genv::event& );
    int w() const {return W+5+gout.twidth(m_label);}
    void Setcheck(const bool b){m_Check=b;}

    void draw(genv::canvas & c);
    w_CheckBox(const w_Control base) : w_Control(base), m_Check(false) {};

    w_CheckBox(const std::string l, const int x, const int y, const int w) :
        w_Control(l, x, y, w, w), m_Check(false) {}


    w_CheckBox(const std::string l):w_Control(l,0,0,def_box_size, def_box_size), m_Check(false){};


};


#endif // W_CHECKBOX_H_INCLUDED
