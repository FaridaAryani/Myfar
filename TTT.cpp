#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
	char Nama[100];
	int Skor;
}Player;
typedef struct{
    char AngkaAwal[50];
    int Dimensi;
    int sisakotak;
}papan;

papan Board;
void Tampil();
void input(int *input);
void Keluar();
void Rules();
void CetakNama(Player *Player1, Player *Player2);
void Level();
void CetakMenang(const char* NamaPemenang);
void Papan1(Player *Player1, Player *Player2);
int cekKondisiWin1(char AngkaAwal[10]);
void Papan2(Player *Player1, Player *Player2);
int cekKondisiWin2(char AngkaAwal[26]);
void Papan3(Player *Player1, Player *Player2);
int cekKondisiWin3(char AngkaAwal[50]);
void Leaderboard(Player *Player1, Player *Player2);
void CetakMenang(const char* NamaPemenang);
void CetakDraw();
void CetakSisa(int *sisakotak);
int CetakMainLagi();
void CekValid();

void Tampil(){
	printf("Tic Tac Toe\n");
	printf("Pilih salah satu\n");
	printf("1. Game\n");
	printf("2. Peraturan\n");
	printf("3. LeaderBoard\n");
	printf("4. Keluar\n");
}
void input(int *input){
    while (1) {
        printf("Masukkan angka: ");
        if (scanf("%d", input) == 1) {
            break;
        } else {
            printf("Input tidak valid. Harap masukkan angka.\n");
            while(getchar() != '\n'); 
        }
    }
    printf("Anda memasukkan: %d\n", *input);
	}
void Keluar(){
	printf("Nanti main lagi yakk");
}
void Rules(){
	printf("\t\t\t\t\t=========================================\n\n");
	printf("\t==========================================================================================================\n");
	printf("\t||                                                                                                      ||\n");
    printf("\t|| 1. Player memilih opsi 1 untuk memulai permainan.\t\t\t\t\t\t\t||\n");
	printf("\t|| 2. Player akan diminta mengisi nama.\t\t\t\t\t\t\t\t\t||\n");
    printf("\t|| 3. Player akan diminta memilih dimensi board yang akan dimainkan.\t\t\t\t\t||\n");
	printf("\t|| 4. Player akan diminta menginput baris dan kolom, sesuai dengan kotak yang ingin di isi \t\t||\n");
	printf("\t|| 5. Player akan diberi waktu selama 10 detik untuk mengisi kotak.\t\t\t\t\t||\n");
	printf("\t|| 6. Player tidak bisa mengisi kotak yang sudah terisi sebelumnya, jika terisi maka akan invalid.   \t||\n");
    printf("\t|| 7. Player tidak bisa menginput baris/kolom diluar jangkauan board yang dipilih,    \t\t\t||\n");
    printf("\t||     jika dipilih maka akan invalid.    \t\t\t\t\t\t\t\t||\n");
	printf("\t|| 8. Player dinyatakan menang jika bisa membuat garis pertama secara horizontal,vertikal, \t\t||\n");
    printf("\t||     ataupun diagonal dari 3,4, atau 5 bidaknya (sesuai dimensi yang dipilih).   \t\t\t||\n");
	printf("\t|| 9. Permainan dinyatakan draw jika board sudah terisi penuh dan keduanya tidak membuat \t\t||\n");
    printf("\t||     3,4, atau 5 bidaknya (sesuai dimensi yang dipilih).   \t\t\t\t\t\t||\n");
	printf("\t|| 10. Player dinyatakan kalah jika lawan yang pertama membuat garis dari ketiga bidaknya.         \t||\n");
    printf("\t|| 11. Jika game sudah selesai, player akan diberikan pilihan untuk kembali main atau tidak.    \t||\n");
	printf("\t||                                                                                                      ||\n");
	printf("\t||======================================================================================================||\n\n");
	printf("\n\n\t Kembali(00) : ");
}
void CetakNama(Player *Player1, Player *Player2){
	printf("Nama Pemain 1(X):\n");
	scanf("%s",Player1->Nama);
	printf("Nama Pemain 2(O):\n");
	scanf("%s",Player2->Nama);
}
void Level(){
	printf("Pilih salah satu\n");
	printf("1. 3x3\n");
	printf("2. 5x5\n");
	printf("3. 7x7\n");
}

void Papan1(Player *Player1, Player *Player2) {
    int sisakotak = 9;
    char AngkaAwal[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int urut, Kotak, counter, win,aftergame,awalgame;
    char board[3][3];
	int cekKondisiWin1(char AngkaAwal[10]);
	void CetakDraw();
	time_t waktu, waktusesudah;
	void CetakSisa(int *sisakotak);
	void Leaderboard(Player *Player1, Player *Player2);
	int CetakMainLagi();
	void CekValid();
	int skorPlayer1 = 0;
	int skorPlayer2 = 0;

    printf("\n\n\t\t   sisa kotak= %d", sisakotak);
    printf("\n\t         |               |             \n");
    printf(" \t   %c\t | \t%c\t |   %c\t\n", AngkaAwal[1], AngkaAwal[2], AngkaAwal[3]);
    printf("\t         |               |             \n");
    printf("\t---------+---------------+---------\n");
    printf("\t         |               |             \n");
    printf(" \t   %c\t | \t%c\t |   %c\t\n", AngkaAwal[4], AngkaAwal[5], AngkaAwal[6]);
    printf("\t         |               |             \n");
    printf("\t---------+---------------+---------\n");
    printf("\t         |               |             \n");
    printf(" \t   %c\t | \t%c\t\t |   %c\t\n", AngkaAwal[7], AngkaAwal[8], AngkaAwal[9]);
    printf("\t         |               |             \n\n");

for (urut = 1; urut < 10; urut++) {
	win = 0;
        if (urut % 2 == 1) {
            printf("%s Turn\n", Player1->Nama);
            printf("Masukkan Kotak[1..9]:");
            scanf("%d", &Kotak);
            waktusesudah = time(NULL);

            if ((AngkaAwal[Kotak] == 'X') || (AngkaAwal[Kotak] == 'O')) {
                printf("Jangan ngisi Kotak yang ini!!!!\n");
                printf("Yang lain aja!!!");
            } else {
                AngkaAwal[Kotak] = 'X';
                sisakotak = sisakotak - 1;
                printf("\n\t\t   sisa kotak= %d", sisakotak);
                printf("\n\t         |               |             \n");
                printf(" \t   %c\t | \t%c\t |   %c\t\n", AngkaAwal[1], AngkaAwal[2], AngkaAwal[3]);
                printf("\t         |               |             \n");
                printf("\t---------+---------------+---------\n");
                printf("\t         |               |             \n");
                printf(" \t   %c\t | \t%c\t |   %c\t\n", AngkaAwal[4], AngkaAwal[5], AngkaAwal[6]);
                printf("\t         |               |             \n");
                printf("\t---------+---------------+---------\n");
                printf("\t         |               |             \n");
                printf(" \t   %c\t | \t%c\t\t |   %c\t\n", AngkaAwal[7], AngkaAwal[8], AngkaAwal[9]);
                printf("\t         |               |             \n\n");
            }
            win = cekKondisiWin1(AngkaAwal);
			if(win == 1){
			CetakMenang(Player1->Nama);
			Player1->Skor = Player1->Skor++;
			break;
			}
        } else {
            printf("%s Turn", Player2->Nama);
            counter = 0;
            while (counter == 0) {
                printf("\nMasukkan Kotak [1...9]: ");
                scanf("%d", &Kotak);
                waktusesudah = time(NULL);
                if(waktusesudah - waktu >= 10){
                	printf("Waktu Habis!!\n");
                	sisakotak = sisakotak +1;
                	counter = 1;
				} else{
					system("cls");
					counter = 1;
					Board.AngkaAwal[10] = 'X';
					printf("\n\t\t   sisa kotak= %d", sisakotak);
               		printf("\n\t         |               |             \n");
                	printf(" \t   %c\t | \t%c\t |   %c\t\n", AngkaAwal[1], AngkaAwal[2], AngkaAwal[3]);
                	printf("\t         |               |             \n");
                	printf("\t---------+---------------+---------\n");
                	printf("\t         |               |             \n");
                	printf(" \t   %c\t | \t%c\t |   %c\t\n", AngkaAwal[4], AngkaAwal[5], AngkaAwal[6]);
                	printf("\t         |               |             \n");
                	printf("\t---------+---------------+---------\n");
                	printf("\t         |               |             \n");
                	printf(" \t   %c\t | \t%c\t\t |   %c\t\n", AngkaAwal[7], AngkaAwal[8], AngkaAwal[9]);
                	printf("\t         |               |             \n\n");
					Board.sisakotak = sisakotak--;
					CetakSisa(&sisakotak);
				}
                
                if ((AngkaAwal[Kotak] == 'X') || (AngkaAwal[Kotak] == 'O')) {
                    printf("Invalid Move!!!\n");
                } else {
                    counter = 1;
                    AngkaAwal[Kotak] = 'O';
                    sisakotak = sisakotak - 1;
                    printf("\n\t\t   sisa kotak= %d", sisakotak);
                    printf("\n\t         |               |             \n");
                    printf(" \t   %c\t | \t%c\t |   %c\t\n", AngkaAwal[1], AngkaAwal[2], AngkaAwal[3]);
                    printf("\t         |               |             \n");
                    printf("\t---------+---------------+---------\n");
                    printf("\t         |               |             \n");
                    printf(" \t   %c\t | \t%c\t |   %c\t\n", AngkaAwal[4], AngkaAwal[5], AngkaAwal[6]);
                    printf("\t         |               |             \n");
                    printf("\t---------+---------------+---------\n");
                    printf("\t         |               |             \n");
                    printf(" \t   %c\t | \t%c\t\t |   %c\t\n", AngkaAwal[7], AngkaAwal[8], AngkaAwal[9]);
                    printf("\t         |               |             \n\n");
                }
            }
            win = cekKondisiWin1(AngkaAwal);
            if(win == 2){
            	CetakMenang(Player2->Nama);
            	Player2->Skor= Player2->Skor++;
            	break;
			}
		}
	}
	if(win == 0){
			CetakDraw();
	}
	counter = 0;
	while(counter==0){
                                aftergame = CetakMainLagi();
                                if(aftergame>2){
                                	system("cls");
                                    CekValid();
                                }
                    			
                                if(aftergame==1){
                                	system("cls");
                                    awalgame=1;
                                    counter=1;
                                    win=0;
                                }
                                else if(aftergame==2){
                                	system("cls");
                                    awalgame=00;
                                    counter=1;
                                    win=0;
                                }
                            }
}

int cekKondisiWin1(char AngkaAwal[10]){
if(AngkaAwal[1]=='X' && AngkaAwal[2]=='X' && AngkaAwal[3] == 'X'){                  //Kondisi Menang untuk Player 1
        	return 1;
        } 
        else if(AngkaAwal[4]=='X' && AngkaAwal[5]=='X' && AngkaAwal[6] == 'X'){
        	return 1;
        }
        else if(AngkaAwal[7]== 'X' && AngkaAwal[8]=='X' && AngkaAwal[9]== 'X'){
        	return 1;
        }
        else if(AngkaAwal[1]=='X' && AngkaAwal[4]== 'X' && AngkaAwal[7] == 'X'){
        	return 1;
        }
        else if(AngkaAwal[2]=='X' && AngkaAwal[5]== 'X' && AngkaAwal[8] == 'X'){
        	return 1;
        }
        else if(AngkaAwal[3]=='X' && AngkaAwal[6]=='X' && AngkaAwal[9]== 'X'){
        	return 1;
        }
        else if(AngkaAwal[1] =='X' && AngkaAwal[5]=='X' && AngkaAwal[9]== 'X'){
        	return 1;
        }
        else if(AngkaAwal[3] =='X' && AngkaAwal[5]=='X' && AngkaAwal[7]== 'X'){
        	return 1;
        }
        else if(AngkaAwal[1] =='O' && AngkaAwal[2]=='O' && AngkaAwal[3] == 'O'){                  //Kondisi Menang untuk Player 2
        	return 2;
        } 
        else if(AngkaAwal[4] =='O' && AngkaAwal[5]=='O' && AngkaAwal[6] == 'O'){
        	return 2;
        }
        else if(AngkaAwal[7] == 'O' && AngkaAwal[8]=='O' && AngkaAwal[9] == 'O'){
        	return 2;
        }
        else if(AngkaAwal[1] =='O' && AngkaAwal[4]== 'O' && AngkaAwal[7] == 'O'){
        	return 2;
        }
        else if(AngkaAwal[2] =='O' && AngkaAwal[5]== 'O' && AngkaAwal[8] == 'O'){
        	return 2;
        }
        else if(AngkaAwal[3] =='O' && AngkaAwal[6]=='O' && AngkaAwal[9] == 'O'){
        	return 2;
        }
        else if(AngkaAwal[1] =='O' && AngkaAwal[5]=='O' && AngkaAwal[9] == 'O'){
        	return 2;
        }
        else if(AngkaAwal[3] =='O' && AngkaAwal[5]=='O' && AngkaAwal[7]== 'O'){
            return 2;
        }
        else{
            return 0;
        }
}


void Papan2(Player *Player1, Player *Player2){
	int sisakotak = 25;
	char AngkaAwal[26]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25};
	int urut, Kotak, counter, win;
	char board[5][5];
	int cekKondisiWin2(char AngkaAwal[26]);
	void CetakDraw();
	
	int skorPlayer1 = 0;
	int skorPlayer2 = 0;
	
	printf("\n\n\t\t   sisa kotak= %d", sisakotak);
    printf("\n\t         |               |               |               |               \n");
    printf(" \t   %c\t | \t%c\t |   %c\t\t |   %c\t\t | %c\t\n",AngkaAwal[1],AngkaAwal[2],AngkaAwal[3],AngkaAwal[4],AngkaAwal[5]);
    printf("\t         |               |               |               |               \n");
    printf("\t---------+---------------+---------------+---------------+---------------\n");
    printf("\t         |               |               |               |               \n");
    printf("\t   %c\t | \t%c\t |   %c\t\t |   %c\t | %c",AngkaAwal[6],AngkaAwal[7],AngkaAwal[8],AngkaAwal[9],AngkaAwal[10]);
    printf("\t         |               |               |               |               \n");
    printf("\t---------+---------------+---------------+---------------+---------------\n");
    printf("\t         |               |               |               |               \n");
    printf("\t   %c\t | \t%c\t |   %c\t\t |   %c\t\t | %c\t\n",AngkaAwal[11],AngkaAwal[12],AngkaAwal[13],AngkaAwal[14],AngkaAwal[15]);
    printf("\t         |               |               |               |               \n");
    printf("\t---------+---------------+---------------+---------------+---------------\n");
    printf("\t         |               |               |               |               \n");
    printf(" \t   %c\t | \t%c\t |   %c\t\t |   %c\t\t | %c\t\n",AngkaAwal[16],AngkaAwal[17],AngkaAwal[18],AngkaAwal[19],AngkaAwal[20]);
    printf("\t         |               |               |               |               \n");
    printf("\t---------+---------------+---------------+---------------+---------------\n");
    printf("\t         |               |               |               |               \n");
    printf("\t   %c\t | \t%c\t |   %c\t\t |   %c\t\t | %c\t\n", AngkaAwal[21], AngkaAwal[22], AngkaAwal[23], AngkaAwal[24], AngkaAwal[25]);
    printf("\t         |               |               |               |               \n");
    
    for (urut = 1; urut < 26; urut++) {
    	win = 0;
        if (urut % 2 == 1) {
            printf("%s Turn", Player1->Nama);
            printf("Masukkan Kotak[1..25]:");
            scanf("%d", &Kotak);

            if ((AngkaAwal[Kotak] == 'X') || (AngkaAwal[Kotak] == 'O')) {
                printf("Jangan ngisi Kotak yang ini!!!!\n");
                printf("Yang lain aja!!!");
            }else{
            	AngkaAwal[Kotak]='X';
            	sisakotak = sisakotak - 1;
            	printf("\n\n\t\t   sisa kotak= %d", sisakotak);
   				printf("\n\t         |               |               |               |               \n");
    			printf("\t   %c\t | \t%c\t |   %c\t\t |   %c\t\t | %c\t\n",AngkaAwal[1],AngkaAwal[2],AngkaAwal[3],AngkaAwal[4],AngkaAwal[5]);
    			printf("\t         |               |               |               |               \n");
    			printf("\t---------+---------------+---------------+---------------+---------------\n");
    			printf("\t         |               |               |               |               \n");
    			printf("\t   %c\t | \t%c\t |   %c\t\t |   %c\t\t | %c\t\n",AngkaAwal[6],AngkaAwal[7],AngkaAwal[8],AngkaAwal[9],AngkaAwal[10]);
    			printf("\t         |               |               |               |               \n");
    			printf("\t---------+---------------+---------------+---------------+---------------\n");
    			printf("\t         |               |               |               |               \n");
    			printf("\t   %c\t | \t%c\t |   %c\t\t |   %c\t\t | %c\t\n",AngkaAwal[11],AngkaAwal[12],AngkaAwal[13],AngkaAwal[14],AngkaAwal[15]);
    			printf("\t         |               |               |               |               \n");
    			printf("\t---------+---------------+---------------+---------------+---------------\n");
    			printf("\t         |               |               |               |               \n");
    			printf("\t   %c\t | \t%c\t |   %c\t\t |   %c\t\t | %c\t\n",AngkaAwal[16],AngkaAwal[17],AngkaAwal[18],AngkaAwal[19],AngkaAwal[20]);
    			printf("\t         |               |               |               |               \n");
    			printf("\t---------+---------------+---------------+---------------+---------------\n");
    			printf("\t         |               |               |               |               \n");
    			printf("\t   %c\t | \t%c\t |   %c\t\t |   %c\t\t | %c\t\n",AngkaAwal[21],AngkaAwal[22],AngkaAwal[23],AngkaAwal[24],AngkaAwal[25]);
    			printf("\t         |               |               |               |               \n\n");
			}
			win = cekKondisiWin2(AngkaAwal);
			if(win == 1){
				CetakMenang(Player1->Nama);
				Player1->Skor = Player1->Skor++;
				break;
			}
		}else {
            printf("%s Turn", Player2->Nama);
            counter = 0;
            while (counter == 0) {
                printf("\nMasukkan Kotak[1...25]: ");
                scanf("%d", &Kotak);

                if ((AngkaAwal[Kotak] == 'X') || (AngkaAwal[Kotak] == 'O')) {
                    printf("Invalid Move!!!\n");
                } else {
                    counter = 1;
                    AngkaAwal[Kotak] = 'O';
                    sisakotak = sisakotak - 1;
                   printf("\n\n\t\t   sisa kotak= %d", sisakotak);
   				printf("\n\t         |               |               |               |               \n");
    			printf(" \t   %c\t | \t%c\t |   %c\t\t |   %c\t\t | %c\t\n",AngkaAwal[1],AngkaAwal[2],AngkaAwal[3],AngkaAwal[4],AngkaAwal[5]);
    			printf("\t         |               |               |               |               \n");
    			printf("\t---------+---------------+---------------+---------------+---------------\n");
    			printf("\t         |               |               |               |               \n");
    			printf(" \t   %c\t | \t%c\t |   %c\t\t |   %c\t\t | %c\t\n",AngkaAwal[6],AngkaAwal[7],AngkaAwal[8],AngkaAwal[9],AngkaAwal[10]);
    			printf("\t         |               |               |               |               \n");
    			printf("\t---------+---------------+---------------+---------------+---------------\n");
    			printf("\t         |               |               |               |               \n");
    			printf(" \t   %c\t | \t%c\t |   %c\t\t |   %c\t\t | %c\t\n",AngkaAwal[11],AngkaAwal[12],AngkaAwal[13],AngkaAwal[14],AngkaAwal[15]);
    			printf("\t         |               |               |               |               \n");
    			printf("\t---------+---------------+---------------+---------------+---------------\n");
    			printf("\t         |               |               |               |               \n");
    			printf(" \t   %c\t | \t%c\t |   %c\t\t |   %c\t\t | %c\t\n",AngkaAwal[16],AngkaAwal[17],AngkaAwal[18],AngkaAwal[19],AngkaAwal[20]);
    			printf("\t         |               |               |               |               \n");
    			printf("\t         |               |               |               |               \n");
    			printf("\t---------+---------------+---------------+---------------+---------------\n");
    			printf("\t         |               |               |               |               \n");
    			printf(" \t   %c\t | \t%c\t |   %c\t\t |   %c\t\t | %c\t\n",AngkaAwal[21],AngkaAwal[22],AngkaAwal[23],AngkaAwal[24],AngkaAwal[25]);
    			printf("\t         |               |               |               |               \n\n");
    		}
    	}
    	win = cekKondisiWin2(AngkaAwal);
    	if(win == 2){
    		CetakMenang(Player2->Nama);
    		Player2->Skor = Player2->Skor++;
    		break;
			}
    	}
	}
	if(win == 0){
		CetakDraw();
	}
}
int cekKondisiWin2(char AngkaAwal[26]){
if(AngkaAwal[1]=='X' && AngkaAwal[2]=='X' && AngkaAwal[3] == 'X' && AngkaAwal[4] == 'X'){                  //Kondisi Menang untuk Player 1
            return 1;
        } 
        else if(AngkaAwal[6]=='X' && AngkaAwal[7]=='X' && AngkaAwal[8] == 'X' && AngkaAwal[9] == 'X'){
             return 1;
        }
        else if(AngkaAwal[11]== 'X' && AngkaAwal[12]=='X' && AngkaAwal[13]== 'X' && AngkaAwal[14] == 'X'){
             return 1;
        }
        else if(AngkaAwal[16]=='X' && AngkaAwal[17]== 'X' && AngkaAwal[18] == 'X' && AngkaAwal[19] == 'X'){
             return 1;
        }
        else if(AngkaAwal[21]=='X' && AngkaAwal[22]== 'X' && AngkaAwal[23] == 'X' && AngkaAwal[24] == 'X'){
             return 1;
        }
        else if(AngkaAwal[2]=='X' && AngkaAwal[3]=='X' && AngkaAwal[4]== 'X' && AngkaAwal[5] == 'X'){
             return 1;
         }
        else if(AngkaAwal[7]=='X' && AngkaAwal[8]=='X' && AngkaAwal[9]== 'X' && AngkaAwal[10] == 'X'){
             return 1;
        }
        else if(AngkaAwal[12]=='X' && AngkaAwal[13]=='X' && AngkaAwal[14]== 'X' && AngkaAwal[15] == 'X'){
             return 1;
        }
        else if(AngkaAwal[17]=='X' && AngkaAwal[18]=='X' && AngkaAwal[19] == 'X' && AngkaAwal[20] == 'X'){                  
             return 1;
        } 
        else if(AngkaAwal[22]=='X' && AngkaAwal[23]=='X' && AngkaAwal[24] == 'X' && AngkaAwal[25] == 'X'){
             return 1;
        }
        else if(AngkaAwal[1]== 'X' && AngkaAwal[6]=='X' && AngkaAwal[11] == 'X' && AngkaAwal[16] == 'X'){
             return 1;
        }
        else if(AngkaAwal[6]=='X' && AngkaAwal[11]== 'X' && AngkaAwal[16] == 'X' && AngkaAwal[21] == 'X'){
             return 1;
        }
        else if(AngkaAwal[2]=='X' && AngkaAwal[7]== 'X' && AngkaAwal[12] == 'X' && AngkaAwal[17] == 'X'){
             return 1;
        }
        else if(AngkaAwal[7]=='X' && AngkaAwal[12]=='X' && AngkaAwal[17] == 'X' && AngkaAwal[22] == 'X'){
             return 1;
         }
        else if(AngkaAwal[3]=='X' && AngkaAwal[8]=='X' && AngkaAwal[13] == 'X' && AngkaAwal[18] == 'X'){
             return 1;
        }
        else if(AngkaAwal[8]=='X' && AngkaAwal[13]=='X' && AngkaAwal[18]== 'X' && AngkaAwal[23] == 'X'){
            return 1;
        }
        else if(AngkaAwal[4] == 'X' && AngkaAwal[9] == 'X' && AngkaAwal[14] == 'X' && AngkaAwal[19] == 'X'){
        	return 1;
		}
		else if(AngkaAwal[9] == 'X' && AngkaAwal[14] == 'X' && AngkaAwal[19] == 'X' && AngkaAwal[24] == 'X'){
			return 1;
		}
		else if(AngkaAwal[5] == 'X' && AngkaAwal[10] == 'X' && AngkaAwal[15] == 'X' && AngkaAwal[20] == 'X'){
			return 1;
		}
		else if(AngkaAwal[10] == 'X' && AngkaAwal[15] == 'X' && AngkaAwal[20] == 'X' && AngkaAwal[25] == 'X'){
			return 1;
		}
		else if(AngkaAwal[1] == 'X' && AngkaAwal[7] == 'X' && AngkaAwal[13] == 'X' && AngkaAwal[19] == 'X'){
			return 1;
		}
		else if(AngkaAwal[7] == 'X' && AngkaAwal[13] == 'X' && AngkaAwal[19] == 'X' && AngkaAwal[25] == 'X'){
			return 1;
		}
		else if(AngkaAwal[2] == 'X' && AngkaAwal[8] == 'X' && AngkaAwal[14] == 'X' && AngkaAwal[20] == 'X'){
			return 1;
		}
		else if(AngkaAwal[6] == 'X' && AngkaAwal[12] == 'X' && AngkaAwal[18] == 'X' && AngkaAwal[24] == 'X'){
			return 1;
		}
		else if(AngkaAwal[5] == 'X' && AngkaAwal[9] == 'X' && AngkaAwal[13] == 'X' && AngkaAwal[17] == 'X'){
			return 1;
		}
		else if(AngkaAwal[9] == 'X' && AngkaAwal[13] == 'X' && AngkaAwal[17] == 'X' && AngkaAwal[21] == 'X'){
			return 1;
		}
		else if(AngkaAwal[4] == 'X' && AngkaAwal[8] == 'X' && AngkaAwal[12] == 'X' && AngkaAwal[16] == 'X'){
			return 1;
		}
		else if(AngkaAwal[10] == 'X' && AngkaAwal[14] == 'X' && AngkaAwal[18] == 'X' && AngkaAwal[23] == 'X'){
			return 1;
		}
		else if(AngkaAwal[1]=='O' && AngkaAwal[2]=='O' && AngkaAwal[3] == 'O' && AngkaAwal[4] == 'O'){                  //Kondisi Menang untuk Player 2
            return 2;
        } 
        else if(AngkaAwal[6]=='O' && AngkaAwal[7]=='O' && AngkaAwal[8] == 'O' && AngkaAwal[9] == 'O'){
             return 2;
        }
        else if(AngkaAwal[11]== 'O' && AngkaAwal[12]=='O' && AngkaAwal[13]== 'O' && AngkaAwal[14] == 'O'){
             return 2;
        }
        else if(AngkaAwal[16]=='O' && AngkaAwal[17]== 'O' && AngkaAwal[18] == 'O' && AngkaAwal[19] == 'O'){
             return 2;
        }
        else if(AngkaAwal[21]=='O' && AngkaAwal[22]== 'O' && AngkaAwal[23] == 'O' && AngkaAwal[24] == 'O'){
             return 2;
        }
        else if(AngkaAwal[2]=='O' && AngkaAwal[3]=='O' && AngkaAwal[4]== 'O' && AngkaAwal[5] == 'O'){
             return 2;
         }
        else if(AngkaAwal[7]=='O' && AngkaAwal[8]=='O' && AngkaAwal[9]== 'O' && AngkaAwal[10] == 'O'){
             return 2;
        }
        else if(AngkaAwal[12]=='O' && AngkaAwal[13]=='O' && AngkaAwal[14]== 'O' && AngkaAwal[15] == 'O'){
             return 2;
        }
        else if(AngkaAwal[17]=='O' && AngkaAwal[18]=='O' && AngkaAwal[19] == 'O' && AngkaAwal[20] == 'O'){                  //Kondisi Menang untuk Player 2
             return 2;
        } 
        else if(AngkaAwal[22]=='O' && AngkaAwal[23]=='O' && AngkaAwal[24] == 'O' && AngkaAwal[25] == 'O'){
             return 2;
        }
        else if(AngkaAwal[1]== 'O' && AngkaAwal[6]=='O' && AngkaAwal[11] == 'O' && AngkaAwal[16] == 'O'){
             return 2;
        }
        else if(AngkaAwal[6]=='O' && AngkaAwal[11]== 'O' && AngkaAwal[16] == 'O' && AngkaAwal[21] == 'O'){
             return 2;
        }
        else if(AngkaAwal[2]=='O' && AngkaAwal[7]== 'O' && AngkaAwal[12] == 'O' && AngkaAwal[17] == 'O'){
             return 2;
        }
        else if(AngkaAwal[7]=='O' && AngkaAwal[12]=='O' && AngkaAwal[17] == 'O' && AngkaAwal[22] == 'O'){
             return 2;
         }
        else if(AngkaAwal[3]=='O' && AngkaAwal[8]=='O' && AngkaAwal[13] == 'O' && AngkaAwal[18] == 'O'){
             return 2;
        }
        else if(AngkaAwal[8]=='O' && AngkaAwal[13]=='O' && AngkaAwal[18]== 'O' && AngkaAwal[23] == 'O'){
            return 2;
        }
        else if(AngkaAwal[4] == 'O' && AngkaAwal[9] == 'O' && AngkaAwal[14] == 'O' && AngkaAwal[19] == 'O'){
        	return 2;
		}
		else if(AngkaAwal[9] == 'O' && AngkaAwal[14] == 'O' && AngkaAwal[19] == 'O' && AngkaAwal[24] == 'O'){
			return 2;
		}
		else if(AngkaAwal[5] == 'O' && AngkaAwal[10] == 'O' && AngkaAwal[15] == 'O' && AngkaAwal[20] == 'O'){
			return 2;
		}
		else if(AngkaAwal[10] == 'O' && AngkaAwal[15] == 'O' && AngkaAwal[20] == 'O' && AngkaAwal[25] == 'O'){
			return 2;
		}
		else if(AngkaAwal[1] == 'O' && AngkaAwal[7] == 'O' && AngkaAwal[13] == 'O' && AngkaAwal[19] == 'O'){
			return 2;
		}
		else if(AngkaAwal[7] == 'O' && AngkaAwal[13] == 'O' && AngkaAwal[19] == 'O' && AngkaAwal[25] == 'O'){
			return 2;
		}
		else if(AngkaAwal[2] == 'O' && AngkaAwal[8] == 'O' && AngkaAwal[14] == 'O' && AngkaAwal[20] == 'O'){
			return 2;
		}
		else if(AngkaAwal[6] == 'O' && AngkaAwal[12] == 'O' && AngkaAwal[18] == 'O' && AngkaAwal[24] == 'O'){
			return 2;
		}
		else if(AngkaAwal[5] == 'O' && AngkaAwal[9] == 'O' && AngkaAwal[13] == 'O' && AngkaAwal[17] == 'O'){
			return 2;
		}
		else if(AngkaAwal[9] == 'O' && AngkaAwal[13] == 'O' && AngkaAwal[17] == 'O' && AngkaAwal[21] == 'O'){
			return 2;
		}
		else if(AngkaAwal[4] == 'O' && AngkaAwal[8] == 'O' && AngkaAwal[12] == 'O' && AngkaAwal[16] == 'O'){
			return 2;
		}
		else if(AngkaAwal[10] == 'O' && AngkaAwal[14] == 'O' && AngkaAwal[18] == 'O' && AngkaAwal[23] == 'O'){
			return 2;
		}
        else{
            return 0;
        }
}
void Papan3(Player *Player1, Player *Player2){
	int sisakotak = 49;
	char AngkaAwal[50]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49};
	int urut, Kotak, counter, win;
	char board[7][7];
	int cekKondisiWin3(char AngkaAwal[50]);
	void CetakDraw();
	
	int skorPlayer1 = 0;
	int skorPlayer2 = 0;
	
	printf("\n\n\t\t   sisa kotak= %d", sisakotak);
    printf("\n\t         |               |               |               |               |               |               \n");
    printf(" \t   %c\t | \t%c\t |   %c\t\t |   %c\t\t | %c\t\t |   %c\t\t |   %c\t\n",AngkaAwal[1],AngkaAwal[2],AngkaAwal[3],AngkaAwal[4],AngkaAwal[5],AngkaAwal[6],AngkaAwal[7]);
    printf("\t         |               |               |               |               |               |               \n");
    printf("\t---------+---------------+---------------+---------------+---------------+---------------+---------------\n");
    printf("\t         |               |               |               |               |               |               \n");
    printf(" \t   %c\t | \t%c\t |   %c\t\t |   %c\t\t | %c\t\t |   %c\t\t |   %c\t\n",AngkaAwal[8],AngkaAwal[9],AngkaAwal[10],AngkaAwal[11],AngkaAwal[12],AngkaAwal[13],AngkaAwal[14]);
    printf("\t         |               |               |               |               |               |               \n");
    printf("\t---------+---------------+---------------+---------------+---------------+---------------+---------------\n");
    printf("\t         |               |               |               |               |               |               \n");
    printf(" \t   %c\t | \t%c\t |   %c\t\t |   %c\t\t | %c\t\t |   %c\t\t |   %c\t\n",AngkaAwal[15],AngkaAwal[16],AngkaAwal[17],AngkaAwal[18],AngkaAwal[19],AngkaAwal[20],AngkaAwal[21]);
    printf("\t         |               |               |               |               |               |               \n");
    printf("\t---------+---------------+---------------+---------------+---------------+---------------+---------------\n");
    printf("\t         |               |               |               |               |               |               \n");
    printf(" \t   %c\t | \t%c\t |   %c\t\t |   %c\t\t | %c\t\t |   %c\t\t |   %c\t\n",AngkaAwal[22],AngkaAwal[23],AngkaAwal[24],AngkaAwal[25],AngkaAwal[26],AngkaAwal[27],AngkaAwal[28]);
    printf("\t         |               |               |               |               |               |               \n");
    printf("\t         |               |               |               |               |               |               \n");
    printf("\t---------+---------------+---------------+---------------+---------------+---------------+---------------\n");
    printf("\t         |               |               |               |               |               |               \n");
    printf(" \t   %c\t | \t%c\t |   %c\t\t |   %c\t\t | %c\t\t |   %c\t\t |   %c\t\n",AngkaAwal[29],AngkaAwal[30],AngkaAwal[31],AngkaAwal[32],AngkaAwal[33],AngkaAwal[34],AngkaAwal[35]);
    printf("\t         |               |               |               |               |               |               \n");
    printf("\t         |               |               |               |               |               |               \n");
    printf("\t---------+---------------+---------------+---------------+---------------+---------------+---------------\n");
    printf("\t         |               |               |               |               |               |               \n");
    printf(" \t   %c\t | \t%c\t |   %c\t\t |   %c\t\t | %c\t\t |   %c\t\t |   %c\t\n",AngkaAwal[36],AngkaAwal[37],AngkaAwal[38],AngkaAwal[39],AngkaAwal[40],AngkaAwal[41],AngkaAwal[42]);
    printf("\t         |               |               |               |               |               |               \n");
    printf("\t         |               |               |               |               |               |               \n");
    printf("\t---------+---------------+---------------+---------------+---------------+---------------+---------------\n");
    printf("\t         |               |               |               |               |               |               \n");
    printf(" \t   %c\t | \t%c\t |   %c\t\t |   %c\t\t | %c\t\t |   %c\t\t |   %c\t\n",AngkaAwal[43],AngkaAwal[44],AngkaAwal[45],AngkaAwal[46],AngkaAwal[47],AngkaAwal[48],AngkaAwal[49]);
    printf("\t         |               |               |               |               |               |               \n\n");
    
    
    for (urut = 1; urut < 50; urut++) {
        if (urut % 2 == 1) {
            printf("%s Turn\n", Player1->Nama);
            printf("Masukkan Kotak[1..49]:");
            scanf("%d", &Kotak);

            if ((AngkaAwal[Kotak] == 'X') || (AngkaAwal[Kotak] == 'O')) {
                printf("Jangan ngisi Kotak yang ini!!!!\n");
                printf("Yang lain aja!!!");
            }else{
            	AngkaAwal[Kotak]='X';
            	sisakotak = sisakotak - 1;
            	printf("\n\n\t\t   sisa kotak= %d", sisakotak);
    			printf("\n\t         |               |               |               |               |               |               \n");
    			printf(" \t   %c\t | \t%c\t |   %c\t\t |   %c\t\t | %c\t\t |   %c\t\t |   %c\t\n",AngkaAwal[1],AngkaAwal[2],AngkaAwal[3],AngkaAwal[4],AngkaAwal[5],AngkaAwal[6],AngkaAwal[7]);
    			printf("\t         |               |               |               |               |               |               \n");
    			printf("\t---------+---------------+---------------+---------------+---------------+---------------+---------------\n");
    			printf("\t         |               |               |               |               |               |               \n");
    			printf(" \t   %c\t | \t%c\t |   %c\t\t |   %c\t\t | %c\t\t |   %c\t\t |   %c\t\n",AngkaAwal[8],AngkaAwal[9],AngkaAwal[10],AngkaAwal[11],AngkaAwal[12],AngkaAwal[13],AngkaAwal[14]);
    			printf("\t         |               |               |               |               |               |               \n");
    			printf("\t---------+---------------+---------------+---------------+---------------+---------------+---------------\n");
    			printf("\t         |               |               |               |               |               |               \n");
    			printf(" \t   %c\t | \t%c\t |   %c\t\t |   %c\t\t | %c\t\t |   %c\t\t |   %c\t\n",AngkaAwal[15],AngkaAwal[16],AngkaAwal[17],AngkaAwal[18],AngkaAwal[19],AngkaAwal[20],AngkaAwal[21]);
    			printf("\t         |               |               |               |               |               |               \n");
    			printf("\t---------+---------------+---------------+---------------+---------------+---------------+---------------\n");
    			printf("\t         |               |               |               |               |               |               \n");
    			printf(" \t   %c\t | \t%c\t |   %c\t\t |   %c\t\t | %c\t\t |   %c\t\t |   %c\t\n",AngkaAwal[22],AngkaAwal[23],AngkaAwal[24],AngkaAwal[25],AngkaAwal[26],AngkaAwal[27],AngkaAwal[28]);
    			printf("\t         |               |               |               |               |               |               \n");
    			printf("\t         |               |               |               |               |               |               \n");
    			printf("\t---------+---------------+---------------+---------------+---------------+---------------+---------------\n");
    			printf("\t         |               |               |               |               |               |               \n");
    			printf(" \t   %c\t | \t%c\t |   %c\t\t |   %c\t\t | %c\t\t |   %c\t\t |   %c\t\n",AngkaAwal[29],AngkaAwal[30],AngkaAwal[31],AngkaAwal[32],AngkaAwal[33],AngkaAwal[34],AngkaAwal[35]);
    			printf("\t         |               |               |               |               |               |               \n");
    			printf("\t         |               |               |               |               |               |               \n");
    			printf("\t---------+---------------+---------------+---------------+---------------+---------------+---------------\n");
   				printf("\t         |               |               |               |               |               |               \n");
    			printf(" \t   %c\t | \t%c\t |   %c\t\t |   %c\t\t | %c\t\t |   %c\t\t |   %c\t\n",AngkaAwal[36],AngkaAwal[37],AngkaAwal[38],AngkaAwal[39],AngkaAwal[40],AngkaAwal[41],AngkaAwal[42]);
    			printf("\t         |               |               |               |               |               |               \n");
    			printf("\t         |               |               |               |               |               |               \n");
    			printf("\t---------+---------------+---------------+---------------+---------------+---------------+---------------\n");
    			printf("\t         |               |               |               |               |               |               \n");
    			printf(" \t   %c\t | \t%c\t |   %c\t\t |   %c\t\t | %c\t\t |   %c\t\t |   %c\t\n",AngkaAwal[43],AngkaAwal[44],AngkaAwal[45],AngkaAwal[46],AngkaAwal[47],AngkaAwal[48],AngkaAwal[49]);
    			printf("\t         |               |               |               |               |               |               \n\n");
    		}
    		win = cekKondisiWin3(AngkaAwal);
    		if(win == 1){
    			CetakMenang(Player1->Nama);
    			Player1->Skor = Player1->Skor++;
    			break;
			}
    	}else{
    		printf("%s Turn", Player2->Nama);
    		counter = 0;
    		while (counter == 0){
    			printf("\nMasukkan Kotak [1..49]:");
    			scanf("%d", &Kotak);
    			
    			if ((AngkaAwal[Kotak] == 'X') || (AngkaAwal[Kotak] == 'O')){
    				printf("Invalid Move!!!\n");
				}else{
					counter = 1;
					AngkaAwal[Kotak] = 'O';
          		sisakotak = sisakotak - 1;
            	printf("\n\n\t\t   sisa kotak= %d", sisakotak);
    			printf("\n\t         |               |               |               |               |               |               \n");
    			printf(" \t   %c\t | \t%c\t |   %c\t\t |   %c\t\t | %c\t\t |   %c\t\t |   %c\t\n",AngkaAwal[1],AngkaAwal[2],AngkaAwal[3],AngkaAwal[4],AngkaAwal[5],AngkaAwal[6],AngkaAwal[7]);
    			printf("\t         |               |               |               |               |               |               \n");
    			printf("\t---------+---------------+---------------+---------------+---------------+---------------+---------------\n");
    			printf("\t         |               |               |               |               |               |               \n");
    			printf(" \t   %c\t | \t%c\t |   %c\t\t |   %c\t\t | %c\t\t |   %c\t\t |   %c\t\n",AngkaAwal[8],AngkaAwal[9],AngkaAwal[10],AngkaAwal[11],AngkaAwal[12],AngkaAwal[13],AngkaAwal[14]);
    			printf("\t         |               |               |               |               |               |               \n");
    			printf("\t---------+---------------+---------------+---------------+---------------+---------------+---------------\n");
    			printf("\t         |               |               |               |               |               |               \n");
    			printf(" \t   %c\t | \t%c\t |   %c\t\t |   %c\t\t | %c\t\t |   %c\t\t |   %c\t\n",AngkaAwal[15],AngkaAwal[16],AngkaAwal[17],AngkaAwal[18],AngkaAwal[19],AngkaAwal[20],AngkaAwal[21]);
    			printf("\t         |               |               |               |               |               |               \n");
    			printf("\t---------+---------------+---------------+---------------+---------------+---------------+---------------\n");
    			printf("\t         |               |               |               |               |               |               \n");
    			printf("\t   %c\t | \t%c\t |   %c\t\t |   %c\t\t | %c\t\t |   %c\t\t |   %c\t\n",AngkaAwal[22],AngkaAwal[23],AngkaAwal[24],AngkaAwal[25],AngkaAwal[26],AngkaAwal[27],AngkaAwal[28]);
    			printf("\t         |               |               |               |               |               |               \n");
    			printf("\t         |               |               |               |               |               |               \n");
    			printf("\t---------+---------------+---------------+---------------+---------------+---------------+---------------\n");
    			printf("\t         |               |               |               |               |               |               \n");
    			printf("\t   %c\t | \t%c\t |   %c\t\t |   %c\t\t | %c\t\t |   %c\t\t |   %c\t\n",AngkaAwal[29],AngkaAwal[30],AngkaAwal[31],AngkaAwal[32],AngkaAwal[33],AngkaAwal[34],AngkaAwal[35]);
    			printf("\t         |               |               |               |               |               |               \n\n");
    			printf("\t         |               |               |               |               |               |               \n");
   				printf("\t---------+---------------+---------------+---------------+---------------+---------------+---------------\n");
    			printf("\t         |               |               |               |               |               |               \n");
    			printf(" \t   %c\t | \t%c\t |   %c\t\t |   %c\t\t | %c\t\t |   %c\t\t |   %c\t\n",AngkaAwal[36],AngkaAwal[37],AngkaAwal[38],AngkaAwal[39],AngkaAwal[40],AngkaAwal[41],AngkaAwal[42]);
    			printf("\t         |               |               |               |               |               |               \n");
    			printf("\t         |               |               |               |               |               |               \n");
    			printf("\t---------+---------------+---------------+---------------+---------------+---------------+---------------\n");
    			printf("\t         |               |               |               |               |               |               \n");
    			printf(" \t   %c\t | \t%c\t |   %c\t\t |   %c\t\t | %c\t\t |   %c\t\t |   %c\t\n",AngkaAwal[43],AngkaAwal[44],AngkaAwal[45],AngkaAwal[46],AngkaAwal[47],AngkaAwal[48],AngkaAwal[49]);
    			printf("\t         |               |               |               |               |               |               \n\n");
				}
			}
			win = cekKondisiWin3(AngkaAwal);
			if(win == 2){
				CetakMenang(Player2->Nama);
				Player2->Skor = Player2->Skor++;
				break;
			}
		}
    }
    if(win == 0){
    	CetakDraw();
	}
}
int cekKondisiWin3(char AngkaAwal[50]){
if(AngkaAwal[1]=='X' && AngkaAwal[2]=='X' && AngkaAwal[3] == 'X' && AngkaAwal[4] == 'X' && AngkaAwal[5] == 'X'){                  //Kondisi Menang untuk Player 1
            return 1;
        } 
        else if(AngkaAwal[8]=='X' && AngkaAwal[9]=='X' && AngkaAwal[10] == 'X' && AngkaAwal[11] == 'X' && AngkaAwal[12] == 'X'){
             return 1;
        }
        else if(AngkaAwal[15]== 'X' && AngkaAwal[16]=='X' && AngkaAwal[17]== 'X' && AngkaAwal[18] == 'X' && AngkaAwal[19] == 'X'){
             return 1;
        }
        else if(AngkaAwal[22]=='X' && AngkaAwal[23]== 'X' && AngkaAwal[24] == 'X' && AngkaAwal[25] == 'X' && AngkaAwal[26] == 'X'){
             return 1;
        }
        else if(AngkaAwal[29]=='X' && AngkaAwal[30]== 'X' && AngkaAwal[31] == 'X' && AngkaAwal[32] == 'X' && AngkaAwal[33] == 'X'){
             return 1;
        }
        else if(AngkaAwal[36]=='X' && AngkaAwal[37]=='X' && AngkaAwal[38]== 'X' && AngkaAwal[39] == 'X' && AngkaAwal[40] == 'X'){
             return 1;
        }
        else if(AngkaAwal[43]=='X' && AngkaAwal[44]=='X' && AngkaAwal[45]== 'X' && AngkaAwal[46] == 'X' && AngkaAwal[47] == 'X'){
             return 1;
        }
        else if(AngkaAwal[2]=='X' && AngkaAwal[3]=='X' && AngkaAwal[4]== 'X' && AngkaAwal[5] == 'X' && AngkaAwal[6] == 'X'){
             return 1;
        }
        else if(AngkaAwal[9]=='X' && AngkaAwal[10]=='X' && AngkaAwal[11] == 'X' && AngkaAwal[12] == 'X' && AngkaAwal[13] == 'X'){                  
             return 1;
        } 
        else if(AngkaAwal[16]=='X' && AngkaAwal[17]=='X' && AngkaAwal[18] == 'X' && AngkaAwal[19] == 'X' && AngkaAwal[20] == 'X'){
             return 1;
        }
        else if(AngkaAwal[23]== 'X' && AngkaAwal[24]=='X' && AngkaAwal[25] == 'X' && AngkaAwal[26] == 'X' && AngkaAwal[27] == 'X'){
             return 1;
        }
        else if(AngkaAwal[30]=='X' && AngkaAwal[31]== 'X' && AngkaAwal[32] == 'X' && AngkaAwal[33] == 'X' && AngkaAwal[34] == 'X'){
             return 1;
        }
        else if(AngkaAwal[37]=='X' && AngkaAwal[38]== 'X' && AngkaAwal[39] == 'X' && AngkaAwal[40] == 'X' && AngkaAwal[41] == 'X'){
             return 1;
        }
        else if(AngkaAwal[44]=='X' && AngkaAwal[45]=='X' && AngkaAwal[46] == 'X' && AngkaAwal[47] == 'X' && AngkaAwal[48] == 'X'){
             return 1;
         }
        else if(AngkaAwal[3]=='X' && AngkaAwal[4]=='X' && AngkaAwal[5] == 'X' && AngkaAwal[6] == 'X' && AngkaAwal[7]== 'X'){
             return 1;
        }
        else if(AngkaAwal[10]=='X' && AngkaAwal[11]=='X' && AngkaAwal[12]== 'X' && AngkaAwal[13] == 'X' && AngkaAwal[14] == 'X'){
            return 1;
        }
        else if(AngkaAwal[17] == 'X' && AngkaAwal[18] == 'X' && AngkaAwal[19] == 'X' && AngkaAwal[20] == 'X' && AngkaAwal[21] == 'X'){
        	return 1;
		}
		else if(AngkaAwal[24] == 'X' && AngkaAwal[25] == 'X' && AngkaAwal[26] == 'X' && AngkaAwal[27] == 'X' && AngkaAwal[28] == 'X'){
			return 1;
		}
		else if(AngkaAwal[31] == 'X' && AngkaAwal[32] == 'X' && AngkaAwal[33] == 'X' && AngkaAwal[34] == 'X' && AngkaAwal[35] == 'X'){
			return 1;
		}
		else if(AngkaAwal[38] == 'X' && AngkaAwal[39] == 'X' && AngkaAwal[40] == 'X' && AngkaAwal[41] == 'X' && AngkaAwal[42] == 'X'){
			return 1;
		}
		else if(AngkaAwal[45] == 'X' && AngkaAwal[46] == 'X' && AngkaAwal[47] == 'X' && AngkaAwal[48] == 'X' && AngkaAwal[49] == 'X'){
			return 1;
		}
		else if(AngkaAwal[1] == 'X' && AngkaAwal[8] == 'X' && AngkaAwal[15] == 'X' && AngkaAwal[22] == 'X' && AngkaAwal[29] == 'X'){
			return 1;
		}
		else if(AngkaAwal[2] == 'X' && AngkaAwal[9] == 'X' && AngkaAwal[16] == 'X' && AngkaAwal[23] == 'X' && AngkaAwal[30] == 'X'){
			return 1;
		}
		else if(AngkaAwal[3] == 'X' && AngkaAwal[10] == 'X' && AngkaAwal[17] == 'X' && AngkaAwal[24] == 'X' && AngkaAwal[31] == 'X'){
			return 1;
		}
		else if(AngkaAwal[4] == 'X' && AngkaAwal[11] == 'X' && AngkaAwal[18] == 'X' && AngkaAwal[25] == 'X' && AngkaAwal[32] == 'X'){
			return 1;
		}
		else if(AngkaAwal[5] == 'X' && AngkaAwal[12] == 'X' && AngkaAwal[19] == 'X' && AngkaAwal[26] == 'X' && AngkaAwal[33] == 'X'){
			return 1;
		}
		else if(AngkaAwal[6] == 'X' && AngkaAwal[13] == 'X' && AngkaAwal[20] == 'X' && AngkaAwal[27] == 'X' && AngkaAwal[34] == 'X'){
			return 1;
		}
		else if(AngkaAwal[7] == 'X' && AngkaAwal[14] == 'X' && AngkaAwal[21] == 'X' && AngkaAwal[28] == 'X' && AngkaAwal[35] == 'X'){
			return 1;
		}
		else if(AngkaAwal[8]=='X' && AngkaAwal[15]=='X' && AngkaAwal[22] == 'X' && AngkaAwal[29] == 'X' && AngkaAwal[36] == 'X'){               
            return 1;
        } 
        else if(AngkaAwal[9]=='X' && AngkaAwal[16]=='X' && AngkaAwal[23] == 'X' && AngkaAwal[30] == 'X' && AngkaAwal[37] == 'X'){
             return 1;
        }
        else if(AngkaAwal[10]== 'X' && AngkaAwal[17]=='X' && AngkaAwal[24]== 'X' && AngkaAwal[31] == 'X' && AngkaAwal[38] == 'X'){
             return 1;
        }
        else if(AngkaAwal[11]=='X' && AngkaAwal[18]== 'X' && AngkaAwal[25] == 'X' && AngkaAwal[32] == 'X' && AngkaAwal[39] =='X'){
             return 1;
        }
        else if(AngkaAwal[12]=='X' && AngkaAwal[19]== 'X' && AngkaAwal[26] == 'X' && AngkaAwal[33] == 'X' && AngkaAwal[40] == 'X'){
             return 1;
        }
        else if(AngkaAwal[13]=='X' && AngkaAwal[20]=='X' && AngkaAwal[27]== 'X' && AngkaAwal[34] == 'X' && AngkaAwal[41] == 'X'){
             return 1;
         }
        else if(AngkaAwal[14]=='X' && AngkaAwal[21]=='X' && AngkaAwal[28]== 'X' && AngkaAwal[35] == 'X' && AngkaAwal[42] == 'X'){
             return 1;
        }
        else if(AngkaAwal[15]=='X' && AngkaAwal[22]=='X' && AngkaAwal[29]== 'X' && AngkaAwal[36] == 'X' && AngkaAwal[43] == 'X'){
             return 1;
        }
        else if(AngkaAwal[16]=='X' && AngkaAwal[23]=='X' && AngkaAwal[30] == 'X' && AngkaAwal[37] == 'X' && AngkaAwal[44] == 'X'){                  
             return 1;
        } 
        else if(AngkaAwal[17]=='X' && AngkaAwal[24]=='O' && AngkaAwal[30] == 'X' && AngkaAwal[38] == 'X' && AngkaAwal[45] == 'X'){
             return 1;
        }
        else if(AngkaAwal[18]== 'X' && AngkaAwal[25]=='X' && AngkaAwal[31] == 'X' && AngkaAwal[39] == 'X' && AngkaAwal[46] == 'X'){
             return 1;
        }
        else if(AngkaAwal[19]=='X' && AngkaAwal[26]== 'X' && AngkaAwal[32] == 'X' && AngkaAwal[40] == 'X' && AngkaAwal[47] == 'X'){
             return 1;
        }
        else if(AngkaAwal[20]=='X' && AngkaAwal[27]== 'X' && AngkaAwal[33] == 'X' && AngkaAwal[41] == 'X' && AngkaAwal[48] == 'X'){
             return 1;
        }
        else if(AngkaAwal[21]=='X' && AngkaAwal[28]=='X' && AngkaAwal[34] == 'X' && AngkaAwal[42] == 'X' && AngkaAwal[49] == 'X'){
             return 1;
         }
        else if(AngkaAwal[15]=='X' && AngkaAwal[23]=='X' && AngkaAwal[31] == 'X' && AngkaAwal[39] == 'X' && AngkaAwal[47] == 'X'){
             return 1;
        }
        else if(AngkaAwal[8]=='X' && AngkaAwal[16]=='X' && AngkaAwal[27]== 'X' && AngkaAwal[32] == 'X' && AngkaAwal[40] == 'X'){
            return 1;
        }
        else if(AngkaAwal[16] == 'X' && AngkaAwal[27] == 'X' && AngkaAwal[32] == 'X' && AngkaAwal[40] == 'X' && AngkaAwal[48] == 'X'){
        	return 1;
		}
		else if(AngkaAwal[1] == 'X' && AngkaAwal[9] == 'X' && AngkaAwal[17] == 'X' && AngkaAwal[25] == 'X' && AngkaAwal[33] == 'X'){
			return 1;
		}
		else if(AngkaAwal[9] == 'X' && AngkaAwal[17] == 'X' && AngkaAwal[25] == 'X' && AngkaAwal[33] == 'X' && AngkaAwal[41] == 'X'){
			return 1;
		}
		else if(AngkaAwal[17] == 'X' && AngkaAwal[25] == 'X' && AngkaAwal[33] == 'X' && AngkaAwal[41] == 'X' && AngkaAwal[49] == 'X'){
			return 1;
		}
		else if(AngkaAwal[2] == 'X' && AngkaAwal[10] == 'X' && AngkaAwal[18] == 'X' && AngkaAwal[26] == 'X' && AngkaAwal[34] == 'X'){
			return 1;
		}
		else if(AngkaAwal[10] == 'X' && AngkaAwal[18] == 'X' && AngkaAwal[26] == 'X' && AngkaAwal[34] == 'X' && AngkaAwal[42] == 'X'){
			return 1;
		}
		else if(AngkaAwal[3] == 'X' && AngkaAwal[11] == 'X' && AngkaAwal[19] == 'X' && AngkaAwal[27] == 'X' && AngkaAwal[35] == 'X'){
			return 1;
		}
		else if(AngkaAwal[5] == 'X' && AngkaAwal[11] == 'X' && AngkaAwal[17] == 'X' && AngkaAwal[23] == 'X' && AngkaAwal[29] == 'X'){
			return 1;
		}
		else if(AngkaAwal[6] == 'X' && AngkaAwal[12] == 'X' && AngkaAwal[18] == 'X' && AngkaAwal[24] == 'X' && AngkaAwal[30] == 'X'){
			return 1;
		}
		else if(AngkaAwal[12] == 'X' && AngkaAwal[18] == 'X' && AngkaAwal[24] == 'X' && AngkaAwal[30] == 'X' && AngkaAwal[36] == 'X'){
			return 1;
		}
		else if(AngkaAwal[7] == 'X' && AngkaAwal[13] == 'X' && AngkaAwal[19] == 'X' && AngkaAwal[25] == 'X' && AngkaAwal[31] == 'X'){
			return 1;
		}
		else if(AngkaAwal[13] == 'X' && AngkaAwal[19] == 'X' && AngkaAwal[25] == 'X' && AngkaAwal[31] == 'X' && AngkaAwal[37] == 'X'){
			return 1;
		}
		else if(AngkaAwal[19] == 'X' && AngkaAwal[25] == 'X' && AngkaAwal[31] == 'X' && AngkaAwal[37] == 'X' && AngkaAwal[49] == 'X'){
			return 1;
		}
		else if(AngkaAwal[14] == 'X' && AngkaAwal[20] == 'X' && AngkaAwal[26] == 'X' && AngkaAwal[32] == 'X' && AngkaAwal[38] == 'X'){
			return 1;
		}
		else if(AngkaAwal[20] == 'X' && AngkaAwal[26] == 'X' && AngkaAwal[32] == 'X' && AngkaAwal[38] == 'X' && AngkaAwal[44] == 'X'){
			return 1;
		}
		else if(AngkaAwal[21] == 'X' && AngkaAwal[27] == 'X' && AngkaAwal[33] == 'X' && AngkaAwal[39] == 'X' && AngkaAwal[45] == 'X'){
			return 1;
		}
		else if(AngkaAwal[1] == 'O' && AngkaAwal[2]=='O' && AngkaAwal[3] == 'O' && AngkaAwal[4] == 'O' && AngkaAwal[5] == 'O'){                  //Kondisi Menang untuk Player 2
            return 2;
        } 
        else if(AngkaAwal[8] == 'O' && AngkaAwal[9]=='O' && AngkaAwal[10] == 'O' && AngkaAwal[11] == 'O' && AngkaAwal[12] == 'O'){
             return 2;
        }
        else if(AngkaAwal[15] == 'O' && AngkaAwal[16]=='O' && AngkaAwal[17]== 'O' && AngkaAwal[18] == 'O' && AngkaAwal[19] == 'O'){
             return 2;
        }
        else if(AngkaAwal[22] == 'O' && AngkaAwal[23]== 'O' && AngkaAwal[24] == 'O' && AngkaAwal[25] == 'O' && AngkaAwal[26] == 'O'){
             return 2;
        }
        else if(AngkaAwal[29] == 'O' && AngkaAwal[30]== 'O' && AngkaAwal[31] == 'O' && AngkaAwal[32] == 'O' && AngkaAwal[33] == 'O'){
             return 2;
        }
        else if(AngkaAwal[36] == 'O' && AngkaAwal[37]=='O' && AngkaAwal[38]== 'O' && AngkaAwal[39] == 'O' && AngkaAwal[40] == 'O'){
             return 2;
        }
        else if(AngkaAwal[43] == 'O' && AngkaAwal[44]=='O' && AngkaAwal[45]== 'O' && AngkaAwal[46] == 'O' && AngkaAwal[47] == 'O'){
             return 2;
        }
        else if(AngkaAwal[2] == 'O' && AngkaAwal[3]=='O' && AngkaAwal[4]== 'O' && AngkaAwal[5] == 'O' && AngkaAwal[6] == 'O'){
             return 2;
        }
        else if(AngkaAwal[9] == 'O' && AngkaAwal[10]=='O' && AngkaAwal[11] == 'O' && AngkaAwal[12] == 'O' && AngkaAwal[13] == 'O'){                  
             return 2;
        } 
        else if(AngkaAwal[16] == 'O' && AngkaAwal[17]=='O' && AngkaAwal[18] == 'O' && AngkaAwal[19] == 'O' && AngkaAwal[20] == 'O'){
             return 2;
        }
        else if(AngkaAwal[23] == 'O' && AngkaAwal[24]=='O' && AngkaAwal[25] == 'O' && AngkaAwal[26] == 'O' && AngkaAwal[27] == 'O'){
             return 2;
        }
        else if(AngkaAwal[30] == 'O' && AngkaAwal[31]== 'O' && AngkaAwal[32] == 'O' && AngkaAwal[33] == 'O' && AngkaAwal[34] == 'O'){
             return 2;
        }
        else if(AngkaAwal[37] == 'O' && AngkaAwal[38]== 'O' && AngkaAwal[39] == 'O' && AngkaAwal[40] == 'O' && AngkaAwal[41] == 'O'){
             return 2;
        }
        else if(AngkaAwal[44] == 'O' && AngkaAwal[45]=='O' && AngkaAwal[46] == 'O' && AngkaAwal[47] == 'O' && AngkaAwal[48] == 'O'){
             return 2;
         }
        else if(AngkaAwal[3] == 'O' && AngkaAwal[4]=='O' && AngkaAwal[5] == 'O' && AngkaAwal[6] == 'O' && AngkaAwal[7]== 'O'){
             return 2;
        }
        else if(AngkaAwal[10] == 'O' && AngkaAwal[11]=='O' && AngkaAwal[12]== 'O' && AngkaAwal[13] == 'O' && AngkaAwal[14] == 'O'){
            return 2;
        }
        else if(AngkaAwal[17] == 'O' && AngkaAwal[18] == 'O' && AngkaAwal[19] == 'O' && AngkaAwal[20] == 'O' && AngkaAwal[21] == 'O'){
        	return 2;
		}
		else if(AngkaAwal[24] == 'O' && AngkaAwal[25] == 'O' && AngkaAwal[26] == 'O' && AngkaAwal[27] == 'O' && AngkaAwal[28] == 'O'){
			return 2;
		}
		else if(AngkaAwal[31] == 'O' && AngkaAwal[32] == 'O' && AngkaAwal[33] == 'O' && AngkaAwal[34] == 'O' && AngkaAwal[35] == 'O'){
			return 2;
		}
		else if(AngkaAwal[38] == 'O' && AngkaAwal[39] == 'O' && AngkaAwal[40] == 'O' && AngkaAwal[41] == 'O' && AngkaAwal[42] == 'O'){
			return 2;
		}
		else if(AngkaAwal[45] == 'O' && AngkaAwal[46] == 'O' && AngkaAwal[47] == 'O' && AngkaAwal[48] == 'O' && AngkaAwal[49] == 'O'){
			return 2;
		}
		else if(AngkaAwal[1] == 'O' && AngkaAwal[8] == 'O' && AngkaAwal[15] == 'O' && AngkaAwal[22] == 'O' && AngkaAwal[29] == 'O'){
			return 2;
		}
		else if(AngkaAwal[2] == 'O' && AngkaAwal[9] == 'O' && AngkaAwal[16] == 'O' && AngkaAwal[23] == 'O' && AngkaAwal[30] == 'O'){
			return 2;
		}
		else if(AngkaAwal[3] == 'O' && AngkaAwal[10] == 'O' && AngkaAwal[17] == 'O' && AngkaAwal[24] == 'O' && AngkaAwal[31] == 'O'){
			return 2;
		}
		else if(AngkaAwal[4] == 'O' && AngkaAwal[11] == 'O' && AngkaAwal[18] == 'O' && AngkaAwal[25] == 'O' && AngkaAwal[32] == 'O'){
			return 2;
		}
		else if(AngkaAwal[5] == 'O' && AngkaAwal[12] == 'O' && AngkaAwal[19] == 'O' && AngkaAwal[26] == 'O' && AngkaAwal[33] == 'O'){
			return 2;
		}
		else if(AngkaAwal[6] == 'O' && AngkaAwal[13] == 'O' && AngkaAwal[20] == 'O' && AngkaAwal[27] == 'O' && AngkaAwal[34] == 'O'){
			return 2;
		}
		else if(AngkaAwal[7] == 'O' && AngkaAwal[14] == 'O' && AngkaAwal[21] == 'O' && AngkaAwal[28] == 'O' && AngkaAwal[35] == 'O'){
			return 2;
		}
		else if(AngkaAwal[8] == 'O' && AngkaAwal[15] =='O' && AngkaAwal[22] == 'O' && AngkaAwal[29] == 'O' && AngkaAwal[36] == 'O'){               
            return 2;
        } 
        else if(AngkaAwal[9] == 'O' && AngkaAwal[16] =='O' && AngkaAwal[23] == 'O' && AngkaAwal[30] == 'O' && AngkaAwal[37] == 'O'){
            return 2;
        }
        else if(AngkaAwal[10] == 'O' && AngkaAwal[17]=='O' && AngkaAwal[24]== 'O' && AngkaAwal[31] == 'O' && AngkaAwal[38] == 'O'){
            return 2;
        }
        else if(AngkaAwal[11] == 'O' && AngkaAwal[18]== 'O' && AngkaAwal[25] == 'O' && AngkaAwal[32] == 'O' && AngkaAwal[39] =='O'){
            return 2;
        }
        else if(AngkaAwal[12] == 'O' && AngkaAwal[19]== 'O' && AngkaAwal[26] == 'O' && AngkaAwal[33] == 'O' && AngkaAwal[40] == 'O'){
            return 2;
        }
        else if(AngkaAwal[13] == 'O' && AngkaAwal[20]=='O' && AngkaAwal[27]== 'O' && AngkaAwal[34] == 'O' && AngkaAwal[41] == 'O'){
            return 2;
         }
        else if(AngkaAwal[14] == 'O' && AngkaAwal[21]=='O' && AngkaAwal[28]== 'O' && AngkaAwal[35] == 'O' && AngkaAwal[42] == 'O'){
            return 2;
        }
        else if(AngkaAwal[15] == 'O' && AngkaAwal[22]=='O' && AngkaAwal[29]== 'O' && AngkaAwal[36] == 'O' && AngkaAwal[43] == 'O'){
            return 2;
        }
        else if(AngkaAwal[16] == 'O' && AngkaAwal[23]=='O' && AngkaAwal[30] == 'O' && AngkaAwal[37] == 'O' && AngkaAwal[44] == 'O'){                  
            return 2;
        } 
        else if(AngkaAwal[17] == 'O' && AngkaAwal[24]=='O' && AngkaAwal[30] == 'O' && AngkaAwal[38] == 'O' && AngkaAwal[45] == 'O'){
            return 2;
        }
        else if(AngkaAwal[18] == 'O' && AngkaAwal[25]=='O' && AngkaAwal[31] == 'O' && AngkaAwal[39] == 'O' && AngkaAwal[46] == 'O'){
            return 2;
        }
        else if(AngkaAwal[19] == 'O' && AngkaAwal[26]== 'O' && AngkaAwal[32] == 'O' && AngkaAwal[40] == 'O' && AngkaAwal[47] == 'O'){
            return 2;
        }
        else if(AngkaAwal[20] == 'O' && AngkaAwal[27]== 'O' && AngkaAwal[33] == 'O' && AngkaAwal[41] == 'O' && AngkaAwal[48] == 'O'){
            return 2;
        }
        else if(AngkaAwal[21] == 'O' && AngkaAwal[28]=='O' && AngkaAwal[34] == 'O' && AngkaAwal[42] == 'O' && AngkaAwal[49] == 'O'){
            return 2;
         }
        else if(AngkaAwal[15] == 'O' && AngkaAwal[23]=='O' && AngkaAwal[31] == 'O' && AngkaAwal[39] == 'O' && AngkaAwal[47] == 'O'){
            return 2;
        }
        else if(AngkaAwal[8] == 'O' && AngkaAwal[16]=='O' && AngkaAwal[27]== 'O' && AngkaAwal[32] == 'O' && AngkaAwal[40] == 'O'){
            return 2;
        }
        else if(AngkaAwal[16] == 'O' && AngkaAwal[27] == 'O' && AngkaAwal[32] == 'O' && AngkaAwal[40] == 'O' && AngkaAwal[48] == 'O'){
        	return 2;
		}
		else if(AngkaAwal[1] == 'O' && AngkaAwal[9] == 'O' && AngkaAwal[17] == 'O' && AngkaAwal[25] == 'O' && AngkaAwal[33] == 'O'){
			return 2;
		}
		else if(AngkaAwal[9] == 'O' && AngkaAwal[17] == 'O' && AngkaAwal[25] == 'O' && AngkaAwal[33] == 'O' && AngkaAwal[41] == 'O'){
			return 2;
		}
		else if(AngkaAwal[17] == 'O' && AngkaAwal[25] == 'O' && AngkaAwal[33] == 'O' && AngkaAwal[41] == 'O' && AngkaAwal[49] == 'O'){
			return 2;
		}
		else if(AngkaAwal[2] == 'O' && AngkaAwal[10] == 'O' && AngkaAwal[18] == 'O' && AngkaAwal[26] == 'O' && AngkaAwal[34] == 'O'){
			return 2;
		}
		else if(AngkaAwal[10] == 'O' && AngkaAwal[18] == 'O' && AngkaAwal[26] == 'O' && AngkaAwal[34] == 'O' && AngkaAwal[42] == 'O'){
			return 2;
		}
		else if(AngkaAwal[3] == 'O' && AngkaAwal[11] == 'O' && AngkaAwal[19] == 'O' && AngkaAwal[27] == 'O' && AngkaAwal[35] == 'O'){
			return 2;
		}
		else if(AngkaAwal[5] == 'O' && AngkaAwal[11] == 'O' && AngkaAwal[17] == 'O' && AngkaAwal[23] == 'O' && AngkaAwal[29] == 'O'){
			return 2;
		}
		else if(AngkaAwal[6] == 'O' && AngkaAwal[12] == 'O' && AngkaAwal[18] == 'O' && AngkaAwal[24] == 'O' && AngkaAwal[30] == 'O'){
			return 2;
		}
		else if(AngkaAwal[12] == 'O' && AngkaAwal[18] == 'O' && AngkaAwal[24] == 'O' && AngkaAwal[30] == 'O' && AngkaAwal[36] == 'O'){
			return 2;
		}
		else if(AngkaAwal[7] == 'O' && AngkaAwal[13] == 'O' && AngkaAwal[19] == 'O' && AngkaAwal[25] == 'O' && AngkaAwal[31] == 'O'){
			return 2;
		}
		else if(AngkaAwal[13] == 'O' && AngkaAwal[19] == 'O' && AngkaAwal[25] == 'O' && AngkaAwal[31] == 'O' && AngkaAwal[37] == 'O'){
			return 2;
		}
		else if(AngkaAwal[19] == 'O' && AngkaAwal[25] == 'O' && AngkaAwal[31] == 'O' && AngkaAwal[37] == 'O' && AngkaAwal[49] == 'O'){
			return 2;
		}
		else if(AngkaAwal[14] == 'O' && AngkaAwal[20] == 'O' && AngkaAwal[26] == 'O' && AngkaAwal[32] == 'O' && AngkaAwal[38] == 'O'){
			return 2;
		}
		else if(AngkaAwal[20] == 'O' && AngkaAwal[26] == 'O' && AngkaAwal[32] == 'O' && AngkaAwal[38] == 'O' && AngkaAwal[44] == 'O'){
			return 2;
		}
		else if(AngkaAwal[21] == 'O' && AngkaAwal[27] == 'O' && AngkaAwal[33] == 'O' && AngkaAwal[39] == 'O' && AngkaAwal[45] == 'O'){
			return 2;
		}
        else{
            return 0;
        }
}
void Leaderboard(Player *Player1, Player *Player2){
	FILE *Skor;
	
	Skor = fopen("Skor.txt", "a+");
	if(Skor == NULL){
		exit(1);
	}else{
		fprintf(Skor,"%s %d", Player1->Nama, Player1->Skor);
		fprintf(Skor,"%s %d", Player2->Nama, Player2->Skor);
		fclose(Skor);
	}
}
void CetakMenang(const char* NamaPemenang){
	printf("%s win", NamaPemenang);
}
void CetakDraw(){   
	printf("\t\t\t\t>> Draw <<");
}
void CetakSisa(int *sisakotak){
	printf(" Sisa Kotak : %d\n\n", *sisakotak);
}
int CetakMainLagi(){
    int aftergame;
    
    printf("\n\n Main Lagi yes(1)/no(2)?\n Masukkan Angka : ");
    input(&aftergame);
    return aftergame;
}

int main(){
	int awalgame,aftergame;
	Proses:
	Tampil();
	input(&awalgame);
	system("cls");
	//Deklarasi Pemain
	Player Player1, Player2;
	//input pada tampilan
	if(awalgame == 1){
		CetakNama(&Player1, &Player2);
		system("cls");
		Level();
		input(&awalgame);
		system("cls");
		if(awalgame == 1){
			Papan1(&Player1, &Player2);
		}else if(awalgame == 2){
			Papan2(&Player1, &Player2);
		}else if(awalgame == 3){
			Papan3(&Player1, &Player2);
		}
	}else if(awalgame == 2){
		Rules();
		input(&awalgame);
		system("cls");
		goto Proses;		//untuk kembali ke tampilan awal
	}else if(awalgame == 3){
		printf("Leaderboard:\n");
		Leaderboard(&Player1, &Player2);
		input(&awalgame);
		system("cls");
		goto Proses;
	}else if(awalgame == 4){
		Keluar();
	}
	return 0;
}
