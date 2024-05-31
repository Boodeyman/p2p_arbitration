/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExit;
    QAction *actionru;
    QAction *actionen;
    QWidget *centralwidget;
    QTableWidget *tableWidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QComboBox *comboBox;
    QPushButton *logoutButton;
    QPushButton *hoverButton;
    QLineEdit *lineEdit;
    QLabel *label;
    QFrame *line;
    QComboBox *comboBox_2;
    QTableWidget *topLosersWidget;
    QTableWidget *topGainersWidget;
    QTableWidget *topVolumeWidget;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *themeChange;
    QStatusBar *statusbar;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuLanguage;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1001, 768);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(100);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(0, 0));
        MainWindow->setMaximumSize(QSize(9999, 9999));
        MainWindow->setCursor(QCursor(Qt::ArrowCursor));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/icons/icon_of_app_1.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setLayoutDirection(Qt::LeftToRight);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName("actionExit");
        QIcon icon1;
        QString iconThemeName = QString::fromUtf8("application-exit");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon1 = QIcon::fromTheme(iconThemeName);
        } else {
            icon1.addFile(QString::fromUtf8(":/icons/icons/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
            icon1.addFile(QString::fromUtf8("icons/exit.png"), QSize(), QIcon::Normal, QIcon::On);
        }
        actionExit->setIcon(icon1);
        actionru = new QAction(MainWindow);
        actionru->setObjectName("actionru");
        actionen = new QAction(MainWindow);
        actionen->setObjectName("actionen");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        tableWidget = new QTableWidget(centralwidget);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setGeometry(QRect(0, 310, 1001, 391));
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy1);
        tableWidget->setMouseTracking(true);
        tableWidget->setShowGrid(false);
        tableWidget->setGridStyle(Qt::NoPen);
        tableWidget->horizontalHeader()->setVisible(true);
        tableWidget->horizontalHeader()->setCascadingSectionResizes(false);
        tableWidget->horizontalHeader()->setHighlightSections(false);
        tableWidget->verticalHeader()->setVisible(true);
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(110, 13, 326, 84));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_2 = new QPushButton(horizontalLayoutWidget);
        pushButton_2->setObjectName("pushButton_2");
        sizePolicy1.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy1);
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        font.setPointSize(18);
        font.setBold(true);
        pushButton_2->setFont(font);
        pushButton_2->setMouseTracking(false);
        pushButton_2->setTabletTracking(false);
        pushButton_2->setFlat(true);

        horizontalLayout->addWidget(pushButton_2);

        pushButton = new QPushButton(horizontalLayoutWidget);
        pushButton->setObjectName("pushButton");
        pushButton->setEnabled(true);
        sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy1);
        pushButton->setFont(font);
        pushButton->setFlat(true);

        horizontalLayout->addWidget(pushButton);

        comboBox = new QComboBox(horizontalLayoutWidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        sizePolicy1.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy1);
        comboBox->setFont(font);
        comboBox->setAutoFillBackground(false);
        comboBox->setFrame(true);

        horizontalLayout->addWidget(comboBox);

        logoutButton = new QPushButton(centralwidget);
        logoutButton->setObjectName("logoutButton");
        logoutButton->setGeometry(QRect(940, 30, 61, 51));
        logoutButton->setInputMethodHints(Qt::ImhNone);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/icons/logout_1.png"), QSize(), QIcon::Normal, QIcon::Off);
        logoutButton->setIcon(icon2);
        logoutButton->setIconSize(QSize(30, 30));
        logoutButton->setFlat(true);
        hoverButton = new QPushButton(centralwidget);
        hoverButton->setObjectName("hoverButton");
        hoverButton->setGeometry(QRect(450, 30, 51, 51));
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(hoverButton->sizePolicy().hasHeightForWidth());
        hoverButton->setSizePolicy(sizePolicy2);
        hoverButton->setLayoutDirection(Qt::LeftToRight);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/icons/interface.png"), QSize(), QIcon::Normal, QIcon::Off);
        hoverButton->setIcon(icon3);
        hoverButton->setIconSize(QSize(25, 25));
        hoverButton->setFlat(true);
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(510, 40, 231, 30));
        sizePolicy2.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy2);
        lineEdit->setLayoutDirection(Qt::LeftToRight);
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 90, 90));
        label->setPixmap(QPixmap(QString::fromUtf8(":/icons/icons/icon_of_app_1.png")));
        label->setScaledContents(true);
        line = new QFrame(centralwidget);
        line->setObjectName("line");
        line->setGeometry(QRect(0, 100, 1001, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        comboBox_2 = new QComboBox(centralwidget);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName("comboBox_2");
        comboBox_2->setGeometry(QRect(10, 160, 131, 61));
        topLosersWidget = new QTableWidget(centralwidget);
        topLosersWidget->setObjectName("topLosersWidget");
        topLosersWidget->setGeometry(QRect(410, 140, 241, 101));
        topLosersWidget->setShowGrid(false);
        topLosersWidget->horizontalHeader()->setVisible(false);
        topLosersWidget->verticalHeader()->setVisible(false);
        topGainersWidget = new QTableWidget(centralwidget);
        topGainersWidget->setObjectName("topGainersWidget");
        topGainersWidget->setGeometry(QRect(150, 140, 241, 101));
        topGainersWidget->setShowGrid(false);
        topGainersWidget->horizontalHeader()->setVisible(false);
        topGainersWidget->verticalHeader()->setVisible(false);
        topVolumeWidget = new QTableWidget(centralwidget);
        topVolumeWidget->setObjectName("topVolumeWidget");
        topVolumeWidget->setGeometry(QRect(670, 140, 241, 101));
        topVolumeWidget->setShowGrid(false);
        topVolumeWidget->horizontalHeader()->setVisible(false);
        topVolumeWidget->verticalHeader()->setVisible(false);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(160, 120, 101, 16));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(420, 120, 101, 16));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(680, 120, 101, 16));
        themeChange = new QPushButton(centralwidget);
        themeChange->setObjectName("themeChange");
        themeChange->setGeometry(QRect(870, 30, 52, 52));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/icons/dark.png"), QSize(), QIcon::Normal, QIcon::Off);
        themeChange->setIcon(icon4);
        themeChange->setIconSize(QSize(30, 30));
        themeChange->setFlat(true);
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 1001, 43));
        menuBar->setLayoutDirection(Qt::LeftToRight);
        menuBar->setDefaultUp(false);
        menuBar->setNativeMenuBar(true);
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName("menuFile");
        menuFile->setEnabled(true);
        QIcon icon5;
        iconThemeName = QString::fromUtf8("application-exit");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon5 = QIcon::fromTheme(iconThemeName);
        } else {
            icon5.addFile(QString::fromUtf8("icons/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        }
        menuFile->setIcon(icon5);
        menuLanguage = new QMenu(menuBar);
        menuLanguage->setObjectName("menuLanguage");
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuLanguage->menuAction());
        menuFile->addAction(actionExit);
        menuLanguage->addAction(actionru);
        menuLanguage->addAction(actionen);

        retranslateUi(MainWindow);
        QObject::connect(actionExit, &QAction::triggered, MainWindow, qOverload<>(&QMainWindow::close));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionExit->setText(QString());
        actionru->setText(QCoreApplication::translate("MainWindow", "ru", nullptr));
        actionen->setText(QCoreApplication::translate("MainWindow", "en", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Buy Crypto", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Market", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "More", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "info", nullptr));

        logoutButton->setText(QString());
        hoverButton->setText(QString());
        label->setText(QString());
        comboBox_2->setItemText(0, QCoreApplication::translate("MainWindow", "Overview", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("MainWindow", "Dynamics", nullptr));

        label_2->setText(QCoreApplication::translate("MainWindow", "Top Gainer Coin", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Top Loser Coin", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Top Volume Coin", nullptr));
        themeChange->setText(QString());
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        menuLanguage->setTitle(QCoreApplication::translate("MainWindow", "Language", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
