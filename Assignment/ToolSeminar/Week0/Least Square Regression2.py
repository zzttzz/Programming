import numpy
import random

def loss_func(x, y, a_t, b_t):
    error = a_t + b_t * x - y
    return 1. / 2. * numpy.sum(error**2)

def train_func(x, y, a_t, b_t, eta):
    n = x.shape[0]
    grad_a = numpy.ones(n).dot(a_t + b_t * x - y)
    grad_b = x.dot(a_t + b_t * x - y)

    a_tp1 = a_t - eta * grad_a
    b_tp1 = b_t - eta * grad_b

    return [a_tp1, b_tp1]

class Trainer:
    def __init__(self,config,loss_func,train_func):
        self.x,self.y,self.a,self.b,self.a_ture,self.b_ture,self.eta=config
        self.loss_func=loss_func
        self.train_func=train_func
        self.loss=float("inf")
        self.iter_ctr=0

    def one_iteration(self):
        self.loss=self.loss_func(self.x,self.y,self.a,self.b)
        self.a,self.b=self.train_func(self.x,self.y,self.a,self.b,self.eta)
        self.iter_ctr+=1
    def go(self,n=1000):
        for i in range(n):
            self.one_iteration()
    def result(self):
        print("Final #iteration: {0}, loss: {1:.5f}".format(self.iter_ctr, self.loss))
        print("Result: a = {0:.5f}, b = {1:.5f}".format(self.a, self.b))
        print("Groundtruth:  a = {0:.5f}, b = {1:.5f}".format(self.a_true, self.b_true))