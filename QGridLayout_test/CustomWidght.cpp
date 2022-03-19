#include "CustomWidght.h"
#include <QGridLayout>
#include <QString>

CustomWidght::CustomWidght(QWidget *parent)
  :QWidget (parent)
{
  myPalette.setColor(QPalette::Window,QColor(12,23,44));
  QList<QLabel*>* labelList = new QList<QLabel*>;
  for (int i = 0;i < 3;++i) {
    QLabel *temp = new QLabel("Label Num "+QString::number(i+1,10));
    temp->setAutoFillBackground(true);
    temp->setPalette(myPalette);
    labelList->push_front(temp);
  }
  layout = new QGridLayout();
  setlayout(layout,this,labelList);
}

CustomWidght::~CustomWidght()
{
  while (labelList->size()) {
    QLabel *temp = labelList->last();
    labelList->removeLast();
    delete temp;
  }
  delete labelList;
  delete layout;
}
void CustomWidght::setlayout(QGridLayout* layout,QWidget* testWidget,QList<QLabel*>*labelList)
{
  //放置窗口,设置窗口布局
  testWidget->setLayout(layout);
  layout->addWidget(labelList->at(0),0,0);
  layout->addWidget(labelList->at(1),1,0);
  layout->addWidget(labelList->at(2),0,1,2,1);
  //列比例,第0列与第一列比 1:2
  layout->setColumnStretch(0,1);
  layout->setColumnStretch(1,2);
  //行比例,第0行与第一行之比 1:1
  layout->setRowStretch(0,1);
  layout->setRowStretch(1,1);
}

void CustomWidght::mousePressEvent(QMouseEvent *event)
{
  //event->globalPos()鼠标按下时,鼠标相对于整个屏幕的位置
  //pos() this->pos()鼠标按下时,窗口相对于整个屏幕的位置
  m_pointPos = event->globalPos() - pos();
//  for(int i=0; i < labelList->size();++i)
//  {
//    if(labelList->at(i)->geometry().contains(m_pointPos))
//      labelList->removeAt(i);
//  }
}

void CustomWidght::mouseReleaseEvent(QMouseEvent *event)
{

}
