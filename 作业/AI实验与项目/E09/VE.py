"""
    孙新梦
    18340149
    AI E09
"""


class VariableElimination:
    @staticmethod
    def inference(factorList, queryVariables,
                  orderedListOfHiddenVariables, evidenceList):

        # step1.restrict. 把每个因子里面含有证据的替换取值，创建新的表
        for ev in evidenceList:  # 遍历证据
            for factor in factorList:  # 遍历所有因子找出含有证据的相关因子
                if ev in factor.varList:
                    # 使用restrict函数替换变量的值并创建新的cpt
                    factorList.append(factor.restrict(ev, evidenceList[ev]))
                    # 删除原先的factor
                    factorList.remove(factor)

        # step2.elimation.按照给定的顺序进行变量消除算法
        for var in orderedListOfHiddenVariables:  # 消除顺序遍历变量
            # 含有目标变量的要加入elimationList
            elimationList = list(filter(lambda factor: var in factor.varList, factorList))

            new_var = elimationList[0]
            for eli in elimationList:
                for factor in factorList:
                    if factor.name == eli.name:
                        factorList.remove(factor)
                # 第一个之后乘起来
                if eli != elimationList[0]:
                    new_var = new_var.multiply(eli)
            new_var = new_var.sumout(var)   #加和
            factorList.append(new_var)

        #计算结果
        print("RESULT:")
        res = factorList[0]
        for factor in factorList[1:]:
            res = res.multiply(factor)
        total = sum(res.cpt.values())
        res.cpt = {k: v / total for k, v in res.cpt.items()}
        res.printInf()

    @staticmethod
    def printFactors(factorList):
        for factor in factorList:
            factor.printInf()


class Util:
    @staticmethod
    def to_binary(num, len):
        return format(num, '0' + str(len) + 'b')


class Node:
    def __init__(self, name, var_list):
        self.name = name
        self.varList = var_list
        self.cpt = {}

    def setCpt(self, cpt):
        self.cpt = cpt

    def printInf(self):
        print("Name = " + self.name)
        print(" vars " + str(self.varList))
        for key in self.cpt:
            print("   key: " + key + " val : " + str(self.cpt[key]))
        print("")

    def multiply(self, factor):
        """function that multiplies with another factor"""
        # Your code here
        # 两个节点的表相乘
        newList = [var for var in self.varList]
        new_cpt = {}

        # 计算公共变量的索引
        index1 = []
        index2 = []
        for var1 in self.varList:
            for var2 in factor.varList:
                if var1 == var2:
                    index1.append(self.varList.index(var1))
                    index2.append(factor.varList.index(var2))
                else:
                    newList.append(var2)

        for k1, v1 in self.cpt.items():
            for k2, v2 in factor.cpt.items():
                flag = True  # 表示两个项能否做乘积，要求之前记录的公共部分相同都为00之类
                for i in range(len(index1)):
                    if k1[index1[i]] != k2[index2[i]]:
                        flag = False
                        break
                    if flag:
                        new_key = k1  # 以k1为蓝本，添加k2除了相同的项之外的符号
                        for i in range(len(k2)):
                            if i in index2:
                                continue
                            new_key += k2[i]

                    new_cpt[new_key] = v1 * v2

        # theList = []
        # for letter in newlist:
        #     theList.append(letter)
        #print(theList)

        new_node = Node("f" + str(newList), newList)  # newlist为两个节点的list合并去重
        # new_node = Node("f"+str(theList), theList)
        new_node.setCpt(new_cpt)  # 新的cpt为两个产生的newcpt

        return new_node

    def sumout(self, variable):
        """function that sums out a variable given a factor"""
        # Your code here
        new_var_List = [var for var in self.varList]
        new_var_List.remove(variable)
        new_cpt = {}

        # index:需要被加和的遍历的下标
        index = self.varList.index(variable)

        # 遍历cpt字典的键值对，把目标变量相同的加在一起
        for k, v in self.cpt.items():
            # 没有记录过这一项新增上来，
            if k[:index] + k[index + 1:] not in new_cpt.keys():
                new_cpt[k[:index] + k[index + 1:]] = v
            else:  # 有了加和在原来基础上
                new_cpt[k[:index] + k[index + 1:]] += v

        theList = []
        for letter in new_var_List:
            theList.append(letter)
        #print(theList)

        new_node = Node("f" + str(theList), theList)
        new_node.setCpt(new_cpt)
        return new_node

    def restrict(self, variable, value):
        """function that restricts a variable to some value
        in a given factor"""
        # Your code here
        new_var_List = [var for var in self.varList]
        new_var_List.remove(variable)
        new_cpt = {}

        # index:需要被限制的变量下标
        index = self.varList.index(variable)

        # 把和value相同的variable的值存放进新字典
        for k, v in self.cpt.items():
            if k[index] == str(value):
                new_cpt[k[:index] + k[index + 1:]] = v

        theList = []
        for letter in new_var_List:
            theList.append(letter)
        #print(theList)

        new_node = Node("f" + str(theList), theList)
        new_node.setCpt(new_cpt)
        return new_node


# create nodes for Bayes Net
B = Node("B", ["B"])
E = Node("E", ["E"])
A = Node("A", ["A", "B", "E"])
J = Node("J", ["J", "A"])
M = Node("M", ["M", "A"])

# Generate cpt for each node
B.setCpt({'0': 0.999, '1': 0.001})
E.setCpt({'0': 0.998, '1': 0.002})
A.setCpt({'111': 0.95, '011': 0.05, '110': 0.94, '010': 0.06,
          '101': 0.29, '001': 0.71, '100': 0.001, '000': 0.999})
J.setCpt({'11': 0.9, '01': 0.1, '10': 0.05, '00': 0.95})
M.setCpt({'11': 0.7, '01': 0.3, '10': 0.01, '00': 0.99})

print("P(A) **********************")
VariableElimination.inference([B, E, A, J, M], ['A'], ['B', 'E', 'J', 'M'], {})

print("P(B | J~M) **********************")
VariableElimination.inference([B, E, A, J, M], ['B'], ['E', 'A'], {'J': 1, 'M': 0})

print("P(A | J~M) **********************")
VariableElimination.inference([B, E, A, J, M], ['A'], ['B', 'E'], {'J': 1, 'M': 0})
