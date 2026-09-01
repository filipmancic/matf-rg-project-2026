#pragma once

#include <engine/core/Engine.hpp>

namespace app {

class ProjectApp final : public engine::core::App {
    void app_setup() override;
};

}