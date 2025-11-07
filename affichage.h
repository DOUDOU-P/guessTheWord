#pragma once

#include <iostream>
#include <string>
#include <limits>
#include <sstream>
#include <vector>
#include <cctype>

using namespace std;

inline void afficherBarreDessus()
{
    cout << "============================ Guess The Word ============================" << endl;
}

inline void afficherBarreDessous()
{
    cout << "=======================================================================" << endl;
}

inline string formaterMotAvecEspaces(const string& mot)
{
    if (mot.empty())
    {
        return {};
    }
    ostringstream oss;
    for (size_t i = 0; i < mot.size(); ++i)
    {
        oss << mot[i];
        if (i + 1 < mot.size())
        {
            oss << ' ';
        }
    }
    return oss.str();
}

inline void bienvenue()
{
    system("clear");
    afficherBarreDessus();
    cout << "Bienvenue dans Guess The Word !" << endl;
    cout << "Devinez le mot mystere en un nombre limite de tentatives." << endl;
    cout << "Chaque bonne lettre revele sa position dans le mot." << endl;
    afficherBarreDessous();
    cout<<"Created by Oumar Dicko (github:Oumvr19)"<<endl;
}

inline void menuPrincipal(const string& meilleurPseudo = string{}, int meilleurScore = 0)
{
    system("clear");
    afficherBarreDessus();
    cout << "Menu Principal" << endl;
    afficherBarreDessous();
    cout << "1 - Jouer" << endl;
    cout << "2 - Regles du jeu" << endl;
    cout << "3 - Derniers scores" << endl;
    cout << "4 - Quitter" << endl;
    afficherBarreDessous();
    if (!meilleurPseudo.empty())
    {
        cout << "Record a battre : " << meilleurPseudo << " avec " << meilleurScore << " points." << endl;
        afficherBarreDessous();
    }
    cout << "Veuillez choisir une option : ";
}

inline void afficherScoresRecents(const vector<string>& lignes)
{
    system("clear");
    afficherBarreDessus();
    cout << "Les 5 derniers scores" << endl;
    afficherBarreDessous();
    if (lignes.empty())
    {
        cout << "Aucun score enregistre pour le moment." << endl;
    }
    else
    {
        for (size_t index = 0; index < lignes.size(); ++index)
        {
            cout << index + 1 << ". " << lignes[index] << endl;
        }
    }
    afficherBarreDessous();
}

inline void reglesJeu()
{
    system("clear");
    afficherBarreDessus();
    cout << "Regles du jeu" << endl;
    afficherBarreDessous();
    cout << "1 - Choisissez un niveau de difficulte." << endl;
    cout << "2 - Un mot mystere vous est attribue." << endl;
    cout << "3 - Proposez des lettres : les bonnes se revelent, les autres coutent une tentative." << endl;
    cout << "4 - Gagnez en trouvant toutes les lettres avant d'epuiser vos tentatives." << endl;
    afficherBarreDessous();
}

inline void erreurChoixMenu()
{
    system("clear");
    afficherBarreDessus();
    cout << "Attention !" << endl;
    afficherBarreDessous();
    cout << "Le choix effectue est invalide. Veuillez reessayer." << endl;
    afficherBarreDessous();
}

inline void pause()
{
    cout << endl << "Appuyez sur Entree pour continuer ..." << endl;
    if (cin.rdbuf()->in_avail() > 0)
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.get();
}

inline void demanderPseudo(string& pseudo)
{
    system("clear");
    afficherBarreDessus();
    cout << "Quel est votre pseudo ?" << endl;
    afficherBarreDessous();
    cout << "> ";
    cin >> pseudo;
}

inline void menuDifficulte()
{
    system("clear");
    afficherBarreDessus();
    cout << "Choisissez un niveau" << endl;
    afficherBarreDessous();
    cout << "1 - Facile (plus de tentatives)" << endl;
    cout << "2 - Moyen" << endl;
    cout << "3 - Difficile (moins de tentatives)" << endl;
    afficherBarreDessous();
    cout << "Selection : ";
}

inline void afficherScore(const string& pseudo, int score, const string& motTrouve, const string& messageSupplementaire = {})
{
    system("clear");
    afficherBarreDessus();
    cout << "Bravo " << pseudo << " !" << endl;
    cout << "Mot trouve : " << formaterMotAvecEspaces(motTrouve) << " (" << motTrouve.size() << " lettres)" << endl;
    cout << "Score de la partie : " << score << " points" << endl;
    if (!messageSupplementaire.empty())
    {
        afficherBarreDessous();
        cout << messageSupplementaire << endl;
    }
    afficherBarreDessous();
}

inline void afficherDefaite(const string& pseudo, const string& motMystere)
{
    system("clear");
    afficherBarreDessus();
    cout << "Courage " << pseudo << " !" << endl;
    cout << "Vous n'avez plus de tentatives." << endl;
    cout << "Le mot mystere etait : " << formaterMotAvecEspaces(motMystere) << endl;
    afficherBarreDessous();
}

inline void afficherGameOver(const string& pseudo, const string& motMystere)
{
    system("clear");
    afficherBarreDessus();
    cout << "GAME OVER" << endl;
    afficherBarreDessous();
    cout << "Desole " << pseudo << ", la partie est terminee." << endl;
    cout << "Le mot mystere etait : " << formaterMotAvecEspaces(motMystere) << endl;
    afficherBarreDessous();
}

inline void inciterLettre(char& lettre)
{
    cout << "> ";
    cin >> lettre;
}

inline bool demanderRejouer()
{
    cout << endl << "Souhaitez-vous continuer ? (o/n) : ";
    while (true)
    {
        char reponse = 'n';
        if (!(cin >> reponse))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entree invalide. Veuillez repondre par o ou n : ";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        reponse = static_cast<char>(tolower(static_cast<unsigned char>(reponse)));
        if (reponse == 'o')
        {
            return true;
        }
        if (reponse == 'n')
        {
            return false;
        }
        cout << "Entree invalide. Veuillez repondre par o ou n : ";
    }
}

inline void afficherNiveauChoisi(const string& niveauLibelle, int tentatives)
{
    system("clear");
    afficherBarreDessus();
    cout << "Niveau " << niveauLibelle << " selectionne." << endl;
    cout << "Vous disposez de " << tentatives << " tentatives." << endl;
    afficherBarreDessous();
}

inline void afficherEtatJeu(const string& pseudo,
                            const string& niveauLibelle,
                            const string& motAffiche,
                            int tentativesRestantes,
                            const string& lettresProposees,
                            const string& feedback)
{
    system("clear");
    afficherBarreDessus();
    cout << "Joueur : " << pseudo << " | Niveau : " << niveauLibelle << endl;
    afficherBarreDessous();
    cout << "Mot a deviner (" << motAffiche.size() << " lettres) : " << formaterMotAvecEspaces(motAffiche) << endl;
    cout << "Tentatives restantes : " << tentativesRestantes << endl;
    if (!lettresProposees.empty())
    {
        cout << "Lettres proposees : " << lettresProposees << endl;
    }
    if (!feedback.empty())
    {
        afficherBarreDessous();
        cout << feedback << endl;
    }
    afficherBarreDessous();
    cout << "Proposez une lettre puis validez avec Entree." << endl;
}
