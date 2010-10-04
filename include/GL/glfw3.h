/************************************************************************
 * GLFW - An OpenGL framework
 * API version: 3.0
 * WWW:         http://www.glfw.org/
 *------------------------------------------------------------------------
 * Copyright (c) 2002-2006 Marcus Geelnard
 * Copyright (c) 2006-2010 Camilla Berglund
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would
 *    be appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not
 *    be misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source
 *    distribution.
 *
 *************************************************************************/

#ifndef __glfw_h_
#define __glfw_h_

#ifdef __cplusplus
extern "C" {
#endif


/*************************************************************************
 * Global definitions
 *************************************************************************/

/* We need a NULL pointer from time to time */
#ifndef NULL
 #ifdef __cplusplus
  #define NULL 0
 #else
  #define NULL ((void*) 0)
 #endif
#endif /* NULL */


/* ------------------- BEGIN SYSTEM/COMPILER SPECIFIC -------------------- */

/* Please report any probles that you find with your compiler, which may
 * be solved in this section! There are several compilers that I have not
 * been able to test this file with yet.
 *
 * First: If we are we on Windows, we want a single define for it (_WIN32)
 * (Note: For Cygwin the compiler flag -mwin32 should be used, but to
 * make sure that things run smoothly for Cygwin users, we add __CYGWIN__
 * to the list of "valid Win32 identifiers", which removes the need for
 * -mwin32)
 */
#if !defined(_WIN32) && (defined(__WIN32__) || defined(WIN32) || defined(__CYGWIN__))
 #define _WIN32
#endif /* _WIN32 */

/* In order for extension support to be portable, we need to define an
 * OpenGL function call method. We use the keyword APIENTRY, which is
 * defined for Win32. (Note: Windows also needs this for <GL/gl.h>)
 */
#ifndef APIENTRY
 #ifdef _WIN32
  #define APIENTRY __stdcall
 #else
  #define APIENTRY
 #endif
 #define GL_APIENTRY_DEFINED
#endif /* APIENTRY */


/* The following three defines are here solely to make some Windows-based
 * <GL/gl.h> files happy. Theoretically we could include <windows.h>, but
 * it has the major drawback of severely polluting our namespace.
 */

/* Under Windows, we need WINGDIAPI defined */
#if !defined(WINGDIAPI) && defined(_WIN32)
 #if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__POCC__)
  /* Microsoft Visual C++, Borland C++ Builder and Pelles C */
  #define WINGDIAPI __declspec(dllimport)
 #elif defined(__LCC__)
  /* LCC-Win32 */
  #define WINGDIAPI __stdcall
 #else
  /* Others (e.g. MinGW, Cygwin) */
  #define WINGDIAPI extern
 #endif
 #define GL_WINGDIAPI_DEFINED
#endif /* WINGDIAPI */

/* Some <GL/glu.h> files also need CALLBACK defined */
#if !defined(CALLBACK) && defined(_WIN32)
 #if defined(_MSC_VER)
  /* Microsoft Visual C++ */
  #if (defined(_M_MRX000) || defined(_M_IX86) || defined(_M_ALPHA) || defined(_M_PPC)) && !defined(MIDL_PASS)
   #define CALLBACK __stdcall
  #else
   #define CALLBACK
  #endif
 #else
  /* Other Windows compilers */
  #define CALLBACK __stdcall
 #endif
 #define GLU_CALLBACK_DEFINED
#endif /* CALLBACK */

/* Microsoft Visual C++, Borland C++ and Pelles C <GL*glu.h> needs wchar_t */
#if defined(_WIN32) && (defined(_MSC_VER) || defined(__BORLANDC__) || defined(__POCC__)) && !defined(_WCHAR_T_DEFINED)
 typedef unsigned short wchar_t;
 #define _WCHAR_T_DEFINED
#endif /* _WCHAR_T_DEFINED */


/* ---------------- GLFW related system specific defines ----------------- */

#if defined(_WIN32) && defined(GLFW_BUILD_DLL)

 /* We are building a Win32 DLL */
 #define GLFWAPI      __declspec(dllexport)

#elif defined(_WIN32) && defined(GLFW_DLL)

 /* We are calling a Win32 DLL */
 #if defined(__LCC__)
  #define GLFWAPI      extern
 #else
  #define GLFWAPI      __declspec(dllimport)
 #endif

#else

 /* We are either building/calling a static lib or we are non-win32 */
 #define GLFWAPI

#endif

/* -------------------- END SYSTEM/COMPILER SPECIFIC --------------------- */

/* Include standard OpenGL headers: GLFW uses GL_FALSE/GL_TRUE, and it is
 * convenient for the user to only have to include <GL/glfw.h>. This also
 * solves the problem with Windows <GL/gl.h> and <GL/glu.h> needing some
 * special defines which normally requires the user to include <windows.h>
 * (which is not a nice solution for portable programs).
 */
#if defined(__APPLE_CC__)
 #include <OpenGL/gl.h>
 #ifndef GLFW_NO_GLU
  #include <OpenGL/glu.h>
 #endif
#else
 #include <GL/gl.h>
 #ifndef GLFW_NO_GLU
  #include <GL/glu.h>
 #endif
#endif


/*************************************************************************
 * GLFW version
 *************************************************************************/

#define GLFW_VERSION_MAJOR    3
#define GLFW_VERSION_MINOR    0
#define GLFW_VERSION_REVISION 0


/*************************************************************************
 * Input handling definitions
 *************************************************************************/

/* Key and button state/action definitions */
#define GLFW_RELEASE            0
#define GLFW_PRESS              1

/* Keyboard key definitions: 8-bit ISO-8859-1 (Latin 1) encoding is used
 * for printable keys (such as A-Z, 0-9 etc), and values above 256
 * represent special (non-printable) keys (e.g. F1, Page Up etc).
 */
#define GLFW_KEY_UNKNOWN      -1
#define GLFW_KEY_SPACE        32
#define GLFW_KEY_SPECIAL      256
#define GLFW_KEY_ESC          (GLFW_KEY_SPECIAL+1)
#define GLFW_KEY_F1           (GLFW_KEY_SPECIAL+2)
#define GLFW_KEY_F2           (GLFW_KEY_SPECIAL+3)
#define GLFW_KEY_F3           (GLFW_KEY_SPECIAL+4)
#define GLFW_KEY_F4           (GLFW_KEY_SPECIAL+5)
#define GLFW_KEY_F5           (GLFW_KEY_SPECIAL+6)
#define GLFW_KEY_F6           (GLFW_KEY_SPECIAL+7)
#define GLFW_KEY_F7           (GLFW_KEY_SPECIAL+8)
#define GLFW_KEY_F8           (GLFW_KEY_SPECIAL+9)
#define GLFW_KEY_F9           (GLFW_KEY_SPECIAL+10)
#define GLFW_KEY_F10          (GLFW_KEY_SPECIAL+11)
#define GLFW_KEY_F11          (GLFW_KEY_SPECIAL+12)
#define GLFW_KEY_F12          (GLFW_KEY_SPECIAL+13)
#define GLFW_KEY_F13          (GLFW_KEY_SPECIAL+14)
#define GLFW_KEY_F14          (GLFW_KEY_SPECIAL+15)
#define GLFW_KEY_F15          (GLFW_KEY_SPECIAL+16)
#define GLFW_KEY_F16          (GLFW_KEY_SPECIAL+17)
#define GLFW_KEY_F17          (GLFW_KEY_SPECIAL+18)
#define GLFW_KEY_F18          (GLFW_KEY_SPECIAL+19)
#define GLFW_KEY_F19          (GLFW_KEY_SPECIAL+20)
#define GLFW_KEY_F20          (GLFW_KEY_SPECIAL+21)
#define GLFW_KEY_F21          (GLFW_KEY_SPECIAL+22)
#define GLFW_KEY_F22          (GLFW_KEY_SPECIAL+23)
#define GLFW_KEY_F23          (GLFW_KEY_SPECIAL+24)
#define GLFW_KEY_F24          (GLFW_KEY_SPECIAL+25)
#define GLFW_KEY_F25          (GLFW_KEY_SPECIAL+26)
#define GLFW_KEY_UP           (GLFW_KEY_SPECIAL+27)
#define GLFW_KEY_DOWN         (GLFW_KEY_SPECIAL+28)
#define GLFW_KEY_LEFT         (GLFW_KEY_SPECIAL+29)
#define GLFW_KEY_RIGHT        (GLFW_KEY_SPECIAL+30)
#define GLFW_KEY_LSHIFT       (GLFW_KEY_SPECIAL+31)
#define GLFW_KEY_RSHIFT       (GLFW_KEY_SPECIAL+32)
#define GLFW_KEY_LCTRL        (GLFW_KEY_SPECIAL+33)
#define GLFW_KEY_RCTRL        (GLFW_KEY_SPECIAL+34)
#define GLFW_KEY_LALT         (GLFW_KEY_SPECIAL+35)
#define GLFW_KEY_RALT         (GLFW_KEY_SPECIAL+36)
#define GLFW_KEY_TAB          (GLFW_KEY_SPECIAL+37)
#define GLFW_KEY_ENTER        (GLFW_KEY_SPECIAL+38)
#define GLFW_KEY_BACKSPACE    (GLFW_KEY_SPECIAL+39)
#define GLFW_KEY_INSERT       (GLFW_KEY_SPECIAL+40)
#define GLFW_KEY_DEL          (GLFW_KEY_SPECIAL+41)
#define GLFW_KEY_PAGEUP       (GLFW_KEY_SPECIAL+42)
#define GLFW_KEY_PAGEDOWN     (GLFW_KEY_SPECIAL+43)
#define GLFW_KEY_HOME         (GLFW_KEY_SPECIAL+44)
#define GLFW_KEY_END          (GLFW_KEY_SPECIAL+45)
#define GLFW_KEY_KP_0         (GLFW_KEY_SPECIAL+46)
#define GLFW_KEY_KP_1         (GLFW_KEY_SPECIAL+47)
#define GLFW_KEY_KP_2         (GLFW_KEY_SPECIAL+48)
#define GLFW_KEY_KP_3         (GLFW_KEY_SPECIAL+49)
#define GLFW_KEY_KP_4         (GLFW_KEY_SPECIAL+50)
#define GLFW_KEY_KP_5         (GLFW_KEY_SPECIAL+51)
#define GLFW_KEY_KP_6         (GLFW_KEY_SPECIAL+52)
#define GLFW_KEY_KP_7         (GLFW_KEY_SPECIAL+53)
#define GLFW_KEY_KP_8         (GLFW_KEY_SPECIAL+54)
#define GLFW_KEY_KP_9         (GLFW_KEY_SPECIAL+55)
#define GLFW_KEY_KP_DIVIDE    (GLFW_KEY_SPECIAL+56)
#define GLFW_KEY_KP_MULTIPLY  (GLFW_KEY_SPECIAL+57)
#define GLFW_KEY_KP_SUBTRACT  (GLFW_KEY_SPECIAL+58)
#define GLFW_KEY_KP_ADD       (GLFW_KEY_SPECIAL+59)
#define GLFW_KEY_KP_DECIMAL   (GLFW_KEY_SPECIAL+60)
#define GLFW_KEY_KP_EQUAL     (GLFW_KEY_SPECIAL+61)
#define GLFW_KEY_KP_ENTER     (GLFW_KEY_SPECIAL+62)
#define GLFW_KEY_KP_NUM_LOCK  (GLFW_KEY_SPECIAL+63)
#define GLFW_KEY_CAPS_LOCK    (GLFW_KEY_SPECIAL+64)
#define GLFW_KEY_SCROLL_LOCK  (GLFW_KEY_SPECIAL+65)
#define GLFW_KEY_PAUSE        (GLFW_KEY_SPECIAL+66)
#define GLFW_KEY_LSUPER       (GLFW_KEY_SPECIAL+67)
#define GLFW_KEY_RSUPER       (GLFW_KEY_SPECIAL+68)
#define GLFW_KEY_MENU         (GLFW_KEY_SPECIAL+69)
#define GLFW_KEY_LAST         GLFW_KEY_MENU

/* Mouse button definitions */
#define GLFW_MOUSE_BUTTON_1      0
#define GLFW_MOUSE_BUTTON_2      1
#define GLFW_MOUSE_BUTTON_3      2
#define GLFW_MOUSE_BUTTON_4      3
#define GLFW_MOUSE_BUTTON_5      4
#define GLFW_MOUSE_BUTTON_6      5
#define GLFW_MOUSE_BUTTON_7      6
#define GLFW_MOUSE_BUTTON_8      7
#define GLFW_MOUSE_BUTTON_LAST   GLFW_MOUSE_BUTTON_8

/* Mouse button aliases */
#define GLFW_MOUSE_BUTTON_LEFT   GLFW_MOUSE_BUTTON_1
#define GLFW_MOUSE_BUTTON_RIGHT  GLFW_MOUSE_BUTTON_2
#define GLFW_MOUSE_BUTTON_MIDDLE GLFW_MOUSE_BUTTON_3

/* Joystick identifiers */
#define GLFW_JOYSTICK_1          0
#define GLFW_JOYSTICK_2          1
#define GLFW_JOYSTICK_3          2
#define GLFW_JOYSTICK_4          3
#define GLFW_JOYSTICK_5          4
#define GLFW_JOYSTICK_6          5
#define GLFW_JOYSTICK_7          6
#define GLFW_JOYSTICK_8          7
#define GLFW_JOYSTICK_9          8
#define GLFW_JOYSTICK_10         9
#define GLFW_JOYSTICK_11         10
#define GLFW_JOYSTICK_12         11
#define GLFW_JOYSTICK_13         12
#define GLFW_JOYSTICK_14         13
#define GLFW_JOYSTICK_15         14
#define GLFW_JOYSTICK_16         15
#define GLFW_JOYSTICK_LAST       GLFW_JOYSTICK_16


/*************************************************************************
 * Other definitions
 *************************************************************************/

/* glfwOpenWindow modes */
#define GLFW_WINDOWED             0x00010001
#define GLFW_FULLSCREEN           0x00010002

/* glfwGetWindowParam tokens */
#define GLFW_ACTIVE               0x00020002
#define GLFW_ICONIFIED            0x00020003
#define GLFW_ACCELERATED          0x00020004

/* The following constants are used for both glfwGetWindowParam
 * and glfwOpenWindowHint
 */
#define GLFW_RED_BITS             0x00020005
#define GLFW_GREEN_BITS           0x00020006
#define GLFW_BLUE_BITS            0x00020007
#define GLFW_ALPHA_BITS           0x00020008
#define GLFW_DEPTH_BITS           0x00020009
#define GLFW_STENCIL_BITS         0x0002000A
#define GLFW_REFRESH_RATE         0x0002000B
#define GLFW_ACCUM_RED_BITS       0x0002000C
#define GLFW_ACCUM_GREEN_BITS     0x0002000D
#define GLFW_ACCUM_BLUE_BITS      0x0002000E
#define GLFW_ACCUM_ALPHA_BITS     0x0002000F
#define GLFW_AUX_BUFFERS          0x00020010
#define GLFW_STEREO               0x00020011
#define GLFW_WINDOW_NO_RESIZE     0x00020012
#define GLFW_FSAA_SAMPLES         0x00020013
#define GLFW_OPENGL_VERSION_MAJOR 0x00020014
#define GLFW_OPENGL_VERSION_MINOR 0x00020015
#define GLFW_OPENGL_FORWARD_COMPAT 0x00020016
#define GLFW_OPENGL_DEBUG_CONTEXT 0x00020017
#define GLFW_OPENGL_PROFILE       0x00020018

/* GLFW_OPENGL_PROFILE tokens */
#define GLFW_OPENGL_CORE_PROFILE  0x00050001
#define GLFW_OPENGL_COMPAT_PROFILE 0x00050002

/* glfwEnable/glfwDisable tokens */
#define GLFW_MOUSE_CURSOR         0x00030001
#define GLFW_STICKY_KEYS          0x00030002
#define GLFW_STICKY_MOUSE_BUTTONS 0x00030003
#define GLFW_SYSTEM_KEYS          0x00030004
#define GLFW_KEY_REPEAT           0x00030005

/* glfwGetJoystickParam tokens */
#define GLFW_PRESENT              0x00050001
#define GLFW_AXES                 0x00050002
#define GLFW_BUTTONS              0x00050003

/* glfwGetError/glfwErrorString tokens */
#define GLFW_NO_ERROR             0
#define GLFW_NOT_INITIALIZED      0x00070001
#define GLFW_INVALID_ENUM         0x00070002
#define GLFW_INVALID_VALUE        0x00070003
#define GLFW_OUT_OF_MEMORY        0x00070004
#define GLFW_OPENGL_NOT_SUPPORTED 0x00070005
#define GLFW_NO_PIXEL_FORMAT      0x00070006
#define GLFW_VIDEO_MODE_FAILED    0x00070007
#define GLFW_UNAVAILABLE_VERSION  0x00070008
#define GLFW_NO_CURRENT_WINDOW    0x00070009
#define GLFW_INTERNAL_ERROR       0x0007000A


/*************************************************************************
 * Typedefs
 *************************************************************************/

/* Window handle type */
typedef struct _GLFWwindow* GLFWwindow;

/* The video mode structure used by glfwGetVideoModes */
typedef struct
{
    int width;
    int height;
    int redBits;
    int blueBits;
    int greenBits;
} GLFWvidmode;

/* Function pointer types */
typedef void (* GLFWwindowsizefun)(GLFWwindow,int,int);
typedef int  (* GLFWwindowclosefun)(GLFWwindow);
typedef void (* GLFWwindowrefreshfun)(GLFWwindow);
typedef void (* GLFWwindowfocusfun)(GLFWwindow,int);
typedef void (* GLFWwindowiconifyfun)(GLFWwindow,int);
typedef void (* GLFWmousebuttonfun)(GLFWwindow,int,int);
typedef void (* GLFWmouseposfun)(GLFWwindow,int,int);
typedef void (* GLFWscrollfun)(GLFWwindow,int,int);
typedef void (* GLFWkeyfun)(GLFWwindow,int,int);
typedef void (* GLFWcharfun)(GLFWwindow,int);


/*************************************************************************
 * Prototypes
 *************************************************************************/

/* Initialization, termination and version querying */
GLFWAPI int  glfwInit(void);
GLFWAPI void glfwTerminate(void);
GLFWAPI void glfwGetVersion(int* major, int* minor, int* rev);
GLFWAPI const char* glfwGetVersionString(void);

/* Error handling */
GLFWAPI int glfwGetError(void);
GLFWAPI const char* glfwErrorString(int error);

/* Video mode functions */
GLFWAPI int  glfwGetVideoModes(GLFWvidmode* list, int maxcount);
GLFWAPI void glfwGetDesktopMode(GLFWvidmode* mode);

/* Window handling */
GLFWAPI GLFWwindow glfwOpenWindow(int width, int height, int mode, const char* title, GLFWwindow share);
GLFWAPI void glfwOpenWindowHint(int target, int hint);
GLFWAPI void glfwMakeWindowCurrent(GLFWwindow window);
GLFWAPI int  glfwIsWindow(GLFWwindow window);
GLFWAPI GLFWwindow glfwGetCurrentWindow(void);
GLFWAPI void glfwCloseWindow(GLFWwindow window);
GLFWAPI void glfwSetWindowTitle(GLFWwindow, const char* title);
GLFWAPI void glfwGetWindowSize(GLFWwindow, int* width, int* height);
GLFWAPI void glfwSetWindowSize(GLFWwindow, int width, int height);
GLFWAPI void glfwGetWindowPos(GLFWwindow, int* x, int* y);
GLFWAPI void glfwSetWindowPos(GLFWwindow, int x, int y);
GLFWAPI void glfwIconifyWindow(GLFWwindow window);
GLFWAPI void glfwRestoreWindow(GLFWwindow window);
GLFWAPI int  glfwGetWindowParam(GLFWwindow window, int param);
GLFWAPI void glfwSetWindowUserPointer(GLFWwindow window, void* pointer);
GLFWAPI void* glfwGetWindowUserPointer(GLFWwindow window);
GLFWAPI void glfwSetWindowSizeCallback(GLFWwindow window, GLFWwindowsizefun cbfun);
GLFWAPI void glfwSetWindowCloseCallback(GLFWwindow window, GLFWwindowclosefun cbfun);
GLFWAPI void glfwSetWindowRefreshCallback(GLFWwindow window, GLFWwindowrefreshfun cbfun);
GLFWAPI void glfwSetWindowFocusCallback(GLFWwindow window, GLFWwindowfocusfun cbfun);
GLFWAPI void glfwSetWindowIconifyCallback(GLFWwindow window, GLFWwindowiconifyfun cbfun);

/* Event handling */
GLFWAPI void glfwPollEvents(void);
GLFWAPI void glfwWaitEvents(void);

/* Input handling */
GLFWAPI int  glfwGetKey(GLFWwindow window, int key);
GLFWAPI int  glfwGetMouseButton(GLFWwindow window, int button);
GLFWAPI void glfwGetMousePos(GLFWwindow window, int* xpos, int* ypos);
GLFWAPI void glfwSetMousePos(GLFWwindow window, int xpos, int ypos);
GLFWAPI void glfwGetScrollOffset(GLFWwindow window, int* x, int* y);
GLFWAPI void glfwSetKeyCallback(GLFWwindow window, GLFWkeyfun cbfun);
GLFWAPI void glfwSetCharCallback(GLFWwindow window, GLFWcharfun cbfun);
GLFWAPI void glfwSetMouseButtonCallback(GLFWwindow window, GLFWmousebuttonfun cbfun);
GLFWAPI void glfwSetMousePosCallback(GLFWwindow window, GLFWmouseposfun cbfun);
GLFWAPI void glfwSetScrollCallback(GLFWwindow window, GLFWscrollfun cbfun);

/* Joystick input */
GLFWAPI int glfwGetJoystickParam(int joy, int param);
GLFWAPI int glfwGetJoystickPos(int joy, float* pos, int numaxes);
GLFWAPI int glfwGetJoystickButtons(int joy, unsigned char* buttons, int numbuttons);

/* Time */
GLFWAPI double glfwGetTime(void);
GLFWAPI void   glfwSetTime(double time);

/* OpenGL support */
GLFWAPI void  glfwSwapBuffers(void);
GLFWAPI void  glfwSwapInterval(int interval);
GLFWAPI int   glfwExtensionSupported(const char* extension);
GLFWAPI void* glfwGetProcAddress(const char* procname);
GLFWAPI void  glfwGetGLVersion(int* major, int* minor, int* rev);

/* Enable/disable functions */
GLFWAPI void glfwEnable(GLFWwindow window, int token);
GLFWAPI void glfwDisable(GLFWwindow window, int token);


#ifdef __cplusplus
}
#endif

#endif /* __glfw_h_ */

