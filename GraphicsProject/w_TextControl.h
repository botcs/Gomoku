#ifndef W_TEXTCONTROL_H_INCLUDED
#define W_TEXTCONTROL_H_INCLUDED

#include "w_BaseWidget.h"

using namespace genv;
class w_TextControl : public w_Control
{
    int m_length;
    std::string m_text;
public:
    void draw(genv::canvas & c);
    const std::string Gettext() const {return m_text;}
    void Settext(std::string s) {m_text=s;}
    void handle_event(event&);
    w_TextControl(const int x,const int y,const int w):
        w_Control(x, y, w, gout.cdescent()+gout.cascent()), m_length(w/gout.twidth(" ") ){}

    w_TextControl(std::string s, const int x, const int y) :
        w_Control(x, y, gout.twidth(s)+10, gout.cdescent()+gout.cascent()), m_length(s.size()), m_text(s){}
};

#endif // W_TEXTCONTROL_H_INCLUDED
