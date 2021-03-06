#include <gccore.h>
#include <stdio.h>
#include <stdlib.h>
#include <wiiuse/wpad.h>
#include "roll.h"

#define COUNT 4

static void *xfb = NULL;

static GXRModeObj *rmode = NULL;

void setup()
{
	VIDEO_Init();

	WPAD_Init();

	rmode = VIDEO_GetPreferredMode(NULL);

	xfb = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));

	console_init(xfb, 20, 20, rmode->fbWidth, rmode->xfbHeight,
		rmode->fbWidth * VI_DISPLAY_PIX_SZ);

	VIDEO_Configure(rmode);

	VIDEO_SetNextFramebuffer(xfb);

	VIDEO_SetBlack(FALSE);

	VIDEO_Flush();

	VIDEO_WaitVSync();

	if (rmode->viTVMode & VI_NON_INTERLACE)
		VIDEO_WaitVSync();
}

int main()
{
	u32 button;

	setup();

	srand(time(NULL));

	printf("\x1b[2;0HPress A to roll or HOME to exit.\n");

	while (true)
	{
		WPAD_ScanPads();

		button = WPAD_ButtonsDown(0);

		if (button & WPAD_BUTTON_A)
		{
			roll(COUNT);

			printf("\n\n");
		}

		else if (button & WPAD_BUTTON_HOME)
			exit(0);

		VIDEO_WaitVSync();
	}

	return 0;
}
