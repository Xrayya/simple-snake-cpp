#include "app.hpp"

App::App(AppSpec appSpec)
    : game(appSpec.width, appSpec.height), renderer(game) {}

App::App() : game(AppSpec().width, AppSpec().height), renderer(game) {}

// void App::run() {
//   while (game.isRunning()) {
//     game.update();
//     renderer.render();
//     break;
//   }
// }
