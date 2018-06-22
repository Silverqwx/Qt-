/********************************************************************************
** Form generated from reading UI file 'myQt.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYQT_H
#define UI_MYQT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_myQtClass
{
public:
    QWidget *centralWidget;
    QPushButton *Button_ok;
    QPushButton *load_image;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *myQtClass)
    {
        if (myQtClass->objectName().isEmpty())
            myQtClass->setObjectName(QStringLiteral("myQtClass"));
        myQtClass->resize(965, 645);
        centralWidget = new QWidget(myQtClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Button_ok = new QPushButton(centralWidget);
        Button_ok->setObjectName(QStringLiteral("Button_ok"));
        Button_ok->setGeometry(QRect(710, 120, 75, 23));
        load_image = new QPushButton(centralWidget);
        load_image->setObjectName(QStringLiteral("load_image"));
        load_image->setGeometry(QRect(710, 180, 75, 23));
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(89, 69, 451, 361));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        myQtClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(myQtClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 965, 23));
        myQtClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(myQtClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        myQtClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(myQtClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        myQtClass->setStatusBar(statusBar);

        retranslateUi(myQtClass);
        QObject::connect(Button_ok, SIGNAL(clicked()), myQtClass, SLOT(Button_ok_clicked()));
        QObject::connect(load_image, SIGNAL(clicked()), myQtClass, SLOT(load_image_Event()));

        QMetaObject::connectSlotsByName(myQtClass);
    } // setupUi

    void retranslateUi(QMainWindow *myQtClass)
    {
        myQtClass->setWindowTitle(QApplication::translate("myQtClass", "myQt", Q_NULLPTR));
        Button_ok->setText(QApplication::translate("myQtClass", "ok", Q_NULLPTR));
        load_image->setText(QApplication::translate("myQtClass", "\345\212\240\350\275\275\345\233\276\347\211\207", Q_NULLPTR));
        label->setText(QApplication::translate("myQtClass", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class myQtClass: public Ui_myQtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYQT_H
