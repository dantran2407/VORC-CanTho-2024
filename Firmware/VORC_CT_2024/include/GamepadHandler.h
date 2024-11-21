#include <PS2X_lib.h>

class GamepadHandler
{
private:
    PS2X _ps2x;
    bool _connected;
public:
    GamepadHandler();
    bool InitializeGamepad();
    bool isConnected();
    void update();
    bool isPressed(int button);

    bool isReleased(int button);
    int getJoystickValue(int axis);
};