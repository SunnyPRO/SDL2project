#include "Environment.h"

CEnvironment::CEnvironment(int ScreenWidth, int ScreenHeight, float *passed_CameraX, float *passed_CameraY, CSDL_Setup* passed_csdl_setup)
{
	cout << "Constructor Environment" << endl;

	csdl_setup = passed_csdl_setup;

	CameraX = passed_CameraX;
	CameraY = passed_CameraY;

	for (int i = 0; i < 4; i++)
	for (int j = 0; j < 7; j++)
		grass[i][j] = new CSprite(csdl_setup->GetRenderer(), "Data/resources/environment/grass.bmp", ScreenWidth * i, ScreenHeight * j, ScreenWidth, ScreenHeight, CameraX, CameraY, CCollisionRectangle());
	
	Mode = LevelCreation;
	LoadFromFile();


	OnePressed = false;

	//trees.push_back(new Tree(300, 300, CameraX, CameraY, csdl_setup));
	//tree = new Tree(300, 300, CameraX, CameraY, csdl_setup);
}


CEnvironment::~CEnvironment()
{
	for (int i = 0; i < 4; i++)
	for (int j = 0; j < 7; j++)
		delete grass[i][j];

	for (vector<Tree*>::iterator i = trees.begin(); i != trees.end(); i++)
	{
		delete (*i);
	}
	trees.clear();
}


void CEnvironment::DrawBack()
{
	for (int i = 0; i < 4; i++)
	for (int j = 0; j < 7; j++)
		grass[i][j]->Draw();

	for (vector<Tree*>::iterator i = trees.begin(); i != trees.end(); i++)
	{
		(*i)->DrawTrunk();
	}
}

void CEnvironment::DrawFront()
{
	for (vector<Tree*>::iterator i = trees.begin(); i != trees.end(); i++)
	{
		(*i)->DrawCrown();
	}
}

void CEnvironment::LoadFromFile()
{
	ifstream LoadedFile("Data/LevelLayout.txt");

	string line;

	enum ObjectType
	{
		TypeNone,
		TypeTree
	};

	int CurrentType = TypeNone;

	if (LoadedFile.is_open())
	{
		while (LoadedFile.good())
		{
			getline(LoadedFile, line);
			if (line == "---====BEGIN_COORDONATES====---")
			{
				CurrentType = TypeTree;
			}
			else if (line == "---====END_COORDONATES====---")
			{
				CurrentType == TypeNone;
			}
			else if (CurrentType == TypeTree)
			{
				istringstream iss(line);

				int TempX = 0;
				int TempY = 0;
				string PreviousWord = "";

				while (iss)
				{
					string word;
					iss >> word;
					t_cout(15) << word;
					if (PreviousWord == "x:")
					{
						TempX = atoi (word.c_str()); // string to int
					}

					if (PreviousWord == "y:")
					{
						TempY = atoi(word.c_str()); // string to int
						trees.push_back(new Tree(TempX, TempY, CameraX, CameraY, csdl_setup));
					}

					PreviousWord = word;

				}
			}
		}
	}
	else
	{
		t_cout(12) << "File Could Not be Open: LevelLayout.txt";
	}
}

void CEnvironment::SaveToFile()
{
	ofstream LoadedFile;
	LoadedFile.open("Data/StageLayout.txt");

	LoadedFile << "---====BEGIN_COORDONATES====---" << endl; 

	for (vector<Tree*>::iterator i = trees.begin(); i != trees.end(); i++)
	{
		LoadedFile << "x: " << (*i)->GetX()
			       << "  y: " << (*i)->GetY() << endl;

	}

	LoadedFile << "---====END_COORDONATES====---" << endl;


	LoadedFile.close();

	t_cout(14) << "Level Saved!";
}

void CEnvironment::Update()
{
	if (Mode == LevelCreation)
	{
		if (csdl_setup->GetMainEvent()->type == SDL_KEYDOWN)
		{
			if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_2)
			{
				SaveToFile();
				OnePressed = true;
			}
		}
		if (csdl_setup->GetMainEvent()->type == SDL_KEYUP)
		{
			if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_2) //key send
			{
				OnePressed = false;
			}
		}

		if (csdl_setup->GetMainEvent()->type == SDL_KEYDOWN)
		{
			if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_1)
			{
				t_cout(14) << "ONE";
				trees.push_back(new Tree(-*CameraX + 275, -*CameraY + 90, CameraX, CameraY, csdl_setup));
				OnePressed = true;
			}
		}

		if (csdl_setup->GetMainEvent()->type == SDL_KEYUP)
		{
			if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_1) //key send
			{
				OnePressed = false;
			}
		}

		if (csdl_setup->GetMainEvent()->type == SDL_KEYDOWN)
		{
			if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_3)
			{

				if (trees.size() > 0)
				{
					delete trees[trees.size() - 1];

					trees.pop_back();
					t_cout(14) << "TREE POP BACK!";
				}
				OnePressed = true;
			}
		}

		if (csdl_setup->GetMainEvent()->type == SDL_KEYUP)
		{
			if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_3) //key send
			{
				OnePressed = false;
			}
		}
	}


	if (csdl_setup->GetMainEvent()->type == SDL_KEYDOWN)
	{
		if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_F1)
		{
			
			if (Mode == LevelCreation)
			{
				t_cout(14) << "MODE GAMEPLAY";
				Mode = GamePlay;
			}
			else if (Mode == GamePlay)
			{
				t_cout(14) << "MODE LevelCreation";
				Mode = LevelCreation;
			}
			OnePressed = true;
		}
	}
	if (csdl_setup->GetMainEvent()->type == SDL_KEYUP)
	{
		if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_F1) //key send
		{
			OnePressed = false;
		}
	}

}