/*		This code has been created by Banu Octavian aka Choko - 20 may 2000
 *		and uses NeHe tutorials as a starting point (window initialization,
 *		texture loading, GL initialization and code for keypresses) - very good
 *		tutorials, Jeff. If anyone is interested about the presented algorithm
 *		please e-mail me at boct@romwest.ro
 *		Attention!!! This code is not for beginners.
 */

 /* **************************************************************
 *  Project: $(project)
 *  Function : Main program
 ***************************************************************
 *  $Author: Jeff Molofee 2000
 *  $Name:  $
 ***************************************************************
 *
 *  Copyright NeHe Production
 *
 ***************************************************************/

/**         Comments manageable by Doxygen
*
*  Modified smoothly by Thierry DECHAIZE
*
*  Paradigm : obtain one source (only one !) compatible for multiple free C Compilers
*    and provide for all users an development environment on Windows (64 bits compatible),
*    the great Code::Blocks manager (version 20.03), and don't use glaux.lib or glaux.dll.
*
*	a) Mingw 32 bits, version officielle gcc 9.2.0 (old !) : downloadable on http://sourceforge.net/projects/mingw/ (official)
*	b) Mingw 64 bits included in new IDE Red Panda Dev-Cpp, version gcc 10.3.0 : donwloadable on http://sourceforge.net/projects/dev-cpp-2020/
*	c) Mingw 64 bits included in package Code::Blocks (version 20.03), version gcc 8.1.0 (very old !) : downloadable on http://sourceforge.net/projects/codeblocks/files/Binaries/20.03/Windows/
*	d) Mingw 32 and 64 bits packagés, version gcc 11.2.0 : downloadable on  https://winlibs.com/ (and CLANG included in, 32 and 64 bits), two kits :
*			- winlibs-i686-posix-dwarf-gcc-12.2.0-llvm-14.0.6-mingw-w64ucrt-10.0.0-r2.7z (32 bits)
*			- winlibs-x86_64-posix-seh-gcc-12.2.0-llvm-14.0.6-mingw-w64ucrt-10.0.0-r2.7z (64 bits)
*	e) Cygwin64, 32 et 64 bits, version gcc 11.3.0 : downloadable on http://www.cygwin.com/install.html (tool for install : setup-x86_64.exe)
*	f) TDM GCC, 32 et 64 bits, version 10.3.0 : downloadable on http://sourceforge.net/projects/TDM-GCC
*	g) MSYS2 environnement MINGW32 and MINGW64, 32 et 64 bits, version de 2022 (msys2-x86_64-20220603.exe), version gcc 12.2.0 : downloadable on https://repo.msys2.org/distrib/x86_64/msys2-x86_64-20220603.exe
*	h) Visual Studio 2022, 32 et 64 bits, community edition for free : downloadable on https://visualstudio.microsoft.com/fr/thank-you-downloading-visual-studio/?sku=Community&rel=17
*	i) Borland C/C++ 32 bits, version 5.5 : downloadable on https://developerinsider.co/download-and-install-borland-c-compiler-on-windows-10/
*	j) Digital Mars Compiler C/C++ 32 bits version 8.57 : downloadable on http://www.digitalmars.com (the more old compiler, the more bugged, dead branch !)
*	k) OpenWatcom C/C++ 32 et 64 bits, version 2.0 : downloadable on http://openwatcom.mirror.fr/ (only 32 bits version run correctly !)
*	l) Lcc and Lcc64, 32 et 64 bits: downloadable http://www.cs.virginia.edu/~lcc-win32/
*	m) PELLES C (only C) , 32 et 64 bits, version 11.0 : downloadable on http://www.smorgasbordet.com/pellesc/
*	o) CLANG, adossé aux environnements MINGW64 et MINGW32, version 14.0.6 (version gcc 12.0.0) : downloadable on https://winlibs.com/
*	p) CLANG, adossé aux environnements Visual Studio 2022 (+ kits Microsoft), version 15.0.1 : downloadable on https://releases.llvm.org/download.html
*	q) CLANG de la version MSYS2, adossé aux environnements MINGW64 et MINGW32, version 15.0.0 (version gcc 12.2.0) : downloadable on https://repo.msys2.org/distrib/x86_64/msys2-x86_64-20220118.exe
*	r) CLANG de la version CYGWIN, adossé aux environnements MINGW64 et MINGW32, version 8.0.0 (very old !) (version gcc 11.3.0) : downloadable http://www.cygwin.com/install.html (tool for install or update : setup-x86_64.exe)
*
*   TDE -> Add resource file and resource header for restitute version + icon OpenGL.ico for fun
*			because versionning is important, same for freeware :-) !
*
*  Date : 2022/02/16
*
* \file            Lesson27.c
* \author          Jeff Molofee ( NeHe ) originely, Modified for LCCWin32 compiler by Robert Wishlaw 2002/11/23
* \author          After adapted by Thierry Dechaize to verify paradigm : one source for multiple C Compilers
* \version         2.0.1.0
* \date            16 février 2022
* \brief           Ouvre une fenêtre Windows et dessine une pièce éclairée avec une sphère et un tétrahédre en croix (NEHE GameDev) stocké dans le répertoire ./data.
* \details         Ce programme ne gére plusieurs événements : les touches et la sortie par la touche ESC.
*
*
*/

#if defined __CYGWIN__ || defined __LCC__
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>		    // Header File For Windows
#if defined(__LCC__)
#ifndef WINGDIAPI
#   define WINGDIAPI __stdcall
#endif
#endif

#include <gl\gl.h>										// Header File For The OpenGL32 Library
#include <gl\glu.h>										// Header File For The GLu32 Library
// #include <gl\glaux.h>									// Header File For The Glaux Library
// #include <stdbool.h>										// Header File For The C99 bool definitions
#include <stdlib.h>										// Header File For The Standard Library (function abs(...) for LCC 64 bits)

#if defined __GNUC__ || defined __LCC__ || defined _MSC_VER || defined __TURBOC__ || defined __POCC__
#include <stdbool.h>
#endif

#if defined(__SC__) || defined(__DMC__)
#include <wtypes.h>
// typedef BOOLEAN         bool;
#endif

// A user defined ``bool'' type for compilers that don't yet support one.
//
#if defined(__BORLANDC__) && (__BORLANDC__ < 0x500) || defined(__WATCOMC__)
  #define DONT_HAVE_BOOL_TYPE
#endif

// A ``bool'' type for compilers that don't yet support one.
#if defined(DONT_HAVE_BOOL_TYPE)
  typedef char bool;

  #ifdef true
    #warning Better check include file ``mytypes.h''.
    #undef true
  #endif
  #define true 1

  #ifdef false
    #warning Better check include file ``mytypes.h''.
    #undef false
  #endif
  #define false 0
#endif

typedef float GLvector4f[4];							// Typedef's For VMatMult Procedure
typedef float GLmatrix16f[16];							// Typedef's For VMatMult Procedure

HDC			hDC=NULL;									// Private GDI Device Context
HGLRC		hRC=NULL;									// Permanent Rendering Context
HWND		hWnd=NULL;									// Holds Our Window Handle
HINSTANCE	hInstance=NULL;								// Holds The Instance Of The Application

bool keys[256], keypressed[256];						// Array Used For The Keyboard Routine
bool active=TRUE;										// Window Active Flag Set To TRUE By Default
bool fullscreen=TRUE;									// Fullscreen Flag Set To Fullscreen Mode By Default

GLfloat		xrot=0, xspeed=0;							// X Rotation & X Speed
GLfloat		yrot=0, yspeed=0;							// Y Rotation & Y Speed

float LightPos[] = { 0.0f, 5.0f,-4.0f, 1.0f};			// Light Position
float LightAmb[] = { 0.2f, 0.2f, 0.2f, 1.0f};			// Ambient Light Values
float LightDif[] = { 0.6f, 0.6f, 0.6f, 1.0f};			// Diffuse Light Values
float LightSpc[] = {-0.2f, -0.2f, -0.2f, 1.0f};			// Specular Light Values

float MatAmb[] = {0.4f, 0.4f, 0.4f, 1.0f};				// Material - Ambient Values
float MatDif[] = {0.2f, 0.6f, 0.9f, 1.0f};				// Material - Diffuse Values
float MatSpc[] = {0.0f, 0.0f, 0.0f, 1.0f};				// Material - Specular Values
float MatShn[] = {0.0f};								// Material - Shininess

float ObjPos[] = {-2.0f,-2.0f,-5.0f};					// Object Position

GLUquadricObj	*q;										// Quadratic For Drawing A Sphere
float SpherePos[] = {-4.0f,-5.0f,-6.0f};

#include "3dobject.h"									// Header File For 3D Object Handling
struct glObject obj;									// Object

static	PIXELFORMATDESCRIPTOR pfd=					// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),					// Size Of This Pixel Format Descriptor
		1,												// Version Number
		PFD_DRAW_TO_WINDOW |							// Format Must Support Window
		PFD_SUPPORT_OPENGL |							// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,								// Must Support Double Buffering
		PFD_TYPE_RGBA,									// Request An RGBA Format
		0 /*bits*/,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,								// Color Bits Ignored
		0,												// No Alpha Buffer
		0,												// Shift Bit Ignored
		0,												// No Accumulation Buffer
		0, 0, 0, 0,										// Accumulation Bits Ignored
		16,												// 16Bit Z-Buffer (Depth Buffer)
		1,												// Use Stencil Buffer ( * Important * )
		0,												// No Auxiliary Buffer
		PFD_MAIN_PLANE,									// Main Drawing Layer
		0,												// Reserved
		0, 0, 0											// Layer Masks Ignored
};

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc

/**	            This Code calculate new matrix
*
* \brief      Fonction VMatMult : calcul des coordonnées de la nouvelle matrice des objets
* \details    En entrée la nouvelle matrice et un vecteur
* \param	  M     		la nouvelle matrice	des objets			                *
* \param	  v		        le vecteur de translation		                        *
* \return     void          un void (aucun retour).
*
*/

void VMatMult(GLmatrix16f M, GLvector4f v)
{
	GLfloat res[4];										// Hold Calculated Results
	res[0]=M[ 0]*v[0]+M[ 4]*v[1]+M[ 8]*v[2]+M[12]*v[3];
	res[1]=M[ 1]*v[0]+M[ 5]*v[1]+M[ 9]*v[2]+M[13]*v[3];
	res[2]=M[ 2]*v[0]+M[ 6]*v[1]+M[10]*v[2]+M[14]*v[3];
	res[3]=M[ 3]*v[0]+M[ 7]*v[1]+M[11]*v[2]+M[15]*v[3];
	v[0]=res[0];										// Results Are Stored Back In v[]
	v[1]=res[1];
	v[2]=res[2];
	v[3]=res[3];										// Homogenous Coordinate
}

/**	            This Code Resize the main window.
*
* \brief      Fonction ReSizeGLScene : redimensionnement de la fenêtre Windows gérant OpenGL
* \details    En entrée les deux nouvelles dimensions de la fenêtre
* \param	  width			Width of the GL Window Or Fullscreen Mode				*
* \param	  height		Height of the GL Window Or Fullscreen Mode			    *
* \return     GLvoid        un void OpenGL.
*
*/

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.001f,100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

/**	            This Code draw room of scene
*
* \brief      Fonction InitGLObjects : initialisation de l'objet de la scène.
* \details    Rien
* \param	  void		    un void (aucun paramètre)
* \return     int      	    un entier (testé en bolléen)
*
*/

int InitGLObjects(void)										// Initialize Objects
{
    unsigned int i=0;

	if (!ReadObject("../../Data/Object2.txt", &obj))			// Read Object2 Into obj
	{
		return FALSE;									// If Failed Return False
	}

	SetConnectivity(&obj);								// Set Face To Face Connectivity

	for (i=0;i<obj.nPlanes;i++)			// Loop Through All Object Planes
		CalcPlane(&obj, &(obj.planes[i]));				// Compute Plane Equations For All Faces

	return TRUE;										// Return True
}

/**	            This Code finish the initialization OpenGL of the main window.
*
* \brief      Fonction InitGL : Fin de l'initialisation de la fenêtre Windows gérant OpenGL
* \details    Rien de spécial
* \param	  GLvoid		un void OpenGL.
* \return     int        	un entier (booleen)
*
*/

int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	if (!InitGLObjects()) return FALSE;					// Function For Initializing Our Object(s)
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glClearStencil(0);									// Stencil Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

	glLightfv(GL_LIGHT1, GL_POSITION, LightPos);		// Set Light1 Position
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmb);			// Set Light1 Ambience
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDif);			// Set Light1 Diffuse
	glLightfv(GL_LIGHT1, GL_SPECULAR, LightSpc);		// Set Light1 Specular
	glEnable(GL_LIGHT1);								// Enable Light1
	glEnable(GL_LIGHTING);								// Enable Lighting

	glMaterialfv(GL_FRONT, GL_AMBIENT, MatAmb);			// Set Material Ambience
	glMaterialfv(GL_FRONT, GL_DIFFUSE, MatDif);			// Set Material Diffuse
	glMaterialfv(GL_FRONT, GL_SPECULAR, MatSpc);		// Set Material Specular
	glMaterialfv(GL_FRONT, GL_SHININESS, MatShn);		// Set Material Shininess

	glCullFace(GL_BACK);								// Set Culling Face To Back Face
	glEnable(GL_CULL_FACE);								// Enable Culling
	glClearColor(0.1f, 1.0f, 0.5f, 1.0f);				// Set Clear Color (Greenish Color)

	q = gluNewQuadric();								// Initialize Quadratic
	gluQuadricNormals(q, GL_SMOOTH);					// Enable Smooth Normal Generation
	gluQuadricTexture(q, GL_FALSE);						// Disable Auto Texture Coords

	return TRUE;										// Initialization Went OK
}

/**	            This Code draw room of scene
*
* \brief      Fonction DrawFloor : dessin da la pièce de la scène.
* \details    Rien
* \param	  void		    un void (aucun paramètre)
* \return     void       	un void (aucun retour)
*
*/

void DrawGLRoom(void)									// Draw The Room (Box)
{
	glBegin(GL_QUADS);									// Begin Drawing Quads
		// Floor
		glNormal3f(0.0f, 1.0f, 0.0f);					// Normal Pointing Up
		glVertex3f(-10.0f,-10.0f,-20.0f);				// Back Left
		glVertex3f(-10.0f,-10.0f, 20.0f);				// Front Left
		glVertex3f( 10.0f,-10.0f, 20.0f);				// Front Right
		glVertex3f( 10.0f,-10.0f,-20.0f);				// Back Right
		// Ceiling
		glNormal3f(0.0f,-1.0f, 0.0f);					// Normal Point Down
		glVertex3f(-10.0f, 10.0f, 20.0f);				// Front Left
		glVertex3f(-10.0f, 10.0f,-20.0f);				// Back Left
		glVertex3f( 10.0f, 10.0f,-20.0f);				// Back Right
		glVertex3f( 10.0f, 10.0f, 20.0f);				// Front Right
		// Front Wall
		glNormal3f(0.0f, 0.0f, 1.0f);					// Normal Pointing Away From Viewer
		glVertex3f(-10.0f, 10.0f,-20.0f);				// Top Left
		glVertex3f(-10.0f,-10.0f,-20.0f);				// Bottom Left
		glVertex3f( 10.0f,-10.0f,-20.0f);				// Bottom Right
		glVertex3f( 10.0f, 10.0f,-20.0f);				// Top Right
		// Back Wall
		glNormal3f(0.0f, 0.0f,-1.0f);					// Normal Pointing Towards Viewer
		glVertex3f( 10.0f, 10.0f, 20.0f);				// Top Right
		glVertex3f( 10.0f,-10.0f, 20.0f);				// Bottom Right
		glVertex3f(-10.0f,-10.0f, 20.0f);				// Bottom Left
		glVertex3f(-10.0f, 10.0f, 20.0f);				// Top Left
		// Left Wall
		glNormal3f(1.0f, 0.0f, 0.0f);					// Normal Pointing Right
		glVertex3f(-10.0f, 10.0f, 20.0f);				// Top Front
		glVertex3f(-10.0f,-10.0f, 20.0f);				// Bottom Front
		glVertex3f(-10.0f,-10.0f,-20.0f);				// Bottom Back
		glVertex3f(-10.0f, 10.0f,-20.0f);				// Top Back
		// Right Wall
		glNormal3f(-1.0f, 0.0f, 0.0f);					// Normal Pointing Left
		glVertex3f( 10.0f, 10.0f,-20.0f);				// Top Back
		glVertex3f( 10.0f,-10.0f,-20.0f);				// Bottom Back
		glVertex3f( 10.0f,-10.0f, 20.0f);				// Bottom Front
		glVertex3f( 10.0f, 10.0f, 20.0f);				// Top Front
	glEnd();											// Done Drawing Quads
}

/**	            This Code draw the scene OpenGL in the main window.
*
* \brief      Fonction DrawGLScene : Dessin sous OpenGL dans la fenêtre Windows.
* \details    Rien de spécial
* \param	  GLvoid		un void OpenGL.
* \return     int        	un entier (booleen)
*
*/

int DrawGLScene(GLvoid)									// Main Drawing Routine
{
	GLmatrix16f Minv;
	GLvector4f wlp, lp;

	// Clear Color Buffer, Depth Buffer, Stencil Buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glLoadIdentity();									// Reset Modelview Matrix
	glTranslatef(0.0f, 0.0f, -20.0f);					// Zoom Into Screen 20 Units
	glLightfv(GL_LIGHT1, GL_POSITION, LightPos);		// Position Light1
	glTranslatef(SpherePos[0], SpherePos[1], SpherePos[2]);	// Position The Sphere
	gluSphere(q, 1.5f, 32, 16);							// Draw A Sphere

	// calculate light's position relative to local coordinate system
	// dunno if this is the best way to do it, but it actually works
	// if u find another aproach, let me know ;)

	// we build the inversed matrix by doing all the actions in reverse order
	// and with reverse parameters (notice -xrot, -yrot, -ObjPos[], etc.)
	glLoadIdentity();									// Reset Matrix
	glRotatef(-yrot, 0.0f, 1.0f, 0.0f);					// Rotate By -yrot On Y Axis
	glRotatef(-xrot, 1.0f, 0.0f, 0.0f);					// Rotate By -xrot On X Axis
	glGetFloatv(GL_MODELVIEW_MATRIX,Minv);				// Retrieve ModelView Matrix (Stores In Minv)
	lp[0] = LightPos[0];								// Store Light Position X In lp[0]
	lp[1] = LightPos[1];								// Store Light Position Y In lp[1]
	lp[2] = LightPos[2];								// Store Light Position Z In lp[2]
	lp[3] = LightPos[3];								// Store Light Direction In lp[3]
	VMatMult(Minv, lp);									// We Store Rotated Light Vector In 'lp' Array
	glTranslatef(-ObjPos[0], -ObjPos[1], -ObjPos[2]);	// Move Negative On All Axis Based On ObjPos[] Values (X, Y, Z)
	glGetFloatv(GL_MODELVIEW_MATRIX,Minv);				// Retrieve ModelView Matrix From Minv
	wlp[0] = 0.0f;										// World Local Coord X To 0
	wlp[1] = 0.0f;										// World Local Coord Y To 0
	wlp[2] = 0.0f;										// World Local Coord Z To 0
	wlp[3] = 1.0f;
	VMatMult(Minv, wlp);								// We Store The Position Of The World Origin Relative To The
														// Local Coord. System In 'wlp' Array
	lp[0] += wlp[0];									// Adding These Two Gives Us The
	lp[1] += wlp[1];									// Position Of The Light Relative To
	lp[2] += wlp[2];									// The Local Coordinate System

	glColor4f(0.7f, 0.4f, 0.0f, 1.0f);					// Set Color To An Orange
	glLoadIdentity();									// Reset Modelview Matrix
	glTranslatef(0.0f, 0.0f, -20.0f);					// Zoom Into The Screen 20 Units
	DrawGLRoom();										// Draw The Room
	glTranslatef(ObjPos[0], ObjPos[1], ObjPos[2]);		// Position The Object
	glRotatef(xrot, 1.0f, 0.0f, 0.0f);					// Spin It On The X Axis By xrot
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);					// Spin It On The Y Axis By yrot
	DrawGLObject(&obj);									// Procedure For Drawing The Loaded Object
	CastShadow(&obj, lp);								// Procedure For Casting The Shadow Based On The Silhouette

	glColor4f(0.7f, 0.4f, 0.0f, 1.0f);					// Set Color To Purplish Blue
	glDisable(GL_LIGHTING);								// Disable Lighting
	glDepthMask(GL_FALSE);								// Disable Depth Mask
	glTranslatef(lp[0], lp[1], lp[2]);					// Translate To Light's Position
														// Notice We're Still In Local Coordinate System
	gluSphere(q, 0.2f, 16, 8);							// Draw A Little Yellow Sphere (Represents Light)
	glEnable(GL_LIGHTING);								// Enable Lighting
	glDepthMask(GL_TRUE);								// Enable Depth Mask

	xrot += xspeed;										// Increase xrot By xspeed
	yrot += yspeed;										// Increase yrot By yspeed

	glFlush();											// Flush The OpenGL Pipeline
	return TRUE;										// Everything Went OK
}

/**	            This Code test keyboard press.
*
* \brief      Fonction ProcessKeyboard : Gestion des touches clavier.
* \details    Rien
* \param      void       	un void (aucun paramètre)
* \return     void       	un void (aucun retour)
*
*/

void ProcessKeyboard(void)									// Process Key Presses
{
	// Spin Object
	if (keys[VK_LEFT])	yspeed -= 0.1f;					// 'Arrow Left' Decrease yspeed
	if (keys[VK_RIGHT])	yspeed += 0.1f;					// 'Arrow Right' Increase yspeed
	if (keys[VK_UP])	xspeed -= 0.1f;					// 'Arrow Up' Decrease xspeed
	if (keys[VK_DOWN])	xspeed += 0.1f;					// 'Arrow Down' Increase xspeed

	// Adjust Light's Position
	if (keys['L']) LightPos[0] += 0.05f;				// 'L' Moves Light Right
	if (keys['J']) LightPos[0] -= 0.05f;				// 'J' Moves Light Left

	if (keys['I']) LightPos[1] += 0.05f;				// 'I' Moves Light Up
	if (keys['K']) LightPos[1] -= 0.05f;				// 'K' Moves Light Down

	if (keys['O']) LightPos[2] += 0.05f;				// 'O' Moves Light Toward Viewer
	if (keys['U']) LightPos[2] -= 0.05f;				// 'U' Moves Light Away From Viewer

	// Adjust Object's Position
	if (keys[VK_NUMPAD6]) ObjPos[0] += 0.05f;			// 'Numpad6' Move Object Right
	if (keys[VK_NUMPAD4]) ObjPos[0] -= 0.05f;			// 'Numpad4' Move Object Left

	if (keys[VK_NUMPAD8]) ObjPos[1] += 0.05f;			// 'Numpad8' Move Object Up
	if (keys[VK_NUMPAD5]) ObjPos[1] -= 0.05f;			// 'Numpad5' Move Object Down

	if (keys[VK_NUMPAD9]) ObjPos[2] += 0.05f;			// 'Numpad9' Move Object Toward Viewer
	if (keys[VK_NUMPAD7]) ObjPos[2] -= 0.05f;			// 'Numpad7' Move Object Away From Viewer

	// Adjust Ball's Position
	if (keys['D']) SpherePos[0] += 0.05f;				// 'D' Move Ball Right
	if (keys['A']) SpherePos[0] -= 0.05f;				// 'A' Move Ball Left

	if (keys['W']) SpherePos[1] += 0.05f;				// 'W' Move Ball Up
	if (keys['S']) SpherePos[1] -= 0.05f;				// 'S' Move Ball Down

	if (keys['E']) SpherePos[2] += 0.05f;				// 'E' Move Ball Toward Viewer
	if (keys['Q']) SpherePos[2] -= 0.05f;				// 'Q' Move Ball Away From Viewer
}

/**	            This Code destroy all resources of this program.
*
* \brief      Fonction KillGLWindow : Destruction de toutes les ressources du programme.
* \details    Rien de spécial
* \param	  GLvoid			un void OpenGL.
* \return     GLvoid        	un void OpenGL.
*
*/

GLvoid KillGLWindow(GLvoid)								// Properly Kill The Window
{
	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd,hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;										// Set hWnd To NULL
	}

	if (fullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL,0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}

	if (!UnregisterClass("OpenGL",hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;									// Set hInstance To NULL
	}
}

/**				This Code Creates Our OpenGL Window.
 *  \brief          Creation of our OpenGL Window
 *  \param 			title			- Title To Appear At The Top Of The Window				*
 *	\param 			width			- Width Of The GL Window Or Fullscreen Mode				*
 *	\param 			height			- Height Of The GL Window Or Fullscreen Mode			*
 *	\param          bits			- Number Of Bits To Use For Color (8/16/24/32)			*
 *	\param          fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*
 *  \return         BOOL            - un entier booleen (OK ou non).             			*
 */

BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;							// Holds The Results After Searching For A Match
	WNDCLASS	wc;										// Windows Class Structure
	DWORD		dwExStyle;								// Window Extended Style
	DWORD		dwStyle;								// Window Style

	fullscreen=fullscreenflag;							// Set The Global Fullscreen Flag

	hInstance			= GetModuleHandle(NULL);		// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= (WNDPROC) WndProc;			// WndProc Handles Messages
	wc.cbClsExtra		= 0;							// No Extra Window Data
	wc.cbWndExtra		= 0;							// No Extra Window Data
	wc.hInstance		= hInstance;					// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);	// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);	// Load The Arrow Pointer
	wc.hbrBackground	= NULL;							// No Background Required For GL
	wc.lpszMenuName		= NULL;							// We Don't Want A Menu
	wc.lpszClassName	= "OpenGL";						// Set The Class Name

	if (!RegisterClass(&wc))							// Attempt To Register The Window Class
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									// Return FALSE
	}

	if (fullscreen)										// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;						// Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);	// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth	= width;		// Selected Screen Width
		dmScreenSettings.dmPelsHeight	= height;		// Selected Screen Height
		dmScreenSettings.dmBitsPerPel	= bits;			// Selected Bits Per Pixel
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				fullscreen=FALSE;						// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else										// Otherwise
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return FALSE;							// Return FALSE
			}
		}
	}

	if (fullscreen)										// Are We Still In Fullscreen Mode?
	{
		dwExStyle=WS_EX_APPWINDOW;						// Window Extended Style
		dwStyle=WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;	// Windows Style
		ShowCursor(FALSE);								// Hide Mouse Pointer
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;	// Window Extended Style
		dwStyle=WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;	// Windows Style
	}

	// Create The Window
	if (!(hWnd=CreateWindowEx(	dwExStyle,				// Extended Style For The Window
								"OpenGL",				// Class Name
								title,					// Window Title
								dwStyle,				// Window Style
								0, 0,					// Window Position
								width, height,			// Selected Width And Height
								NULL,					// No Parent Window
								NULL,					// No Menu
								hInstance,				// Instance
								NULL)))					// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();									// Reset The Display
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									// Return FALSE
	}

	pfd.cColorBits = bits;  // Select Our Color Depth

	if (!(hDC=GetDC(hWnd)))								// Did We Get A Device Context?
	{
		KillGLWindow();									// Reset The Display
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									// Return FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))		// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();									// Reset The Display
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									// Return FALSE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))			// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();									// Reset The Display
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									// Return FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))					// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();									// Reset The Display
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									// Return FALSE
	}

	if(!wglMakeCurrent(hDC,hRC))						// Try To Activate The Rendering Context
	{
		KillGLWindow();									// Reset The Display
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									// Return FALSE
	}

	ShowWindow(hWnd,SW_SHOW);							// Show The Window
	SetForegroundWindow(hWnd);							// Slightly Higher Priority
	SetFocus(hWnd);										// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);						// Set Up Our Perspective GL Screen

	if (!InitGL())										// Initialize Our Newly Created GL Window
	{
		KillGLWindow();									// Reset The Display
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;									// Return FALSE
	}

	return TRUE;										// Success
}

/**         Comments manageable by Doxygen
*
* \brief      Fonction CALLBACK de traitement des messages Windows
* \details    Traitement de la boucle infinie des messages Windows
* \param      hWnd         L'header de la fenêtre principale.
* \param      uMsg         Un entier non signé.
* \param      wParam       Les paramétres en entrée.
* \param      lParam       Autres paramétres en entrée.
* \return     LRESULT 	   Un LRESULT donnant le status du traitement du message.
*
*/

LRESULT CALLBACK WndProc(	HWND	hWnd,				// Handle For This Window
							UINT	uMsg,				// Message For This Window
							WPARAM	wParam,				// Additional Message Information
							LPARAM	lParam)				// Additional Message Information
{
	switch (uMsg)										// Check For Windows Messages
	{
		case WM_ACTIVATE:								// Watch For Window Activate Message
		{
			if (!HIWORD(wParam))						// Check Minimization State
			{
				active=TRUE;							// Program Is Active
			}
			else										// Otherwise
			{
				active=FALSE;							// Program Is No Longer Active
			}

			return 0;									// Return To The Message Loop
		}

		case WM_SYSCOMMAND:								// Intercept System Commands
		{
			switch (wParam)								// Check System Calls
			{
				case SC_SCREENSAVE:						// Screensaver Trying To Start?
				case SC_MONITORPOWER:					// Monitor Trying To Enter Powersave?
				return 0;								// Prevent From Happening
			}
			break;										// Exit
		}

		case WM_CLOSE:									// Did We Receive A Close Message?
		{
			PostQuitMessage(0);							// Send A Quit Message
			return 0;									// Jump Back
		}

		case WM_KEYDOWN:								// Is A Key Being Held Down?
		{
			keys[wParam] = TRUE;						// If So, Mark It As TRUE
			return 0;									// Jump Back
		}

		case WM_KEYUP:									// Has A Key Been Released?
		{
			keys[wParam] = FALSE;						// If So, Mark It As FALSE
			return 0;									// Jump Back
		}

		case WM_SIZE:									// Resize The OpenGL Window
		{
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
			return 0;									// Jump Back
		}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

/**	This Code is mandatory to create windows application (function WinMain)					*
 *  \brief          Creation of our application on Windows System (not console application) *
 *  \param 			hInstance		- Header de l'instance Windows				            *
 *	\param 			hPrevInstance	- Header de l'instance précédente de Windows 			*
 *	\param 			lpCmdLine		- Un pointeur sur la ligne de commande 			        *
 *	\param          nCmdShow		- Un indicateur d'état			                        *
 *  \return         int             - un entier booleen (OK ou non).                        *
 *	                                                                                        *
 */

int WINAPI WinMain(	HINSTANCE	hInstance,				// Instance
					HINSTANCE	hPrevInstance,			// Previous Instance
					LPSTR		lpCmdLine,				// Command Line Parameters
					int			nCmdShow)				// Window Show State
{
	MSG		msg;										// Windows Message Structure
	BOOL	done=FALSE;									// Bool Variable To Exit Loop

	// Ask The User Which Screen Mode They Prefer
	if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen=FALSE;								// Windowed Mode
	}

	// Create Our OpenGL Window
	if (!CreateGLWindow("Banu Octavian & NeHe's Shadow Casting Tutorial",800,600,32,fullscreen))
	{
		return 0;										// Quit If Window Was Not Created
	}

	while(!done)										// Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))		// Is There A Message Waiting?
		{
			if (msg.message==WM_QUIT)					// Have We Received A Quit Message?
			{
				done=TRUE;								// If So done=TRUE
			}
			else										// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);					// Translate The Message
				DispatchMessage(&msg);					// Dispatch The Message
			}
		}
		else											// If There Are No Messages
		{
			// Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
			if (active && keys[VK_ESCAPE])				// Active?  Was There A Quit Received?
			{
				done=TRUE;								// ESC or DrawGLScene Signalled A Quit
			}
			else										// Not Time To Quit, Update Screen
			{
				DrawGLScene();							// Draw GL Scene
				SwapBuffers(hDC);						// Swap Buffers (Double Buffering)
				ProcessKeyboard();						// Process Key Presses
			}
		}
	}

	// Shutdown
	KillGLWindow();										// Kill The Window
	return (msg.wParam);								// Exit The Program
}
