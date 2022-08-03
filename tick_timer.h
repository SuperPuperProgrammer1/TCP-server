#define SEC 11
#define MILLISEC 12
#define NANOSEC 13

uint64_t timer_init(){
	uint64_t c, d, tick1;	
	asm volatile("rdtsc" : "=a" (c), "=d" (d));
	tick1 = (((uint64_t)c) | (((uint64_t)d) << 32)); 
	return tick1;
}

uint64_t timer_start(){
	return timer_init();
}

uint64_t timer_stop(uint64_t tick1){
	 return timer_init()-tick1;
}

float timer_look(uint64_t finaltick, int key){  
	float time;
	switch(key){
		case 11:
			time = finaltick/3292713105;
			return time;
			break;
		case 12:
			time = finaltick/3292713.105;
			return time;
			break;
		case 13:
			time=finaltick/3.292713105;
			return time;
			break;
	}
}



