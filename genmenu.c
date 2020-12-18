#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h> // Pour pouvoir utiliser printf()
#include <string.h>//pour essayer de centrer le menu quel que soit la taille de la fenetre
#include "GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "BmpLib.h" // Cet include permet de manipuler des fichiers BMP

// Largeur et hauteur par defaut d'une image correspondant a nos criteres
#define LargeurFenetre 800
#define HauteurFenetre 600

void gestionEvenement(EvenementGfx evenement);

//Fonction nous permettant d'afficher l'endroit ou l'utilisateur veut aller
void choixmenu (void)
{
	if (abscisseSouris()>(largeurFenetre()/2) - 120)
	{
		if (abscisseSouris()<(largeurFenetre()/2) + 120)
		{
			
			//CAS 1 : Le Joueur appuie sur PLAY
			if (ordonneeSouris()<(hauteurFenetre()/2+30))
			{
				if (ordonneeSouris()>(hauteurFenetre()/2)-10)
				{
					printf("Curseur sur zone PLAY\n");
					//mettre en lien la fonction permettant de lancer le jeu
				}
			}
			
			//CAS 2 : Le Joueur Appuie sur LEADERBOARD
			if (ordonneeSouris()<((hauteurFenetre()/2)-40))
			{
				if (ordonneeSouris()>((hauteurFenetre()/2)-80))
				{
					printf("Curseur sur la zone LEADERBOARD\n");
					//afficher la page du leaderboard
				}
			}
			
			//CAS 3 : Le Joueur appuie sur Options
			if (ordonneeSouris()<hauteurFenetre()/2 - 110)
			{
				if (ordonneeSouris()>hauteurFenetre()/2 - 150)
				{
					printf("Curseur sur la zone OPTIONS\n");
					//afficher la page d'options
				}
			}
			
			//CAS 4 : Le Joueur appuie sur Credits
			if(ordonneeSouris()<hauteurFenetre()/2 - 180)
			{
				if(ordonneeSouris()>hauteurFenetre()/2 - 215)
				{
					printf("Curseur sur la zone CREDITS\n");
					//afficher la page des credits
				}
			}
			
			//CAS 5 : Le joueur appuie sur Quit
			if(ordonneeSouris()<hauteurFenetre()/2 - 250)
			{
				if(ordonneeSouris()>hauteurFenetre()/2 - 290)
				{
					printf("Curseur sur la zone QUIT\n");
					//on quitte le jeu
					termineBoucleEvenements();
				}
			}
		}
	}
	
	
}

int main(int argc, char **argv)
{
	initialiseGfx(argc, argv);
	
	prepareFenetreGraphique("Space Invaders", LargeurFenetre, HauteurFenetre);
	
	// Lance la boucle qui aiguille les evenements sur la fonction gestionEvenement ci-apres,
	// qui elle-meme utilise fonctionAffichage ci-dessous
	lanceBoucleEvenements();
	
	return 0;
}

// La fonction de gestion des evenements, appelee automatiquement par le systeme
// des qu'une evenement survient
void gestionEvenement(EvenementGfx evenement)
{
	static bool pleinEcran = true; // Pour savoir si on est en mode plein ecran ou pas
	
	switch (evenement)
	{
		default:
			break;
		case Initialisation:
			modePleinEcran();
			// Le message "Initialisation" est envoye une seule fois, au debut du
			// programme
			// Pas besoin de tempo; le menu ne bouge pas (pour le moment)
			demandeTemporisation(20);
			break;
		case Affichage:
			
			// On part d'un fond d'ecran noir
			effaceFenetre (0, 0, 0);


			//Affichage du titre du jeu
			couleurCourante(210, 210, 210);
			epaisseurDeTrait(3);
			afficheChaine("SPACE INVADERS", 40, (largeurFenetre()/2)-strlen("space invaders")*12, 0.80*hauteurFenetre());
			
			//affichage d'un rectangle blanc pour la section play
			
			/*couleurCourante(210,210,210);
			rectangle(largeurFenetre()/2-100, hauteurFenetre()/2-50 ,largeurFenetre()/2+100, hauteurFenetre()/2+50);
			*/
			//Affichage du texte play du menu
			
			couleurCourante(210,210,210);
			afficheChaine("PLAY", 30, (largeurFenetre()/2)- strlen("play")*10, hauteurFenetre()/2);
			
			//affichage du texte leaderboard du menu
			
			couleurCourante(210,210,210);
			afficheChaine("LEADERBOARD", 30, (largeurFenetre()/2) -strlen("leaderboard")*9.5, (hauteurFenetre()/2)-70);
			
			//affichage du texte options du menu
			
			couleurCourante(210,210,210);
			afficheChaine("OPTIONS", 30, (largeurFenetre()/2) -strlen("options")*9.5, hauteurFenetre()/2 - 140);
			
			//affichage de la section crédit
			
			couleurCourante(210,210,210);
			afficheChaine("CREDITS", 30, (largeurFenetre()/2) - strlen("credits")*9.5, hauteurFenetre()/2 - 210);
			
			//affichage du bouton quit
			
			couleurCourante(210,210,210);
			afficheChaine("QUIT", 30, largeurFenetre()/2 - strlen("quit")*9.5, hauteurFenetre()/2 - 280);
			
			break;
			
		case Clavier:
			printf("%c : ASCII %d\n", caractereClavier(), caractereClavier());

			switch (caractereClavier())
			{
				case 'Q': // Pour sortir quelque peu proprement du programme
				case 'q':
				
					termineBoucleEvenements();
					break;

				case 'F':
				case 'f':
					pleinEcran = !pleinEcran; // Changement de mode plein ecran
					if (pleinEcran)
						modePleinEcran();
					else
						redimensionneFenetre(LargeurFenetre, HauteurFenetre);
					break;
					
				case 'R':
				case 'r':
					// Configure le systeme pour generer un message Temporisation
					// toutes les 20 millisecondes (rapide)
					demandeTemporisation(20);
					break;
				
				case 'L':
				case 'l':
					// Configure le systeme pour generer un message Temporisation
					// toutes les 100 millisecondes (lent)
					demandeTemporisation(100);
					break;

				case 'S':
				case 's':
					// Configure le systeme pour ne plus generer de message Temporisation
					demandeTemporisation(-1);
					break;
			}
			break;
			
		case ClavierSpecial:
			printf("ASCII %d\n", toucheClavier());
			break;

		case BoutonSouris:
			if (etatBoutonSouris() == GaucheAppuye)
			{
				printf("Bouton gauche appuye en : (%d, %d)\n", abscisseSouris(), ordonneeSouris());
				// Si le bouton gauche de la souris est appuye, on regarde ou le joueur clique pour définir les actions suivantes
				choixmenu();
			
			}
			else if (etatBoutonSouris() == GaucheRelache)
			{
				printf("Bouton gauche relache en : (%d, %d)\n", abscisseSouris(), ordonneeSouris());
			}
			break;
		
		case Souris: // Si la souris est deplacee
			break;
		
		case Inactivite: // Quand aucun message n'est disponible
			break;
		
		case Redimensionnement: // La taille de la fenetre a ete modifie ou on est passe en plein ecran
			printf("Largeur : %d\t", largeurFenetre());
			printf("Hauteur : %d\n", hauteurFenetre());
			break;
	}
}
