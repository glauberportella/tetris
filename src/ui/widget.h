#ifndef _WIDGET_H_
#define _WIDGET_H_

#include <SDL.h>

#define WIDGET_ID_LEN 30
#define WIDGET_TITLE_LEN 50

typedef struct Widget {
    SDL_Color bg_color;
    SDL_Color text_color;
    SDL_Color border_color;
    SDL_Surface* surface;

    int x;
    int y;
    int width;
    int height;
    
    char* id;
    char* title;
    
    struct Widget* parent;
    struct Widget* children;
} Widget;

Widget* widget_create(
    char* title, 
    char* id, 
    int x, 
    int y, 
    int w, 
    int h,
    SDL_Color bg_color,
    SDL_Color text_color,
    SDL_Color border_color
);

Widget* widget_add_child(
    Widget* parent, 
    Widget* child
);

void widget_render(Widget* widget, SDL_Renderer* renderer);
void render_widget_tree(Widget* root, SDL_Renderer* renderer);

void widget_destroy(Widget* widget);

#endif