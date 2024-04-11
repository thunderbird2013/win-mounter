#include "cabout.h"


About_Dialog::About_Dialog(QWidget *parent)
    :QDialog(parent)
{

          QVBoxLayout *layout = new QVBoxLayout(this);


          QLabel *label = new QLabel("GUI mount", this);
          layout->addWidget(label);

          // Picture label
          pictureLabel = new QLabel(this);
          layout->addWidget(pictureLabel);

          QPushButton *button = new QPushButton("Close", this);
          layout->addWidget(button);

          connect(button, &QPushButton::clicked, this, &QDialog::accept);
}

void About_Dialog::setPicture(const QPixmap &pixmap)
{
     pictureLabel->setPixmap(pixmap);
}
