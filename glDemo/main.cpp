
#include "core.h"


// global variables

// Window size
const unsigned int initWidth = 512;
const unsigned int initHeight = 512;

// Function prototypes
void renderScene();
void resizeWindow(GLFWwindow* window, int width, int height);
void DrawPolygon(int _x, int _y, int _sides, float _radius);
void DrawStar(float _atX, float _atY, float _innerRadius, float _outerRadius, int _points);
void DrawTank(float _atX, float _atY, float _orientation);
void keyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods);
void updateScene();


int main() {

	//
	// 1. Initialisation
	//
	

	// Initialise glfw and setup window
	glfwInit();

	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GLFW_TRUE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);

	GLFWwindow* window = glfwCreateWindow(initWidth, initHeight, "Real-Time Computer Graphics", NULL, NULL);

	// Check window was created successfully
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window!\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	

	// Set callback functions to handle different events
	glfwSetFramebufferSizeCallback(window, resizeWindow); // resize window callback
	glfwSetKeyCallback(window, keyboardHandler); // Keyboard input callback


	// Initialise glew
	glewInit();

	
	// Setup window's initial size
	resizeWindow(window, initWidth, initHeight);

	// Initialise scene - geometry and shaders etc
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // setup background colour to be black


	gluOrtho2D(0, 1000, 0, 1000);


	//
	// 2. Main loop
	// 
	

	// Loop while program is not terminated.
	while (!glfwWindowShouldClose(window)) {

		updateScene();
		renderScene();						// Render into the current buffer
		glfwSwapBuffers(window);			// Displays what was just rendered (using double buffering).

		// Poll events (key presses, mouse events)
		// glfwWaitEvents();				// Use this if no animation.
		// glfwWaitEventsTimeout(1.0/60.0);	// Use this to animate at 60 frames/sec (timing is NOT reliable)
		glfwPollEvents();					// Use this version when animating as fast as possible
	}

	glfwTerminate();
	return 0;
}


void DrawTank(float _atX, float _atY, float _orientation)
{

	glPushMatrix();
	glTranslatef(_atX, _atY,0.0f);
	glRotatef(_orientation, 0.0f, 0.0f, 1.0f);



	glBegin(GL_LINE_LOOP);

	glVertex2f(-75.0f, 40.0f);
	glVertex2f(75.0f, 40.0f);
	glVertex2f(75.0f, -40.0f);
	glVertex2f(-75.0f, -40.0f);

	glEnd();


	glBegin(GL_LINE_LOOP);

	glVertex2f(-50.0f, 30.0f);
	glVertex2f(60.0f, 0.0f);
	glVertex2f(-50.0f, -30.0f);

	glEnd();
	glPopMatrix();


}

void DrawStar(float _atX, float _atY, float _innerRadius, float _outerRadius, int _points)
{
	glBegin(GL_POLYGON);
	for (int i = 0; i < _points *2; ++i)
	{
		float angle = i * 3.1415926f / _points;
		float radius = (i % 2 == 0) ? _outerRadius : _innerRadius;
		float x = _atX + cosf(angle) * radius;
		float y = _atY + sinf(angle) * radius;
		glVertex2d(x, y);

	}
	glEnd();


}
void DrawPolygon(int _x, int _y, int _sides, float _radius)
{
	if (_sides < 3)return;

	glBegin(GL_POLYGON);
	for (int i = 0; i < _sides; ++i)
	{
		float angle = 2.0f * 3.1415926f * i / _sides;
		float x = _x + cosf(angle) * _radius;
		float y = _y + sinf(angle) * _radius;
		glVertex2d(x, y);

	}
	glEnd();




}


// renderScene - function to render the current scene
void renderScene()
{
	// Clear the rendering window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//DrawPolygon(500, 500, 100, 200);
	//DrawStar(500.0f, 500.0f, 350.0f, 200.0f, 5);
	//DrawTank(500,500, 90.0f);

	
	

}


// Function to call when window resized
void resizeWindow(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);		// Draw into entire window
}


// Function to call to handle keyboard input
void keyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {

		// check which key was pressed...
		switch (key)
		{
			case GLFW_KEY_ESCAPE:
				glfwSetWindowShouldClose(window, true);
				break;

			default:
			{
			}
		}
	}
	else if (action == GLFW_RELEASE) {
		// handle key release events
	}
}


// Function called to animate elements in the scene
void updateScene() {
}

