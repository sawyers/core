"""
# Basic print and input from prompt

name = input("input name ")

age = input(f"How old is {name} ")

print(f"{age} is old")
"""

"""
# -------------- Basic If loops

print("What's your name?")
name = input()

if name.lower() == "mike":
    print("back for more pain?")
elif name.lower() == "Bob":
    print(f"{name} sniffs gym socks")
else:
    print(f"Nice to see you {name}")
"""

"""
# -------------- For loops

for i in range(0, 10):  # repeat 10x 0 - 10
    print(f"hello {i}")

num = input("Enter a number: ")

for i in range(0, 10):
    print(num * i)
"""


"""
# -------------- factorization list prime numbers

num = input("Enter a number to factorize: ")
num = int(num)

counter = 0

for i in range(1, num + 1):
    if num % i == 0:
        print(f"{i} is a factor")
        counter += 1

if counter == 2:
    print(f"{num} is a prime number")
"""


"""
# -------------- factorization with loops

num = input("Enter a number to factorize: ")
num = int(num)

for i in range(1, num + 1):
    if num % i == 0:
        print(f"{i} is a factor")
"""


"""
# -------------- Inputs with turtle to draw a square

import turtle

len = int(input("Side length is: "))

for i in range(0, 4):
    turtle.forward(len)
    turtle.left(90)
"""


"""
# -------------- Turtle with more loops

import turtle

len = int(input("Side length is: "))
sides = int(input("Num of sides: "))

# Twisted display
while True:
    len -= 2
    turtle.forward(len)
    turtle.left(360 / sides)
    turtle.left(1)
    if len < 0:
        break

# 2nd, concentric pattern
while True:
    len -= 2
    turtle.forward(len)
    turtle.left(360 / sides)
    if len < 0:
        break

# First example
for i in range(0, sides):
    turtle.forward(len)
    turtle.left(360 / sides)
    for i in range(0, sides):
        turtle.forward(len)
        turtle.right(360 / sides)
"""

"""
# -------------- Turtle lists and colors

import turtle
import random

turtle.speed(100)
colors = ["green", "blue", "red", "purple"]

x = 1
while x < 275:
    turtle.forward(x)
    turtle.right(75)
    c = random.choice(colors)
    turtle.color(colors[x % 4])  # cycle through colors or...
    # turtle.color(c) # pick random color
    x += 1
"""

"""
Did not know this was an option, it makes the idea of a DnD assistant so much easier.
Instead of 'rolling' 3d6 and adding the results I can just do random.choice(range(3,19))
and get the job done with one statement. Same for all the data table roles. So much
easier than what I had been doing
"""


"""
# -------------- Turtle with coordinates

import turtle
import random

turtle.speed(100)
colors = ["green", "blue", "red", "purple"]
sizes = [22, 35, 74, 37, 55, 63, 82, 95, 99, 29]
locations = [-250, 200, 15, 289, 55, 211, -180, 150, -99]


def poly(sides, sideL):
    for i in range(0, sides):
        turtle.forward(sideL)
        turtle.left(360 / sides)


for i in range(1, 11, 2):
    y = locations[i]
    x = locations[i - 1]
    turtle.penup()
    turtle.goto(x, y)
    turtle.pendown()
    turtle.color(random.choice(colors))
    turtle.begin_fill()
    poly(random.randint(3, 8), random.choice(sizes))
    turtle.end_fill()
"""

"""
# -------------- Functions in python

def hello5():
    i = 0
    while i < 6:
        print("hello")
        i += 1


def greet(person):
    print(f"Hello {person}")


def addnums(num1, num2):
    return num1 + num2


def factorize(num):
    for i in range(1, num - 1):
        if num % i == 0:
            print(f"{i} is a factor")


greet("Mike")
print(addnums(5, 2))
factorize(57)
"""


"""
# -------------- Functions with turtle

import turtle

turtle.speed(100)


def poly(sides, length):
    for i in range(0, sides):
        turtle.forward(length)
        turtle.left(360 / sides)
    turtle.forward(3)
    turtle.left(5)
    if length < 1:
        return False
    poly(sides, length - 2)


poly(5, 125)
"""


"""
# -------------- Functions to organize code
def main():
    print("Make a selection by number:")
    print("Press 1 for greeting")
    print("Press 2 for timestable")
    print("Press 3 for factorize")
    choice = input("Your selection: ")

    if choice == "1":
        greeting()
    elif choice == "2":
        timestable()
    else:
        factorize()


def factorize():
    num = int(input("Enter a number to factorize: "))
    for i in range(1, num - 1):
        if num % i == 0:
            print(f"{i} is a factor")


def greeting():
    print("What's your name?")
    name = input()

    if name.lower() == "mike":
        print("back for more pain?")
    elif name.lower() == "Bob":
        print(f"{name} sniffs gym socks")
    else:
        print(f"Nice to see you {name}")


def timestable():
    num = int(input("Enter a number: "))

    for i in range(0, 10):
        print(num * i)


main()
"""

"""
# -------------- Built-in String functions
# https://www.w3schools.com/python/python_ref_string.asp

bobo = "HKJkj ksd fkKJHjk sdkjas"
bobo.upper()  # all upper
bobo.lower()  # all lower
bobo.capitalize()  # First cap rest lower
bobo.title()  # first letter of the each word cap
bobo.strip()  # Remove matching char, default space and returns list
len(bobo)  # how long
bobo[0:5]  # return range
bobo[:-1]  # last
bobo.isupper()  # is all upper
bobo.startswith
bobo.endswith
bobo.isnumeric

bobo.replace("a", "b")  # replace a with b
"""

"""
# -------------- Lists
a = []
numbers = [1, 2, 3, 4, 5]
letters = ["a", "b", "c", "d", "e"]
letters[0] # "a"
numbers[2] # 3
letters + numbers # merge
letters * 3 # repeast list 3x
'b' in letters # returns true / false
biglist = letters+numbers

for item in biglist:
    print (item)
"""

"""
# -------------- List functions
# https://www.w3schools.com/python/python_ref_list.asp

numbers = [1, 2, 3, 4, 5]
letters = ["a", "b", "c", "d", "e"]

numbers.append(33)

numbers.extend(letters)  # same as adding together

numbers.pop  # return last element and remove from the list

numbers.insert(4, "Anything")  # insert at index location

# list numbers up to the limit that are prime
limit = input("enter the upper limit: ")
limit = int(limit)
primes = []

for num in range(2, limit + 1):
    counter = 0
    for i in range(1, num + 1):
        if num % i == 0:
            counter += 1
    if counter == 2:
        primes.append(num)

print(primes)
"""

"""
# -------------- dictionaries
d = {}
d["key"] = "value"
d[4] = "four"
d[5] = (1, 2, 3, 4)
print(d)

Jane = {}
Jane["age"] = 29
Jane["residence"] = "melbourne"
Jane["height"] = 172
print(Jane)
"""

"""
# -------------- Applied dictionaries
# Replace in text blocks using dictionaries
text = open("sample-2mb-text-file.txt")
text = text.read()
text = text[0:5600]

d = {}
d["eiusmod"] = "--splunk--"
d["penatibus"] = "--plumbus--"
d["Habitant"] = "--Da House--"

for key in d:
    text = text.replace(key, d[key])

print(text)
"""

# -------------- Logging
import logging
import os


def event_log(event):
    path = os.path.relpath(__file__)
    dir_path = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
    FORMAT = "%(asctime)-15s %(clientip)s %(user)-8s %(message)s"
    log = logging.getLogger(__name__)
    logging.basicConfig(format=FORMAT)
    log.warning("Protocol problem: %s", "connection reset", extra=event)


stage = "setup"
outcome = "success"
msg = "tested"
event = {"clientip": "192.168.0.1", "user": "fbloggs"}
event_log(event)
