#include "Track.h"


Track::Track() {
	field = new int* [track_height];

	for (int i = 0; i < track_height; i++) {
		field[i] = new int[track_width];
		for (int j = 0; j < track_width; j++) {
			field[i][j] = 0;
		}
	}

	freeSpace = 7;
}

void Track::Start()
{
	player.SetPos(field, 6, 14, track_width, track_height);

	enemy1 = Enemy(2, 3, -4, track_width, track_height);
	enemy2 = Enemy(3, 6, -13, track_width, track_height);

	std::thread playerController(&Player::Controller, std::ref(player), std::ref(field), track_width, track_height);
	std::thread updateController(&Track::Update, this);

	playerController.join();
	updateController.join();

	//Update();
}

void Track::Update()
{
	while (!player.IsDie()) {
		for (int i = 0; i < track_height; i++) {
			std::cout << std::endl;
			for (int j = 0; j < track_width; j++) {

				switch (field[i][j])
				{
				case 1: {
					color.SetColor(color.Green, color.Green);
					break;
				}
				case 2: {
					color.SetColor(color.Red, color.Red);
					break;
				}
				case 3: {
					color.SetColor(color.Blue, color.Blue);
					break;
				}
				default:
					color.SetColor(color.DarkGray, color.DarkGray);
				}


				std::cout << field[i][j] << " ";
			}
		}

		color.ResetColor();

		if (!enemy1.IsDie()) enemy1.Update(field, player);
		else GenerateEnemy(enemy1, enemy2);


		if (!enemy2.IsDie()) enemy2.Update(field, player);
		else GenerateEnemy(enemy2, enemy1);

		int boost = 500 - (player.GetScore() / 5);
		int speed = (player.GetScore() / 5) + 50;
		
		color.SetColor(color.Yellow);

		if(player.GetBestScore() > 0 && player.GetScore() < player.GetBestScore()) std::cout << "\n\nBest Score: " << player.GetBestScore() << std::endl;

		if(player.GetScore() > player.GetBestScore()) std::cout << "\nNEW Score: " << player.GetScore() << std::endl;
		else {
			std::cout << "\nScore: " << player.GetScore() << std::endl;
		}

		if (speed <= 150) color.SetColor(color.Green);
		if (speed > 250) color.SetColor(color.Red);

		std::cout << "Speed: " << speed << " Km/h" << std::endl;

		Sleep(boost >= 10 ? boost : 10);
		clear();
	}

	End();
}

void Track::GenerateEnemy(Enemy& enemy, Enemy& secondEnemy)
{
	int y = 0;

	if (secondEnemy.GetCoords().Y <= 0) y = (rand() % 10 <= 5) ? secondEnemy.GetCoords().Y - freeSpace : secondEnemy.GetCoords().Y - (freeSpace + 2);
	else  y = (rand() % 10 <= 5) ? -4  : secondEnemy.GetCoords().Y - 13;

	enemy.SetPos((rand() % 10 <= 5) ? 3 : 6, y);
}

void Track::End()
{
	clear();
	color.ResetColor();
	color.SetColor(color.Red);
	std::cout << "\n\t\tGAME OVER!";

	color.SetColor(color.DarkGray);

	if (player.GetScore() > player.GetBestScore()) {
		std::fstream ff;
		ff.open("score.txt", std::ios::in | std::ios::binary | std::ios::app);

		int bestScore = player.GetScore();
		ff.write((char*)&bestScore, sizeof(bestScore));

		std::cout << "\n\t\tNEW BEST SCORE: " << player.GetScore();
	}
	else std::cout << "\n\t\tSCORE: " << player.GetScore();
}
