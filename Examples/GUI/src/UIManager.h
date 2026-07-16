#pragma once
#include "UniFox.h"

#include "Widget.h"
#include "Container.h"

struct ManagerProperty {
    glm::vec2 position = {0, 0};
};
class ManagerSlot : public Slot {
public:
    ManagerSlot(UniFox::Ref<Widget> Widget, const ManagerProperty& desire) : desire(desire) {widget = Widget;}
    ManagerProperty desire;
};
class UIManager : public Container {
public:
    UIManager() {};
    ~UIManager() = default;

    bool OnEvent(UniFox::Event& e);

    virtual void Draw(const float z = 0.0) const override;
    virtual void AddChild(UniFox::Ref<Widget> child) override;
    void AddChild(UniFox::Ref<Widget> child, const ManagerProperty& property);
    virtual UniFox::Ref<Widget> GetChild(const uint32_t index = 0) const override;
    virtual uint32_t GetChildCount() const override;
private:
    UniFox::Ref<Widget> GetWidget(const glm::vec2& position);

    virtual glm::vec2 OnMeasure(const Constraint& c) override {return {0, 0};}
    virtual void OnArrange(const Rect& rect) override {}
private:
    std::vector<ManagerSlot> m_Slots;

    UniFox::Ref<Widget> m_Hover = nullptr;
    UniFox::Ref<Widget> m_Focus = nullptr;
};