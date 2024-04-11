#include "mainwindow.h"
#include "ctray.h"
#include <QIcon>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

   // qDebug() << "This application requires root privileges to run.";
   // Prompt user to run the application with sudo
   // qDebug() << "Please run the following command with sudo:";
   // qDebug() << "sudo" << QCoreApplication::applicationFilePath();


    a.setOverrideCursor(Qt::ArrowCursor);
    a.setWindowIcon(QIcon(":/icons/hdd.png"));

    mainWindow w;
    w.setMaximumSize(600,400); // Maximal Size Window
    w.show();

    std::unique_ptr<CTray> systemtray(new CTray(&w));

    return a.exec();
}
