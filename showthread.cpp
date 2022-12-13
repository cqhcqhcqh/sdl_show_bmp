#include "showthread.h"
#include <QDebug>
extern "C" {
#include <SDL2/SDL.h>
}
#include <QFile>
#ifdef Q_OS_MAC
#define FILENAME "/Users/caitou/Desktop/in.bmp"
#elif Q_OS_Win32
#define FILENAME "C:/Workspaces/in.yuv"
#else
#define FILENAME "/Users/caitou/Desktop/in.bmp"
#endif
#define YUV_VIDEO_SIZE_WIDTH 640
#define YUV_VIDEO_SIZE_HEIGHT 480

#define GOTOEND(res, METHODNAME) \
        if (res) { \
            qDebug() << #METHODNAME << "error" << SDL_GetError();\
            goto end; \
        }
ShowThread::ShowThread(QObject *parent)
    : QThread{parent}
{
    connect(this, &ShowThread::finished, this, &ShowThread::deleteLater);
}

ShowThread::~ShowThread() {
    disconnect();
    requestInterruption();
    quit();
    wait();

    qDebug() << this << "has been destoryed";
}

void ShowThread::run() {
    ShowThread::showYuv();
}

void ShowThread::showYuv() {
    SDL_Renderer *ctx = nullptr;
    SDL_Window *window = nullptr;
    SDL_Texture *tex = nullptr;
    SDL_Surface *surface = nullptr;

    GOTOEND(SDL_Init(SDL_INIT_VIDEO), SDL_Init);

    surface = SDL_LoadBMP(FILENAME);
    GOTOEND(!surface, SDL_LoadBMP);
    qDebug() << "surface w" << surface->w << "surface h" << surface->h;
    window = SDL_CreateWindow("window's title",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              surface->w,
                              surface->h,
                              SDL_WINDOW_SHOWN);

    GOTOEND(!window, SDL_CreateWindow);

    ctx = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    GOTOEND(!ctx, SDL_CreateRenderer1);

    if (ctx == nullptr) {
        ctx = SDL_CreateRenderer(window, -1, 0);
    }

    GOTOEND(!ctx, SDL_CreateRenderer2);

    tex = SDL_CreateTextureFromSurface(ctx, surface);
    GOTOEND(!tex, SDL_CreateTextureFromSurface);

//    GOTOEND(SDL_SetRenderDrawColor(ctx, 255, 255, 0, 255), SDL_SetRenderDrawColor);

//    GOTOEND(SDL_RenderClear(ctx), SDL_RenderClear);

    GOTOEND(SDL_RenderCopy(ctx, tex, NULL, NULL), SDL_RenderCopy);
    SDL_RenderPresent(ctx);

while (true) {
    SDL_Event event;
    SDL_WaitEvent(&event);
}
end:
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ctx);
    SDL_DestroyWindow(window);
    SDL_FreeSurface(surface);
    SDL_Quit();
}
