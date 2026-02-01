// ldd: -lncurses 
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>

// Déclaration des constantes
#define board_size 4

typedef struct {
    int val;
} tab;

typedef enum { 
  key_up, 
  key_down, 
  key_left, 
  key_right, 
  key_backspace  
} key ;

// variables globales
tab board[board_size][board_size];
int score= 0 ; // stocke le score


// initialise le plateau avec des cases vides
void init_board() {
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            board[i][j].val = 0; //cases vides
        }
    }
}


// affiche le plateau du jeu
void display_board() {
  
    clear() ;
    move(0,0);
    // Affichage de la bannière avec le nom du jeu et le score
    printw("== 2048 =============================\n");
    printw("======================Score:%8i\n\n", score);
  

  
    // Affiche le tableau
    for (int i = 0; i < board_size; i++) { //chaque ligne
      
        // Ligne horizontale avant chaque ligne de cellules
        for (int j = 0; j <  board_size ; j++) { //chaque colonne
            printw("+--------");
        }
        printw("+\n");
      
      

        // Affichage de chaque ligne verticale de cellules
        for (int j = 0; j < board_size; j++) { 
            printw("|        "); //sous-ligne 1
        }
        printw("|\n");
      
        for (int j = 0; j < board_size; j++) { 
          if (board[i][j].val==0) {
             printw("|        "); //sous-ligne 2
          } else { printw("|%5i   ",board[i][j].val ); } //sous-ligne 2
        }
        printw("|\n");
      
        for (int j = 0; j < board_size; j++) { 
             printw("|        "); //sous-ligne 3
        }
        printw("|\n");
    }

  
  
    // Ligne horizontale en bas du plateau
    for (int i = 0; i <  board_size ; i++) {
        printw("+--------");
    }
    printw("+\n\n");
  
    refresh() ;
}

//renvoie le nombre de case vide
int count_empty() {
  
  int empty = 0 ;
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
          if (board[i][j].val==0) {
            empty++; }
        }
    }
    return empty ;
}

// insère aléatoirement le nombre 2 dans le plateau
void add_two(int empty) {

    empty = count_empty() ;
    int random_index = random() % empty; // Choisi un index aléatoire entre 0 et empty-1
    int count = 0; // pour parcourir le plateau
  
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            if (board[i][j].val == 0) { // Si la case est vide
                if (count == random_index) { // Si c'est l'index choisi
                    board[i][j].val = 2; } // Ajoute le nombre 2 dans cette case                
                count++; } // passe à la prochaine case vide            
        }
    }
}

// vérifie si le jeu est terminé
int game_over(int add) {

    int empty = count_empty() ;
    if ( empty == 0) { // si aucune case vide
        printw("============= GAME OVER =============\n");
        printw("=========== (press a key) ===========\n");
        getch(); // Attend qu'on appuie sur une touche
        return 1; } // jeu terminé
  
    else if ( empty >= 1 && add ) {
        add_two(empty); // Ajoute un 2 sur le plateau
        display_board(); // Affiche le plateau
        return 0; }
    
    else { return 0; }
}

// décale tous les chiffres à gauche pour chaque ligne
int shift_board() {
    int moved = 0; // 0 si pas de décalage

    for (int i = 0; i < board_size; i++) {
       int index = 0; // Indice où déplacer les éléments non nuls
       for (int j = 0; j < board_size; j++) {
         if (board[i][j].val != 0) { //s'il y a un chiffre dans la case
           board[i][index].val = board[i][j].val; //décale à gauche si index < j
           index++; //si 0 != 0 (un trou dans la ligne), alors index < j car condition non éxécuté, donc pas de index++
              if (j != index - 1) { //condition respectée lorsqu'il y a eu décalage
                board[i][j].val = 0; // vide l'ancienne position car le chiffre s'est décalé à gauche
                moved = 1; // Le décalage a eu lieu
               }
           }
       }
   }

    return moved;
}



// fais les additions des nombres égaux
int update_board() {
    int moved = shift_board() ;

    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
          if (board[i][j].val != 0 && board[i][j].val == board[i][j+1].val ) {
            board[i][j].val += board[i][j+1].val ; // addition des valeurs égaux
            board[i][j+1].val = 0 ; // vide la valeur de droite
            score += board[i][j].val ; // met à jour le score
            moved = 1 ;
            }
        }
    }
    shift_board();
    return moved;
}


// lit une touche au clavier ( flèches de direction, backspace )
key get_key() {
    int touch ;
    touch = getch() ;
    while (1) {
      switch(touch) {
        case KEY_UP :
          return KEY_UP ;
        case KEY_DOWN :
          return KEY_DOWN ;
        case KEY_LEFT :
          return KEY_LEFT ;
        case KEY_RIGHT :
          return KEY_RIGHT ;
        case KEY_BACKSPACE :
          return KEY_BACKSPACE ;
      }
    }
}

// échange deux entiers en mémoire
void swap (int* a, int* b) {
     int temp = *a ;
     *a = *b ;
     *b = temp ;
}

// échange le contenu de chaque ligne avec sa position miroir
void mirror_board() {
      for (int i = 0 ; i < board_size ; i++) {
        for (int j = 0 ; j < board_size / 2 ; j++) { // divise par 2 car on change la moitié des lignes
          // échange entre les premières et dernières lignes
          swap(&board[i][j].val, &board[i][board_size - 1 - j].val) ;
        }
    }
}

// échange les cases (i,j) avec (j,i)
void pivot_board() {
      for (int i = 0 ; i < board_size ; i++) {
        for (int j = i + 1 ; j < board_size ; j++) { // +1 car sinon c'est les même coordonées pendant le pivot         
          swap(&board[i][j].val, &board[j][i].val) ;     
        }
    }
}

int play(key dir) {
    int moved = 0 ;
    
    // Oriente le plateau au cas de compression vers la gauche
    switch (dir) {
        case KEY_LEFT:
            // Pas de transformation car le plateau est déjà orienté vers la gauche
            break;
        case KEY_RIGHT:
            mirror_board(); 
            break;
        case KEY_UP:
            pivot_board(); 
            break;
        case KEY_DOWN:
            pivot_board(); 
            mirror_board(); 
            break;
        default:
            break;
    }

    moved = update_board(); // compresse le plateau à gauche

    // Remet le plateau dans son orientation d'origine
    switch (dir) {
        case KEY_RIGHT:
            mirror_board(); 
            break;
        case KEY_UP:
            pivot_board(); 
            break;
        case KEY_DOWN:
            mirror_board(); 
            pivot_board(); 
            break;
        default:
            break;
    }
    return moved ;
}

// initialise le terminal
void INIT_2048() {
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    srand(time(NULL));
}

// rétabli le terminal et quitte le jeu
void DONE_2048() {
    endwin();
    exit(0);
}

int main() {
  
    int add = 1 ;
    INIT_2048();
    init_board();

       while(!game_over(add)) {
           key dir = get_key() ;        

        if ( play(dir) ) {
            display_board(); }        
        }
  
    DONE_2048();

    return 0;
}
