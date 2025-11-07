# Guess The Word (Version C++)

## Aperçu
Ce projet propose une variante C++ du jeu "Guess The Word" : un mot mystère est choisi aléatoirement et le joueur doit le découvrir avant d'épuiser ses tentatives. L'interface console a été pensée pour offrir une progression fluide avec menu principal, choix de difficulté, suivi du score et historique des parties.

## Fonctionnalités clés
- **Interface guidée** : menus clairs pour lancer une partie, consulter les règles ou afficher les derniers scores.
- **Niveaux de difficulté** : trois listes de mots (`facile`, `moyen`, `difficile`) influencent le nombre de tentatives accordées.
- **Système de score** : calcul basé sur les tentatives restantes, la longueur du mot et l'efficacité du joueur.
- **Suivi des performances** :
  - `best_score.txt` conserve le meilleur score global.
  - `scores.txt` liste les dernières parties (affichées depuis le menu principal).
  - `historique.txt` archive l'ensemble des résultats (utile pour analyser toutes les parties).
- **Gestion des données** : les mots possibles sont stockés dans `txt/<niveau>.txt`, faciles à enrichir.

## Arborescence
```
c++/
├── affichage.h        # Fonctions d'affichage et d'interface utilisateur
├── main.cpp           # Boucle principale : menus, gameplay, calcul du score
├── variable.h         # Constantes et variables globales partagées
├── txt/
│   ├── facile.txt     # Mots du niveau facile
│   ├── moyen.txt      # Mots du niveau moyen
│   ├── difficile.txt  # Mots du niveau difficile
│   ├── best_score.txt # Record actuel
│   ├── scores.txt     # Derniers scores (affichés dans le menu)
│   └── historique.txt # Historique complet des parties
└── README.md          # Ce document
```

## Compilation
Depuis le dossier `c++/`, compilez avec **g++** (C++17 recommandé) :
```bash
g++ -std=c++17 -o guessTheWord main.cpp
```

## Lancement
Toujours dans `c++/` :
```bash
./guessTheWord
```

## Déroulement d'une partie
1. **Menu principal** : choisir "Jouer".
2. **Pseudo** : renseigner un nom pour personnaliser les scores.
3. **Difficulté** : sélectionner le niveau (influe sur les tentatives). Le mot mystère est alors tiré au hasard.
4. **Tour par tour** : proposer des lettres ; les bonnes sont révélées dans le mot. Les autres réduisent le nombre de tentatives.
5. **Fin de partie** :
   - **Victoire** : calcul du score, possible nouveau record, ajout à l'historique.
   - **Défaite** : révélation du mot mystère et sauvegarde du résultat.

## Personnalisation rapide
- Ajouter ou modifier des mots : éditer `txt/facile.txt`, `txt/moyen.txt`, `txt/difficile.txt`.
- Changer le nombre de tentatives de base : ajuster `maxTentatives` dans `variable.h`.
- Adapter le calcul du score : modifier `calculerScore` dans `main.cpp`.

## Licences et attribution
Les fichiers textes et le code C++ sont fournis à titre pédagogique. Adaptez, partagez ou améliorez librement en mentionnant la source si nécessaire.
