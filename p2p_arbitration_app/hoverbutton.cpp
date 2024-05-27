#include "hoverbutton.h"

HoverButton::HoverButton(QLineEdit *lineEdit, QWidget *parent)
    : QPushButton(parent), lineEdit(lineEdit) {
    connect(this, &HoverButton::hovered, this, [lineEdit](bool isHovered) {
        lineEdit->setVisible(isHovered);
        if (isHovered) {
            lineEdit->setFocus();
        }
    });
}

void HoverButton::enterEvent(QEnterEvent *event) {
    emit hovered(true);
    QPushButton::enterEvent(event);
}

void HoverButton::leaveEvent(QEvent *event) {
    emit hovered(false);
    QPushButton::leaveEvent(event);
}
