#include "common.h"

static struct {
  uint32_t a, b, c, d;
  uint32_t count;
} xorwow_state;

static uint32_t xorwow() {

	uint32_t t = xorwow_state.d;

	uint32_t s = xorwow_state.a;
	xorwow_state.d = xorwow_state.c;
	xorwow_state.c = xorwow_state.b;
	xorwow_state.b = s;

	t ^= t >> 2;
	t ^= t << 1;
	t ^= s ^ (s << 4);
	xorwow_state.a = t;

	xorwow_state.count += 362437;
	return t + xorwow_state.count;
}


uint8_t map[12][12];
uint8_t map_revealed[12][12];

static SHIP ships[12];

static void paint_ship(const SHIP *ship) {
	
	if (ship->o==0) {
		for (uint8_t i=0; i<ship->sz+2; i++) {
			
			map[ship->x+i-1][ship->y-1] = WATER;
			map[ship->x+i-1][ship->y+0] = WATER;
			map[ship->x+i-1][ship->y+1] = WATER;
		}

		for (uint8_t i=0; i<ship->sz; i++)
			map[ship->x+i][ship->y] = SHIP_CENTER_VERTICAL;

		map[ship->x           ][ship->y] = SHIP_TOP;
		map[ship->x+ship->sz-1][ship->y] = SHIP_BOTTOM;
		
	} else {
		for (uint8_t i=0; i<ship->sz+2; i++) {
			
			map[ship->x-1][ship->y+i-1] = WATER;
			map[ship->x+0][ship->y+i-1] = WATER;
			map[ship->x+1][ship->y+i-1] = WATER;
		}

		for (uint8_t i=0; i<ship->sz; i++)
			map[ship->x][ship->y+i] = SHIP_CENTER_HORIZONTAL;

		map[ship->x][ship->y           ] = SHIP_LEFT;
		map[ship->x][ship->y+ship->sz-1] = SHIP_RIGHT;
	}

	if (ship->sz==1) {
		
		map[ship->x][ship->y] = SHIP_SUB;
	}
}

static uint8_t place_ships(const uint8_t *ship_sizes, uint8_t N) {
	
	
	SHIP *ship = ships + N;
	ship->sz = ship_sizes[N];
	
	if (ship->sz==0) return 1;
	
	for (uint8_t t=0; t<100; t++) {
		
		while (true) {
			
			uint16_t r = xorwow() & 0xFFFF;
			
			ship->o = ((r&0x100)==0);
			if (ship->o==0) {
				
				ship->x = 1+ (r&0xF);
				ship->y = 1+((r&0xF0)>>4);
				if (ship->x+ship->sz-1>10) continue;
				if (ship->y>10) continue;
				if (map[ship->x][ship->y] != EMPTY) continue;
			} else {
				
				ship->x = 1+ (r&0xF);
				ship->y = 1+((r&0xF0)>>4);
				if (ship->x>10) continue;
				if (ship->y+ship->sz-1>10) continue;
				if (map[ship->x][ship->y] != EMPTY) continue;
			}
			break;
		}
		uint8_t found = 0;
		if (ship->o==0) {
			for (uint8_t i=1; i<ship->sz; i++) 
				if (map[ship->x+i][ship->y] != EMPTY) found = 1; 
		} else {
			for (uint8_t i=1; i<ship->sz; i++) 
				if (map[ship->x][ship->y+i] != EMPTY) found = 1; 
		}
		if (found) continue;

		
		paint_ship(ship);

		
		uint8_t success = place_ships(ship_sizes, N+1);
		if (success) return 1;

		for (uint8_t i=0; i<12; i++)
			for (uint8_t j=0; j<12; j++)
				map[i][j] = EMPTY;
		
		for (uint8_t i=0; i<N; i++)
			paint_ship(ship+i);
		
	}
	return 0;
}

static void generateMap() {
	
//	const uint8_t ship_sizes[] = {4,3,3,2,2,2,1,1,1,1,0};
	const uint8_t ship_sizes_rank[][11] = {
		{1,1,1,1,0,0,0,0,0,0,0},
		{2,1,1,1,1,0,0,0,0,0,0},
		{2,2,2,1,1,1,1,0,0,0,0},
		{3,2,2,2,1,1,1,1,0,0,0},
		{3,3,2,2,2,1,1,1,1,0,0},
		{4,3,3,2,2,2,1,1,1,1,0},
		{4,3,3,2,2,2,1,1,1,1,0},
		{4,3,3,2,2,2,1,1,1,1,0},
		{4,3,3,2,2,2,1,1,1,1,0},
		{4,3,3,2,2,2,1,1,1,1,0},
		{4,3,3,2,2,2,1,1,1,1,0},
		{4,3,3,2,2,2,1,1,1,1,0},
	};
	
	for (uint8_t i=0; i<12; i++) {
		for (uint8_t j=0; j<12; j++) {
			
			map[i][j] = EMPTY;
		}
	}
	
	while (!place_ships(ship_sizes_rank[rank],0));
}

static int8_t solveMap(uint8_t n) {
	
	if (ships[n].sz==0) return 1;
	return 1;
	/*
	
	if (solver_frameCount>30) return -1;
	
	for (uint8_t i=1; i<12; i++) {
		uint8_t free_sum = 0;
		uint8_t ship_sum_actual = 0;
		uint8_t ship_sum_expected = 0;
		for (uint8_t j=1; j<12; j++) {
			if (map[i][j]>WATER) {
				ship_sum_expected = 0;
			}
			if (solveMap[i][j]>WATER) {
				ship_sum_actual = 0;
			}
			if (solveMap[i][j]>WATER) {
				ship_sum_actual = 0;
			}
		}
	}*/
}

void init_map() {

	xorwow_state.a = 0x12345678U ^ rand16();
	xorwow_state.b = 0x56781234U ^ rand16();
	xorwow_state.c = 0x34567878U ^ rand16();
	xorwow_state.d = 0x81238123U ^ rand16();
	xorwow_state.count = 0xDEADBEEFU ^ rand16();

	while (true) {
		
		//paged_isr.f = nullptr;
		generateMap();
		
		uint8_t subsRevealed = 0;
		for (uint8_t i=1; i<11; i++) {
			for (uint8_t j=1; j<11; j++) {
				
				if (map[i][j]==EMPTY) {
					map[i][j]=WATER;
				}				
				
				map_revealed[i][j]=EMPTY;
				
//				map_revealed[i][j] = map[i][j];
				
				uint8_t easyness = 9;
				if (rank>5) easyness -= (rank-5);
				
				if ((xorwow()&0xFF)<easyness)
					map_revealed[i][j] = map[i][j];

				if (subsRevealed<2 && map[i][j]==SHIP_SUB && (xorwow()&0xF)<easyness) {
					subsRevealed++;
					map_revealed[i][j] = map[i][j];
				}

				if (map[i][j]>SHIP_SUB && (xorwow()&0x3F)<easyness)
					map_revealed[i][j] = map[i][j];
			}
		}
		
		if (solveMap(0)==1) break;
	}
	
}
