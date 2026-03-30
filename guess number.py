import random
import time
months = [
    "Jan",
    "Feb",
    "March",
    "April",
    "May",
    "June",
    "July",
    "Aug",
    "Sept",
    "Oct",
    "Nov",
    "Dec"
]

map = {
    "Jan" : 6,
    "Feb" : 2,
    "March" : 2,
    "April" : 5,
    "May" : 0,
    "June" : 3,
    "July" : 5,
    "Aug" : 1,
    "Sept": 4,
    "Oct": 6,
    "Nov" : 2,
    "Dec" : 4
}

score = 0

wrong_months = []

start = time.time()
for i in range(0,12):
    curr_month = random.choice(months)
    n = int(input(curr_month + " : "))
    if n == map.get(curr_month):
        score+=1
    else:
        wrong_months.append(curr_month)
    months.remove(curr_month)

end = time.time()
print("SCORE : " ,score , "/12")
print("Wrong months: " , wrong_months)
print("Time Taken: ", end-start)


