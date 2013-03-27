/********************************************************************************
** Form generated from reading UI file 'ergocam.ui'
**
** Created by: Qt User Interface Compiler version 5.0.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ERGOCAM_H
#define UI_ERGOCAM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ErgoCamClass
{
public:
    QAction *save_directory_action;
    QAction *select_camera_action;
    QWidget *centralWidget;
    QLabel *preview_label;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *track_icon_label;
    QLabel *track_text_label;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *tired_button;
    QSlider *tired_slider;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *focus_button;
    QSlider *focus_slider;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *stress_button;
    QSlider *stress_slider;
    QLabel *status_label;
    QCheckBox *model_checkbox;
    QCheckBox *landmark_checkbox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_5;
    QLabel *pitch_static_label;
    QLabel *pitch_label;
    QHBoxLayout *horizontalLayout_6;
    QLabel *roll_static_label;
    QLabel *roll_label;
    QHBoxLayout *horizontalLayout_7;
    QLabel *yaw_static_label;
    QLabel *yaw_label;
    QHBoxLayout *horizontalLayout_8;
    QLabel *distance_static_label;
    QLabel *distance_label;
    QHBoxLayout *horizontalLayout_9;
    QLabel *blink_static_label;
    QLabel *blink_label;
    QHBoxLayout *horizontalLayout_10;
    QLabel *yawn_static_label;
    QLabel *yawn_label;
    QMenuBar *menuBar;
    QMenu *menu_File;
    QMenu *menu_Camera;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ErgoCamClass)
    {
        if (ErgoCamClass->objectName().isEmpty())
            ErgoCamClass->setObjectName(QStringLiteral("ErgoCamClass"));
        ErgoCamClass->resize(851, 545);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ErgoCamClass->sizePolicy().hasHeightForWidth());
        ErgoCamClass->setSizePolicy(sizePolicy);
        save_directory_action = new QAction(ErgoCamClass);
        save_directory_action->setObjectName(QStringLiteral("save_directory_action"));
        select_camera_action = new QAction(ErgoCamClass);
        select_camera_action->setObjectName(QStringLiteral("select_camera_action"));
        centralWidget = new QWidget(ErgoCamClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        preview_label = new QLabel(centralWidget);
        preview_label->setObjectName(QStringLiteral("preview_label"));
        preview_label->setGeometry(QRect(10, 10, 640, 480));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(670, 21, 169, 389));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        track_icon_label = new QLabel(layoutWidget);
        track_icon_label->setObjectName(QStringLiteral("track_icon_label"));
        track_icon_label->setPixmap(QPixmap(QString::fromUtf8(":/ErgoCam/Resources/red.png")));

        horizontalLayout->addWidget(track_icon_label);

        track_text_label = new QLabel(layoutWidget);
        track_text_label->setObjectName(QStringLiteral("track_text_label"));
        QFont font;
        font.setPointSize(10);
        track_text_label->setFont(font);

        horizontalLayout->addWidget(track_text_label);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        tired_button = new QPushButton(layoutWidget);
        tired_button->setObjectName(QStringLiteral("tired_button"));
        QFont font1;
        font1.setFamily(QStringLiteral("Comic Sans MS"));
        font1.setPointSize(14);
        tired_button->setFont(font1);

        horizontalLayout_2->addWidget(tired_button);

        tired_slider = new QSlider(layoutWidget);
        tired_slider->setObjectName(QStringLiteral("tired_slider"));
        tired_slider->setMinimum(1);
        tired_slider->setMaximum(3);
        tired_slider->setPageStep(1);
        tired_slider->setValue(3);
        tired_slider->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(tired_slider);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        focus_button = new QPushButton(layoutWidget);
        focus_button->setObjectName(QStringLiteral("focus_button"));
        focus_button->setFont(font1);

        horizontalLayout_3->addWidget(focus_button);

        focus_slider = new QSlider(layoutWidget);
        focus_slider->setObjectName(QStringLiteral("focus_slider"));
        focus_slider->setMinimum(1);
        focus_slider->setMaximum(3);
        focus_slider->setPageStep(1);
        focus_slider->setValue(3);
        focus_slider->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(focus_slider);


        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        stress_button = new QPushButton(layoutWidget);
        stress_button->setObjectName(QStringLiteral("stress_button"));
        stress_button->setFont(font1);

        horizontalLayout_4->addWidget(stress_button);

        stress_slider = new QSlider(layoutWidget);
        stress_slider->setObjectName(QStringLiteral("stress_slider"));
        stress_slider->setMinimum(1);
        stress_slider->setMaximum(3);
        stress_slider->setPageStep(1);
        stress_slider->setValue(3);
        stress_slider->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(stress_slider);


        gridLayout->addLayout(horizontalLayout_4, 3, 0, 1, 1);

        status_label = new QLabel(layoutWidget);
        status_label->setObjectName(QStringLiteral("status_label"));
        QFont font2;
        font2.setPointSize(14);
        status_label->setFont(font2);

        gridLayout->addWidget(status_label, 4, 0, 1, 1);

        model_checkbox = new QCheckBox(layoutWidget);
        model_checkbox->setObjectName(QStringLiteral("model_checkbox"));
        model_checkbox->setFont(font);
        model_checkbox->setChecked(true);

        gridLayout->addWidget(model_checkbox, 5, 0, 1, 1);

        landmark_checkbox = new QCheckBox(layoutWidget);
        landmark_checkbox->setObjectName(QStringLiteral("landmark_checkbox"));
        landmark_checkbox->setFont(font);

        gridLayout->addWidget(landmark_checkbox, 6, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        pitch_static_label = new QLabel(layoutWidget);
        pitch_static_label->setObjectName(QStringLiteral("pitch_static_label"));
        pitch_static_label->setFont(font);

        horizontalLayout_5->addWidget(pitch_static_label);

        pitch_label = new QLabel(layoutWidget);
        pitch_label->setObjectName(QStringLiteral("pitch_label"));
        pitch_label->setFont(font);
        pitch_label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(pitch_label);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        roll_static_label = new QLabel(layoutWidget);
        roll_static_label->setObjectName(QStringLiteral("roll_static_label"));
        roll_static_label->setFont(font);

        horizontalLayout_6->addWidget(roll_static_label);

        roll_label = new QLabel(layoutWidget);
        roll_label->setObjectName(QStringLiteral("roll_label"));
        roll_label->setFont(font);
        roll_label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_6->addWidget(roll_label);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        yaw_static_label = new QLabel(layoutWidget);
        yaw_static_label->setObjectName(QStringLiteral("yaw_static_label"));
        yaw_static_label->setFont(font);

        horizontalLayout_7->addWidget(yaw_static_label);

        yaw_label = new QLabel(layoutWidget);
        yaw_label->setObjectName(QStringLiteral("yaw_label"));
        yaw_label->setFont(font);
        yaw_label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_7->addWidget(yaw_label);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        distance_static_label = new QLabel(layoutWidget);
        distance_static_label->setObjectName(QStringLiteral("distance_static_label"));
        distance_static_label->setFont(font);

        horizontalLayout_8->addWidget(distance_static_label);

        distance_label = new QLabel(layoutWidget);
        distance_label->setObjectName(QStringLiteral("distance_label"));
        distance_label->setFont(font);
        distance_label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_8->addWidget(distance_label);


        verticalLayout->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        blink_static_label = new QLabel(layoutWidget);
        blink_static_label->setObjectName(QStringLiteral("blink_static_label"));
        blink_static_label->setFont(font);

        horizontalLayout_9->addWidget(blink_static_label);

        blink_label = new QLabel(layoutWidget);
        blink_label->setObjectName(QStringLiteral("blink_label"));
        blink_label->setFont(font);
        blink_label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_9->addWidget(blink_label);


        verticalLayout->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        yawn_static_label = new QLabel(layoutWidget);
        yawn_static_label->setObjectName(QStringLiteral("yawn_static_label"));
        yawn_static_label->setFont(font);

        horizontalLayout_10->addWidget(yawn_static_label);

        yawn_label = new QLabel(layoutWidget);
        yawn_label->setObjectName(QStringLiteral("yawn_label"));
        yawn_label->setFont(font);
        yawn_label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_10->addWidget(yawn_label);


        verticalLayout->addLayout(horizontalLayout_10);


        gridLayout->addLayout(verticalLayout, 7, 0, 1, 1);

        ErgoCamClass->setCentralWidget(centralWidget);
        layoutWidget->raise();
        preview_label->raise();
        menuBar = new QMenuBar(ErgoCamClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 851, 21));
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QStringLiteral("menu_File"));
        menu_Camera = new QMenu(menuBar);
        menu_Camera->setObjectName(QStringLiteral("menu_Camera"));
        ErgoCamClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(ErgoCamClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ErgoCamClass->setStatusBar(statusBar);

        menuBar->addAction(menu_File->menuAction());
        menuBar->addAction(menu_Camera->menuAction());
        menu_File->addAction(save_directory_action);
        menu_Camera->addAction(select_camera_action);

        retranslateUi(ErgoCamClass);

        QMetaObject::connectSlotsByName(ErgoCamClass);
    } // setupUi

    void retranslateUi(QMainWindow *ErgoCamClass)
    {
        ErgoCamClass->setWindowTitle(QApplication::translate("ErgoCamClass", "ErgoCam", 0));
        save_directory_action->setText(QApplication::translate("ErgoCamClass", "Save Directory", 0));
        select_camera_action->setText(QApplication::translate("ErgoCamClass", "Select Camera", 0));
        preview_label->setText(QString());
        track_icon_label->setText(QString());
        track_text_label->setText(QApplication::translate("ErgoCamClass", "Not Tracking", 0));
        tired_button->setText(QApplication::translate("ErgoCamClass", "Tired", 0));
        focus_button->setText(QApplication::translate("ErgoCamClass", "Focus", 0));
        stress_button->setText(QApplication::translate("ErgoCamClass", "Stress", 0));
        status_label->setText(QString());
        model_checkbox->setText(QApplication::translate("ErgoCamClass", "Show Face Model", 0));
        landmark_checkbox->setText(QApplication::translate("ErgoCamClass", "Show Landmarks", 0));
        pitch_static_label->setText(QApplication::translate("ErgoCamClass", "Pitch:", 0));
        pitch_label->setText(QString());
        roll_static_label->setText(QApplication::translate("ErgoCamClass", "Roll:", 0));
        roll_label->setText(QString());
        yaw_static_label->setText(QApplication::translate("ErgoCamClass", "Yaw:", 0));
        yaw_label->setText(QString());
        distance_static_label->setText(QApplication::translate("ErgoCamClass", "Distance:", 0));
        distance_label->setText(QString());
        blink_static_label->setText(QApplication::translate("ErgoCamClass", "Blink Count:", 0));
        blink_label->setText(QString());
        yawn_static_label->setText(QApplication::translate("ErgoCamClass", "Yawn Count:", 0));
        yawn_label->setText(QString());
        menu_File->setTitle(QApplication::translate("ErgoCamClass", "&File", 0));
        menu_Camera->setTitle(QApplication::translate("ErgoCamClass", "&Camera", 0));
    } // retranslateUi

};

namespace Ui {
    class ErgoCamClass: public Ui_ErgoCamClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ERGOCAM_H
