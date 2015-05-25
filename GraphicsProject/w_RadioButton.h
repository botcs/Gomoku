#ifndef W_RADIOBUTTON_H_INCLUDED
#define W_RADIOBUTTON_H_INCLUDED
#include "w_Frame.h"
#include "w_CheckBox.h"
#include "w_Slider.h"
#include <vector>
class w_RadioButton : public w_Control
{
    std::vector<w_CheckBox *> m_RBs;
    std::vector<std::string> m_Options;

    int m_choice_ind;

    int inner_height;
    genv::canvas frame;
    w_Slider* m_slider;
    void resize_frame();

    void btnPushed(genv::event&);

public:
    w_RadioButton(const std::string, const std::vector<std::string>, const int, const int);
    ~w_RadioButton(){for(w_CheckBox* RB : m_RBs) delete RB; delete m_slider;}

    void handle_event(genv::event &);
    void draw(genv::canvas&);

    void add_opt(std::string);
    //void remove_opt(const int); NO DELETION ALLOWED

    void SelectNext();
    void SelectPrev();

    int choiceind()const{return m_choice_ind;}
    const std::string choicestr ()const;
};

#endif // W_RADIOBUTTON_H_INCLUDED
