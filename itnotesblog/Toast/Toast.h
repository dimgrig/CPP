#ifndef TOAST_H
#define TOAST_H

#include <QWidget>
#include <QTimer>

class QTextEdit;
class QLabel;

class Toast : public QWidget {
    Q_OBJECT
public:
    Toast(QWidget* parent = nullptr);
    ~Toast();

    void show_toast(const QString& message, const char* const style_class,
                    int show_time = 3000, double x_position = 0.7, double y_position = 0.7);
protected:
    void resizeEvent(QResizeEvent*);
private slots:

private:
    QTextEdit* _edit;

    QLabel* _l_toast;
    QTimer _timer;

    int _show_time = 1000;
    double _x_position = 0.7;
    double _y_position = 0.7;
};

#endif // TOAST_H
