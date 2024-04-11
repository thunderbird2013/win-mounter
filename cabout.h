#ifndef ABOUT_DIALOG_H
#define ABOUT_DIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>

class About_Dialog : public QDialog
{
    Q_OBJECT

    public:

        explicit About_Dialog(QWidget *parent = nullptr);
            void setPicture(const QPixmap &pixmap);
    private:
        QLabel *pictureLabel;
        QLabel *label;
        QPushButton *button;
};

#endif // ABOUT_DIALOG_H
