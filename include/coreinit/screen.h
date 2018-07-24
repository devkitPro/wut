#pragma once
#include <wut.h>

/**
 * \defgroup coreinit_screen Screen
 * \ingroup coreinit
 *
 * <!-- quick blurb - may show up on Modules page -->
 * Software-rendered graphics system, suitable for text output and simple
 * graphics.
 *
 * OSScreen is much more straightforward than GX2, which makes it appealing for
 * situations that do not require complex graphics. It can draw text and pixels
 * (one at a time!) to both the Gamepad and TV.
 *
 * To use OSScreen, first call \link OSScreenInit \endlink. Then, allocate a
 * memory area and pass it to OSScreen with \link OSScreenSetBufferEx \endlink -
 * after enabling the screens with \link OSScreenEnableEx \endlink, the library
 * will be ready to draw! Drawing is accomplished with \link
 * OSScreenClearBufferEx \endlink, \link OSScreenPutFontEx \endlink and \link
 * OSScreenPutPixelEx \endlink. Once drawing is complete, call \link
 * OSScreenFlipBuffersEx \endlink to show the results on-screen. Rinse and
 * repeat!
 *
 * <!-- Documentation meta: OSScreen has a weird naming convention, especially
 *      around the word "buffer". So, here's what we're doing:
 *      - A single framebuffer is a "buffer".
 *      - The framebuffer that is visible is the "visible buffer" while the one
 *        being drawn to is the "work buffer"
 *      - The pointers going to OSScreenSetBufferEx are not buffers. Try "memory
 *        area", "location", whatever.
 *      - A "screen" refers to the Gamepad or TV.
 *      - Members of OSScreenID are not buffers. Try "screen ID".
 *      This should help prevent confusion. If you change this, make sure to
 *      update all the docs to keep everything consistent. -->
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

//! Defines the ID of a display usable with OSScreen.
typedef enum OSScreenID
{
   //! Represents the TV connected to the system.
   SCREEN_TV      = 0,
   //! Represents the screen in the DRC (gamepad).
   SCREEN_DRC     = 1,
} OSScreenID;

/**
 * Initialises the OSScreen library for use. This function must be called before
 * using any other OSScreen functions.
 *
 * \sa <ul>
 * <li>\link OSScreenSetBufferEx \endlink</li>
 * <li>\link OSScreenEnableEx \endlink</li>
 * <li>\link OSScreenShutdown \endlink</li>
 * </ul>
 */
void
OSScreenInit();

/**
 * Cleans up and shuts down the OSScreen library.
 *
 * \sa <ul>
 * <li>\link OSScreenEnableEx \endlink</li>
 * </ul>
 */
void
OSScreenShutdown();

/**
 * Gets the amount of memory required to fit both buffers of a given screen.
 *
 * \param screen
 * The ID of the screen to be sized.
 *
 * \sa <ul>
 * <li>\link OSScreenSetBufferEx \endlink</li>
 * </ul>
 */
uint32_t
OSScreenGetBufferSizeEx(OSScreenID screen);

/**
 * Sets the memory location for both buffers of a given screen. This location
 * must be of the size prescribed by \link OSScreenGetBufferSizeEx \endlink and
 * at an address aligned to 0x100 bytes.
 *
 * \param screen
 * The ID of the screen whose memory location should be changed.
 *
 * \param addr
 * Pointer to the memory to use. This area must be 0x100 aligned, and of the
 * size given by \link OSScreenGetBufferSizeEx \endlink.
 *
 * \sa <ul>
 * <li>\link OSScreenGetBufferSizeEx \endlink</li>
 * </ul>
 */
void
OSScreenSetBufferEx(OSScreenID screen,
                    void *addr);

/**
 * Clear the work buffer of the given screen by setting all of its pixels to
 * a given colour.
 *
 * \param screen
 * The ID of the screen to clear. Only the work buffer will be cleared.
 *
 * \param colour
 * The colour to use, in big-endian RGBX8 format - 0xRRGGBBXX, where X bits are
 * ignored.
 *
 * \note
 * Since this function only affects the <em>work buffer</em>, its effect will
 * not appear on screen immediately. See \link OSScreenFlipBuffersEx \endlink.
 *
 * \sa <ul>
 * <li>\link OSScreenPutFontEx \endlink</li>
 * <li>\link OSScreenPutPixelEx \endlink</li>
 * </ul>
 *
 * <!-- TODO: Are the XX bits really ignored? I'm basing this off a vague memory
 * of setting them to 00 and nothing changing... Check this. -->
 */
void
OSScreenClearBufferEx(OSScreenID screen,
                      uint32_t colour);

/**
 * Swap the buffers of the given screen. The work buffer will become the visible
 * buffer and will start being shown on-screen, while the visible buffer becomes
 * the new work buffer. This operation is known as "flipping" the buffers.
 *
 * You must call this function once drawing is complete, otherwise draws will
 * not appear on-screen.
 *
 * \param screen
 * The ID of the screen to flip.
 */
void
OSScreenFlipBuffersEx(OSScreenID screen);

/**
 * Draws text at the given position. The text will be drawn to the work
 * buffer with a built-in monospace font, coloured white, and anti-aliased.
 * The position coordinates are in <em>characters</em>, not pixels.
 *
 * \param screen
 * The ID of the screen to draw to. Only the work buffer will be affected.
 *
 * \param row
 * The row, in characters, to place the text in. 0 corresponds to the top of
 * the screen.
 *
 * \param column
 * The column, in characters, to place the text at. 0 corresponds to the left of
 * the screen.
 *
 * \param buffer
 * Pointer to the string of text to draw. Null-terminated.
 *
 * \note
 * Since this function only affects the <em>work buffer</em>, its effect will
 * not appear on screen immediately. See \link OSScreenFlipBuffersEx \endlink.
 *
 * \sa <ul>
 * <li>\link OSScreenPutPixelEx \endlink</li>
 * <li>\link OSScreenClearBufferEx \endlink</li>
 * </ul>
 */
void
OSScreenPutFontEx(OSScreenID screen,
                  uint32_t row,
                  uint32_t column,
                  const char *buffer);

/**
 * Draws a single pixel at the given position. The pixel, a 32-bit RGBX
 * colour, will be placed in the work buffer at the coordinates given.
 *
 * \param screen
 * The ID of the screen to place the pixel in.
 *
 * \param x
 * The x-coordinate, in pixels, to draw the pixel at.
 *
 * \param y
 * The y-coordinate, in pixels, to draw the pixel at.
 *
 * \param colour
 * The desired colour of the pixel to draw, in RGBX32 colour (0xRRGGBBXX, where
 * the XX value is ignored).
 *
 * \note
 * Since this function only affects the <em>work buffer</em>, its effect will
 * not appear on screen immediately. See \link OSScreenFlipBuffersEx \endlink.
 *
 * \sa <ul>
 * <li>\link OSScreenPutFontEx \endlink</li>
 * <li>\link OSScreenClearBufferEx \endlink</li>
 * </ul>
 */
void
OSScreenPutPixelEx(OSScreenID screen,
                   uint32_t x,
                   uint32_t y,
                   uint32_t colour);

/**
 * Enables or disables a given screen. If a screen is disabled, it shows black.
 *
 * \param screen
 * The ID of the screen to enable or disable.
 *
 * \param enable
 * \c true if the screen should be enabled, otherwise false.
 */
void
OSScreenEnableEx(OSScreenID screen,
                 BOOL enable);

#ifdef __cplusplus
}
#endif

/** @} */
