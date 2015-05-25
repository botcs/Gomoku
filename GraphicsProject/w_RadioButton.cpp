#include "w_RadioButton.h"
using namespace genv;
const int RBSize = 20;
const int Space=5;

w_RadioButton::w_RadioButton(const std::string l, const std::vector<std::string> opts, const int x, const int y):
    w_Control(l,x,y,0,0),
    m_Options(opts),
    m_choice_ind(opts.size()),
    m_slider(0)
    {
        size_t LongestStrLength=0;
        for (std::string s : m_Options) if(s.size()>LongestStrLength) LongestStrLength=s.size();
        if (LongestStrLength<l.size()) W=l.size()*gout.twidth(" ")+2*RBSize;
            else W=LongestStrLength*gout.twidth(" ")+3*RBSize;

        H=m_Options.size()*(RBSize+Space)+Space;

        for (size_t i=0; i<m_Options.size(); i++)
        {
            std::string &s=m_Options[i];
            m_RBs.push_back(new w_CheckBox(s,Space,i*(RBSize+Space)+Space, RBSize));
        }
        frame.open(W,H);
        inner_height=H;
    }

const std::string w_RadioButton::choicestr ()const
{
    if(m_choice_ind<m_Options.size())
        return m_Options[m_choice_ind];
    else return std::string("!NO SELECT!");
}

void w_RadioButton::SelectNext()
{
    for (size_t i=0; i<m_RBs.size(); i++) if(m_RBs[i]->IsActive)
    {
        m_RBs[i]->IsActive=false;
        i++;
        m_RBs[i%m_RBs.size()]->IsActive=true;
        return;
    }

    m_RBs[0]->IsActive=true;
}

void w_RadioButton::SelectPrev()
{
    for (size_t i=0; i<m_RBs.size(); i++) if(m_RBs[i]->IsActive)
    {
        m_RBs[i]->IsActive=false;
        i--;
        m_RBs[(m_RBs.size()+i)%m_RBs.size()]->IsActive=true;
        return;
    }

    m_RBs[0]->IsActive=true;
}

void w_RadioButton::resize_frame()
{
    size_t LongestStrLength=0;
    for (std::string s : m_Options) if(s.size()>LongestStrLength) LongestStrLength=s.size();
    if (LongestStrLength<m_label.size()) W=m_label.size()*gout.twidth(" ")+2*RBSize;
        else W=LongestStrLength*gout.twidth(" ")+3*RBSize;

    inner_height=m_Options.size()*(RBSize+Space)+Space;


    frame.open(W-Space, inner_height);
}

void w_RadioButton::add_opt(std::string s)
{
    m_Options.push_back(s);

    m_slider=new w_Slider(w_Control(X+W-Space, Y, 2*Space, H), w_Slider::Vertical);

    resize_frame();

    int i=m_Options.size()-1;
    {
        std::string &s=m_Options[i];
        m_RBs.push_back(new w_CheckBox(s,Space,i*(RBSize+Space)+Space, RBSize));
    }


    for (w_CheckBox* RB : m_RBs) RB->IsActive=false;
    m_choice_ind=m_Options.size();
    IsActive=false;
}
/* NO NEED OF REMOVING OPTIONS
void w_RadioButton::remove_opt(const int i)
{
    if (i<0 || i>=m_RBs.size()) return;

    delete m_RBs[i];
    m_RBs.erase(m_RBs.begin()+i);
}
*/

void w_RadioButton::btnPushed(event& e)
{
    bool NoSelect=true;

    for (size_t i=0; i<m_RBs.size(); i++)
    {
        m_RBs[i]->Setcheck(false);
        if(m_RBs[i]->IsActive)
        {
            m_RBs[i]->handle_event(e);
            if(m_RBs[i]->Getcheck())
            {
                m_choice_ind=i;
                NoSelect=false;
            }
        }
    }


    if(NoSelect) m_choice_ind=m_RBs.size();
}

void w_RadioButton::handle_event(event& e)
{

    int calib=0;
    if(m_slider) calib=m_slider->state()*(inner_height-H);

    if(e.button==btn_left)
    {
        for (w_CheckBox* RB : m_RBs)
        {
            RB->IsActive=(RB->IsMouseOver(e.pos_x-X, e.pos_y-Y+calib));
        }
        btnPushed(e);

        if(m_slider) m_slider->IsActive=m_slider->IsMouseOver(e.pos_x, e.pos_y);
    }

    if(m_slider && m_slider->IsActive) m_slider->handle_event(e);

    if(e.keycode==key_up)  SelectPrev();
    if(e.keycode==key_down)SelectNext();
    if(e.keycode==key_space || e.keycode==key_enter) btnPushed(e);
}

void w_RadioButton::draw(canvas& c)
{
    drawBase(c);
    if(!IsActive) for (w_CheckBox* RB : m_RBs) RB->IsActive=false;

    c<<move_to(X-1, Y-1)<<color(black)<<box(W+2,H+2)<<move_to(X,Y)<<color(defColor)<<box(W,H);

    c<<move_to(X+Space,Y)<<color(defColor)<<box(c.twidth(m_label),-c.cascent())
     <<move_to(X+Space,Y)<<color(white)<<text(m_label);

    if(m_slider) m_slider->draw(c);

    frame<<move_to(0, 0)<<color(defColor)<<box(W-Space, inner_height);
    for (w_CheckBox* RB : m_RBs) RB->draw(frame);

    if(m_slider) c<<stamp(frame,  0, m_slider->state()*(inner_height-H), W, H, X, Y);
    else  c<<stamp(frame,  0, 0, W-Space, H, X, Y);
}
