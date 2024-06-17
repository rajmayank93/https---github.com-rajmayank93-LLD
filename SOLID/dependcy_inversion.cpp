#include <iostream>

using namespace std;

// Classes should depend on the interface rather than on concrete class

// Keyboard interface
class Keyboard {
public:
    virtual void type() = 0;
    virtual ~Keyboard() {}
};

// Mouse interface
class Mouse {
public:
    virtual void click() = 0;
    virtual ~Mouse() {}
};

// Concrete implementation of Keyboard
class MechanicalKeyboard : public Keyboard {
public:
    void type() override {
        cout << "Typing on Mechanical Keyboard" << endl;
    }
};

// Concrete implementation of Mouse
class OpticalMouse : public Mouse {
public:
    void click() override {
        cout << "Clicking Optical Mouse" << endl;
    }
};

// MacBook class depending on Keyboard and Mouse interfaces
class MacBook {
private:
    Keyboard* keyboard;
    Mouse* mouse;
public:
    MacBook(Keyboard* keyboard, Mouse* mouse)
        : keyboard(keyboard), mouse(mouse) {}

    void use() {
        keyboard->type();
        mouse->click();
    }

    ~MacBook() {
        delete keyboard;
        delete mouse;
    }
};

// Example usage
int main() {
    Keyboard* keyboard = new MechanicalKeyboard();
    Mouse* mouse = new OpticalMouse();

    MacBook macBook(keyboard, mouse);
    macBook.use();

    return 0;
}
