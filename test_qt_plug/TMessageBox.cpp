#include <QApplication>
#include <QFile>
#include <QLabel>
#include <QStringLiteral>
#include <QDesktopWidget>
#include <QKeyEvent>
#include <QGridLayout>
#include <QSpacerItem>
#include <QPainter>
#include <QPainterPath>
#include <QGraphicsDropShadowEffect>
#include <QDebug>
#include <QTextLayout>

#include "TimedMessageBox.h"

namespace {
constexpr int k_textRightMargin = 16;
constexpr int k_textBottomMargin = 5;
constexpr int k_iconLeftMargin = 6;
constexpr int k_shadowSize = 4;
const QColor k_backgroundColor(45, 45, 45);
constexpr int k_radius = 4;
const QColor k_shadowColor(25, 25, 25, 130);
const QSize k_textSize(348, 15);
constexpr QSize k_iconSize(43, 40);

const QString k_styleSheet = R"qss(
    QPushButton {
        color: rgba(255, 255, 255,225);
        min-width: 78px;
        min-height:22px;
        background-color:rgba(255, 255, 255, 0.1);
        border-radius: 4px;
        padding: 3px 12px 3px 12px;
    }
    QPushButton:hover {
        background-color:rgba(255, 255, 255, 0.2);
    }
    *[titleField="true"] {
        color: rgba(255, 255, 255, 0.85);
    }
    *[textField="true"] {
        color: rgba(255, 255, 255, 0.6);
    }
    *[detailField="true"] {
        color: rgba(255, 255, 255, 0.4);
    }
    *[closeIconButton="true"] {
        min-width:16px;max-width:16px;
        min-height:16px;max-height:16px;
        image: url(:/msgbox_close.png);
        border-radius: 2px;
        padding:0px;
        background-color:transparent;
    })qss";

void createShadowEffectTo(QWidget* const widget)
{
    auto* const shadow = new QGraphicsDropShadowEffect(widget);
    shadow->setOffset(2, 3); // show more shadow on bottom and right side
    shadow->setColor(k_shadowColor);
    shadow->setBlurRadius(2);
    widget->setGraphicsEffect(shadow);
}

/** @brief add '\n' to Text for auto wrap in QLabel with setWordWrap(true).
 *  font: for different pixel size used in font. */
QString addWordBreakToText(const QFont& font, const QString& text, int labelMaxWidth, const QChar wordBreak = '\n')
{
    QStringList retList{};
    const QFontMetrics fontMetrics(font);
    int startPos = 0;
    int remainedLength = fontMetrics.horizontalAdvance(text);
    const int textLength = text.length();
    while (remainedLength > labelMaxWidth) {
        if (startPos >= textLength)
            break;
        int accumulatedWidth = 0;
        unsigned int endPos = 0;
        for (int i = startPos; i < textLength; i++) {
            accumulatedWidth += fontMetrics.horizontalAdvance(text.at(i));
            if (accumulatedWidth >= labelMaxWidth || text.at(i) == wordBreak) {
                endPos = i;
                break;
            }
        }
        const QString splitted = text.mid(startPos, endPos - startPos);
        retList.append(splitted);
        if (!splitted.endsWith(wordBreak))
            retList.append(wordBreak);

        if (text.midRef(endPos).startsWith(wordBreak))
            ++endPos;
        const QString remainedText = text.mid(endPos);
        remainedLength = fontMetrics.horizontalAdvance(remainedText);
        startPos = endPos;
        if (remainedLength <= labelMaxWidth)
            retList.append(remainedText);
    }
    if (retList.isEmpty())
        return text;
    return retList.join(QString());
}

QString splitByWordWrap(const QFont& font, const QString& string, const int pixelLength)
{
    QStringList result{};

    const QStringList list = string.split('\n');

    std::for_each(list.cbegin(), list.cend(), [&](const QString& str) {
        QTextLayout textLayout(str, font);
        textLayout.beginLayout();
        while (true) {
            QTextLine line = textLayout.createLine();
            if (!line.isValid())
                break;

            line.setLineWidth(pixelLength);
            result.append(str.mid(line.textStart(), line.textLength()));
        }
        textLayout.endLayout();
    });

    return result.join(QString());
}

QLabel* generateTextLabel(const QString& text, TimedMessageBox* parent)
{
    auto* const label = new QLabel(parent);
    label->setText(addWordBreakToText(label->font(), text, k_textSize.width()));
    label->setMinimumSize(k_textSize);
    label->setWordWrap(true);
    return label;
}
} // namespace
TimedMessageBox::TimedMessageBox(QtMsgType type, const TimedMessageBoxParam& messageBoxParam, QWidget* parent,
                                 StandardButtons buttons)
    : QMessageBox(parent)
{
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    // see also setQuitOnLastWindowClosed
    setAttribute(Qt::WA_QuitOnClose, false);
    setAttribute(Qt::WA_TranslucentBackground);
    setModal(false);
    createShadowEffectTo(this);
    setStandardButtons(buttons);
    setupUi(type, messageBoxParam); // special style

    if (messageBoxParam.timeInMs > 0) {
        setTimedButton(messageBoxParam.timedButtonText);
        _refreshBtnTextTimer.setInterval(1000);
        _closeMsgBoxTimer.setInterval(messageBoxParam.timeInMs);
        connect(&_refreshBtnTextTimer, &QTimer::timeout, this, &TimedMessageBox::refreshTimedButtonText);
        connect(&_closeMsgBoxTimer, &QTimer::timeout, this, [this] { _timedButton->click(); });
    }
}

void TimedMessageBox::refreshTimedButtonText()
{
    setTimedButtonText(
        QStringLiteral("%1(%2s)").arg(_timedButtonOriText).arg(round(_closeMsgBoxTimer.remainingTime() / 1000.)));
}
void TimedMessageBox::showEvent(QShowEvent* event)
{
    if (_closeMsgBoxTimer.interval() > 0) {
        startTimer();
        refreshTimedButtonText();
    }

    const QPoint center = QApplication::desktop()->availableGeometry(this).center();
    move(center - QPoint(rect().width() / 2, rect().height() / 2));
    QMessageBox::showEvent(event);
}

void TimedMessageBox::mousePressEvent(QMouseEvent* event)
{
    cancelCountdown();
    if (event->button() == Qt::LeftButton) {
        _lastMousePos = event->globalPos();
        _mousePressed = true;
    }
    QMessageBox::mousePressEvent(event);
}

void TimedMessageBox::mouseMoveEvent(QMouseEvent* event)
{
    if (_mousePressed) {
        move(pos() + event->globalPos() - _lastMousePos);
        _lastMousePos = event->globalPos();
    }
    QMessageBox::mouseMoveEvent(event);
}

void TimedMessageBox::mouseReleaseEvent(QMouseEvent* event)
{
    _mousePressed = false;
    QMessageBox::mouseReleaseEvent(event);
}

void TimedMessageBox::paintEvent(QPaintEvent* event)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    QPainterPath path;
    path.addRoundedRect(rect().adjusted(4, 4, -4, -4), k_radius, k_radius);
    p.setPen(k_backgroundColor);
    p.fillPath(path, k_backgroundColor);
    p.drawPath(path);
    QMessageBox::paintEvent(event);
}
void TimedMessageBox::closeMessageBox() { close(); }

void TimedMessageBox::setupUi(QtMsgType type, const TimedMessageBoxParam& messageBoxParam)
{
    setStyleSheet(k_styleSheet); // default style

    // icon
    auto* const iconTypeLabel = new QLabel(this);
    QString iconPath;
    if (type == QtMsgType::QtCriticalMsg)
        iconPath = QStringLiteral(":/msgbox_error.png"); // use pixcache
    else if (type == QtMsgType::QtWarningMsg)
        iconPath = QStringLiteral(":/msgbox_warning.png");
    else
        iconPath = QStringLiteral(":/msgbox_info.png");
    iconTypeLabel->setPixmap(QPixmap(iconPath).scaled(k_iconSize));

    auto* const iconTypeVLayout = new QVBoxLayout;
    iconTypeVLayout->addWidget(iconTypeLabel);
    iconTypeVLayout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Fixed, QSizePolicy::Expanding));

    auto* const iconTypeHLayout = new QHBoxLayout;
    iconTypeHLayout->addSpacerItem(new QSpacerItem(k_iconLeftMargin, 1, QSizePolicy::Fixed));
    iconTypeHLayout->addLayout(iconTypeVLayout);
    // X
    _closeButton = new QPushButton(this);
    connect(_closeButton, &QPushButton::clicked, this, &TimedMessageBox::closeMessageBox);

    auto* closeIconLayout = new QHBoxLayout;
    closeIconLayout->addSpacerItem(new QSpacerItem(1, 1, QSizePolicy::Expanding));
    closeIconLayout->addWidget(_closeButton);
    // text
    auto* const textLayout = new QVBoxLayout;
    auto* title = generateTextLabel(messageBoxParam.title, this);
    if (messageBoxParam.title.size())
        textLayout->addWidget(title);
    auto* text = generateTextLabel(messageBoxParam.text, this);
    if (messageBoxParam.text.size())
        textLayout->addWidget(text);
    auto* solution = generateTextLabel(messageBoxParam.solution, this);
    if (messageBoxParam.solution.size())
        textLayout->addWidget(solution);
    textLayout->addSpacerItem(
        new QSpacerItem(k_textSize.width(), k_textBottomMargin, QSizePolicy::Fixed, QSizePolicy::Fixed));

    auto* const gridLayout = static_cast<QGridLayout*>(layout());
    gridLayout->addLayout(iconTypeHLayout, 1, 0);
    gridLayout->addLayout(textLayout, 1, 1);
    gridLayout->addLayout(closeIconLayout, 0, 1);
    // style
    title->setProperty("titleField", true);
    text->setProperty("textField", true);
    solution->setProperty("detailField", true);
    _closeButton->setProperty("closeIconButton", true);
    adjustSize();
}

void TimedMessageBox::setTimedButton(const QString& buttonText)
{
    auto* const found = dynamic_cast<QPushButton*>(button(QMessageBox::StandardButton::Ok));
    if (!found) {
        _timedButton = new QPushButton(buttonText.size() ? buttonText : tr("OK"), this);
    } else {
        _timedButton = found;
        _timedButton->setText(buttonText);
    }
    _timedButtonOriText = _timedButton->text();
}
