#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class MarioCartExample : public olc::PixelGameEngine {
public:
	MarioCartExample() {
		sAppName = "MarioCartExample";
	}

public:
	bool OnUserCreate() override {

		//Converting angles to radions
		fPlayerAngle = fPlayerAngle * 3.14259f / 180.0f;
		fPlayerFOV = fPlayerFOV * 3.14259f / 180.0f;
		fPlayerFOVHalf = fPlayerFOV / 2;
		fPlayerTanFOVHalf = tanf(fPlayerFOVHalf);
		fPlayerRotatingSpeed = fPlayerRotatingSpeed * 3.14259f / 180.0f;

		fdNear = sqrtf(fZNear * fZNear + (fZNear * fPlayerTanFOVHalf) * (fZNear * fPlayerTanFOVHalf));
		fdFar = sqrtf(fZFar * fZFar + (fZFar * fPlayerTanFOVHalf) * (fZFar * fPlayerTanFOVHalf));
		
		//Calculating nScreenOriginY
		if(fScreenOriginY > 0 && fScreenOriginY < 1) nScreenOriginY = roundf((float)ScreenHeight() * fScreenOriginY);
		else nScreenOriginY = ScreenHeight() / 2;
		
		//Loading the Ground Sprite
		sprGround = new olc::Sprite("MarioKartLevel.png");
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override {
		//Handling Input
		if (GetKey(olc::W).bHeld) {
			fPlayerPositionX += cosf(fPlayerAngle) * fPlayerMovingSpeed * fElapsedTime;
			fPlayerPositionY += sinf(fPlayerAngle) * fPlayerMovingSpeed * fElapsedTime;
		}
		if (GetKey(olc::S).bHeld) {
			fPlayerPositionX -= cosf(fPlayerAngle) * fPlayerMovingSpeed * fElapsedTime;
			fPlayerPositionY -= sinf(fPlayerAngle) * fPlayerMovingSpeed * fElapsedTime;
		}
		if (GetKey(olc::D).bHeld) {
			fPlayerPositionX += sinf(fPlayerAngle) * fPlayerMovingSpeed * fElapsedTime;
			fPlayerPositionY -= cosf(fPlayerAngle) * fPlayerMovingSpeed * fElapsedTime;
		}
		if (GetKey(olc::A).bHeld) {
			fPlayerPositionX -= sinf(fPlayerAngle) * fPlayerMovingSpeed * fElapsedTime;
			fPlayerPositionY += cosf(fPlayerAngle) * fPlayerMovingSpeed * fElapsedTime;
		}
		if (GetKey(olc::J).bHeld) {
			fPlayerAngle += fPlayerRotatingSpeed * fElapsedTime;
		}
		if (GetKey(olc::L).bHeld) {
			fPlayerAngle -= fPlayerRotatingSpeed * fElapsedTime;
		}


		//if (GetKey(olc::U).bHeld) {
		//	fZFar += 1.0f;
		//	fdFar = sqrtf(fZFar * fZFar + (fZFar * fPlayerTanFOVHalf) * (fZFar * fPlayerTanFOVHalf));
		//}
		//if (GetKey(olc::I).bHeld) {
		//	fZFar -= 1.0f;
		//	fdFar = sqrtf(fZFar * fZFar + (fZFar * fPlayerTanFOVHalf) * (fZFar * fPlayerTanFOVHalf));
		//}
		//if (GetKey(olc::O).bHeld) {
		//	fZNear += 0.1f;
		//	fdNear = sqrtf(fZNear * fZNear + (fZNear * fPlayerTanFOVHalf) * (fZNear * fPlayerTanFOVHalf));
		//}
		//if (GetKey(olc::P).bHeld) {
		//	fZNear -= 0.1f;
		//	fdNear = sqrtf(fZNear * fZNear + (fZNear * fPlayerTanFOVHalf) * (fZNear * fPlayerTanFOVHalf));
		//}


		float fNearX1 = fPlayerPositionX + cosf(fPlayerAngle + fPlayerFOVHalf) * fdNear;
		float fNearY1 = fPlayerPositionY + sinf(fPlayerAngle + fPlayerFOVHalf) * fdNear;
		float fNearX2 = fPlayerPositionX + cosf(fPlayerAngle - fPlayerFOVHalf) * fdNear;
		float fNearY2 = fPlayerPositionY + sinf(fPlayerAngle - fPlayerFOVHalf) * fdNear;

		float fFarX1 = fPlayerPositionX + cosf(fPlayerAngle + fPlayerFOVHalf) * fdFar;
		float fFarY1 = fPlayerPositionY + sinf(fPlayerAngle + fPlayerFOVHalf) * fdFar;
		float fFarX2 = fPlayerPositionX + cosf(fPlayerAngle - fPlayerFOVHalf) * fdFar;
		float fFarY2 = fPlayerPositionY + sinf(fPlayerAngle - fPlayerFOVHalf) * fdFar;


		for (int y = 0; y < ScreenHeight() - nScreenOriginY; y++) {

			float fSampleDepth = (float)y / (float)(ScreenHeight() - nScreenOriginY);
			
			float fStartX = (fFarX1 - fNearX1) / fSampleDepth + fNearX1;
			float fStartY = (fFarY1 - fNearY1) / fSampleDepth + fNearY1;

			float fEndX = (fFarX2 - fNearX2) / fSampleDepth + fNearX2;
			float fEndY = (fFarY2 - fNearY2) / fSampleDepth + fNearY2;

			for (int x = 0; x < ScreenWidth(); x++) {
				float fSampleWidth = (float)x / (float)ScreenWidth();
				float fSampleX = (fEndX - fStartX) * fSampleWidth + fStartX;
				float fSampleY = (fEndY - fStartY) * fSampleWidth + fStartY;

				int nSampleX = (int)roundf(fSampleX);
				int nsampleY = (int)roundf(fSampleY);

				nSampleX = nSampleX % sprGround->width;
				nsampleY = nsampleY % sprGround->height;
				

				Draw(x, nScreenOriginY + y, sprGround->GetPixel(nSampleX, nsampleY));
			}
		}

		return true;
	}

private:
	olc::Sprite *sprGround = nullptr;

	float fScreenOriginY = 0.3f; //This has to be in between 0 and 1. This can take less than 0.5f. We can fine tune it and find the sweet spot later

	int nScreenOriginY = 0; //This will be calculated in runtime

	//Player tranformations
	float fPlayerPositionX = 10000.0f;
	float fPlayerPositionY = 10000.0f;
	float fPlayerAngle = 90; //This is in degrees. You need to convert this to radians in OnUserCreate

	float fPlayerMovingSpeed = 100.0f;
	float fPlayerRotatingSpeed = 45.0f; //In degrees

	float fZFar = 10.0f;
	float fZNear = 1.0f;

	float fPlayerFOV = 90.0f; //This is in degrees. (0 < fPlayerFOV < 180, fPlayerFOV must not be 0 or 180)
	float fPlayerFOVHalf = 0.0f; //You need to assign this to the half of the fPlayerFOV (in radions)
	float fPlayerTanFOVHalf = 0.0f; //This will be calculated in runtime

	float fdNear = 0.0f; //This will be calculated in runtime
	float fdFar = 0.0f; //This will be calculated in runtime
};

#pragma region EntryPoint
int main(int argc, char* argv[]) {
	MarioCartExample game;
	if (game.Construct(300, 150, 4, 4))
		game.Start();
}
#pragma endregion
