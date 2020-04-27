#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

int nScreenWidth = 800;
int nScreenHeight = 600;

class PixelFPS : public olc::PixelGameEngine {

private:
	const int nMapWidth = 8;
	const int nMapHeight = 8;

	int pixelMapWidth = 0;
	int pixelMapHeight = 0;

	int mapPixelHeight = 8;
	int mapPixelWidth = 8;

	float fPlayerPositionX = 3.0f;
	float fPlayerPositionY = 3.0f;

	float fPlayerAngle = 3.14 / 2;
	float fPlayerFOV = 3.14 / 4; //in Degrees. You have to convert this to Radians later by multiplying (180.0f/3.1459f);

	float fDepth = 6.0f;

	float fPlayerMovingSpeed = 2.0f;
	float fPlayerRotatingSpeed = 6.0f;

	std::wstring map;
	olc::Pixel *pMap = nullptr;

	void SetMapPixel(int x, int y,olc::Pixel p) {
		int mapx = x * mapPixelWidth;
		int mapy = y * mapPixelHeight;
		for (int tx = 0; tx < mapPixelWidth; tx++) {
			for (int ty = 0; ty < mapPixelHeight; ty++) {
				int mx = mapx + tx; int my = mapy + ty;
				if(mx >= 0 && mx < pixelMapWidth && my >=0 && my<pixelMapHeight)
					pMap[(mx) + (my)*pixelMapHeight] = p;
			}
		}
	}

	void ClearMap(olc::Pixel p = olc::BLUE) {
		for (int i = 0; i < pixelMapWidth * pixelMapHeight; i++) {
			pMap[i] = p;
		}
	}

	void DrawMapTOScreen(int locationX, int locationY) {
		for (int x = 0; x < pixelMapWidth; x++) {
			for (int y = 0; y < pixelMapHeight; y++) {
				Draw(x + locationX, y + locationY, pMap[x + y * pixelMapWidth]);
			}
		}
	}

public:
	bool OnUserCreate() override {
		//map += L"################################";
		//map += L"#..............................#";
		//map += L"#..............................#";
		//map += L"#..........####................#";
		//map += L"#..............................#";
		//map += L"#..............................#";
		//map += L"#..............................#";
		//map += L"#..............................#";
		//map += L"#..............................#";
		//map += L"#####..........................#";
		//map += L"#..............................#";
		//map += L"#..............................#";
		//map += L"#..............................#";
		//map += L"#..............................#";
		//map += L"#..............................#";
		//map += L"#..............................#";
		//map += L"#..............................#";
		//map += L"#..............................#";
		//map += L"#............#########.........#";
		//map += L"#............#########.........#";
		//map += L"#............#########.........#";
		//map += L"#............#########.........#";
		//map += L"#..............................#";
		//map += L"#..............................#";
		//map += L"#..............................#";
		//map += L"#..............................#";
		//map += L"#..............................#";
		//map += L"#.......#######................#";
		//map += L"#.......#######................#";
		//map += L"#..............................#";
		//map += L"#..............................#";
		//map += L"################################";

		//map += L"#########.......#########.......";
		//map += L"#...............#...............";
		//map += L"#.......#########.......########";
		//map += L"#..............##..............#";
		//map += L"#......##......##......##......#";
		//map += L"#......##..............##......#";
		//map += L"#..............##..............#";
		//map += L"###............####............#";
		//map += L"##.............###.............#";
		//map += L"#............####............###";
		//map += L"#..............................#";
		//map += L"#..............##..............#";
		//map += L"#..............##..............#";
		//map += L"#...........#####...........####";
		//map += L"#..............................#";
		//map += L"###..####....########....#######";
		//map += L"####.####.......######..........";
		//map += L"#...............#...............";
		//map += L"#.......#########.......##..####";
		//map += L"#..............##..............#";
		//map += L"#......##......##.......#......#";
		//map += L"#......##......##......##......#";
		//map += L"#..............##..............#";
		//map += L"###............####............#";
		//map += L"##.............###.............#";
		//map += L"#............####............###";
		//map += L"#..............................#";
		//map += L"#..............................#";
		//map += L"#..............##..............#";
		//map += L"#...........##..............####";
		//map += L"#..............##..............#";
		//map += L"################################";

		map += L"########";
		map += L"#.#....#";
		map += L"#....#.#";
		map += L"#....#.#";
		map += L"#......#";
		map += L"#...####";
		map += L"##.....#";
		map += L"########";

		pixelMapWidth = nMapWidth * mapPixelWidth;
		pixelMapHeight = nMapHeight * mapPixelHeight;
		pMap = new olc::Pixel[pixelMapWidth * pixelMapHeight];


		//fPlayerAngle = fPlayerAngle * (3.14f/ 180.0f );
		//fPlayerFOV = fPlayerFOV * (3.14f / 180.0f);
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override {
		for (int x = 0; x < ScreenWidth(); x++)
			for (int y = 0; y < ScreenHeight(); y++)
				Draw(x, y, olc::BLACK);

		ClearMap();
		//Handle Input
		if (GetKey(olc::J).bHeld) {
			fPlayerAngle -= (0.1f) * fElapsedTime * fPlayerRotatingSpeed;
		}
		if (GetKey(olc::L).bHeld) {
			fPlayerAngle += (0.1f) * fElapsedTime * fPlayerRotatingSpeed;
		}
		if (GetKey(olc::W).bHeld) {

			fPlayerPositionX += cos(fPlayerAngle) * fElapsedTime * fPlayerMovingSpeed;
			fPlayerPositionY += sin(fPlayerAngle) * fElapsedTime * fPlayerMovingSpeed;

			if (map[(int)fPlayerPositionX + (int)fPlayerPositionY * nMapWidth] == '#') {
				fPlayerPositionX -= cos(fPlayerAngle) * fElapsedTime * fPlayerMovingSpeed;
				fPlayerPositionY -= sin(fPlayerAngle) * fElapsedTime * fPlayerMovingSpeed;
			}
		}
		if (GetKey(olc::S).bHeld) {
			fPlayerPositionX -= cos(fPlayerAngle) * fElapsedTime * fPlayerMovingSpeed;
			fPlayerPositionY -= sin(fPlayerAngle) * fElapsedTime * fPlayerMovingSpeed;

			if (map[(int)fPlayerPositionX + (int)fPlayerPositionY * nMapWidth] == '#') {
				fPlayerPositionX += cos(fPlayerAngle) * fElapsedTime * fPlayerMovingSpeed;
				fPlayerPositionY += sin(fPlayerAngle) * fElapsedTime * fPlayerMovingSpeed;
			}
		}

		if (GetKey(olc::D).bHeld) {

			fPlayerPositionX -= sin(fPlayerAngle) * fElapsedTime * fPlayerMovingSpeed;
			fPlayerPositionY -= -cos(fPlayerAngle) * fElapsedTime * fPlayerMovingSpeed;

			if (map[(int)fPlayerPositionX + (int)fPlayerPositionY * nMapWidth] == '#') {
				fPlayerPositionX += sin(fPlayerAngle) * fElapsedTime * fPlayerMovingSpeed;
				fPlayerPositionY += -cos(fPlayerAngle) * fElapsedTime * fPlayerMovingSpeed;
			}
		}
		if (GetKey(olc::A).bHeld) {
			fPlayerPositionX += sin(fPlayerAngle) * fElapsedTime * fPlayerMovingSpeed;
			fPlayerPositionY += -cos(fPlayerAngle) * fElapsedTime * fPlayerMovingSpeed;

			if (map[(int)fPlayerPositionX + (int)fPlayerPositionY * nMapWidth] == '#') {
				fPlayerPositionX -= sin(fPlayerAngle) * fElapsedTime * fPlayerMovingSpeed;
				fPlayerPositionY -= -cos(fPlayerAngle) * fElapsedTime * fPlayerMovingSpeed;
			}
		}
		
		for (int x = 0; x < nMapWidth; x++) {
			for (int y = 0; y < nMapHeight; y++) {
				if (map[x + y * nMapWidth] == '#')
					SetMapPixel(x, y, olc::GREEN);
			}
		}

		SetMapPixel((int)fPlayerPositionX, (int)fPlayerPositionY, olc::RED);

		//Wall Drawing Routine
		for (int x = 0; x < ScreenWidth(); x++) {
			float fRayAngle = (fPlayerAngle - fPlayerFOV / 2.0f) + ((float)x / (float)ScreenWidth()) * fPlayerFOV;

			float fRayX = cos(fRayAngle);
			float fRayY = sin(fRayAngle);

			bool bHitWall = false;
			bool bBoundary = false;

			float fWallDistance = 0;

			while (!bHitWall && fWallDistance <= fDepth) {
				fWallDistance += 0.001f;

				int nRayPointX = fPlayerPositionX + fRayX * fWallDistance;
				int nRayPointY = fPlayerPositionY + fRayY * fWallDistance;

				if (nRayPointX >= nMapWidth || nRayPointY >= nMapHeight) {
					bHitWall = true;
				}
				else if (map[nRayPointX + nRayPointY * nMapWidth] == '#') {
					bHitWall = true;

					//I have no idea what the fuck is this doing
					std::vector<std::pair<float, float>> p;

					for (int tx = 0; tx < 2; tx++) {
						for (int ty = 0; ty < 2; ty++) {
							float vy = (float)nRayPointY + ty - fPlayerPositionY;
							float vx = (float)nRayPointX + tx - fPlayerPositionX;
							float d = sqrt(vx*vx + vy * vy);
							float dot = (fRayX * vx / d) + (fRayY * vy / d);
							p.push_back(std::make_pair(d, dot));
						}
					}

					std::sort(p.begin(), p.end(), [](const std::pair<float, float> &left, const std::pair<float, float> &right) {return left.first < right.first; });

					float fBound = 0.001f;
					if (acos(p.at(0).second) < fBound) bBoundary = true;
					if (acos(p.at(1).second) < fBound) bBoundary = true;

				}
			}

			int nCellin = (float)(ScreenHeight() / 2.0f) - (float)ScreenHeight() / (fWallDistance *2);
			int nFloor = ScreenHeight() - nCellin;
			float h = ( fWallDistance / fDepth)*255.0f;
			for (int y = 0; y < ScreenHeight(); y++) {
				if (y < nCellin) {
					Draw(x, y, olc::CYAN);
				}
				else if (y > nCellin && y < nFloor) {
					if (bHitWall) Draw(x, y, olc::Pixel((int)h, (int)h, (int)h));
					if (bBoundary) Draw(x, y, olc::BLACK);
				}
				else {
					Draw(x, y, olc::DARK_GREEN);
				}

				//for (int y = nCellin; y <= nFloor; y++) {
				//	if (bHitWall) Draw(x, y, olc::Pixel((int)h, (int)h, (int)h));
				//}
			}
		}

		DrawMapTOScreen(0, 0);
		return true;
	}
};

int main() {
	PixelFPS demo;
	demo.Construct(nScreenWidth, nScreenHeight, 1, 1);
	demo.Start();
	return 0;
}