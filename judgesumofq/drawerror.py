# 本文件将会读入error.txt中的数据，并绘制图像
import matplotlib.pyplot as plt
import numpy as np

import os

# 打印当前工作目录
print("Current working directory:", os.getcwd())

os.chdir('./judgesumofq')

# 读取数据
data = np.loadtxt('error.txt')

# 绘制图像
plt.plot(data)
plt.xlabel('iteration')
plt.ylabel('error')
plt.yscale('log')
plt.title('Error')
plt.show()
