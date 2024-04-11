#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCoreApplication>
#include <QVBoxLayout>
#include <QComboBox>
#include <QListWidget>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>

class mainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit mainWindow(QWidget *parent = nullptr);
    void resizeComponents(int width, int height);
private:

    QVBoxLayout *mainLayout;
    QComboBox *comboBox;
    QListWidget *listWidget;
    QGroupBox *groupBox;
    QListWidget * list;
    void createMenu();
    QString readcombonow(QComboBox* combo);
    void setlabels(int hddint);
    void showAbout();
    // Label Table Member Init
    QLabel *rightLabel1; // Devname
    QLabel *rightLabel2; // Label
    QLabel *rightLabel3; // UUID
    QLabel *rightLabel4; // TYPE
    QLabel *rightLabel5; // PARTLABEL
    QLabel *rightLabel6; // PARTUUID
    QLabel *rightLabel7; // BLOCKSIZE

    std::vector<QString> myVector;

signals:

private slots:
    void comboBoxItemChange(int index);

};

#endif // MAINWINDOW_H
