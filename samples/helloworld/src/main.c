#include <coreinit_debug.h>
#include <gx2_init.h>

int main(int argc, char **argv)
{
	GX2Init();
	OSFatal("my first rpx");
	return 0;
}
