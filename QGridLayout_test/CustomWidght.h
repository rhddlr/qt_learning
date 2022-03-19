#ifndef CUSTOMWIDGHT_H
#define CUSTOMWIDGHT_H
#include <QPalette>
#include <QWidget>
#include <QLabel>
#include <QList>
#include <QGridLayout>
#include <QPoint>
#include <QMouseEvent>

class CustomWidght:public QWidget
{
  Q_OBJECT
public:
  CustomWidght(QWidget *parent = Q_NULLPTR);
  ~CustomWidght();
  void setlayout(QGridLayout* layout,QWidget* testWidget,QList<QLabel*>*labelList);

protected:
  void mousePressEvent(QMouseEvent* event);
  void mouseReleaseEvent(QMouseEvent* event);
private:
  QPalette myPalette;
  QList<QLabel*>* labelList;
  QGridLayout *layout;
  QPoint m_pointPos;
};

#endif // CUSTOMWIDGHT_H
