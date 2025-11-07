/*Librairie */
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <random>
#include <limits>
#include <algorithm>
#include <cctype>
#include <sstream>
#include "affichage.h"
#include "variable.h"
using namespace std;

struct BestScore
{
    string pseudo;
    int score = 0;
};

struct ScoreEntry
{
    string pseudo;
    int score = 0;
    string mot;
    string niveau;
    bool victoire = false;
    int tentativesUtilisees = 0;
};

static string formaterNomNiveau(const string& niveau);

static string normaliserMot(string mot)
{
    if (!mot.empty() && mot.back() == '\r')
    {
        mot.pop_back();
    }
    transform(mot.begin(), mot.end(), mot.begin(), [](unsigned char c)
    {
        return static_cast<char>(tolower(c));
    });
    return mot;
}

static BestScore chargerBestScore(const string& chemin)
{
    BestScore best;
    ifstream fichier(chemin);
    if (!fichier)
    {
        return best;
    }
    fichier >> best.pseudo >> best.score;
    if (!fichier)
    {
        best.pseudo.clear();
        best.score = 0;
    }
    return best;
}

static void sauvegarderBestScore(const string& chemin, const BestScore& best)
{
    ofstream fichier(chemin, ios::trunc);
    if (fichier)
    {
        fichier << best.pseudo << ' ' << best.score;
    }
}

static void enregistrerScore(const string& chemin, const ScoreEntry& entree)
{
    ofstream fichier(chemin, ios::app);
    if (fichier)
    {
        fichier << entree.pseudo << ';' << entree.score << ';' << entree.mot << ';' << entree.niveau << ';'
                << (entree.victoire ? "victoire" : "defaite") << ';' << entree.tentativesUtilisees << '\n';
    }
}

static void ajouterHistorique(const string& chemin, const ScoreEntry& entree)
{
    enregistrerScore(chemin, entree);
}

static vector<ScoreEntry> chargerDerniersScores(const string& chemin, size_t maxScores)
{
    vector<ScoreEntry> scores;
    ifstream fichier(chemin);
    if (!fichier)
    {
        return scores;
    }

    string ligne;
    while (getline(fichier, ligne))
    {
        if (ligne.empty())
        {
            continue;
        }
        ScoreEntry entree;
        vector<string> morceaux;
        string morceau;
        stringstream ss(ligne);
        while (getline(ss, morceau, ';'))
        {
            morceaux.push_back(morceau);
        }
        if (morceaux.size() < 6)
        {
            continue;
        }
        try
        {
            entree.pseudo = morceaux[0];
            entree.score = stoi(morceaux[1]);
            entree.mot = morceaux[2];
            entree.niveau = morceaux[3];
            entree.victoire = (morceaux[4] == "victoire");
            entree.tentativesUtilisees = stoi(morceaux[5]);
            scores.push_back(entree);
        }
        catch (...)
        {
            continue;
        }
    }

    if (scores.size() > maxScores)
    {
        return vector<ScoreEntry>(scores.end() - maxScores, scores.end());
    }
    return scores;
}

static vector<string> formatterScoresRecents(const vector<ScoreEntry>& scores)
{
    vector<string> lignes;
    lignes.reserve(scores.size());
    for (auto it = scores.rbegin(); it != scores.rend(); ++it)
    {
        ostringstream oss;
        oss << it->pseudo << " - " << it->score << " pts - " << (it->victoire ? "victoire" : "defaite")
            << " - niveau : " << formaterNomNiveau(it->niveau)
            << " - mot : " << formaterMotAvecEspaces(it->mot)
            << " - tentatives utilisees : " << it->tentativesUtilisees;
        lignes.push_back(oss.str());
    }
    return lignes;
}

static int calculerScore(int tentativesRestantes, int tentativesInitiales, size_t longueurMot)
{
    const int bonusTentatives = tentativesRestantes * 20;
    const int bonusLongueur = static_cast<int>(longueurMot) * 3;
    const int bonusEfficacite = (tentativesInitiales - tentativesRestantes) <= 0 ? 10 : (tentativesInitiales - tentativesRestantes) * 2;
    return bonusTentatives + bonusLongueur + bonusEfficacite;
}

static string nomNiveauDepuisChoix(int choix)
{
    switch (choix)
    {
        case 1:
            return "facile";
        case 2:
            return "moyen";
        case 3:
            return "difficile";
        default:
            return {};
    }
}

static int tentativesPourNiveau(const string& niveau)
{
    if (niveau == "facile")
    {
        return maxTentatives + 3;
    }
    if (niveau == "difficile")
    {
        return std::max(2, maxTentatives - 1);
    }
    return maxTentatives;
}

static string formaterNomNiveau(const string& niveau)
{
    if (niveau.empty())
    {
        return {};
    }
    string resultat = niveau;
    resultat[0] = static_cast<char>(toupper(static_cast<unsigned char>(resultat[0])));
    for (size_t i = 1; i < resultat.size(); ++i)
    {
        resultat[i] = static_cast<char>(tolower(static_cast<unsigned char>(resultat[i])));
    }
    return resultat;
}

static string formaterListeLettres(const unordered_set<char>& lettres)
{
    if (lettres.empty())
    {
        return {};
    }
    vector<char> lettresTriees(lettres.begin(), lettres.end());
    sort(lettresTriees.begin(), lettresTriees.end());
    string resultat;
    resultat.reserve(lettresTriees.size() * 2);
    for (size_t i = 0; i < lettresTriees.size(); ++i)
    {
        resultat.push_back(lettresTriees[i]);
        if (i + 1 < lettresTriees.size())
        {
            resultat.push_back(' ');
        }
    }
    return resultat;
}

int main()
{
    unordered_map<string, vector<string>> listeMots;
    const vector<string> niveaux = {"facile", "moyen", "difficile"};
    for (const auto& niveau : niveaux)
    {
        const string path = "txt/" + niveau + ".txt";
        ifstream fichier(path);
        if (!fichier)
        {
            cerr << "Erreur lors de l'ouverture du fichier " << path << endl;
            return 1;
        }
        string mot;
        while (getline(fichier, mot))
        {
            mot = normaliserMot(mot);
            if (!mot.empty())
            {
                listeMots[niveau].push_back(mot);
            }
        }
    }

    BestScore meilleur = chargerBestScore("txt/best_score.txt");

    random_device rd;
    mt19937 generateur(rd());

    bienvenue();
    pause();

    while (true)
    {
        menuPrincipal(meilleur.pseudo, meilleur.score);
        int choix = 0;
        if (!(cin >> choix))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            erreurChoixMenu();
            pause();
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choix)
        {
            case 1:
            {
                string pseudo;
                demanderPseudo(pseudo);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                bool continuerPartie = true;
                string niveauSelectionne;
                string niveauLibelle;
                int tentativesInitiales = 0;
                int scoreTotal = 0;

                while (continuerPartie)
                {
                    if (niveauSelectionne.empty())
                    {
                        int choixNiveau = 0;
                        while (niveauSelectionne.empty())
                        {
                            menuDifficulte();
                            if (!(cin >> choixNiveau))
                            {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                erreurChoixMenu();
                                pause();
                                continue;
                            }
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            niveauSelectionne = nomNiveauDepuisChoix(choixNiveau);
                            if (niveauSelectionne.empty())
                            {
                                erreurChoixMenu();
                                pause();
                            }
                        }
                    }

                    const auto& mots = listeMots[niveauSelectionne];
                    if (mots.empty())
                    {
                        cerr << "Aucun mot disponible pour le niveau " << niveauSelectionne << endl;
                        pause();
                        continuerPartie = false;
                        break;
                    }

                    uniform_int_distribution<size_t> distribution(0, mots.size() - 1);
                    const string motMystere = mots[distribution(generateur)];
                    string motAffiche(motMystere.size(), '*');

                    tentativesInitiales = tentativesPourNiveau(niveauSelectionne);
                    int tentativesRestantes = tentativesInitiales;
                    unordered_set<char> lettresProposees;
                    niveauLibelle = formaterNomNiveau(niveauSelectionne);

                    afficherNiveauChoisi(niveauLibelle, tentativesInitiales);
                    pause();

                    string feedback = "Bonne chance !";
                    bool motTrouve = false;
                    while (tentativesRestantes > 0 && !motTrouve)
                    {
                        const string lettresAffichees = formaterListeLettres(lettresProposees);
                        afficherEtatJeu(pseudo, niveauLibelle, motAffiche, tentativesRestantes, lettresAffichees, feedback);
                        feedback.clear();

                        char lettre = '\0';
                        inciterLettre(lettre);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        lettre = static_cast<char>(tolower(static_cast<unsigned char>(lettre)));

                        if (!isalpha(static_cast<unsigned char>(lettre)))
                        {
                            feedback = "Veuillez proposer une lettre valide (a-z).";
                            continue;
                        }

                        if (lettresProposees.count(lettre))
                        {
                            feedback = "Lettre deja proposee. Essayez-en une autre.";
                            continue;
                        }
                        lettresProposees.insert(lettre);

                        int occurrences = 0;
                        for (size_t i = 0; i < motMystere.size(); ++i)
                        {
                            if (motMystere[i] == lettre)
                            {
                                motAffiche[i] = lettre;
                                ++occurrences;
                            }
                        }

                        if (occurrences > 0)
                        {
                            feedback = "Bravo ! La lettre '" + string(1, lettre) + "' est presente";
                            if (occurrences > 1)
                            {
                                feedback += " " + to_string(occurrences) + " fois.";
                            }
                            else
                            {
                                feedback += " dans le mot.";
                            }
                            if (motAffiche == motMystere)
                            {
                                motTrouve = true;
                            }
                        }
                        else
                        {
                            feedback = "Oops ! La lettre '" + string(1, lettre) + "' n'est pas dans le mot.";
                            --tentativesRestantes;
                        }
                    }

                    const int scorePartie = motTrouve ? calculerScore(tentativesRestantes, tentativesInitiales, motMystere.size()) : 0;
                    if (motTrouve)
                    {
                        scoreTotal += scorePartie;
                    }
                    const int tentativesUtilisees = tentativesInitiales - tentativesRestantes;
                    const ScoreEntry entree{pseudo, scoreTotal, motMystere, niveauSelectionne, motTrouve, tentativesUtilisees};
                    enregistrerScore("txt/scores.txt", entree);
                    ajouterHistorique("txt/historique.txt", entree);

                    bool rejouer = false;
                    if (motTrouve)
                    {
                        string messageSupplementaire = "Score total : " + to_string(scoreTotal) + " points.";
                        if (scoreTotal > meilleur.score)
                        {
                            meilleur.pseudo = pseudo;
                            meilleur.score = scoreTotal;
                            sauvegarderBestScore("txt/best_score.txt", meilleur);
                            messageSupplementaire += "\nNouveau meilleur score !";
                        }
                        else if (!meilleur.pseudo.empty())
                        {
                            messageSupplementaire += "\nRecord actuel : " + meilleur.pseudo + " - " + to_string(meilleur.score) + " points.";
                        }
                        afficherScore(pseudo, scorePartie, motMystere, messageSupplementaire);
                        rejouer = demanderRejouer();
                    }
                    else
                    {
                        afficherGameOver(pseudo, motMystere);
                        rejouer = demanderRejouer();
                    }

                    if (!rejouer)
                    {
                        niveauSelectionne.clear();
                        continuerPartie = false;
                    }
                }

                break;
            }
            case 2:
                reglesJeu();
                pause();
                break;
            case 3:
            {
                const auto scoresRecents = chargerDerniersScores("txt/scores.txt", 5);
                const auto lignes = formatterScoresRecents(scoresRecents);
                afficherScoresRecents(lignes);
                pause();
                break;
            }
            case 4:
                cout << "Merci d'avoir joue ! Au revoir !" << endl;
                return 0;
            default:
                erreurChoixMenu();
                pause();
                break;
        }
    }
    return 0;
}