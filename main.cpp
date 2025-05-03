#include "mainwindow.h"  // Include the header file for the MainWindow class, which contains the main UI logic
#include <QApplication>   // Include the QApplication class, responsible for managing application-wide settings and control flow
#include <QDebug>         // Include the QDebug class, which is used for printing debug messages to the console

int main(int argc, char *argv[])
{
    // Initialize a QApplication object. This is needed for any Qt GUI application to handle things like events and settings
    QApplication a(argc, argv);

    // Example: Log a message indicating the start of the application for debugging purposes
    qDebug() << "Starting Hospital Patient Record Management System...";

    // Create an instance of the MainWindow class, which will be the main window of the application
    MainWindow w;

    // Show the main window, making it visible to the user
    w.show();

    // Enter the application's event loop. This function keeps the application running and responsive to user inputs
    return a.exec();  // The event loop continues until the application is closed
}
