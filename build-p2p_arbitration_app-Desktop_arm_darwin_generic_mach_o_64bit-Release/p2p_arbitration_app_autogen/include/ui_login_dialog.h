/********************************************************************************
** Form generated from reading UI file 'login_dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_DIALOG_H
#define UI_LOGIN_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QLabel *label;
    QWidget *verticalLayoutWidget;
    QGridLayout *gridLayout;
    QLineEdit *usernameLineEdit;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *loginButton;
    QLineEdit *passwordLineEdit;
    QSpacerItem *horizontalSpacer_2;
    QFrame *line;
    QLineEdit *lineEdit;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName("Dialog");
        Dialog->setEnabled(true);
        Dialog->resize(400, 331);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/icons/icon_of_app_1.png"), QSize(), QIcon::Normal, QIcon::Off);
        Dialog->setWindowIcon(icon);
        label = new QLabel(Dialog);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 90, 90));
        label->setPixmap(QPixmap(QString::fromUtf8(":/icons/icons/icon_of_app_1.png")));
        label->setScaledContents(true);
        verticalLayoutWidget = new QWidget(Dialog);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(0, 130, 401, 171));
        gridLayout = new QGridLayout(verticalLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        usernameLineEdit = new QLineEdit(verticalLayoutWidget);
        usernameLineEdit->setObjectName("usernameLineEdit");
        usernameLineEdit->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(usernameLineEdit->sizePolicy().hasHeightForWidth());
        usernameLineEdit->setSizePolicy(sizePolicy);
        usernameLineEdit->setMaximumSize(QSize(200, 20));
        usernameLineEdit->setMouseTracking(true);
        usernameLineEdit->setFocusPolicy(Qt::ClickFocus);
        usernameLineEdit->setInputMethodHints(Qt::ImhHiddenText|Qt::ImhNoAutoUppercase|Qt::ImhNoPredictiveText|Qt::ImhSensitiveData);
        usernameLineEdit->setFrame(true);
        usernameLineEdit->setAlignment(Qt::AlignCenter);
        usernameLineEdit->setClearButtonEnabled(false);

        gridLayout->addWidget(usernameLineEdit, 1, 1, 1, 1);

        pushButton_2 = new QPushButton(verticalLayoutWidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setAutoDefault(false);

        gridLayout->addWidget(pushButton_2, 4, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        loginButton = new QPushButton(verticalLayoutWidget);
        loginButton->setObjectName("loginButton");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(loginButton->sizePolicy().hasHeightForWidth());
        loginButton->setSizePolicy(sizePolicy1);
        loginButton->setAutoDefault(false);

        gridLayout->addWidget(loginButton, 3, 1, 1, 1);

        passwordLineEdit = new QLineEdit(verticalLayoutWidget);
        passwordLineEdit->setObjectName("passwordLineEdit");
        passwordLineEdit->setEnabled(true);
        passwordLineEdit->setFocusPolicy(Qt::ClickFocus);
        passwordLineEdit->setStyleSheet(QString::fromUtf8(""));
        passwordLineEdit->setEchoMode(QLineEdit::Password);
        passwordLineEdit->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(passwordLineEdit, 2, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 2, 1, 1);

        line = new QFrame(Dialog);
        line->setObjectName("line");
        line->setGeometry(QRect(0, 80, 401, 16));
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);
        lineEdit = new QLineEdit(Dialog);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setEnabled(false);
        lineEdit->setGeometry(QRect(110, 100, 181, 21));
        lineEdit->setFrame(false);
        lineEdit->setAlignment(Qt::AlignCenter);
        lineEdit->setClearButtonEnabled(false);

        retranslateUi(Dialog);

        pushButton_2->setDefault(false);
        loginButton->setDefault(true);


        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        label->setText(QString());
        usernameLineEdit->setPlaceholderText(QCoreApplication::translate("Dialog", "Login", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Dialog", "sign up", nullptr));
        loginButton->setText(QCoreApplication::translate("Dialog", "log in", nullptr));
        passwordLineEdit->setPlaceholderText(QCoreApplication::translate("Dialog", "Password", nullptr));
        lineEdit->setText(QCoreApplication::translate("Dialog", "Log in or sign up to continue", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_DIALOG_H
