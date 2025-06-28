# 本文件将分别对3个txt文件绘制图像
import matplotlib.pyplot as plt
import numpy as np

# 读取数据
data1 = np.loadtxt('time1.txt')
data2 = np.loadtxt('time2.txt')
data3 = np.loadtxt('time3.txt')

# 绘制图像
plt.figure()
plt.plot(data1, label='time for find after sort', marker = 'o')
plt.plot(data2, label='time for divide and conquer', marker = '^')
plt.plot(data3, label='time for SLT', marker = 's')
plt.legend()
plt.yscale('log')
plt.xlabel("num of input in log scale")
plt.ylabel("time in log scale")
plt.show()

# 绘制柱状图，将三个算法的时间绘制在同一张图上
plt.figure()
bar_width = 0.25
index = np.arange(len(data1))
plt.bar(index, data1, bar_width, label='time for find after sort')
plt.bar(index + bar_width, data2, bar_width, label='time for divide and conquer')
plt.bar(index + 2 * bar_width, data3, bar_width, label='time for SLT')
plt.legend()
plt.xlabel("num of input")
plt.ylabel("time")
plt.yscale('log')
plt.show()
