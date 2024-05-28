#include "login_dialog.h"
#include "ui_login_dialog.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    initializeDatabase();
    setDarkStyle(this);

    connect(ui->loginButton, &QPushButton::clicked, this, &LoginDialog::handleLogin);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &LoginDialog::handleRegister);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::initializeDatabase() {
    QString databasePath = "/Users/kirillzykov/Desktop/HSE DSBA/Programming/C++/CryptoX project/p2p_arbitration/p2p_arbitration_app/users.db";
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(databasePath);

    if (!db.open()) {
        QMessageBox::critical(this, "Ошибка базы данных", db.lastError().text());
        qDebug() << "Failed to open database at" << databasePath;
        return;
    } else {
        qDebug() << "Database opened at" << databasePath;
    }

    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS users ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "username TEXT NOT NULL, "
               "password TEXT NOT NULL)");

    if (query.lastError().isValid()) {
        qDebug() << "Failed to create table:" << query.lastError();
    } else {
        qDebug() << "Table created or already exists";
    }
}

void LoginDialog::handleLogin() {
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Ошибка ввода", "Пожалуйста, введите и имя пользователя, и пароль.");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (query.exec()) {
        if (query.next()) {
            QMessageBox::information(this, "Успешный вход", "Добро пожаловать, " + username + "!");
            accept(); // Закрывает диалог с успешным результатом
        } else {
            QMessageBox::warning(this, "Ошибка входа", "Неверное имя пользователя или пароль.");
        }
    } else {
        QMessageBox::critical(this, "Ошибка базы данных", query.lastError().text());
    }
}

void LoginDialog::handleRegister() {
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Ошибка ввода", "Пожалуйста, введите и имя пользователя, и пароль.");
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password) VALUES (:username, :password)");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (query.exec()) {
        QMessageBox::information(this, "Регистрация успешна", "Пользователь " + username + " успешно зарегистрирован.");
    } else {
        QMessageBox::critical(this, "Ошибка базы данных", query.lastError().text());
    }
}

void LoginDialog::setDarkStyle(QWidget *widget) {
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor("#16181c"));
    darkPalette.setColor(QPalette::WindowText, QColor(204, 204, 204));
    darkPalette.setColor(QPalette::Base, QColor("#16181c"));
    darkPalette.setColor(QPalette::AlternateBase, QColor(22, 24, 28));
    darkPalette.setColor(QPalette::ToolTipBase, QColor(204, 204, 204));
    darkPalette.setColor(QPalette::ToolTipText, QColor(204, 204, 204));
    darkPalette.setColor(QPalette::Text, QColor(204, 204, 204));
    darkPalette.setColor(QPalette::Button, QColor(62, 62, 62));
    darkPalette.setColor(QPalette::ButtonText, QColor(255, 255, 255));
    darkPalette.setColor(QPalette::BrightText, QColor(255, 0, 0));
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(50, 60, 90));
    darkPalette.setColor(QPalette::HighlightedText, QColor(204, 204, 204));
    widget->setPalette(darkPalette);
}
