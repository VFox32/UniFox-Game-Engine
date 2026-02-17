#pragma once

#include "UniFox/Layer.h"

#include "UniFox/Events/KeyEvent.h"
#include "UniFox/Events/MouseEvent.h"
#include "UniFox/Events/WindowEvent.h"

namespace UniFox {
    class UF_API ImGuiLayer : public Layer {
    public:
        ImGuiLayer();
        ~ImGuiLayer() = default;
        
        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnImGuiRender() override;

        void Begin();
        void End();
    private:
        float m_Time = 0.0;
    };
}