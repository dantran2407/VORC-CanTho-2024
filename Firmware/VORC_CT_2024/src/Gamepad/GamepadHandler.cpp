#include <GamepadHandler.h>
#include <variable.h>

GamepadHandler::GamepadHandler() : _connected(false) {};

bool GamepadHandler::InitializeGamepad()
{
    int error = _ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, true, true);
    _connected = (error == 0);
    return _connected;
}

bool GamepadHandler::isConnected()
{
    return _connected;
}

bool GamepadHandler::isPressed(int key)
{
    if (!_connected)
        return false;

    return _ps2x.ButtonPressed(key);
}

bool GamepadHandler::isReleased(int key) {
    if (!_connected) return false;

    return _ps2x.ButtonReleased(key);
}

int GamepadHandler::getJoystickValue(int axis)
{
    if (!_connected)
        return 0;

    switch (axis)
    {
    case 1:
        return _ps2x.Analog(PSS_LX); // Left Joystick, X Axis
    case 2:
        return _ps2x.Analog(PSS_LY); // Left Joystick,  Y Axis
    case 3:
        return _ps2x.Analog(PSS_RX); // Right Joystick,  X Axis
    case 4:
        return _ps2x.Analog(PSS_RY); // Right Joystick,  Y Axis
    default:
        return 0;
    }
};

void GamepadHandler::update()
{
    if (!_connected)
        return;
    _ps2x.read_gamepad(0, 0);
}