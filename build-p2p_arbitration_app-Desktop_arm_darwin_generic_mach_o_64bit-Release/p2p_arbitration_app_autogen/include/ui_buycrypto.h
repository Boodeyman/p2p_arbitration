/********************************************************************************
** Form generated from reading UI file 'buycrypto.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUYCRYPTO_H
#define UI_BUYCRYPTO_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_buycrypto
{
public:
    QLabel *label;
    QPushButton *homeButton;

    void setupUi(QDialog *buycrypto)
    {
        if (buycrypto->objectName().isEmpty())
            buycrypto->setObjectName("buycrypto");
        buycrypto->resize(1001, 768);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(buycrypto->sizePolicy().hasHeightForWidth());
        buycrypto->setSizePolicy(sizePolicy);
        buycrypto->setMaximumSize(QSize(9999, 9999));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/icons/icon_of_app_1.png"), QSize(), QIcon::Normal, QIcon::Off);
        buycrypto->setWindowIcon(icon);
        label = new QLabel(buycrypto);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 10, 90, 90));
        label->setPixmap(QPixmap(QString::fromUtf8(":/icons/icons/icon_of_app_1.png")));
        label->setScaledContents(true);
        homeButton = new QPushButton(buycrypto);
        homeButton->setObjectName("homeButton");
        homeButton->setGeometry(QRect(10, 85, 90, 32));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        homeButton->setFont(font);
        homeButton->setAutoDefault(false);
        homeButton->setFlat(true);

        retranslateUi(buycrypto);

        homeButton->setDefault(false);


        QMetaObject::connectSlotsByName(buycrypto);
    } // setupUi

    void retranslateUi(QDialog *buycrypto)
    {
        buycrypto->setWindowTitle(QCoreApplication::translate("buycrypto", "Dialog", nullptr));
        label->setText(QString());
        homeButton->setText(QCoreApplication::translate("buycrypto", "Home", nullptr));
    } // retranslateUi

};

namespace Ui {
    class buycrypto: public Ui_buycrypto {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUYCRYPTO_H
