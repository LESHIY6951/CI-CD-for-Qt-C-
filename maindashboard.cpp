#include "maindashboard.h"
#include "ui_maindashboard.h"

MainDashBoard::MainDashBoard(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainDashBoard)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("89.111.141.217");
    db.setDatabaseName("testdb");
    db.setUserName("lesh1y");
    db.setPassword("qpalzm321");

    db.open();


    RefreshTable();


}

MainDashBoard::~MainDashBoard()
{
    delete ui;
}


void MainDashBoard::on_AddButton_2_clicked()
{
    QSqlQuery query(db);
    query.prepare("INSERT INTO students (name, number, birth_date, begin_date) VALUES (:name, :number, :birth_date, :begin_date)");
    query.bindValue(":name", ui->FIO_2->text());
    query.bindValue(":number", ui->Num_2->text());
    query.bindValue(":birth_date", ui->BirthDate_2->date());
    query.bindValue(":begin_date", ui->BeginDate_2->date());
    query.exec();
    ui->FIO_2->clear();
    ui->Num_2->clear();
    //ui->BirthDate_2->clear();
    //ui->BeginDate_2->clear();
    RefreshTable();
}

void MainDashBoard::RefreshTable() {
    QSqlTableModel *model = new QSqlTableModel(this);
    model->setTable("students");
    model->select();

    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("ФИО"));
    model->setHeaderData(2, Qt::Horizontal, tr("Номер зачетной книжки"));
    model->setHeaderData(3, Qt::Horizontal, tr("Дата рождения"));
    model->setHeaderData(4, Qt::Horizontal, tr("Дата поступления"));

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
}


void MainDashBoard::on_DeleteButton_2_clicked()
{
    QSqlQuery query(db);

    if (!ui->FIO_2->text().isEmpty()) {
        query.prepare("DELETE FROM students WHERE name = :name");
        query.bindValue(":name", ui->FIO_2->text());
        query.exec();
    } else if (!ui->Num_2->text().isEmpty()) {
        query.prepare("DELETE FROM students WHERE number = :num");
        query.bindValue(":num", ui->Num_2->text());
        query.exec();
    } else {
        QMessageBox::information(this, "INFO", "Заполните какое-то поле для удаления");
    }

    ui->FIO_2->clear();
    ui->Num_2->clear();
    RefreshTable();

}


void MainDashBoard::on_pushButton_clicked()
{
    // Получаем значения из QSpinBox для возраста
    int minAge = ui->spinBox->value();
    int maxAge = ui->spinBox_2->value();

    // Получаем значения из QDateEdit для фильтрации по дате
    QDate dateAfter = ui->dateEdit->date();
    QDate dateBefore = ui->dateEdit_2->date();

    // Преобразуем QDate в строку формата YYYY-MM-DD
    QString dateAfterStr = dateAfter.toString("yyyy-MM-dd");
    QString dateBeforeStr = dateBefore.toString("yyyy-MM-dd");

    // Строим SQL-запрос с условиями фильтрации
    QString queryStr = QString(
        "SELECT * FROM students "
        "WHERE (EXTRACT(YEAR FROM AGE(NOW(), birth_date)) BETWEEN :minAge AND :maxAge) "
        "AND (begin_date BETWEEN :dateAfter AND :dateBefore)"
    );

    // Подготавливаем запрос
    QSqlQuery query(db);
    query.prepare(queryStr);
    query.bindValue(":minAge", minAge);
    query.bindValue(":maxAge", maxAge);
    query.bindValue(":dateAfter", dateAfterStr);  // Используем строковое значение даты
    query.bindValue(":dateBefore", dateBeforeStr);  // Используем строковое значение даты

    // Выполняем запрос
    if (query.exec()) {
        // Если запрос выполнен успешно, создаем модель данных на основе результата
        QSqlQueryModel *model = new QSqlQueryModel(this);
        model->setQuery(query);  // Устанавливаем результат запроса в модель
        model->setHeaderData(0, Qt::Horizontal, tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, tr("ФИО"));
        model->setHeaderData(2, Qt::Horizontal, tr("Номер зачетной книжки"));
        model->setHeaderData(3, Qt::Horizontal, tr("Дата рождения"));
        model->setHeaderData(4, Qt::Horizontal, tr("Дата поступления"));

        // Устанавливаем модель данных для QTableView
        ui->tableView->setModel(model);
    } else {
        qDebug() << "Query failed: " << query.lastError();
    }
}

