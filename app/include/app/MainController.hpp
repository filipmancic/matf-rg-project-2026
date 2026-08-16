#pragma once

#include <engine/core/Engine.hpp>

namespace app {

class MainController final : public engine::core::Controller {
public:
    void initialize() override;
    void begin_draw() override;
    void draw() override;
    void end_draw() override;
    void draw_skybox();
};

}