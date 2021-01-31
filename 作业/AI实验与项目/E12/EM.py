"""
    File:EM.py
    Name:孙新梦
    ID:18340149
    TASK:用EM算法对Iris数据集进行分类，
        输出γ，μ，Σ，可视化输出分类
"""
import math
import numpy as np
from copy import deepcopy as cp


def readData():
    data = []
    lable = []
    with open('iris.data', 'r') as f:
        flag = 0
        for line in f.readlines():
            now_line = line.split(',')
            data.append(list(map(lambda x: float(x), now_line[:-1])))
            lable.append(line[-1])
    return data, lable


def gaussion(inputs, miu, sigma):
    D = len(miu)

    m = [inputs[i] - miu[i] for i in range(D)]
    minus = np.array(m)

    return 1 / (math.sqrt(math.pow(2 * math.pi, D) * np.linalg.det(sigma)) ) * math.exp(
        -0.5 * (minus.reshape(1, D)).dot(np.linalg.inv(sigma)).dot(minus.reshape(D, 1)))


def get_init(data, K, dim):
    N = len(data)
    mask = np.random.permutation(N)[:K]
    miu = cp(data[mask])
    sigma = np.array([np.zeros((dim, dim)) for i in range(K)])

    for i in range(K):
        for j in range(dim):
            sigma[i, j, j] = np.random.rand()
    # sigma = np.array([np.identity(dim) for i in range(K)])

    pi = np.ones(K) / K
    return pi, miu, sigma


def EM(data, K, dim):
    # initialization
    pi, miu, sigma = get_init(data, K, dim)

    N = len(data)
    # N*K的一个矩阵——shape参数,行数表示哪一个样例，列数表示是哪一类的概率
    gamma = np.ndarray((N, K))

    # 10次迭代
    for epoch in range(10):
        print("\n-----第 ", epoch, " 次迭代-----")
        print("μ = ", miu)
        print("Σ = ", sigma)
        print("Π = ", pi)

        # E step
        for n in range(N):
            fenmu = 0
            for k in range(K):
                val = pi[k] * gaussion(data[n], miu[k], sigma[k])
                gamma[n, k] = val
                fenmu += val
            gamma[n] /= fenmu

        # M step
        Nk = gamma.sum(0)
        pi = Nk / N
        for k in range(K):
            temp = np.zeros(miu[k].shape)
            for n in range(N):
                temp += gamma[n, k] * data[n]
            miu[k] = temp / Nk[k]

            temp = np.zeros(sigma[k].shape)
            for n in range(N):
                temp += gamma[n, k] * ((data[n] - miu[k]).reshape(data[n].size, 1)).dot(
                    (data[n] - miu[k]).reshape(1, data[n].size))
            sigma[k] += temp / Nk[k]

    print("\n\n*****分类*****")
    for n in range(N):
        the_class = np.argmax(gamma[n])
        print("第 ", n, " 条，分类为：第 ", the_class, " 类")


# name = ['']
if __name__ == '__main__':
    K = 3
    data, lable = readData()
    data = np.array(data)
    # dimension = 4
    EM(data, K, 4)
