#ifndef W_BUTTON_H_INCLUDED
#define W_BUTTON_H_INCLUDED

#include "w_BaseWidget.h"
#include <functional>

class w_Button : public w_Control
{
    std::function<void()> callback;
    int m_HotKey;
public:
    w_Button(const std::string label, const int, const int, std::function<void()>);
    w_Button(const std::string, const int, const int, std::function<void()>, const int);
    w_Button();

    void handle_event(genv::event&);
    void draw(genv::canvas&);
};

#endif // W_BUTTON_H_INCLUDED
