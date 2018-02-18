import numpy as np

if __name__ == '__main__':
    A = np.random.random(16).reshape(4, 4)
    print(A)
    for x_a in range(0, np.size(A,0)-2):
        for x_b in range(x_a + 1, np.size(A,0)-1):
            for x_c in range(x_b + 1, np.size(A,0)-0):
                for y_a in range(0, np.size(A,1)-2):
                    for y_b in range(x_a + 1, np.size(A,1)-1):
                        for y_c in range(x_b + 1, np.size(A,1)-0):
                            print(A[[x_a,x_b,x_c],:].T[[y_a,y_b,y_c],:].T)
