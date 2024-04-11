#include "mainwindow.h"
#include "blkid.h"
#include "cabout.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <vector>
#include <QMenuBar>
#include <QMessageBox>
#include <QIcon>
#include <QPainter>
#include <QPixmap>

mainWindow::mainWindow(QWidget *parent)
    : QMainWindow{parent}
{
    QWidget *centralWidget = new QWidget(this);

        setWindowTitle("Quick Mount Version 0.1 by MST-SOFTWARE");
        setCentralWidget(centralWidget);

        mainLayout = new QVBoxLayout(centralWidget);

        // Create horizontal layout for combobox and button
        QHBoxLayout *comboBoxLayout = new QHBoxLayout;


        // Create and add the combo box at the top
        comboBox = new QComboBox;
        comboBox->setMaxVisibleItems(7);

        std::unique_ptr<blkid> partinfo(new blkid()); // Class init and autop Delete from ptr....

        partinfo->init(); // Init Hauptteil

        // Json Extract one Key for Combobox
        for(const QString& value : partinfo->Extract_keys("DEVNAME")){
         comboBox->addItem(value);

        }

        comboBoxLayout->addWidget(comboBox);

        // Trigger of Combobox
        connect(comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
                    this, &mainWindow::comboBoxItemChange);

        // Create and add the button
        QPushButton *button = new QPushButton();
        button->setFixedWidth(30);
        QIcon icon(":/icons/hdd.png");
        button->setIcon(icon);
        button->setIconSize(QSize(16,16));

        comboBoxLayout->addWidget(button);

        mainLayout->addLayout(comboBoxLayout);

        // Create and add the group box at the bottom
        groupBox = new QGroupBox("Partitions-Info");
        QVBoxLayout *groupBoxLayout = new QVBoxLayout(groupBox);

        // Label Table statisch muss noch dynamisch gemacht werden....

        QHBoxLayout *labelsLayout1 = new QHBoxLayout;
        QLabel *leftLabel1 = new QLabel("DEVNAME:");
        rightLabel1 = new QLabel("---");
        rightLabel1->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        labelsLayout1->addWidget(leftLabel1);
        labelsLayout1->addWidget(rightLabel1);
        groupBoxLayout->addLayout(labelsLayout1);

        QHBoxLayout *labelsLayout2 = new QHBoxLayout;
        QLabel *leftLabel2 = new QLabel("LABEL:");
        rightLabel2 = new QLabel("---");
        rightLabel2->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        labelsLayout2->addWidget(leftLabel2);
        labelsLayout2->addWidget(rightLabel2);
        groupBoxLayout->addLayout(labelsLayout2);

        QHBoxLayout *labelsLayout3 = new QHBoxLayout;
        QLabel *leftLabel3 = new QLabel("UUID:");
        rightLabel3 = new QLabel("---");
        rightLabel3->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        labelsLayout3->addWidget(leftLabel3);
        labelsLayout3->addWidget(rightLabel3);
        groupBoxLayout->addLayout(labelsLayout3);


        QHBoxLayout *labelsLayout4 = new QHBoxLayout;
        QLabel *leftLabel4 = new QLabel("TYPE:");
        rightLabel4 = new QLabel("---");
        rightLabel4->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        labelsLayout4->addWidget(leftLabel4);
        labelsLayout4->addWidget(rightLabel4);
        groupBoxLayout->addLayout(labelsLayout4);


        QHBoxLayout *labelsLayout5 = new QHBoxLayout;
        QLabel *leftLabel5 = new QLabel("PARTLABEL:");
        rightLabel5 = new QLabel("---");
        rightLabel5->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        labelsLayout5->addWidget(leftLabel5);
        labelsLayout5->addWidget(rightLabel5);
        groupBoxLayout->addLayout(labelsLayout5);


        QHBoxLayout *labelsLayout6 = new QHBoxLayout;
        QLabel *leftLabel6 = new QLabel("PARTUUID:");
        rightLabel6 = new QLabel("---");
        rightLabel6->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        labelsLayout6->addWidget(leftLabel6);
        labelsLayout6->addWidget(rightLabel6);
        groupBoxLayout->addLayout(labelsLayout6);

        QHBoxLayout *labelsLayout7 = new QHBoxLayout;
        QLabel *leftLabel7 = new QLabel("BLOCK SIZE:");
        rightLabel7 = new QLabel("---");
        rightLabel7->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        labelsLayout7->addWidget(leftLabel7);
        labelsLayout7->addWidget(rightLabel7);
        groupBoxLayout->addLayout(labelsLayout7);

        mainLayout->addWidget(groupBox);

        centralWidget->setLayout(mainLayout);

        createMenu();

        // Set initial size of the window
        resize(500, 250); // Set the initial width and height of the window

        //mainWindow::rightLabel1->setText(readcombonow(comboBox));
        int count = comboBox->currentIndex();
        mainWindow::setlabels(count);

}

void mainWindow::resizeComponents(int width, int height)
{
    setFixedSize(width, height);

    // Calculate sizes for components
    int comboBoxHeight = height * 0.2; // 20% of the height
    int listWidgetHeight = height * 0.5; // 50% of the height
    int groupBoxHeight = height * 0.3; // 30% of the height

    // Resize components
    comboBox->setFixedHeight(comboBoxHeight);
    listWidget->setFixedHeight(listWidgetHeight);
    groupBox->setFixedHeight(groupBoxHeight);
}

void mainWindow::createMenu()
{
    // Create File menu
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

    // Add actions to File menu
    QAction *exitAction = new QAction(tr("&Exit"), this);
    exitAction->setShortcut(QKeySequence::Quit);
    connect(exitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
    fileMenu->addAction(exitAction);

    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));

    // Add actions to Help menu
    QAction *aboutAction = new QAction(tr("&About"), this);
    connect(aboutAction, &QAction::triggered, this, &mainWindow::showAbout); // Assuming MyMainWindow is the class name of your main window
    helpMenu->addAction(aboutAction);


}

void mainWindow::comboBoxItemChange(int index)
{       
    QString selectedText = comboBox->itemText(index);
    int selectedNumber = comboBox->itemData(index, Qt::DisplayRole).toInt();
    std::unique_ptr<blkid> info_ptr(new blkid());
    info_ptr->infohdd(selectedText);
    mainWindow::rightLabel1->setText(selectedText);
    int count = comboBox->currentIndex(); // Entry Number schwere geburt ey ;-)))
    mainWindow::setlabels(count);


   // qDebug() << QString("Current Entrie: %1").arg(count);

   // QMessageBox::information(this, "Item Selected", "You selected: " + selectedText + " / "+QString("Current Entrie: %1").arg(count));
}

QString mainWindow::readcombonow(QComboBox* combo)
{
    QString now = combo->currentText();
    return now;
}

void mainWindow::setlabels(int hddint)
{
    std::unique_ptr<blkid> info(new blkid());

    if(!info->init()){
        qDebug() << "Etwas ist schief gelaufen !!!!";
    }

    std::vector<QJsonValue> jsonValuePartOne1;
    int hddinfo = hddint;


    QStringList stringParts;
    std::vector<QString> myVector;

    for (const auto& jsonObj : info->JsonHDDInfo[hddinfo]) {
         // qDebug() << jsonObj;
          jsonValuePartOne1.push_back(jsonObj); // Schiebe das Array info->JsonHDDInfo[array] in den Vector
        }

        for (const QJsonValue& value : jsonValuePartOne1) {

            QString stringValue = value.toString();

            //qDebug() << "String content:" << stringValue;

            // Splitting the string using a space as the delimiter

            stringParts = stringValue.split(" ");

               //  qDebug() << stringParts;

               for (auto i : stringParts) {
                      myVector.push_back(i);
                  }

        }


    // qDebug() << myVector[0] << myVector[1] << myVector[2] << myVector[3] << myVector[4] << myVector[5] <<  myVector[6];

    mainWindow::rightLabel1->setText(myVector[1]);
    mainWindow::rightLabel2->setText(myVector[3]);
    mainWindow::rightLabel3->setText(myVector[2]);
    mainWindow::rightLabel4->setText(myVector[6]);
    mainWindow::rightLabel5->setText(myVector[0]);
    mainWindow::rightLabel6->setText(myVector[4]);
    mainWindow::rightLabel7->setText(myVector[5]);



}


void mainWindow::showAbout()
{
    std::unique_ptr<About_Dialog> sabout(new About_Dialog()); // unique_ptr -> Delete auto pointer
    sabout->setPicture(QPixmap(":/icons/logo.png"));
    sabout->resize(300, 100);
    sabout->exec();
}
