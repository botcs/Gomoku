#ifndef W_WINDOW_H
#define W_WINDOW_H
#include "graphics.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <time.h>

#include "w_BaseWidget.h"
#include "w_CheckBox.h"
#include "w_TextControl.h"
#include "w_Button.h"
#include "w_NumTxtCtrl.h"
#include "w_RadioButton.h"

#define defColor 100,100,100
#define clrscr move_to(0, 0)<<color(defColor)<<box_to(XX-1, YY-1)

/** TO DO LIST

    Widget collision checking

    Re-implement the widget handling system

    Develop HotKey manager

    Save the world-Seize the day
*/

class w_Window
{
    static unsigned int FrameCounter;
    const unsigned int XX, YY;
    unsigned int m_PosX, m_PosY;
    genv::event  m_event;
    std::vector<w_Widget*>  m_Widgets;
    std::vector<w_Control*> m_ControlPanel;

    std::vector<w_CheckBox*>    m_CBs;
    std::vector<w_TextControl*> m_TCs;
    std::vector<w_Button*>      m_Buttons;
    std::vector<w_NumTxtCtrl*>  m_NumCs;
    std::vector<w_RadioButton*> m_RBs;

public:
    const unsigned int ID;

    /**MAIN INPUT OF FRAME*/
        void refreshFrame(genv::event& e);

    /**MAIN OUTPUT OF FRAME*/
        genv::canvas c;


    /**EVENT HANDLERS*/
        void selectNext();
        void click(const int MX, const int MY);

    /**FRAME MANIPULATORS*/
        void addCheckBox    (const std::string,const int,const int,const int);
        void addTextControl (const std::string,const int,const int);
        void addButton      (const std::string,const int,const int,std::function<void()>);
        void addNumControl  (const int,const int,const int,const double,const double,const unsigned int);
        void addRButtonSet  (const std::string, const std::vector<std::string>, const int, const int);

    w_Window(const unsigned int, const unsigned int);
    ~w_Window();

    void printValues(std::string LogName);

    w_CheckBox*       GetCB(const int i)     const{return m_CBs[i]; }
    w_TextControl*    GetTC(const int i)     const{return m_TCs[i]; }
    w_Button*         GetButton(const int i) const{return m_Buttons[i]; }
    w_NumTxtCtrl*     GetNumC(const int i)   const{return m_NumCs[i]; }
    w_RadioButton*    GetRadB(const int i)   const{return m_RBs[i]; }
};

#endif // w_Window_H
