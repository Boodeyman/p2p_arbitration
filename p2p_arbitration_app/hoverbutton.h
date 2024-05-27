#ifndef HOVERBUTTON_H
#define HOVERBUTTON_H

#include <QPushButton>
#include <QLineEdit>
#include <QEnterEvent>

class HoverButton : public QPushButton {
    Q_OBJECT
public:
    HoverButton(QLineEdit *lineEdit, QWidget *parent = nullptr);
protected:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
signals:
    void hovered(bool isHovered);
private:
    QLineEdit *lineEdit;
};

#endif // HOVERBUTTON_H
