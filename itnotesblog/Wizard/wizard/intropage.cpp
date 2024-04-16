#include "intropage.h"

#include <QLineEdit>
#include <QLabel>
#include <QRadioButton>
#include <QBoxLayout>

#include "shared_defs.h"

IntroPage::IntroPage(QWidget* parent)
    : QWizardPage(parent) {

    setTitle(trUtf8("Начальная страница"));
    setSubTitle(trUtf8("Пожалуйста, представьтесь."));

    QBoxLayout* mainLayout = new QVBoxLayout;

    mainLayout->addWidget(m_edit = new QLineEdit);
    mainLayout->addWidget(m_errorLbl = new QLabel);
    mainLayout->addWidget(m_rbtnPath1 = new QRadioButton(trUtf8("Путь 1")));
    mainLayout->addWidget(m_rbtnPath2 = new QRadioButton(trUtf8("Путь 2")));
    mainLayout->addStretch(1);

    registerField("userName*", m_edit);
    m_errorLbl->setStyleSheet("color: red; font-size: 8pt;");

    m_rbtnPath1->setChecked(true);

    setLayout(mainLayout);
}

IntroPage::~IntroPage() {

}

int IntroPage::nextId() const {
    if(m_rbtnPath1->isChecked()) {
        return MIDDLE_PAGE_PATH_1;
    }

    return MIDDLE_PAGE_PATH_2;
}

bool IntroPage::validatePage() {
    bool ok = 2 <= m_edit->text().trimmed().size();

    m_errorLbl->setText(ok ? "" : trUtf8("Имя должно состоять хотя бы из двух символов"));
    m_edit->setFocus();

    return ok;
}
