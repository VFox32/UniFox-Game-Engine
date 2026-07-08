#include "Widget.h"
#include "ufpch.h"

glm::vec2 Widget::Measure(const Constraint& c) {
    if(!(m_DirtyFlags & DirtyFlag::Measure) && m_Measurement.constraint == c) {
        return m_Measurement.size;
    }
    
    glm::vec2 size = OnMeasure(c);

    m_Measurement = {
        c, size
    };

    m_DirtyFlags &= ~DirtyFlag::Measure;

    return size;
}
void Widget::Arrange(const Rect& rect) {
    if(!(m_DirtyFlags & DirtyFlag::Arrange) && m_Arrangement.rect == rect) {
        return;
    }

    OnArrange(rect);

    m_Arrangement = {
        rect
    };

    m_DirtyFlags &= ~DirtyFlag::Arrange;
}

void Widget::InvalidteMeasure() {
    m_DirtyFlags |= DirtyFlag::Measure;
    m_DirtyFlags |= DirtyFlag::Arrange;
    m_DirtyFlags |= DirtyFlag::Paint;

    if(m_Parent) {
        m_Parent->InvalidteMeasure();
    }
}
void Widget::InvalidateArrange() {
    m_DirtyFlags |= DirtyFlag::Arrange;
    m_DirtyFlags |= DirtyFlag::Paint;

    if(m_Parent) {
        m_Parent->InvalidateArrange();
    }
}
void Widget::InvalidatePaint() {
    m_DirtyFlags |= DirtyFlag::Paint;

    if(m_Parent) {
        m_Parent->InvalidatePaint();
    }
}
uint8_t Widget::GetFlags() const {
    return m_DirtyFlags;
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

Button::Button(const LayoutProperty& property) {
    m_Property = property;
}
glm::vec2 Button::OnMeasure(const Constraint& c) {
    glm::vec2 size = {0, 0};

    if(m_Property.h.mode == LengthMode::Pixels) {
        size.x = m_Property.h.size;
    } else if(m_Property.h.mode == LengthMode::Fill) {
        size.x = c.maxSize.x;
    } else if(m_Property.h.mode == LengthMode::Percent) {
        
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
    UniFox::Renderer2D::DrawQuad({pos.x, pos.y, z}, size, 0, m_Style->bgColor);
}