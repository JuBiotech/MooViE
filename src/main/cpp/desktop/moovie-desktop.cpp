#include "MainWindow.h"
#include <QApplication>
#include <QIcon>

void
messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    std::string file(context.file ? context.file : ""),
            function(context.function ? context.function : "");
    switch (type) {
        case QtDebugMsg:
        case QtInfoMsg:
        case QtWarningMsg:
            break;
        case QtCriticalMsg:
        case QtFatalMsg:
            std::cout << "Error: " << msg.toStdString() << " (" << file << ":" << context.line << ", " << function
                      << ")" << std::endl;
            break;
    }
}

int
main(int argc, char *argv[])
{
    qInstallMessageHandler(messageHandler);
  QApplication moovie(argc, argv);

  MainWindow window;
  window.show();

  return moovie.exec();
}
