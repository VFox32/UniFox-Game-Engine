#include "Container.h"
#include "ufpch.h"

VerticalPanel::VerticalPanel(const LayoutProperty& propery) {
    m_Property = propery;
}
glm::vec2 VerticalPanel::OnMeasure(const Constraint& c) {
    glm::vec2 total = {m_Padding.x+m_Padding.z, m_Padding.y+m_Padding.w};

    for(uint32_t i = 0; i < m_Slots.size(); i++) {
        glm::vec2 size = m_Slots[i].widget->Measure({{0, 0}, {c.maxSize.x, INFINITE}});
        total.x = glm::max(total.x, size.x);
        total.y += size.y;
    }
    total.y += m_Margin.y * (m_Slots.size() - 1);

    if(m_Property.w.mode == LengthMode::Pixels) {
        total.x = m_Property.w.size;
    } else if(m_Property.w.mode == LengthMode::Fill) {
        total.x = glm::max(total.x, c.maxSize.x);
    } else if(m_Property.w.mode == LengthMode::Percent) {
        
    } else {
        total.x = glm::max(total.x, c.minSize.x);
    }
    if(m_Property.h.mode == LengthMode::Pixels) {
        total.y = m_Property.h.size;
    } else if(m_Property.h.mode == LengthMode::Fill) {
        total.y = glm::max(total.y, c.maxSize.y);
    } else if(m_Property.h.mode == LengthMode::Percent) {
        
    } else {
        total.y = glm::max(total.y, c.minSize.y);
    }
    if(m_Property.w.mode == LengthMode::Ratio) {
        total.x = total.y * m_Property.w.size;
    } if(m_Property.h.mode == LengthMode::Ratio) {
        total.y = total.x * m_Property.h.size;
    }

    total = glm::clamp(total, c.minSize, c.maxSize);

    return total;
}
void VerticalPanel::OnArrange(const Rect& rect) {
    glm::vec2 pos = rect.position + glm::vec2(m_Padding.x, m_Padding.y);
    glm::vec2 total = rect.size - glm::vec2(m_Padding.x+m_Padding.z, m_Padding.y+m_Padding.w) - glm::vec2(0, m_Margin.y*(m_Slots.size()-1));
    glm::vec2 size = {0, 0};

    glm::vec2 totalDesire = {0, 0};
    for(uint32_t i = 0; i < m_Slots.size(); i++) {
        glm::vec2 size = m_Slots[i].widget->GetMeasurement().size;
        totalDesire.x = glm::max(totalDesire.x, size.x);
        totalDesire.y += size.y + m_Margin.y;
    }

    for(uint32_t i = 0; i < m_Slots.size(); i++) {
        size = m_Slots[i].widget->GetMeasurement().size;
        size = glm::clamp(size, glm::vec2(0), glm::vec2(total.x, (size.y/totalDesire.y)*total.y));
        Alignment a = m_Slots[i].desire.alignment;
        if(a == Alignment::Left)
            m_Slots[i].widget->Arrange({pos, size});
        else if(a == Alignment::Right)
            m_Slots[i].widget->Arrange({{pos.x + (total.x-size.x), pos.y}, size});
        else if(a == Alignment::None)
            m_Slots[i].widget->Arrange({{pos.x + 0.5*(total.x-size.x), pos.y}, size});
        pos.y += size.y + m_Margin.y;
    }
}
void VerticalPanel::Draw(const float z) const {
    glm::vec2 size = m_Arrangement.rect.size;
    glm::vec2 pos = m_Arrangement.rect.position + size/glm::vec2(2);
    UniFox::Renderer2D::DrawQuad({pos.x, pos.y, z}, size, 0, m_Style->fgColor);

    for(uint32_t i = 0; i < m_Slots.size(); i++) {
        m_Slots[i].widget->Draw(z + 0.1);
    }
}
void VerticalPanel::AddChild(UniFox::Ref<Widget> child) {
    AddChild(child, VerticalProperty());
}
void VerticalPanel::AddChild(UniFox::Ref<Widget> child, const VerticalProperty& property) {
    m_Slots.push_back(VerticalSlot(child, property));
    child->SetParent(shared_from_this());
    child->InvalidteMeasure();
}
void VerticalPanel::SetPadding(const glm::vec4& padding) {
    m_Padding = padding;
    InvalidteMeasure();
}
void VerticalPanel::SetMargin(const glm::vec2& margin) {
    m_Margin = margin;
    InvalidteMeasure();
}
UniFox::Ref<Widget> VerticalPanel::GetChild(const uint32_t index) const {
    return m_Slots[index].widget;
}
uint32_t VerticalPanel::GetChildCount() const {
    return m_Slots.size();
}

HorizontalPanel::HorizontalPanel(const LayoutProperty& propery) {
    m_Property = propery;
}
glm::vec2 HorizontalPanel::OnMeasure(const Constraint& c) {
    glm::vec2 total = {m_Padding.x+m_Padding.z, m_Padding.y+m_Padding.w};

    for(uint32_t i = 0; i < m_Slots.size(); i++) {
        glm::vec2 size = m_Slots[i].widget->Measure({{0, 0}, {c.maxSize.x, INFINITE}});
        total.x += size.x;
        total.y = glm::max(total.y, size.y);
    }
    total.x += m_Margin.x * (m_Slots.size() - 1);

    if(m_Property.w.mode == LengthMode::Pixels) {
        total.x = m_Property.w.size;
    } else if(m_Property.w.mode == LengthMode::Fill) {
        total.x = glm::max(total.x, c.maxSize.x);
    } else if(m_Property.w.mode == LengthMode::Percent) {
        
    } else {
        total.x = glm::max(total.x, c.minSize.x);
    }
    if(m_Property.h.mode == LengthMode::Pixels) {
        total.y = m_Property.h.size;
    } else if(m_Property.h.mode == LengthMode::Fill) {
        total.y = glm::max(total.y, c.maxSize.y);
    } else if(m_Property.h.mode == LengthMode::Percent) {
        
    } else {
        total.y = glm::max(total.y, c.minSize.y);
    }
    if(m_Property.w.mode == LengthMode::Ratio) {
        total.x = total.y * m_Property.w.size;
    } if(m_Property.h.mode == LengthMode::Ratio) {
        total.y = total.x * m_Property.h.size;
    }

    total = glm::clamp(total, c.minSize, c.maxSize);

    return total;
}
void HorizontalPanel::OnArrange(const Rect& rect) {
    glm::vec2 pos = rect.position + glm::vec2(m_Padding.x, m_Padding.y);
    glm::vec2 total = rect.size - glm::vec2(m_Padding.x+m_Padding.z, m_Padding.y+m_Padding.w) - glm::vec2(m_Margin.x*(m_Slots.size()-1), 0);
    glm::vec2 size = {0, 0};

    glm::vec2 totalDesire = {0, 0};
    for(uint32_t i = 0; i < m_Slots.size(); i++) {
        glm::vec2 size = m_Slots[i].widget->GetMeasurement().size;
        totalDesire.x += size.x + m_Margin.x;
        totalDesire.y = glm::max(totalDesire.y, size.y);
    }

    for(uint32_t i = 0; i < m_Slots.size(); i++) {
        size = m_Slots[i].widget->GetMeasurement().size;
        size = glm::clamp(size, glm::vec2(0), glm::vec2((size.x/totalDesire.x)*total.x, total.y));
        Alignment a = m_Slots[i].desire.alignment;
        if(a == Alignment::Bottom)
            m_Slots[i].widget->Arrange({pos, size});
        else if(a == Alignment::Top)
            m_Slots[i].widget->Arrange({{pos.x, pos.y + (total.y-size.y)}, size});
        else if(a == Alignment::None)
            m_Slots[i].widget->Arrange({{pos.x, pos.y + 0.5*(total.y-size.y)}, size});
        pos.x += size.x + m_Margin.x;
    }
}
void HorizontalPanel::Draw(const float z) const {
    glm::vec2 size = m_Arrangement.rect.size;
    glm::vec2 pos = m_Arrangement.rect.position + size/glm::vec2(2);
    UniFox::Renderer2D::DrawQuad({pos.x, pos.y, z}, size, 0, m_Style->fgColor);

    for(uint32_t i = 0; i < m_Slots.size(); i++) {
        m_Slots[i].widget->Draw(z + 0.1);
    }
}
void HorizontalPanel::AddChild(UniFox::Ref<Widget> child) {
    AddChild(child, HorizontalProperty());
}
void HorizontalPanel::AddChild(UniFox::Ref<Widget> child, const HorizontalProperty& property) {
    m_Slots.push_back(HorizontalSlot(child, property));
    child->SetParent(shared_from_this());
    child->InvalidteMeasure();
}
void HorizontalPanel::SetPadding(const glm::vec4& padding) {
    m_Padding = padding;
    InvalidteMeasure();
}
void HorizontalPanel::SetMargin(const glm::vec2& margin) {
    m_Margin = margin;
    InvalidteMeasure();
}
UniFox::Ref<Widget> HorizontalPanel::GetChild(const uint32_t index) const {
    return m_Slots[index].widget;
}
uint32_t HorizontalPanel::GetChildCount() const {
    return m_Slots.size();
}

GridPanel::GridPanel(const glm::ivec2& size) 
    : m_Size(size) {
}
void GridPanel::Draw(const float z) const {
    glm::vec2 size = m_Arrangement.rect.size;
    glm::vec2 pos = m_Arrangement.rect.position + size/glm::vec2(2);
    UniFox::Renderer2D::DrawQuad({pos.x, pos.y, z}, size, 0, m_Style->fgColor);

    for(uint32_t i = 0; i < m_Slots.size(); i++) {
        m_Slots[i].widget->Draw(z + 0.1);
    }
}
void GridPanel::AddChild(UniFox::Ref<Widget> child) {
    AddChild(child, GridProperty());
}
void GridPanel::AddChild(UniFox::Ref<Widget> child, const GridProperty& property) {
    m_Slots.push_back(GridSlot(child, property));
    child->SetParent(shared_from_this());
    child->InvalidteMeasure();
}
void GridPanel::SetPadding(const glm::vec4& padding) {
    m_Padding = padding;
    InvalidteMeasure();
}
void GridPanel::SetMargin(const glm::vec4& margin) {
    m_Margin = margin;
    InvalidteMeasure();
}
glm::vec2 GridPanel::OnMeasure(const Constraint& c) {
    glm::vec2 total = {0.0, 0.0};

    for(uint32_t x = 0; x < m_Size.x; x++) {
        float max = 0.0f;
        for(uint32_t y = 0; y < m_Size.y; y++) {
            uint32_t i = x + y*m_Size.x;
            if(i > m_Slots.size()) break;
            max = glm::max(max, m_Slots[i].widget->Measure({{0, 0}, {c.maxSize.x, INFINITE}}).x);
        }
        total.x += max + m_Padding.x;
    }

    for(uint32_t y = 0; y < m_Size.y; y++) {
        float max = 0.0f;
        for(uint32_t x = 0; x < m_Size.x; x++) {
            uint32_t i = x + y*m_Size.x;
            if(i > m_Slots.size()) break;
            max = glm::max(max, m_Slots[i].widget->Measure(c).y);
        }
        total.y += max + m_Padding.y;
    }

    if(m_Property.w.mode == LengthMode::Pixels) {
        total.x = m_Property.w.size;
    } else if(m_Property.w.mode == LengthMode::Fill) {
        total.x = c.maxSize.x;
    } else if(m_Property.w.mode == LengthMode::Percent) {
        
    } else {
    }
    if(m_Property.h.mode == LengthMode::Pixels) {
        total.y = m_Property.h.size;
    } else if(m_Property.h.mode == LengthMode::Fill) {
        total.y = c.maxSize.y;
    } else if(m_Property.h.mode == LengthMode::Percent) {
        
    } else {
    }
    if(m_Property.w.mode == LengthMode::Ratio) {
        total.x = total.y * m_Property.w.size;
    } if(m_Property.h.mode == LengthMode::Ratio) {
        total.y = total.x * m_Property.h.size;
    }

    return glm::clamp(total, c.minSize, c.maxSize);
}
void GridPanel::OnArrange(const Rect& rect) {

}
UniFox::Ref<Widget> GridPanel::GetChild(const uint32_t index) const {
    return m_Slots[index].widget;
}
uint32_t GridPanel::GetChildCount() const {
    return m_Slots.size();
}