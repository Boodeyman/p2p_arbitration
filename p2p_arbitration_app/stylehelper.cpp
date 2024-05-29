#include "stylehelper.h"

#include <QWidget>
#include <QPalette>
#include <QColor>

void setDarkStyle(QWidget *widget) {
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
