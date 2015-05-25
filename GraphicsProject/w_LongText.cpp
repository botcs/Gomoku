#include "w_LongText.h"
#include <iostream>
using namespace genv;

w_LongText::w_LongText(const w_Widget base, const std::string file, w_LongText::align type) : w_Control(base)
{
    renderer = new w_Frame(base);

    /**FORMATTING TEXT*/
    const size_t width=(W-2*margin)/gout.twidth(" ");

    std::ifstream f (file.c_str(), std::ifstream::in);

    std::stringstream words, wrapped_text;
    std::string sentence;

    char c;
    while (f.get(c))
    {
        if (c == '\t')
            words << "   ";
        else
            words << c;
    }

    sentence=words.str();

    if(type==wrapped || type==justified)
    {
        std::string::iterator it = sentence.begin();
        std::string::iterator lastSpace = sentence.begin();
        int distanceToWidth = 0;
        while (it != sentence.end())
        {
            while (it != sentence.end() && distanceToWidth < width)
            {
                ++distanceToWidth;
                if (isspace(*it))
                {
                    lastSpace = it;
                    if (width <= distanceToWidth)
                    {
                        break;
                    }
                }
                ++it;
            }
            if (lastSpace != sentence.begin() && width<=distanceToWidth)
            {
                *lastSpace = '\n';
                it=lastSpace;
            }

            //std::cout<<distanceToWidth<<" \n"<<sentence<<"\n\n";
            lastSpace = sentence.begin();
            distanceToWidth = 0;

        }
    }
    wrapped_text<<sentence;
    line_count=0;

    if(type==unformatted || type==wrapped) while (wrapped_text)
        {
            std::string line;
            getline(wrapped_text, line);

            //std::cout<<width<<' '<<line.size()<<'\n';
            renderer->push(new w_Text(line, 0, line_count*(gout.cascent()+gout.cdescent())));
            line_count++;
        }

    if(type==justified) while (wrapped_text)
        {
            std::stringstream ss;
            std::string line, word;
            getline(wrapped_text, line);
            if(line.size()>1)
            {
                ss<<line;
                //special whitespeces now are omitted
                int spaces = 0;
                for (char c : line) if(c==' ')  spaces++;
                std::cout<<"space in line:"<< line_count << ' '<<spaces<<'\n';
                spaces = width-(line.size()-spaces);
                std::vector<std::string> wil; //WORDS IN LINE

                while (ss>>word) wil.push_back(word);
                w_Text * prev_t, *act_t;

                prev_t=new w_Text(wil[0], 0, line_count*(gout.cascent()+gout.cdescent()));
                renderer->push(prev_t);

                int space_px=spaces*gout.twidth(" ")/wil.size()-1;
                for(int i=1; i<wil.size(); i++)
                {
                    act_t = new w_Text(wil[i], 0, line_count*(gout.cascent()+gout.cdescent()));
                    act_t->align(prev_t, space_px, w_Widget::after);
                    renderer->push(act_t);
                    prev_t=act_t;
                    //std::cout<<wil[i-1].size()+i<<'\n';
                }
            } //else renderer->push(new w_Text(line, 0, line_count*(gout.cascent()+gout.cdescent())));

            line_count++;
        }

}

void w_LongText::push_line(std::string line)
{

    renderer->push(new w_Text(line, 0, line_count*(gout.cascent()+gout.cdescent())));
}

void w_LongText::handle_event(genv::event & e)
{

    renderer->handle_event(e);
}

void w_LongText::draw (canvas & c)
{
    renderer->IsActive=IsActive;
    c<<move_to(X+margin, Y+gout.cascent())<<color(black);
    renderer->draw(c);
}
