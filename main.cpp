#include "menu.h"


int main(int argc, char* argv[]) {

    QApplication app(argc, argv);

    Menu window;

    window.resize(1000, 800);
    window.setWindowTitle("Snakes");
    window.show();

    return app.exec();
}