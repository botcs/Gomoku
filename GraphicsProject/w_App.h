#ifndef W_APP_H_INCLUDED
#define W_APP_H_INCLUDED

#include <memory>
#include <list>
#include "graphics.hpp"
#include "w_BaseWidget.h"
#include "w_Frame.h"

class w_App
{
    w_Frame* renderer;
    const int XX, YY;
public:
    virtual int hor_space() const {return 20;}
    virtual int ver_space() const {return 20;}
    enum
    {
        exit,
        running
    } state;

    enum lo_ops
    {
        left,
        endl,
        downstream
    }lay_op=left;

    w_Widget *_cursor, *_begin;
    int run();
    virtual bool push(w_Widget* W);

    w_App(const int width, const int height);
    virtual ~w_App() {delete renderer;}
};

w_App&  operator << (w_App& lay_out, w_App::lo_ops layout_oper);
w_App&  operator << (w_App& lay_out, w_Widget* W);



#endif // W_APP_H_INCLUDED
