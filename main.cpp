#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <time.h>
#define NBJOUEUR 2
int main(int argc, char *argv[])
{
    SDL_Surface *ecran = NULL, *image=NULL, *rouge=NULL, *bleu=NULL, *bonus;
    SDL_Rect position, positionrouge,positionbleu, positionbonus;
    SDL_Init(SDL_INIT_VIDEO | SDL_DOUBLEBUF);//on initialise la vidéo
    SDL_Event event;
    int continuer=1,aleatoire,i = 0,collision=100,droite=709,haut=33,bas=508,gauche=35;
    clock_t debut=clock(),fin;
    double duree;
    char titre[i];
    char* ct;

    ecran=SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE);//on crée l'écran avec le format 640x480 avec les couleurs en 32 bit et l'autre truc osef
     SDL_WM_SetCaption("Boing", NULL);//titre de l'écran en haut à gauche
    image=SDL_LoadBMP("map.bmp");//image de fond

    srand(time(NULL));
    if (NBJOUEUR==2)
    {
    position.x = 0;//position de l'image de fond
    position.y = 0;//position de l'image de fond

    positionrouge.x=300; //rand()%500;//position du rond rouge
    positionrouge.y=400;//rand()%500;//position du rond rouge

    positionbleu.x= 450;//rand()%500;
    positionbleu.y=350;//rand()%500;

    positionbonus.x=400;//rand()%500;
    positionbonus.y= 300;//rand()%500;

    bleu=SDL_LoadBMP("bleu.bmp");
    rouge=SDL_LoadBMP("rouge.bmp");//on charge l'image du rond rouge
    bonus=SDL_LoadBMP("bonus.bmp");
    SDL_EnableKeyRepeat(10,10);
    while(continuer)
    {

        /**(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer=0;
                break;
            case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
                case (SDLK_ESCAPE):
                    continuer=0;
                    break;

                case (SDLK_UP):// Flèche haut
                    positionrouge.y--;
                    break;

                case (SDLK_DOWN): // Flèche bas
                    positionrouge.y++;
                    break;

                case (SDLK_RIGHT): // Flèche droite
                    positionrouge.x++;
                    break;

                case (SDLK_LEFT): // Flèche gauche
                    positionrouge.x--;
                    break;

                default:
                    break;
            }
        }**/


        aleatoire = rand()%4+ 1;


        if(aleatoire == 1) //||  positionbleu.x < positionrouge.x)
        {
            for(i=0; i<5; i++)
            {
                positionrouge.x++;
            }
        }
        else if(aleatoire == 2) //|| positionbleu.x > positionrouge.x)
        {
            for(i=0; i<5; i++)
            {
                positionrouge.x--;
            }
        }
        else if(aleatoire == 3) //|| positionbleu.y < positionrouge.y)
        {
            for(i=0; i<5; i++)
            {
                positionrouge.y++;
            }
        }
        else if(aleatoire ==4)//||  positionbleu.y > positionrouge.y)
        {
            for(i=0; i<5; i++)
            {
                positionrouge.y--;
            }
        }




        aleatoire = rand()%4 + 1;

        if(aleatoire == 1) //||  positionbleu.x < positionrouge.x)
        {
            for(i=0; i<5; i++)
            {
                positionbleu.x++;
            }
        }
        else if(aleatoire == 2) //|| positionbleu.x > positionrouge.x)
        {
            for(i=0; i<5; i++)
            {
                positionbleu.x--;
            }
        }
        else if(aleatoire == 3) //|| positionbleu.y < positionrouge.y)
        {
            for(i=0; i<5; i++)
            {
                positionbleu.y++;
            }
        }
        else if(aleatoire ==4)//||  positionbleu.y > positionrouge.y)
        {
            for(i=0; i<5; i++)
            {
                positionbleu.y--;
            }
        }

        if(positionbleu.x > 600)
        {
            positionbleu.x--;
        }
        else if(positionbleu.x <200)
        {
            positionbleu.x++;
        }
        else if(positionbleu.y >400)
        {
            positionbleu.y--;
        }
        else if(positionbleu.y <200)
        {
            positionbleu.y++;
        }



        if(positionrouge.x > 600)
        {
            positionrouge.x--;
        }
        else if(positionrouge.x <200)
        {
            positionrouge.x++;
        }
        else if(positionrouge.y >400)
        {
            positionrouge.y--;
        }
        else if(positionrouge.y <200)
        {
            positionrouge.y++;
        }
        SDL_BlitSurface(image,NULL,ecran,&position);//On colle l'image de fond sur l'écran
        /* On place rouge à sa nouvelle position */
        SDL_BlitSurface(rouge, NULL, ecran, &positionrouge);
        SDL_BlitSurface(bleu, NULL, ecran, &positionbleu);
        SDL_BlitSurface(bonus, NULL, ecran, &positionbonus);


        //gestion des collisions entre rouge et bleu
        if (positionrouge.x+32 == positionbleu.x && (positionrouge.y <= positionbleu.y+32 && positionrouge.y >= positionbleu.y-32))
        {
            positionbleu.x += collision;
            SDL_BlitSurface(rouge, NULL, ecran, &positionrouge);
            SDL_BlitSurface(bleu, NULL, ecran, &positionbleu);
            SDL_BlitSurface(bonus, NULL, ecran, &positionbonus);
            SDL_Flip(ecran);
        }

        else if (positionrouge.x-32 == positionbleu.x && (positionrouge.y <= positionbleu.y+32 && positionrouge.y >= positionbleu.y-32))
        {
            positionbleu.x = positionbleu.x - collision;
            SDL_BlitSurface(rouge, NULL, ecran, &positionrouge);
            SDL_BlitSurface(bleu, NULL, ecran, &positionbleu);
            SDL_BlitSurface(bonus, NULL, ecran, &positionbonus);
            SDL_Flip(ecran);
        }

        else  if (positionrouge.y+32 == positionbleu.y && (positionrouge.x <= positionbleu.x+32 && positionrouge.x >= positionbleu.x-32))
        {
            positionbleu.y += collision;
            SDL_BlitSurface(rouge, NULL, ecran, &positionrouge);
            SDL_BlitSurface(bleu, NULL, ecran, &positionbleu);
            SDL_BlitSurface(bonus, NULL, ecran, &positionbonus);
            SDL_Flip(ecran);
        }

        else if (positionrouge.y-32 == positionbleu.y && (positionrouge.x <= positionbleu.x+32 && positionrouge.x >= positionbleu.x-32))
        {
            positionbleu.y = positionbleu.y-collision;
            SDL_BlitSurface(rouge, NULL, ecran, &positionrouge);
            SDL_BlitSurface(bleu, NULL, ecran, &positionbleu);
            SDL_BlitSurface(bonus, NULL, ecran, &positionbonus);
            SDL_Flip(ecran);
        }

        SDL_Flip(ecran);

        if (positionrouge.x>droite || positionrouge.y<haut||positionrouge.y>bas||positionrouge.x<gauche)
        {
            SDL_SetAlpha(rouge, SDL_SRCALPHA, 0);
            positionrouge.x = 1000;
            positionrouge.y = 1000;
            SDL_Flip(ecran);
        }

        if (positionbleu.x>droite || positionbleu.y<haut||positionbleu.y>bas||positionbleu.x<gauche)
        {
            SDL_SetAlpha(bleu, SDL_SRCALPHA, 0);
            positionbleu.x = 1000;
            positionbleu.y = 1000;
            SDL_Flip(ecran);
        }

        if ((positionrouge.x+32>=400&&(positionrouge.y+32>=300 &&positionrouge.y<=332))||(positionrouge.x<=432&&(positionrouge.y+32>=300 &&positionrouge.y<=332))||(positionrouge.y+32>=300&&(positionrouge.x<=432&&positionrouge.x+32>=400))||(positionrouge.y<=332&&(positionrouge.x<=432&&positionrouge.x+32>=400)))
        {
            collision=200;
        }

        if (positionbleu.x == 1000 || positionrouge.x == 1000)
        {
            SDL_Delay(1000);
            continuer = 0;
        }
        fin=clock();
        duree = (double)(fin - debut) / CLOCKS_PER_SEC;
        if(duree>=180)
        {
            image=SDL_LoadBMP("map2.bmp");
            droite=519;
            haut=191;
            bas=394;
            gauche=222;
            SDL_BlitSurface(image,NULL,ecran,&position);
        }
    }
    SDL_FreeSurface(rouge);
    SDL_FreeSurface(bonus);
    SDL_FreeSurface(bleu);
    }
    /**if (NBJOUEUR>2)
    {
        SDL_Rect joueur[NBJOUEUR][2];
        FILE* fichier=NULL;
               fichier=fopen("texte.txt","r");
               i=0;
               if (fichier!=NULL)
               {
                   do
                    {
                       ct=NULL;
                       strok(titre[i]," ")
                       i+=1;
                   }
                   while (fgets(titre[i],11, fichier) != NULL)
               }
        while (continuer)
        {

        }
    }**/
    SDL_FreeSurface(image);//on libere
    SDL_Quit();

    return EXIT_SUCCESS;
}

