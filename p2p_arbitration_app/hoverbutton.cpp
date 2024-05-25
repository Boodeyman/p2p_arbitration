#include "hoverbutton.h"
#include <QVBoxLayout>

HoverButton::HoverButton(QPushButton *button, QLineEdit *lineEdit, QWidget *parent)
    : QWidget(parent), button(button), lineEdit(lineEdit), hoverText(""), defaultIcon(QIcon("://icons/icons/searchLine.png")) {
    this->button->setIcon(defaultIcon); // Установите начальную иконку
    lineEdit->setVisible(false); // Изначально скрыть QLineEdit
    lineEdit->setFixedHeight(button->sizeHint().height()); // Установить фиксированную высоту для предотвращения сдвигов

    // Установите родительские отношения вручную
    button->setParent(this);
    lineEdit->setParent(this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(button);
    layout->addWidget(lineEdit);
    setLayout(layout);

    connect(button, &QPushButton::clicked, [=]() {
        lineEdit->setVisible(true); // Показать QLineEdit при нажатии на кнопку
        lineEdit->setFocus();
    });

    connect(lineEdit, &QLineEdit::editingFinished, [=]() {
        lineEdit->setVisible(false); // Скрыть QLineEdit после завершения редактирования
    });
}

void HoverButton::enterEvent(QEnterEvent *event) {
    Q_UNUSED(event);
    lineEdit->setVisible(true); // Показать QLineEdit при наведении
}

void HoverButton::leaveEvent(QEvent *event) {
    Q_UNUSED(event);
    if (!lineEdit->hasFocus()) {
        lineEdit->setVisible(false); // Скрыть QLineEdit при уходе, если он не в фокусе
    }
    button->setIcon(defaultIcon); // Восстановить иконку
}
