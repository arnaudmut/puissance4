#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QApplication>
#include <QPushButton>
#include<QWidget>
#include<QSlider>

class MainWindow : public QWidget
{
Q_OBJECT
public:
    MainWindow();
    MainWindow(int w, int h);
public slots:
    void tes (int l);
private :
    QPushButton *m_bouton;
    QSlider *m_slider;
};

#endif // MAINWINDOW_H
