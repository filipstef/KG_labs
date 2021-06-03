#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <vector>
#include <iostream>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 700;
const unsigned int SCR_HEIGHT = 700;

static const char *vertexShaderSource = "#version 330 core\n"
                                        "layout (location = 0) in vec3 aPos;\n"
                                        "void main()\n"
                                        "{\n"
                                        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                        "}\0";
static const char *fragmentShaderSource = "#version 330 core\n"
                                          "out vec4 FragColor;\n"
                                          "void main()\n"
                                          "{\n"
                                          "   FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);\n"
                                          "}\n\0";
static const char *fragmentShaderSourceYellow = "#version 330 core\n"
                                                "out vec4 FragColor;\n"
                                                "void main()\n"
                                                "{\n"
                                                "   FragColor = vec4(1.0f, 0.9f, 0.0f, 1.0f);\n"
                                                "}\n\0";

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress)))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    //VERTEX SHADER 2
    GLuint vertexShader2 = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader2, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader2);
    // check for shader compile errors
    int success2;
    char infoLog2[512];
    glGetShaderiv(vertexShader2, GL_COMPILE_STATUS, &success2);
    if (!success2)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    //FRAGMENT SHADER 2
    GLuint fragmentShaderY = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderY, 1, &fragmentShaderSourceYellow, nullptr);
    glCompileShader(fragmentShaderY);
    // check for shader compile errors
    glGetShaderiv(fragmentShaderY, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    //link shaders 2
    GLuint shaderProgram2 = glCreateProgram();
    glAttachShader(shaderProgram2, vertexShader2);
    glAttachShader(shaderProgram2, fragmentShaderY);
    glLinkProgram(shaderProgram2);
    // check for linking errors
    glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader2);
    glDeleteShader(fragmentShaderY);
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    //FIRST OBJECT
    std::vector<float> vertices;

    float const PI  = glm::pi<float>();
    const int num_segments = 30 ;

    // Starting angle is not 0, but PI/8
    float angle = 0;
    float increment = PI/90;

    float r1 = 1.0f;
    float r2 = 0.9f;

    float xc,yc,zc;
    xc = yc = zc = 0.0f;

    vertices.push_back(xc);
    vertices.push_back(yc);
    vertices.push_back(zc);



    for (auto i=0; i< num_segments+1; ++i) {

        vertices.push_back(xc + r2 * glm::cos(angle));
        vertices.push_back(yc + r2 * glm::sin(angle));
        vertices.push_back(0.0f);

        angle += increment;
    }
//SECOND OBJECT
    std::vector<float> vertices2;


    const int num_segments2 = 30 ;

    // Starting angle is not 0, but PI/8
    float angle2 = 2.1;
    float increment2 = PI/90;

    float rr1 = 1.0f;
    float rr2 = 0.9f;

    //float xxc,yyc,zzc;
    //xxc=yyc=zzc == 0.0f;

    vertices2.push_back(xc);
    vertices2.push_back(yc);
    vertices2.push_back(zc);



    for (auto i=0; i< num_segments2+1; ++i) {

        vertices2.push_back(xc + rr2 * glm::cos(angle2));
        vertices2.push_back(yc + rr2 * glm::sin(angle2));
        vertices2.push_back(0.0f);

        angle2 += increment2;
    }

    //THIRD OBJECT
    std::vector<float> vertices3;

    const int num_segments3 = 30 ;

    // Starting angle is not 0, but PI/8
    float angle3 = 4.2;
    float increment3 = PI/90;

    float r13 = 1.0f;
    float r23 = 0.9f;

    float xc3,yc3,zc3;
    xc3=yc3=zc3 == 0.0f;

    vertices3.push_back(xc);
    vertices3.push_back(yc);
    vertices3.push_back(zc);



    for (auto i=0; i< num_segments3+1; ++i) {

        vertices3.push_back(xc + r13 * glm::cos(angle3));
        vertices3.push_back(yc + r23* glm::sin(angle3));
        vertices3.push_back(0.0f);

        angle3 += increment3;
    }


    //FOURTH OBJECT
    std::vector<float> vertices4;

    const int num_segments4 = 30 ;

    // Starting angle is not 0, but PI/8
    float angle4 = 0;
    float increment4 = 2 * PI/num_segments4;

    float r14 = 1.0f;
    float r24 = 0.2f;

    float xc4,yc4,zc4;
    xc4=yc4=zc4 == 0.0f;

    vertices4.push_back(xc);
    vertices4.push_back(yc);
    vertices4.push_back(zc);



    for (auto i=0; i< num_segments4+1; ++i) {

        vertices4.push_back(xc + r24 * glm::cos(angle4));
        vertices4.push_back(yc + r24 * glm::sin(angle4));
        vertices4.push_back(0.0f);

        angle4 += increment4;
    }

    //FIFTH OBJECT
    std::vector<float> vertices5;

    const int num_segments5 = 30 ;

    // Starting angle is not 0, but PI/8
    float angle5 = 0;
    float increment5 = 2 * PI/num_segments5;

    float r15 = 1.0f;
    float r25 = 0.30f;

    float xc5,yc5,zc5;
    xc4=yc4=zc4 == 0.0f;

    vertices5.push_back(xc);
    vertices5.push_back(yc);
    vertices5.push_back(zc);



    for (auto i=0; i< num_segments5+1; ++i) {

        vertices5.push_back(xc + r25 * glm::cos(angle5));
        vertices5.push_back(yc + r25 * glm::sin(angle5));
        vertices5.push_back(0.0f);

        angle5 += increment5;
    }


    unsigned int VBO[5], VAO[5];
    glGenVertexArrays(1, &VAO[0]);
    glGenBuffers(1, &VBO[0]);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices), &vertices[0], GL_STATIC_DRAW);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_a), vertices_a, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    //BIND SEOND OBJECT
    glGenVertexArrays(1, &VAO[1]);
    glGenBuffers(1, &VBO[1]);

    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, vertices2.size() * sizeof(vertices2), &vertices2[0], GL_STATIC_DRAW);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_a), vertices_a, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    //BIOND THIRD OBJECT
    glGenVertexArrays(1, &VAO[2]);
    glGenBuffers(1, &VBO[2]);

    glBindVertexArray(VAO[2]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, vertices3.size() * sizeof(vertices3), &vertices3[0], GL_STATIC_DRAW);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_a), vertices_a, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    //BIND FOURTH OBJECT
    glGenVertexArrays(1, &VAO[3]);
    glGenBuffers(1, &VBO[3]);

    glBindVertexArray(VAO[3]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);
    glBufferData(GL_ARRAY_BUFFER, vertices4.size() * sizeof(vertices4), &vertices4[0], GL_STATIC_DRAW);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_a), vertices_a, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    //BIND FIFTH OBJECT
    glGenVertexArrays(1, &VAO[4]);
    glGenBuffers(1, &VBO[4]);

    glBindVertexArray(VAO[4]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[4]);
    glBufferData(GL_ARRAY_BUFFER, vertices5.size() * sizeof(vertices5), &vertices5[0], GL_STATIC_DRAW);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_a), vertices_a, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);


    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(1.0f, 0.9f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO[0]); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLE_FAN, 0, num_segments+2);
        //glBindVertexArray(0);

        glBindVertexArray(VAO[1]); // no need to unbind it every time
        glDrawArrays(GL_TRIANGLE_FAN, 0, num_segments2+2);
        //glBindVertexArray(0);

        glBindVertexArray(VAO[2]); // no need to unbind it every time
        glDrawArrays(GL_TRIANGLE_FAN, 0, num_segments3+2);

        glUseProgram(shaderProgram2);
        glBindVertexArray(VAO[4]); // no need to unbind it every time
        glDrawArrays(GL_TRIANGLE_FAN, 0, num_segments5+2);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO[3]); // no need to unbind it every time
        glDrawArrays(GL_TRIANGLE_FAN, 0, num_segments4+2);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO[0]);
    glDeleteBuffers(1, &VBO[0]);
    glDeleteVertexArrays(1, &VAO[1]);
    glDeleteBuffers(1, &VBO[1]);
    glDeleteVertexArrays(1, &VAO[2]);
    glDeleteBuffers(1, &VBO[2]);
    glDeleteVertexArrays(1, &VAO[3]);
    glDeleteBuffers(1, &VBO[3]);
    glDeleteVertexArrays(1, &VAO[4]);
    glDeleteBuffers(1, &VBO[4]);
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


