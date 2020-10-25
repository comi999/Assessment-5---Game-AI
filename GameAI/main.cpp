#include <raylib.h>
#include "Application.h"

int main(int argc, char* argv[])
{
    Application* corona = new Application("Corona", 1500, 1000);

    corona->Run();
    corona->Shutdown();

    return 0;
}