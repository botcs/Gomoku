#ifndef W_LISTBOX_H_INCLUDED
#define W_LISTBOX_H_INCLUDED
#include <vector>
#include "w_BaseWidget.h"
#include "w_Frame.h"
#include "graphics.hpp"

using namespace genv;

struct _Frame_override : public w_Frame
{
    void handle_event(event e);

    void draw(canvas & c);

    _Frame_override(w_Widget base) : w_Frame(base) {}
};

template <class T>
class w_ListBox : public w_Control
{
    std::vector<T*> m_items;
    int m_choice_ind;

    _Frame_override * renderer;
public:
    void handle_event(event& ev)
    {
        if(ev.keycode==key_up || ev.keycode==key_pgup) SelectPrev();
        else if(ev.keycode==key_down || ev.keycode==key_pgdn) SelectNext();
        else renderer->handle_event(ev);
    }
    void draw(canvas& c)
    {
        renderer->IsActive=IsActive;
        renderer->draw(c);
    }
    void push_back(T*item)
    {
        m_items.push_back(item);
        renderer->push(item);
    }

    void push_front(T*item)
    {
        m_items.push_front(item);
        renderer->push(item);
    }

    void erase_selected()
    {
        typename std::vector<T*>::iterator it;
        it=m_items.begin();
        for (T * item : m_items)
        {
            if(item->IsActive)
            {
                delete item;
                m_items.erase(it);
            }
            it++;
        }

        if(it==m_items.end()) it==m_items.begin();
        (*it)->IsActive=true;
    }

    void SelectNext()
    {
        for (size_t i=0; i<m_items.size(); i++) if(m_items[i]->IsActive)
            {
                m_items[i]->IsActive=false;
                i++;
                m_items[i%m_items.size()]->IsActive=true;
                return;
            }

        if(m_items[0]) m_items[0]->IsActive=true;
    }

    void SelectPrev()
    {
        for (size_t i=0; i<m_items.size(); i++) if(m_items[i]->IsActive)
            {
                m_items[i]->IsActive=false;
                i--;
                m_items[(m_items.size()+i)%m_items.size()]->IsActive=true;
                return;
            }

        if(m_items[0]) m_items[0]->IsActive=true;
    }

    bool select(T* ptr_select_item)
    {
        typename std::vector<T*>::iterator it=m_items.begin();
        for (T * item : m_items)
        {
            if(it==item)
            {
                item->IsActive=true;
                return true;
            }
            it++;
        }
        return false;
    }

    w_ListBox (w_Widget base) : w_Control(base), renderer(new _Frame_override(base)) {};
    ~w_ListBox ()
    {
        for (auto item : m_items) delete item;
    }
};




#endif // W_LISTBOX_H_INCLUDED
