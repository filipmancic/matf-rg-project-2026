#include <app/ProjectApp.hpp>
#include <app/MainController.hpp>

namespace app {

void ProjectApp::app_setup() {
    auto main_controller =
        register_controller<MainController>();

    main_controller->after(
        engine::core::Controller::get<
            engine::core::EngineControllersEnd
        >()
    );
}

}

int main(int argc, char **argv) {
    return std::make_unique<app::ProjectApp>()->run(argc, argv);
}