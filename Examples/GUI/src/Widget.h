#pragma once
#include "UniFox.h"

#include "Style.h"
#include "Constraint.h"

enum WidgetFlag {
    None = 0,
    Hovered = 1,
    Focused = 2,
    DirtyMeasure = 4,
    DirtyArrange = 8,
    DirtyPaint = 16
};

struct LayoutProperty {
    Length w = {LengthMode::Auto, 0};
    Length h = {LengthMode::Auto, 0};
};

class Widget : public std::enable_shared_from_this<Widget> {
public:
    glm::vec2 Measure(const Constraint& c);
    void Arrange(const Rect& rect);
    virtual void Draw(const float z) const = 0;
    bool Contains(const glm::vec2& pos);
    virtual bool IsContainer() const = 0;
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
    uint8_t& GetFlags();

    UniFox::Ref<EventDispatcher> Events();
    bool Dispatch(UniFox::Event& e);
protected:
    virtual glm::vec2 OnMeasure(const Constraint& c) = 0;
    virtual void OnArrange(const Rect& rect) = 0;

    UniFox::Ref<Widget> m_Parent = nullptr;
    LayoutProperty m_Property = LayoutProperty();
    UniFox::Ref<Style> m_Style = nullptr;

    MeasureCache m_Measurement = {Constraint(), glm::vec2(0, 0)};
    ArrangeCache m_Arrangement = {Rect()};

    //uint8_t m_DirtyFlags = 7;
    uint8_t m_Flags = 28;
    UniFox::Ref<EventDispatcher> m_EventDispatcher;
protected:
    virtual bool OnEvent(UniFox::Event& e) = 0;
};

class Button : public Widget {
public:
    Button(const LayoutProperty& propery = LayoutProperty());
    ~Button() = default;

    virtual glm::vec2 OnMeasure(const Constraint& c) override;
    virtual void OnArrange(const Rect& rect) override;
    virtual void Draw(const float z) const override;
    virtual bool IsContainer() const override {return false;}
    virtual bool OnEvent(UniFox::Event& e) override;
private:
    bool m_Pressed = false;
};

/*class Slider : public Widget {
    Slider(const LayoutProperty& propery = LayoutProperty());
    ~Slider() = default;

    virtual glm::vec2 OnMeasure(const Constraint& c) override;
    virtual void OnArrange(const Rect& rect) override;
    virtual void Draw(const float z) const override;
    virtual bool IsContainer() const override {return false;}
    virtual bool OnEvent(UniFox::Event& e) override;
private:
    bool m_Pressed = false;
    float m_Ratio;
    float m_Min;
    float m_Max;
};*/