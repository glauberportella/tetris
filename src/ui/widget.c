#include "widget.h"

Widget* widget_create(
    char* id, 
    char* title,
    int x, 
    int y, 
    int w, 
    int h,
    SDL_Color bg_color,
    SDL_Color font_color,
    SDL_Color border_color
) {
    Widget* widget = (Widget*)malloc(sizeof(Widget));
    widget->children = NULL;
    widget->parent = NULL;
    widget->surface = SDL_CreateRGBSurface(0, w, h, 0, bg_color.r, bg_color.g, bg_color.b, bg_color.a);
    widget->id = id;
    widget->title = title;
    widget->x = x;
    widget->y = y;
    widget->width = w;
    widget->height = h;
    return widget;
}

void widget_destroy(Widget* widget) {
    if (widget == NULL) {
        return;
    }

    // Primeiro, liberamos recursivamente os widgets filhos
    Widget* child = widget->children;
    while (child != NULL) {
        Widget* next_child = child->parent;
        widget_destroy(child);
        child = next_child;
    }

    // Agora, liberamos a memória do widget atual
    SDL_FreeSurface(widget->surface);
    widget->surface = NULL;

    // Finalmente, liberamos o widget atual
    free(widget);
}

Widget* widget_add_child(
    Widget* parent, 
    Widget* child
) {
    child->parent = parent;
    child->children = NULL;
    Widget* next_child = parent->children;
    while (next_child != NULL) {
        next_child = next_child->children;
    }
    next_child->children = child;
    return child;
}

void render_widget(Widget* widget, SDL_Renderer* renderer) {
    if (widget == NULL || renderer == NULL) {
        return;
    }

    // Desenha no surface do widget atual
    if (widget->surface != NULL) {
        // Cria um renderer temporário para desenhar na surface do widget
        SDL_Renderer* tempRenderer = SDL_CreateSoftwareRenderer(widget->surface);
        if (tempRenderer != NULL) {
            // Desenha algo na surface do widget aqui, por exemplo:
            SDL_SetRenderDrawColor(tempRenderer, widget->bg_color.r, widget->bg_color.g, widget->bg_color.b, SDL_ALPHA_OPAQUE);
            SDL_RenderClear(tempRenderer);
            // Aqui você pode adicionar desenhos adicionais conforme necessário
            SDL_DestroyRenderer(tempRenderer);
        }
    }

    // Renderiza recursivamente os widgets filhos
    Widget* child = widget->children;
    while (child != NULL) {
        render_widget(child, renderer);
        child = child->parent; // Avança para o próximo filho
    }

    // Blit a surface do widget atual no renderer principal
    if (widget->surface != NULL) {
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, widget->surface);
        if (texture != NULL) {
            SDL_Rect dstRect = {widget->x, widget->y, widget->width, widget->height};
            SDL_RenderCopy(renderer, texture, NULL, &dstRect);
            SDL_DestroyTexture(texture);
        }
    }
}

// Função para renderizar todos os widgets da árvore, começando pelo widget raiz
void render_widget_tree(Widget* root, SDL_Renderer* renderer) {
    // Limpa o renderer antes de renderizar todos os widgets
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    
    render_widget(root, renderer);
    SDL_RenderPresent(renderer); // Para atualizar a tela depois de renderizar todos os widgets
}