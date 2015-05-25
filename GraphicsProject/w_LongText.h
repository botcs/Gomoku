#ifndef W_LONGTEXT_H_INCLUDED
#define W_LONGTEXT_H_INCLUDED
#include "w_BaseWidget.h"
#include "graphics.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include "w_Frame.h"

class w_LongText : public w_Control
{

    int line_count;
    const int margin=0;
    w_Frame * renderer;
public:
    enum align
    {
        unformatted,
        wrapped,
        justified
    };
    void draw(genv::canvas & output_canvas);
    void handle_event(genv::event & handled_event);
    void push_line(std::string line);
    w_LongText(const w_Widget base, const std::string file_name, w_LongText::align=wrapped);
    ~w_LongText(){delete renderer;}
};

#endif // W_LONGTEXT_H_INCLUDED
