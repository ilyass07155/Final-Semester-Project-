#ifndef RECORDMANAGER_H
#define RECORDMANAGER_H

#include "student.h"
#include <QString>
#include <QVector>

class RecordManager {
public:
    RecordManager(const QString &filePath);

    bool addRecord(const Student &s);
    bool updateRecord(const QString &roll, const Student &newData);
    bool deleteRecord(const QString &roll);
    QVector<Student> readAll();

private:
    QString path;
};

#endif // RECORDMANAGER_H

