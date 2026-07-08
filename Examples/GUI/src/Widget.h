#pragma once
#include "UniFox.h"

#include "Style.h"
#include "Constraint.h"

enum DirtyFlag {
    None = 0,
    Measure = 1,
    Arrange = 2,
    Paint = 4
};

class LayoutProperty {
public:
    LayoutProperty(const Length& x = {LengthMode::Pixels, 5}, const Length& y = {LengthMode::Pixels, 5}, const Length& w = {LengthMode::Percent, 0.5}, const Length& h = {LengthMode::Percent, 0.5})
        : x(x), y(y), w(w), h(h) {}

    Length x = {LengthMode::Auto, 0};
    Length y = {LengthMode::Auto, 0};

    Length w = {LengthMode::Auto, 0};
    Length h = {LengthMode::Auto, 0};
};

class Layout;

class Widget : public std::enable_shared_from_this<Widget> {
public:
    glm::vec2 Measure(const Constraint& c);
    void Arrange(const Rect& rect);
    virtual void Draw(const float z) const = 0;
public:
    UniFox::Ref<Widget> GetParent() const;
    void SetParent(UniFox::Ref<Widget> parent);

    LayoutProperty GetProperty() const;
    void SetProperty(const LayoutProperty& property);
    
    UniFox::Ref<Style> GetStyle() const;
    void SetStyle(UniFox::Ref<Style> style);
public:
    ArrangeCache GetArrangement() const;
    MeasureCache GetMeasurement() const;
    void SetArrangement(const ArrangeCache& arrangement);

    void InvalidteMeasure();
    void InvalidateArrange();
    void InvalidatePaint();
    uint8_t GetFlags() const;
protected:
    virtual glm::vec2 OnMeasure(const Constraint& c) = 0;
    virtual void OnArrange(const Rect& rect) = 0;

    UniFox::Ref<Widget> m_Parent = nullptr;
    LayoutProperty m_Property = LayoutProperty();
    UniFox::Ref<Style> m_Style = nullptr;

    MeasureCache m_Measurement = {Constraint(), glm::vec2(0, 0)};
    ArrangeCache m_Arrangement = {Rect()};

    uint8_t m_DirtyFlags = 7;
};

class Button : public Widget {
public:
    Button(const LayoutProperty& propery = LayoutProperty());
    ~Button() = default;

    virtual glm::vec2 OnMeasure(const Constraint& c) override;
    virtual void OnArrange(const Rect& rect) override;
    virtual void Draw(const float z) const override;
};