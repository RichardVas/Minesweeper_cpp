#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <ctime>
#include <utility>
#include <thread>

#include<fstream>
#include<cstdlib>
#include<sstream>

#include"flood.h"
#include"vld.h"


std::vector<std::vector<int>>grid;
std::vector<std::vector<int>>sgrid;

std::fstream f;

void traverseM(std::vector<std::vector<int>>& grid)
{
	for (int i = 0; i!=grid.size(); i++)
	{
		for (int j = 0; j!=grid[i].size(); j++)
		{
			std::cout << grid[i][j];

		}
		std::cout << std::endl;
	}

}



/*a tartalmazást ellenõrzõ fv legyen majd lambda*/
bool init(std::pair<int, int>&data, std::vector<std::pair<int, int>>&pile)
{
	bool bennevan = false;
	for (auto it = pile.begin(); it != pile.end(); it++)
	{
		if ((*it).first == data.first && (*it).second == data.second)
			bennevan = true;

	}
	return bennevan;
}

/*adja vissza a koordinátákat tartalmazó vectort ++ */
void Implement_Field(std::vector<std::vector<int>>& grid)
{
	

	/*generáljunk 10 bombát, a bombák mint egyediek legyenek, többször ne forduljanak elõ, a generált bombákat implementáljuk koord szerint*/
	srand(time(0));
	//legyen eleinte csak 10 akna, de a pozicíójuk mindig más legyen 
	/* legyen egy vector ami tartalmazza a párokat */
	/*az elkészült párokat rakjuk bele majd egy halmazba, hogy még1szer ne forduljanak elõa a párók, FONTOS*/
	
	std::vector<std::pair<int,int>> mines_coord;

	while (mines_coord.size() != 15)
	{
		std::pair<int, int> tmp;
		tmp = std::make_pair(rand()%10+1, rand()%10+1);
		

		if (mines_coord.empty()) {
			mines_coord.push_back(tmp);
		//	std::cout << "elsoelem\n";
		}

		if (!init(tmp, mines_coord))/*az a bug hogy az elsõ elemt bele kell rakni a mines_cordba és a többire ellenõrizni ezt */
		{
			mines_coord.push_back(tmp);
		//	std::cout << "nincsbenne\n";

		}
		/*else
			std::cout << "DUPLICATE!\n";*/

		
	}
	std::cout << "generált bombák : \n";
	for (auto &i : mines_coord)
		std::cout << i.first << "\t" << i.second << std::endl;
	
	/*feltölteni a gridet a generált bombákkal*/
	
	for (int i=0;i<grid.size();i++)
	{
		for (int j=0; j<grid.size();j++)
		{
			for (auto &k : mines_coord)
			{
				if ((k.first == i) && (k.second == j))
				{
					grid[i][j] = 9;
					
				}
			}
		}
	} 

	for (int i = 1; i <= grid.size()-2; i++)
		for (int j = 1; j <= grid.size()-2; j++)
		{
			int n = 0;
			if (grid[i][j] == 9) continue;
			if (grid[i + 1][j] == 9) n++;
			if (grid[i][j + 1] == 9) n++;
			if (grid[i - 1][j] == 9) n++;
			if (grid[i][j - 1] == 9) n++;
			if (grid[i + 1][j + 1] == 9) n++;
			if (grid[i - 1][j - 1] == 9) n++;
			if (grid[i - 1][j + 1] == 9) n++;
			if (grid[i + 1][j - 1] == 9) n++;
			grid[i][j] = n;
		}


}

void Setup(std::vector<std::vector<int>>& grid, std::vector<std::vector<int>>& sgrid)
{

	int i, j;
	for (i = 0; i < 12; i++)
	{
		std::vector<int>tmp;
		for (j = 0; j < 12; j++)
		{
			tmp.push_back(0);
		}
		grid.push_back(tmp);
		sgrid.push_back(tmp);
	}

	for (i = 0; i < 12; i++)
	{
		for (j = 0; j < 12; j++) {
			grid[i][j] = 0;
			sgrid[i][j] = 10;

			if (i == 0)
			{
				grid[i][j] = -1;
			}
			if (i == 11)
			{
				grid[i][j] = -1;
			}
			if (j == 0 || j == 11)
				grid[i][j] = -1;
		}
	}
	for (i = 0; i < 12; i++)
	{
		for (j = 0; j < 12; j++) {
			std::cout << grid[i][j];
		}
		std::cout << std::endl;
	}
	
}
void printM(std::vector<std::vector<int>>& grid)
{
	for (int i = 1;i<11; i++)
	{
		for (int j = 1; j<11; j++)
		{
			std::cout << grid[i][j];
					
		}
		std::cout << std::endl;
	}
}
void reveal(std::vector<std::vector<int>>& grid, std::vector<std::vector<int>>& sgrid)
{
	for (int i = 1; i <= sgrid.size()-2; i++)
		for (int j = 1; j <= sgrid.size()-2; j++)
		{
			sgrid[i][j] = grid[i][j];
		}
}


void floodFill(std::vector<std::vector<int>>& grid, int x, int y)
{
	if (grid[x][y] == 0 && !bennevane(vec, x, y))
	{

		/*grid[x][y] = 1;*/
		sgrid[x][y] = 0;

		vec.push_back(flood(x, y));
		floodFill(grid, x + 1, y);
		floodFill(grid, x - 1, y);
		floodFill(grid, x, y - 1);
		floodFill(grid, x, y + 1);
	}
	else
	{
		return;
	}

}

//a variable with static storage duration cannot be captured -> akkor nem is kell ?
auto score_lambda = []()
{
	//kiszámolni az sgrid felfedett értékeit, nem beleszámolva a bombákat, illetve a game-over helyzetet

	std::vector<int>score_table;
	int n = score_table.size();
	int sum_score = 0;

		
	for (int i = 0; i != sgrid.size(); i++)
		{
			for (int j = 0; j != sgrid[i].size(); j++)
			{
				if (sgrid[i][j] != 10 && sgrid[i][j] != 9 && sgrid[i][j]!=11 && sgrid[i][j]!=-1) {
					//a cellák 10tõl kezdõdidnek, azokat és a bombákat nem számoljuk, sem a zászlókat, sem a szegélyeket
					sum_score += sgrid[i][j];
					score_table.push_back(sum_score);

				}

			}
		}

		

	return sum_score;
};

/*kell egy fv, ami ellenõrzi az x,y koordok helyességét,
azaz, akkor jók, ha azok a LOAD, SAVE, vagy a pályámra mutatnak
*/

bool is_field_koord(int ix, int iy)
{
	bool helyes_field = false;
	int n = sgrid.size() - 1;
	if (ix <= n && iy <= n)
		helyes_field = true;

	return helyes_field;
}
/*a gomboknak meg kell számolnom, hol kezdõdnek a pixelek száma és hol végzõdnek*/
bool is_load_koord(int ix, int iy)
{
	bool helyes_load = false;
	int n = sgrid.size() - 1;
	//az x y koordok levannak kerekítve, 32es pixellel vannak számolva, hogy passzoljjon a képekhez
	if (ix >=14  && ix <= 17 && iy >=3 && iy <= 4 )
		helyes_load = true;

	return helyes_load;
}
bool is_save_koord(int ix, int iy)
{
	bool helyes_save = false;
	int n = sgrid.size() - 1;
	if (ix >= 14 && ix <= 17 && iy > 4 && iy <= 5)// 4el nem lehet egyenlõ, mert akkor egybefednék egymást
		helyes_save = true;

	return helyes_save;
}
/*fajlkezelo fvek implementalasa, majd azok meghívas a while ciklusban*/

//ellenorzni, hogy torent e mar mentes
bool is_file_exist(const char *fileName)
{
	std::ifstream infile(fileName);
	return infile.good();
}
/* kijavítani, és rájönni hogy miért nem volassa be az utolsó elemet */

int loadfromfile()
{
	int current_time=0;

	int tmpx, tmpy;


	// nyilvan csak akkor olvashatunk ,ha van mibõl
	
	if (is_file_exist("game_state.txt"))
	{
		f.open("game_state.txt", std::fstream::in | std::fstream::out | std::fstream::app);


		//ha létezik és olvashatjuk, akkor a jelenlegi sgrid elemeit írjuk felül a fájlban lévõ értékekkel.

		for (int i = 1; i != sgrid.size()-1 /*&& !f.eof()*/; i++)
		{
			for (int j = 1; j != sgrid[i].size()-1; j++)
			{
				f >> tmpx >> tmpy;

					sgrid[i][j] = tmpx;
					grid[i][j] = tmpy;
			}
			
		
		}
		/*miután az összes érték belett olvasva a meglelõ koordinátákra, azután az elõzõleg elmentett idõ lesz beolvasva*/
		f >> tmpx >> tmpy;
		current_time = tmpx;

		std::cout << current_time << "\t ido\n";
	}
	else
		std::cout << "nincs ilyen ilyen fajl\n";

	
	f.close();

	return current_time;

}

void savetofile(int curr_time)
{
	/*ha leztik mar ilyen fajl, akkor azt kiüritjuk majd felülírjuk az új sgrid adataival*/
	/* ha nem, akkor persze újat csinál*/
	f.open("game_state.txt", std::fstream::in | std::fstream::out | std::fstream::trunc);

	for (int i = 1; i != sgrid.size()-1; i++)
	{
		for (int j = 1; j != sgrid[i].size()-1; j++)
		{
			f << sgrid[i][j];
			f << "\t";
			f << grid[i][j];
			f << std::endl;
			// 2 adat kerül 1 sorba, így roppantúl könnyen lez olvasható
			/*elso az sgrid adott koord értéke másik meg a gridé*/
		}
		
	}

	f << curr_time;
	f << "\t";
	f << -1;

	f.close();
	
}
auto field_lambda = []() {
	Setup(grid, sgrid);
	Implement_Field(grid);

};
auto gui_lambda= []() {
	/*kezelni kell azt a hibát, hogy a koordináták validak legyenek a mátrix bejáráshoz
	ne omoljon össze, ha mellé kattintok + idõzítõ befejezése*/

	srand(time(0));
	sf::RenderWindow app(sf::VideoMode(640, 480), "Aknakeresõ!");
	bool isgameover = false;

	sf::Texture t;
	t.loadFromFile("tiles.jpg");
	sf::Sprite s(t);

	int jelen_ido = 0;

	//fontokat külsõleg kell hozzáadni, ez a basic
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		// error...
	}

	// CLOCK _ Timer1
	sf::Text t1;
	sf::Clock clock;
	int countdown = 30;
	int timer = clock.getElapsedTime().asSeconds();
	t1.setFont(font);
	t1.setCharacterSize(24);
	t1.setFillColor(sf::Color::Red);


	//LOAD_BUTTON

	sf::Texture l;
	l.loadFromFile("load_b.png");
	sf::Sprite lb(l);

	//SAVE BUTTON
	sf::Texture savet;
	savet.loadFromFile("save_b.png");
	sf::Sprite sb(savet);

	//SCORE
	sf::Text scr;
	int score;
	scr.setFont(font);
	scr.setCharacterSize(24);
	scr.setFillColor(sf::Color::Blue);


	//felbontás mérete tulajdonképpen
	int w = 32;

	//Setup(grid, sgrid);
	//Implement_Field(grid);
	traverseM(grid);
	printM(grid);


	while (app.isOpen())
	{

		int timer = clock.getElapsedTime().asSeconds();
			//std::cout << timer << std::endl;
		if (timer > 0 && countdown>0)
		{
			countdown--;
			t1.setString(std::to_string(countdown));

			clock.restart();
		}
		if (countdown == 0)
			isgameover = true;

		sf::Vector2i pos = sf::Mouse::getPosition(app);
		int x = pos.x / w;
		int y = pos.y / w;

		sf::Event e;
		while (app.pollEvent(e))
		{

			if (e.type == sf::Event::Closed)
				app.close();
			if (e.type == sf::Event::MouseButtonPressed) {

				
				/*le kell kezelni, ha pályán kívül kattintasz*/
				if (is_field_koord(x, y)) {
					if (e.key.code == sf::Mouse::Left) sgrid[x][y] = grid[x][y];
					else if (e.key.code == sf::Mouse::Right) sgrid[x][y] = 11;
					if (sgrid[x][y] == 9)
					{
						reveal(grid, sgrid);
						isgameover = true;
					}
					if (sgrid[x][y] == 0)
					{
						floodFill(grid, x, y);
					}
				}//sztem else ifekkel kéne elválasztani a kattintások helyét

					//LOAD BUTTON FUNCKIÓJA 
				if (is_load_koord(x, y)) {
					if (e.key.code == sf::Mouse::Left) {
						countdown = loadfromfile();
						isgameover = false;
						std::cout << countdown << "LOAD\n";

					}
				}
				//SAVE BUTTON FUNCKCIÓJA
				if (is_save_koord(x, y)) {
					if (e.key.code == sf::Mouse::Left) {
						savetofile(countdown);
						std::cout << "SAVE\n";

					}
				}




			}



		}
		
		if (!isgameover) {
			score = score_lambda();
		}
		app.clear(sf::Color::White);

		t1.setPosition(448, 64);
		//b1.setPosition(440, 100);

		//LOAD BUTTON 
		lb.setTextureRect(sf::IntRect(0, 0, 84, w));
		lb.setPosition(448, 128);
		app.draw(lb);
		//SAVE BUTTON
		sb.setTextureRect(sf::IntRect(0, 0, 84, w));
		sb.setPosition(448, 160);
		app.draw(sb);

		//TIMER
		app.draw(t1);

		//SCORE 
		scr.setString(std::to_string(score));
		scr.setPosition(448, 224);
		app.draw(scr);

		for (int i = 1; i <= sgrid.size()-2; i++)
			for (int j = 1; j <= sgrid.size()-2; j++)
			{
				s.setTextureRect(sf::IntRect(sgrid[i][j] * w, 0, w, w));
				s.setPosition(i*w, j*w);
				app.draw(s);

			}

		app.display();

	}


};
int main()
{
	std::thread t1(field_lambda);
	std::thread t2(gui_lambda);
	t1.join();
	t2.join();


	return 0;
}