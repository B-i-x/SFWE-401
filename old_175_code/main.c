#define CRT_SECURE_NO_WARNINGS

#define DECK_SIZE 52

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include<time.h>


typedef struct card_s {
 char suit;
 int face;
 struct card_s *next;
} card;

void setup_game(char name[]);
void create_linked_list(card** head_p, card** tail, int count_of_cards);
void shuffleDeck(card* head_pt);

card dealCards(card* deck_pt, card* hand_head_pt, int card_index);
void deleteCard(card **h, card **t, int given_face, char given_suit);

void change_hand(card** hand_headp, card** deck_headp, card** deck_tail);

int check_hand(card* hand_head_pt, char winname[]);

void test_hand(card** hand_headp, char handtype[]);

void check_repeated(int bet_array[], card* hand_head_pt);
void check_flush(int bet_array[], card* hand_head_pt);
void check_straight(int bet_array[], card* hand_head_pt);
void check_fancy_flush(int bet_array[], card* hand_head_pt);



void print_list(card* pt, int input_type);
void print_cards(card *hand_headp);
void print_money(int bet, char name[]);
int deckCount(card* deck);
int get_bet(int money);


int main(void) {
  srand(time(0));

  char name[15];

  int bet, money = 100;

  setup_game(name);

  card* deck_headp = NULL, * decktail = NULL;
  create_linked_list(&deck_headp, &decktail, 52);

  card* hand_headp = NULL, * handtemp, * handtail = NULL;
  create_linked_list(&hand_headp, &handtail, 5);

  int i;
  for (i = 0; i <10000; i++) {
    shuffleDeck(deck_headp);
  }

  for (int j = 1; j < 6; ++j) {
    card card_dealt = dealCards(deck_headp, hand_headp, j);
    deleteCard(&deck_headp, &decktail, card_dealt.face, card_dealt.suit);
  }
  while (1) {
    printf("\n");
    print_money(money, name);
    printf("\n");
    bet = get_bet(money);
    if (bet == -1) {
      break;
    }
    printf("You bet %d coins\n\n", bet);
    
    printf("%s's hand:\n", name);
    //print_list(hand_headp, 0);
    print_cards(hand_headp);

    printf("\n");

    change_hand(&hand_headp, &deck_headp, &decktail);

    char win_string[30];
    
    int bet_scalar = check_hand(hand_headp, win_string);
      
    printf("\n%s's hand %s\n", name, win_string);

    print_cards(hand_headp);

    if (bet_scalar > 1) {
      money = money + (bet * bet_scalar);
      printf("\nYou WON %d coins and you now have %d coins\n", bet * bet_scalar, money);
    }

    if (bet_scalar == 0) {
      money = money - bet;
      printf("\nYou LOST and now you have %d coins\n", money);
    }

    if (money == 0) {
      printf("\nYou lost all your coins. Game Over!\n");
      break;
    }
    
    if (deckCount(deck_headp) < 20) {
      create_linked_list(&deck_headp, &decktail, 52);
      for (i = 0; i <10000; i++) {
        shuffleDeck(deck_headp);
      }
    }
    getchar();
    printf("\nHit Enter key to continue: ");
    if (getchar() != '\n') {
      break;
    }

    for (int j = 1; j < 6; ++j) {
      card card_dealt = dealCards(deck_headp, hand_headp, j);
      deleteCard(&deck_headp, &decktail, card_dealt.face, card_dealt.suit);
    }
  }

  printf("\nGoodbye %s", name);

  free(deck_headp);
  free(hand_headp);
  free(decktail);
  free(handtail);
  return 0;
}


void setup_game(char name[]) {
  char diamonds[30], spades[30], hearts[30], clubs[30], square[30];
  strcpy(diamonds, "\u2666\0");
  strcpy(spades, "\u2660\0");
  strcpy(hearts, "\u2665\0");
  strcpy(clubs, "\u2663\0");
  strcpy(square, "\u25A0\0");
  printf("Enter your name: ");
  scanf("%s", name);
  printf("\n$$$$$$$$$ $$$$$$$$$ $$$$$$$$$ $$$$$$$$$ $$$$$$$$$\n\t\t  $$$$$$$$$ $$$$$$$$$ $$$$$$$$$\n");
  printf("\t\t\t\t\t%s\n\t\t Let's play Two pairs or Better", name);
  printf("\n\t\t  $$$$$$$$$ $$$$$$$$$ $$$$$$$$$\n$$$$$$$$$ $$$$$$$$$ $$$$$$$$$ $$$$$$$$$ $$$$$$$$$\n");
  printf("$$$$$$$$$\t\t Rank of winning\t\t$$$$$$$$$\n");

  printf("\t\t\t\t\t\t\t\t\t\t\tPay\n");
  printf("Royal Flush\t\t 10%s J%s Q%s K%s A%s\t\t  250*bet\n", diamonds, diamonds, diamonds, diamonds, diamonds);
  printf("Straight Flush\t  2%s 3%s 4%s 5%s 6%s\t\t  100*bet\n", diamonds, diamonds, diamonds, diamonds, diamonds);
  printf("Four of a Kind\t  5%s 5%s 5%s 5%s  %s\t\t  50*bet\n", diamonds, spades, hearts, clubs, square);
  printf("Full House\t\t  8%s 8%s 8%s 2%s 2%s\t\t  25*bet\n", diamonds, spades, hearts, clubs, diamonds);
  printf("Flush     \t\t  %s%s %s%s %s%s %s%s %s%s\t\t  10*bet\n", square, diamonds, square, diamonds,square, diamonds,square, diamonds,square, diamonds);
  printf("Straight  \t\t  4%s 5%s 6%s 7%s 8%s\t\t  5*bet\n", square,  square, square, square, square);
  printf("Three of a Kind\t  7%s 7%s 7%s  %s  %s\t\t  4*bet\n", diamonds, spades, hearts, square, square);
  printf("Two Pair\t\t  K%s K%s 3%s 3%s  %s\t\t  2*bet\n", diamonds, spades, hearts, clubs, square);
}


void print_money(int money, char name[]) {
  /*
  this prints the amount that the person has
  */
  printf("\n********* *********  ********* *********  *********\n");
  printf("********* %s, you have %d coins *********\n", name, money);
  printf("********* *********  ********* *********  *********\n");
}


int get_bet(int money) {
  int bet = 0;
  while (1) {
    printf("Place your bet (1-%d) coins (-1 quit playing): ", money);
    scanf("%d", &bet);
    if (bet == -1) {
      return bet;
    }
    else if ((bet >= 0) && (bet <= money)) {
      return bet;
    }
  }
}


void create_linked_list(card** head_p, card** tail, int count_of_cards) {
    card* temp_card;

    char suit_list[4] = { 'S', 'H', 'D', 'C' };

    for (int i = 1; i <= count_of_cards; i++) {
        //allocate a memory for one node and make temp point to it. 
        temp_card = (card*)malloc(sizeof(card));
        //assign value i to the x member of temp

        int face = i % 13;

        int suit_index = i / 13;

        if (face == 0) {
          face = 13;
          suit_index = i / 13 - 1;
        }

        temp_card->face = face;
        temp_card->suit = suit_list[suit_index];
        if ((*head_p) == NULL) { //make headp point to the location that temp points to 
            (*head_p) = temp_card;
        }
        else {
            (*tail)->next = temp_card;//make next pointer member of tail point to temp
        }
        *tail = temp_card;// updating tail
        (*tail)->next = NULL;// setting next pt. of tail to null.
    }

}


void print_list(card* pt, int input_type) { 
    //prints the entire list 
    int cntr = 0;
    while (pt != NULL) {
      //printf("%d%c ", pt->face, pt->suit);
      //

      switch(pt->face) {
        case(1):
          printf("A");
          cntr ++;
          break;
        case(11):
          printf("J");
          cntr ++;
          break;
        case(12):
          printf("Q");
          cntr ++;
          break;
        case(13):
          printf("K");
          cntr ++;
          break;
        default:
          printf("%d", pt->face);
          cntr ++;
          break;
          
      }

      printf("%c ", pt->suit);
      if (input_type == 1) {
        if (cntr == 13) {
        printf("\n");
        cntr = 0;
        }
      }
      pt = pt->next;
    }
  printf("\n");
}


void print_cards(card *hand_headp) {

  char faces_array[5][3];

  char suits_array[5][10];

  int cntr = 0;

  while (hand_headp != NULL) {

    switch(hand_headp->face) {
      case(1):
        faces_array[cntr][0] = 'A';
        faces_array[cntr][1] = '\0';
        break;
      case(10):
        faces_array[cntr][0] = '1';
        faces_array[cntr][1] = '0';
        faces_array[cntr][2] = '\0';
        break;
      case(11):
        faces_array[cntr][0] = 'J';
        faces_array[cntr][1] = '\0';
        break;
      case(12):
        faces_array[cntr][0] = 'Q';
        faces_array[cntr][1] = '\0';
        break;
      case(13):
        faces_array[cntr][0] = 'K';
        faces_array[cntr][1] = '\0';
        break;
      default:
        faces_array[cntr][0] = hand_headp->face + '0';
        faces_array[cntr][1] = '\0';
        break;
        
    }

    switch(hand_headp->suit) {
      case('S'):
        strcpy(suits_array[cntr], "\u2660\0");
        break;
      case('H'):
        strcpy(suits_array[cntr], "\u2665\0");
        break;
      case('D'):
        strcpy(suits_array[cntr], "\u2666\0");
        break;
      case('C'):
        strcpy(suits_array[cntr], "\u2663\0");
        break;
    }

    ++cntr;
    hand_headp = hand_headp->next;
  }


  int j;
  printf("\n");
  for (j = 0; j < 5; j++) {
    printf("---------\t");
  }
  printf("\n");
  for (j = 0; j < 5; j++) {
    if (strcmp(faces_array[j], "10") == 0) {
      printf("| %s%s   |\t", faces_array[j], suits_array[j]);
    }
    else {
      printf("| %s%s    |\t", faces_array[j], suits_array[j]);
    }
  }
  printf("\n");
  for (j = 0; j < 5; j++) {
    printf("|       |\t");
  }
  printf("\n");
  for (j = 0; j < 5; j++) {
    if (strcmp(faces_array[j], "10") == 0) {
      printf("|    %s%s|\t", faces_array[j], suits_array[j]);
    }
    else {
      printf("|     %s%s|\t", faces_array[j], suits_array[j]);
    }
  }
  printf("\n");
  for (j = 0; j < 5; j++) {
    printf("---------\t");
  }

}


void shuffleDeck(card* head_pt) {
  int i_index = (rand() % DECK_SIZE);
  int j_index = (rand() % DECK_SIZE);

  int i, j;

  card* i_temp = head_pt, *j_temp = head_pt;
  for (i = 0; i < i_index; i++) {
    i_temp = i_temp->next;
  }
  for (j = 0; j < j_index; j++) {
    j_temp = j_temp->next;
  }

  char temp1_suit, temp2_suit;
  int temp1_face, temp2_face;

  temp1_suit = i_temp->suit;
  temp1_face = i_temp->face;
  temp2_suit = j_temp->suit;
  temp2_face = j_temp->face;

  i_temp->face = temp2_face;
  i_temp->suit = temp2_suit;
  j_temp->face = temp1_face;
  j_temp->suit = temp1_suit;

  
}


card dealCards(card* deck_pt, card* hand_head_pt, int card_index) {
  /*given an index (1-5) of the hand, it will take the first card of the deck and put it in that hand index*/
  int i;

  card* temp_deck_pt = deck_pt;
  card* temp_hand_pt = hand_head_pt;
  for (i = 1; i < card_index; ++i) {
    temp_hand_pt = temp_hand_pt->next;
    temp_deck_pt = temp_deck_pt->next;
  }
  hand_head_pt = temp_hand_pt;
  hand_head_pt->face = deck_pt->face;
  hand_head_pt->suit = deck_pt->suit;

  return (*hand_head_pt);
}


void deleteCard(card **h, card **t, int given_face, char given_suit){
  card *targetp= *h; // pointer to card to be deleted
  card *prev = *h; // namepointer to the head of the list
  while (targetp != NULL) {
    if (targetp->face != given_face && targetp->suit != given_suit) {
      targetp = targetp->next;
    }
    else {
      break;
    }
  }
  if (targetp == NULL) {
    return;
  }
  else {
    if (targetp == *h) {// if first card is to be deleted
      *h = targetp->next;
      } // update headp
    else {
      while ( prev->next != targetp)
      prev = prev->next; // find the card before the target card
      if (targetp == *t) { // if last card is to be deleted
      *t = prev;// update the tail
      (*t)->next = NULL;
      }
      else {
      prev->next = targetp->next; // skip card to be deleted
      }
  free(targetp); // free the memory
    }
  }
}

void test_hand(card** hand_headp, char handtype[]) {
  /*this is just to test certain hands*/
  card *temphand = *hand_headp;
  if (strcmp(handtype, "royal flush") == 0) {
    for (int i = 10; i < 14; ++i) {
      temphand->face = i;
      temphand->suit = 'C';
      temphand = temphand->next;
    }
    temphand->suit = 'C';
    temphand->face = 1;
  }
  else if (strcmp(handtype, "straight flush") == 0) {
    for (int i = 7; i < 11; ++i) {
      temphand->face = i;
      temphand->suit = 'C';
      temphand = temphand->next;
    }
    temphand->suit = 'C';
    temphand->face = 11;
  }
  else if (strcmp(handtype, "flush") == 0) {
    for (int i = 0; i < 4; ++i) {
      temphand->suit = 'C';
      temphand = temphand->next;
    }
    temphand->suit = 'C';
  }
  else if (strcmp(handtype, "straight") == 0) {
    for (int i = 1; i < 5; ++i) {
      temphand->face = i;
      temphand = temphand->next;
    }
    temphand->suit = 5;
  }
  else if (strcmp(handtype, "poker") == 0) {
    for (int i = 1; i < 5; ++i) {
      temphand->face = 8;
      temphand = temphand->next;
    }
    temphand->suit = 5;
  }
  else if (strcmp(handtype, "FH") == 0) {
    for (int i = 1; i < 4; ++i) {
      temphand->face = 9;
      temphand = temphand->next;
    }
    temphand->face = 5;
    temphand = temphand->next;
    temphand->face = 5;
  }

  //print_cards(hand_head_pt);

}


void change_hand(card** hand_headp, card** deck_headp, card** deck_tail) {
  /*this function allows the user to change his hand
  the idea is that the keep array has 5 ints, each represents one card
  if the index of the array is 0 then that card index in that hand stays the same. if it is 1 then that card index will be dealt a new hand
  */
  int keep[5] = {0,0,0,0,0}; 
  int cnt = 0, entered_inp, i;

  while (entered_inp != -1) {
    printf("Pick cards (between 1-5) to hold (-1 to stop): ");
    scanf("%d", &entered_inp);

    if (entered_inp != -1) {
      keep[entered_inp-1] = 1;
    }

    cnt++;
    
  } 
  cnt = 0;

  for (i = 0; i < 5; ++i) {
    if (1 != keep[i]) {
      card card_dealt = dealCards(*deck_headp, *hand_headp, i+1);
      deleteCard(deck_headp, deck_tail, card_dealt.face, card_dealt.suit);
    }
  }
}


void check_repeated(int bet_array[], card* hand_head_pt) {
  int hand_face_copy[5], hand_face_copy2[5];
  card* temp_deck_pt = hand_head_pt;

  for (int i = 0; i < 5; ++i) {
    hand_face_copy[i] = temp_deck_pt->face;
    hand_face_copy2[i] = hand_face_copy[i];

    temp_deck_pt = temp_deck_pt->next;
  }

  int count_arr[5];
  int count_of_card = 0;

  for (int i = 0; i < 5; ++i) {
    int compared_face = hand_face_copy[i];
    count_of_card = 0;

    for (int j = 0; j < 5; ++j) {
      if (hand_face_copy[i] == hand_face_copy2[j]) {
        ++count_of_card;
      }
    }
    
    count_arr[i] = count_of_card;
  }
  
  int pair = 0;
  int triple = 0;
  int four = 0;

  for (int i = 0; i < 5; ++i) {
    if (count_arr[i] == 2) {
      ++pair;
    }
    else if (count_arr[i] == 3) {
      ++triple;
    }
    else if (count_arr[i] == 4) {
      ++four;
    }
  }

  if (pair == 4) {
    bet_array[7] = 2;
  }
  else {
    bet_array[7] = 1;
  }

  if (triple == 3) {
    bet_array[6] = 4;
  }
  else {
    bet_array[6] = 1;
  }

  if ((pair == 2) && (triple == 3)) {
    bet_array[3] = 25;
  }
  else {
    bet_array[3] = 1;
  }

  if (four == 4) {
    bet_array[2] = 50;
  }
  else {
    bet_array[2] = 1;
  }


}


void check_flush(int bet_array[], card* hand_head_pt) {
  char suits[5];
  int i;
  int flag = 0;
  int cnt = 0;
  card* temp_deck_pt = hand_head_pt;
  for (i = 0; i < 5; ++i) {
    suits[i] = temp_deck_pt->suit;
    temp_deck_pt = temp_deck_pt->next;
  }
  for (i = 1; i < 5; ++i) {
    if (suits[i] == suits[i - 1]) {
      cnt = cnt + 1;
    }
    else {
      bet_array[4] = 1;
      break;
    }
  }
  if (cnt == 4) {
    bet_array[4] = 10;
  }
}


void swap(int* min, int* ind){
    int temp = *min;
    *min = *ind;
    *ind = temp;
}


void selectionSort(int arr[], int n){
    int i, j, min;
    for (i = 0; i < n - 1; i++) {
      min = i;
      for (j = i + 1; j < n; j++) {
        if (arr[j] < arr[min]) {
          min = j;
          swap(&arr[min], &arr[i]);
        }
      }
    }
}


//check straight function!!!
void check_straight(int bet_array[], card* hand_head_pt){
  int faces[5];
  int i, max;
  int cnt = 0;
  card* temp_deck_pt = hand_head_pt;
  for (i = 0; i < 5; ++i) {
    faces[i] = temp_deck_pt->face;
    temp_deck_pt = temp_deck_pt->next;
  }
  selectionSort(faces, 5);
  for (i = 1; i < 5; ++i) {
    if (faces[i] == faces[i - 1] + 1) {
      cnt = cnt + 1;
    }
    else {
      bet_array[5] = 1;
      break;
    }
  }
  if (cnt == 4) {
    bet_array[5] = 5;
  }

  if (faces[0] == 1 && faces[1] == 10 && faces[2] == 11 && faces[3] == 12 && faces[4] == 13) {
    bet_array[5] = 5;
  }
}

void check_fancy_flush(int bet_array[], card* hand_head_pt) {

  int first_face = hand_head_pt->face;
  if ((bet_array[5] == 5 && (bet_array[4] == 10)) && first_face!= 10) {
    bet_array[1] = 100;
  }
  else if ((bet_array[5] == 5 && (bet_array[4] == 10)) && first_face== 10) {
    bet_array[0] = 250;
  }
}

int check_hand(card* hand_head_pt, char winname[]) {
  /*this function returns the scalar multiplied to the bet that will be payed out
  going down the list of winning hands, if one is detected, it will return the appropriate betting scalar
  if royal flush == true
    return 250
  else if straight flush  == true
    return 100
  */

  //test_hand(&hand_head_pt, "flush");
  //test_hand(&hand_head_pt, "straight");
  //test_hand(&hand_head_pt, "straight flush"); 
  //test_hand(&hand_head_pt, "royal flush");
  //test_hand(&hand_head_pt, "poker");
  //test_hand(&hand_head_pt, "FH");

  int bet_scalar_arr[8] = {0,0,0,0,0,0,0,0};

  check_repeated(bet_scalar_arr, hand_head_pt);

  check_flush(bet_scalar_arr, hand_head_pt);

  check_straight(bet_scalar_arr, hand_head_pt);

  check_fancy_flush(bet_scalar_arr, hand_head_pt);

  int max_scalar = 1;

  for (int i = 0; i < 8; ++i) {
    if (bet_scalar_arr[i] > max_scalar) {
      max_scalar = bet_scalar_arr[i];
    }
  }

  switch (max_scalar) {
    case (2):
      strcpy(winname, "(Two Pair)");
      break;
    case (4):
      strcpy(winname, "(Three of a Kind)");
      break;
    case (5):
      strcpy(winname, "(Straight)");
      break;
    case (10):
      strcpy(winname, "(Flush)");
      break;
    case (25):
      strcpy(winname, "(Full House)");
      break;
    case (50):
      strcpy(winname, "(Four of a Kind)");
      break;
    case (100):
      strcpy(winname, "(Straight Flush)");
      break;
    case (250):
      strcpy(winname, "(Royal Flush)");
      break;
    case(1):
      strcpy(winname, "");
      max_scalar = 0;
      break;
  }
  
  return max_scalar;  
}


int deckCount(card* deck_headp){
  int num = 0; 
  card* temp_deck_pt = deck_headp;
  while (temp_deck_pt != NULL) {
    num = num + 1;
    temp_deck_pt = temp_deck_pt->next;
  }
  return num;
}

