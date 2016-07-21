#include "cEnvironment.h"


cEnvironment::cEnvironment(int ScreenWidth, int ScreenHeight, float *passed_CameraX, float *passed_CameraY, cSDL_Setup* passed_csdl_setup)
{
	csdl_setup = passed_csdl_setup;

	CameraX = passed_CameraX;
	CameraY = passed_CameraY;

	for (int i = 0; i < 1; i++)
	for (int j = 0; j < 1; j++)
		grass[i][j] = new cSprite(csdl_setup->GetRenderer(), "Data/resources/environment/grass.bmp", ScreenWidth * i, ScreenHeight * j, ScreenWidth, ScreenHeight, CameraX, CameraY, cCollisionRectangle());
	
	Mode = LevelCreation;
	generateFromFile();


	OnePressed = false;

	//trees.push_back(new Tree(300, 300, CameraX, CameraY, csdl_setup));
	//tree = new Tree(300, 300, CameraX, CameraY, csdl_setup);
    
    cout << "Constructor Environment" << endl;
}


cEnvironment::~cEnvironment()
{
	for (int i = 0; i < 1; i++)
	for (int j = 0; j < 1; j++)
		delete grass[i][j];

	for (vector<cTree*>::iterator i = trees.begin(); i != trees.end(); i++)
	{
		delete (*i);
	}
	trees.clear();
    
    cout<< " cEnvironment Destroyed! "<<endl;
}



void cEnvironment::DrawBack()
{
	for (int i = 0; i < 1; i++)
	for (int j = 0; j < 1; j++)
		grass[i][j]->Draw();

	for (vector<cTree*>::iterator i = trees.begin(); i != trees.end(); i++)
	{
		(*i)->DrawTrunk();
	}
}

void cEnvironment::DrawFront()
{
	for (vector<cTree*>::iterator i = trees.begin(); i != trees.end(); i++)
	{
		(*i)->DrawCrown();
	}
}

void cEnvironment::generateFromFile()
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
			if (line == "BEGIN_COORDONATES")
			{
				CurrentType = TypeTree;
			}
			else if (line == "END_COORDONATES")
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
						trees.push_back(new cTree(TempX, TempY, CameraX, CameraY, csdl_setup));
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

void cEnvironment::SaveToFile()
{
	ofstream LoadedFile;
	LoadedFile.open("Data/StageLayout.txt");

	LoadedFile << "BEGIN_COORDONATES" << endl; 

	for (vector<cTree*>::iterator i = trees.begin(); i != trees.end(); i++)
	{
		LoadedFile << "x: " << (*i)->GetX()
			       << "  y: " << (*i)->GetY() << endl;

	}

	LoadedFile << "END_COORDONATES" << endl;


	LoadedFile.close();

	t_cout(14) << "Level Saved!";
}

void cEnvironment::Update()
{
	if (Mode == LevelCreation)
	{
		if (csdl_setup->GetMainEvent()->type == SDL_KEYDOWN)
		{
			if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_F2)
			{
				SaveToFile();
				OnePressed = true;
			}
		}
		if (csdl_setup->GetMainEvent()->type == SDL_KEYUP)
		{
			if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_F2) //key send
			{
				OnePressed = false;
			}
		}

		if (csdl_setup->GetMainEvent()->type == SDL_KEYDOWN)
		{
			if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_F4)
			{
				t_cout(14) << "ONE";
				trees.push_back(new cTree(-*CameraX + 275, -*CameraY + 90, CameraX, CameraY, csdl_setup));
				OnePressed = true;
			}
		}

		if (csdl_setup->GetMainEvent()->type == SDL_KEYUP)
		{
			if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_F4) //key send
			{
				OnePressed = false;
			}
		}

		if (csdl_setup->GetMainEvent()->type == SDL_KEYDOWN)
		{
			if (!OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_F3)
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
			if (OnePressed && csdl_setup->GetMainEvent()->key.keysym.sym == SDLK_F3) //key send
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