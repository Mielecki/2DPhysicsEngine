#include "graphics.hpp"
#include <SDL2/SDL.h>
#include "particle.hpp"
#include "engine.hpp"
#include <string>
#include <sstream>
#include <SDL2/SDL_ttf.h>
#include <algorithm>

Graphics::Graphics() : mWindow(nullptr), mRenderer(nullptr), mEngine(nullptr)
{
    dt = 1.0f/SCREEN_FPS;
}

Graphics::~Graphics()
{
    cleanup();
}

// Initalize SDL, window, renderer and physics engine
bool Graphics::init()
{
    // Initialize SDL video
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL initaliaztion error: %s\n", SDL_GetError());
        return false;
    }

    // Initalize SDL_ttf
    if (TTF_Init() == -1)
    {
        printf("SDL_ttf initaliaztion error: %s\n", TTF_GetError());
        return false;
    }

    // Create window
    mWindow = SDL_CreateWindow("2DPhysicsEngine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (mWindow == nullptr)
    {
        printf("SDL creating window error: %s\n", SDL_GetError());
        return false;
    }

    // Create renderer for window that uses hardware acceleration and vsync
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (mRenderer == nullptr)
    {
        printf("SDL creating renderer error: %s\n", SDL_GetError());
        return false;
    }

    mEngine = new Engine(SCREEN_WIDTH, SCREEN_HEIGHT);
    return true;
}

// Close SDL2
void Graphics::cleanup()
{
    if (mEngine != nullptr)
    {
        delete mEngine;
        mEngine = nullptr;
    }

    for (Texture* texture : mTextTextures) {
        delete texture;
    }

    mTextTextures.clear();

    TTF_CloseFont(mFont);
    mFont = nullptr;

    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    mRenderer = nullptr;
    mWindow = nullptr;

    SDL_Quit();
    TTF_Quit();
}

bool Graphics::loadMedia()
{
    mFont = TTF_OpenFont("src/assets/RobotoMono-VariableFont_wght.ttf", TEXT_SIZE);
    if (mFont == nullptr)
    {
        printf("SDL_ttf opening font error: %s\n", TTF_GetError());
        return false;
    }

    return true;
}


void Graphics::updateFPS(int &frameCounter, Timer& fpsTimer, Texture* fpsText)
{
    frameCounter++;
    Uint32 updateTime = fpsTimer.getTicks();
    if (updateTime >= FPS_UPDATE_INTERVAL)
    {
        float fps = frameCounter / (updateTime / 1000.0f);
        frameCounter = 0;

        fpsTimer.start();

        updateTextTexture(fpsText, "FPS: " + std::to_string(fps).substr(0, 5));
    }
}


void Graphics::drawParticles()
{
    for (Particle& particle : mEngine->getParticles())
    {   
        Vector2D velocityVector = particle.getVelocity(dt);
        float velocity = std::min(sqrt(velocityVector.x * velocityVector.x + velocityVector.y + velocityVector.y), MAX_DRAW_VELOCITY);
        Uint8 normVel = velocity / MAX_DRAW_VELOCITY * 255;
        SDL_Color color = {normVel, 0x00, 0xFF - normVel, 0xFF};
        particle.setColor(color);
        particle.draw(mRenderer);
    }
}

void Graphics::handleEvents(SDL_Event& e, bool& running, SDL_Point &mousePosition, int &particlesCount)
{
    while (SDL_PollEvent(&e) != 0)
    {
        switch(e.type)
        {
        case SDL_QUIT: // Prevent from closing immediately
            running = false;
            break;
        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
            break;
        case SDL_MOUSEBUTTONDOWN:
            particlesCount++;
            mEngine->addParticle(mousePosition.x, mousePosition.y, mParticleRadius);
            break;
        case SDL_KEYDOWN:
            switch (e.key.keysym.sym)
            {
            case SDLK_UP:
                if (mParticleRadius < 40) mParticleRadius += 1;
                break;
            case SDLK_DOWN:
                if (mParticleRadius > 5) mParticleRadius -= 1;
                break;
            }
            break;
        }


        if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
        {
            mEngine->changeContainerSize(e.window.data1, e.window.data2);
        }
    }
}

Texture* Graphics::createTextTexture(std::string initText)
{
    Texture* newTexture = new Texture(mRenderer, mFont);
    mTextTextures.push_back(newTexture);
    if (!newTexture->loadFromRenderedText(initText, TEXT_COLOR))
    {
        printf("Failed to render text.\n");
    }

    return newTexture;
}

void Graphics::updateTextTexture(Texture* texture, std::string text)
{
    if (!texture->loadFromRenderedText(text, TEXT_COLOR))
    {
        printf("Failed to render text.\n");
    }
}

void Graphics::renderTextTextures()
{
    int offset = 0;
    for(Texture* texture : mTextTextures)
    {
        texture->render(0, offset);
        offset += TEXT_SIZE;
    }
}

void Graphics::run()
{
    // Flag that indicates whether the engine is running
    bool running = true;

    // Event handler (necessary to prevent the window from closing immediately)
    SDL_Event e;
    
    // Timer necessary for capping the frame rate
    Timer capTimer;

    SDL_Point mousePosition = {0, 0};
 
    int particlesCount = 0;
    Texture* particlesCountText = createTextTexture("Particles: 0");

    Uint64 currentFrame = 0;
    int frameCounter = 0;
    Timer fpsTimer;
    Texture* fpsText = createTextTexture("FPS: 0");
    fpsTimer.start();

    Texture* particleSizeText = createTextTexture("Particle size: " + std::to_string(mParticleRadius));
    
    while (running)
    {   
        capTimer.start();
        handleEvents(e, running, mousePosition, particlesCount);

        updateTextTexture(particlesCountText, "Particles: " + std::to_string(particlesCount));
        updateTextTexture(particleSizeText, "Particle size: " + std::to_string(mParticleRadius));

        SDL_SetRenderDrawColor(mRenderer, 0x80, 0x80, 0x80, 0xFF);
        SDL_RenderClear(mRenderer);

        mEngine->update(dt);

        drawParticles();

        updateFPS(frameCounter, fpsTimer, fpsText);

        renderTextTextures();

        SDL_RenderPresent(mRenderer);

        // cap the frame rate
        int frameTicks = capTimer.getTicks();
        if (frameTicks < 1000 / SCREEN_FPS)
        {
            SDL_Delay(1000/SCREEN_FPS - frameTicks);
        }

        currentFrame++;
    }
}