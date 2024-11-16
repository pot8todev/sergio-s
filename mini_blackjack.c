#include <stdio.h>
#include <stdlib.h>
#include <time.h> // for srand
#include <unistd.h>  // For usleep()kj

int randomDraw(int card_qnt[]){ // random number and decrements
    int min= 0, max=12;
    int count = 0;// overtime
    int random_number = (rand() % (max - min +1)) + min;// random the element POSITION
    while (card_qnt[random_number]<= 0)// if the POSITION have 0 cards or less, pull again and check again
    {
        random_number = (rand() % (max - min +1)) + min;
        if (count>100)
        {
            printf("\n Either we are out of cards or the dealer retired, go back another time.\n");
            random_number= 0;
            break;
        }
        
        count++;
    }

    card_qnt[random_number]-= 1;//finally, the place with >0 cards left is decremented
    return random_number;
}
int sum(int farray[], int max_count){// Function recives a farray, and sums its elements.
	float sum = 0;
	int i = 0;
	
	for(i=0; i<=(max_count); i++){  // sum == farr[0]+ farr[1]...
    	sum += farray[i];
	}
	
	//printf("\n a soma de todos os resultados é: %.1f ",sum); ~test
	return sum;
}
void memory(int deck_size, int card_qnt[], char card_names[]){
    for(int i=0; i<deck_size; i++){ 

    printf("%c : %d, \n",card_names[i], card_qnt[i]);

}

}

int main() {
    /*variaveis e operaçoes*/
    srand(time(NULL)); // seconds in the day since januwary 1st of 1970
    int i, j;
    int x ,card_pos = 0; // x stores the occult card /card_pos stores the randomDraw() number/
    int points = 0; //calculated at the end of each game
    int card_qnt[12];//deck de 12 cartas, o valor de cada carta sera preenchido o longo do código
    int card_value[] = {1,2,3,4,5,6,7,8,9,10,10,10,11}; //valor de cada carta, 10/j/Q/K have the same cost
    int deck_size = (sizeof(card_value)/sizeof(card_value[0]));
    char card_names[] = {'1','2','3','4','5','6','7','8','9','J','Q','K', 'A'};


    int hand_size = 1, playerHand[hand_size ], dealerHand[hand_size];// lists with the values in hand
    int player_sum = sum(playerHand, hand_size) , dealer_sum = sum(dealerHand,hand_size);

    int stopper = 0; // stopper, used both in the inner and outer loop

    /* deckGenerate() ALTERAVEL */
    for(i=0; i<deck_size; i++){ 
        card_qnt[i]=4; //considerando 1 deck
    }   

    printf("warning: \n A=11, J,Q,K = 10\n The house always profit. \n And deck remembers...\n\n");
    while (stopper == 0) 
    {      
        /* Draw randomly*/
        for(i = 0; i < 4; i++) //draws 4 cards, 2 for the player, 2 for the dealer
        { 
            card_pos = randomDraw(card_qnt); //card pulled from the position card_pos

            if(i<=1){ //dealer's hand
                dealerHand[i % 2] = card_value[card_pos];
                if (i == 0){
                    printf("D_%c D_@ \n",card_names[card_pos] );
                }
                if (i ==1){
                    x = card_names[card_pos]; // the card name is stored
                }
            }
            else if (i>1){ //players hand
                playerHand[i % 2] = card_value[card_pos]; 
                printf("P_%c ",card_names[card_pos]); 
            }
        }

        
        printf("\n one more card? 0 to proceed or 1 to stop: ");
        scanf(" %d",&stopper);
        /* players hit*/
        player_sum = sum(playerHand, hand_size);
        if (stopper == 0 && player_sum<=21)
        {        
            for (hand_size = 2; stopper == 0 ; hand_size++){ //infinite loop, do .push on hand_size
                card_pos= randomDraw(card_qnt);//draw
                playerHand[hand_size] = card_value[card_pos ]; //stores the card value in the latter memory address
                printf(" P_%c ",card_names[card_pos]); //show the name card just drawed

                player_sum = sum(playerHand, hand_size);
                if (sum(playerHand, hand_size)> 21){//if player busts
                    printf("\n");
                    for(int j = 0; j<=hand_size; j++){// show the players hand up to the last memory adress
                        printf(" P_%d +",playerHand[j]); //show the sum
                    }
                    printf("\n == %d BUSTED, the house wins", player_sum);
                    break;
                }             
                else{// if he choses to stop
                    printf("\n one more card? 0 to proceed or 1 to stop: ");
                    scanf(" %d",&stopper);
                    if (stopper == 1){ 
                        stopper=0; //player not busted, house will have to hit
                        break; 
                    }
                }
            }
        }

        player_sum = sum(playerHand, hand_size);
        dealer_sum = sum(dealerHand, 1);
        printf("\n the occult card was:\n D_%c\n", x);
        /* house's hit */
        if (player_sum <= 21 && dealer_sum<player_sum )// if player was busted, or de dealer already skip the step
        {
            for (hand_size = 2; stopper == 0 ; hand_size++){
            
                card_pos= randomDraw(card_qnt);//draw
                dealerHand[hand_size] = card_value[card_pos]; //stores the card value
                printf(" D_%c ",card_names[card_pos]);//show the name of the same card

                dealer_sum = sum(dealerHand, hand_size);
                if (dealer_sum>21){// house lost
                    printf("\n The house busted. The Player wins\n");
                    points = points + 100;
                    break;
                }   
                else if (dealer_sum>=player_sum)//house wins draws
                {
                    printf("\n the house always wins ...\n");
                    points = 0;
                    break;
                }
                
            }
        }
        else if(player_sum>21){ // busted player message
            printf("the house always wins...\n");
            points=0;
        }
        printf("you made %d$.\n\n the left cards int the deck are: \n", points);
        memory(deck_size,card_qnt,card_names);

        printf("\n one more game? 0 to proceed or 1 to stop \n");
        scanf(" %d",&stopper);
        if (stopper == 1){ // end of the game, dont need reseting
        break;
        }       
    }// quitting the game
    return 0;
}
