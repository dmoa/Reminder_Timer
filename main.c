#include <SDL2/SDL.h>
#include <stdio.h>

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t
#define s32 int32_t
typedef enum {false, true} bool;

struct Color {
    u8 r;
    u8 g;
    u8 b;
} typedef Color;

#define LENGTH 16
#define NUM_BYTES LENGTH*LENGTH*3
#define TICK 100

void SetColor(u8* pixels, Color color) {
    for (u16 i = 0; i < LENGTH*LENGTH; i ++) {
        pixels[i*3] = color.r;
        pixels[i*3 + 1] = color.g;
        pixels[i*3 + 2] = color.b;
    }
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Reminder Timer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_BORDERLESS);

    u8 pixels[NUM_BYTES];

    const Color GREY = {127, 127, 127};
    const Color GREEN = {0, 255, 0};

    SetColor(pixels, GREY);
    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormatFrom(pixels, 16, 16, 8 * 3, 16 * 3, SDL_PIXELFORMAT_RGB24);
    SDL_SetWindowIcon(window, surface);

    const u32 duration = 5000;
    s32 counter = duration;
    bool counter_finished = false;

    while (true) {

        SDL_Event event;

        while (SDL_PollEvent(& event)) {
            switch(event.type) {
                case SDL_KEYDOWN: {
                    switch (event.key.keysym.sym) {

                        case SDLK_ESCAPE:
                            goto exit;
                            break;

                        case SDLK_RETURN:
                            counter_finished = false;
                            counter = duration;
                            SetColor(pixels, GREY);
                            SDL_SetWindowIcon(window, surface);
                            break;

                        default:
                            break;
                    }
                    break;
                }
            }
        }

        if (counter < 0 && counter_finished == false) {
            counter_finished = true;
            SetColor(pixels, GREEN);
            SDL_SetWindowIcon(window, surface);
        }

        counter -= TICK;
        SDL_Delay(TICK);
    }

    exit:
        SDL_DestroyWindow(window);
        SDL_FreeSurface(surface);
        SDL_Quit();
        return 0;
}