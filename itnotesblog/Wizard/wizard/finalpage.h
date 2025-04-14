#ifndef FINALPAGE_H
#define FINALPAGE_H

#include <QWizardPage>

class QLabel;

class FinalPage : public QWizardPage {
public:
    FinalPage(QWidget* parent = nullptr);
    ~FinalPage();

protected:
    void initializePage();

private:
    QLabel* m_lbl;
};

#endif // FINALPAGE_H
