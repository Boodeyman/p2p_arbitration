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

void setLightStyle(QWidget *widget) {
    QPalette lightPalette;
    lightPalette.setColor(QPalette::Window, QColor("#f5f5f5")); // Светло-серый цвет для фона
    lightPalette.setColor(QPalette::WindowText, QColor("#404040")); // Темно-серый цвет для текста
    lightPalette.setColor(QPalette::Base, QColor("#ffffff")); // Белый цвет для базовых элементов
    lightPalette.setColor(QPalette::AlternateBase, QColor("#e0e0e0")); // Светло-серый цвет для чередующихся элементов
    lightPalette.setColor(QPalette::ToolTipBase, QColor("#f5f5f5")); // Светло-серый цвет для подсказок
    lightPalette.setColor(QPalette::ToolTipText, QColor("#404040")); // Темно-серый цвет для текста подсказок
    lightPalette.setColor(QPalette::Text, QColor("#404040")); // Темно-серый цвет для текста
    lightPalette.setColor(QPalette::Button, QColor("#d6d6d6")); // Светло-серый цвет для кнопок
    lightPalette.setColor(QPalette::ButtonText, QColor("#404040")); // Темно-серый цвет для текста на кнопках
    lightPalette.setColor(QPalette::BrightText, QColor("#ff0000")); // Яркий красный цвет для яркого текста
    lightPalette.setColor(QPalette::Link, QColor("#1e90ff")); // Яркий синий цвет для ссылок
    lightPalette.setColor(QPalette::Highlight, QColor("#a6c8ff")); // Светло-голубой цвет для выделенных элементов
    lightPalette.setColor(QPalette::HighlightedText, QColor("#404040")); // Темно-серый цвет для текста выделенных элементов
    widget->setPalette(lightPalette);
}

