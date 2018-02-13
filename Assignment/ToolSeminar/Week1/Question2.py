import time

def show_time(func):
    def wrapper(*ar):
        print("Executing time:",time.time())
        func(*ar)
    return  wrapper


