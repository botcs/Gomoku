#include "w_NumTxtCtrl.h"
#define maxof(a, b) a>b ? a : b
#define minof(a,b) a>b ? b:a
#include <iostream>


using namespace genv;

#include <sstream>
template <typename T>
std::string NumberToString ( T Number )
{
     std::ostringstream ss;
     ss << Number;
     return ss.str();
}

double StringToDouble( const std::string& s )
 {
   std::istringstream i(s);
   double x;
   if (!(i >> x))
     return 0;
   return x;
 }



w_NumTxtCtrl::w_NumTxtCtrl
    (const int x,
     const int y,
     const int w,
     const double minVal,
     const double maxVal,
     const unsigned int steps):
    w_Control(x,y,w,gout.cdescent()+gout.cascent()),
    Min(minof(minVal,maxVal)),
    Max(maxof(minVal,maxVal)),
    Val((Max+Min)/2.0),
    Inc((Max-Min)/double(steps)),
    Add(new w_Button("+", X+W-gout.twidth("+")-10, Y, [this](){this->incrVal();})),
    Take(new w_Button("-", X, Y, [this](){this->decrVal();})),
    KeyInput(new w_TextControl(X+gout.twidth("-")+10, Y, w-gout.twidth("+-")-20))
    {
        KeyInput->Settext(NumberToString(Val));
    }

void w_NumTxtCtrl::incrVal()
{
    if(Val+Inc<Max) Val+=Inc;
        else Val=Max;

    KeyInput->Settext(NumberToString(Val));
}
void w_NumTxtCtrl::decrVal()
{
    if(Val-Inc>Min) Val-=Inc;
        else Val=Min;

    KeyInput->Settext(NumberToString(Val));
}

void w_NumTxtCtrl::draw(genv::canvas & c)
{
    if(!IsActive) KeyInput->IsActive=false, refreshKeyInput();
    drawBase(c);
    Add->draw(c);
    Take->draw(c);
    KeyInput->draw(c);
    //c<<move_to(X+gout.twidth("-")+15, Y+gout.cascent())<<text(NumberToString(Val));
}

void w_NumTxtCtrl::refreshKeyInput()
{
    double SetVal=StringToDouble(KeyInput->Gettext());
    if(SetVal>=Min && SetVal<=Max) Val=SetVal;
    if(SetVal<Min) Val=Min;
    if(SetVal>Max) Val=Max;
    KeyInput->IsActive=false;
    KeyInput->Settext(NumberToString(Val));
}

void w_NumTxtCtrl::setval(const double SetVal)
{
    Val=SetVal;
    if(SetVal>=Min && SetVal<=Max) Val=SetVal;
    if(SetVal<Min) Val=Min;
    if(SetVal>Max) Val=Max;
    KeyInput->IsActive=false;

    KeyInput->Settext(NumberToString(Val));
}

void w_NumTxtCtrl::push_digit(const int d)
{
    if(d<10 && d>=0)
    {
        Val*=10;
        Val+=d;
    }
    KeyInput->Settext(NumberToString(Val));
}

void w_NumTxtCtrl::handle_event(event& e)
{
    if(e.button==btn_left)
    {
        if(Add->IsMouseOver(e.pos_x, e.pos_y))          Add->handle_event(e);
        if(Take->IsMouseOver(e.pos_x, e.pos_y))         Take->handle_event(e);
    }
    if(e.keycode==key_up || e.keycode==key_pgup)    incrVal();
    if(e.keycode==key_down || e.keycode==key_pgdn)  decrVal();

    if((e.keycode>=48 && e.keycode<=57) || e.keycode==key_backspace || e.keycode=='.' || e.keycode=='-')
    {
        KeyInput->IsActive=true;
        KeyInput->handle_event(e);
    }

    if(e.keycode==key_enter) refreshKeyInput();
}
