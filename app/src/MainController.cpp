#include <app/MainController.hpp>
#include <engine/core/Engine.hpp>
#include <engine/graphics/GraphicsController.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace app {

void MainController::initialize() {
    engine::graphics::OpenGL::enable_depth_testing();

    auto graphics =
        engine::core::Controller::get<
            engine::graphics::GraphicsController>();

    graphics->camera()->Position = glm::vec3(0.0f, 0.0f, 10.0f);
}

void MainController::begin_draw() {
    engine::graphics::OpenGL::clear_buffers();
}

void MainController::draw() {
    auto graphics =
        engine::core::Controller::get<
            engine::graphics::GraphicsController>();

    auto resources =
        engine::core::Controller::get<
            engine::resources::ResourcesController>();

    auto shader = resources->shader("basic");
    auto car = resources->model("car");

    shader->use();

    shader->set_mat4(
        "projection",
        graphics->projection_matrix()
    );

    shader->set_mat4(
        "view",
        graphics->camera()->view_matrix()
    );

glm::mat4 model = glm::mat4(1.0f);

model = glm::translate(model, glm::vec3(0.0f, -1.2f, 0.0f));

model = glm::rotate(
    model,
    glm::radians(90.0f),
    glm::vec3(1.0f, 0.0f, 0.0f)
);

model = glm::rotate(
    model,
    glm::radians(180.0f),
    glm::vec3(0.0f, 1.0f, 0.0f)
);

model = glm::scale(
    model,
    glm::vec3(0.06f)
);

    shader->set_mat4("model", model);

    car->draw(shader);

    auto ground = resources->model("ground");

    glm::mat4 ground_model = glm::mat4(1.0f);

    ground_model = glm::translate(
        ground_model,
        glm::vec3(0.0f, -1.0f, 0.0f)
    );

    shader->set_mat4("model", ground_model);

    ground->draw(shader);
}

void MainController::end_draw() {
    engine::core::Controller::get<
        engine::platform::PlatformController
    >()->swap_buffers();
}

}