#pragma once

#include <QMessageBox>
#include <QString>
#include <QTimer>
#include <QPushButton>

struct TimedMessageBoxParam
{
    int timeInMs = -1;
    QString title;
    QString text;
    QString solution;
    QString timedButtonText;
    QString styleSheet;
};

class TimedMessageBox : public QMessageBox
{
    Q_OBJECT
public:
    explicit TimedMessageBox(QtMsgType type, const TimedMessageBoxParam& messageBoxParam, QWidget* parent = nullptr,
                             StandardButtons buttons = QMessageBox::Ok);

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
    void showEvent(QShowEvent* event) override;
private slots:
    void refreshTimedButtonText();
    void closeMessageBox();

private:
    void setupUi(QtMsgType type, const TimedMessageBoxParam& messageBoxParam);

    void setTimedButton(const QString& buttonText);

    void startTimer()
    {
        _refreshBtnTextTimer.start();
        _closeMsgBoxTimer.start();
    }
    void stopTimer()
    {
        _refreshBtnTextTimer.stop();
        _closeMsgBoxTimer.stop();
    }
    void setTimedButtonText(const QString& text)
    {
        if (!_timedButton)
            return;
        _timedButton->setText(text);
    }
    void cancelCountdown()
    {
        stopTimer();
        setTimedButtonText(_timedButtonOriText);
    }

    QPushButton* _timedButton = nullptr;
    QPushButton* _closeButton = nullptr;
    QString _timedButtonOriText;
    QTimer _refreshBtnTextTimer;
    QTimer _closeMsgBoxTimer;
    QPoint _lastMousePos;
    bool _mousePressed = false;
};
