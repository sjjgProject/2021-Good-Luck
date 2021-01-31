"""
Name:SunXinmeng
ID:18340149
Program:15puzzle.py
Compile and Run:python15puzzle.py
"""

target = {}
num = 1
#initialization target matrix
for i in range(4):
    for j in range(4):
        target[num] = (i, j)
        num += 1

    target[0] = (3, 3)

#define heuristic function h(n),node is the matrix to store state's picture
def h(node):
    cost = 0
    for i in range(4):
        for j in range(4):
            num = node[i][j]
            x, y = target[num]
            cost += abs(x - i) + abs(y - j)

    return cost


#judge if the node reaches final state
def is_goal(node):
    index = 1
    for row in node:
        for col in row:
            if (index != col):
                break
            index += 1
    return index == 16

#find successors of a node after ordering
def successors(node):
    x, y = 0, 0
    #find 0
    for i in range(4):
        for j in range(4):
            if (node[i][j] == 0):
                x, y = i, j
    success = []
    moves = [(1, 0), (-1, 0), (0, 1), (0, -1)]  #direction
    for i, j in moves:
        a, b = x + i, y + j
        if (a < 4 and a > -1 and b < 4 and b > -1):
            temp = [[num for num in col] for col in node]
            temp[x][y] = temp[a][b]
            temp[a][b] = 0
            success.append(temp)

    return sorted(success, key=lambda x: h(x))

#recursive function
def search(path, g, bound):
    node = path[-1]
    f = g + h(node) #f value of the node
    if (f > bound):
        return f
    if (is_goal(node)):
        return -1

    Min = 999
    for succ in successors(node):
        if succ not in path:    #cycle detect
            path.append(succ)
            t = search(path, g + 1, bound)
            if (t == -1):
                return -1
            if (t < Min):
                Min = t
            path.pop()

    return Min


def ida_star(root):
    bound = h(root)#use the h(root) to be bound
    path = [root]

    while (True):
        t = search(path, 0, bound)
        if (t == -1):   #is path == -1, then return the path and bound
            return (path, bound)
        if (t > 70):    #no path
            return ([], bound)

        bound = t

#choose a begin state to get started
def load():
    # root = [[2,  7,  5,  3],[11, 10,  9, 14],[4,  0,  1,  6],[4,  0,  1,  6]]
    # root = [[11, 3, 1, 7], [4, 6, 8, 2], [15, 9, 10, 13], [14, 12, 5, 0]]
    # root = [[5, 1, 3, 4], [2, 7, 8, 12], [9, 6, 11, 15], [0, 13, 10, 14]]
    root = [[6, 10, 3, 15], [14, 8, 7, 11], [5, 1, 0, 2], [13, 12, 9, 4]]
    return root


root = load()
(path, bound) = ida_star(root)
step = 0
print('********Solve 15 Puzzle********')
for p in path:
    print('--------------------')
    print('step', step,'>>')
    step += 1
    for row in p:
        print(row)


print('bound = ', bound)