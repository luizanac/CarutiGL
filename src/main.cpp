#include "Core/Result.hpp"
#include "CaruticraftApplication.hpp"

using namespace Caruti;

const int SCREEN_WIDTH = 1024, SCREEN_HEIGHT = 600;

int main() {
    auto application = CaruticraftApplication(SCREEN_WIDTH, SCREEN_HEIGHT);
    application.Run();
    return Success;
}

