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

void MainController::draw_skybox() {
    auto shader =
        engine::core::Controller::get<
            engine::resources::ResourcesController
        >()->shader("skybox");

    auto skybox =
        engine::core::Controller::get<
            engine::resources::ResourcesController
        >()->skybox("skybox");

    engine::core::Controller::get<
        engine::graphics::GraphicsController
    >()->draw_skybox(shader, skybox);
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
    auto car_2 = resources->model("car_2");
    auto ground = resources->model("ground");

    float dirIntensity =
        m_directional_light_enabled ? 1.0f : 0.0f;

    float pointIntensity =
        m_point_light_enabled
            ? m_point_light_intensity
            : 0.0f;

    shader->use();

    // Camera

    shader->set_vec3(
        "viewPos",
        graphics->camera()->Position
    );

    shader->set_mat4(
        "projection",
        graphics->projection_matrix()
    );

    shader->set_mat4(
        "view",
        graphics->camera()->view_matrix()
    );

    // Directional light

    shader->set_vec3(
        "dirLight.direction",
        glm::vec3(-0.2f, -1.0f, -0.3f)
    );

    shader->set_vec3(
        "dirLight.ambient",
        glm::vec3(0.25f) * dirIntensity
    );

    shader->set_vec3(
        "dirLight.diffuse",
        glm::vec3(0.8f) * dirIntensity
    );

    shader->set_vec3(
        "dirLight.specular",
        glm::vec3(0.5f) * dirIntensity
    );

    // Point light 

    shader->set_vec3(
        "pointLight.position",
        glm::vec3(2.0f, 1.5f, 3.0f)
    );

    shader->set_float(
        "pointLight.constant",
        1.0f
    );

    shader->set_float(
        "pointLight.linear",
        0.09f
    );

    shader->set_float(
        "pointLight.quadratic",
        0.032f
    );

    shader->set_vec3(
        "pointLight.ambient",
        glm::vec3(0.03f, 0.015f, 0.01f) *
            pointIntensity
    );

    shader->set_vec3(
        "pointLight.diffuse",
        glm::vec3(1.0f, 0.45f, 0.15f) *
            pointIntensity
    );

    shader->set_vec3(
        "pointLight.specular",
        glm::vec3(1.0f, 0.6f, 0.3f) *
            pointIntensity
    );

    // Prvi model auta

    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(
        model,
        glm::vec3(-2.7f, -1.0f, 0.0f)
    );

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

    model = glm::rotate(
        model,
        glm::radians(40.0f),
        glm::vec3(0.0f, 0.0f, 1.0f)
    );

    model = glm::scale(
        model,
        glm::vec3(0.055f)
    );

    shader->set_mat4("model", model);

    car->draw(shader);

    // Drugi auto

    glm::mat4 model_2 = glm::mat4(1.0f);

    model_2 = glm::translate(
        model_2,
        glm::vec3(3.0f, -0.15f, 0.0f)
    );

    model_2 = glm::rotate(
        model_2,
        glm::radians(135.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );

    model_2 = glm::scale(
        model_2,
        glm::vec3(1.35f)
    );

    shader->set_mat4("model", model_2);

    car_2->draw(shader);

    // Ground

    glm::mat4 ground_model = glm::mat4(1.0f);

    ground_model = glm::translate(
        ground_model,
        glm::vec3(0.0f, -1.0f, 0.0f)
    );

    shader->set_mat4("model", ground_model);

    ground->draw(shader);

    // Skybox

    draw_skybox();
}

void MainController::poll_events() {
    auto platform =
        engine::core::Controller::get<
            engine::platform::PlatformController>();

    // 1 -> Directional light ON/OFF
    if (
        platform->key(engine::platform::KEY_1).state() ==
        engine::platform::Key::State::JustPressed
    ) {
        m_directional_light_enabled =
            !m_directional_light_enabled;
    }

    // 2 -> Point light ON/OFF
    if (
        platform->key(engine::platform::KEY_2).state() ==
        engine::platform::Key::State::JustPressed
    ) {
        m_point_light_enabled =
            !m_point_light_enabled;
    }

    // UP - jaci intenzitet point light
    if (
        platform->key(engine::platform::KEY_UP).state() ==
        engine::platform::Key::State::JustPressed
    ) {
        m_point_light_intensity += 0.1f;
    }

    // DOWN - smanji point light
    if (
        platform->key(engine::platform::KEY_DOWN).state() ==
        engine::platform::Key::State::JustPressed
    ) {
        m_point_light_intensity -= 0.1f;

        if (m_point_light_intensity < 0.0f) {
            m_point_light_intensity = 0.0f;
        }
    }

    // E - timer
    if (
        platform->key(engine::platform::KEY_E).state() ==
        engine::platform::Key::State::JustPressed
    ) {
        m_event_sequence_active = true;
        m_event_timer = 0.0f;
        m_event_stage = 0;

        m_point_light_enabled = true;
        m_directional_light_enabled = true;
    }
}

void MainController::update() {
    if (!m_event_sequence_active) {
        return;
    }

    auto platform =
        engine::core::Controller::get<
            engine::platform::PlatformController>();

    m_event_timer += platform->dt();

    // EVENT A - nakon 1 sekunde
    if (
        m_event_stage == 0 &&
        m_event_timer >= 1.0f
    ) {
        m_point_light_enabled = false;

        m_event_stage = 1;
        m_event_timer = 0.0f;
    }

    // EVENT B - nakon jos 2 sekunde
    else if (
        m_event_stage == 1 &&
        m_event_timer >= 2.0f
    ) {
        m_directional_light_enabled = false;

        m_event_stage = 2;
        m_event_sequence_active = false;
    }
}

void MainController::end_draw() {
    engine::core::Controller::get<
        engine::platform::PlatformController
    >()->swap_buffers();
}

}