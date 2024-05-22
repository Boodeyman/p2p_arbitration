#ifndef HOVERBUTTON_H
#define HOVERBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QEnterEvent>
#include <QIcon>

class HoverButton : public QWidget {
    Q_OBJECT

public:
    HoverButton(QPushButton *button, QLineEdit *lineEdit, QWidget *parent = nullptr);

private:
    QPushButton *button;
    QLineEdit *lineEdit;
    QString hoverText;
    QIcon defaultIcon;

protected:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
};

#endif // HOVERBUTTON_H
