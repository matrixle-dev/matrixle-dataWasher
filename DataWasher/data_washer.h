#ifndef DATAWASHER_H
#define DATAWASHER_H


#include <cassert>

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QTextEdit>
#include <QtSql>


class DataWasher
{
public:
  DataWasher(QJsonObject *iObj, QJsonObject *oObj);

  static int extractNumber(QString str);
  static QString extractString(QString str);

  bool washNumber(const QString &iObjName, const QString &oObjName);
  bool washString(const QString &iObjName, const QString &oObjName);
  bool washNumberArray(const QString &iObjName, const QString &oObjName);
  bool washStringArray(const QString &iObjName, const QString &oObjName);


private:
  QJsonObject *i_obj;
  QJsonObject *o_obj;


};
#endif // DATAWASHER_H
