#ifndef API_H
#define API_H

#ifndef ST_MAX
#define ST_MAX 32
#endif

#define ST_FRAME_SIZE 128

#ifndef ST_STACK_SIZE
#define ST_STACK_SIZE 128
#endif

char st_frame[ST_MAX][ST_FRAME_SIZE]={1};
char st_stack[ST_MAX][ST_STACK_SIZE]={1};
char st_busy[ST_MAX]={1};


//////////// Internal functions ////////////

void fork_sync(int a0, int a1, int a2, int a3, int a4, void *child_func, char *child_frame, char *child_stack);

int wait_sync(char *child_frame);

//////////// Full feature fork ////////////

inline void fork0(void *child_func, char *child_frame, char *child_stack)
	{fork_sync(0, 0, 0, 0, 0, child_func, child_frame, child_stack);}

inline void fork1(int a0, void *child_func, char *child_frame, char *child_stack)
	{fork_sync(a0, 0, 0, 0, 0, child_func, child_frame, child_stack);}

inline void fork2(int a0, int a1, void *child_func, char *child_frame, char *child_stack)
	{fork_sync(a0, a1, 0, 0, 0, child_func, child_frame, child_stack);}

inline void fork3(int a0, int a1, int a2, void *child_func, char *child_frame, char *child_stack)
	{fork_sync(a0, a1, a2, 0, 0, child_func, child_frame, child_stack);}

inline void fork4(int a0, int a1, int a2, int a3, void *child_func, char *child_frame, char *child_stack)
	{fork_sync(a0, a1, a2, a3, 0, child_func, child_frame, child_stack);}

inline void fork5(int a0, int a1, int a2, int a3, int a4, void *child_func, char *child_frame, char *child_stack)
	{fork_sync(a0, a1, a2, a3, a4, child_func, child_frame, child_stack);}


//////////// No-stack fork ////////////

inline void fork0NS(void *child_func, char *child_frame)
	{fork_sync(0, 0, 0, 0, 0, child_func, child_frame, 0);}

inline void fork1NS(int a0, void *child_func, char *child_frame)
	{fork_sync(a0, 0, 0, 0, 0, child_func, child_frame, 0);}

inline void fork2NS(int a0, int a1, void *child_func, char *child_frame)
	{fork_sync(a0, a1, 0, 0, 0, child_func, child_frame, 0);}

inline void fork3NS(int a0, int a1, int a2, void *child_func, char *child_frame)
	{fork_sync(a0, a1, a2, 0, 0, child_func, child_frame, 0);}

inline void fork4NS(int a0, int a1, int a2, int a3, void *child_func, char *child_frame)
	{fork_sync(a0, a1, a2, a3, 0, child_func, child_frame, 0);}

inline void fork5NS(int a0, int a1, int a2, int a3, int a4, void *child_func, char *child_frame)
	{fork_sync(a0, a1, a2, a3, a4, child_func, child_frame, 0);}


//////////// Wait ////////////

inline int wait(char *child_frame)
	{return wait_sync(child_frame);}

//////////// Block ////////////

int block1D(int x0, int x1, int dx, int (*shader_func)(int), int (*reduce_func)(int,int)) {

	int res = 0;
	int sid = 0;

	for(int i = 0; i < ST_MAX; ++i)
		st_busy[i] = 0;

	for (int i=x0; i<x1; i+=dx) {
		if(st_busy[sid])
			res = (*reduce_func)(res,wait(st_frame[sid]));
		fork1(i,(void*)shader_func,st_frame[sid],st_stack[sid]+ST_STACK_SIZE);
		st_busy[sid] = 1; sid = (sid+1)%ST_MAX;
	}

	for(sid = 0; sid < ST_MAX; ++sid)
		if(st_busy[sid])
			res = (*reduce_func)(res,wait(st_frame[sid]));

	return res;

}

int block2D(int x0, int x1, int dx, int y0, int y1, int dy, int (*shader_func)(int,int), int (*reduce_func)(int,int)) {

	int res = 0;
	int sid = 0;

	for(int i = 0; i < ST_MAX; ++i)
		st_busy[i] = 0;

	for (int i=x0; i<x1; i+=dx) {
		for (int j=y0; j<y1; j+=dy) {
			if(st_busy[sid])
				res = (*reduce_func)(res,wait(st_frame[sid]));
			fork2(i,j,(void*)shader_func,st_frame[sid],st_stack[sid]+ST_STACK_SIZE);
			st_busy[sid] = 1; sid = (sid+1)%ST_MAX;
		}
	}

	for(sid = 0; sid < ST_MAX; ++sid)
		if(st_busy[sid])
			res = (*reduce_func)(res,wait(st_frame[sid]));

	return res;

}

int block3D(int x0, int x1, int dx, int y0, int y1, int dy, int z0, int z1, int dz, int (*shader_func)(int,int,int), int (*reduce_func)(int,int)) {

	int res = 0;
	int sid = 0;

	for(int i = 0; i < ST_MAX; ++i)
		st_busy[i] = 0;

	for (int i=x0; i<x1; i+=dx) {
		for (int j=y0; j<y1; j+=dy) {
			for (int k=z0; k<z1; k+=dz) {
				if(st_busy[sid])
					res = (*reduce_func)(res,wait(st_frame[sid]));
				fork3(i,j,k,(void*)shader_func,st_frame[sid],st_stack[sid]+ST_STACK_SIZE);
				st_busy[sid] = 1; sid = (sid+1)%ST_MAX;
			}
		}
	}

	for(sid = 0; sid < ST_MAX; ++sid)
		if(st_busy[sid])
			res = (*reduce_func)(res,wait(st_frame[sid]));

	return res;

}

#endif