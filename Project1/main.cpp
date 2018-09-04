//--------------------------------------------------------------------------//
//                                                                          //
//  Project Assignment 1 - Eren Limon - 0054129                             //
//                                                                          //
//--------------------------------------------------------------------------//

#include "Angel.h"
#include <vector>

typedef vec4  color4;
typedef vec4  point4;

//--------------------------Global Variables--------------------------------

GLuint buffer, buffer2, buffer3;

// cube variables
const int NumVertices = 36; //(6 faces)(2 triangles/face)(3 vertices/triangle)
point4 points[NumVertices];
color4 colors[NumVertices];


// sphere variables
int numOfVerticesForSphere;
int numOfTrianglesForSphere;
int numOfEdgesForSphere;
point4 *pointsForSphere; // to be drawn
color4 *colorsForSphere; // to be used while drawing
point4 *verticesForSphere;
color4 *vertexColorsForSphere;


// car variables
int numOfVerticesForCar;
int numOfTrianglesForCar;
int numOfEdgesForCar;
point4 *pointsForCar; // to be drawn
color4 *colorsForCar; // to be used while drawing
point4 *verticesForCar;
color4 *vertexColorsForCar;


// some enumerated types to increase readability
enum{ black = 0, red = 1, yellow = 2, green = 3, blue = 4, magenta = 5, white = 6, cyan = 7, randomized = 8};
enum{ sphereOption = 0, carOption = 1, cubeOption = 2};
enum{ wireframe = 0, solid = 1};


// default options
int colorOption = randomized;
int shape = carOption;
int drawingMode = solid;

// these two variables are needed for normalization
point4 globalMinVertex(INT_MAX);
point4 globalMaxVertex(INT_MIN);


GLfloat scaleFactor[3] = {1.0, 1.0, 1.0};

// Model-view and projection matrices uniform location
GLuint  ModelView, Projection;

mat4  model_view;

// Vertices of a unit cube centered at origin, sides aligned with axes
point4 vertices[8] = {
    point4( -0.5, -0.5,  0.5, 1.0 ),
    point4( -0.5,  0.5,  0.5, 1.0 ),
    point4(  0.5,  0.5,  0.5, 1.0 ),
    point4(  0.5, -0.5,  0.5, 1.0 ),
    point4( -0.5, -0.5, -0.5, 1.0 ),
    point4( -0.5,  0.5, -0.5, 1.0 ),
    point4(  0.5,  0.5, -0.5, 1.0 ),
    point4(  0.5, -0.5, -0.5, 1.0 )
};

// RGBA olors
color4 vertex_colors[8] = {
    color4( 0.0, 0.0, 0.0, 1.0 ),  // black
    color4( 1.0, 0.0, 0.0, 1.0 ),  // red
    color4( 1.0, 1.0, 0.0, 1.0 ),  // yellow
    color4( 0.0, 1.0, 0.0, 1.0 ),  // green
    color4( 0.0, 0.0, 1.0, 1.0 ),  // blue
    color4( 1.0, 0.0, 1.0, 1.0 ),  // magenta
    color4( 1.0, 1.0, 1.0, 1.0 ),  // white
    color4( 0.0, 1.0, 1.0, 1.0 )   // cyan
};

//----------------------------------------------------------------------------







//--------------------------------Methods-------------------------------------

/*  tridSphere method properly fills the pointsForSphere and colorsForSphere
    arrays which are used to create trianglular surfaces in glDrawArray method.
*/

int Index2 = 0;

void
tridSphere(int a, int b,int c)
{
    //std::cout << "Point indexes: " << a << " " << b << " " << c << std::endl
    colorsForSphere[Index2] = vertexColorsForSphere[a];
    pointsForSphere[Index2] = verticesForSphere[a];
    //std::cout << colorsForSphere[Index2] << std::endl;
    Index2++;
    
    colorsForSphere[Index2] = vertexColorsForSphere[b];
    pointsForSphere[Index2] = verticesForSphere[b];
    //std::cout << colorsForSphere[Index2] << std::endl;
    Index2++;
    
    colorsForSphere[Index2] = vertexColorsForSphere[c];
    pointsForSphere[Index2] = verticesForSphere[c];
    //std::cout << colorsForSphere[Index2] << std::endl;
    Index2++;
}

//----------------------------------------------------------------------------


/*  tridCar method properly fills the pointsForCar and colorsForCar
 arrays which are used to create trianglular surfaces in glDrawArray method.
 */

int Index3 = 0;

void
tridCar(int a, int b,int c)
{
    //std::cout << "Point indexes: " << a << " " << b << " " << c << std::endl
    colorsForCar[Index3] = vertexColorsForCar[a];
    pointsForCar[Index3] = verticesForCar[a];
    //std::cout << colorsForCar[Index3] << std::endl;
    Index3++;
    
    colorsForCar[Index3] = vertexColorsForCar[b];
    pointsForCar[Index3] = verticesForCar[b];
    //std::cout << colorsForCar[Index3] << std::endl;
    Index3++;
    
    colorsForCar[Index3] = vertexColorsForCar[c];
    pointsForCar[Index3] = verticesForCar[c];
    //std::cout << colorsForCar[Index3] << std::endl;
    Index3++;
}

//----------------------------------------------------------------------------


/*  quad method properly fills the points and colors
 arrays which are used to create quadrilateral surfaces in glDrawArray method.
 */

int Index = 0;

void
quad( int a, int b, int c, int d )
{
    colors[Index] = vertex_colors[a]; points[Index] = vertices[a]; Index++;
    colors[Index] = vertex_colors[b]; points[Index] = vertices[b]; Index++;
    colors[Index] = vertex_colors[c]; points[Index] = vertices[c]; Index++;
    colors[Index] = vertex_colors[a]; points[Index] = vertices[a]; Index++;
    colors[Index] = vertex_colors[c]; points[Index] = vertices[c]; Index++;
    colors[Index] = vertex_colors[d]; points[Index] = vertices[d]; Index++;
}

//----------------------------------------------------------------------------


/*  colorbude method generates 12 triangles: 36 vertices and 36 colors
 */

void
colorcube()
{
    quad( 1, 0, 3, 2 );
    quad( 2, 3, 7, 6 );
    quad( 3, 0, 4, 7 );
    quad( 6, 5, 1, 2 );
    quad( 4, 5, 6, 7 );
    quad( 5, 4, 0, 1 );
}

//----------------------------------------------------------------------------


/*  changeColor method changes the color arrays of all objects when the related
    submenu is chosen.
 */

void changeColor(int colorOption){
    
    // changing the color of the car
    for(int i = 0; i < numOfTrianglesForCar*3; i++){
        if(colorOption == red){
            colorsForCar[i] = color4( 1.0, 0.0, 0.0, 1.0 );  // red;
        } else if(colorOption == black){
            colorsForCar[i] = color4( 0.0, 0.0, 0.0, 1.0 );  // black
        } else if(colorOption == yellow){
            colorsForCar[i] = color4( 1.0, 1.0, 0.0, 1.0 );  // yellow
        } else if(colorOption == green){
            colorsForCar[i] = color4( 0.0, 1.0, 0.0, 1.0 );  // green
        } else if(colorOption == blue){
            colorsForCar[i] = color4( 0.0, 0.0, 1.0, 1.0 );  // blue
        } else if(colorOption == magenta){
            colorsForCar[i] = color4( 1.0, 0.0, 1.0, 1.0 );  // magenta
        } else if(colorOption == white){
            colorsForCar[i] = color4( 1.0, 1.0, 1.0, 1.0 );  // white
        } else if(colorOption == cyan){
            colorsForCar[i] = color4( 0.0, 1.0, 1.0, 1.0 );  // cyan
        } else {
            colorsForCar[i] = color4(
                                     static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
                                     static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
                                     static_cast <float> (rand()) / static_cast <float> (RAND_MAX), 1.0 );  // randomized
            
        }
        
    }
    
    
    // changing the color of the sphere
    for(int i = 0; i < numOfTrianglesForSphere*3; i++){
        if(colorOption == red){
            colorsForSphere[i] = color4( 1.0, 0.0, 0.0, 1.0 );  // red;
        } else if(colorOption == black){
            colorsForSphere[i] = color4( 0.0, 0.0, 0.0, 1.0 );  // black
        } else if(colorOption == yellow){
            colorsForSphere[i] = color4( 1.0, 1.0, 0.0, 1.0 );  // yellow
        } else if(colorOption == green){
            colorsForSphere[i] = color4( 0.0, 1.0, 0.0, 1.0 );  // green
        } else if(colorOption == blue){
            colorsForSphere[i] = color4( 0.0, 0.0, 1.0, 1.0 );  // blue
        } else if(colorOption == magenta){
            colorsForSphere[i] = color4( 1.0, 0.0, 1.0, 1.0 );  // magenta
        } else if(colorOption == white){
            colorsForSphere[i] = color4( 1.0, 1.0, 1.0, 1.0 );  // white
        } else if(colorOption == cyan){
            colorsForSphere[i] = color4( 0.0, 1.0, 1.0, 1.0 );  // cyan
        } else {
            colorsForSphere[i] = color4(
                                     static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
                                     static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
                                     static_cast <float> (rand()) / static_cast <float> (RAND_MAX), 1.0 );  // randomized
            
        }
        
    }
    
    // changing the color of the cube
    for(int i = 0; i < NumVertices; i++){
        if(colorOption == red){
            colors[i] = color4( 1.0, 0.0, 0.0, 1.0 );  // red;
        } else if(colorOption == black){
            colors[i] = color4( 0.0, 0.0, 0.0, 1.0 );  // black
        } else if(colorOption == yellow){
            colors[i] = color4( 1.0, 1.0, 0.0, 1.0 );  // yellow
        } else if(colorOption == green){
            colors[i] = color4( 0.0, 1.0, 0.0, 1.0 );  // green
        } else if(colorOption == blue){
            colors[i] = color4( 0.0, 0.0, 1.0, 1.0 );  // blue
        } else if(colorOption == magenta){
            colors[i] = color4( 1.0, 0.0, 1.0, 1.0 );  // magenta
        } else if(colorOption == white){
            colors[i] = color4( 1.0, 1.0, 1.0, 1.0 );  // white
        } else if(colorOption == cyan){
            colors[i] = color4( 0.0, 1.0, 1.0, 1.0 );  // cyan
        } else {
            colors[i] = color4(
                                     static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
                                     static_cast <float> (rand()) / static_cast <float> (RAND_MAX),
                                     static_cast <float> (rand()) / static_cast <float> (RAND_MAX), 1.0 );  // randomized
            
        }
        
    }
    
}


//----------------------------------------------------------------------------


/*  readFromFile method reads from the off file given the file name, properly
    fills the array contents normalization is handled inside of this function.
 */


bool
readFromFile(char* name){
    
    //std::cout << "Name is: " << name;
    std::string fileName(name);
    std::string path = "/Users/erenlimon/Desktop/MyApps/Project1/Project1/" + fileName;
    
    const char* pathAsPointer = path.c_str();
    FILE * file = fopen(pathAsPointer, "r"); // openning to read
    if( file == NULL ){
        std::cout << "File cannot be opened!" << std::endl;
        return false;
    }
    
    int index = 0;
    int lineNumber = 1;
    
    if(strcmp(name,"sphere.off") == 0){
        // if we are reading the sphere file
        while(true){
            
            if(lineNumber == 1){
                // skip the first line
                char firstWord[128];
                int line = fscanf(file, "%s", firstWord);
                if (line == EOF)
                    break;
                if (strcmp(firstWord, "OFF") == 0){
                    //std::cout << "First word is: " << firstWord << "\n";
                }
                
            } else if(lineNumber == 2){
                // numOfVertices, numOfTriangles, numOfEdges
                
                fscanf(file, "%d %d %d\n", &numOfVerticesForSphere, &numOfTrianglesForSphere, &numOfEdgesForSphere );
                
                // initialize arrays according to their given lengths in the files.
                verticesForSphere = new point4[numOfVerticesForSphere];
                vertexColorsForSphere = new color4[numOfVerticesForSphere];
                pointsForSphere = new point4[numOfTrianglesForSphere*3];
                colorsForSphere = new color4[numOfTrianglesForSphere*3];
                
                
            } else if(lineNumber <= numOfVerticesForSphere + 2){
                
                point4 vertex;
                int line = fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
                if (line == EOF)
                    break;
                //std::cout << vertex.x << " "<< vertex.y << " "<< vertex.z << "\n";
                vertex.w = 1.0;
                verticesForSphere[index] = vertex;
                
                // initially randomized colors to see objects properly. random colors helps
                // us to have a shadow-like effects.
                color4 color;
                color.x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                color.y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                color.z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                color.w = 1.0;
                vertexColorsForSphere[index] = color;
                
                index++;
                
            } else if(lineNumber <= numOfVerticesForSphere + numOfTrianglesForSphere + 2){
                
                int dummy;
                int ind1;
                int ind2;
                int ind3;
                int line = fscanf(file, "%d %d %d %d\n", &dummy, &ind1, &ind2, &ind3);
                //std::cout << dummy << " "<< ind1 << " "<< ind2 << " "<< ind3 << "\n";
                if (line == EOF)
                    break;
                tridSphere(ind1, ind2, ind3);
                
            } else {
                char firstWord[128];
                int line = fscanf(file, "%s", firstWord);
                if (line == EOF)
                    break;
            }
            
            lineNumber++;
        }
        
    } else if(strcmp(name,"car.off") == 0){
        // if we are reading the car file
        while(true){
            
            if(lineNumber == 1){
                // skip the first line
                char firstWord[128];
                int line = fscanf(file, "%s", firstWord);
                if (line == EOF)
                    break;
                if (strcmp(firstWord, "OFF") == 0){
                    //std::cout << "First word is: " << firstWord << "\n";
                }
                
            } else if(lineNumber == 2){
                // numOfVertices, numOfTriangles, numOfEdges
                
                fscanf(file, "%d %d %d\n", &numOfVerticesForCar, &numOfTrianglesForCar, &numOfEdgesForCar );
            
                //std::cout << numOfVerticesForCar << " "<< numOfTrianglesForCar << " "<< numOfEdgesForCar << "\n";
                
                // initialize arrays according to their given lengths in the files.
                verticesForCar = new point4[numOfVerticesForCar];
                vertexColorsForCar = new color4[numOfVerticesForCar];
                pointsForCar = new point4[numOfTrianglesForCar*3];
                colorsForCar = new color4[numOfTrianglesForCar*3];
                
            } else if(lineNumber <= numOfVerticesForCar + 2){
                
                point4 vertex;
                int line = fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
                if (line == EOF)
                    break;
                //std::cout << vertex.x << " "<< vertex.y << " "<< vertex.z << "\n";
                vertex.w = 1.0;
                verticesForCar[index] = vertex;
                
                // To normalize, we need to find the max values
                if(vertex.x > globalMaxVertex.x)
                    globalMaxVertex.x = vertex.x;
                if(vertex.x < globalMinVertex.x)
                    globalMinVertex.x = vertex.x;
                
                if(vertex.y > globalMaxVertex.y)
                    globalMaxVertex.y = vertex.y;
                if(vertex.y < globalMinVertex.y)
                    globalMinVertex.y = vertex.y;
                
                if(vertex.z > globalMaxVertex.z)
                    globalMaxVertex.z = vertex.z;
                if(vertex.z < globalMinVertex.z)
                    globalMinVertex.z = vertex.z;
                
                // initially randomized colors to see objects properly. random colors helps
                // us to have a shadow-like effects.
                color4 color;
                color.x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                color.y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                color.z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
                color.w = 1.0;
                
                vertexColorsForCar[index] = color;
                //std::cout << vertexColorsForCar[index] << std::endl;
                index++;
                
            } else if(lineNumber <= numOfVerticesForCar + numOfTrianglesForCar + 2){
                
                if(lineNumber==numOfVerticesForCar + 3){
                    // normalize once
                    
                    for(int i = 0; i < numOfVerticesForCar; i++){
                        /*if(verticesForCar[i].x > 0){
                            verticesForCar[i].x = verticesForCar[i].x / globalMaxVertex.x;
                        } else {
                            verticesForCar[i].x = verticesForCar[i].x / -globalMinVertex.x;
                        }
                        
                        if(verticesForCar[i].y > 0){
                            verticesForCar[i].y = verticesForCar[i].y / globalMaxVertex.y;
                        } else {
                            verticesForCar[i].y = verticesForCar[i].y / -globalMinVertex.y;
                        }
                        
                        if(verticesForCar[i].z > 0){
                            verticesForCar[i].z = verticesForCar[i].z / globalMaxVertex.z;
                        }else {
                            verticesForCar[i].z = verticesForCar[i].z / -globalMinVertex.z;
                        }*/
                        
                        verticesForCar[i].x = verticesForCar[i].x / (globalMaxVertex.x - globalMinVertex.x);
                        verticesForCar[i].y = verticesForCar[i].y / (globalMaxVertex.y - globalMinVertex.y);
                        verticesForCar[i].z = verticesForCar[i].z / (globalMaxVertex.z - globalMinVertex.z);
                        //std::cout << verticesForCar[i].x << " "<< verticesForCar[i].y << " "<< verticesForCar[i].z << "\n";
                    }
                }
                
                int dummy;
                int ind1;
                int ind2;
                int ind3;
                int line = fscanf(file, "%d %d %d %d\n", &dummy, &ind1, &ind2, &ind3);
                //std::cout << dummy << " "<< ind1 << " "<< ind2 << " "<< ind3 << "\n";
                if (line == EOF)
                    break;
                
                tridCar(ind1, ind2, ind3);
                
            } else {
                char firstWord[128];
                int line = fscanf(file, "%s", firstWord);
                if (line == EOF)
                    break;
            }
            
            lineNumber++;
        }
        
    } else {
        // other name options can be added later.
    }
    
    return true;
}

//----------------------------------------------------------------------------


GLuint vaoArray[2];

bool isFirstLoad = true;

// OpenGL initialization
void
init()
{
    GLuint program;
    GLuint vPosition;
    GLuint vColor;
    
    
    if(isFirstLoad){ // to change color, isFirstLoad becomes false after the first run
        
        colorcube();
        
        char* obj1 = "sphere.off";
        char* obj2 = "car.off";
        
        readFromFile(obj1);
        readFromFile(obj2);
        
        program = InitShader( "vshader.glsl", "fshader.glsl" );
        
        
        // Create a vertex array object
        glGenVertexArrays( 3, vaoArray );
        glBindVertexArray( vaoArray[0] );
        
        
        // car methods
        glGenBuffers( 1, &buffer );
        glBindBuffer( GL_ARRAY_BUFFER, buffer );
        glBufferData( GL_ARRAY_BUFFER, sizeof(point4) * numOfTrianglesForCar*3+ sizeof(color4)*numOfTrianglesForCar*3, NULL, GL_STATIC_DRAW );
        glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(point4) * numOfTrianglesForCar*3, pointsForCar );
        glBufferSubData( GL_ARRAY_BUFFER, sizeof(point4) * numOfTrianglesForCar*3, sizeof(color4)*numOfTrianglesForCar*3, colorsForCar );
        vPosition = glGetAttribLocation( program, "vPosition" );
        glEnableVertexAttribArray( vPosition );
        glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
        vColor = glGetAttribLocation( program, "vColor" );
        glEnableVertexAttribArray( vColor );
        glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(point4) * numOfTrianglesForCar*3) );
        
        
        glBindVertexArray( vaoArray[1] );
        
        // sphere methods
        glGenBuffers( 1, &buffer2 );
        glBindBuffer( GL_ARRAY_BUFFER, buffer2 );
        glBufferData( GL_ARRAY_BUFFER, sizeof(point4) * numOfTrianglesForSphere*3+ sizeof(color4)*numOfTrianglesForSphere*3, NULL, GL_STATIC_DRAW );
        glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(point4) * numOfTrianglesForSphere*3, pointsForSphere );
        glBufferSubData( GL_ARRAY_BUFFER, sizeof(point4) * numOfTrianglesForSphere*3, sizeof(color4)*numOfTrianglesForSphere*3, colorsForSphere );
        glEnableVertexAttribArray( vPosition );
        glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
        glEnableVertexAttribArray( vColor );
        glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(point4) * numOfTrianglesForSphere*3) );
        
        
        glBindVertexArray( vaoArray[2] );
        
        // cube methods
        glGenBuffers( 1, &buffer3 );
        glBindBuffer( GL_ARRAY_BUFFER, buffer3 );
        glBufferData( GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors), NULL, GL_STATIC_DRAW );
        glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(points), points );
        glBufferSubData( GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors );
        glEnableVertexAttribArray( vPosition );
        glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
        glEnableVertexAttribArray( vColor );
        glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points)) );
        
        
        
        // Retrieve transformation uniform variable locations
        ModelView = glGetUniformLocation( program, "ModelView" );
        Projection = glGetUniformLocation( program, "Projection" );
        
        // Set current program object
        glUseProgram( program );
        
        
        model_view=identity();
        
        // Enable hiddden surface removal
        glEnable( GL_DEPTH_TEST );
        
        // Set state variable "clear color" to clear buffer with.
        glClearColor( 1.0, 1.0, 1.0, 1.0 );
        isFirstLoad = false;
        
    } else {
        
        // car arrays recreated after changing color
        glBindBuffer( GL_ARRAY_BUFFER, buffer );
        glBufferData( GL_ARRAY_BUFFER, sizeof(point4) * numOfTrianglesForCar*3+ sizeof(color4)*numOfTrianglesForCar*3, NULL, GL_STATIC_DRAW );
        glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(point4) * numOfTrianglesForCar*3, pointsForCar );
        glBufferSubData( GL_ARRAY_BUFFER, sizeof(point4) * numOfTrianglesForCar*3, sizeof(color4)*numOfTrianglesForCar*3, colorsForCar );
        vPosition = glGetAttribLocation( program, "vPosition" );
        glEnableVertexAttribArray( vPosition );
        glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
        vColor = glGetAttribLocation( program, "vColor" );
        glEnableVertexAttribArray( vColor );
        glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(point4) * numOfTrianglesForCar*3) );
        
        //glBindVertexArray( vaoArray[1] );
        
        // sphere arrays recreated after changing color
        glBindBuffer( GL_ARRAY_BUFFER, buffer2 );
        glBufferData( GL_ARRAY_BUFFER, sizeof(point4) * numOfTrianglesForSphere*3+ sizeof(color4)*numOfTrianglesForSphere*3, NULL, GL_STATIC_DRAW );
        glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(point4) * numOfTrianglesForSphere*3, pointsForSphere );
        glBufferSubData( GL_ARRAY_BUFFER, sizeof(point4) * numOfTrianglesForSphere*3, sizeof(color4)*numOfTrianglesForSphere*3, colorsForSphere );
        glEnableVertexAttribArray( vPosition );
        glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
        glEnableVertexAttribArray( vColor );
        glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(point4) * numOfTrianglesForSphere*3) );
        
        
        //glBindVertexArray( vaoArray[2] );
        
        // cube arrays recreated after changing color
        glBindBuffer( GL_ARRAY_BUFFER, buffer3 );
        glBufferData( GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors), NULL, GL_STATIC_DRAW );
        glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(points), points );
        glBufferSubData( GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors );
        glEnableVertexAttribArray( vPosition );
        glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
        glEnableVertexAttribArray( vColor );
        glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points)) );
        
    }
    
}

//----------------------------------------------------------------------------


void reshape( int w, int h )
{
    glViewport( 0, 0, w, h );
    
    // Set projection matrix
    mat4  projection;
    if (w <= h)
        projection = Ortho(-1.0, 1.0, -1.0 * (GLfloat) h / (GLfloat) w,
                           1.0 * (GLfloat) h / (GLfloat) w, -1.0, 1.0);
    else  projection = Ortho(-1.0* (GLfloat) w / (GLfloat) h, 1.0 *
                             (GLfloat) w / (GLfloat) h, -1.0, 1.0, -1.0, 1.0);
    
    /*if (w <= h)
     projection = Perspective( 45.0, (GLfloat) w / (GLfloat) h, 0.5, 6.0 );
     else  projection = Perspective( 45.0, (GLfloat) h / (GLfloat) w, 0.5, 6.0 );*/
    
    
    glUniformMatrix4fv( Projection, 1, GL_TRUE, projection );
    
}
//----------------------------------------------------------------------------

// Array of rotation angles (in degrees) for each coordinate axis
enum { Xaxis = 0, Yaxis = 1, Zaxis = 2, NumAxes = 3 };
int  Axis = Yaxis;
GLfloat  Theta[NumAxes] = { 0.0, 0.0, 0.0 };


void
display( void )
{
    if(shape == carOption){
        glBindVertexArray( vaoArray[0] );
        model_view = ( Scale(scaleFactor[0], scaleFactor[1], scaleFactor[2]) * Translate(vec3(0.0, -0.5, 0.0)));
        
    } else if(shape == sphereOption){
        glBindVertexArray( vaoArray[1] );
        model_view = ( Scale(scaleFactor[0]/2, scaleFactor[1]/2, scaleFactor[2]/2) *
                      RotateX( Theta[Xaxis] ) *
                      RotateY( Theta[Yaxis] ) *
                      RotateZ( Theta[Zaxis] ) );
    } else {
        glBindVertexArray( vaoArray[2] );
        model_view = ( Scale(scaleFactor[0], scaleFactor[1], scaleFactor[2]) );
    }
    
    //  Generate tha model-view matrix
    //const vec3 displacement( 0.0, 0.0, -6.0 );
    //const vec3 displacement( 0.0, 0.0, 0.0 );
    /*model_view = ( Scale(scaleFactor[0], scaleFactor[1], scaleFactor[2]) * Translate( displacement ) *
     RotateX( Theta[Xaxis] ) *
     RotateY( Theta[Yaxis] ) *
     RotateZ( Theta[Zaxis] ) );*/
    
    glUniformMatrix4fv( ModelView, 1, GL_TRUE, model_view );
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    if(shape == carOption && drawingMode == wireframe){
        glDrawArrays( GL_LINES, 0, numOfTrianglesForCar*3 );
    } else if(shape == sphereOption && drawingMode == wireframe) {
        glDrawArrays( GL_LINES, 0, numOfTrianglesForSphere*3 );
    } else if(shape == carOption && drawingMode == solid) {
        glDrawArrays( GL_TRIANGLES, 0, numOfTrianglesForCar*3 );
    } else if(shape == sphereOption && drawingMode == solid){
        glDrawArrays( GL_TRIANGLES, 0, numOfTrianglesForSphere*3 );
    } else if(shape == cubeOption && drawingMode == wireframe){
        glDrawArrays( GL_LINES, 0, NumVertices );
    } else {
        glDrawArrays( GL_TRIANGLES, 0, NumVertices );
    }
    
    
    //glFlush();
    
    
    glutSwapBuffers();
    
}


//----------------------------------------------------------------------------
float acceleration = 0.015; // 0.05 max - 0.005 min

void
idle( void )
{
    
    
    scaleFactor[0] *= (1.00 + acceleration);
    scaleFactor[1] *= (1.00 + acceleration);
    scaleFactor[2] *= (1.00 + acceleration);
    if(scaleFactor[0] >= 1.95 || scaleFactor[1] >= 1.95 || scaleFactor[0] >= 1.95){
        scaleFactor[0] = 1.95; // sometimes scalefactor becomes slightly higher than 1.95, which creates a bug
        scaleFactor[1] = 1.95; // so we need to set it back to 1.95
        scaleFactor[2] = 1.95;
        acceleration = -acceleration;
    } else if (scaleFactor[0] <= 1.0 || scaleFactor[1] <= 1.0 || scaleFactor[0] <= 1.0) {
        scaleFactor[0] = 1.0;
        scaleFactor[1] = 1.0;
        scaleFactor[2] = 1.0;
        acceleration = -acceleration;
    }
    
    
    
     Theta[Axis] += 2.0;
     
     if ( Theta[Axis] > 360.0 ) {
     Theta[Axis] -= 360.0;
     }
    
    
    glutPostRedisplay();
    
}

//----------------------------------------------------------------------------

void
keyboard( unsigned char key,int x, int y )
{
    if(key == 'Q' | key == 'q')
        exit(0);
    else if(key == 'H' | key == 'h'){
        std::cout << "------------------------------" << std::endl;
        std::cout << "------/// Need Help? \\\\\\------" << std::endl;
        std::cout << "------------------------------" << std::endl;
        std::cout << "\nKey\tFunction\n" << std::endl;
        std::cout << "Q\tExit the program" << std::endl;
        std::cout << "I\tInitialize(reset) the pose" << std::endl;
        std::cout << "Up Arrow\tIncrease the animation speed" << std::endl;
        std::cout << "Down Arrow\tDecrease the animation speed" << std::endl;
        std::cout << "H\tHelp" << std::endl;
    } else if (key == 'I' | key == 'i'){
        scaleFactor[0] = 1.0;
        scaleFactor[1] = 1.0;
        scaleFactor[2] = 1.0;
        if(acceleration > 0){
            acceleration = 0.015;
        } else {
            acceleration = -0.015;
        }
    }
}

//----------------------------------------------------------------------------

void
arrowInput( int key,int x, int y )
{
    if (key == GLUT_KEY_UP) {
        if(acceleration < 0.05 && acceleration > 0){
            acceleration += 0.005;
        } else if (acceleration > -0.05 && acceleration < 0){
            acceleration -= 0.005;
        }
        
        //std::cout << "Acc: " << acceleration << std::endl;
        glutPostRedisplay();
    } else if (key == GLUT_KEY_DOWN) {
        
        
        if(acceleration > 0.005 && acceleration > 0){
            acceleration -= 0.005;
        } else if (acceleration < -0.005 && acceleration < 0){
            acceleration += 0.005;
        }
        
        
        //std::cout << "Acc down: " << acceleration << std::endl;
        glutPostRedisplay();
    }
    
    
}


//----------------------------------------------------------------------------

void objectTypeCallback(int id)
{
    switch(id) {
        case 1:
            shape=sphereOption;
            break;
        case 2:
            shape=carOption;
            break;
        case 3:
            shape=cubeOption;
            break;
    }
    glutPostRedisplay();
}
//----------------------------------------------------------------------------

void drawingModeCallback(int id)
{
    switch(id) {
        case 1:
            drawingMode = wireframe;
            break;
        case 2:
            drawingMode = solid;
            break;
    }
    glutPostRedisplay();
}
//----------------------------------------------------------------------------

void colorCallback(int id)
{
    switch(id) {
        case 1:
            colorOption = red;
            break;
        case 2:
            colorOption = black;
            break;
        case 3:
            colorOption = yellow;
            break;
        case 4:
            colorOption = green;
            break;
        case 5:
            colorOption = blue;
            break;
        case 6:
            colorOption = magenta;
            break;
        case 7:
            colorOption = white;
            break;
        case 8:
            colorOption = cyan;
            break;
        case 9:
            colorOption = randomized;
            break;
    }
    changeColor(colorOption);
    init();
    glutPostRedisplay();
}

//----------------------------------------------------------------------------

int
main( int argc, char **argv )
{
    
    
    glutInit( &argc, argv );
    glutInitDisplayMode(  GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
    glutInitWindowSize( 512, 512 );
    glutCreateWindow( "Project - elimon15" );
    
    init();
    
    int objectTypeSubMenu = glutCreateMenu(objectTypeCallback);
    glutAddMenuEntry("Sphere", 1);
    glutAddMenuEntry("Car", 2);
    glutAddMenuEntry("Cube", 3);
    
    int drawingModeSubMenu = glutCreateMenu(drawingModeCallback);
    glutAddMenuEntry("Wireframe", 1);
    glutAddMenuEntry("Solid", 2);
    
    int colorSubMenu = glutCreateMenu(colorCallback);
    glutAddMenuEntry("Red", 1);
    glutAddMenuEntry("Black", 2);
    glutAddMenuEntry("Yellow", 3);
    glutAddMenuEntry("Green", 4);
    glutAddMenuEntry("Blue", 5);
    glutAddMenuEntry("Magenta", 6);
    glutAddMenuEntry("White", 7);
    glutAddMenuEntry("Cyan", 8);
    glutAddMenuEntry("Random", 9);
    
    glutCreateMenu(NULL);
    glutAddSubMenu("Object Type", objectTypeSubMenu);
    glutAddSubMenu("Drawing Mode", drawingModeSubMenu);
    glutAddSubMenu("Color", colorSubMenu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    
    glutDisplayFunc( display ); // set display callback function
    glutReshapeFunc( reshape );
    glutIdleFunc( idle );
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(arrowInput);

    
    glutMainLoop();
    return 0;
    
}

