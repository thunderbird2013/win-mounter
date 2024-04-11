#ifndef BLKID_H
#define BLKID_H

#include <QProcess>
#include <QRegularExpression>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QStringList>

class blkid
{

public:

    blkid();//Constructor
    int check_blkid(); // danke an mein freund Thomas Schmidt für die Idee
    void  Json_BlkID(); // QProcess on data holding
    QStringList Extract_keys(QString csearchKey); // Extract Devname /dev/.... etc..
    void ConvertJson(); // Function is old delete it soon
    void infohdd(QString& InfoHddString); // Function is old delete it soon
    int init(); // New Function parse Json in Vector/Json

    // Members
    QJsonArray jsonDevicesArray;  // QByteArray
    std::vector<QJsonObject> jsonObjects; // Vector Object
    std::vector<QJsonObject> JsonHDDInfo; // New Json Vector with data of detail /dev/.. drive

private:

    QByteArray Import_BlkID(); // Parse QBytearray from Process internal Function
    void addEntryData(std::vector<QJsonObject> &jsonObjects,
                      QString intr, QString devname, QString label,
                      QString type,QString uuid, QString partlabel,QString partuuid); // Add Vector Json Function Internal Func..
    QJsonObject parseStringToJsonObject(const QString &input);
};

#endif // BLKID_H
