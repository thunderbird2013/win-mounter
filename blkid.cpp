/*
 *  BLKID Command
 *  Class made by MST-SOFTWARE
 *  Matthias Stoltze 2024
 *
*/
#include "blkid.h"

blkid::blkid()
{

}


QByteArray blkid::Import_BlkID()
{
    // Run the blkid command to get block device information ;-))
    QProcess blkidProcess;
    blkidProcess.start("blkid", QStringList() << "-o" << "export");
    if (!blkidProcess.waitForStarted()) {
        qDebug() << "Error: Failed to start blkid process";
        //return 1;
    }
    if (!blkidProcess.waitForFinished()) {
        qDebug() << "Error: Failed to read blkid output";
        //return 1;
    }
    // Read the output of blkid
    QByteArray blkidOutput = blkidProcess.readAllStandardOutput();
    return blkidOutput;

}

void blkid::Json_BlkID()
{
    // Convert output to QStringList
    QStringList blkidLines = QString(this->Import_BlkID()).split('\n', Qt::SkipEmptyParts);
    // Process each line
    for (const QString& line : blkidLines) {
          //qDebug() << line;
        // Parse key-value pairs from the line
                QStringList parts = line.split('=');
                if (parts.length() == 2) {
                    QString key = parts[0];
                    QString value = parts[1];

                    // Create JSON object for each line
                    QJsonObject jsonObject;
                    jsonObject[key] = value;

                    // Add JSON object to array
                    jsonDevicesArray.append(jsonObject);
                }

    }

}

QStringList blkid::Extract_keys(QString csearchKey)
{
        // Convert JSON array to JSON document
        QJsonDocument jsonDoc(jsonDevicesArray);

        // Convert JSON document to string
        QString jsonString = jsonDoc.toJson();

        // Search key name
           QString searchKey = csearchKey; // Change this to the key name you want to search for

           // Extract all values corresponding to the search key
           QStringList values;
           for (const QJsonValue& value : jsonDevicesArray) {
               QJsonObject obj = value.toObject();
               if (obj.contains(searchKey)) {
                   values << obj.value(searchKey).toString();
               }
           }

    return values;

}

void blkid::addEntryData(std::vector<QJsonObject> &jsonObjects, QString intr, QString devname, QString label, QString type,
                         QString uuid, QString partlabel,QString partuuid)
{
    QJsonObject newEntry;

    newEntry["intr"] = intr;
    newEntry["devname"] = devname;
    newEntry["label"] = label;
    newEntry["type"] = type;
    newEntry["uuid"] = uuid;
    newEntry["partlabel"] = partlabel;
    newEntry["partuuid"] = partuuid;

    jsonObjects.push_back(newEntry);
}

void blkid::ConvertJson()
{
    // Convert JSON array to JSON document
    QJsonDocument jsonDoc(jsonDevicesArray);

    QString m_devname ;
    QString m_label;
    QString m_uuid ;
    QString m_type;
    QString m_partlabel ;
    QString m_partuuid ;

    if (!jsonDoc.isNull()) {
        if (jsonDoc.isArray()) {
            QJsonArray jsonArray = jsonDoc.array();
            foreach (const QJsonValue &value, jsonArray) {

                if (value.isObject())
                {

                    QJsonObject obj = value.toObject();
                    // Zugriff auf die Daten im Objekt

                     m_devname = obj["DEVNAME"].toString();
                     m_label = obj["LABEL"].toString();
                     m_type = obj["TYPE"].toString();
                     m_uuid = obj["UUID"].toString();
                     m_partuuid = obj["PARTUUID"].toString();

                }

            }

        }

    }

    //qDebug() << "ByteArray content:" << name;
}


QJsonObject blkid::parseStringToJsonObject(const QString &input) {
    QJsonObject obj;

    QStringList parts = input.split(" ");
    for (const QString &part : parts) {
        if (part.isEmpty())
            continue;

        QStringList keyValue = part.split("=");
        if (keyValue.size() == 2) {
            QString key = keyValue[0];
            QString value = keyValue[1].replace("\"", "");
            obj[key] = value;
        }
    }

    return obj;
}

void blkid::infohdd(QString& InfoHddString)
{


    QProcess blkidProcess;

    blkidProcess.start("blkid", QStringList() << InfoHddString);
    if (!blkidProcess.waitForStarted()) {
        qDebug() << "Error: Failed to start blkid process";
        //return 1;
    }

    if (!blkidProcess.waitForFinished()) {
        qDebug() << "Error: Failed to read blkid output";
        //return 1;
    }

    // Read the output of blkid console
    QString hddoutput = blkidProcess.readAllStandardOutput();
    // Convert in Jsonobject
    QJsonObject jsonObj = parseStringToJsonObject(hddoutput);


    // Ausgabe der einzelnen Informationen
    //    qDebug() << "DEVNAME:" << InfoHddString;
    //    qDebug() << "UUID:" << jsonObj["UUID"].toString();
    //    qDebug() << "BLOCK_SIZE:" << jsonObj["BLOCK_SIZE"].toString();
    //    qDebug() << "TYPE:" << jsonObj["TYPE"].toString();
    //    qDebug() << "PARTLABEL:" << jsonObj["PARTLABEL"].toString();
    //    qDebug() << "PARTUUID:" << jsonObj["PARTUUID"].toString();

}

int blkid::init()
{
   // int CPart = 0; // Counter Json zum Itentifiziern der Infos

    this->Json_BlkID(); // void function save in jsonDevicesArray....

    // Json Extract one Key for all Parts
    for(const QString& value : this->Extract_keys("DEVNAME")){

        QString PExtractDevname = value;

        QProcess blkidProcess;

        blkidProcess.start("blkid", QStringList() << PExtractDevname);
        if (!blkidProcess.waitForStarted()) {
            qDebug() << "Error: Failed to start blkid process";
            return 0;
        }

        if (!blkidProcess.waitForFinished()) {
            qDebug() << "Error: Failed to read blkid output";
            return 0;
        }

        // Read the output of blkid console
        QString POutput = blkidProcess.readAllStandardOutput();
        // Convert in Jsonobject
        QJsonObject jsonObj = parseStringToJsonObject(POutput);

        //qDebug() << jsonObj;

                addEntryData(this->JsonHDDInfo,
                     value,
                     jsonObj["LABEL"].toString(),
                     jsonObj["UUID"].toString(),
                     jsonObj["BLOCK_SIZE"].toString(),
                     jsonObj["TYPE"].toString(),
                     jsonObj["PARTLABEL"].toString(),
                     jsonObj["PARTUUID"].toString());

      //  CPart++;


    }
 return 1;
}

int blkid::check_blkid()
{


   QProcess blkidProcess;
  // blkidProcess.start("blkid", QStringList);





   return 1;
}


