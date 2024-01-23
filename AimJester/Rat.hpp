#pragma once


namespace rat {
    class Rat {
    public:
        static void send_mouse_input(int x, int y) {
            INPUT inputs[1] = {};
            ZeroMemory(inputs, sizeof(inputs));
            inputs[0].type = INPUT_MOUSE;
            inputs[0].mi.dx = x;
            inputs[0].mi.dy = y;
            inputs[0].mi.dwFlags = MOUSEEVENTF_MOVE;
            SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
        }
    };

}