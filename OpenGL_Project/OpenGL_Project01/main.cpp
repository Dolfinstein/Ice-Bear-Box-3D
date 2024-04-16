#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "camera.h"


//float vertices[] = {
//	//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
//		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
//		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
//		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
//		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
//};


// Initiate Camera class

//Camera camera(glm::vec3(0, 0, 3.0f), glm::vec3(0, 0, 0), glm::vec3(0, 1.0f, 0)); // 此為target版本 1.position, 2.target, 3.worldup
Camera camera(glm::vec3(0, 0, 3.0f), glm::radians(15.0f), glm::radians(180.0f), glm::vec3(0, 1.0f, 0));


float lastX;
float lastY;
bool firstMouse = true; // 用來防止第一次沒東西在lastX, lastY可能導致游標量暴衝
void mouse_callback(GLFWwindow* window, double xPos, double yPos) //用來接收滑鼠input 一定要這樣定義 才符合gl的作法
{

	if (firstMouse == true)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	float deltaX = xPos - lastX;
	float deltaY = yPos - lastY;

	lastX = xPos;
	lastY = yPos;
	camera.ProcessMouseMovement(deltaX, deltaY);
	//std::cout << deltaX << std::endl;
}


float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};   


glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};
unsigned int indices[] = {
	0, 1, 2,
	2, 3, 0
};
using namespace std;
void processinput(GLFWwindow* window)
{
	
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}


	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) // 用來改變camera位置的偵測
	{
		camera.speedZ = 1.0f;
		//cout << camera.speedZ;
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.speedZ = -1.0f;
		//cout << camera.speedZ;
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.speedLR = -1.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.speedLR = 1.0f;
	}
	else
	{
		camera.speedZ = 0.0f;
		camera.speedLR = 0;
		//cout << camera.speedZ;
	}
};


//
//#version version_number // for the version of the OpenGL
//in type in_variable_name; // 輸入變數 這些變數是從VAO送進去的
//in type in_variable_name;
//
//out type out_variable_name;  // 輸出變數
//
//uniform type uniform_name; // uniform變數則是從cpu送進去的


//"#version 330 core                \n     "
//"layout(location = 0) in vec3 aPos;             \n   " // 把VAO中的 attribute 0號送進aPos當成輸入變數
//"void main() {\n                     "
//"              gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);}  \n"; // 這裡是把gl_Position作為輸出，裡面的值除了aPos的三個點外還多增加第四個維度並且值為1.0 特別的是gl_Position是不需要額外宣告的並且必須要叫這個名字
																		// 另外第四維度的用途為標記是純量位置還是向量位置、純量位置給1向量位置給0


int main() {

	


	glfwInit(); // 初始化函式庫
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// printf("hihihi");
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Window", NULL, NULL); // 此函式用於創建window並且返還該window的指標
	// (int width, int height, const char *title, 後面兩個也是給指針
	// 可以給NULL)
	if (window == NULL) // 如果開啟失敗就要結束執行
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // 把游標關掉
	glfwSetCursorPosCallback(window, mouse_callback); // glfw裡面用來接收滑鼠input的函數

	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		cout << "init GLEW failed";
		glfwTerminate();
		return -1;
	}


	

	glViewport(0, 0, 800, 600); // 起始座標為前兩個param 後兩個param為高跟寬 此為可以操作的空間


	glEnable(GL_DEPTH_TEST); // 此指令會使用z緩衝去計算深度訊息 避免錯誤的深度覆蓋
	Shader* myShader = new Shader("vertexSource.txt", "fragmentSource.txt");

	

	

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO); // bind 使他進入主要狀態 之後opengl就只會處理它





	/*unsigned int VAO[10];
	glGenVertexArrays(1, VAO);*/

	// OpenGL 同時只能運行一個VBO和一個VAO
	unsigned int VBO; // Vertex buffer object 用來把從cpu送來的點們存進GPU裡面
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);  // bind 使他進入主要狀態 之後opengl就只會處理它
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // 把data送進VBO





	unsigned int EBO;  // 類似於VBO 不過傳入的是索引值 在這裡給定四個頂點進入VBO
	// 然後再把六個索引值送入EBO 再使用使用索引值來畫出兩個三角形
	glGenBuffers(1, &EBO);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);



	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	/*glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);*/


	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(3);




	unsigned int TexBufferA; // texture的緩存
	glGenTextures(1, &TexBufferA); // 生成緩存
	glActiveTexture(GL_TEXTURE0); // 開啟GL_TEXTURE_2D的零號位置給他用
	glBindTexture(GL_TEXTURE_2D, TexBufferA); // 把緩存綁上gpu的GL_TEXTURE_2D裡面 注意這邊綁上零號位置


	

	int width, height, nrChannel;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("ice_bear01.jpg", &width, &height, &nrChannel, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "load image failed1";
	}
	stbi_image_free(data);

	unsigned int TexBufferB;
	glGenTextures(1, &TexBufferB);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, TexBufferB); // 注意這邊綁的位置是一號
	unsigned char* data2 = stbi_load("container.jpg", &width, &height, &nrChannel, 0);


	if (data2)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		cout << "load image failed2";
	}
	stbi_image_free(data2);

	

	

	/*unsigned int VAO[10];
	glGenVertexArrays(1, VAO);*/


	glm::mat4 trans; // 用glm 的mat4 來創造transformation matrix dimensioin 4 沒有特別聲明的話就是給idendity matrix
	
	
	
	/*trans = glm::translate(trans, glm::vec3(-0.1f, 0, 0));*/ // 移動矩陣 特別注意這個動作是把原本的trans(identity matrix)
	//去乘以一個以後面的param去決定的平移矩陣
	//所以如果把這個動作放到while裡面效果會不斷疊加起來
	/*trans = glm::rotate(trans, glm::radians(5.0f), glm::vec3(0, 0, 0.0f));*/
	// 1.目標矩陣, 2.角度(弧度為單位，其中glm::radians為把角度轉成弧度, 3.旋轉軸(沿著什麼旋轉))
	/*trans = glm::scale(trans, glm::vec3(2.0f, 2.0f, 2.0f));*/

	/*trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0, 0, 1.0f));
	trans = glm::scale(trans, glm::vec3(0.5, 0.5f, 0.5f));*/
	// 這裡trans做了兩個動作 注意雖然在程式上面是是先rotate再scale 也就是在矩陣乘法上面也是先rotate再scale
	// 但是這在實際上相當於是先scale再rotate 這個線性代數的矩陣乘法與線性變換的關係有關
	// 一般在做transform時實際上要要先scale再rotate再translate
	// 因此程式上(矩陣相乘上)要反過來 先translate再rotate再scale


	// Initiate Camera class

	//Camera camera(glm::vec3(0, 0, 3.0f), glm::vec3(0, 0, 0), glm::vec3(0, 1.0f, 0)); // 此為target版本 1.position, 2.target, 3.worldup
	//Camera camera(glm::vec3(0, 0, 3.0f), glm::radians(15.0f), glm::radians(180.0f), glm::vec3(0, 1.0f, 0));


	//------Coordinate system----vvv
	glm::mat4 modelMat;
	 modelMat = glm::rotate(modelMat, glm::radians(-25.0f), glm::vec3(1.0f, 0, 0));

	glm::mat4 viewMat;  // 針對攝影機的位置調整坐標系
	//viewMat = glm::translate(viewMat, glm::vec3(0, 0, -3.0f)); //假設攝影機在(0, 0, -3)的位置 因此要把整個模型往下面移動
																//這個矩陣要乘以整個model的所有座標點 可以使攝影機位置變成新座標的(0, 0, 0)
	viewMat = camera.GetViewMatrix();

	
	glm::mat4 projMat;
	projMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f); // 這個動作除了投影矩陣以外還有near far plane, clipping 跟透視裁切
	//------Coordinate system----^^^

	while (!glfwWindowShouldClose(window)) // 檢查窗口是否應該關閉
	{	
		//modelMat = glm::rotate(modelMat, glm::radians(-1.0f), glm::vec3(1.0f, 0, 0));
		//trans = glm::rotate(trans, glm::radians(50.0f), glm::vec3(1.0f, 0, 1.0f));
		//trans = glm::rotate(trans, glm::radians(5.0f), glm::vec3(0, 1.0f, 0.0f));
		//trans = glm::translate(trans, glm::vec3(-0.001f, 0, 0));
		processinput(window); //　我自己寫的函數

		glClearColor(0.5f, 0.5f, 0.5f, 1.0f); // 設置清除的顏色 裡面的值分別是RGBA A是透明度
		// glClear(GL_COLOR_BUFFER_BIT); // 清除緩衝區，顏色會跟著上面設置的
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 把z緩衝也給清掉 不然上一禎的z緩衝還影響現在這一禎很怪 
		glActiveTexture(GL_TEXTURE0);

		glBindTexture(GL_TEXTURE_2D, TexBufferA);
		glActiveTexture(GL_TEXTURE1);

		glBindTexture(GL_TEXTURE_2D, TexBufferB);


		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//float timeValue = glfwGetTime();
		//float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		//int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");  //  找出ourColor的位置
		//glUseProgram(shaderProgram);
		//glUniform4f(vertexColorLocation, 0, greenValue, 0, 1.0f);
		
		viewMat = camera.GetViewMatrix();

		for (int i = 0; i < 10; i++)  // 讓他畫十個箱子
		{	
			glm::mat4 modelMat2;
			modelMat2 = glm::translate(modelMat2, cubePositions[i]); //每個箱子位移值 根據cubePositions
			


			myShader->use();
			glUniform1i(glGetUniformLocation(myShader->ID, "ourTexture"), 0);// 把GL_TEXTURE的某個位置的圖給到fragment buffer的ourTexture裡面
			glUniform1i(glGetUniformLocation(myShader->ID, "ourFace"), 1);// 最後一個欄位要看讀取GL_TEXTURE幾號位置
			//glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "transform"), 1, GL_FALSE, glm::value_ptr(trans));
			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat2));
			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
			glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
			glDrawArrays(GL_TRIANGLES, 0, 36); // in this case is for drawing 3d box
		}


	         //myShader->use();
	         //glUniform1i(glGetUniformLocation(myShader->ID, "ourTexture"), 0);// 把GL_TEXTURE的某個位置的圖給到fragment buffer的ourTexture裡面
	         //glUniform1i(glGetUniformLocation(myShader->ID, "ourFace"), 1);// 最後一個欄位要看讀取GL_TEXTURE幾號位置
	         //glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "transform"), 1, GL_FALSE, glm::value_ptr(trans));
	         //glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
	         //glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
	         //glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
		     
		// glUnifoirmMatrix4fv 用途為把矩陣送入shader裡面的uniform variable裡面
		// 4代表4維 f代表float v則是vector
		// 可用的param則為 1. uniform variable的位置 2. 傳幾個矩陣 3. 是否要transpose 4. 要送進去的數據
		

		//glDrawArrays(GL_TRIANGLES, 0, 36); // in this case is for drawing 3d box

		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // 專門用EBO來畫的函式
		// 參數為 要畫什麼、要畫幾個頂點

		

		glfwSwapBuffers(window);  // 交換前後緩衝區，將渲染的內容呈現到螢幕上
		glfwPollEvents(); // 處理所有調用它之前被觸發的事件，如鍵盤輸入，滑鼠游標移動等等，檢查並調用相應的事件處理函數，用已響應用戶的輸入
		camera.UpdateCameraPos();

	}
	glfwTerminate();
	return 0;
	
	return 0;


}