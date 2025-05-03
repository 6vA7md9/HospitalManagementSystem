#include "mainwindow.h"  // Include the header file for the MainWindow class
#include <QApplication>   // Include the QApplication class, which manages application-wide resources
#include <QDebug>         // Include the QDebug class, which is used for logging and debugging

int main(int argc, char *argv[])
{
    // Create the QApplication object, which is required for any Qt application
    QApplication a(argc, argv);

    // Example: Logging the application start using qDebug()
    qDebug() << "Starting Hospital Patient Record Management System...";

    // Create an instance of the MainWindow class, which is the main window of the application
    MainWindow w;

    // Show the main window on the screen
    w.show();

    // Enter the application’s event loop, which keeps the application running and responsive
    return a.exec();  // This function will return when the application closes
}
