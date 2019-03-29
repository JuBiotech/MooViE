#include <MainWindow.h>
#include <QApplication>
#include <QIcon>

int
main (int argc, char *argv[])
{
  QApplication moovie (argc, argv);

  MainWindow window;
  window.show ();

  return moovie.exec ();
}
