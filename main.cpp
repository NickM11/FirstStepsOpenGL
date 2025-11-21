#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

//Vertex Shader Source code
const char* vertexShaderSource = "#version 330 core \n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
" gl_Position = vec4(aPos.x, aPos.y,aPos.z, 1.0);\n"
"}\0";

//Fragment Shader Source code
const char* fragmentShaderSource = "#version 330 core \n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
" FragColor = vec4(0.8,0.3,0.02,1.0);\n"
"}\n\0";

int main() {

	//Intialize GLFW
	glfwInit();
	
	//Tell GLFW what version of OpenGL we using
	//We using 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	
	//Tell GLFW we use CORE profile
	//Which means only modern function is available
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	//Vertices coordinates
	GLfloat vertices[] =
	{
		-0.5f,-0.5f * float(sqrt(3)) / 3, 0.0f,//Lower left corner
		0.5f,-0.5f * float(sqrt(3)) / 3, 0.0f,//Lower right corner
		0.0f,0.5f * float(sqrt(3)) *2 / 3, 0.0f//Upper corner

	};

	//Create a GLFWwindow object with entered dimensions
	GLFWwindow* window = glfwCreateWindow(800, 800, "WindowA", NULL, NULL);

	//Checking if we successfully created a window
	if (window == NULL) {
		std::cout << "Failed to create GLFW Window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//Introduce window into current context
	glfwMakeContextCurrent(window);
	
	//Load GLAD so it configures OpenGL
	gladLoadGL();

	//Specify the viewport of OpenGl in the Window
	//In this case it goes from x=0 and y= 0 to x=800 and y=800
	glViewport(0, 0, 800, 800);

	//Create Vertex Shader Object and get reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//Attach Vertex Shader source to Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//Compile the Vertex Shader into machine code
	glCompileShader(vertexShader);

	//Create Fragment Shader Object and get refernce
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//Attach Fragment Shader source to Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//Compile the Fragment Shader into machine code
	glCompileShader(fragmentShader);

	//Creatin Shader program and getting its reference
	GLuint shaderProgram = glCreateProgram();
	//Attaching Vertex and Fragment Shaders to program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	//Wrap/Link all the shaders together into Shader program 
	glLinkProgram(shaderProgram);

	//Deleting now useless Vertex and Fragment Shader objects 
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);




	//Creating reference containers for Vertex Array and Vertex Buffers objects
	GLuint VAO,VBO;
	
	//Generate the VAO and VBO with 1 object each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//Making the VAO the current Vertex Array Object by binding it
	glBindVertexArray(VAO);

	//Binding the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Introducing the Vertices into VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//Configure the Vertex Attribute so that OpenGL know how to read VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//Enable the Vertex Attribute so that OpenGL knows to use it
	glEnableVertexAttribArray(0);

	//Bind both VBO and VAO to zero so we don't accidently modify the VAO and change it
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	//Specify the background color
	glClearColor(0.07f,0.13f,0.17f,1.0f);
	//Clean the back buffer and assigning new color to it
	glClear(GL_COLOR_BUFFER_BIT);
	//Swap the back buffer with front buffer
	glfwSwapBuffers(window);

	//Main while loop
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL What SHADER Program to use
		glUseProgram(shaderProgram);
		// Bind VAO so OpenGL knows to use it
		glBindVertexArray(VAO);
		// Draw the Triangle using OpenGl Primitive
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);

		//Take care of all GLFW events
		glfwPollEvents();
	}

	//Delete all objects we created
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	//Delete window before ending the program
	glfwDestroyWindow(window);
	//Terminating GLFW before ending the program
	glfwTerminate();
	return 0;
}