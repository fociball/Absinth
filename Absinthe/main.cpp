/** Example 006 2D Graphics

This Tutorial shows how to do 2d graphics with the Irrlicht Engine.
It shows how to draw images, keycolor based sprites,
transparent rectangles, and different fonts. You may consider
this useful if you want to make a 2d game with the engine, or if
you want to draw a cool interface or head up display for your 3d game.

As always, I include the header files, use the irr namespace,
and tell the linker to link with the .lib file.
*/
#include <irrlicht.h>
#include "driverChoice.h"
#include "irrMath.h"
#include <irrKlang.h>
#include <stdio.h>
#include <sstream>
#include <stdlib.h>
#include <ctime>

#if defined(WIN32)
#include <conio.h>
#else
#include "../common/conio.h"
#endif

using namespace irr;
using namespace irrklang;

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(lib, "irrKlang.lib")
#endif


class MyEventReceiver : public IEventReceiver
{
public:
    // This is the one method that we have to implement
    virtual bool OnEvent(const SEvent& event)
    {
        // Remember whether each key is down or up
        if (event.EventType == irr::EET_KEY_INPUT_EVENT)
            KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

        return false;
    }

    // This is used to check whether a key is being held down
    virtual bool IsKeyDown(EKEY_CODE keyCode) const
    {
        return KeyIsDown[keyCode];
    }
    
    MyEventReceiver()
    {
        for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
            KeyIsDown[i] = false;
    }

private:
    // We use this array to store the current state of each key
    bool KeyIsDown[KEY_KEY_CODES_COUNT];
};

bool isWithinWorld(int x, int y)
{
	
	if(x < 550 && y < 600 && x >=0 && y>=30)
		return true;
	else
		return false;
}


/*
At first, we let the user select the driver type, then start up the engine, set
a caption, and get a pointer to the video driver.
*/
int main()
{

	 srand((unsigned)time(0));

	// ask user for driver
	video::E_DRIVER_TYPE driverType=driverChoiceConsole();
	if (driverType==video::EDT_COUNT)
		return 1;

	// create device
	 MyEventReceiver receiver;

	IrrlichtDevice* device = createDevice(driverType,
            core::dimension2d<u32>(800,600), 16, false, false, false, &receiver);


	if (device == 0)
		return 1; // could not create selected driver.

	device->setWindowCaption(L"ABSIIIIIIIIIINTHE");

    video::IVideoDriver* driver = device->getVideoDriver();
    scene::ISceneManager* smgr = device->getSceneManager();

	 scene::ISceneNode * node = smgr->addSphereSceneNode();


	ISoundEngine* engine = createIrrKlangDevice();

	if (!engine)
      return 0; // error starting up the engine

	

	 irrklang::ISound* snd = engine->play2D("../../media/full-loop.ogg", true);
	
	

	/*
	All 2d graphics in this example are put together into one texture,
	2ddemo.png. Because we want to draw colorkey based sprites, we need to
	load this texture and tell the engine, which part of it should be
	transparent based on a colorkey.

	In this example, we don't tell it the color directly, we just say "Hey
	Irrlicht Engine, you'll find the color I want at position (0,0) on the
	texture.". Instead, it would be also possible to call
	driver->makeColorKeyTexture(images, video::SColor(0,0,0,0)), to make
	e.g. all black pixels transparent. Please note that
	makeColorKeyTexture just creates an alpha channel based on the color.
	*/
	video::ITexture* images = driver->getTexture("../../media/AbsintheTestSkyWalks.png");
	driver->makeColorKeyTexture(images, core::position2d<s32>(0,0));
		
	gui::IGUIFont* font = device->getGUIEnvironment()->getBuiltInFont();
    gui::IGUIFont* font2 =
        device->getGUIEnvironment()->getFont("../../media/bigfont.png");

	core::rect<s32> tables[10];
	int randomx[4], randomy[4], gridx[4], gridy[4];


	int r=1,j=0;

	for(int i=0;i<4;i++)
	{	
		gridx[i] = r;
		r+=97;
	}
			
	r=103;
	for(int i=0;i<4;i++)
	{
		gridy[i] = r;
		r+=94;
	}
	for(int i=0;i<4;i++)
	{
		randomx[i]=rand() % 5;
		randomy[i]=rand() % 5;
	}




	core::rect<s32> table0(965,675,1059,766);
	
	for(int i=0;i<10;i++)
		tables[i] = table0;

	core::rect<s32>	tablePos[4];

	tablePos[0] = core::rect<s32> (randomx[0], randomy[0],randomx[0]+94,randomy[0]+91);
	tablePos[1] = core::rect<s32> (randomx[1], randomy[1],randomx[1]+94,randomy[1]+91);
	tablePos[2] = core::rect<s32> (randomx[2], randomy[2],randomx[2]+94,randomy[2]+91);
	tablePos[3] = core::rect<s32> (randomx[3], randomy[3],randomx[3]+94,randomy[3]+91);

	core::rect<s32> playerwl1(891,630,926,766);
	core::rect<s32> playerwl2(928,630,963,766);
	core::rect<s32> playerwr1(1061,630,1096,766);		//create rect's for different player animations i.e: playerwl1= player walk left first frame
	core::rect<s32> playerwr2(1098,630,1133,766);
	core::rect<s32> playerwu1(1209,630,1244,766);
	core::rect<s32> playerwu2(1246,630,1281,766);
	core::rect<s32> playerwd1(1135,630,1170,766);
	core::rect<s32> playerwd2(1172,630,1207,766);

	core::rect<s32> ladyRedwl1(1324,632,1362,766);
	core::rect<s32> ladyRedwr1(1283,632,1322,766);
	core::rect<s32> ladyWhitewl1(1364,632,1403,766);
	core::rect<s32> ladyWhitewr1(1405,632,1443,766);
	core::rect<s32> ladyBluewl1(1445,632,1484,766);
	core::rect<s32> ladyBluewr1(1486,632,1524,766);
	core::rect<s32> paramonwl1(1526,632,1565,766);
	core::rect<s32> paramonwr1(1567,632,1606,766);

	core::rect<s32> sky(891,768,1690,859);


	
	/*
	Prepare a nicely filtering 2d render mode for special cases.
	*/
	driver->getMaterial2D().TextureLayer[0].BilinearFilter=true;
	driver->getMaterial2D().AntiAliasing=video::EAAM_FULL_BASIC;

	/*
	Everything is prepared, now we can draw everything in the draw loop,
	between the begin scene and end scene calls. In this example, we are
	just doing 2d graphics, but it would be no problem to mix them with 3d
	graphics. Just try it out, and draw some 3d vertices or set up a scene
	with the scene manager and draw it.
	*/

	int lastFPS = -1;

    // In order to do framerate independent movement, we have to know
    // how long it was since the last frame
    u32 then = device->getTimer()->getTime();

    // This is the movemen speed in units per second.
    const f32 MOVEMENT_SPEED = 50.f;

	




	core::rect<s32> patrons[7];

	
	patrons[0] = core::rect<s32>(500,200,539,339);
	patrons[1] = core::rect<s32>(123,454,162,593);
	patrons[2] = core::rect<s32>(94,130,133,269);
	patrons[3] = core::rect<s32>(400,430,439,596);
	patrons[4] = core::rect<s32>(300,330,339,469);
	patrons[5] = core::rect<s32>(450,430,489,569);


	int patronsx[6], patronsy[6];



		patronsx[0] =500;
		patronsx[1] =123;
		patronsx[2] =94;
		patronsx[3] =400;
		patronsx[4] =300;
		patronsx[5] =450;

		patronsy[0] = 200;
		patronsy[1] = 454;
		patronsy[2] = 130;
		patronsy[3] = 430;
		patronsy[4] = 330;
		patronsy[5] = 430;



	float PosX=300, PosY=120;
	float skyPos=0;
	int walkingFlag=0, collideFlag=0, timerCount=60; 
		long timerCount1=0;
	//core::rect<s32> currentPos(PosX,PosY,PosX+35,PosY+136)

	while(device->run() && driver)
	{
		if (device->isWindowActive())
		{
			
			const u32 now = device->getTimer()->getTime();
			const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
			then = now;

			u32 time = device->getTimer()->getTime();

			 core::vector3df nodePosition = node->getPosition();
			
			 core::rect<s32> playerPos(PosX,PosY,PosX+35, PosY+136);
		
			 timerCount=time/1000;
			
				if(receiver.IsKeyDown(irr::KEY_KEY_W) && isWithinWorld(PosX,PosY))
			{
				walkingFlag=3;
				PosY -= MOVEMENT_SPEED * frameDeltaTime;		
			}
			else if(receiver.IsKeyDown(irr::KEY_KEY_S) && isWithinWorld(PosX,PosY))
				{
				walkingFlag=1;
				PosY += MOVEMENT_SPEED * frameDeltaTime;	
			}
			else if(receiver.IsKeyDown(irr::KEY_KEY_W) && !isWithinWorld(PosX,PosY))
				{
				walkingFlag=3;
				PosY += 10;	
			}
			else if(receiver.IsKeyDown(irr::KEY_KEY_S) && !isWithinWorld(PosX,PosY))
				{
				walkingFlag=1;
				PosY -= 10;					
			}
			else if( walkingFlag >0 && walkingFlag < 8)
				walkingFlag--;
	

		
				
				
			if(receiver.IsKeyDown(irr::KEY_KEY_A) && isWithinWorld(PosX,PosY))
			{
				walkingFlag=5;
				PosX -= MOVEMENT_SPEED * frameDeltaTime;					
			}
			else if(receiver.IsKeyDown(irr::KEY_KEY_D) && isWithinWorld(PosX,PosY))
				{
				walkingFlag=7;
				PosX += MOVEMENT_SPEED*frameDeltaTime;					
			}
			else if(receiver.IsKeyDown(irr::KEY_KEY_A) && !isWithinWorld(PosX,PosY))
				{
				walkingFlag=5;
				PosX += 10;			
			}
			else if(receiver.IsKeyDown(irr::KEY_KEY_D) && !isWithinWorld(PosX,PosY))
				{
				walkingFlag=7;
				PosX -= 10;	
			}
			



	
				
			//engine->play2D(music, true);
			driver->beginScene(true, true, video::SColor(255,120,102,136));

			/*
			First, we draw 3 sprites, using the alpha channel we
			created with makeColorKeyTexture. The last parameter
			specifies that the drawing method should use this alpha
			channel. The last-but-one parameter specifies a
			color, with which the sprite should be colored.
			(255,255,255,255) is full white, so the sprite will
			look like the original. The third sprite is drawn
			with the red channel modulated based on the time.
			*/

			if(skyPos >= 0 && skyPos < 600) //loop sky outside window
			{
				skyPos += .001;
			}
			else if(skyPos >= 599)
				skyPos=0;

				driver->draw2DImage(images, core::position2d<s32>(skyPos,40), //draw sky
				sky, 0,
				video::SColor(255,255,255,255), true);

			// draw bar/background
			driver->draw2DImage(images, core::position2d<s32>(0,0),
				core::rect<s32>(21,332,820,931), 0,
				video::SColor(255,255,255,255), true);
	
			for(int i=0;i<10;i++)
			{
				
				for(int o=0;o<4;o++)
				{
					int y=randomx[o], l=randomy[o];
					driver->draw2DImage(images, core::position2d<s32>(gridx[y],gridy[l]),
					tables[i], 0,
					video::SColor(255, 255,255,255), true);
				}
				
			}


			for(int i=0, j=0;i<6;i++)
			{
				if(playerPos.isRectCollided(patrons[i]))
				{
					patronsx[i] = 1000;
					patronsy[i] = 1000;
					

					engine->play2D("../../media/scream1.mp3", false);
					patrons[i] = core::rect<s32>(1000,1000,1200,1200);
					j=1;
				}
				else if(!playerPos.isRectCollided(patrons[i]))
				{
						driver->draw2DImage(images, core::position2d<s32>(patronsx[0],patronsy[0]),
				ladyWhitewl1, 0,
				video::SColor(255, 255,255,255), true);
						driver->draw2DImage(images, core::position2d<s32>(patronsx[1],patronsy[1]),
									ladyWhitewr1, 0,
									video::SColor(255, 255,255,255), true);
						driver->draw2DImage(images, core::position2d<s32>(patronsx[2],patronsy[2]),
									ladyBluewl1, 0,
									video::SColor(255, 255,255,255), true);
						driver->draw2DImage(images, core::position2d<s32>(patronsx[3],patronsy[3]),
									ladyBluewr1, 0,
									video::SColor(255, 255,255,255), true);
						driver->draw2DImage(images, core::position2d<s32>(patronsx[4],patronsy[4]),
									paramonwl1, 0,
									video::SColor(255, 255,255,255), true);
							driver->draw2DImage(images, core::position2d<s32>(patronsx[5],patronsy[5]),
						paramonwr1, 0,
				video::SColor(255, 255,255,255), true);			
				}
			}

			




		
			if(walkingFlag==0)
			{
			// draw second flying imp with colorcylce
			driver->draw2DImage(images, core::position2d<s32>(PosX,PosY),
				playerwd1, 0,
				video::SColor(255, 255,255,255), true);
			}
			else if(walkingFlag==1)
			{
			// draw second flying imp with colorcylce
			driver->draw2DImage(images, core::position2d<s32>(PosX,PosY),
				(time/500 % 2) ? playerwd1 : playerwd2, 0,
				video::SColor(255, 255,255,255), true);
			}
			else if(walkingFlag==2)
			{
			// draw second flying imp with colorcylce
			driver->draw2DImage(images, core::position2d<s32>(PosX,PosY),
				 playerwu1, 0,
				video::SColor(255, 255,255,255), true);
			}
			else if(walkingFlag==3)
			{
			// draw second flying imp with colorcylce
			driver->draw2DImage(images, core::position2d<s32>(PosX,PosY),
				(time/500 % 2) ? playerwu1 : playerwu2, 0,
				video::SColor(255, 255,255,255), true);
			}
			else if(walkingFlag==4)
			{
			// draw second flying imp with colorcylce
			driver->draw2DImage(images, core::position2d<s32>(PosX,PosY),
				 playerwl1, 0,
				video::SColor(255, 255,255,255), true);
			}
				else if(walkingFlag==5)
			{
			// draw second flying imp with colorcylce
			driver->draw2DImage(images, core::position2d<s32>(PosX,PosY),
				(time/500 % 2) ? playerwl1 : playerwl2, 0,
				video::SColor(255, 255,255,255), true);
			}
					else if(walkingFlag==6)
			{
			// draw second flying imp with colorcylce
			driver->draw2DImage(images, core::position2d<s32>(PosX,PosY),
				playerwr1, 0,
				video::SColor(255, 255,255,255), true);
			}
						else if(walkingFlag==7)
			{
			// draw second flying imp with colorcylce
			driver->draw2DImage(images, core::position2d<s32>(PosX,PosY),
				(time/500 % 2) ? playerwr1 : playerwr2, 0,
				video::SColor(255, 255,255,255), true);
			}

			
	
			 // draw some other text
            if (font2)
                font2->draw(L"Clear out those patrons!",
                    core::rect<s32>(0,20,300,120),
                    video::SColor(255,255,255,255));

			 // draw some other text
            if (font2)
                font2->draw(L"You have 60 seconds to win.",
                    core::rect<s32>(0,70,300,120),
                    video::SColor(255,255,255,25));
	
	
		
			// draw some other text
            if (font2)
                font2->draw(core::stringc(timerCount),
                    core::rect<s32>(500,20,300,100),
                    video::SColor(255, time % 255,time % 255 ,255));

			if(patrons[0]==core::rect<s32>(1000,1000,1200,1200) && patrons[1]==core::rect<s32>(1000,1000,1200,1200) && patrons[2]==core::rect<s32>(1000,1000,1200,1200)
				 && patrons[3]==core::rect<s32>(1000,1000,1200,1200)  && patrons[4]==core::rect<s32>(1000,1000,1200,1200)  && patrons[5]==core::rect<s32>(1000,1000,1200,1200))
			{
				driver->draw2DRectangle(video::SColor(255,0,0,0),
                                  core::rect<s32>(0,0 ,driver->getScreenSize().Width, driver->getScreenSize().Height));
				//snd->stop();
				engine->play2D("../../media/game-win.mp3", false);

				 if (font2)
                font2->draw(L"YOU WINNNNNNNNNNN",
                    core::rect<s32>(0,20,300,120),
                    video::SColor(255,25,25,255));
			}

			

			if(timerCount==60)
			{
				driver->draw2DRectangle(video::SColor(255,0,0,0),
                                  core::rect<s32>(0,0 ,driver->getScreenSize().Width, driver->getScreenSize().Height));

				//snd->stop();
				engine->play2D("../../media/game-lose.mp3", false);

					 if (font2)
                font2->draw(L"YOU LOSE YOU SUCK",
                    core::rect<s32>(30,200,300,120),
                    video::SColor(25,25,25,255));

					 timerCount = 60;

					 
					 
			}

			smgr->drawAll(); // draw the 3d scene
			device->getGUIEnvironment()->drawAll(); // draw the gui environment (the logo)

			driver->endScene();

			int fps = driver->getFPS();

			if (lastFPS != fps)
			{
				core::stringw tmp(L"Absinthe Demo [");
				tmp += driver->getName();
				tmp += L"] fps: ";
				tmp += fps;

				device->setWindowCaption(tmp.c_str());
				lastFPS = fps;
			}
	
		}
	}

	device->drop();
	 engine->drop();
	return 0;
	}

/*
That's all. I hope it was not too difficult.
**/
