#pragma once
#include "UniFox.h"

#include "Widget.h"
#include "Constraint.h"

enum class Alignment {
    None = 0,
    Left = 1,
    Right = 2,
    Top = 4,
    Bottom = 8
};

class Slot {
public:
    UniFox::Ref<Widget> widget;
};
class Container : public Widget {
public:
    virtual void Draw(const float z) const = 0;

    virtual void AddChild(UniFox::Ref<Widget> child) = 0;
    virtual UniFox::Ref<Widget> GetChild(const uint32_t index = 0) const = 0;
    virtual uint32_t GetChildCount() const = 0;
private:
    virtual glm::vec2 OnMeasure(const Constraint& c) = 0;
    virtual void OnArrange(const Rect& rect) = 0;
};

struct VerticalProperty {
    int row = -1;
    Alignment alignment = Alignment::Left;
};
class VerticalSlot : public Slot {
public:
    VerticalSlot(UniFox::Ref<Widget> Widget, const VerticalProperty& desire) : desire(desire) {widget = Widget;}
    VerticalProperty desire;
    VerticalProperty actual;
};
class VerticalPanel : public Container {
public:
    VerticalPanel(const LayoutProperty& propery = LayoutProperty());
    ~VerticalPanel() = default;

    virtual void Draw(const float z) const override;
    virtual void AddChild(UniFox::Ref<Widget> child) override;
    void AddChild(UniFox::Ref<Widget> child, const VerticalProperty& property);
    virtual UniFox::Ref<Widget> GetChild(const uint32_t index = 0) const override;
    virtual uint32_t GetChildCount() const override;
public:
    void SetPadding(const glm::vec4& padding);
    void SetMargin(const glm::vec4& margin);
private:
    virtual glm::vec2 OnMeasure(const Constraint& c) override;
    virtual void OnArrange(const Rect& rect) override;

    glm::vec4 m_Padding = {0, 0, 0, 0};
    glm::vec4 m_Margin = {0, 0, 0, 0};
    std::vector<VerticalSlot> m_Slots;
};

struct HorizontalProperty {
    int column = -1;
    Alignment alignment = Alignment::Top;
};
class HorizontalSlot : public Slot{
public:
    HorizontalSlot(UniFox::Ref<Widget> Widget, const HorizontalProperty& desire) {widget = Widget;}
    HorizontalProperty desire;
    HorizontalProperty actual;
};
class HorizontalPanel : public Container {
public:
    HorizontalPanel(const LayoutProperty& propery = LayoutProperty());
    ~HorizontalPanel() = default;

    virtual void Draw(const float z) const override;
    virtual void AddChild(UniFox::Ref<Widget> child) override;
    void AddChild(UniFox::Ref<Widget> child, const HorizontalProperty& property);
    virtual UniFox::Ref<Widget> GetChild(const uint32_t index = 0) const override;
    virtual uint32_t GetChildCount() const override;
public:
    void SetPadding(const glm::vec4& padding);
    void SetMargin(const glm::vec4& margin);
private:
    virtual glm::vec2 OnMeasure(const Constraint& c) override;
    virtual void OnArrange(const Rect& rect) override;

    glm::vec4 m_Padding = {0, 0, 0, 0};
    glm::vec4 m_Margin = {0, 0, 0, 0};
    std::vector<HorizontalSlot> m_Slots;
};

struct GridProperty {
    glm::ivec2 coord;
    Alignment alignment = Alignment::None;
};
class GridSlot : public Slot {
public:
    GridSlot(UniFox::Ref<Widget> Widget, const GridProperty& desire) {widget = Widget;}
    GridProperty desire;
    GridProperty actual;
};
class GridPanel : public Container {
public:
    GridPanel(const glm::ivec2& size = {1, 1});
    ~GridPanel() = default;

    virtual void Draw(const float z) const override;
    virtual void AddChild(UniFox::Ref<Widget> child) override;
    void AddChild(UniFox::Ref<Widget> child, const GridProperty& propery);
    virtual UniFox::Ref<Widget> GetChild(const uint32_t index = 0) const override;
    virtual uint32_t GetChildCount() const override;
public:
    void SetPadding(const glm::vec4& padding);
    void SetMargin(const glm::vec4& margin);
private:
    virtual glm::vec2 OnMeasure(const Constraint& c) override;
    virtual void OnArrange(const Rect& rect) override;

    glm::ivec2 m_Size = {1, 1};

    glm::vec4 m_Padding = {0, 0, 0, 0};
    glm::vec4 m_Margin = {0, 0, 0, 0};
    std::vector<GridSlot> m_Slots;
};

//dock layout
//flex layout
//abs  layout