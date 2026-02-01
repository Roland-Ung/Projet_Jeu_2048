# Jeu 2048

## Objectifs
- Implémenter un jeu interactif en C
- Manipuler un tableau 2D et des structures de données
- Gérer les entrées clavier en temps réel
- Utiliser la bibliothèque ncurses pour l’affichage terminal

## Fonctionnalités

### 1 - Initialisation du jeu
- Création d’un plateau 4×4
- Initialisation des cases à 0
- Initialisation du terminal avec `ncurses`
- Génération aléatoire contrôlée (`srand`, `time`)

### 2 - Affichage du plateau
- Affichage du plateau sous forme de grille ASCII
- Affichage du score en temps réel
- Rafraîchissement dynamique de l’écran (`clear`, `refresh`)

### 3 - Gestion des déplacements
- Déplacements via les flèches directionnelles
- Compression des tuiles vers la direction choisie
- Orientations du plateau : miroir, pivot (transposition)

### 4 - Fusion des tuiles
- Fusion automatique des tuiles adjacentes de même valeur
- Mise à jour du score après chaque fusion
- Suppression des tuiles fusionnées

### 5 - Génération de nouvelles tuiles
- Ajout automatique d’une tuile 2 après chaque coup valide
- Placement aléatoire sur une case vide

### 6 - Détection de fin de partie
- Vérification du nombre de cases vides
- Affichage d’un message GAME OVER
- Attente d’une action utilisateur avant fermeture

## Installation et Utilisation

### Prérequis
- Système Linux / macOS
- Compilateur C : `gcc` ou `clang`
- Bibliothèque ncurses

**Installation de ncurses (Linux)**
```bash
sudo apt install libncurses5-dev libncursesw5-dev
```

### Installation

**1. Cloner le dépôt**
```bash
git clone https://github.com/Roland-Ung/Projet_Jeu_2048.git
cd Projet_Jeu_2048
```

**2. Compiler le jeu**
```bash
gcc main.c -o jeu2048 -lncurses
```

**3. Lancer le jeu**
```bash
./jeu2048
```

## Structure du projet
```
Projet_Jeu_2048/
│
├── main.c
├── .gitignore
└── README.md
```
