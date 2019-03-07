#include <MainWindow.h>
#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication moovie(argc, argv);
    MainWindow window;
    window.setWindowIcon(QIcon("/usr/share/pixmaps/moovie.png"));
    window.setWindowTitle("MooViE - Desktop");
    window.show();

    return moovie.exec();
}
