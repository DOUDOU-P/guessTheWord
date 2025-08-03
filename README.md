Programme console pour faire deviner un mot à l'utilisateur
Le principe est simple, l'utilisateurs a droit à un nombre de tentatives et doit deviner un mot choisi aléatoirement dans le fichier words.txt.
Au debut, aucune lettre n'est devoilée, chaque bonne lettre proposé par l'utilisateur est affiché autant de fois qu'il se trouve dans le mot à deviner
Les autres lettres qui n'ont pas encore été devinées sont masquées par des étoiles jusqu'à ce qu'elles soient devinées.
Le jeu est gagné lorsque l'utilisateur trouve toutes les lettres qui composent le mot et perdu si celui ci ne trouve pas le mot correct au bout de sa dernière tentative.
Le fichier secretWord.h contient les prototypes de toutes les fonctions utilisées.

unsigned int generateRandomNumber(const unsigned int, const unsigned int);
  Cette fonction génère un nombre aléatoire entre 1 et n, n étant le nombre de mots dans le fichier
  Sa sortie est utilisée par la fonction getSecretWord afin de trouver le m ième mot m étant le nombre aléatoire
  généré entre 1 et n.
  
void getSecretWord(FILE*, const unsigned int, const unsigned int, char*);
  Cette fonction se sert du fichier et de la sortie de la fonction generateRandomNumber
  pour selectionner le bon mot le 3e paramètre est la chaine dans laquelle on écrira le
  mot sélectionné.

void initializeWithStars(char*, const size_t);
  Cette fonction prend une chaine et l'initialise avec des etoiles.
  Les etoiles seront progressivement remplacées par les caractères
  trouvées par l'utilisateur au fil du jeu
  
void gameLoop(const char*, char*, char*, unsigned int);
  C'est le coeur du programme, elle a pour role de prendre les propositions
  de l'utilisateur, verifier si elles sont dans le mot secret et les remplacer
  dans le tableau guessedLetters qui au départ à été initialisé avec des étoiles 
  avec la fonction initializeWithStars(). Cette fonction est donc notre 
  boucle de jeu et s'arrêtre dans 2 cas de figures
  - Le nombre d'essais a atteint zéro
  - L'utilisateur a trouvé le bon mot

    
void clearBuffer();
  Cette fonction est un utilitaire pour vider la mémoire tampon, surtout après la lecture d'un caractère afin d'éviter
  de recupérer un résidus de la mémoire tampon
