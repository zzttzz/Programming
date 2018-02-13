import Question3
import json


class UserEncoder(json.JSONEncoder):
    def default(self, obj):
        if isinstance(obj, Question3.stack):
            a = obj
            b = []
            while not a.isempty():
                b.append(a.pop())
            return b
        return json.JSONEncoder.default(self, obj)


def serialize(object):
    return json.dumps(object, cls=UserEncoder)

#Test
if __name__ == '__main__':
    a = Question3.stack()
    a.push(1)
    a.push(2)
    a.push(3)

    print(serialize(a))

