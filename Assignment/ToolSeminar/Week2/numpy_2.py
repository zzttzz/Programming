import numpy as np


def gauss(arr):
    for i in range(np.size(arr, 1)):  # 对每一列
        for j in range(i, np.size(arr, 0)):  # 对每一行,找出第j+1元不为零的行，并与第i+1行交换
            if arr[j, i] != 0 and arr[j, i] > arr[i, i]:  # 取最大元
                arr[[i, j], :] = A[[j, i], :]  # 交换第i+1行与第j+1行,
        for m in range(i + 1, np.size(arr, 0)):  # 消去第j+1元
            arr[m] = arr[m] + (-arr[m, i] / arr[i, i]) * arr[i]


if __name__ == '__main__':
    A = np.random.random(100).reshape(10, 10)
    # A = np.arange(9.0).reshape(3, 3)
    gauss(A)
    print(A)
    r = np.size(A, 0)
    for i in range(np.size(A, 0)):
        for j in range(i, np.size(A, 1)):
            if (abs(A[i, j]) > 0.000001):
                break
            r = i
    print("rank(A):{}".format(r))
