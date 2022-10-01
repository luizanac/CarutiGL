#include "Core/Result.hpp"
#include "CaruticraftApplication.hpp"

using namespace Caruti;

const int ScreenWidth = 1024, ScreenHeight = 600;

int main() {
    auto application = CaruticraftApplication(ScreenWidth, ScreenHeight);
    application.Run();
    return Success;
}

