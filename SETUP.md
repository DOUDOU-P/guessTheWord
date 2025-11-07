# Configuration et Exécution de la version C++

Ce guide décrit toutes les étapes nécessaires pour compiler et lancer la version C++ du jeu **Guess The Word**.

## 1. Prérequis
- **Système** : Linux, macOS ou Windows (avec un shell compatible).
- **Compilateur C++** : `g++` (version 9 ou supérieure recommandée) ou tout équivalent compatible C++17.
- **Terminal** : accès à un terminal/console permettant d'exécuter des commandes.

Pour vérifier la présence de `g++`, exécutez :
```bash
g++ --version
```

## 2. Installation des dépendances
Aucune bibliothèque externe n'est requise. Si `g++` n'est pas installé :
- **Ubuntu/Debian** : `sudo apt install build-essential`
- **Fedora** : `sudo dnf install gcc-c++`
- **macOS** : `xcode-select --install`
- **Windows** : installer MinGW-w64 ou utiliser WSL avec `sudo apt install build-essential`.

## 3. Préparation du projet
Assurez-vous que l'arborescence suivante existe dans le dossier `c++/` :
```
main.cpp
affichage.h
variable.h
txt/
  ├── facile.txt
  ├── moyen.txt
  ├── difficile.txt
  ├── best_score.txt
  ├── scores.txt
  └── historique.txt
```
Les fichiers `scores.txt`, `best_score.txt` et `historique.txt` peuvent être vides lors de la première exécution.

## 4. Compilation
Depuis le dossier `c++/`, lancez la commande :
```bash
g++ -std=c++17 -o guessTheWord main.cpp
```
Cette commande génère l’exécutable `guessTheWord` à la racine du dossier `c++/`.

## 5. Exécution
Toujours dans le dossier `c++/`, exécutez :
```bash
./guessTheWord
```
Sur Windows (sans WSL), remplacez par :
```cmd
guessTheWord.exe
```

## 6. Conseils de dépannage
- **Erreur d’inclusion** : vérifiez que tous les fichiers `.h` et le dossier `txt/` sont présents.
- **Problème de locale ou d’affichage** : assurez-vous que le terminal est configuré en UTF-8.
- **Fichiers de mots introuvables** : vérifiez les chemins relatifs (l’exécutable doit être lancé depuis `c++/`).

Bonne compilation et bon jeu !

---

_Oumar Dicko – [github.com/oumvr19](https://github.com/oumvr19)_
