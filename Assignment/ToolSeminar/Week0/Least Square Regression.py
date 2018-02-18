import random
import numpy


class Trainer:
    def __init__(self, config):
        self.x, self.y = config

    def Result(self):
        self.a = (2 * sum([(i - sum(self.x) / len(self.x)) * (self.y[j] - sum(self.y) / len(self.y))] for j, i in
                          enumerate(self.x)) / sum([(i - sum(self.x) / len(self.x)) ** 2 for i in self.x]))
        self.b = (sum(self.y) - self.a * sum(self.x)) / len(self.x)


