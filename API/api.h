#ifndef API_H
#define API_H


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


#endif
