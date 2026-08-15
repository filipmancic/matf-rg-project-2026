#pragma once

#include <engine/core/Engine.hpp>

namespace app {

class MainController final : public engine::core::Controller {
    void initialize() override;
};

}