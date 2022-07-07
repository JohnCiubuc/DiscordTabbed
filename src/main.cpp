#include "src/DiscordTabbed.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    // https://stackoverflow.com/a/43373070/6622587
    std::vector<char*> new_argv(argv, argv + argc);
    qputenv("QTWEBENGINE_CHROMIUM_FLAGS", "--ignore-gpu-blacklist");
    qputenv("QTWEBENGINE_CHROMIUM_FLAGS", "--enable-accelerated-video-decode");
    qputenv("QTWEBENGINE_CHROMIUM_FLAGS", "--enable-gpu-rasterization");
    qputenv("QTWEBENGINE_CHROMIUM_FLAGS", "--num-raster-threads=4");
    qputenv("QTWEBENGINE_CHROMIUM_FLAGS", "--enable-gpu-compositing");
    new_argv.push_back(const_cast<char *>("--enable-accelerated-video-decode"));
    new_argv.push_back(const_cast<char *>("--enable-gpu-compositing"));
    new_argv.push_back(const_cast<char *>("--use-gl=desktop"));
    new_argv.push_back(const_cast<char *>("--enable-gpu"));
    new_argv.push_back(const_cast<char *>("--ignore-gpu-blacklist"));
    new_argv.push_back(const_cast<char *>("--enable-gpu-rasterization"));
    new_argv.push_back(const_cast<char *>("--enable-native-gpu-memory-buffers"));
    new_argv.push_back(const_cast<char *>("--num-raster-threads=4"));


    QSettings settings("DiscordTabbed");
    if(settings.value("smooth-scroll", true).toBool())
    {
        qputenv("QTWEBENGINE_CHROMIUM_FLAGS", "--enable-smooth-scrolling");
        new_argv.push_back(const_cast<char *>("--enable-smooth-scrolling"));
    }



    new_argv.push_back(nullptr);
    argv = new_argv.data();
    argc = argc + 1;
    QApplication::setAttribute(Qt::AA_UseOpenGLES, true);
    QApplication a(argc, argv);
    DiscordTabbed w;
    w.show();
    return a.exec();
}
