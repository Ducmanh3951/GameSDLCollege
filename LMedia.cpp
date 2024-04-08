#include "LMedia.h"

#include"LTexture.h"

string path;
bool init(SDL_Window* &gWindow, SDL_Renderer* &gRenderer, const char* WINDOW_TITLE)
{
    bool success = true;
    // Initialize SDL and SDL_mixer
    if(SDL_Init(SDL_INIT_VIDEO || SDL_INIT_AUDIO) < 0)
    {
        cout << "Could not initialize SDL and SDL_mixer! SDL Error: " << SDL_GetError() << endl;
        success = false;
    }
    else
    {
        // Create window
        gWindow = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(gWindow == NULL)
        {
            cout << "Could not create window! SDL Error: " << SDL_GetError() << endl;
            success = false;
        }
        else
        {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if(gRenderer == NULL)
            {
                cout << "Could not create renderer! SDL Error:" << SDL_GetError() << endl;
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor(gRenderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);

                // Initialize SDL_image
                int imgFlags = IMG_INIT_PNG;
                if(!(IMG_Init(imgFlags) && imgFlags))
                {
                    cout << "Could not initialize SDL_image! SDL_image Error: " << IMG_GetError() << endl;
                    success = false;
                }

                //Initialize SDL_mixer
                // Mix_OpenAudio(sound frequency, the sample format, number of hardware channels, size of chunk sound)
                if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = false;
                }

                //Initialize SDL_ttf
                if( TTF_Init() == -1 )
                {
                    cout << "SDL_ttf could not initialize! SDL_ttf Error:" << TTF_GetError() << endl;
                    success = false;
                }

            }
        }
    }
    return success;
}

bool loadMedia(LTexture &gPlayer1_jump, LTexture &gPlayer2_jump, LTexture &gPlayer3_jump, LTexture &gPlayer_death_1, LTexture &gPlayer_death_2, LTexture &gPlayer_death_3,
               LTexture &gPlayer_background, LTexture &oObstacle1, LTexture &oObstacle2,
               LTexture &gPause, LTexture &gResume, LTexture &gScore, LTexture &game_over,LTexture &replay, LTexture &exit_game, LTexture &gHighscore, LTexture &introduction,
               Mix_Music *&gMusic_in_menu, Mix_Music *&gMusic_when_playing, Mix_Chunk *&gjump, Mix_Chunk *&gdeath, TTF_Font *&gFont,
               SDL_Renderer* &gRenderer,
               LTexture &gPlayer1_ground, SDL_Rect &player1_rect, int &frame1_width,
               LTexture &gPlayer2_ground, SDL_Rect &player2_rect, int &frame2_width,
               LTexture &gPlayer3_ground, SDL_Rect &player3_rect, int &frame3_width,
               LTexture &gArrow_left, LTexture &gArrow_right, LTexture &gArcher_left, LTexture &gArcher_right,
               LTexture &menu, LTexture &select, LTexture &select1, LTexture &select2, LTexture &select3)
{
    bool success = true;
    //Load character Run animation
    if(!gPlayer1_ground.load_media_from_file("img\\Character_1_Run.png", gRenderer))
    {
        cout << "Could not load character animation" << endl;
        success = false;
    }
    else
    {
        frame1_width = gPlayer1_ground.getWidth()/8;
        player1_rect.w = frame1_width;
        player1_rect.h = gPlayer1_ground.getHeight();
        player1_rect.x = 0;
        player1_rect.y = 0;
    }

    if(!gPlayer2_ground.load_media_from_file("img\\Character_2_Run.png", gRenderer))
    {
        cout << "Could not load character animation" << endl;
        success = false;
    }
    else
    {
        frame2_width = gPlayer2_ground.getWidth()/8;
        player2_rect.w = frame2_width;
        player2_rect.h = gPlayer2_ground.getHeight();
        player2_rect.x = 0;
        player2_rect.y = 0;
    }

    if(!gPlayer3_ground.load_media_from_file("img\\Character_3_Run.png", gRenderer))
    {
        cout << "Could not load character animation" << endl;
        success = false;
    }
    else
    {
        frame3_width = gPlayer3_ground.getWidth()/6;
        player3_rect.w = frame3_width;
        player3_rect.h = gPlayer3_ground.getHeight();
        player3_rect.x = 0;
        player3_rect.y = 0;
    }
    // Load character Jump
    if(!gPlayer1_jump.load_media_from_file("img\\Character_1_Jump.png", gRenderer))
    {
        cout << "Could not load character 1 when jump" << endl;
        success = false;
    }

    if(!gPlayer2_jump.load_media_from_file("img\\Character_2_Jump.png", gRenderer))
    {
        cout << "Could not load character 2 when jump" << endl;
        success = false;
    }

    if(!gPlayer3_jump.load_media_from_file("img\\Character_3_Jump.png", gRenderer))
    {
        cout << "Could not load character 3 when jump" << endl;
        success = false;
    }
    // Load character die
    if(!gPlayer1_death.load_media_from_file("img\\character_death.png", gRenderer))
    {
        cout << "Could not load character when die";
        success = false;
    }
    if(!gPlayer2_death.load_media_from_file("img\\character_death.png", gRenderer))
    {
        cout << "Could not load character when die";
        success = false;
    }
    if(!gPlayer3_death.load_media_from_file("img\\character_death.png", gRenderer))
    {
        cout << "Could not load character when die";
        success = false;
    }
    // Load background
    if(!gPlayer_background.load_media_from_file("img\\pixel-waterfall-thumb.jpg", gRenderer))
    {
        cout << "Could not load Dino background" << endl;
        success = false;
    }

    // Load obstacle_1
    if(!oObstacle1.load_media_from_file("img\\bush2.png", gRenderer))
    {
        cout << "Could not load obstacle 1" << endl;
        success = false;
    }

    // Load obstacle_2
    if(!oObstacle2.load_media_from_file("img\\rock3.png", gRenderer))
    {
        cout << "Could not load obstacle 2" << endl;
        success = false;
    }
    // Load arrow_left
    if(!gArrow_left.load_media_from_file("img\\Arrow_Left.png", gRenderer))
    {
        cout << "Could not load Arrow left" << endl;
        success = false;
    }
    // Load rocket 2
    if(!gArrow_right.load_media_from_file("img\\Arrow_Right.png", gRenderer))
    {
        cout << "Could not load Arrow right" << endl;
        success = false;
    }

    // Load Warning signal
    if(!gArcher_left.load_media_from_file("img\\Samurai_Left.png", gRenderer))
    {
        cout << "Could not load Archer!" << endl;
        success = false;
    }
    if(!gArcher_right.load_media_from_file("img\\Samurai_Right.png", gRenderer))
    {
        cout << "Could not load Archer!" << endl;
        success = false;
    }
    // Load main menu png
    if(!menu.load_media_from_file("img\\Mainmenu.png", gRenderer))
    {
        cout << "Could not load Main menu png" << endl;
        success = false;
    }
    // Load select menu png
    if(!select.load_media_from_file("img\\Select_player.png", gRenderer))
    {
        cout << "Could not load How to play png" << endl;
        success = false;
    }
    // Load select character 1 png
    if(!select1.load_media_from_file("img\\Select_1.png", gRenderer))
    {
        cout << "Could not load How to play png" << endl;
        success = false;
    }
    // Load select character 2 png
    if(!select2.load_media_from_file("img\\Select_2.png", gRenderer))
    {
        cout << "Could not load How to play png" << endl;
        success = false;
    }
    // Load select character 3 png
    if(!select3.load_media_from_file("img\\Select_3.png", gRenderer))
    {
        cout << "Could not load How to play png" << endl;
        success = false;
    }
    // Load how to play png
    if(!introduction.load_media_from_file("img\\How_to_play.png", gRenderer))
    {
        cout << "Could not load How to play png" << endl;
        success = false;
    }

    // Load pause image
    if(!gPause.load_media_from_file("img\\pause.png", gRenderer))
    {
        cout << "Could not load pause img" << endl;
        success = false;
    }

    // Load resume image
    if(!gResume.load_media_from_file("img\\resume.png", gRenderer))
    {
        cout << "Could not load resume img" << endl;
        success = false;
    }

    // Load game over image
    if(!game_over.load_media_from_file("img\\Game_over3.png", gRenderer))
    {
        cout << "Could not load resume img" << endl;
        success = false;
    }

    // Open the font
    gFont = TTF_OpenFont("FzTokugawa.ttf", 15);
    if(gFont == NULL)
    {
        cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << endl;
        success = false;
    }
    else
    {
        SDL_Color textColor = {0, 0, 0, 255}; // black
        // Load current score
        if(!gScore.load_from_rendered_text("Score:", textColor, gRenderer, gFont))
        {
            cout << "Unable to render score texture!" << endl;
            success = false;
        }
        // Load high score
        if(!gHighscore.load_from_rendered_text("Hi: ", textColor, gRenderer, gFont))
        {
            cout << "Unable to render hi score texture!" << endl;
            success = false;
        }
        // Load texts on screen
        /*if(!game_over.load_from_rendered_text("GAME OVER!", textColor, gRenderer, gFont))
        {
            cout << "Unable to render game over texture!" << endl;
            success = false;
        }
        if(!replay.load_from_rendered_text("Press R to play again", textColor, gRenderer, gFont))
        {
            cout << "Unable to render play again texture!" << endl;
            success = false;
        }
        if(!exit_game.load_from_rendered_text("Press Esc to quit", textColor, gRenderer, gFont))
        {
            cout << "Unable to render exit game texture!" << endl;
            success = false;
        }*/

    }
    // Load music in menu
    gMusic_in_menu = Mix_LoadMUS("music\\MenuSound.mp3");
    if(gMusic_in_menu == NULL)
    {
        cout << "Failed to load background music! SDL_mixer Error: " << Mix_GetError() << endl;
        success = false;
    }
    // Load music when playing
    gMusic_when_playing = Mix_LoadMUS("music\\Music2.mp3");
    if(gMusic_when_playing == NULL)
    {
        cout << "Failed to load background music! SDL_mixer Error: " << Mix_GetError() << endl;
        success = false;
    }

    // load sound when jump
    gjump = Mix_LoadWAV("music\\Jump1.wav");
    if(gjump == NULL)
    {
        cout << "Failed to load jumping sound effect! SDL_mixer Error: " << Mix_GetError() << endl;
        success = false;
    }

    // Load sound when die
    gdeath = Mix_LoadWAV("music\\Die1.wav");
    if(gdeath == NULL)
    {
        cout << "Failed to load death sound effect! SDL_mixer Error: " << Mix_GetError() << endl;
        success = false;
    }

    return success;
}

void close(LTexture &gPlayer1_jump, LTexture &gPlayer2_jump, LTexture &gPlayer3_jump, LTexture &gPlayer1_death, LTexture &gPlayer2_death, LTexture &gPlayer3_death,
           LTexture &gPlayer_background, LTexture &oObstacle1, LTexture &oObstacle2,
           LTexture &gPause, LTexture &gResume, LTexture &gScore, LTexture &game_over, LTexture &replay, LTexture &exit_game, LTexture &gHighscore, LTexture &introduction,
           Mix_Music *&gMusic_in_menu, Mix_Music *&gMusic_when_playing, Mix_Chunk *&gjump, Mix_Chunk *&gdeath, TTF_Font *&gFont, LTexture &current_score,
           SDL_Window *&gWindow, SDL_Renderer* &gRenderer,
           LTexture &gPlayer1_run, LTexture &gPlayer2_run, LTexture &gPlayer3_ground,
           LTexture &gArrow_left, LTexture &gArrow_right, LTexture &gArcher_left, LTexture &gArcher_right,
           LTexture &menu, LTexture &select, LTexture &select1, LTexture &select2, LTexture &select3)
{
    gPlayer1_jump.free();
    gPlayer2_jump.free();
    gPlayer3_jump.free();
    gPlayer1_death.free();
    gPlayer2_death_2.free();
    gPlayer3_death_3.free();
    gPlayer1_run.free();
    gPlayer2_run.free();
    gPlayer3_run.free();
    gPlayer_background.free();
    gScore.free();
    gHighscore.free();
    current_score.free();
    gPause.free();
    gResume.free();
    oObstacle1.free();
    oObstacle2.free();
    gArrow_left.free();
    gArrow_right.free();
    gArcher_left.free();
    gArcher_right.free();
    game_over.free();
    replay.free();
    exit_game.free();
    menu.free();
    select.free();
    select1.free();
    select2.free();
    select3.free();
    introduction.free();

    TTF_CloseFont(gFont);
    gFont = NULL;
    Mix_FreeMusic(gMusic_in_menu);
    gMusic_in_menu = NULL;
    Mix_FreeMusic(gMusic_when_playing);
    gMusic_when_playing = NULL;
    Mix_FreeChunk(gjump);
    gjump = NULL;
    Mix_FreeChunk(gdeath);
    gdeath = NULL;
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    TTF_Quit();
    SDL_Quit();
    IMG_Quit();
    Mix_Quit();
}
