#include "data_washer.h"

DataWasher::DataWasher(QJsonObject *iObj, QJsonObject *oObj)
  : i_obj(iObj)
  , o_obj(oObj)
{

}

int DataWasher::extractNumber(QString str)
{
  str.replace("\n", "");
  str.replace(" ", "");
  str.replace("-","");
  return str.toInt();
}

QString DataWasher::extractString(QString str)
{
  str.replace("\n", "");
  for(int i = 0; i < str.size(); i ++)
    {
      if(str.left(1) == " ")
          str.remove(0, 1);
      else
          break;
    }
  for(int i = str.size(); i > 0; i --)
    {
      if(str.right(1) == " ")
          str.remove(i - 1, 1);
      else
          break;
    }
  return str;
}

bool DataWasher::washNumber(const QString &iObjName, const QString &oObjName)
{
  o_obj->insert(oObjName, extractNumber(i_obj->value(iObjName).toArray().first().toString()));
  return true;
}

bool DataWasher::washString(const QString &iObjName, const QString &oObjName)
{
  o_obj->insert(oObjName, extractString(i_obj->value(iObjName).toArray().first().toString()));
  return true;
}

bool DataWasher::washNumberArray(const QString &iObjName, const QString &oObjName)
{
  QJsonArray iArray = i_obj->value(iObjName).toArray();
  QJsonArray oArray;
  foreach (QJsonValue val, iArray)
    {
      int num = extractNumber(val.toString());
      oArray.append(num);
    }
  o_obj->insert(oObjName, oArray);
  return true;
}

bool DataWasher::washStringArray(const QString &iObjName, const QString &oObjName)
{
  QJsonArray iArray = i_obj->value(iObjName).toArray();
  QJsonArray oArray;
  foreach (QJsonValue val, iArray)
    {
      QString str = extractString(val.toString());
      if(!str.isEmpty())
        oArray.append(str);
    }
  o_obj->insert(oObjName, oArray);
  return true;
}




