#include "login_dialog.h"
#include "ui_login_dialog.h"
#include "stylehelper.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    QString basePath = QCoreApplication::applicationDirPath();

    databasePath = basePath + "/../Resources/users.db";

    initializeDatabase();

    if (counter % 2 == 0) {
        setDarkStyle(this);

    }
    else {
        setLightStyle(this);
    }
    connect(ui->loginButton, &QPushButton::clicked, this, &LoginDialog::handleLogin);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &LoginDialog::handleRegister);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::initializeDatabase() {
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
            accept();
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
