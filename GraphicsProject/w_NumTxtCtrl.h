#ifndef w_NumTxtCtrl_H_INCLUDED
#define w_NumTxtCtrl_H_INCLUDED

#include "w_BaseWidget.h"
#include "w_Button.h"
#include "w_TextControl.h"

class w_NumTxtCtrl : public w_Control
{
    double Min, Max, Val, Inc;
    w_Button * Add;
    w_Button * Take;
    w_TextControl * KeyInput;

    void refreshKeyInput();
public:
    w_NumTxtCtrl(const int,const int,const int,const double,const double,const unsigned int);
    ~w_NumTxtCtrl(){delete Add; delete Take; delete KeyInput;}

    void handle_event(genv::event&);
    void draw(genv::canvas&);
    void incrVal();
    void decrVal();

    double val() const {return Val;}
    void setval(const double SetVal);
    void push_digit(const int d);
};

#endif // w_NumTxtCtrl_H_INCLUDED
