#pragma once

#include <engine/core/Engine.hpp>

namespace app {

class MainController final : public engine::core::Controller {
public:
    void initialize() override;
    void poll_events() override;
    void begin_draw() override;
    void draw() override;
    void end_draw() override;
    void draw_skybox();
    void update() override;

private:
    bool m_directional_light_enabled = true;
    bool m_point_light_enabled = true;
    float m_point_light_intensity = 1.0f;
    bool m_event_sequence_active = false;
    float m_event_timer = 0.0f;
    int m_event_stage = 0;
};

}