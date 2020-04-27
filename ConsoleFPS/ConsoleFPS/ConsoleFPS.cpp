#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <unordered_map>
//using namespace std;

#include <Windows.h>

int nScreenWidth =120;
int nScreenHeight = 30;

const int nMapWidth = 20;
const int nMapHeight = 20;

float fPlayerX = 4.0f;
float fPlayerY = 4.0f;

float fPlayerAngle = 3.14 / 2;
float fFOV = 3.14 / 4;

float fDepth = 20.0f;

float fRotaionSpeed = 10.0f;
float fMovingSpeed = 10.0f;

int main() {
	SMALL_RECT rect;
	rect.Top = 0;
	rect.Left = 0;
	rect.Bottom = nScreenHeight - 1;
	rect.Right = nScreenWidth - 1;
	HANDLE hwnd = GetStdHandle(STD_OUTPUT_HANDLE);
	wchar_t *screen = new wchar_t[nScreenWidth * nScreenHeight]; 
	// This creates the console screen buffer and return us a handle to that screen buffer
	// Writing this buffer to the Console screen done by windows itself once we call the right functions
	HANDLE hConsole = CreateConsoleScreenBuffer(
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL
	);
	//This function make our cnosole window to use the buffer we created above;
	SetConsoleActiveScreenBuffer(hConsole);
	//SetConsoleWindowInfo()
	if (SetConsoleWindowInfo(hwnd, TRUE, &rect))
		return 1;
	DWORD dwBytesWritten = 0;

	char map[] =
		"####################"
		"#..................#"
		"#..................#"
		"#..................#"
		"#..................#"
		"#..................#"
		"#..................#"
		"#..................#"
		"#........###.......#"
		"#........###.......#"
		"#..................#"
		"#..................#"
		"#..................#"
		"#..................#"
		"#..................#"
		"#..................#"
		"#..................#"
		"#..................#"
		"#..................#"
		"####################"
		;

	//This is just a test to make shadows. It doesn't work. Let's just comment it out untill I figure it out :)

	//	int nLightSourceX = 0;
	//	int nLightSourceY = 0;
	//
	//	std::unordered_map<int, int> m ;
	//
	//	for (int nY = 0; nY < nMapHeight; nY++) {
	//		for (int nX = 0; nX < nMapWidth; nX++) {
	//			if (map[nX + nY * nMapWidth] == 'L') {
	//				nLightSourceX = nX;
	//				nLightSourceY = nY;
	//				goto here;
	//			}
	//		}
	//	}
	//here:
	//	
	//	for (float fLightRayAngle = 0; fLightRayAngle < 2 * 3.14; fLightRayAngle += 0.1f) {
	//		float fLRayX = cos(fLightRayAngle);
	//		float fLRayY = sin(fLightRayAngle);
	//
	//		float fLWallDistance = 0;
	//
	//		bool bLHitWall = false;
	//
	//		while (!bLHitWall) {
	//			fLWallDistance += 0.1f;
	//			int fLRayPointX = nLightSourceX + fLRayX * fLWallDistance;
	//			int fLRayPointY = nLightSourceY + fLRayY * fLWallDistance;
	//
	//			if (map[fLRayPointX + fLRayPointY * nMapWidth] == '#') {
	//				if (m.find(fLRayPointX + fLRayPointY * nMapWidth) == m.end()) {
	//					m[fLRayPointX + fLRayPointY * nMapWidth] = 9;
	//				}
	//			}
	//		}
	//	}
	
	auto tp1 = std::chrono::system_clock::now();
	auto tp2 = std::chrono::system_clock::now();

	while (true) {
		tp2 = std::chrono::system_clock::now();
		std::chrono::duration<float> elapsedTime = tp2 - tp1;
		tp1 = tp2;
		float fElapsedTime = elapsedTime.count();

		if (GetAsyncKeyState((unsigned short)'J') & 0x8000) {
			fPlayerAngle -= (0.1f) * fElapsedTime * fRotaionSpeed;
		}
		if (GetAsyncKeyState((unsigned short)'L') & 0x8000) {
			fPlayerAngle += (0.1f) * fElapsedTime * fRotaionSpeed;
		}
		if (GetAsyncKeyState((unsigned short)'W') & 0x8000) {

			fPlayerX += cos(fPlayerAngle) * fElapsedTime * fMovingSpeed;
			fPlayerY += sin(fPlayerAngle) * fElapsedTime * fMovingSpeed;

			if (map[(int)fPlayerX + (int)fPlayerY * nMapWidth] == '#') {
				fPlayerX -= cos(fPlayerAngle) * fElapsedTime * fMovingSpeed;
				fPlayerY -= sin(fPlayerAngle) * fElapsedTime * fMovingSpeed;
			}
		}
		if (GetAsyncKeyState((unsigned short)'S') & 0x8000) {
			fPlayerX -= cos(fPlayerAngle) * fElapsedTime * fMovingSpeed;
			fPlayerY -= sin(fPlayerAngle) * fElapsedTime * fMovingSpeed;

			if (map[(int)fPlayerX + (int)fPlayerY * nMapWidth] == '#') {
				fPlayerX += cos(fPlayerAngle) * fElapsedTime * fMovingSpeed;
				fPlayerY += sin(fPlayerAngle) * fElapsedTime * fMovingSpeed;
			}
		}

		if (GetAsyncKeyState((unsigned short)'D') & 0x8000) {

			fPlayerX -= sin(fPlayerAngle) * fElapsedTime * fMovingSpeed;
			fPlayerY -= -cos(fPlayerAngle) * fElapsedTime * fMovingSpeed;

			if (map[(int)fPlayerX + (int)fPlayerY * nMapWidth] == '#') {
				fPlayerX += sin(fPlayerAngle) * fElapsedTime * fMovingSpeed;
				fPlayerY += -cos(fPlayerAngle) * fElapsedTime * fMovingSpeed;
			}
		}
		if (GetAsyncKeyState((unsigned short)'A') & 0x8000) {
			fPlayerX += sin(fPlayerAngle) * fElapsedTime * fMovingSpeed;
			fPlayerY += -cos(fPlayerAngle) * fElapsedTime * fMovingSpeed;

			if (map[(int)fPlayerX + (int)fPlayerY * nMapWidth] == '#') {
				fPlayerX -= sin(fPlayerAngle) * fElapsedTime * fMovingSpeed;
				fPlayerY -= -cos(fPlayerAngle) * fElapsedTime * fMovingSpeed;
			}
		}

		for (int x = 0; x < nScreenWidth; x++) {

			float fRayAngle = (fPlayerAngle - fFOV / 2.0f) + ((float)x / (float)nScreenWidth) * fFOV;


			//This is the unit vector of the ray that indicates the direction of the ray		
			float fRayX = cos(fRayAngle);
			float fRayY = sin(fRayAngle);

			bool bHitWall = false;
			bool bBoundary = false;

			float fWallDistcance = 0;


			while (!bHitWall && fWallDistcance <= fDepth) {

				fWallDistcance += 0.1f;
			
				int nRayPointX = fPlayerX + fRayX * fWallDistcance;
				int nRayPointY = fPlayerY + fRayY * fWallDistcance;

				if (nRayPointX >= nMapWidth || nRayPointY >= nMapHeight) {
					bHitWall = true;
				}
				else if (map[nRayPointX + nRayPointY * nMapWidth] == '#') {
					bHitWall = true;
					
					//I have no idea what the fuck is this doing
					std::vector<std::pair<float, float>> p;

					for (int tx = 0; tx < 2; tx++) {
						for (int ty = 0; ty < 2; ty++) {
							float vy = (float)nRayPointY + ty - fPlayerY;
							float vx = (float)nRayPointX + tx - fPlayerX;
							float d = sqrt(vx*vx + vy * vy);
							float dot = (fRayX * vx / d) + (fRayY * vy / d);
							p.push_back(std::make_pair(d, dot));
						}
					}

					std::sort(p.begin(), p.end(), [](const std::pair<float, float> &left, const std::pair<float, float> &right) {return left.first < right.first; });
					
					float fBound = 0.0005f;
					if (acos(p.at(0).second) < fBound) bBoundary = true;
					if (acos(p.at(1).second) < fBound) bBoundary = true;
					
				}

			}

			int nCellin = (float)(nScreenHeight / 2.0f) - (float)nScreenHeight / (fWallDistcance * 0.5);
			int nFloor = nScreenHeight - nCellin;

			for (int y = 0; y < nScreenHeight; y++) {
				if (y < nCellin) {
					screen[x + y * nScreenWidth] = ' ';
				}
				else if (y == nCellin && bHitWall) screen[x + y * nScreenWidth] = '_';
				else if (y > nCellin && y < nFloor) {
					if (bHitWall) {
						if (fWallDistcance < 3.0f)		screen[x + y * nScreenWidth] = '&'; //0x2588;	//'&'; //
						else if (fWallDistcance < 5.0f)	screen[x + y * nScreenWidth] = '#'; //0x2593;	//'#'; //
						else if (fWallDistcance < 7.0f)	screen[x + y * nScreenWidth] = 'x'; //0x2592;	//'x'; //
						else							screen[x + y * nScreenWidth] = '.'; //0x2591;	//'.'; //
					}
					else {
						screen[x + y * nScreenWidth] = ' ';
					}
					if (bBoundary) {
						screen[x + y * nScreenWidth] = ' ';
					}
				}
				else if (y == nFloor && bHitWall) screen[x + y * nScreenWidth] = '-';
				else {
					screen[x + y * nScreenWidth] = ' ';
				}
			}

		}



		screen[nScreenWidth * nScreenHeight - 1] = '\0';
		WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
	}

	return 0;
}