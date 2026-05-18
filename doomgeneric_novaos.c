#include <stdint.h>
#include <stdlib.h>

#include "m_argv.h"
#include "doomgeneric.h"

pixel_t* DG_ScreenBuffer = NULL;
uint32_t* fb;

/* =========================
   INIT VIDEO
   ========================= */
void DG_Init(void)
{
    fb = (uint32_t*)0xFD000000;
}

/* =========================
   DRAW FRAME
   ========================= */
void DG_DrawFrame(void)
{
    uint32_t* src = DG_ScreenBuffer;
    uint32_t* dst = fb;

    for (int i = 0; i < DOOMGENERIC_RESX * DOOMGENERIC_RESY; i++)
    {
        dst[i] = src[i];
    }
}

/* =========================
   INPUT / TIMER STUBS
   ========================= */
uint32_t DG_GetTicksMs(void)
{
    return 0; // TODO: conectar timer IRQ
}

int DG_GetKey(int* pressed, unsigned char* key)
{
    return 0; // TODO: teclado driver
}

void DG_SetWindowTitle(const char* title)
{
    (void)title;
}

/* =========================
   SLEEP (TEMP BUSY LOOP)
   ========================= */
void DG_SleepMs(uint32_t ms)
{
    for (volatile unsigned int i = 0; i < ms * 100000; i++)
        __asm__ volatile("nop");
}

/* =========================
   ARGS
   ========================= */
static char *argv[] =
{
    "doom",
    "-iwad",
    "doom1.wad",
    0
};

/* =========================
   ENTRY POINT
   ========================= */
void _start(void)
{
    DG_Init();

    doomgeneric_Create(3, argv);

    while (1)
        __asm__ volatile("hlt");
}

/* =========================
   DOOM INIT
   ========================= */
void doomgeneric_Create(int argc, char **argv)
{
    myargc = argc;
    myargv = argv;

    M_FindResponseFile();

    /* evita double init */
    if (!DG_ScreenBuffer)
    {
        DG_ScreenBuffer =
            malloc(DOOMGENERIC_RESX * DOOMGENERIC_RESY * sizeof(uint32_t));
    }

    if (!DG_ScreenBuffer)
    {
        while (1)
            __asm__ volatile("hlt");
    }

    D_DoomMain();
}