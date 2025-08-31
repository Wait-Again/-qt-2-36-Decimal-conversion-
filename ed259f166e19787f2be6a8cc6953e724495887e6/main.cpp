#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("进制转换器");
    MainWindow w;
    w.show();
    return app.exec();
}
