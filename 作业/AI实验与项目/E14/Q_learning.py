"""
    孙新梦 18340149
    Q-learning.py
    实现实验要求上的机器人走房间的Q-learning算法
"""
import numpy as np
import random

# 奖励函数R
R = [
    [-1, -1, -1, -1, 0, -1],
    [-1, -1, -1, 0, -1, 100],
    [-1, -1, -1, 0, -1, -1],
    [-1, 0, 0, -1, 0, -1],
    [0, -1, -1, 0, -1, 100],
    [-1, 0, -1, -1, 0, 100]
]
# 参数alpha
alpha = 0.8
# 参数gamma
gamma = 0.8


# 大循环开始根据R随机选,返回操作的数字
def random_select_state():
    return random.randint(0, 5)


# 是不是到了5号房
def Goal(state):
    return state == 5


# 根据当前状态随机选择可能动作,返回动作编号（数字去到几号房
def random_select_action(state):
    not_zeros = [i for i in range(6) if R[state][i] != -1]
    action = random.sample(not_zeros, 1)
    return action[0]


# 大学习函数，进行外循环
def Q_learning(Q):
    epoches = 0

    # 大循环开始
    while epoches < 100:
        epoches += 1
        print("-------------------------------------")
        count = 0
        state = random_select_state()  # state是初始哪个房间的动作编号
        while not Goal(state):
            print("***************")
            action = random_select_action(state)
            print("action = ", action)
            next_state = action  # 相当于做了动作到了对应房间

            # 找到next_state对应可做动作的最大Q值，直接看Q对应那一行的最大值就是，
            # 因为如果不是可行的话，不会被更新，不会是最大值
            pre_Q = Q[state][action]
            Q[state][action] = (1 - alpha) * Q[state][action] + alpha * (R[state][action] + gamma * max(Q[next_state]))

            if pre_Q != Q[state][action]:
                count += 1
            state = next_state  # 状态更新
            # 输出显示
            print("state = ", state)
            print("Q = ")
            for i in Q:
                print(i)


if __name__ == '__main__':
    # Q矩阵初始化
    Q = np.zeros((6, 6))
    Q = Q.tolist()

    Q_learning(Q)

    # 输出Q
    print("-------------------------------------")
    print("最后的Q = ")
    for i in Q:
        print(i)
    print("最后策略：")
    for row in range(6):
        for i in range(6):
            if Q[row][i] == max(Q[row]):
                print("在房间 ", row," 就前往房间 ", i )