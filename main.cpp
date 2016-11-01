#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {

    // Start QApplication
    QApplication qapplication(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();

    return qapplication.exec();

}
