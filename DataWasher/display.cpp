#include "display.h"



Display::Display(QWidget *parent)
  : QTextEdit(parent)
{
  this->setWindowTitle("乐析数据清洗系统");
  QFile iFile("/Volumes/VirtualDisk/data.json");
  if(!iFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
      return;
    }
  QTextStream in(&iFile);
  QByteArray inByteArray = in.readAll().toUtf8();
  iFile.close();
  iFile.flush();

  QJsonParseError jsonError;
  QJsonDocument readJsonDocument = QJsonDocument::fromJson(inByteArray, &jsonError);
  if(jsonError.error != QJsonParseError::NoError)
    {
      qDebug()<<"json decode failed";
      return;
    }

  QJsonArray writeJsonArray;

  foreach(QJsonValue val, readJsonDocument.array())
    {
      QJsonObject iPeople = val.toObject();\
      QJsonObject oPeople;

      DataWasher washer(&iPeople, &oPeople);
      washer.washNumber("act", "act");
      washer.washNumber("sat", "sat");
      washer.washNumber("toefl", "toefl");
      washer.washNumber("year", "year");
      washer.washString("school", "school");
      washer.washStringArray("major", "major");

      QJsonArray ieltsArray;
      for(int i = 0; i < 4; i ++) // because nobody takes ielts!! Bad!!!
          ieltsArray.append(0);
      oPeople.insert("ielts", ieltsArray);

      writeJsonArray.append(oPeople);
    }

  QJsonDocument writeJsonDocument(writeJsonArray);


  QFile oFile("/Volumes/VirtualDisk/data_out.json");
  if(!oFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
      return;
    }
  QTextStream out(&oFile);
  out << readJsonDocument.toJson(QJsonDocument::Indented);
  oFile.close();
  oFile.flush();

  this->setText(writeJsonDocument.toJson());

}

Display::~Display()
{



}

