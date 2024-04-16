#include "middlepage.h"

#include "shared_defs.h"

#include <QBoxLayout>
#include <QLabel>
#include <QVariant>

MiddlePage::MiddlePage(const QString& subTitle, QWidget* parent)
    : QWizardPage(parent)
{
    setTitle(trUtf8("Промежуточная страница"));
    setSubTitle(subTitle);
    setCommitPage(true);

    QBoxLayout* l = new QVBoxLayout;
    l->addWidget(m_lbl = new QLabel);

    setLayout(l);
}

MiddlePage::~MiddlePage() {

}

void MiddlePage::initializePage() {
    m_lbl->setText(trUtf8("Здравствуйте, <strong>%1</strong>.").
                   arg(field("userName").toString()));
}

int MiddlePage::nextId() const {
    return FINAL_PAGE;
}
