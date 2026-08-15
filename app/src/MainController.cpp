#include <app/MainController.hpp>
#include <spdlog/spdlog.h>

namespace app {

void MainController::initialize() {
    spdlog::info("Hello, from MainController!");
}

}