#include "stylehelper.h"
#include "mainwindow.h"
#include <QWidget>
#include <QPalette>
#include <QColor>
#include <QComboBox>
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

    // Специфические стили для QTableWidget
    if (QTableWidget *tableWidget = qobject_cast<QTableWidget *>(widget)) {
        tableWidget->setStyleSheet(
            "QTableWidget {"
            "    background-color: #16181c;"
            "    color: #cccccc;"
            "    gridline-color: #444444;"
            "}"
            "QTableWidget QHeaderView::section {"
            "    background-color: #16181c;"
            "    color: #cccccc;"
            "    border: 1px solid #444444;"
            "}"
            "QTableWidget::item {"
            "    background-color: #16181c;"
            "    color: #cccccc;"
            "}"
            );
    }
    if (QTableWidget *topGainersWidget = qobject_cast<QTableWidget *>(widget)) {
        topGainersWidget->setStyleSheet(
            "QTableWidget {"
            "    background-color: #16181c;"
            "    color: #cccccc;"
            "    gridline-color: #444444;"
            "}"
            "QTableWidget QHeaderView::section {"
            "    background-color: #16181c;"
            "    color: #cccccc;"
            "    border: 1px solid #444444;"
            "}"
            "QTableWidget::item {"
            "    background-color: #16181c;"
            "    color: #cccccc;"
            "}"
            );
    }
    if (QComboBox *comboBox = qobject_cast<QComboBox *>(widget)) {
        comboBox->setStyleSheet(
            "QComboBox {"
            "    background-color: #16181c;"
            "    color: #cccccc;"
            "    padding: 10px;"
            "}"
            "QComboBox QAbstractItemView {"
            "    background-color: #16181c;"
            "    color: #cccccc;"
            "    selection-background-color: #444444;"
            "    selection-color: #cccccc;"
            "}"
            "QComboBox::drop-down {"
            "    subcontrol-origin: padding;"
            "    subcontrol-position: top right;"
            "    background-color: #16181c;"
            "}"
            "QComboBox::down-arrow {"
            "    image: url(:/icons/icons/arrowWhite.png);"
            "    width: 20px;"
            "}"
            );
    }
}


void setLightStyle(QWidget *widget) {
    QPalette lightPalette;
    lightPalette.setColor(QPalette::Window, QColor("#f5f5f5"));
    lightPalette.setColor(QPalette::WindowText, QColor("#404040"));
    lightPalette.setColor(QPalette::Base, QColor("#ffffff"));
    lightPalette.setColor(QPalette::AlternateBase, QColor("#e0e0e0"));
    lightPalette.setColor(QPalette::ToolTipBase, QColor("#f5f5f5"));
    lightPalette.setColor(QPalette::ToolTipText, QColor("#404040"));
    lightPalette.setColor(QPalette::Text, QColor("#404040"));
    lightPalette.setColor(QPalette::Button, QColor("#d6d6d6"));
    lightPalette.setColor(QPalette::ButtonText, QColor("#404040"));
    lightPalette.setColor(QPalette::BrightText, QColor("#ff0000"));
    lightPalette.setColor(QPalette::Link, QColor("#1e90ff"));
    lightPalette.setColor(QPalette::Highlight, QColor("#a6c8ff"));
    lightPalette.setColor(QPalette::HighlightedText, QColor("#404040"));

    widget->setPalette(lightPalette);

    // Специфические стили для QTableWidget
    if (QTableWidget *tableWidget = qobject_cast<QTableWidget *>(widget)) {
        tableWidget->setStyleSheet(
            "QTableWidget {"
            "    background-color: #f5f5f5;"
            "    color: #404040;"
            "    gridline-color: #d6d6d6;"
            "}"
            "QTableWidget QHeaderView::section {"
            "    background-color: #f5f5f5;"
            "    color: #404040;"
            "    border: 1px solid #d6d6d6;"
            "}"
            "QTableWidget::item {"
            "    background-color: #f5f5f5;"
            "    color: #404040;"
            "}"
            );
    }
    if (QTableWidget *topGainersWidget = qobject_cast<QTableWidget *>(widget)) {
        topGainersWidget->setStyleSheet(
            "QTableWidget {"
            "    background-color: #f5f5f5;"
            "    color: #404040;"
            "    gridline-color: #d6d6d6;"
            "    border-radius: 15px;"
            "}"
            "QTableWidget QHeaderView::section {"
            "    background-color: #f5f5f5;"
            "    color: #404040;"
            "    border: 1px solid #d6d6d6;"
            "}"
            "QTableWidget::item {"
            "    background-color: #f5f5f5;"
            "    color: #404040;"
            "}"
            );
    }
    if (QComboBox *comboBox = qobject_cast<QComboBox *>(widget)) {
        comboBox->setStyleSheet(
            "QComboBox {"
            "    background-color: #f5f5f5;"
            "    color: #404040;"
            "    padding: 10px;"
            "}"
            "QComboBox QAbstractItemView {"
            "    background-color: #f5f5f5;"
            "    color: #404040;"
            "    selection-background-color: #a6c8ff;"
            "    selection-color: #404040;"
            "}"
            "QComboBox::drop-down {"
            "    subcontrol-origin: padding;"
            "    subcontrol-position: top right;"
            "    background-color: #f5f5f5;"
            "}"
            "QComboBox::down-arrow {"
            "    image: url(:/icons/icons/arrowBlack.png);"
            "    width: 20px;"
            "}"
            );
    }
}


