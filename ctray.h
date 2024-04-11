#ifndef CTRAY_H
#define CTRAY_H

#include <QApplication>
#include <QObject>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QWidget>

class CTray : public QObject
{
    Q_OBJECT
public:
    explicit CTray(QWidget *mainWindow, QObject *parent = nullptr);


signals:

private slots:
       void iconActivated(QSystemTrayIcon::ActivationReason reason);
       void showContextMenu(const QPoint& pos);
private:
       void createTrayIcon();
       QSystemTrayIcon* trayIcon;
       QWidget *mainWindow;
};

#endif // CTRAY_H
