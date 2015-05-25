#ifndef W_BASEWIDGET_H_INCLUDED
#define W_BASEWIDGET_H_INCLUDED
#include "graphics.hpp"
#include <string>

#define red 255,0,0
#define black 0, 0, 0
#define defColor 100,100,100
#define white 255, 255, 255

using namespace genv;

class w_App;

class w_Widget
{
private:
    w_App* m_parent;
protected:
    static unsigned int wCounter;
    int X, Y, W, H;
    std::string m_label;
    virtual void drawBase(canvas& c);
public:
    bool IsActive;
    enum
    {
        above,
        below,
        before,
        after
    };
    virtual void align (w_Widget* align_to, int distance, int direction=after);

    bool adopt(w_App * parent);
    int x() const {return X;}
    int y() const {return Y;}
    virtual int w() const {return W;}
    virtual int h() const {return H;}
    virtual bool focusable() const {return false;}
    const unsigned int ID;


    virtual void draw(canvas& c) {drawBase(c);}
    virtual void handle_event(event &){return;}
    virtual bool IsMouseOver(const int, const int) const {return false;}

    w_Widget(const int x, const int y, const int w, const int h) :
        X(x), Y(y), W(w), H(h), IsActive(false) , ID(wCounter){++wCounter;}

    w_Widget(const std::string l, const int x, const int y, const int w, const int h) :
        X(x), Y(y), W(w), H(h), m_label(l), IsActive(false) , ID(wCounter){++wCounter;}


    //for w_App
    w_Widget(w_App *parent, const int x, const int y, const int w, const int h) :
        m_parent(parent), X(x), Y(y), W(w), H(h), IsActive(false), ID(wCounter){++wCounter;}

    w_Widget(w_App *parent, const std::string l, const int x, const int y, const int w, const int h):
        m_parent(parent), X(x), Y(y), W(w), H(h), m_label(l), IsActive(false) , ID(wCounter){++wCounter;}

    w_Widget(w_App *parent, const std::string l, const int w, const int h):
        m_parent(parent), W(w), H(h), m_label(l), IsActive(false), ID(wCounter){++wCounter;}

    virtual ~w_Widget(){}
};


const int margin=0;
struct w_Text : public w_Widget
{
    virtual bool focusable() const {return true;}

    w_Text(const w_Widget base) : w_Widget(base){}
    w_Text() : w_Widget(0,0,0,0,0){}
    w_Text(const std::string text): w_Widget(text, 0,0,gout.twidth(text)+margin,gout.cascent()+gout.cdescent()){}
    w_Text(const std::string text, const int x, const int y) :
        w_Widget(text, x, y, gout.twidth(text)+margin, gout.cascent()+gout.cdescent()) {}

    void setText(const std::string text) {m_label=text;}
    std::string getText() {return m_label;}
    void x(const int new_x) {X=new_x;}
    void y(const int new_y) {Y=new_y;}

    void draw(canvas & c);
};

struct w_Control : public w_Widget
{
    void drawBase(canvas& c);
    virtual void handle_event(event &){return;}
    virtual bool focusable () const {return true;}
    bool IsMouseOver(int, int) const;

    w_Control(const w_Widget base) : w_Widget(base){}

    w_Control(const int x, const int y, const int w, const int h) :
        w_Widget(x,y,w,h){}

    w_Control(const std::string l, const int x, const int y, const int w, const int h) :
        w_Widget(l, x, y, w, h){}
};

#endif // W_BASEWIDGET_H_INCLUDED
