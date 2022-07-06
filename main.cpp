#include "src/DiscordTabbed.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    // https://stackoverflow.com/a/43373070/6622587
    std::vector<char*> new_argv(argv, argv + argc);
    new_argv.push_back(const_cast<char *>("--enable-smooth-scrolling"));
    new_argv.push_back(nullptr);
    argv = new_argv.data();
    argc = argc + 1;
    QApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);
    QApplication a(argc, argv);
    DiscordTabbed w;
    w.show();
    return a.exec();
}
