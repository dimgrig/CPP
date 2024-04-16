#ifndef INTROPAGE_H
#define INTROPAGE_H

#include <QWizardPage>

class QLineEdit;
class QRadioButton;
class QLabel;

class IntroPage : public QWizardPage {
    Q_OBJECT
public:
    IntroPage(QWidget* parent = nullptr);
    ~IntroPage();

protected:
    int nextId() const;
    bool validatePage();
private:
    QLineEdit* m_edit;
    QLabel* m_errorLbl;

    QRadioButton* m_rbtnPath1;
    QRadioButton* m_rbtnPath2;
};

#endif // INTROPAGE_H
