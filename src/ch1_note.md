## OpenGL概述

---

###1.1 OpenGL

* 是一种应用程序编程接口(Application Programming Interface,API)，可以对图形硬件设备访问。
* OpenGL与硬件无关，拥有很好的可移植性，在多种电脑和移动平台上都可以使用
* 由于OpenGL与硬件无关，所以它**没有实现应用程序窗口或者处理用户输入操作的的函数也没有表达任何三维物体的模型以及读取图形文件的函数**。上面所说的功能需要根据不同平台的差异性来进行开发，或者使用一些已经写好的工具库例如(glut)。
* OpenGL使用客户端-服务器的形式实现的，我们编写的程序可以看做客户端，而计算机图形硬件厂商所提供的OpenGL实现可以看做服务器。
* 总的来说OpenGL是一个底层花的图形接口，它所做的只是把程序设计的图像信息通过硬件平台显示在屏幕上。


###1.2 初识OpenGL程序(了解程序结构)

渲染(render):从模型创建最终图像的过程。
模型(model):描述渲染物体的模型，一组在空间中的顶点(vertex)的集合，通过集合图元(包括点、线、三角)构建。**也就是说空间中的一些顶点所包围的区域可以理解为一个形状，而用点来构建就是一组点，用线来构建就是一个空框，用三角形来构建就是一个物体的样子了(3.0之后已经没有三角形之外的多边形来构建模型，因为三角形最简单，其他任何多边形都可以由三角形替换)。**
着色器(shader):为图形处理单元(GPU)编译的一种小型程序，从着色器可以创建GPU所需要的编译代码并执行。**就是封装好了的渲染函数**。

###1.3 OpenGL语法(函数规则、数据类型)

* OpenGL库中的函数都是以gl开头，两个工具库glew和glut则是以glew和glut开头。
* 所有的常量都是GL_开头。
* 为了在不同操作系统中一直OpenGL定义了自己的变量类型    


|后缀|数据类型|C类型|OpenGL类型|    

|----|----|----|----|    
|b|8位整型|signed char|GLbyte|
|s|16位整型|signed short|GLshort|
|i|32位整型|int|GLint,GLsizei|
|f|32位浮点型|float|GLfloat,GLclampf|
|d|64位浮点型|double|GLdouble,GLclampd|
|ub|ub8位无符号整型|unsigned char|GLubyte|
|us|16位无符号整型|unsigned short|GLushort|
|ui|32位无符号整型|unsigned byte|GLuint,GLuenum,GLbitfield|    


* 函数后缀中的数字表示函数需要传入的参数个数，字母表示参数类型，2f代表2个GLfloat类型，后缀字母为v则表示要传入一个向量(vector)，即点坐标数组。
* 使用OpenGL数据类型可以避免多平台移植时数据类型不匹配的问题。

###1.4 OpenGL渲染管线(如何从数据到屏幕上的图像)

**顶点数据-->顶点着色器-->细分控制着色器-->细分计算着色器-->几何着色器-->图元设置-->剪切-->光栅化(rasterizer)-->片元着色器-->屏幕图像**

1. __准备向OpenGL传输数据__。将需要的所有数据保存到缓存对象中。常用方法`glBufferdata();`。
2. __将数据传输到OpenGL__。通过绘图命令请求渲染缓存中的几何图元。例如`glDrawArrays()；`。
3. __顶点着色__。对于每个顶点OpenGL会调用一个顶点着色器来处理数据，可能是直接传递，也可能进行大量的顶点计算，比如矩阵转换(物体移动的时候)或者颜色计算(颜色改变或者光照改变的时候)。
4. __细分着色__。使用Patch来描述一个的形状，使用相对简单的几何体链接完成细分的工作(组成物体表面)。这会让几何图元数量增加且外观更为平顺。
5. __几何着色__。在光栅或之前对每个几何图元做更近一步的处理，这个阶段可选。
6. __图元装配__。将顶点与相关的几何图元组织起来，准备剪切和光栅化。
7. __剪切__。移除落在视口(viewport)也就是窗口区域之外的顶点，由OpenGL自动完成。
8. __光栅化__。将图元传递到光栅化单元，生成对应的片元(候选的像素)放入缓存，进行下面处理。
9. __片元着色__。使用着色器计算最终的颜色和深度值，如果使用纹理会进行纹理映射来决定片元的颜色值。这一步主要决定片元的颜色。
10. __逐片元操作__。通常会使用深度测试和模板测试来决定一个片元是否可见。

###1.5 OpenGL相关函数库

* GLU:包含了一些函数，利用地城的OpenGL执行一些特定任务，例如设置矩阵，多边形以及表面渲染，资料《OpenGL Refrence Manual》。
* 不同操作系统对GL的支持库，X窗口：GLX，Windows：WGL，Mac：AGL、CGL、Cocoa。
* OpenGL实用工具库(OpenGL Unity Tookit,GLUT)。术中使用freeglut,我这里如果不是必须就用自带的glut。
* GLUT说明：可以完成在不同系统下生成窗口，处理用户输入以及生成一些简单三维物体,下面是常用函数。

* `glutInit(int * argc , char **argv)；`**初始化GLUT，写在其他GLUT函数之前**。
* `glutInitDisplayMode(unsigned int mode);`指定使用RGBA显示模式还是颜色索引模式，还可以指定单缓冲或者双缓冲窗口，还可以表示希望窗口拥有的相关联的深度、模板、多重采样和缓冲区。例如`glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);`表示选用双缓冲窗口，RGBA模式，深度。
* `glutInitWindowPosition(int x , int y);`指定窗口位置(左上角)。
* `glutInitWindowSize(int width , int size);`指定窗口大小(像素单位)。
* `glutInitContextVersion(int majorVersion,int minorVersion);`声明使用OpenGL的版本(freeglut新增函数)，
* `glutInitContextFlags(int flags);`声明了想要使用的OpenGL渲染环境(freeglut新增函数)。
* `glutCreateWindow(char * string);`创建窗口，在`glutMainLoop()`之前这个窗口并没有显示。
* `glutDisplayFunc(void(*func)(void));`每当GLUT确定一个窗口的内容需要重新显示时，会通过`glutDisplayFunc()`注册的回调函数刷新窗口，**所以重新绘制场景的所有代码都要在这个函数里**。
* `glutPostRedisplay()`如果程序修改了窗口内容，这个函数会知识`glutMainLoop()`调用已经注册的显示回调函数。
* `glutMainLoop()`启动程序。
* `glutReshapeFunc(void(*Func)(int w , int h))`窗口大小发生变化调用。
* `glutKcyboardFunc(void(*Func)(unsigned char key , int x , int y))`键盘按键时候调用。
* `glutMouseFunc(void(*Func)(int button , int state , int x , int y))`鼠标按下时候调用。
* `glutMontionFunc(void(*Func)(int x, in ty))` 拖动鼠标时调用。
* `glutIdelFunc(Void(*Func)(void))`如果不存在其他尚未完成的事件，就执行这个函数。**如果传递NULL(0)，就相当于禁用这个函数**。
* 绘制函数，立方体和球体，它们的中心都为与全局坐标系统的原点。

        void glutWireCube(GLdoubel size);
        void glutSolidCube(GLdoubel size);
        void glutWireSphere(GLdoubel radius , GLint slices , GLint staks);
        void glutSolidSphere(GLdoubel radius , GLint slices , GLint staks);


###1.6 动画   

* 在每秒固定帧数的刷新情况下，由于正在绘制的物体会越来越快的清除，所以光宠可能看到的只有被清除的背景。绝大多数情况下OpenGL采用双缓冲提供两个颜色缓冲区交互显示和绘制。
* `swap_the_buffers();`函数用来交换缓冲区来更新帧，它会等待屏幕刷新周期结束，这样就会完整的显示内容。
* 如果帧的内容太复杂，无法再一个帧的时间内完成绘制，那么每帧显示的次数将不止一次。
* `void glutSwapBuffer();`函数是上述函数在glut中的实现。






