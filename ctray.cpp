#include "ctray.h"
#include <QApplication>
#include <QAction>

CTray::CTray(QWidget *mainWindow, QObject *parent)
    : QObject{parent},
      mainWindow(mainWindow)
{
    createTrayIcon();
}

void CTray::iconActivated(QSystemTrayIcon::ActivationReason reason) {
    if (reason == QSystemTrayIcon::Trigger) {
        // Toggle main window visibility
               if (mainWindow->isVisible()) {
                   mainWindow->hide();
               } else {
                   mainWindow->show();
               }
    }
}

void CTray::showContextMenu(const QPoint& pos) {
    QMenu contextMenu;
    QAction action("Exit");
    connect(&action, &QAction::triggered, qApp, &QCoreApplication::quit);
    contextMenu.addAction(&action);
    contextMenu.exec(trayIcon->geometry().center() - QPoint(0, contextMenu.sizeHint().height()));
}

void CTray::createTrayIcon() {
    trayIcon = new QSystemTrayIcon(QIcon(":/icons/tray.png"), this);
    connect(trayIcon, &QSystemTrayIcon::activated, this, &CTray::iconActivated);

    QMenu* menu = new QMenu();
    QAction* quitAction = new QAction("Exit", this);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
    menu->addAction(quitAction);
    trayIcon->setContextMenu(menu);

    trayIcon->show();
}
