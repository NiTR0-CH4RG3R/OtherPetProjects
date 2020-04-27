
#include <algorithm>
#include "olcConsoleGameEngineGL.h"

class ConsoleFPS : public olcConsoleGameEngine {
public:
	ConsoleFPS() {
		m_sAppName = L"ConsoleFPS";
	}

private:
	void ClearScreen() {
		for (int y = 0; y < ScreenHeight(); y++)
			for (int x = 0; x < ScreenWidth(); x++)
				Draw(x, y, PIXEL_SOLID, FG_BLACK);
	}

	void ClassifyPixel(float luminance, short &sym, short &fg_col, short &bg_col) {
		
		int pixel_bw = (int)roundf(luminance * 10.0f);

		switch (pixel_bw) {
		//case 0: bg_col = BG_BLACK; fg_col = FG_BLACK; sym = PIXEL_SOLID; break;

		case 0: bg_col = BG_BLACK; fg_col = FG_DARK_GREY; sym = PIXEL_QUARTER; break;
		case 1: bg_col = BG_BLACK; fg_col = FG_DARK_GREY; sym = PIXEL_HALF; break;
		case 2: bg_col = BG_BLACK; fg_col = FG_DARK_GREY; sym = PIXEL_THREEQUARTERS; break;
		case 3: bg_col = BG_BLACK; fg_col = FG_DARK_GREY; sym = PIXEL_SOLID; break;



		case 4: bg_col = BG_DARK_GREY; fg_col = FG_GREY; sym = PIXEL_QUARTER; break;
		case 5: bg_col = BG_DARK_GREY; fg_col = FG_GREY; sym = PIXEL_HALF; break;
		case 6: bg_col = BG_DARK_GREY; fg_col = FG_GREY; sym = PIXEL_THREEQUARTERS; break;
		case 7: bg_col = BG_DARK_GREY; fg_col = FG_GREY; sym = PIXEL_SOLID; break;


		case 8:  bg_col = BG_GREY; fg_col = FG_WHITE; sym = PIXEL_QUARTER; break;
		case 9:	 bg_col = BG_GREY; fg_col = FG_WHITE; sym = PIXEL_HALF; break;
		//case 10: bg_col = BG_GREY; fg_col = FG_WHITE; sym = PIXEL_THREEQUARTERS; break;
		//case 11: bg_col = BG_GREY; fg_col = FG_WHITE; sym = PIXEL_SOLID; break;
		}
	}

public:
	bool OnUserCreate() override {

		//Initialize the map
		map += L"########";
		map += L"#.#....#";
		map += L"#....#.#";
		map += L"#....#.#";
		map += L"#......#";
		map += L"#...####";
		map += L"##.....#";
		map += L"########";

		fPlayerAngle = fPlayerAngle * 3.141592f / 180.0f;
		fPlayerFOV = fPlayerFOV * 3.141592f / 180.0f;

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override {
		//ddClearScreen();

		//InputHandle
		if (m_keys[L'W'].bHeld) {
			fPlayerPositionX += cosf(fPlayerAngle) * fElapsedTime * fPlayerMovingSpeed;
			fPlayerPositionY += sinf(fPlayerAngle) * fElapsedTime * fPlayerMovingSpeed;

			if (map[(int)roundf(fPlayerPositionX) + (int)roundf(fPlayerPositionY) * nMapWidth] == L'#') {
				fPlayerPositionX -= cosf(fPlayerAngle) * fElapsedTime * fPlayerMovingSpeed;
				fPlayerPositionY -= sinf(fPlayerAngle) * fElapsedTime * fPlayerMovingSpeed;
			}
		}
		if (m_keys[L'S'].bHeld) {
			fPlayerPositionY -= sinf(fPlayerAngle) * fElapsedTime * fPlayerMovingSpeed;
			fPlayerPositionX -= cosf(fPlayerAngle) * fElapsedTime * fPlayerMovingSpeed;

			if (map[(int)roundf(fPlayerPositionX) + (int)roundf(fPlayerPositionY) * nMapWidth] == L'#') {
				fPlayerPositionX += cosf(fPlayerAngle) * fElapsedTime * fPlayerMovingSpeed;
				fPlayerPositionY += sinf(fPlayerAngle) * fElapsedTime * fPlayerMovingSpeed;
			}
		}
		if (m_keys[L'D'].bHeld) {
			fPlayerPositionX += sinf(fPlayerAngle) * fElapsedTime * fPlayerMovingSpeed;
			fPlayerPositionY -= cosf(fPlayerAngle) * fElapsedTime * fPlayerMovingSpeed;

			if (map[(int)roundf(fPlayerPositionX) + (int)roundf(fPlayerPositionY) * nMapWidth] == L'#') {
				fPlayerPositionX -= sinf(fPlayerAngle) * fElapsedTime * fPlayerMovingSpeed;
				fPlayerPositionY += cosf(fPlayerAngle) * fElapsedTime * fPlayerMovingSpeed;
			}
		}
		if (m_keys[L'A'].bHeld) {
			fPlayerPositionX -= sinf(fPlayerAngle) * fElapsedTime * fPlayerMovingSpeed;
			fPlayerPositionY += cosf(fPlayerAngle) * fElapsedTime * fPlayerMovingSpeed;

			if (map[(int)roundf(fPlayerPositionX) + (int)roundf(fPlayerPositionY) * nMapWidth] == L'#') {
				fPlayerPositionX += sinf(fPlayerAngle) * fElapsedTime * fPlayerMovingSpeed;
				fPlayerPositionY -= cosf(fPlayerAngle) * fElapsedTime * fPlayerMovingSpeed;
			}
		}
		if (m_keys[L'J'].bHeld) {
			fPlayerAngle += fElapsedTime * fPlayerRotatingSpeed;
		}
		if (m_keys[L'L'].bHeld) {
			fPlayerAngle -= fElapsedTime * fPlayerRotatingSpeed;
		}

		//Drawing routine
		for (int x = 0; x < ScreenWidth(); x++) {
			
			//Ray Angle in Degrees (clockwise)
			float fRayAngle = (fPlayerAngle + fPlayerFOV / 2) - (float)x * fPlayerFOV / ScreenWidth();
			
			//Ray anlgle in 2D Vector format
			float fRayDirectionX = cosf(fRayAngle);
			float fRayDirectionY = sinf(fRayAngle);

			float fWallDistance = 0.0f;
			bool bHitWall = false;
			bool bBoundary = false;

			while (!bHitWall && fWallDistance < fPlayerDepth) {
				fWallDistance += 0.001f;
				int nRayCurrentPositionX = roundf(fPlayerPositionX + fWallDistance * fRayDirectionX);
				int nRayCurrentPositionY = roundf(fPlayerPositionY + fWallDistance * fRayDirectionY);
				
				if (map[nRayCurrentPositionX + nRayCurrentPositionY * nMapWidth] == L'#') {
					bHitWall = true;
					//I have no idea what the fuck is this doing
					std::vector<std::pair<float, float>> p;

					for (int tx = 0; tx < 2; tx++) {
						for (int ty = 0; ty < 2; ty++) {
							float vy = (float)nRayCurrentPositionX + ty - fPlayerPositionX;
							float vx = (float)nRayCurrentPositionY + tx - fPlayerPositionY;
							float d = sqrt(vx*vx + vy * vy);
							float dot = (fRayDirectionX * vx / d) + (fRayDirectionY * vy / d);
							p.push_back(std::make_pair(d, dot));
						}
					}

					std::sort(p.begin(), p.end(), [](const std::pair<float, float> &left, const std::pair<float, float> &right) {return left.first < right.first; });

					float fBound = 0.001f;
					if (acos(p.at(0).second) < fBound) bBoundary = true;
					if (acos(p.at(1).second) < fBound) bBoundary = true;
				}
			}

			int nCellin = (float)ScreenHeight() / 2 - (float)ScreenHeight() / (fWallDistance);
			int nFloor = ScreenHeight() - nCellin;

			float luminance = 1.0f - fWallDistance / fPlayerDepth;

			for (int y = 0; y < ScreenHeight(); y++) {
				short sym = PIXEL_SOLID;
				short fg_col = 0x0;
				short bg_col = 0x0;

				if (y < nCellin) {
					Draw(x, y, PIXEL_SOLID, FG_BLACK);
				}
				else if (y >= nCellin && y <= nFloor) {

					if (bHitWall) {

							ClassifyPixel(luminance, sym, fg_col, bg_col);
							Draw(x, y, sym, fg_col | bg_col);

					}
					else {
						Draw(x, y, PIXEL_SOLID, FG_BLACK);
					}
					if (bBoundary) { Draw(x, y, PIXEL_SOLID, FG_BLACK); }

				}
				else {
					Draw(x, y, PIXEL_SOLID, FG_BLACK);
				}
			}
		}

		return true;
	}

private:
	int nMapWidth = 8;
	int nMapHeight = 8;
	std::wstring map;

	float fPlayerPositionX = 3.0f;
	float fPlayerPositionY = 3.0f;
	float fPlayerAngle = 90.0f; //In degrees
	float fPlayerFOV = 45.0f; //In degrees
	float fPlayerDepth = 6.0f;
	float fPlayerMovingSpeed = 2.0f;
	float fPlayerRotatingSpeed = 2.0f;
};

int main() {
	ConsoleFPS demo;
	if (demo.ConstructConsole(600, 300, 1, 1))
		demo.Start();
	return 0;
}