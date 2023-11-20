#pragma once
#include "InputListener.h"
#include <vector>
#include <Windows.h>
#include "Point.h"

class InputSystem{
public:

    static InputSystem* getInstance();
    static void initialize();
    static void destroy();

    void addListener(InputListener* listener);
    void removeListener(InputListener* listener);

    void setCursorPosition(const Point& pos);
    void showCursor(bool show);

    void update();

    bool isKeyDown(int key);
    bool isKeyUp(int key);


private:

    static InputSystem* sharedInstance;

    void callOnKeyDown(int key);
    void callOnKeyUp(int key);

    Point oldMousePos;
    bool firstTimeCall = true;

    void callOnMouseMove(Point deltaPt);
    void callOnLeftMouseDown(Point deltaPt);
    void callOnLeftMouseUp(Point deltaPt);
    void callOnRightMouseDown(Point deltaPt);
    void callOnRightMouseUp(Point deltaPt);

    std::vector<InputListener*> inputListenerList;

    unsigned char keyStates[256] = {};
    unsigned char oldkeyStates[256] = {};

    InputSystem();
    ~InputSystem();
    InputSystem(InputSystem const&) {};
    InputSystem& operator=(InputSystem const&) {};

};