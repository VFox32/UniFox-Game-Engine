#include "UIManager.h"

bool UIManager::OnEvent(UniFox::Event& e) {
    UniFox::Ref<Widget> widget = GetWidget({UniFox::Input::GetMouseX(), 720-UniFox::Input::GetMouseY()});

    // hovered widget
    if(e.GetEventType() == UniFox::EventType::MouseMoved) {
        if(widget != m_Hover) {
            if(m_Hover) {
                m_Hover->GetFlags() &= ~WidgetFlag::Hovered;
                m_Hover->Dispatch(*(new UniFox::WindowLeftEvent()));
            }
            if(widget) {
                widget->GetFlags() |= WidgetFlag::Hovered;
                widget->Dispatch(*(new UniFox::WindowEnteredEvent()));
            }
            m_Hover = widget;
        }
    }
    // focused widget
    if(e.GetEventType() == UniFox::EventType::MouseButtonPressed) {
        if(widget != m_Focus) {
            if(m_Focus) {
                m_Focus->GetFlags() &= ~WidgetFlag::Focused;
                m_Focus->Dispatch(*(new UniFox::WindowUnfocusEvent()));
            }
            if(widget) {
                widget->GetFlags() |= WidgetFlag::Focused;
                widget->Dispatch(*(new UniFox::WindowFocusEvent()));
            }
            m_Focus = widget;
        }
    }

    // widget events
    if(e.GetCategoryFlags() & UniFox::EventCategory::EventCategoryMouse) {
        if(widget) widget->Dispatch(e);
        /*UniFox::Ref<Widget> current = widget;
        while(current) {
            current->Dispatch(e);
            if(e.Handled) break;
            current = current->GetParent();
        }*/
    } else {
        if(m_Focus) m_Focus->Dispatch(e);
    }
    return true;
}

void UIManager::Draw(const float z) const {
    //Constraint c = Constraint(m_Size, m_Size);
    //glm::vec2 size = m_Container->Measure(c);
    //Rect r = Rect({0, 0}, size);
    //m_Container->SetArrangement({r});
    //m_Container->Arrange(r);
    //m_Container->Draw(0.0);
    for(uint32_t i = 0; i < m_Slots.size(); i++) {
        glm::vec2 size = m_Slots[i].widget->Measure(Constraint({0, 0}, {1080, 720}));
        //m_Slots[i].widget->SetArrangement({m_Slots[i].desire.position, size});
        m_Slots[i].widget->Arrange({m_Slots[i].desire.position, size});
        m_Slots[i].widget->Draw(z);
    }
}

void UIManager::AddChild(UniFox::Ref<Widget> child) {
    AddChild(child, ManagerProperty());
}
void UIManager::AddChild(UniFox::Ref<Widget> child, const ManagerProperty& property) {
    m_Slots.push_back(ManagerSlot(child, property));
    child->SetParent(shared_from_this());
    child->InvalidteMeasure();
}

UniFox::Ref<Widget> UIManager::GetChild(const uint32_t index) const {
    return m_Slots[index].widget;
}

uint32_t UIManager::GetChildCount() const {
    return m_Slots.size();
}

UniFox::Ref<Widget> UIManager::GetWidget(const glm::vec2& position) {
    UniFox::Ref<Widget> current = nullptr;

    for(uint32_t i = 0; i < m_Slots.size(); i++) {
        if(m_Slots[i].widget->Contains(position)) {
            current = m_Slots[i].widget;
            break;
        }
    }

    if(!current) return current;

    bool child = true;
    while(current->IsContainer() && child) {
        child = false;
        Container* c = dynamic_cast<Container*>(current.get());
        for(uint32_t i = 0; i < c->GetChildCount(); i++) {
            if(c->GetChild(i)->Contains(position)) {
                current = c->GetChild(i);
                child = true;
                break;
            }
        }
    }

    return current;
}