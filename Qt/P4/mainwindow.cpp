#include "mainwindow.h"

MainWindow::MainWindow() : QWidget() {
    setFixedSize(150,150);
    //construction bouton
    m_bouton = new QPushButton("click",this);
    m_bouton->setFont(QFont());
    m_bouton->setCursor(Qt::PointingHandCursor);
    m_bouton->setIcon(QIcon("smile.png"));
    m_bouton->move(QPoint(40,50));
    m_slider = new QSlider(Qt::Horizontal,this);

     QObject::connect(m_bouton,SIGNAL(clicked()),qApp,SLOT(quit()));
     QObject::connect(m_slider,SIGNAL(valueChanged(int)),this,SLOT(tes(int)));

}
void MainWindow::tes(int l){
    setFixedSize(l,350);
}
MainWindow::MainWindow(int w, int h) : QWidget() {
    setFixedSize(w,h);
    //construction bouton
    m_bouton = new QPushButton("click",this);
    m_bouton->setFont(QFont());
    m_bouton->setCursor(Qt::PointingHandCursor);
    m_bouton->setIcon(QIcon("smile.png"));
    m_bouton->move(QPoint(40,50));
    QObject::connect(m_bouton,SIGNAL(clicked()),qApp,SLOT(quit()));
    m_slider = new QSlider(Qt::Horizontal,this);
    QObject::connect(m_slider,SIGNAL(valueChanged(int)),this,SLOT(tes(int)));

}



