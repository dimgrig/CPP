#include "finalpage.h"

#include <QBoxLayout>
#include <QLabel>
#include <QVariant>

FinalPage::FinalPage(QWidget* parent) : QWizardPage(parent) {
    setTitle(trUtf8("Финальная страница"));
    setSubTitle(trUtf8("Работа с программой почти окончена."));

    QBoxLayout* l = new QVBoxLayout;
    l->addWidget(m_lbl = new QLabel);

    setLayout(l);
}

FinalPage::~FinalPage() {
}

void FinalPage::initializePage() {
    m_lbl->setText(trUtf8("До свидания, <strong>%1</strong>.").arg(field("userName").toString()));
}
