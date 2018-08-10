#### 绘图工具集
##### 清除窗口
* `glClearColor(r,g,b,a)` : RGBA 清屏
* `glClear(mask)` : 清除指定缓冲区
  * GL_COLOR_BUFFER_BIT: 颜色缓冲区
  * GL_DEPTH_BUFFER_BIT: 深度缓冲区
  * GL_ACCUM_BUFFER_BIT: 累积缓冲区
  * GL_STENCIL_BUFFER_BIT: 模板缓冲区
* 需要设定每个缓冲区的清除值,每个缓冲区有对应函数

##### 指定颜色
 * 先设定颜色在绘制物体,`glColor3f()`设定
 
##### 
 * `glFlush` : 强制以前发出的OpenGL命令开始执行,因此保证它们能够在优先时间内完成 - 不等待?
 * `glFinish` : 强制以前发出的GL命令完成执行,在以前的命令执行完之前,函数不返回 - 等待？
 
##### 绘图
  * 矩形 : `glRect()` , z=0
  * 指定顶点 : `glVertex()`
  * `glBelgn(GLenum mode)` : 开始绘图,到 `glEnd` 结束
   * `GL_POINTS` : 单个点
   * `GL_LINES` : 每两个点画一个线段
   * `GL_LINE_STRIP` : 连续线段
   * `GL_LINE_LOOP` : 同上,最后一个点和第一个连起来
   * `GL_TRIANGLES` : 三个点画一个三角形
   * `GL_TRIANGLE_STRIP` : 三角形串
   * `GL_TRIANGLE_FAN` : 三角形扇
   * `GL_QUADS` : 四个顶点画一个四边形
   * `GL_QUAD_STRIP` : 四边形串
   * `GL_POLYGON` : 一个凸多边形
  * `glEnd(void)` : 绘图结束
  
#### 状态管理 纹理、光照、隐藏表秒清除等等
  * `glEnable(GLenum capability)` : 启动状态
  * `glDisable(GLenum capability)` : 关闭状态
  * `glIsEnable(GLenum capability)` : 查询状态是否启用, 返回`GL_TRUE`或`GL_FALSE`
  * 状态查询函数,非true或false状态比如颜色等
   * `void glGetBooleanv(GLenum pname, GLboolean * params);`
   * `void glGetIntegerv(GLenum pname, GLint * params);`
   * `void glGetFloatv(GLenum pname, GLfloat * params);`
   * `void glGetDoublev(GLenum pname, GLdoublen * params);`
   * `void glGetPointerv(GLenum pname, GLvoid ** params);`
   
#### 点、直线、多边形
 * `glPointSize(GLfloat size);` :  设定点大小 默认1.0
 * `glLineWidth(GLfloat size);` : 设定线宽默认1.0
 * 点画线
 
        glLineStipple(1, 0x3F07);
        glEnable(GL_LINE_STIPPE);
        //void glLineStipple(GLint factor, GLushort patter);
        //factor 线段对patter 进行几次重复
        //patter 16位序列 0010000100001100 1绘制0不绘制,形成虚线,然后整个序列重复 factor 次
        
 * __多边形__
 * `void glPolygonMode(GLenum face, GLenum mode)` face : `GL_PRONT_AND_BACK`(3.1只有这个),`GL_FRONT`,`GL_BACK`  mode : `GL_POINT`,`GL_LINE`,`GL_FILL`
 * `void glFrontFace(GLenum mode)`:设定多边形正反面 mode : `GL_CCW`逆时针正面,`GL_CW`顺时针正面
 * `void glCullFace(GLenum mode)` : 剔除 mode : `GL_FRONT`,`GL_BACK`,`GL_FRONT_AND_BACK`, `glEnable(GL_CULL_FACE)`启动剔除功能,`glDisable(GL_CULL_FACE)`禁用
 * 点画填充多边形(32 x 32 窗口填充)`void glPolygonStipple(const GLubute * mask)` : mask 32x32 指针 GLubyte[128]   `glEable(GL_POLYGON_STIPPLE)`开启
 * 绘制多边形顶点可以指定点是否为边界起点,默认为是,不是顶点的不会被绘制,用来隐藏多边形内的三角形和不想展示的线段
  * `void glEdgeFlag(GLboolean flag)``void glEdgeFlagv(const GLboolean * flag)`: 两个之间的可以设定为flag判断的是否为边界点
  
  #### 法线
  * `void glNormal3`: 设定法线向量,画一个顶点之前设定一个法线
  * 法线向量自动规范化`glEnable(GL_NORMALIZE)`, `glEnable(GL_RESCALE_NORMAL)`
  
  #### 顶点数组 openGL 3.1 只支持顶点数组
  * __1启用数组__:`void glEnableClinetState(GLenum array)` , 禁用数组:`void glDisableClientState(GLenum array)`
   * `GL_VERTEX_ARRAY` : 顶点
   * `GL_COLOR_ARRAY` : 颜色
   * `GL_SECONDARY_COLOR_ARRAY` : 
   * `GL_INDEX_ARRAY` : 
   * `GL_NORMAL_ARRAY` : 法线
   * `GL_FOG_COORDINATE_ARRAY` : 雾
   * `GL_TEXTURE_COORD_ARRAY` : 纹理
   * `GL_EDGE_FLAG_ARRAY`: 剔除
 * __2指定数据__
  * `void glVertexPointer(GLint size, GLenum type, GLsizei stride, const GLvoid * pointer)` : 顶点
   * pointer : 数据指针
   * size : 每个顶点坐标数量 `2`|`3`|`4`
   * type : 顶点数据类型 `GL_SHORT`|`GL_INT`|`GL_FLOAT`|`GL_DOUBLE `
   * stride : 联系顶点之间字节偏移量, 如果用混合数组 则指定一个顶点的元素开始为pointer 跨度为一个顶点元素数量
   * `glColorPointer`,`glSeconaryColorPointer`,`glIndexPointer`,`glNormalPointer`,`glFogCoordPointer`,`glTexCoordPointer`,`glEddgeFlagPointer`
 * __3解引用和渲染__
  * `void glArrayElement(GLint ith)` : 获取已经疫情数组的一个顶点数据,调用glVertex,glColor等,数据会自己计算传入,glBegin和glEnd之间调用
  * `void glDrawElements(GLenum mode, GLsizei count, Glenum type, const GLvoid * indices)` : 
  
            //相当于
            glBegin(mode);
            for(int i = 0 ; i < count, i ++){
                glArrayElement(indices[i]);
            }
            glEnd();
            
   * indices : 顶点索引数组 ; mode : 和glBegin参数相同,标识如何绘制 ; count:元素个数 ; type:indices里数据类型
   * `void glMultiDrawElements(GLenum mode, GLsizei * count, GLenum type, const GLvoid ** indices, GLsizei primcount)` :  连续的glDrawElements
  * `void glDrawRangeElements`:
  * `void glDrawArray(GLenum mode, GLint first, GLsizei count)` : 渲染整个顶点元素数组
  * `vodi glMultiDrawArray(GLenum mode, GLint * first, GLsizei * count, GLsizei primcount)` : 好几个 glDrawArray
  *__混合数组__ : `void glInterleavedArray(GLenum format, GLsize stride, const GLvoid * pointer)` : 用一个混合数组初始化顶点数据,没有偏移设置
   * format : GL_V2F、GL_VEF_V3F...... 数组数据类型 
   * stride : 连续顶点之间的字节偏移一般为0表示顶点之间无别的数据
   
#### 缓冲区: 标识符生成,3.1之后只能系统分配
*  `void glGenBuffer(GLsizei n, GLuint * buffers)` : 创建,在buffer数组中返回nge当前未使用的名称,0保留不返回
*  `GLboolean glIsBuffer(GLUint buffer)` : 判断名称是否用了
*  `void glBindBuffer(GLenum target, GLuint buffer)` :  指定当前活动缓冲区对象然后操作, target:GL_ARRAY_BUFFER,GL_ELEMENT_ARRAY_BUFFER...
*  `void glBufferData(GLenum targetm GLsizeiptr size, const GLvoid * data, GLenum usage)` : 分配空间
 * target : `GL_ARRAY_BUFFER`顶点,`GL_ELEMENT_ARRAY_BUFFER`索引数据,`GL_PIXEL_UNPACK_BUFFER`(传递给GL的像素数据),`GL_PIXEL_PACK_BUFFER`(从GL获取的像素数据),`GL_COPY_READ_BUFFER``GL_COPY_WRITE_BUFFER`(缓冲区之间复制数据),`GL_TEXTURE_BUFFER`(作为纹理缓冲区存储纹理),`GL_TRANSFORM_FEEDBACK_BUFFER`(执行一个反馈着色器的效果),`GL_UNIFORM_BUFFER`(统一变量值)
 * size : 大小
 * data : 为NULL函数会保留size个单位供初始化使用,但不会初始化,不为空则从data指向的地址复制到GL服务机
 * usage : 数据分配之后如何读写, GL_STREAM_DRAW,GL_STREAM_READ,GL_STREAM_COPY.....
* `void glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid * data)` : 更新缓冲区数据

#### 顶点数组对象
       











