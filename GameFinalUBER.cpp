//Mochammad Fauzan Satriawan
//NIM : 1217050080
//UAS Praktikum Algoritma Dan Pemograman
#include <iostream>
#include <conio.h>
#include <time.h>
#include <windows.h>
using namespace std;

// Arrow key
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ESC 27

// Fungsi set warna
void setcolor(unsigned short color)
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon, color);
}

// Fungsi menjalankan player 
void playerMovement(int key);

// Fungsi coloring and symbolic
void displayMap();

// Fungsi Set warna
void setcolor(unsigned short color);

const int panjangPeta = 50;
const int lebarPeta = 20;
int playerX = 7;
int playerY = 7;
int arrowKey = ' ';


// Map peta UBER
int peta[lebarPeta][panjangPeta] = {
		{9, 9, 9, 9, 9, 9, 8, 8, 8, 7, 7, 7, 8, 8, 8, 8, 7, 7, 2, 7, 9, 9, 9, 9, 7, 7},
		{9, 9, 9, 9, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 7, 5, 7, 9, 9, 9, 9, 9, 7},
		{9, 9, 9, 1, 1, 1, 1, 1, 1, 2, 2, 1, 2, 2, 1, 1, 1, 7, 1, 7, 9, 9, 9, 7, 9, 7},
		{9, 9, 9, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1, 7, 1, 7, 9, 9, 9, 7, 9, 7},
		{9, 9, 9, 10, 10, 10, 10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 9, 9, 9, 7},
		{9, 9, 10, 10, 10, 10, 10, 10, 1, 1, 1, 1, 1, 1, 1, 7, 9, 1, 1, 1, 9, 9, 9, 7, 9, 7},
		{9, 9, 9, 11, 11, 11, 11, 1, 1, 1, 1, 1, 1, 1, 7, 2, 9, 1, 1, 1, 9, 9, 7, 9, 9, 7},
		{9, 9, 9, 11, 10, 10, 11, 1, 1, 1, 1, 1, 1, 1, 7, 1, 9, 1, 1, 1, 9, 9, 7, 7, 9, 7},
		{9, 9, 9, 11, 11, 11, 11, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 8, 1, 1, 7, 9, 9, 7, 9, 7},
		{9, 9, 1, 8, 1, 1, 8, 1, 1, 1, 1, 1, 1, 1, 1, 1, 8, 1, 8, 1 , 9, 9, 9, 9, 9, 7},
		{9, 9, 1, 8, 1, 1, 8, 1, 1, 1, 1, 1, 1, 1, 1, 1, 8, 8, 1, 1, 9, 9, 9, 7, 9, 7},
		{9, 9, 1, 1, 1, 4, 1, 1, 1, 9, 9, 1, 1, 1, 8, 8, 8, 1, 1, 1, 7, 7, 7, 9, 9, 7},
		{9, 9, 1, 1, 9, 1, 1, 1, 1, 1, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 7, 9, 9, 7, 7},
		{9, 9, 1, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 9, 9, 7, 9, 9, 7},
		{9, 9, 9, 1, 1, 1, 7, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 9, 9, 9, 9, 9, 7}, 
		{9, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 10, 10, 10, 10, 9, 9, 9, 9, 7, 9, 7},
		{9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 9, 1, 1, 1, 10, 10, 10, 10, 10, 10, 9, 9, 9, 9, 9, 7},
		{9, 7, 2, 2, 7, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 11, 11, 11, 11, 8, 9, 9, 9, 7, 9, 7},
		{9, 7, 2, 2, 7, 1, 1, 1, 1, 9, 2, 1, 1, 1, 1, 11, 10, 10, 11, 8, 9, 9, 9, 9, 7, 7},
		{9, 7, 7, 7, 7, 9, 9, 9, 9, 9, 9, 9, 6, 1, 1, 11, 11, 11, 11, 8, 9, 9, 9, 9, 7, 7},
};

// Structure Player
struct Pemain
{
	string name;
	int hp;
	int atk;
	int def;

	void baseAtkPlayer(int *Pokemon_hp, int *Pokemon_def)
	{
		*Pokemon_hp = *Pokemon_hp - (atk - *Pokemon_def);
	}
};

// Structure Pokemon monster
struct Pokemon
{
	string name;
	int hp;
	int atk;
	int def;

	void baseAtkPokemon(int *player_hp, int *player_def)
	{
		*player_hp = *player_hp - (atk - *player_def);
	}
};

//Fungsi Menjalankan Player
void playerMovement(int key)
{
  	if (key == KEY_UP
  	&& peta[playerY - 1][playerX] < 7)
	{
	  playerY -= 1;
	  playerY < 0 ? playerY =
	    0 : playerY;
	}
      else if (key == KEY_DOWN
		&& peta[playerY + 1][playerX] < 7)
	{
	  playerY += 1;
	  playerY > 19 ? playerY =
	    19 : playerY;
	}
      else if (key == KEY_LEFT
	       && peta[playerY][playerX - 1] < 7)
	{
	  playerX -= 1;
	  playerX < 0 ? playerX =
	    0 : playerX;
	}
      else if (key == KEY_RIGHT
	       && peta[playerY][playerX + 1] < 7)
	{
	  playerX += 1;
	  playerX > 19 ? playerX =
	    19 : playerX;
	}
	  else if (key == ESC)
    {  
    	system("cls");
    	char	 choice;
    	cout << "\tApa anda yakin ingin keluar?" << endl;
    	cout << "\tTerima Kasih sudah mau bermain :)" << endl;
    	cout << "1. Ya Tentu \n2. tidak mau\n";
    	choice = getch();

    	if (choice == '1') {
			exit(0);
		} else if (choice == '2') {
			system("cls");
		}
    };     
}

void displayMap()
{
	int koordinat = peta[playerY][playerX];
	
	cout << "\t\t=========================\n";
	cout << "\t\t=   [LvL.1] HUTAN UBER  =\n";
	cout << "\t\t=========================\n";
	
	for (int i = 0; i < lebarPeta; i++)
	{
	  for (int j = 0; j < panjangPeta; j++)
	    {
	      	if (playerX == j && playerY == i
		  	&& koordinat < 7)
			{
				//Player Bojan
		  		setcolor (7);		
		  		cout << char (2);	
		  		setcolor (7);
			}
	      		else if (peta[i][j] == 1)
			{
				//Rumput pendek
		  		setcolor (14);		
		  		cout << ".";		
		  		setcolor (7);
			}
	      		else if (peta[i][j] == 2)
			{
				//Genangan air
		  		setcolor (9);		
		  		cout << "~";		
		  		setcolor (7);
			}
				else if (peta[i][j] == 3)
			{
				//udin
		  		setcolor (11);		
		  		cout << "UD";		
		  		setcolor (7);
			}
			
	      		else if (peta[i][j] == 4)
			{
				//UCOK
		  		setcolor (4);		
		  		cout << "UC";		
		  		setcolor (7);
			}
	      		else if (peta[i][j] == 5)
			{
				//UJANG
		  		setcolor (13);		
		  		cout << "UJ";		
		  		setcolor (7);
			}
		  		else if (peta[i][j] == 6)
			{
				//Asep
		  		setcolor (11);		
		  		cout << "AS";		
		 		 setcolor (7);
			}
		  		else if (peta[i][j] == 7)
			{
				//Gunung
		  		setcolor (2);		
		  		cout << "^";		
		 		setcolor (7);
			}	
	      		else if (peta[i][j] == 8)
			{
				//Batu
		  		setcolor (8);		
		  		cout << "o";		
		  		setcolor (7);
			}
	     		else if (peta[i][j] == 9)
			{
				//Semak
		  		setcolor (10);		
		  		cout << "#";		
		  		setcolor (7);
			}
			else if (peta[i][j] == 10)
			{
				//RUMAH
		  		setcolor (6);		
		  		cout << "_";		
		  		setcolor (7);
			}
			else if (peta[i][j] == 11)
			{
				//RUMAH
		  		setcolor (6);		
		  		cout << "|";		
		  		setcolor (7);
			}
	     		else
	     	{
		}
	    }
	  cout << "\n";
	};
}

int main()
{
	int pil;
	int oke;
	
	setcolor(6);
    cout << "\t=======***======" << endl;
    setcolor(11);
    cout << "\t   Demo Game" << endl;
    setcolor(6);					
    cout << "\t=======***======" << endl; 

    cout << "1. Mulai Permainan\n2. Keluar\nPilihan : ";
    cin >> pil;
    switch (pil) 
    case 1 :
        system("cls");
        cout <<  "===   Welkam tu Gim UBER!   ===\n";
        cout <<  "===   BETA 1.0 !   ===\n";
        cout << "Insert any key : "; cin >> oke;
    while (true) 
		
	while (true)
	{
		// Gerak Player
		playerMovement(arrowKey);
		
		// Tampilan Peta
		displayMap();
		
		// Input Keyboard dan panduan
		cout << " \n";
		cout << "-----------------------\n";
		cout << "BERGERAK MENGGUNAKAN PANAH DI KEYBOARD\n";
		setcolor (10);
		cout << "# = Rumput\n";
		setcolor (2);
		cout << "^ = Gunung\n";
		setcolor (6);
		cout << "| dan _ = Bentukan Rumah\n";
		setcolor (8);
		cout << "o = Batu\n";
		setcolor (9);
		cout << "~ = Genangan Air\n";
		setcolor (4);
		cout << "UC = Enemey Ucok\n";
		setcolor (11);
		cout << "UD = Enemey Udin\n";
		setcolor (13);
		cout << "UJ = Enemy Ujang\n";
		setcolor (11);
		cout << "AS = Enemy Asep\n";
		setcolor (7);
		cout << ":) = Player\n";
		setcolor (7);
		cout << "-----------------------\n";
		cout << " Tekan ESC untuk keluar  \n";
		
		arrowKey = getch();
		
		//Clear Screen
		system("cls");

		// Hero Object
		Pemain player;
		player.name = "Nicholas Bojan";
		player.hp = 520;
		player.atk = 50;
		player.def = 25;

		// find pokemon
		if (peta[playerY][playerX] == 4)
		{
			// Pokemon Object
			Pokemon pokemonucok;
			pokemonucok.name = "Ucok,";
			pokemonucok.hp = 450;
			pokemonucok.atk = 50;
			pokemonucok.def = 22;

			while (true)
			{
				system("cls");

				char input_battle = ' ';
				cout << "\t ==kau bertemu " << pokemonucok.name << "Kapaksa kudu nyerang Bojan!!==" << endl;
				cout << player.name << ": " << player.hp << endl;
				cout << pokemonucok.name << ": " << pokemonucok.hp << endl;
				cout << "Pencet F untuk menyerang si ucok!" << endl;
				input_battle = getch();
	
				if (input_battle == 'f' || input_battle == 'F')
				{
					player.baseAtkPlayer(&pokemonucok.hp, &pokemonucok.def);
					pokemonucok.baseAtkPokemon(&player.hp, &player.def);
				}

				if (pokemonucok.hp <= 0)
				{
					peta[playerY][playerX] = 1;
					setcolor(6);
					cout << "Bojan telah menang melawan " << pokemonucok.name << endl;
					setcolor(7);
					
					cout << "[LOADING Mohon tunggu sebentar]" << endl;
					setcolor(7);
					
					Sleep(3000);
					system("cls");
					break;
				}
			}
		}
		if (peta[playerY][playerX] == 3 )
		{
			// Pokemon Object
			Pokemon pokemonudin;
			pokemonudin.name = "UDIN,";
			pokemonudin.hp = 110;
			pokemonudin.atk = 50;
			pokemonudin.def = 22;

			while (true)
			{
				system("cls");

				char input_battle = ' ';
				cout << "\t ==kau bertemu " << pokemonudin.name << "Kapaksa kudu nyerang Bojan!!==" << endl;
				cout << player.name << ": " << player.hp << endl;
				cout << pokemonudin.name << ": " << pokemonudin.hp << endl;
				cout << "Pencet F untuk menyerang si Udin!" << endl;
				input_battle = getch();
	
				if (input_battle == 'f' || input_battle == 'F')
				{
					player.baseAtkPlayer(&pokemonudin.hp, &pokemonudin.def);
					pokemonudin.baseAtkPokemon(&player.hp, &player.def);
				}

				if (pokemonudin.hp <= 0)
				{
					peta[playerY][playerX] = 1;
					setcolor(6);
					cout << "Bojan telah menang melawan " << pokemonudin.name << endl;
					setcolor(7);
					
					cout << "[LOADING Mohon tunggu sebentar]" << endl;
					setcolor(7);
					
					Sleep(3000);
					system("cls");
					break;
				}
			}
		}
		if (peta[playerY][playerX] == 5)
		{
			// Pokemon Object
			Pokemon pokemonujang;
			pokemonujang.name = "Ujang";
			pokemonujang.hp = 500;
			pokemonujang.atk = 225;
			pokemonujang.def = 100;

			while (true)
			{
				system("cls");

				char input_battle = ' ';
				cout << "\t==Kau menggangu " << pokemonujang.name << "Kapaksa kudu nyerang Bojan!!==" << endl;
				cout << player.name << ": " << player.hp << endl;
				cout << pokemonujang.name << ": " << pokemonujang.hp << endl;
				cout << "Pencet F untuk menyerang si Ujang!" << endl;
				input_battle = getch();

				if (input_battle == 'f' || input_battle == 'F')
				{
					player.baseAtkPlayer(&pokemonujang.hp, &pokemonujang.def);
					pokemonujang.baseAtkPokemon(&player.hp, &player.def);
				}

				if (player.hp <= 0)
				{
					peta[playerY][playerX] = 1;
					setcolor(6);
					cout << "Bojan telah kalah melawan " << pokemonujang.name << endl;
					setcolor(6);
						
					cout << "[LOADING Mohon tunggu sebentar]" << endl;
					setcolor(7);
					
					Sleep(3000);
					system("cls");
					break;
				}
			}
		}
		if (peta[playerY][playerX] == 6)
		{
			// Pokemon Object
			Pokemon pokemonasep;
			pokemonasep.name = "Asep";
			pokemonasep.hp = 500;
			pokemonasep.atk = 40;
			pokemonasep.def = 15;

			while (true)
			{
				system("cls");

				char input_battle = ' ';
				cout << "\t==Kau bertemu " << pokemonasep.name << ",Asep sedang membentakmu!==" << endl;
				cout << player.name << ": " << player.hp << endl;
				cout << pokemonasep.name << ": " << pokemonasep.hp << endl;
				cout << "Pencet F untuk membentak balik!" << endl;
				input_battle = getch();

				if (input_battle == 'f' || input_battle == 'F')
				{
					player.baseAtkPlayer(&pokemonasep.hp, &pokemonasep.def);
					pokemonasep.baseAtkPokemon(&player.hp, &player.def);
				}

				if (pokemonasep.hp <= 0)
				{
					peta[playerY][playerX] = 1;
					setcolor(6);
					cout << "Bojan menang mental dengan " << pokemonasep.name << endl;
					setcolor(7);
					
					cout << "[LOADING Mohon tunggu sebentar]" << endl;
					setcolor(7);
					
					Sleep(3000);
					system("cls");
					break;
				}
			}
		}
		else if (peta[playerY][playerX] == 2)
		{
			int chance;
			srand(time(NULL));
			chance = rand() % 10;

			if (chance < 4)
			{
				while(true)
				{
					system("cls");
					int choice;
					cout << "kamu menemukan monster, Bojan!"<<endl;
	      			cout << "1. Gelutan\n2. Lumpat" << endl;
	      			cout << "Segera pilih opsi anda!";
					choice = getch();
				
	      			if (choice == '1')
					{
	      				//Pokemon Object
						Pokemon pokemonucing;
						pokemonucing.name = "Ucing Hideung";
						pokemonucing.hp = 520;
						pokemonucing.atk = 30;
						pokemonucing.def = 15;
						
						while(true)
						{	
							system("cls");
							char input_battle = ' ';
							cout << "\t==Kau menemukan" << pokemonucing.name << " Kapaksa kudu nyerang Bojan!!==" << endl;
							cout << player.name << ": " << player.hp << endl;
							cout << pokemonucing.name << ": " << pokemonucing.hp << endl;
							cout << "Pencet F untuk menjinakan!" << endl;
							input_battle = getch();
							
							if (input_battle == 'f' || input_battle == 'F')
							{
								player.baseAtkPlayer(&pokemonucing.hp, &pokemonucing.def);
								pokemonucing.baseAtkPokemon(&player.hp, &player.def);
							}
							if (pokemonucing.hp <= 0)
							{
								setcolor(6);
								cout << "Bojan telah menjinakan " << pokemonucing.name << endl;
								setcolor(7);
								
								cout << "[LOADING Mohon tunggu sebentar]" << endl;
								setcolor(7);
								
								Sleep(2000);
								system("cls");
								break;
							}
						}
						break;
					}
					else if (choice == '2')
					{
						break;
					}
				
				}
			}
		}
	};
	getch();
	return 0;
}
