/********************************************************************************
** Form generated from reading UI file 'lessonwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LESSONWINDOW_H
#define UI_LESSONWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_lessonWindow
{
public:
    QAction *actionOpen_File;
    QAction *actionSave_File;
    QAction *actionLesson_Editor;
    QAction *actionStudent_View;
    QWidget *centralWidget;
    QTextEdit *textEdit;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuView;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *lessonWindow)
    {
        if (lessonWindow->objectName().isEmpty())
            lessonWindow->setObjectName(QStringLiteral("lessonWindow"));
        lessonWindow->resize(400, 300);
        actionOpen_File = new QAction(lessonWindow);
        actionOpen_File->setObjectName(QStringLiteral("actionOpen_File"));
        actionSave_File = new QAction(lessonWindow);
        actionSave_File->setObjectName(QStringLiteral("actionSave_File"));
        actionLesson_Editor = new QAction(lessonWindow);
        actionLesson_Editor->setObjectName(QStringLiteral("actionLesson_Editor"));
        actionStudent_View = new QAction(lessonWindow);
        actionStudent_View->setObjectName(QStringLiteral("actionStudent_View"));
        centralWidget = new QWidget(lessonWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(70, 130, 104, 71));
        lessonWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(lessonWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QStringLiteral("menuView"));
        lessonWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(lessonWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        lessonWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(lessonWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        lessonWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuFile->addAction(actionOpen_File);
        menuFile->addAction(actionSave_File);
        menuView->addAction(actionLesson_Editor);
        menuView->addAction(actionStudent_View);

        retranslateUi(lessonWindow);

        QMetaObject::connectSlotsByName(lessonWindow);
    } // setupUi

    void retranslateUi(QMainWindow *lessonWindow)
    {
        lessonWindow->setWindowTitle(QApplication::translate("lessonWindow", "lessonWindow", 0));
        actionOpen_File->setText(QApplication::translate("lessonWindow", "Open File", 0));
        actionSave_File->setText(QApplication::translate("lessonWindow", "Save File", 0));
        actionLesson_Editor->setText(QApplication::translate("lessonWindow", "Lesson Editor", 0));
        actionStudent_View->setText(QApplication::translate("lessonWindow", "Student View", 0));
        menuFile->setTitle(QApplication::translate("lessonWindow", "File", 0));
        menuView->setTitle(QApplication::translate("lessonWindow", "View", 0));
    } // retranslateUi

};

namespace Ui {
    class lessonWindow: public Ui_lessonWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LESSONWINDOW_H
