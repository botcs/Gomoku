#include "w_Window.h"

using namespace genv;

unsigned int w_Window::FrameCounter=0;

w_Window::w_Window(const unsigned int X, const unsigned int Y) : XX(X), YY(Y), ID(FrameCounter)
{
    c.open(XX, YY);
    FrameCounter++;
}

w_Window::~w_Window()
{
    for(w_Widget* w : m_Widgets) delete w;
    FrameCounter--;
}

void w_Window::click(const int MX, const int MY)
{
    for(w_Control* w: m_ControlPanel)
    {
        if(w->IsMouseOver(MX, MY)) w->IsActive=true;
            else w->IsActive=false;
    }
}

void w_Window::selectNext()
{
    for (size_t i=0; i<m_ControlPanel.size(); i++)
    {
        if(m_ControlPanel[i]->IsActive)
        {

            m_ControlPanel[i]->IsActive=false;
            i++;
            m_ControlPanel[i%m_ControlPanel.size()]->IsActive=true;
            return;
        }
    }

    m_ControlPanel[0]->IsActive=true;
}

void w_Window::refreshFrame(genv::event& ev)
{
    c<<clrscr;
    //Handle event
    m_event=ev;

    if (ev.type==ev_mouse)
    {
        m_PosX=ev.pos_x;
        m_PosY=ev.pos_y;
        //std::cout<<"canvas: "<<m_PosX<<' '<<m_PosY<<'\n';
    }

    if(ev.button==btn_right){};

    if(ev.button==btn_middle){};

    if(ev.button==btn_left) click(m_PosX, m_PosY);

    if(ev.keycode==key_tab) selectNext();


    //Pass Event to control objects to handle
    if (ev.keycode!=key_tab && ev.type!=ev_timer)
    {
        for(w_Control* w: m_ControlPanel)
        {
            if(w->IsActive) w->handle_event(ev);
        }
    }


    for (w_Widget* w : m_Widgets)
    {
        w->draw(c);
    }
    refresh(c);
}

void w_Window::addCheckBox(const std::string l, const int x, const int y, const int w)
{
    w_CheckBox* CB=new w_CheckBox(l, x, y, w);
    m_CBs.push_back(CB);
    m_ControlPanel.push_back(CB);
    m_Widgets.push_back(CB);
}
void w_Window::addTextControl(const std::string l, const int x, const int y)
{
    w_TextControl* TC=new w_TextControl(l,x,y);
    m_TCs.push_back(TC);
    m_ControlPanel.push_back(TC);
    m_Widgets.push_back(TC);
}
void w_Window::addButton(const std::string l, const int x, const int y, std::function<void()> f)
{
    w_Button* B=new w_Button(l,x,y,f);
    m_Buttons.push_back(B);
    m_ControlPanel.push_back(B);
    m_Widgets.push_back(B);
}
void w_Window::addNumControl
    (const int x,
     const int y,
     const int w,
     const double minVal,
     const double maxVal,
     const unsigned int steps)
 {
    w_NumTxtCtrl* NC=new w_NumTxtCtrl(x,y,w,minVal,maxVal,steps);
    m_NumCs.push_back(NC);
    m_ControlPanel.push_back(NC);
    m_Widgets.push_back(NC);
 }
void w_Window::addRButtonSet(const std::string l, const std::vector<std::string> opts, const int x, const int y)
{
    w_RadioButton* RB = new w_RadioButton(l,opts,x,y);
    m_RBs.push_back(RB);
    m_ControlPanel.push_back(RB);
    m_Widgets.push_back(RB);
}
/**FOR asctime function*/
    time_t rawtime;
    struct tm * timeinfo;

void w_Window::printValues(std::string LogName)
{

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    std::ofstream log;
    log.open(LogName.c_str());
    log <<"FRAME PRINTER"                   <<"\n"
        <<"*************************"       <<"\n"
        <<"FRAME NUMBER "<<ID                <<"\n"
        <<"*************************"       <<"\n"
        <<"TIME: "<<asctime (timeinfo)      <<"\n"
        <<"*************************"       <<"\n"
        <<"Widget ID"<<"\t"<<"Value"        <<"\n"
        <<"*************************"       <<"\n";


    log<<"CheckBoxes current state:\n";
    for (w_CheckBox* CB: m_CBs)     log<<"#"<<CB->ID<<"\t"<<CB->Getcheck()<<'\n';

    log<<"\nTextControls current text:\n";
    for (w_TextControl* TC: m_TCs)  log<<"#"<<TC->ID<<"\t"<<TC->Gettext()<<'\n';

    log<<"\nNumericControls current value:\n";
    for(w_NumTxtCtrl* NC: m_NumCs)  log<<"#"<<NC->ID<<"\t"<<NC->Getval()<<'\n';

    log<<"\nRadioButtons current state :\n";
    for(w_RadioButton* RB : m_RBs)  log<<"#"<<RB->ID<<"\t"<<RB->choicestr()<<"["<<RB->choiceind()<<"]"<<'\n';


}
