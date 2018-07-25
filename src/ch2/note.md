#### 绘图工具集
##### 清除窗口
* `glClearColor(r,g,b,a)` : RGBA 清屏
* `glClear(mask)`:清除指定缓冲区
  * GL_COLOR_BUFFER_BIT: 颜色缓冲区
  * GL_DEPTH_BUFFER_BIT: 深度缓冲区
  * GL_ACCUM_BUFFER_BIT: 累积缓冲区
  * GL_STENCIL_BUFFER_BIT: 模板缓冲区
* 需要设定每个缓冲区的清除值,每个缓冲区有对应函数

##### 指定颜色
 * 先设定颜色在绘制物体,`glColor3f()`设定
 
 #####
 * `glFinish`:强制以前发出的GL命令执行(不管数据处理了多少),在以前的命令执行完之前,函数不返回

