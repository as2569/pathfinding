#include <SDL.h>
#include <stdio.h>
#include <string.h>
#include "gf2d_graphics.h"
#include "gf2d_sprite.h"
#include "simple_logger.h"
#include "linked_list.h"
#include "tilemap.h"
#include "pathfinding.h"

int main(int argc, char * argv[])
{
	/*variable declarations*/
	int done = 0;
	const Uint8 * keys;
	Sprite *sprite;

	/*Queues */
	Node* checkList = NULL;
	Node* toCheckTail = NULL;
	Node* pathList = NULL;
	Node* pathListTail = NULL;
	
	/* Mouse variables*/
	int mx, my;
	float mf = 0;
	Sprite *mouse;
	Vector4D mouseColor = { 0,0,255,200 };
	
	TileMap *map; //map
	static Vector2D path[2]; //path to take
	
	char arr[642]; //map array
	int visited[642]; //visited array
	int camefrom[642];
	intVec2 current = { 2, 7 };
	int currentIndex = 0;
	Vector2D newVec = { 0, 0 };
	int next = 0;
	int goalIndex = 0;
	int startIndex = 0;
	Node* this_node;
	int pathlength;
	Vector2D * finalpath;

	/*program initializtion*/
	init_logger("gf2d.log");
	slog("---==== BEGIN ====---");
	gf2d_graphics_initialize(
		"gf2d",
		1200,
		720,
		1200,
		720,
		vector4d(0, 0, 0, 255),
		0);
	gf2d_graphics_set_frame_delay(17);
	gf2d_sprite_init(1024);
	SDL_ShowCursor(SDL_DISABLE);

	/*demo setup*/
	sprite = gf2d_sprite_load_image("images/backgrounds/bg_flat.png");
	mouse = gf2d_sprite_load_all("images/pointer.png", 32, 32, 16);
	map = tilemap_load("levels/tilemap.map");
	vector2d_copy(path[0], map->start);
	vector2d_copy(path[1], map->end);

	//populate array for map
	for (int i = 0; i <= 640; i++)
	{
		arr[i] = map->map[i];
	}
	arr[641] = '\0';
	//popular array for visited with zeros
	for (int i = 0; i <= 640; i++)
	{
		camefrom[i] = 0;
		visited[i] = 0;
	}
	
	//pathfinding algo
	next = MatrixToIndex(2, 7);
	checkList = push(checkList, &toCheckTail, next, 0);

	goalIndex = MatrixToIndex(7, 16);
	camefrom[71] = 999;

	//while(count(toCheckHead) > 0)
	while(checkList != NULL)
	{
		this_node = deq(&checkList);
		currentIndex = this_node->data;

		if (currentIndex == goalIndex)
		{
			printf("found goal");
		}

		next = TileAbove(currentIndex);
		if(arr[next] == '0')
		{
			if (visited[next] == 0)
			{
				checkList = push(checkList, &toCheckTail, next, 0);
				visited[next] = 1;
				camefrom[next] = currentIndex;
			}
		}

		next = TileRight(currentIndex);
		if (arr[next] == '0')
		{
			if (visited[next] == 0)
			{
				checkList = push(checkList, &toCheckTail, next, 0);
				visited[next] = 1;
				camefrom[next] = currentIndex;
			}
		}

		next = TileDown(currentIndex);
		if (arr[next] == '0')
		{
			if (visited[next] == 0)
			{
				checkList = push(checkList, &toCheckTail, next, 0);
				visited[next] = 1;
				camefrom[next] = currentIndex;
			}
		}

		next = TileLeft(currentIndex);
		if (arr[next] == '0')
		{
			if (visited[next] == 0)
			{
				checkList = push(checkList, &toCheckTail, next, 0);
				visited[next] = 1;
				camefrom[next] = currentIndex;
			}
		}

	}

	//construct a path
	currentIndex = goalIndex;
	pathList = push(pathList, &pathListTail, currentIndex, 0);

	while(currentIndex != 999)
	{
		currentIndex = camefrom[currentIndex];
		
		printf("\ncurrent %i camefrom %i", currentIndex, camefrom[currentIndex]);
		pathList = push(pathList, &pathListTail, currentIndex, 0);
		if (currentIndex == 71)
		{
			printf("\nat start");
			break;
		}
	}

	pathlength = count(pathList);
	printf("\nlen %i", pathlength);
	//pathlength++;
	
	//Vector2D finalpath[pathlength];
	finalpath = (Vector2D*)malloc(sizeof(Vector2D) * pathlength);
	memset(finalpath, 0, sizeof(Vector2D) * pathlength);

	for (int j = 0; j < pathlength; j++)
	{
		this_node = deq(&pathList);
		int row = RowFromIndex(this_node->data);
		int column = ColumnFromIndex(this_node->data);
		newVec.y = row;
		newVec.x = column;
		finalpath[j] = newVec;
	}

    /*main game loop*/
    while(!done)
    {
        SDL_PumpEvents();   // update SDL's internal event structures
        keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
        /*update things here*/
        SDL_GetMouseState(&mx,&my);
        mf+=0.1;
        if (mf >= 16.0)mf = 0;
        
        gf2d_graphics_clear_screen();// clears drawing buffers
        // all drawing should happen betweem clear_screen and next_frame

            //backgrounds drawn first
            gf2d_sprite_draw_image(sprite,vector2d(0,0));
                        
            tilemap_draw(map,vector2d(86,24));
            //tilemap_draw_path(path, 2, map, vector2d(86,24));
			tilemap_draw_path(finalpath, pathlength, map, vector2d(86, 24));

            //UI elements last
            gf2d_sprite_draw(
                mouse,
                vector2d(mx,my),
                NULL,
                NULL,
                NULL,
                NULL,
                &mouseColor,
                (int)mf);
        gf2d_grahics_next_frame();// render current draw frame and skip to the next frame
        
        if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition
		//slog("Rendering at %f FPS",gf2d_graphics_get_frames_per_second());
    }
    slog("---==== END ====---");
    return 0;
}
/*eol@eof*/
