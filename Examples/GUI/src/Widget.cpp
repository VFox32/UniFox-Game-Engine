#include "Widget.h"
#include "ufpch.h"

glm::vec2 Widget::Measure(const Constraint& c) {
    if(!(m_Flags & WidgetFlag::DirtyMeasure) && m_Measurement.constraint == c) {
        return m_Measurement.size;
    }
    
    glm::vec2 size = OnMeasure(c);

    m_Measurement = {
        c, size
    };

    m_Flags &= ~WidgetFlag::DirtyMeasure;

    return size;
}
void Widget::Arrange(const Rect& rect) {
    if(!(m_Flags & WidgetFlag::DirtyArrange) && m_Arrangement.rect == rect) {
        return;
    }

    OnArrange(rect);

    m_Arrangement = {
        rect
    };

    m_Flags &= ~WidgetFlag::DirtyArrange;
}
bool Widget::Contains(const glm::vec2& pos) {
    glm::vec2 p = pos - m_Arrangement.rect.position;
    return p.x > 0.0 && p.x < m_Arrangement.rect.size.x && p.y > 0.0 && p.y < m_Arrangement.rect.size.y;
}

void Widget::InvalidteMeasure() {
    m_Flags |= WidgetFlag::DirtyMeasure;
    m_Flags |= WidgetFlag::DirtyArrange;
    m_Flags |= WidgetFlag::DirtyPaint;

    if(m_Parent) {
        m_Parent->InvalidteMeasure();
    }
}
void Widget::InvalidateArrange() {
    m_Flags |= WidgetFlag::DirtyArrange;
    m_Flags |= WidgetFlag::DirtyPaint;

    if(m_Parent) {
        m_Parent->InvalidateArrange();
    }
}
void Widget::InvalidatePaint() {
    m_Flags |= WidgetFlag::DirtyPaint;

    if(m_Parent) {
        m_Parent->InvalidatePaint();
    }
}
uint8_t& Widget::GetFlags() {
    return m_Flags;
}
bool Widget::Dispatch(UniFox::Event& e) {
    if(OnEvent(e)) {
        e.Handled = true;
    }

    if(m_EventDispatcher) {
        m_EventDispatcher->Emit(e);
    }

    return e.Handled;
}

UniFox::Ref<Widget> Widget::GetParent() const {
    return m_Parent;
}
void Widget::SetParent(UniFox::Ref<Widget> parent) {
    m_Parent = parent;
}

LayoutProperty Widget::GetProperty() const {
    return m_Property;
}
void  Widget::SetProperty(const LayoutProperty& property) {
    m_Property = property;
}

UniFox::Ref<Style> Widget::GetStyle() const {
    return m_Style;
}
void Widget::SetStyle(UniFox::Ref<Style> style) {
    m_Style = style;
    InvalidatePaint();
}

MeasureCache Widget::GetMeasurement() const {
    return m_Measurement;
}
ArrangeCache Widget::GetArrangement() const {
    return m_Arrangement;
}
void Widget::SetArrangement(const ArrangeCache& arrangement) {
    m_Arrangement = arrangement;
}
UniFox::Ref<EventDispatcher> Widget::Events() {
    if(!m_EventDispatcher) m_EventDispatcher = UniFox::MakeRef<EventDispatcher>();
    return m_EventDispatcher;
};

Button::Button(const LayoutProperty& property) {
    m_Property = property;
}
glm::vec2 Button::OnMeasure(const Constraint& c) {
    glm::vec2 size = {0, 0};

    if(m_Property.w.mode == LengthMode::Pixels) {
        size.x = m_Property.w.size;
    } else if(m_Property.w.mode == LengthMode::Fill) {
        size.x = c.maxSize.x;
    } else if(m_Property.w.mode == LengthMode::Percent) {
        
    } else {
        size.x = c.minSize.x;
    }
    if(m_Property.h.mode == LengthMode::Pixels) {
        size.y = m_Property.h.size;
    } else if(m_Property.h.mode == LengthMode::Fill) {
        size.y = c.maxSize.y;
    } else if(m_Property.h.mode == LengthMode::Percent) {
        
    } else {
        size.y = c.minSize.y;
    }
    if(m_Property.w.mode == LengthMode::Ratio) {
        size.x = size.y * m_Property.w.size;
    } if(m_Property.h.mode == LengthMode::Ratio) {
        size.y = size.x * m_Property.h.size;
    }
    
    return glm::clamp(size, c.minSize, c.maxSize);
}
void Button::OnArrange(const Rect& rect) {
    m_Arrangement = {
        rect
    };
}
void Button::Draw(const float z) const {
    glm::vec2 size = m_Arrangement.rect.size;
    glm::vec2 pos = m_Arrangement.rect.position + size/glm::vec2(2);
    glm::vec4 col = m_Pressed ? m_Style->fgColor : m_Style->bgColor;
    if(m_Flags & WidgetFlag::Hovered) col *= 1.2;
    //UniFox::Renderer2D::DrawQuad({pos.x, pos.y, z}, size, 0, m_Style->bgColor);
    UniFox::Renderer2D::DrawQuad({pos.x, pos.y, z}, size, 0, col);
}
bool Button::OnEvent(UniFox::Event& e) {
    if(e.GetEventType() == UniFox::EventType::MouseButtonPressed) {
        m_Pressed = true;
        return true;
    } if(e.GetEventType() == UniFox::EventType::MouseButtonReleased || e.GetEventType() == UniFox::EventType::WindowLeft) {
        m_Pressed = false;
        return true;
    }
    return false;
}

Slider::Slider(const LayoutProperty& propery) {
    m_Property = propery;
}
glm::vec2 Slider::OnMeasure(const Constraint& c) {
    glm::vec2 size = {0, 0};

    if(m_Property.w.mode == LengthMode::Pixels) {
        size.x = m_Property.w.size;
    } else if(m_Property.w.mode == LengthMode::Fill) {
        size.x = c.maxSize.x;
    } else if(m_Property.w.mode == LengthMode::Percent) {
        
    } else {
        size.x = c.minSize.x;
    }
    if(m_Property.h.mode == LengthMode::Pixels) {
        size.y = m_Property.h.size;
    } else if(m_Property.h.mode == LengthMode::Fill) {
        size.y = c.maxSize.y;
    } else if(m_Property.h.mode == LengthMode::Percent) {
        
    } else {
        size.y = c.minSize.y;
    }
    if(m_Property.w.mode == LengthMode::Ratio) {
        size.x = size.y * m_Property.w.size;
    } if(m_Property.h.mode == LengthMode::Ratio) {
        size.y = size.x * m_Property.h.size;
    }
    
    return glm::clamp(size, c.minSize, c.maxSize);
}
void Slider::OnArrange(const Rect& rect) {
    m_Arrangement = {
        rect
    };
}
void Slider::Draw(const float z) const {
    glm::vec2 size = m_Arrangement.rect.size;
    glm::vec2 pos = m_Arrangement.rect.position + size/glm::vec2(2);
    UniFox::Renderer2D::DrawQuad({pos.x, pos.y, z}, size, 0, m_Style->bgColor);
    float s = glm::min(size.x, size.y);
    glm::vec2 p = m_Arrangement.rect.position + glm::vec2(s/2.0f);
    p.x += m_Ratio * (size.x - s);
    UniFox::Renderer2D::DrawQuad({p.x, p.y, z+0.1}, glm::vec2(s), 0, m_Style->fgColor);
}
bool Slider::OnEvent(UniFox::Event& e) {
    if(e.GetEventType() == UniFox::EventType::MouseButtonPressed) {
        glm::vec2 size = m_Arrangement.rect.size;
        float s = glm::min(size.x, size.y);
        glm::vec2 p = glm::vec2(UniFox::Input::GetMouseX(), UniFox::Input::GetMouseY()) - (m_Arrangement.rect.position + glm::vec2(s/2.0f));
        float r = p.x / (size.x - s);
        SetRatio(glm::clamp(r, 0.0f, 1.0f));
        m_Pressed = true;
        return true;
    } if(e.GetEventType() == UniFox::EventType::MouseButtonReleased || e.GetEventType() == UniFox::EventType::WindowLeft) {
        m_Pressed = false;
        return true;
    }
    if(e.GetEventType() == UniFox::EventType::MouseMoved && m_Pressed) {
        UniFox::MouseMovedEvent* E = dynamic_cast<UniFox::MouseMovedEvent*>(&e);
        glm::vec2 size = m_Arrangement.rect.size;
        float s = glm::min(size.x, size.y);
        glm::vec2 p = glm::vec2(E->GetX(), E->GetY()) - (m_Arrangement.rect.position + glm::vec2(s/2.0f));
        float r = p.x / (size.x - s);
        SetRatio(glm::clamp(r, 0.0f, 1.0f));
        return true;
    }
    return false;
}