#ifndef WIDGET_H
#define WIDGET_H

#include "data_washer.h"
#include <QWidget>
#include <QCryptographicHash>


class Display : public QTextEdit
{
  Q_OBJECT

public:
  Display(QWidget *parent = 0);
  ~Display();

private:

};

#endif // WIDGET_H
