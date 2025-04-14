#include "Toast.h"

#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QTimer>
#include <QVBoxLayout>

#include "Logger.h"

static const char* const TOAST_STYLESHEET =
"QLabel {"
"  font-weight: bold;"
"  padding: 5px 7px;"
"  border: 2px solid;"
"  border-radius: 10px;"
"}"
"[class=Info] {"
"  background-color: rgba(128, 128, 128, 50);"
"  border-color: gray;"
"}"
"[class=Ok] {"
"  background-color: rgba(0, 255, 0, 50);"
"  border-color: green;"
"}"
"[class=Warning] {"
"  background-color: rgba(255, 255, 0, 50);"
"  border-color: yellow;"
"}"
"[class=Error] {"
"  background-color: rgba(255, 0, 0, 50);"
"  border-color: red;"
"}"
"[class=Wait] {"
"  background-color: rgba(0, 0, 255, 50);"
"  border-color: blue;"
"}";

Toast::Toast(QWidget* parent)
    : QWidget(parent)
{
    this->hide();

    QVBoxLayout* toast_layout = new QVBoxLayout;
    this->setLayout(toast_layout);

    _l_toast = new QLabel(this);
    _l_toast->setText(trUtf8(""));
    _l_toast->setAlignment(Qt::AlignCenter);
    _l_toast->setWordWrap(true);
    _l_toast->setProperty("class", "Info");
    _l_toast->setStyleSheet(TOAST_STYLESHEET);
    _l_toast->adjustSize();
    toast_layout->addWidget(_l_toast);

    _timer.setSingleShot(true);
    connect(&_timer, &QTimer::timeout, this, &Toast::hide);
    connect(&_timer, &QTimer::timeout, this, &Toast::lower);

    //this->resize(200, 100);
    this->setMinimumSize(200, 100);
    //this->adjustSize();
}

Toast::~Toast() {

}

void Toast::resizeEvent(QResizeEvent*) {
    int x = qApp->activeWindow()->size().width() * _x_position - this->width() / 2;
    int y = qApp->activeWindow()->size().height() * _y_position - this->height() / 2;
    this->move(x, y);
}

void Toast::show_toast(const QString& message, const char* const style_class, int show_time, double x_position, double y_position) {
    _x_position = x_position;
    _y_position = y_position;
    _show_time = show_time;

    if(_timer.isActive()) {
        //return;
        _timer.stop();
    }

    _l_toast->setText(message);
    _l_toast->setProperty("class", style_class); 
    _l_toast->setStyleSheet(_l_toast->styleSheet());
    _l_toast->update();
    _l_toast->adjustSize();
    _l_toast->raise();

    this->setMinimumSize(200, 100);
    this->adjustSize();
    this->raise();
    this->show();

    _timer.start(show_time);

    resizeEvent(NULL);
}
