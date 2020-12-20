#include <SDL2/SDL.h>
#include <stdio.h>

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t

#define LENGTH 16
#define NUM_BYTES LENGTH*LENGTH*3

struct Color {
    u8 r;
    u8 g;
    u8 b;
};

inline SetColor(u8* pixels, Color color) {
    for (u16 i = 0; i < LENGTH*LENGTH; i ++) {
        SDL_Log("%i", i);
        pixels[i*3] = color.r;
        pixels[i*3 + 1] = color.g;
        pixels[i*3 + 2] = color.b;
    }
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Reminder", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_BORDERLESS);

    u8 pixels[NUM_BYTES];
    Color red = {255, 0, 0};
    SetColor(pixels, red);

    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormatFrom(pixels, 16, 16, 8 * 3, 16 * 3, SDL_PIXELFORMAT_RGB24);
    SDL_SetWindowIcon(window, surface);

    while (true) {

        SDL_Event event;

        while (SDL_PollEvent(& event)) {
            switch(event.type) {
                case SDL_KEYDOWN: {
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            goto exit;
                            break;
                        default:
                            break;
                    }
                    break;
                }
            }
        }


        SDL_Delay(100);
    }

    exit:
        SDL_DestroyWindow(window);
        SDL_FreeSurface(surface);
        SDL_Quit();
        return 0;
}