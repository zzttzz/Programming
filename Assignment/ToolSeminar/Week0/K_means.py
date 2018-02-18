import random

mu = [[0., 0.], [2., 3.], [-1, 4.], [10., 10.]]
sigma = [[1., 1.], [0.7, 0.9], [0.6, 0.4], [2., 3.]]
num = [50, 150, 100, 200]
k = 4

seed = 0
random.seed(seed)

data = []
for i in range(k):
    data += [[random.gauss(mu[i][j], sigma[i][j]) for j in range(2)] for r in range(num[i])]
# for i in range(k):
#     for r in range(num[i]):
#             data += [[random.gauss(mu[i][j], sigma[i][j]) for j in range(2)]]
# print(data)
rep = 40
cid = [0, 1, 2, 3]


def Distance(p1, p2):
    return ((p1[0] - p2[0]) ** 2 + (p1[1] - p2[1]) ** 2) ** (1 / 2)


def C_point(g_ind, data):
    return [(sum(data[i][j] for i in g_ind) / max(len(g_ind),1)) for j in range(2)]


def Clustering(data, cid, rep, k):
    cpoint = []
    glist = []
    for i in cid:
        cpoint += [data[i]]

    for r in range(rep):
    # 一次循环：
        glist.clear()
        for i in range(k):
            glist += [[]]
        for index, p in enumerate(data):
            n = [0]
            for i in range(k):
                if Distance(p, cpoint[i]) < Distance(p, cpoint[n[0]]):
                    n[0] = i
            glist[n[0]] += [index]

        for i in range(k):
            cpoint[i] = C_point(glist[i], data)
    return glist

if __name__ == '__main__':
    g=Clustering(data,cid,rep,k)

    print((g[1]))
