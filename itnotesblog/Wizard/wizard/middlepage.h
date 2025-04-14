#ifndef MIDDLEPAGE_H
#define MIDDLEPAGE_H

#include <QWizardPage>

class QLabel;

class MiddlePage : public QWizardPage {
public:
    MiddlePage(const QString& subTitle, QWidget* parent = nullptr);
    ~MiddlePage();

protected:
    void initializePage();
    int nextId() const;

private:
    QLabel* m_lbl;
};

#endif // MIDDLEPAGE_H
