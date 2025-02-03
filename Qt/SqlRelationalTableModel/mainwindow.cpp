#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <locale.h>

const int StatusTimeout = AQP::MSecPerSecond * 10;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //qCDebug(logDebug()) << this->ui->dw_batch_parameters->height();

    TestRunner tr;
    RUN_TEST(tr, FunctionsTest);
    RUN_TEST(tr, MacrosesTest);

    this->setFont(QFont("Noto Sans", 10)); //10
    //qCDebug(logDebug()) << this->font();

//    QLocale locale = QLocale::system(); // current locale
//    QLocale russian(QLocale::Russian);
//    locale.setNumberOptions(russian.numberOptions()); // borrow number options from the Russian locale
//    QLocale::setDefault(locale); // set as default
    QLocale::setDefault(QLocale::Russian);
    QLocale::setDefault(QLocale::Russian);
    QLocale::setDefault(QLocale::Russian);
    QLocale locale = QLocale::system(); // current locale
    //if (locale.name() != "ru_RU") {
//        qCDebug(logDebug()) << std::locale().name() << locale.name() << QLocale().name();
//        AQP::warning(this, "Ошибка", "Ошибка установки локали. Выполнить sudo dpkg-reconfigure locales и выбрать локаль ru_RU");
//        exit(1);
//    }

//    qCDebug(logDebug()) << std::locale().name() << locale.name();
//    setlocale(LC_ALL, "ru_RU");
//    //std::locale::global(std::locale(std::locale("ru_RU"), "C", std::locale::numeric));
    //qCDebug(logDebug()) << std::locale().name() << locale.name();

    this->setAttribute(Qt::WA_AlwaysShowToolTips);

    if (QFile(QSS).exists()) {
        QScopedPointer<QFile> styleFile(new QFile(QSS));
        styleFile.data()->open(QFile::ReadOnly);
        QString qssStr = styleFile.data()->readAll();
        styleFile.data()->close();
        this->setStyleSheet(qssStr);
    } else {
        qCDebug(logWarning()) << "style file does not exist";
    }

    //this->ui->centralwidget->hide();

    //this->ui->pb_test->setVisible(false);
    //this->ui->pb_test_oscillogram->setVisible(false);
    //this->ui->pb_quit->setVisible(false);

    //setWindowTitle(QString("%1[*]").arg(QApplication::applicationDisplayName()));
    setWindowTitle(QString("[*]"));

    //this->about_panel->hide();

    //this->installEventFilter(this);

    this->docks();
    this->mvc();

    this->menu_bar();
    this->tool_bar();

    this->connect_signal_slot();

    this->ui->cb_language->addItems(QStringList() << "ru_RU" << "en_US");

    connect(this->ui->cb_language, static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
           [=](const QString &str){
       qtLanguageTranslator.load("QtLanguage_" + str, QCoreApplication::applicationDirPath());   // Загружаем перевод
       qApp->installTranslator(&qtLanguageTranslator);        // Устанавливаем перевод в приложение
    });

    qtLanguageTranslator.load(QString("QtLanguage_") + QString("en_US"), QCoreApplication::applicationDirPath());
    qApp->installTranslator(&qtLanguageTranslator);

    {
        /* Первым делом необходимо создать объект для работы с базой данных
     * и инициализировать подключение к базе данных
     * */
        db = new DataBase();
        db->connectToDataBase();

        /* После чего производим наполнение таблицы базы данных
     * контентом, который будет отображаться в tableView и tableViewDevice
     * */
        for(int i = 1; i < 4; i++){
            QVariantList data;
            data.append("Device " + QString::number(i));
            data.append("192.168.0." + QString::number(i));
            db->inserIntoDeviceTable(data);
        }

        for(int i = 0; i < 10; i++){
            QVariantList data;
            QString random = QString::number(qrand() % ((4 + 1) - 1) + 1);
            data.append(QDate::currentDate());
            data.append(QTime::currentTime());
            data.append(random);
            data.append(random);
            db->inserIntoMainTable(data);
        }

        /* Инициализируем модели для представления данных
     * с заданием названий колонок
     * */
        this->setupMainModel(TABLE,
                             QStringList() << trUtf8("id")
                                           << trUtf8("Дата")
                                           << trUtf8("Время")
                                           << trUtf8("Имя хоста")
                                           << trUtf8("IP адрес")
                             );

        this->setupDeviceModel(DEVICE,
                               QStringList() << trUtf8("id")
                                             << trUtf8("Имя хоста")
                                             << trUtf8("IP адрес")
                               );
        /* Инициализируем внешний вид таблицы с данными
     * */
        this->createUI();
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if (okToClearData())
        event->accept();
    else
        event->ignore();

    this->_saveGeometry();

    QMainWindow::closeEvent(event);
}

bool MainWindow::eventFilter(QObject *target, QEvent *event) {
    Q_UNUSED(target);
    Q_UNUSED(event);

    return false;
}

void MainWindow::connect_signal_slot() {
    connect(this->timer, &QTimer::timeout, this, &MainWindow::on_timer);
    this->timer->start(100);
}

void MainWindow::menu_bar() {

}

void MainWindow::tool_bar() {

}

void MainWindow::auth_users() {

}

void MainWindow::init_auth_users() {

}

void MainWindow::mvc() {

}

void MainWindow::docks() {

}

void MainWindow::_saveGeometry() {

}

void MainWindow::test() {

}

bool MainWindow::okToClearData()
{
//    if (isWindowModified())
//        return AQP::okToClearData(&MainWindow::save_as, this, tr("Несохраненные изменения"), tr("Тестовая карта содержит несохраненные изменения. Сохранить изменения?"));
    return true;
}

void MainWindow::auth_ok() {

}

void MainWindow::on_timer() {

}


/* Метод для инициализации модели представления данных
 * */
void MainWindow::setupMainModel(const QString &tableName, const QStringList &headers)
{
    /* Производим инициализацию модели представления данных
     * с установкой имени таблицы в базе данных, по которому
     * будет производится обращение в таблице
     * */
    modelMain = new QSqlRelationalTableModel(this);
    modelMain->setTable(tableName);
    /* Устанавливаем связи с таблицей устройств, по которым будет производится
     * подстановка данных
     * В метода setRelation указывается номер колонки, в которой будет
     * производится подстановка, а также с помощью класса
     * QSqlRelation указывается имя таблицы,
     * параметр, по которому будет произведена выборка строки
     * и колонка, из которой будут взяты данные
     * */
    modelMain->setRelation(3, QSqlRelation(DEVICE, "id", DEVICE_HOSTNAME));
    modelMain->setRelation(4, QSqlRelation(DEVICE, "id", DEVICE_IP));

    /* Устанавливаем названия колонок в таблице с сортировкой данных
     * */
    for(int i = 0, j = 0; i < modelMain->columnCount(); i++, j++){
        modelMain->setHeaderData(i,Qt::Horizontal,headers[j]);
    }
    // Устанавливаем сортировку по возрастанию данных по нулевой колонке
    modelMain->setSort(0,Qt::AscendingOrder);
    modelMain->select(); // Делаем выборку данных из таблицы
}

void MainWindow::setupDeviceModel(const QString &tableName, const QStringList &headers)
{
    /* Производим инициализацию модели представления данных
     * с установкой имени таблицы в базе данных, по которому
     * будет производится обращение в таблице
     * */
    modelDevice = new QSqlRelationalTableModel(this);
    modelDevice->setTable(tableName);

    /* Устанавливаем названия колонок в таблице с сортировкой данных
     * */
    for(int i = 0, j = 0; i < modelDevice->columnCount(); i++, j++){
        modelDevice->setHeaderData(i,Qt::Horizontal,headers[j]);
    }
    // Устанавливаем сортировку по возрастанию данных по нулевой колонке
    modelDevice->setSort(0,Qt::AscendingOrder);
    modelDevice->select(); // Делаем выборку данных из таблицы
}

void MainWindow::createUI()
{
    ui->tableView->setModel(modelMain);     // Устанавливаем модель на TableView
    ui->tableView->setColumnHidden(0, true);    // Скрываем колонку с id записей
    // Разрешаем выделение строк
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Устанавливаем режим выделения лишь одно строки в таблице
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    // Устанавливаем размер колонок по содержимому
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    modelMain->select(); // Делаем выборку данных из таблицы

    ui->tableViewDevice->setModel(modelDevice);     // Устанавливаем модель на TableView
    ui->tableViewDevice->setColumnHidden(0, true);    // Скрываем колонку с id записей
    // Разрешаем выделение строк
    ui->tableViewDevice->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Устанавливаем режим выделения лишь одно строки в таблице
    ui->tableViewDevice->setSelectionMode(QAbstractItemView::SingleSelection);
    // Устанавливаем размер колонок по содержимому
    ui->tableViewDevice->resizeColumnsToContents();
    ui->tableViewDevice->setItemDelegate(new QSqlRelationalDelegate(ui->tableViewDevice));
    ui->tableViewDevice->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableViewDevice->horizontalHeader()->setStretchLastSection(true);

    modelDevice->select();
}
