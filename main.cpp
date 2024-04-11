#include "mainwindow.h"
#include "ctray.h"
#include <QIcon>
#include <QApplication>
#include "blkid.h"

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

    //Check ob blkid installiert ist

     std::unique_ptr<blkid> checksystem(new blkid());
     int result = checksystem->check_blkid();
     if(result == 0) {
        // Command executed successfully
        qDebug() << "blkid command executed successfully.";
     } else {
        // Command failed
        qDebug() << "Failed to execute blkid command. Exit code:" << result;
        return 1; // Exit with errorcode
     }

    return a.exec();
}
