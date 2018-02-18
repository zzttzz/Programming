import numpy as np
import math
def xy_to_A(x,y):
    r=(x**2+y**2)**(1/2)
    sin=y/r
    cos=x/r
    if sin>=0:
        if cos>=0:
            return math.asin(sin)
        else:
            return (math.pi-math.asin(sin))
    else:#sin<0
        if cos>=0:
            return (2*math.pi+math.asin(sin))
        else:
            return (math.pi-math.asin(sin))


if __name__ == '__main__':
    m_D=np.random.random(20).reshape(10,2)
    mx=np.hsplit(m_D,2)[0]
    my=np.hsplit(m_D,2)[1]
    mr=(mx**2+my**2)**(1/2)
    m_P=np.zeros(20).reshape(10,2)
    for i in range(0, 10):
        m_P[i]=np.array([mr[i][0],xy_to_A(m_D[i][0],m_D[i][1])])
    print(m_P)
