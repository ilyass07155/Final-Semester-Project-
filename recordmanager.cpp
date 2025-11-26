#include "recordmanager.h"
#include <QFile>
#include <QTextStream>

RecordManager::RecordManager(const QString &filePath)
{
    path = filePath;
}

QVector<Student> RecordManager::readAll()
{
    QVector<Student> records;
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return records;

    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.isEmpty()) continue;

        QStringList parts = line.split(',');

        if (parts.size() == 6) {
            Student s;
            s.roll = parts[0];
            s.name = parts[1];
            s.father = parts[2];
            s.caste = parts[3];
            s.district = parts[4];
            s.gpa = parts[5];
            records.append(s);
        }
    }

    file.close();
    return records;
}

bool RecordManager::addRecord(const Student &s)
{
    auto all = readAll();

    for (auto &r : all)
        if (r.roll == s.roll)
            return false;

    QFile file(path);
    if (!file.open(QIODevice::Append | QIODevice::Text))
        return false;

    QTextStream out(&file);
    out << s.roll << "," << s.name << "," << s.father << ","
        << s.caste << "," << s.district << "," << s.gpa << "\n";

    file.close();
    return true;
}

bool RecordManager::updateRecord(const QString &roll, const Student &newData)
{
    auto all = readAll();
    bool found = false;

    for (int i = 0; i < all.size(); i++) {
        if (all[i].roll == roll) {
            all[i] = newData;
            found = true;
            break;
        }
    }

    if (!found)
        return false;

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&file);

    for (auto &s : all)
        out << s.roll << "," << s.name << "," << s.father << ","
            << s.caste << "," << s.district << "," << s.gpa << "\n";

    file.close();
    return true;
}

bool RecordManager::deleteRecord(const QString &roll)
{
    auto all = readAll();
    int before = all.size();

    for (int i = 0; i < all.size(); i++)
        if (all[i].roll == roll) {
            all.remove(i);
            break;
        }

    if (all.size() == before)
        return false;

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&file);

    for (auto &s : all)
        out << s.roll << "," << s.name << "," << s.father << ","
            << s.caste << "," << s.district << "," << s.gpa << "\n";

    file.close();
    return true;
}
