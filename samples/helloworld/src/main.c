#include <coreinit/debug.h>

int main(int argc, char **argv)
{
	OSReport("Testing var args %d", argc);
	OSFatal("my first rpx");
	return 0;
}
